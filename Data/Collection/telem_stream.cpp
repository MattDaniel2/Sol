/* Telemetry Collection
 * Revision : Music
 */
#include <iostream>
#include <iomanip>
#include <tuple>
#include <krpc.hpp>
#include <krpc/services/space_center.hpp>



void telem_stream() {
    auto conn = krpc::connect("Telemetry Collection");
    krpc::services::SpaceCenter sc(&conn);
    auto vessel = sc.active_vessel();
    
    while (true) {
        auto pos = vsl_pos_stream();
        std::cout << std::fixed << std::setprecision(1);
        std::cout << std::get<0>(pos) << ", "
                    << std::get<1>(pos) << ", "
                    << std::get<2>(pos) << std::endl;
  }
}