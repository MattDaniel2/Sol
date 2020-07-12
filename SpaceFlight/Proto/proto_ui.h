#pragma once
#include <krpc.hpp>
#include <krpc/services/ui.hpp>

void setup_hud(ProtoSystem& proto_sys, krpc::Client& conn, ProtoHUD& hud) {
	krpc::services::UI ui(&conn);
	hud.set_sys(proto_sys);
	hud.canvas = ui.stock_canvas();
	//Get size of game window in pixels
	hud.screen_size = hud.canvas.rect_transform().size();
	//Add UI panels
	hud.telem_panel = hud.canvas.add_panel();
	hud.engine_panel = hud.canvas.add_panel();
	//Position panel on screen
	auto rectTelem = hud.telem_panel.rect_transform();
	rectTelem.set_size(std::make_tuple(300, 200));
	rectTelem.set_position(std::make_tuple(110 - ((std::get<0>(hud.screen_size)) / 2), 0));

	auto rectEngine = hud.engine_panel.rect_transform();
	rectEngine.set_size(std::make_tuple(300, 200));
	rectEngine.set_position(std::make_tuple(110 - ((std::get<0>(hud.screen_size)) / 2), 400));
	//Add Engine Fields...
	hud.thrust_text = hud.engine_panel.add_text("Thrust: 0 kN");
	hud.thrust_text.rect_transform().set_position(std::make_tuple(0, -20));
	hud.thrust_text.set_color(std::make_tuple(1, 1, 1));
	hud.thrust_text.set_size(18);

	hud.max_thrust_text = hud.engine_panel.add_text("Max Thrust: 0 kN");
	hud.max_thrust_text.rect_transform().set_position(std::make_tuple(0, -40));
	hud.max_thrust_text.set_color(std::make_tuple(1, 1, 1));
	hud.max_thrust_text.set_size(14);

	hud.isp_text = hud.engine_panel.add_text("ISP: 0 s");
	hud.isp_text.rect_transform().set_position(std::make_tuple(0, -60));
	hud.isp_text.set_color(std::make_tuple(1, 1, 1));
	hud.isp_text.set_size(14);
}
