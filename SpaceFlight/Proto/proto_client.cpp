#include "proto.hpp"
#include "proto_init.hpp"
#include "proto_ui.h"
#include "proto_ascent.hpp"
#include <chrono>
#include <thread>
#include <krpc.hpp>
#include <krpc/services/krpc.hpp>
#include <krpc/services/space_center.hpp>


int main() {
	auto conn = krpc::connect("Proto SpaceFlight Program");
	auto space_center = krpc::services::SpaceCenter::SpaceCenter(&conn);
	krpc::services::KRPC krpc(&conn);
	ProtoSystem proto_sys;
	typedef krpc::services::KRPC::Expression Expr;
	
	std::this_thread::sleep_for(std::chrono::seconds(5));

	proto_sys.init(conn, space_center);
	systems_check(conn, proto_sys);
	//static_fire(proto_sys, proto_hud);
	
	liftoff_sequence(proto_sys);
	ascent(proto_sys);
	
	MECO(proto_sys);
	deploy_fairings(proto_sys);
	stage(proto_sys);

	SES(proto_sys);
	kick(proto_sys);
	SECO(proto_sys);

	prepare_reentry(proto_sys);
}