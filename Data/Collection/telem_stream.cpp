/* Telemetry Collection
 * Revision : Music
 */
#include <Streamer.hpp>
#include <Collector.hpp>
#include <iostream>
#include <iomanip>
#include <tuple>
#include <krpc.hpp>
#include <krpc/services/ui.hpp>
#include <krpc/services/drawing.hpp>
#include <krpc/services/space_center.hpp>



void telem_stream() {
    auto conn = krpc::connect("Telemetry Collection");
    std::this_thread::sleep_for(std::chrono::seconds(3));
    krpc::services::SpaceCenter sc(&conn);
    krpc::services::Drawing drawing(&conn);
    auto vessel = sc.active_vessel();
    auto ref_frame = vessel.surface_velocity_reference_frame();
    
    //drawing.add_direction(std::make_tuple(0, 1, 0), ref_frame);

    Streamer* streamer = new Streamer;
    Collector* collector = new Collector;

    streamer->init(vessel);
    
    int stamp = 0;

    while (stamp < 100000) {
        DataFrame frame = streamer->captureFrame();
        collector->collect_frame(frame);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        stamp += 500;
    }
    collector->dump_log();
}