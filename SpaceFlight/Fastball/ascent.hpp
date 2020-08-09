#pragma once
#include "launch_vehicle.hpp"
const double TOWER_CLEAR_ALT = 500;

void liftoff_sequence(LaunchVehicle& sys);
void MES(LaunchVehicle& sys);
bool ascent(LaunchVehicle& sys);
void coast(LaunchVehicle& sys);
void guidance_tick(LaunchVehicle& sys);
void MECO(LaunchVehicle& sys);
void DeployFairings(LaunchVehicle& sys);
void OrbitalCoast(LaunchVehicle& sys);
void SES(LaunchVehicle& sys);
void UpperBoost(LaunchVehicle& sys);
void SECO(LaunchVehicle& sys);
void prepare_reentry(LaunchVehicle& sys);


void liftoff_sequence(LaunchVehicle& sys) {
	std::cout << "Countdown Sequence Start" << std::endl;
	auto ves = sys.getVesselTick();
	sys.autoPilot.engage();
	sys.autoPilot.target_pitch_and_heading(90, 90);
	sys.updateThrottle_Q(1);
	//sys.Booster.setGimbals(0.5);
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
	sys.Booster.setGimbals(1.0);
	//Pitch Program Phase
	double pitch_angle = 90.0;
	while (sys.getMeanAltitude() < TURN_END_ALT) {
		if (sys.Booster.engineFuelCheck() != 1) {
			double alt_clear = SCALE_FACTOR * (sys.getMeanAltitude() - TOWER_CLEAR_ALT);
			double d_phi = sqrt(alt_clear / (TURN_END_ALT - TOWER_CLEAR_ALT));
			pitch_angle = 90.0 - std::max(0.0, std::min(90.0, (90.0 * d_phi)));
		}

		sys.autoPilot.target_pitch_and_heading(pitch_angle, 90);

		if (sys.Booster.engineFuelCheck() == 2) {
			std::cout << "Resources Low! Shutting Down" << std::endl;
			break;
		}
		if (sys.getFlightTick_Srf().g_force() > 12.0) {
			std::cout << "TWR Dangerous! Shutting Down" << std::endl;
			break;
		}
		if (sys.getMeanAltitude() > 80000) {
			sys.deployFairings();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	};
	return true;
}

void MECO(LaunchVehicle& sys) {
	sys.updateThrottle_Q(0);
	sys.Booster.shutdownEngines();
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void StageSeparation(LaunchVehicle& sys) {
	sys.deployFairings();
	std::this_thread::sleep_for(std::chrono::seconds(2));
	sys.Upper.activateRCS();
	sys.getVesselTick().control().set_rcs(true);
	sys.Interstage.separate();
	std::this_thread::sleep_for(std::chrono::seconds(2));
}

void OrbitalCoast(LaunchVehicle& sys) {
	std::cout << "Planning circularization burn" << std::endl;
	
	auto vessel = sys.getVesselTick();
	sys.autoPilot.set_reference_frame(vessel.surface_velocity_reference_frame());
	sys.autoPilot.set_target_direction(std::make_tuple(0.0, 1.0, 0.0));
	sys.autoPilot.wait();

	std::cout << "Waiting until circularization burn" << std::endl;
	// Execute burn
	double burn_time = 180;
	auto time_to_apoapsis = vessel.orbit().time_to_apoapsis_stream();
	while (time_to_apoapsis() - (burn_time / 2.0) > 0) {
		sys.autoPilot.set_target_direction(std::make_tuple(0.0, 1.0, 0.0));
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

}

void SES(LaunchVehicle& sys) {
	sys.updateThrottle_Q(0);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	sys.Upper.activateEngines();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	sys.updateThrottle_Q(1);
}

void UpperBoost(LaunchVehicle& sys) {
	std::cout << sys.getVesselTick().orbit().apoapsis() << std::endl;
	while (sys.getVesselTick().orbit().apoapsis() < 1500000) {
		if (sys.Upper.engineFuelCheck() == 2) {
			std::cout << "Resources Low! Shutting down" << std::endl;
			break;
		}
		if (sys.getMeanAltitude() > 80000) {
			sys.deployFairings();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	};
}

void SECO(LaunchVehicle& sys) {
	sys.updateThrottle_Q(0);
	sys.Upper.shutdownEngines();
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void DeployPayload(LaunchVehicle& sys) {
	sys.Payload.separate();
	sys.Payload.activateRCS();
	sys.Payload.activateEngines();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	sys.updateThrottle_Q(1);
	while (sys.getVesselTick().orbit().apoapsis() < 1500000) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	sys.updateThrottle_Q(0);
	if (sys.getVesselTick().orbit().periapsis() < 200100) {
		while (sys.getVesselTick().orbit().time_to_apoapsis() > 30) {
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		sys.updateThrottle_Q(1);
		while (sys.getVesselTick().orbit().periapsis() < 200100) {
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
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