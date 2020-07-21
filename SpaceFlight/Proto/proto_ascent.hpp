#pragma once
#include "proto.hpp"
const double TURN_START_ALT = 100;
const double TURN_END_ALT = 180000;
const double PITCH_KICK_ANGLE = 20.0;
const double SCALE_FACTOR = 0.5;

void liftoff_sequence(ProtoSystem& proto_sys);
void MES(ProtoSystem& proto_sys);
bool ascent(ProtoSystem& proto_sys);
void coast(ProtoSystem& proto_sys);
void guidance_tick(ProtoSystem& proto_sys);
void MECO(ProtoSystem& proto_sys);
void stage(ProtoSystem& proto_sys);
void deploy_fairings(ProtoSystem& proto_sys);
void SES(ProtoSystem& proto_sys);
void kick(ProtoSystem& proto_sys);
void SECO(ProtoSystem& proto_sys);
void prepare_reentry(ProtoSystem& proto_sys);


void liftoff_sequence(ProtoSystem& proto_sys) {
	std::cout << "Countdown Sequence Start" << std::endl;
	auto ves = proto_sys.getVesselTick();
	proto_sys.autoPilot.engage();
	proto_sys.autoPilot.target_pitch_and_heading(90, 90);
	proto_sys.updateThrottle_Q(1);
	for (int i = 10; i > 0; i--) {
		if (i == 4) {
			MES(proto_sys);
		}
		std::cout << i << "!" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	for (auto clamp : ves.parts().launch_clamps()) {
		clamp.release();
	}
	std::cout << "Liftoff!" << std::endl;
}

void MES(ProtoSystem& proto_sys) {
	proto_sys.Booster.activateEngines();
}

bool ascent(ProtoSystem& proto_sys) {
//Pitchover Maneuver
	while (proto_sys.getMeanAltitude() < TURN_START_ALT) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	/*
	for (double i = 0.0; i < PITCH_KICK_ANGLE; i++) {
		proto_sys.updatePitchHeading((90.0 - i), 90.0);
		proto_sys.autoPilot.wait();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	std::this_thread::sleep_for(std::chrono::seconds(4));
	*/
//Gravity Turn
	//proto_sys.autoPilot.set_reference_frame(proto_sys.getVesselTick().surface_velocity_reference_frame());
	while (proto_sys.getMeanAltitude() < 180000) {
		//proto_sys.autoPilot.set_target_direction(std::make_tuple(0, 1, 0));
		double alt_diff = SCALE_FACTOR * proto_sys.getMeanAltitude() - TURN_START_ALT;
		double delta = ((proto_sys.getMeanAltitude() - TURN_START_ALT) / alt_diff);
		double pitch_angle = 90.0 - std::max(0.0, std::min(90.0, (90.0 * sqrt(delta))));
		std::cout << "Pitch Angle : " << pitch_angle << "ALT_DIFF" << alt_diff << "Delta : " << delta << std::endl;
		proto_sys.autoPilot.target_pitch_and_heading(pitch_angle, 90);
		if (!proto_sys.Booster.engineFuelCheck()) {
			std::cout << "Resources Low! Shutting Down" << std::endl;
			return false;
		}
		else if (proto_sys.getFlightTick_Srf().g_force() > 15.0) {
			std::cout << "TWR Dangerous! Shutting Down" << std::endl;
			return false;
		}
		/*
		if (proto_sys.getMeanAltitude() > 75000) {
			deploy_fairings(proto_sys);
		}
		*/
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	};
	return true;
}

void coast(ProtoSystem& proto_sys) {
	while (proto_sys.getMeanAltitude() < 100000) {
		proto_sys.autoPilot.set_target_direction(std::make_tuple(0, 1, 0));
		if (proto_sys.getMeanAltitude() > 85000) {
			deploy_fairings(proto_sys);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	};
}

void MECO(ProtoSystem& proto_sys) {
	proto_sys.autoPilot.set_target_direction(std::make_tuple(0, 1, 0));
	proto_sys.updateThrottle_Q(0);
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void stage_separation(ProtoSystem& proto_sys) {
	proto_sys.Kicker.activateRCS();
	proto_sys.getVesselTick().control().set_rcs(true);
	proto_sys.Interstage.separate();
}

void stage(ProtoSystem& proto_sys) {
	proto_sys.getVesselTick().control().activate_next_stage();
}

void deploy_fairings(ProtoSystem& proto_sys) {
	/*
	for (auto fairing : proto_sys.getVesselTick().parts().fairings()) {
		std::cout << fairing.part().title() << fairing.jettisoned() << std::endl;
		fairing.jettison();
	}
	*/
	if (!proto_sys.fairings_deployed) {
		stage(proto_sys);
		proto_sys.fairings_deployed = true;
	}
	std::this_thread::sleep_for(std::chrono::seconds(3));
}

void SES(ProtoSystem& proto_sys) {
	proto_sys.updateThrottle_Q(1);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	proto_sys.Kicker.activateEngines();
}

void kick(ProtoSystem& proto_sys) {
	/*
	proto_sys.autoPilot.set_reference_frame(proto_sys.getVesselTick().orbital_reference_frame());
	proto_sys.autoPilot.set_target_direction(std::make_tuple(0, 1, 0));
	try {
		proto_sys.autoPilot.wait();
	}
	catch (...) {
		std::cout << "Exception in kick:autoPilot.wait()" << std::endl;
	}
	*/
	SES(proto_sys);
	std::this_thread::sleep_for(std::chrono::seconds(5));
	proto_sys.autoPilot.set_target_pitch(0);
	while (true) {
		if (!proto_sys.Kicker.engineFuelCheck()) {
			std::cout << "Resources Low! Shutting down" << std::endl;
			break;
		}
		if (proto_sys.getMeanAltitude() > 85000) {
			deploy_fairings(proto_sys);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	};
}

void SECO(ProtoSystem& proto_sys) {
	proto_sys.updateThrottle_Q(0);
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void prepare_reentry(ProtoSystem& proto_sys) {
	std::this_thread::sleep_for(std::chrono::seconds(1));
	proto_sys.Payload.separate();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	proto_sys.Payload.armParachutes();
	proto_sys.autoPilot.set_target_direction(std::make_tuple(0, -1, 0));
	proto_sys.autoPilot.wait();
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}
/*
void guidance_tick(ProtoSystem& proto_sys) {
	double alt = proto_sys.getMeanAltitude();
	double angle_step = 0.75 * (alt - TURN_START_ALT) / (TURN_END_ALT - TURN_START_ALT);
	angle_step *= 90.0;
	float curQ = proto_sys.getDynPressure();
	if (alt > TURN_START_ALT) {
		proto_sys.updatePitchHeading(90.0 - angle_step, 90.0);
		proto_sys.updateThrottle_Q(1);
	}
}
*/