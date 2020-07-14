#pragma once
const double TURN_START_ALT = 5000;
const double TURN_END_ALT = 60000;

void liftoff_sequence(ProtoSystem& proto_sys, ProtoHUD& proto_hud) {
	std::cout << "Countdown Sequence Start" << std::endl;
	auto ves = proto_sys.getVesselTick();
	ves.auto_pilot().engage();
	ves.auto_pilot().target_pitch_and_heading(90, 90);
	proto_sys.updateThrottle_Q(1);
	for (int i = 10; i > 0; i--) {
		if (i == 4) {
			ves.parts().engines().front().set_active(true);
		}
		std::cout << i << "!" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	for (auto clamp : ves.parts().launch_clamps()) {
		clamp.release();
	}
	std::cout << "Liftoff!" << std::endl;
}

void guidance_tick(ProtoSystem& proto_sys) {
	double alt = proto_sys.getMeanAltitude();
	double angle_step = (alt - TURN_START_ALT) / (TURN_END_ALT - TURN_START_ALT);
	angle_step *= 90.0;
	float curQ = proto_sys.getDynPressure();
	if (alt > TURN_START_ALT) {
		proto_sys.updatePitchHeading(90.0 - angle_step, 90.0);
		proto_sys.updateThrottle_Q(1);
	}
	if (curQ / 56000 > 1) {
		double throt_step = 0.5 - (curQ / 56000) / 5;
		proto_sys.updateThrottle_Q(throt_step);
	}
	else if (curQ / 56000 < 0.8) {
		proto_sys.updateThrottle_Q(1);
	}
	else {
		double throt_step = ((1 - curQ) / 56000) + 0.8;
		proto_sys.updateThrottle_Q(throt_step);
	}
	
}

void deploy_fairings(ProtoSystem& proto_sys, ProtoHUD& proto_hud) {
	for (auto fairing : proto_sys.getVesselTick().parts().fairings()) {
		fairing.jettison();
	}
}