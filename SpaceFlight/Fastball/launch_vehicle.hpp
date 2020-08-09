#pragma once
#include "stage.hpp"
#include <krpc.hpp>
#include <krpc/services/krpc.hpp>
#include <krpc/services/space_center.hpp>

class LaunchVehicle {
private:
	krpc::Stream<krpc::services::SpaceCenter::Flight> srf_flight_stream;
	krpc::Stream<krpc::services::SpaceCenter::Flight> obt_flight_stream;
	krpc::Stream<krpc::services::SpaceCenter::Vessel> vessel_stream;

	krpc::services::SpaceCenter::ReferenceFrame obt_frame;
	krpc::services::SpaceCenter::ReferenceFrame srf_frame;

	bool fairings_deployed;

public:
	krpc::Stream<double> ut_stream;
	Stage Booster;
	Stage Interstage;
	Stage Upper;
	Stage Payload;
	
	krpc::services::SpaceCenter::AutoPilot autoPilot;
	void init(krpc::Client& conn, krpc::services::SpaceCenter& space_center);

	void stage();
	void deployFairings();
	void releaseClamps();
	void setFrames();
	void setupStreams();
	void updateThrottle_Q(float throttle_step);
	void updatePitchHeading(float pitch, float heading);

	float getDynPressure();
	double getMeanAltitude();
	krpc::services::SpaceCenter::Vessel getVesselTick();
	krpc::services::SpaceCenter::Flight getFlightTick_Srf();
	krpc::services::SpaceCenter::Flight getFlightTick_Orb();
	krpc::services::SpaceCenter::ReferenceFrame getOrbitalFrame();
	krpc::services::SpaceCenter::ReferenceFrame getSurfaceFrame();
};

void LaunchVehicle::init(krpc::Client& conn, krpc::services::SpaceCenter& space_center) {
	std::cout << "Bringing up Launch Vehicle" << std::endl;
	this->ut_stream = space_center.ut_stream();
	this->vessel_stream = space_center.active_vessel_stream();
	this->autoPilot = this->vessel_stream().auto_pilot();
	this->setFrames();
	this->setupStreams();
	this->fairings_deployed = false;
	for (auto eng : this->vessel_stream().parts().engines()) {
		if (eng.part().stage() == 4) {
			std::cout << "Booster : " << eng.part().title() << std::endl;
			this->Booster.addEngine(eng);
		}
		else if (eng.part().stage() == 3) {
			std::cout << "Interstage : " << eng.part().title() << std::endl;
			this->Interstage.addEngine(eng);
		}
		else if (eng.part().stage() == 2) {
			std::cout << "Upper : " << eng.part().title() << std::endl;
			this->Upper.addEngine(eng);
		}
		else if (eng.part().stage() == 1) {
			std::cout << "Payload : " << eng.part().title() << std::endl;
			this->Payload.addEngine(eng);
		}
	}
	for (auto rcs : this->vessel_stream().parts().rcs()) {
		if (rcs.part().stage() == 4) {
			std::cout << "Booster : " << rcs.part().title() << std::endl;
			this->Booster.addRCS(rcs);
		}
		else if (rcs.part().stage() == 3) {
			std::cout << "Interstage : " << rcs.part().title() << std::endl;
			this->Interstage.addRCS(rcs);
		}
		else if (rcs.part().stage() == 2) {
			std::cout << "Upper : " << rcs.part().title() << std::endl;
			this->Upper.addRCS(rcs);
		}
		else if (rcs.part().stage() == 1) {
			std::cout << "Payload : " << rcs.part().title() << std::endl;
			this->Payload.addRCS(rcs);
		}
	}
	for (auto dec : this->vessel_stream().parts().decouplers()) {
		if (dec.part().stage() == 4) {
			std::cout << "Booster : " << dec.part().title() << std::endl;
			this->Booster.addDecoupler(dec);
		}
		else if (dec.part().stage() == 3) {
			std::cout << "Interstage : " << dec.part().title() << std::endl;
			this->Interstage.addDecoupler(dec);
		}
		else if (dec.part().stage() == 2) {
			std::cout << "Upper : " << dec.part().title() << std::endl;
			this->Upper.addDecoupler(dec);
		}
		else if (dec.part().stage() == 1) {
			std::cout << "Payload : " << dec.part().title() << std::endl;
			this->Payload.addDecoupler(dec);
		}
	}
	for (auto chute : this->vessel_stream().parts().parachutes()) {
		if (chute.part().stage() == 4) {
			std::cout << "Booster : " << chute.part().title() << std::endl;
			this->Booster.addParachute(chute);
		}
		else if (chute.part().stage() == 3) {
			std::cout << "Interstage : " << chute.part().title() << std::endl;
			this->Interstage.addParachute(chute);
		}
		else if (chute.part().stage() == 2) {
			std::cout << "Upper : " << chute.part().title() << std::endl;
			this->Upper.addParachute(chute);
		}
		else if (chute.part().stage() == 1) {
			std::cout << "Payload : " << chute.part().title() << std::endl;
			this->Payload.addParachute(chute);
		}
	}
	std::cout << "Finished System Initialization" << std::endl;
}

void LaunchVehicle::setFrames() {
	this->obt_frame = this->vessel_stream().orbit().body().non_rotating_reference_frame();
	this->srf_frame = this->vessel_stream().orbit().body().reference_frame();
}

void LaunchVehicle::setupStreams() {
	this->srf_flight_stream = this->vessel_stream().flight_stream(this->srf_frame);
	this->obt_flight_stream = this->vessel_stream().flight_stream(this->obt_frame);
}

krpc::services::SpaceCenter::Vessel LaunchVehicle::getVesselTick() {
	return this->vessel_stream();
}

krpc::services::SpaceCenter::ReferenceFrame LaunchVehicle::getOrbitalFrame() {
	return this->obt_frame;
}
krpc::services::SpaceCenter::ReferenceFrame LaunchVehicle::getSurfaceFrame() {
	return this->srf_frame;
}

krpc::services::SpaceCenter::Flight LaunchVehicle::getFlightTick_Srf() {
	return this->srf_flight_stream();
}

krpc::services::SpaceCenter::Flight LaunchVehicle::getFlightTick_Orb() {
	return this->obt_flight_stream();
}

float LaunchVehicle::getDynPressure() {
	return this->srf_flight_stream().dynamic_pressure();
}

double LaunchVehicle::getMeanAltitude() {
	return this->srf_flight_stream().mean_altitude();
}

void LaunchVehicle::updateThrottle_Q(float throttle_step) {
	this->getVesselTick().control().set_throttle(throttle_step);
};

void LaunchVehicle::updatePitchHeading(float pitch, float heading) {
	this->getVesselTick().auto_pilot().target_pitch_and_heading(pitch, heading);
}

void LaunchVehicle::stage() {
	this->getVesselTick().control().activate_next_stage();
}

void LaunchVehicle::releaseClamps() {
	for (auto clamp : this->getVesselTick().parts().launch_clamps()) {
		clamp.release();
	}
}

void LaunchVehicle::deployFairings() {
	if (!this->fairings_deployed) {
		stage();
		this->fairings_deployed = true;
	}
}
