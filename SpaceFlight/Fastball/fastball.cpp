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
	double TURN_END_ALT{ 100000 };
	double SCALE_FACTOR{ 1.0 };
	std::cout << "Enter Mode : S (Static Fire), or N (Normal Ascent)" << std::endl;
	std::cin >> flight_mode;
	std::this_thread::sleep_for(std::chrono::seconds(5));

	sys.init(conn, space_center);

	if (flight_mode == 'T') {
		testbench_upper(sys);
		return 0;
	}

	if (flight_mode == 'S') {
		static_fire(sys);
		return 0;
	}
	liftoff_sequence(sys);
	bool cutoff = ascent(sys, TURN_END_ALT, SCALE_FACTOR);
	MECO(sys);
	std::this_thread::sleep_for(std::chrono::seconds(3));
	StageSeparation(sys);
	OrbitalCoast(sys);
	SES(sys);
	UpperBoost(sys);
	SECO(sys);
	DeployPayload(sys);
	
}