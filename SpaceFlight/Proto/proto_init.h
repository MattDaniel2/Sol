#pragma once
#include "proto.h"
#include <krpc.hpp>
#include <krpc/services/krpc.hpp>
#include <krpc/services/space_center.hpp>

void systems_check(krpc::Client& conn, ProtoSystem& proto_sys);
void static_fire(ProtoSystem& proto_sys);

void systems_check(krpc::Client& conn, ProtoSystem& proto_sys) {
	std::cout << "Entered Systems Check" << std::endl;
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