#include <iostream>
#include <chrono>
#include <thread>
#include <krpc.hpp>
#include <krpc/services/krpc.hpp>
#include <krpc/services/space_center.hpp>

void initiate_heading(krpc::services::SpaceCenter::Vessel& hello_vessel);

void start_telemetry(krpc::services::SpaceCenter::Vessel& hello_vessel);

void ignition_sequence(krpc::services::SpaceCenter::Vessel& hello_vessel);

void deploy_parachutes(krpc::services::SpaceCenter::Vessel& hello_vessel, krpc::services::KRPC& krpc, krpc::Client& conn);

int main() {
	auto conn = krpc::connect("Hello World SpaceFlight Program");
	krpc::services::KRPC krpc(&conn);
	krpc::services::SpaceCenter space_center(&conn);
	std::this_thread::sleep_for(std::chrono::seconds(5));
	auto vessel = space_center.active_vessel();
	auto flight_info = vessel.flight();
	//start_telemetry(vessel);
	std::cout << flight_info.mean_altitude() << std::endl;

	initiate_heading(vessel);

	ignition_sequence(vessel);
	
	while (true) {
		if (vessel.parts().engines().front().thrust() == 0) {
			std::cout << "Flameout! Occurred at " << flight_info.mean_altitude() << std::endl;
			break;
		}
	}
	
	deploy_parachutes(vessel, krpc, conn);
}

void initiate_heading(krpc::services::SpaceCenter::Vessel& hello_vessel) {
	hello_vessel.auto_pilot().target_pitch_and_heading(90, 90);
	hello_vessel.auto_pilot().engage();
	hello_vessel.control().set_throttle(1);
	std::this_thread::sleep_for(std::chrono::seconds(10));
}



void ignition_sequence(krpc::services::SpaceCenter::Vessel& hello_vessel) {
	std::cout << "Main Engine Ignition Start" << std::endl;
	hello_vessel.control().activate_next_stage();
	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cout << "Liftoff!" << std::endl;
	hello_vessel.control().activate_next_stage();
}

void deploy_parachutes(krpc::services::SpaceCenter::Vessel& hello_vessel, krpc::services::KRPC& krpc, krpc::Client& conn) {
	typedef krpc::services::KRPC::Expression Expr;
	std::cout << "Waiting until altitude < 1km" << std::endl;
	auto srf_alt = hello_vessel.flight().surface_altitude_call();
	auto expr = Expr::less_than(conn, Expr::call(conn, srf_alt), Expr::constant_double(conn, 1000));
	auto event = krpc.add_event(expr);
	event.acquire();
	event.wait();
	event.release();
	std::cout << "Deploying Parachutes!" << std::endl;
	for (auto parachute : hello_vessel.parts().parachutes()) {
		parachute.deploy();
	}
}

void start_telemetry(krpc::services::SpaceCenter::Vessel& hello_vessel) {
	auto command_telemetry = hello_vessel.parts().controlling().experiment();
	std::cout << "Found command experiment in part: " << hello_vessel.parts().controlling() << std::endl;
	std::cout << hello_vessel.parts().controlling().name() << std::endl;
	std::cout << hello_vessel.parts().controlling().title() << std::endl;
	for (auto part : hello_vessel.parts().all()) {
		std::cout << "Part: " << part.title() << std::endl;
	}
	for (auto experiment : hello_vessel.parts().experiments()) {
		std::cout << "Experiment: " << experiment << std::endl;
	}
	for (auto sensor : hello_vessel.parts().sensors()) {
		std::cout << "Sensor: " << sensor << std::endl;
	}
	for (auto resource : hello_vessel.resources().all()) {
		std::cout << "Resource: " << resource.name() << std::endl;
	}
	std::cout << "Exploring Thermometer" << std::endl;
	auto thermo = hello_vessel.parts().all()[1];
	std::cout << thermo.experiment() << thermo.experiment().science_subject() << thermo.modules().front() << std::endl;
	std::cout << thermo.sensor().value() << std::endl;
	std::cout << "Exploring BoosterCam" << std::endl;
	auto cam = hello_vessel.parts().all()[3];
	std::cout << cam.sensor() << cam.experiment().science_subject() << cam.modules().front() << std::endl;
	//std::cout << "Has science subject" << command_telemetry.science_subject() << std::endl;
	//command_telemetry.run();
	//command_telemetry.transmit();
}