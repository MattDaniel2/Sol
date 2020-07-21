#include "proto.hpp"
#include "proto_init.hpp"
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
	//kicker_control_tb(proto_sys, conn);
	//systems_check(proto_sys);
	//static_fire(proto_sys);
	
	liftoff_sequence(proto_sys);
	bool cutoff = ascent(proto_sys);
	MECO(proto_sys);
	deploy_fairings(proto_sys);

	stage_separation(proto_sys);

	SES(proto_sys);
	kick(proto_sys);
	SECO(proto_sys);
	std::this_thread::sleep_for(std::chrono::seconds(10));

	//prepare_reentry(proto_sys);
	
}