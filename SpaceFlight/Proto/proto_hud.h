#pragma once
#include <krpc.hpp>
#include <krpc/services/ui.hpp>
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