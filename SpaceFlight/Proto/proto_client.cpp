#include "proto.h"
#include "proto_init.h"
#include "proto_ui.h"
#include "proto_ascent.h"
#include <chrono>
#include <thread>
#include <krpc.hpp>
#include <krpc/services/krpc.hpp>
#include <krpc/services/space_center.hpp>


int main() {
	auto conn = krpc::connect("Proto SpaceFlight Program");
	auto space_center = krpc::services::SpaceCenter::SpaceCenter(&conn);
	krpc::services::KRPC krpc(&conn);
	std::this_thread::sleep_for(std::chrono::seconds(5));
	ProtoSystem proto_sys;
	ProtoHUD proto_hud;

	std::cout << "Bringing up Proto System" << std::endl;
	proto_sys.init(conn, space_center);
	std::cout << "Finished System Initialization" << std::endl;
	
	systems_check(conn, proto_sys);
	setup_hud(proto_sys, conn, proto_hud);
	//static_fire(proto_sys, proto_hud);
	
	liftoff_sequence(proto_sys, proto_hud);
	std::vector<float> Q_vec;
	
	while (proto_sys.getMeanAltitude() < 60000) {
		guidance_tick(proto_sys);
		if (!proto_sys.engineFuelCheck()) {
			std::cout << "Flameout!" << std::endl;
			break;
		}
		Q_vec.push_back(proto_sys.getDynPressure());
		proto_hud.update_telem();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	};
	proto_sys.getVesselTick().control().set_rcs(true);
	proto_sys.updateThrottle_Q(0);
	proto_sys.updatePitchHeading(0.0, 90.0);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	deploy_fairings(proto_sys);
	std::this_thread::sleep_for(std::chrono::seconds(3));
	stage(proto_sys);

	auto it = std::max_element(std::begin(Q_vec), std::end(Q_vec));
	std::cout << "MaxQ: " << *it << std::endl;

	//point towards retrograde
	auto retro_dir = proto_sys.getFlightTick_Orb().retrograde();
	proto_sys.getVesselTick().auto_pilot().set_target_direction(retro_dir);
	for (auto chute : proto_sys.getVesselTick().parts().parachutes()) {
		std::cout << chute.part().title() << std::endl;
		chute.arm();
	}
	
	while (true) {
		auto retro_dir = proto_sys.getFlightTick_Orb().retrograde();
		proto_sys.getVesselTick().auto_pilot().set_target_direction(retro_dir);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}