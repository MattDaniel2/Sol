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
	char flight_mode{};
	double TURN_END_ALT{ 80000 };
	double SCALE_FACTOR{ 0.7 };
	std::cout << "Enter Mode : T (Static Fire), S (High Altitude Sounding) or N (Normal Ascent)" << std::endl;
	std::cin >> flight_mode;
	std::this_thread::sleep_for(std::chrono::seconds(5));

	proto_sys.init(conn, space_center);
	systems_check(proto_sys);
	if (flight_mode == 'T') {
		static_fire(proto_sys);
		return 0;
	}
	else if (flight_mode == 'S') {
		//TURN_END_ALT = 65000;
		SCALE_FACTOR = 0.1;
	}
	
	liftoff_sequence(proto_sys);
	bool cutoff = ascent(proto_sys, TURN_END_ALT, SCALE_FACTOR);
	MECO(proto_sys);
	deploy_fairings(proto_sys);
	std::this_thread::sleep_for(std::chrono::seconds(3));
	if (flight_mode != 'S') {
		stage_separation(proto_sys);
		SES(proto_sys);
		kick(proto_sys);
		SECO(proto_sys);
		deploy_payload(proto_sys);
	}
}