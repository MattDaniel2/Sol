#pragma once
#include "proto.hpp"
#include <krpc.hpp>
#include <krpc/services/krpc.hpp>
#include <krpc/services/ui.hpp>
#include <krpc/services/drawing.hpp>
#include <krpc/services/space_center.hpp>

void systems_check(ProtoSystem& proto_sys);
void static_fire(ProtoSystem& proto_sys);
void kicker_control_tb(ProtoSystem& proto_sys, krpc::Client& conn);

void systems_check(ProtoSystem& proto_sys) {
	std::cout << "Entered Systems Check" << std::endl;
	auto ves = proto_sys.getVesselTick();
	ves.control().set_sas(false);
	ves.control().set_rcs(true);
	proto_sys.fairings_deployed = false;
	proto_sys.Booster.activateRCS();
	proto_sys.autoPilot.set_stopping_time(std::make_tuple(2.0, 2.0, 2.0));

	ves.control().set_throttle(1);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	ves.control().set_throttle(0.5);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	ves.control().set_throttle(0.75);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	ves.control().set_throttle(0);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	ves.control().set_rcs(false);
	std::cout << "Exiting Systems Check" << std::endl;
}

void static_fire(ProtoSystem& proto_sys) {
	auto ves = proto_sys.getVesselTick();
	proto_sys.updateThrottle_Q(1);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	proto_sys.Booster.activateEngines();
	while (proto_sys.Booster.engineFuelCheck()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	proto_sys.updateThrottle_Q(0);
	std::cout << "Resources Low! Cutting Engine" << std::endl;
}

void kicker_control_tb(ProtoSystem& proto_sys, krpc::Client& conn) {
	krpc::services::Drawing drawing(&conn);
	auto ref_frame = proto_sys.getVesselTick().surface_velocity_reference_frame();
	proto_sys.autoPilot.set_reference_frame(ref_frame);
	proto_sys.getVesselTick().control().set_rcs(true);
	proto_sys.autoPilot.engage();
	drawing.add_direction(std::make_tuple(0, 1, 0), ref_frame);
	//proto_sys.autoPilot.set_target_direction(std::make_tuple(0, 1, 0));
	proto_sys.autoPilot.target_pitch_and_heading(0, 90);
	proto_sys.Interstage.separate();
	proto_sys.Kicker.activateRCS();
	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(5));
		drawing.add_direction(std::make_tuple(0, -1, 0), ref_frame);
		//proto_sys.autoPilot.set_target_direction(std::make_tuple(0, -1, 0));
		proto_sys.autoPilot.target_pitch_and_heading(0, 90);
		std::cout << "Switching Retrograde!" << std::endl;
		proto_sys.autoPilot.wait();
		drawing.add_direction(std::make_tuple(0, 1, 0), ref_frame);
		//proto_sys.autoPilot.set_target_direction(std::make_tuple(0, 1, 0));
		proto_sys.autoPilot.target_pitch_and_heading(-90, 90);
		std::cout << "Switching Prograde!" << std::endl;
		proto_sys.autoPilot.wait();
	}
}