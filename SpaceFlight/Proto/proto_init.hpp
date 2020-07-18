#pragma once
#include "proto.hpp"
#include <krpc.hpp>
#include <krpc/services/krpc.hpp>
#include <krpc/services/space_center.hpp>

void systems_check(krpc::Client& conn, ProtoSystem& proto_sys);
void static_fire(ProtoSystem& proto_sys);

void systems_check(krpc::Client& conn, ProtoSystem& proto_sys) {
	std::cout << "Entered Systems Check" << std::endl;
	auto ves = proto_sys.getVesselTick();
	ves.control().set_sas(false);
	ves.control().set_rcs(true);

	for (auto rcs_thruster : ves.parts().rcs()) {
		rcs_thruster.set_enabled(true);
	}

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

void static_fire(ProtoSystem& proto_sys, ProtoHUD& proto_hud) {
	auto vessel_tick = proto_sys.getVesselTick();
	vessel_tick.control().set_throttle(1);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	vessel_tick.parts().engines().front().set_active(true);
	while (proto_sys.engineFuelCheck()) {
		proto_hud.update_engine();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	std::cout << "Flameout!" << std::endl;
}