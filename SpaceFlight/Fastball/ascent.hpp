#pragma once
#include "launch_vehicle.hpp"
const double TOWER_CLEAR_ALT = 500;

void liftoff_sequence(LaunchVehicle& sys);
void MES(LaunchVehicle& sys);
bool ascent(LaunchVehicle& sys);
void coast(LaunchVehicle& sys);
void guidance_tick(LaunchVehicle& sys);
void MECO(LaunchVehicle& sys);
void stage(LaunchVehicle& sys);
void deploy_fairings(LaunchVehicle& sys);
void SES(LaunchVehicle& sys);
void kick(LaunchVehicle& sys);
void SECO(LaunchVehicle& sys);
void prepare_reentry(LaunchVehicle& sys);


void liftoff_sequence(LaunchVehicle& sys) {
	std::cout << "Countdown Sequence Start" << std::endl;
	auto ves = sys.getVesselTick();
	sys.autoPilot.engage();
	sys.autoPilot.target_pitch_and_heading(90, 90);
	sys.updateThrottle_Q(1);
	for (int i = 10; i > 0; i--) {
		if (i == 4) {
			MES(sys);
		}
		std::cout << i << "!" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	sys.releaseClamps();
	std::cout << "Liftoff!" << std::endl;
}

void MES(LaunchVehicle& sys) {
	sys.Booster.activateEngines();
}

bool ascent(LaunchVehicle& sys, double TURN_END_ALT, double SCALE_FACTOR) {
	//Wait until clearing tower
	while (sys.getMeanAltitude() < TOWER_CLEAR_ALT) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	//Pitch Program Phase
	double pitch_angle = 90.0;
	while (sys.getMeanAltitude() < TURN_END_ALT) {
		double alt_clear = SCALE_FACTOR * (sys.getMeanAltitude() - TOWER_CLEAR_ALT);
		double d_phi = sqrt(alt_clear / (TURN_END_ALT - TOWER_CLEAR_ALT));
		pitch_angle = 90.0 - std::max(0.0, std::min(90.0, (90.0 * d_phi)));
		sys.autoPilot.target_pitch_and_heading(pitch_angle, 90);
		if (sys.Booster.engineFuelCheck() == 2) {
			std::cout << "Resources Low! Shutting Down" << std::endl;
			break;
		}
		else if (sys.Booster.engineFuelCheck() == 1) {
			break;
		}
		else if (sys.getFlightTick_Srf().g_force() > 12.0) {
			std::cout << "TWR Dangerous! Shutting Down" << std::endl;
			break;
		}
		if (sys.getMeanAltitude() > 80000) {
			deploy_fairings(sys);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	};
	while (true) {
		sys.autoPilot.target_pitch_and_heading(pitch_angle, 90);
		if (sys.Booster.engineFuelCheck() == 2) {
			std::cout << "Resources Low! Shutting Down" << std::endl;
			return false;
		}
		else if (sys.getFlightTick_Srf().g_force() > 12.0) {
			std::cout << "TWR Dangerous! Shutting Down" << std::endl;
			return false;
		}
		if (sys.getMeanAltitude() > 80000) {
			deploy_fairings(sys);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	return true;
}

void MECO(LaunchVehicle& sys) {
	sys.updateThrottle_Q(0);
	sys.Booster.shutdownEngines();
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void stage_separation(LaunchVehicle& sys) {
	sys.Kicker.activateRCS();
	sys.getVesselTick().control().set_rcs(true);
	sys.Interstage.separate();
	std::this_thread::sleep_for(std::chrono::seconds(2));
}

void stage(LaunchVehicle& sys) {
	sys.getVesselTick().control().activate_next_stage();
}

void deploy_fairings(LaunchVehicle& sys) {
	if (!sys.fairings_deployed) {
		stage(sys);
		sys.fairings_deployed = true;
	}
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void SES(LaunchVehicle& sys) {
	sys.updateThrottle_Q(1);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	sys.Kicker.activateEngines();
}

void kick(LaunchVehicle& sys) {
	while (true) {
		if (sys.Kicker.engineFuelCheck() == 2) {
			std::cout << "Resources Low! Shutting down" << std::endl;
			break;
		}
		if (sys.getMeanAltitude() > 80000) {
			deploy_fairings(sys);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	};
}

void SECO(LaunchVehicle& sys) {
	sys.updateThrottle_Q(0);
	sys.Kicker.shutdownEngines();
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void deploy_payload(LaunchVehicle& sys) {
	sys.Payload.separate();
	sys.Payload.activateRCS();
	sys.Payload.activateEngines();
	sys.autoPilot.target_pitch_and_heading(0.0, 90.0);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	sys.updateThrottle_Q(1);
	sys.Payload.armParachutes();
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void prepare_reentry(LaunchVehicle& sys) {
	std::this_thread::sleep_for(std::chrono::seconds(1));
	sys.Payload.separate();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	sys.Payload.armParachutes();
	sys.autoPilot.set_target_direction(std::make_tuple(0, -1, 0));
	sys.autoPilot.wait();
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}