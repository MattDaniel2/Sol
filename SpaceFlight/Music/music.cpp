#include <chrono>
#include <thread>
#include <krpc.hpp>
#include <krpc/services/krpc.hpp>
#include <krpc/services/space_center.hpp>

int music_spaceflight() {
	auto conn = krpc::connect("Music 0.1A Sounding Program");
	auto space_center = krpc::services::SpaceCenter::SpaceCenter(&conn);
	krpc::services::KRPC krpc(&conn);

	std::this_thread::sleep_for(std::chrono::seconds(3));

	auto ves = space_center.active_vessel();
	auto autoPilot = ves.auto_pilot();
	
	autoPilot.engage();
	autoPilot.set_target_direction(std::make_tuple(90.0, 90.0, 0.0));
	ves.control().set_throttle(1.0);
	for (int i = 3; i > 0; i--) {
		std::cout << i << "!" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	ves.control().activate_next_stage();
	std::this_thread::sleep_for(std::chrono::milliseconds(300));
	ves.control().activate_next_stage();
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	ves.control().activate_next_stage();
	
#ifdef HIGH_C
	std::this_thread::sleep_for(std::chrono::seconds(47));
	ves.control().activate_next_stage();
	std::this_thread::sleep_for(std::chrono::seconds(5));
	ves.control().activate_next_stage();
#endif
	std::cout << "Arming parachute " << ves.parts().parachutes().front().part().title() << std::endl;
	ves.parts().parachutes().front().arm();
}