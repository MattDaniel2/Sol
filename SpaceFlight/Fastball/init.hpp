#pragma once
#include "launch_vehicle.hpp"
#include <krpc.hpp>
#include <krpc/services/krpc.hpp>
#include <krpc/services/ui.hpp>
#include <krpc/services/drawing.hpp>
#include <krpc/services/space_center.hpp>

void systems_check(LaunchVehicle& sys);
void static_fire(LaunchVehicle& sys);

void systems_check(LaunchVehicle& sys) {
	std::cout << "Entered Systems Check" << std::endl;
	auto ves = sys.getVesselTick();
	ves.control().set_sas(false);
	sys.Booster.activateRCS();
	sys.autoPilot.set_stopping_time(std::make_tuple(2.0, 2.0, 2.0));
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
	sys.updateThrottle_Q(0);
	std::cout << "Resources Low! Cutting Engine" << std::endl;
}

void testbench_upper(LaunchVehicle& sys) {
//OrbitalCoast(sys);
	auto vessel = sys.getVesselTick();
	sys.Upper.activateRCS();
	sys.getVesselTick().control().set_rcs(true);
	sys.autoPilot.engage();
	sys.autoPilot.set_deceleration_time(std::make_tuple(2.0, 2.0, 2.0));
	sys.autoPilot.set_deceleration_time(std::make_tuple(0.25, 0.25, 0.25));
	sys.autoPilot.set_reference_frame(vessel.orbital_reference_frame());
	std::cout << "Pointing Prograde" << std::endl;
	sys.autoPilot.set_target_direction(std::make_tuple(0.0, 1.0, 0.0));
	sys.autoPilot.wait();
	std::cout << "Pointing Retrograde" << std::endl;
	sys.autoPilot.set_target_direction(std::make_tuple(0.0, -1.0, 0.0));
	sys.autoPilot.wait();
	std::cout << "Pointing Normal" << std::endl;
	sys.autoPilot.set_target_direction(std::make_tuple(0.0, 0.0, 1.0));
	sys.autoPilot.wait();
	std::cout << "Pointing Anti-Normal" << std::endl;
	sys.autoPilot.set_target_direction(std::make_tuple(0.0, 0.0, -1.0));
	sys.autoPilot.wait();
	std::cout << "Pointing Anti-Radial" << std::endl;
	sys.autoPilot.set_target_direction(std::make_tuple(1.0, 0.0, 0.0));
	sys.autoPilot.wait();
	std::cout << "Pointing Radial" << std::endl;
	sys.autoPilot.set_target_direction(std::make_tuple(-1.0, 0.0, 0.0));
	sys.autoPilot.wait();

	std::cout << "Checking Engines" << std::endl;
	sys.updateThrottle_Q(0);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	sys.Upper.activateEngines();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	sys.updateThrottle_Q(1);

	std::cout << "Checking Boost" << std::endl;
	std::cout << sys.getVesselTick().orbit().apoapsis() << std::endl;
	while (sys.getVesselTick().orbit().apoapsis() < (double)1500000) {
		if (sys.Upper.engineFuelCheck() == 2) {
			std::cout << "Resources Low! Shutting down" << std::endl;
			break;
		}
		if (sys.getMeanAltitude() > 80000) {
			sys.deployFairings();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	};
	std::cout << "Testbench Done!" << std::endl;
}
