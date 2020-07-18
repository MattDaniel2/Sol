#pragma once
const double TURN_START_ALT = 1000;
const double TURN_END_ALT = 60000;
const double PITCH_KICK_ANGLE = 2.0;

void liftoff_sequence(ProtoSystem& proto_sys);
void MES(ProtoSystem& proto_sys);
void ascent(ProtoSystem& proto_sys);
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
	proto_sys.autoPilot().engage();
	proto_sys.autoPilot().set_reference_frame(proto_sys.getSurfaceFrame());
	proto_sys.autoPilot().target_pitch_and_heading(90, 90);
	proto_sys.updateThrottle_Q(1);
	for (int i = 10; i > 0; i--) {
		if (i == 4) {
			//ves.parts().engines().front().set_active(true);
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
	//ves.parts().engines().front().set_active(true);
	stage(proto_sys);
}

void ascent(ProtoSystem& proto_sys) {
	//Pitchover Maneuver
	//Wait until alt > 500 m
	proto_sys.updatePitchHeading((90.0 - PITCH_KICK_ANGLE), 90.0);
	proto_sys.autoPilot.wait();
	//Gravity Turn
	proto_sys.autoPilot.set_reference_frame(proto_sys.getOrbitalFrame());
	while (true) {
		proto_sys.autoPilot.set_target_direction(std::make_tuple(0, 1, 0));
		if (!proto_sys.stageCheck()) {
			std::cout << "Resources Low! Shutting Down" << std::endl;
			break;
		}
		else if (proto_sys.getFlightTick_Srf().g_force() > 6.0) {
			std::cout << "TWR Dangerous! Shutting Down" << std::endl;
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	};
}

void MECO(ProtoSystem& proto_sys) {
	proto_sys.autoPilot.set_target_direction(std::make_tuple(0, 1, 0));
	proto_sys.autoPilot.wait();
	proto_sys.getVesselTick().control().set_rcs(true);
	proto_sys.updateThrottle_Q(0);
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void stage(ProtoSystem& proto_sys) {
	proto_sys.getVesselTick().control().activate_next_stage();
}

void deploy_fairings(ProtoSystem& proto_sys) {
	for (auto fairing : proto_sys.getVesselTick().parts().fairings()) {
		std::cout << fairing.part().title() << std::endl;
		//fairing.jettison();
	}
	proto_sys.getVesselTick().control().activate_next_stage();
	std::this_thread::sleep_for(std::chrono::seconds(3));
}

void SES(ProtoSystem& proto_sys) {
	proto_sys.updateThrottle_Q(1);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	stage(proto_sys);
}

void kick(ProtoSystem& proto_sys) {
	proto_sys.autoPilot.set_target_direction(std::make_tuple(0, 1, 0));
	proto_sys.autoPilot.wait();
	while (true) {
		proto_sys.autoPilot.set_target_direction(std::make_tuple(0, 1, 0));
		if (!proto_sys.stageCheck()) {
			std::cout << "Resources Low! Shutting down" << std::endl;
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	};
}

void SECO(ProtoSystem& proto_sys) {
	proto_sys.updateThrottle_Q(0);
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void prepare_reentry(ProtoSystem& proto_sys) {
	for (auto chute : proto_sys.getVesselTick().parts().parachutes()) {
		chute.arm();
	}
	proto_sys.autoPilot.set_target_direction(std::make_tuple(0, -1, 0));
	proto_sys.autoPilot.wait();
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

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