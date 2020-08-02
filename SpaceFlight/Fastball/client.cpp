#include "launch_vehicle.hpp"
#include "init.hpp"
#include "ascent.hpp"
#include <chrono>
#include <thread>
#include <krpc.hpp>
#include <krpc/services/krpc.hpp>
#include <krpc/services/space_center.hpp>


int main() {
	auto conn = krpc::connect("Fastball SpaceFlight Program");
	auto space_center = krpc::services::SpaceCenter::SpaceCenter(&conn);
	krpc::services::KRPC krpc(&conn);
	LaunchVehicle sys;
	typedef krpc::services::KRPC::Expression Expr;
	char flight_mode{};
	double TURN_END_ALT{ 85000 };
	double SCALE_FACTOR{ 1.0 };
	std::cout << "Enter Mode : T (Static Fire), or N (Normal Ascent)" << std::endl;
	std::cin >> flight_mode;
	std::this_thread::sleep_for(std::chrono::seconds(5));

	sys.init(conn, space_center);
	systems_check(sys);
	if (flight_mode == 'T') {
		static_fire(sys);
		return 0;
	}
	liftoff_sequence(sys);
	bool cutoff = ascent(sys, TURN_END_ALT, SCALE_FACTOR);
	MECO(sys);
	deploy_fairings(sys);
	std::this_thread::sleep_for(std::chrono::seconds(3));
	stage_separation(sys);
	SES(sys);
	kick(sys);
	SECO(sys);
	deploy_payload(sys);
}