#pragma once
#include <krpc.hpp>
#include <krpc/services/krpc.hpp>
#include <krpc/services/ui.hpp>
#include <krpc/services/space_center.hpp>

class ProtoSystem {
private:
	krpc::Stream<krpc::services::SpaceCenter::Flight> srf_flight_stream;
	krpc::Stream<krpc::services::SpaceCenter::Flight> obt_flight_stream;
	krpc::Stream<krpc::services::SpaceCenter::Vessel> vessel_stream;
	krpc::services::SpaceCenter::ReferenceFrame obt_frame;
	krpc::services::SpaceCenter::ReferenceFrame srf_frame;

public:
	void init(krpc::Client& conn, krpc::services::SpaceCenter& space_center);

	void setFrames();
	void setupStreams();
	void updateThrottle_Q(float throttle_step);
	void updatePitchHeading(float pitch, float heading);

	bool engineFuelCheck();

	float getDynPressure();
	double getMeanAltitude();
	krpc::services::SpaceCenter::Vessel getVesselTick();
	krpc::services::SpaceCenter::Flight getFlightTick_Srf();
	krpc::services::SpaceCenter::Flight getFlightTick_Orb();
	krpc::services::SpaceCenter::ReferenceFrame getOrbitalFrame();
	krpc::services::SpaceCenter::ReferenceFrame getSurfaceFrame();
};

class ProtoHUD {
public:
	krpc::services::UI::Canvas	canvas;
	std::tuple<double, double>	screen_size;
	krpc::services::UI::Panel	telem_panel;
	krpc::services::UI::Panel	engine_panel;
	krpc::services::UI::Text	thrust_text;
	krpc::services::UI::Text	max_thrust_text;
	krpc::services::UI::Text	available_eng_torque_text;
	krpc::services::UI::Text	isp_text;

	void set_sys(ProtoSystem& sys);
	void update_telem();
	void update_engine();


private:
	ProtoSystem* proto_sys;
};

void ProtoSystem::init(krpc::Client& conn, krpc::services::SpaceCenter& space_center) {
	this->vessel_stream = space_center.active_vessel_stream();
	this->setFrames();
	this->setupStreams();
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

bool ProtoSystem::engineFuelCheck() {
	return this->getVesselTick().parts().engines().front().has_fuel();
}






void ProtoHUD::set_sys(ProtoSystem& sys) {
	this->proto_sys = &sys;
}

void ProtoHUD::update_telem() {
	krpc::services::SpaceCenter::Vessel vessel_tick = this->proto_sys->getVesselTick();
}

void ProtoHUD::update_engine() {
	krpc::services::SpaceCenter::Vessel vessel_tick = this->proto_sys->getVesselTick();
	auto thrust_val = (double)(vessel_tick.thrust() / 1000);
	auto max_thrust_val = (double)(vessel_tick.max_thrust() / 1000);
	//auto available_eng_torque_val = vessel_tick.available_engine_torque();
	auto isp_val = (double)vessel_tick.specific_impulse();
	this->thrust_text.set_content("Thrust: " + std::to_string(thrust_val) + " kN");
	this->max_thrust_text.set_content("Max Thrust: " + std::to_string(max_thrust_val) + " kN");
	//this->available_eng_torque_text.set_content("Max Thrust: " + std::to_string(available_eng_torque_val) + " kN");
	this->isp_text.set_content("Specific Impulse: " + std::to_string(isp_val) + " s");
}