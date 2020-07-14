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
	
	while (true) {
		guidance_tick(proto_sys);
		if (!proto_sys.engineFuelCheck()) {
			std::cout << "Flameout!" << std::endl;
			break;
		}
		Q_vec.push_back(proto_sys.getDynPressure());
		proto_hud.update_telem();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	};

	deploy_fairings(proto_sys, proto_hud);

	auto it = std::max_element(std::begin(Q_vec), std::end(Q_vec));
	std::cout << "MaxQ: " << *it << std::endl;

	while (true) {
		//just so that program doesn't shut off and let Proto go wild
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}