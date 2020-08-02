#pragma once
#include "launch_vehicle.hpp"
#include <krpc.hpp>
#include <krpc/services/krpc.hpp>
#include <krpc/services/ui.hpp>
#include <krpc/services/drawing.hpp>
#include <krpc/services/space_center.hpp>

void systems_check(LaunchVehicle& sys);
void static_fire(LaunchVehicle& sys);
void kicker_control_tb(LaunchVehicle& sys, krpc::Client& conn);

void systems_check(LaunchVehicle& sys) {
	std::cout << "Entered Systems Check" << std::endl;
	auto ves = sys.getVesselTick();
	ves.control().set_sas(false);
	ves.control().set_rcs(true);
	sys.fairings_deployed = false;
	sys.Booster.activateRCS();
	sys.autoPilot.set_stopping_time(std::make_tuple(2.0, 2.0, 2.0));

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

void static_fire(LaunchVehicle& sys) {
	auto ves = sys.getVesselTick();
	sys.updateThrottle_Q(1);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	sys.Booster.activateEngines();
	while (sys.Booster.engineFuelCheck()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	proto_sys.updateThrottle_Q(0);
	std::cout << "Resources Low! Cutting Engine" << std::endl;
}