#pragma once
#include "stage.hpp"
#include <krpc.hpp>
#include <krpc/services/krpc.hpp>
#include <krpc/services/space_center.hpp>

class ProtoSystem {
private:
	krpc::Stream<krpc::services::SpaceCenter::Flight> srf_flight_stream;
	krpc::Stream<krpc::services::SpaceCenter::Flight> obt_flight_stream;
	krpc::Stream<krpc::services::SpaceCenter::Vessel> vessel_stream;
	krpc::services::SpaceCenter::ReferenceFrame obt_frame;
	krpc::services::SpaceCenter::ReferenceFrame srf_frame;

public:
	Stage Booster;
	Stage Interstage;
	Stage Kicker;
	Stage Payload;
	bool fairings_deployed;
	krpc::services::SpaceCenter::AutoPilot autoPilot;
	void init(krpc::Client& conn, krpc::services::SpaceCenter& space_center);

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

void ProtoSystem::init(krpc::Client& conn, krpc::services::SpaceCenter& space_center) {
	std::cout << "Bringing up Proto System" << std::endl;
	this->vessel_stream = space_center.active_vessel_stream();
	this->autoPilot = this->vessel_stream().auto_pilot();
	this->setFrames();
	this->setupStreams();
	for (auto eng : this->vessel_stream().parts().engines()) {
		if (eng.part().stage() == 4) {
			this->Booster.addEngine(eng);
		}
		else if (eng.part().stage() == 3) {
			this->Interstage.addEngine(eng);
		}
		else if (eng.part().stage() == 2) {
			this->Kicker.addEngine(eng);
		}
		else if (eng.part().stage() == 1) {
			this->Payload.addEngine(eng);
		}
	}
	for (auto rcs : this->vessel_stream().parts().rcs()) {
		if (rcs.part().stage() == 4) {
			this->Booster.addRCS(rcs);
		}
		else if (rcs.part().stage() == 3) {
			this->Interstage.addRCS(rcs);
		}
		else if (rcs.part().stage() == 2) {
			this->Kicker.addRCS(rcs);
		}
		else if (rcs.part().stage() == 1) {
			this->Payload.addRCS(rcs);
		}
	}
	for (auto dec : this->vessel_stream().parts().decouplers()) {
		if (dec.part().stage() == 4) {
			this->Booster.addDecoupler(dec);
		}
		else if (dec.part().stage() == 3) {
			this->Interstage.addDecoupler(dec);
		}
		else if (dec.part().stage() == 2) {
			this->Kicker.addDecoupler(dec);
		}
		else if (dec.part().stage() == 1) {
			this->Payload.addDecoupler(dec);
		}
	}
	for (auto chute : this->vessel_stream().parts().parachutes()) {
		if (chute.part().stage() == 4) {
			this->Booster.addParachute(chute);
		}
		else if (chute.part().stage() == 3) {
			this->Interstage.addParachute(chute);
		}
		else if (chute.part().stage() == 2) {
			this->Kicker.addParachute(chute);
		}
		else if (chute.part().stage() == 1) {
			this->Payload.addParachute(chute);
		}
	}
	std::cout << "Finished System Initialization" << std::endl;
}

void ProtoSystem::setFrames() {
	this->obt_frame = this->vessel_stream().orbit().body().non_rotating_reference_frame();
	this->srf_frame = this->vessel_stream().orbit().body().reference_frame();
}

void ProtoSystem::setupStreams() {
	this->srf_flight_stream = this->vessel_stream().flight_stream(this->srf_frame);
	this->obt_flight_stream = this->vessel_stream().flight_stream(this->obt_frame);
}

krpc::services::SpaceCenter::Vessel ProtoSystem::getVesselTick() {
	return this->vessel_stream();
}

krpc::services::SpaceCenter::ReferenceFrame ProtoSystem::getOrbitalFrame() {
	return this->obt_frame;
}
krpc::services::SpaceCenter::ReferenceFrame ProtoSystem::getSurfaceFrame() {
	return this->srf_frame;
}

krpc::services::SpaceCenter::Flight ProtoSystem::getFlightTick_Srf() {
	return this->srf_flight_stream();
}

krpc::services::SpaceCenter::Flight ProtoSystem::getFlightTick_Orb() {
	return this->obt_flight_stream();
}

float ProtoSystem::getDynPressure() {
	return this->srf_flight_stream().dynamic_pressure();
}

double ProtoSystem::getMeanAltitude() {
	return this->srf_flight_stream().mean_altitude();
}

void ProtoSystem::updateThrottle_Q(float throttle_step) {
	this->getVesselTick().control().set_throttle(throttle_step);
};

void ProtoSystem::updatePitchHeading(float pitch, float heading) {
	this->getVesselTick().auto_pilot().target_pitch_and_heading(pitch, heading);
}
