#include <Interchange.hpp>
#include <krpc.hpp>
#include <krpc/services/space_center.hpp>

class RefFrame {
public:
    krpc::services::SpaceCenter::ReferenceFrame ref_frame;
    krpc::Stream<std::tuple<double, double, double>> pos_stream;
};

class Aerodynamics {
public:
    krpc::Stream<float> atmo_density;
    krpc::Stream<float> static_pressure;
    krpc::Stream<float> dynamic_pressure;
    krpc::Stream<std::tuple<double,double,double>> aerodynamic_force;
    krpc::Stream<std::tuple<double,double,double>> lift;
    krpc::Stream<std::tuple<double,double,double>> drag;
    krpc::Stream<float> lift_coeff;
    krpc::Stream<float> drag_coeff;
    krpc::Stream<float> mach;
    krpc::Stream<float> reynolds_number;
    krpc::Stream<float> angle_of_attack;
    krpc::Stream<float> sideslip_angle;
};

class Flight {
public:
    Aerodynamics* aero;
    //Flight Overhead
    krpc::Stream<krpc::services::SpaceCenter::Flight> flight;
    //Telemetry
    krpc::Stream<float> g_force;
    krpc::Stream<double> mean_altitude;
    krpc::Stream<double> latitude;
    krpc::Stream<double> longitude;
    krpc::Stream<std::tuple<double,double,double>> velocity;
    krpc::Stream<std::tuple<double,double,double,double>> rotation;
    krpc::Stream<std::tuple<double,double,double>> direction;
    krpc::Stream<float> pitch;
    krpc::Stream<float> heading;
    krpc::Stream<float> roll;
    krpc::Stream<std::tuple<double,double,double>> prograde;
    krpc::Stream<std::tuple<double,double,double>> retrograde;
    krpc::Stream<std::tuple<double,double,double>> normal;
    krpc::Stream<std::tuple<double,double,double>> anti_normal;
    krpc::Stream<std::tuple<double,double,double>> radial;
    krpc::Stream<std::tuple<double,double,double>> anti_radial;

    void init(RefFrame&, krpc::services::SpaceCenter::Vessel&);
};

void Flight::init(RefFrame& ref_frame, krpc::services::SpaceCenter::Vessel& vessel) {
    this->flight = vessel.flight_stream(ref_frame.ref_frame);
    this->g_force = this->flight().g_force_stream();
    this->mean_altitude     = this->flight().mean_altitude_stream();
    this->latitude          = this->flight().latitude_stream();
    this->longitude         = this->flight().longitude_stream();
    this->velocity          = this->flight().velocity_stream();
    this->rotation          = this->flight().rotation_stream();
    this->direction         = this->flight().direction_stream();
    this->pitch             = this->flight().pitch_stream();
    this->heading           = this->flight().heading_stream();
    this->roll              = this->flight().roll_stream();
    this->prograde          = this->flight().prograde_stream();
    this->retrograde        = this->flight().retrograde_stream();
    this->normal            = this->flight().normal_stream();
    this->anti_normal       = this->flight().anti_normal_stream();
    this->radial            = this->flight().radial_stream();
    this->anti_radial       = this->flight().anti_radial_stream();

    this->aero = new Aerodynamics();
    this->aero->atmo_density        = this->flight().atmosphere_density_stream();
    this->aero->static_pressure     = this->flight().static_pressure_stream();
    this->aero->dynamic_pressure    = this->flight().dynamic_pressure_stream();
    this->aero->aerodynamic_force   = this->flight().aerodynamic_force_stream();
    this->aero->lift                = this->flight().lift_stream();
    this->aero->lift_coeff          = this->flight().lift_coefficient_stream();
    this->aero->drag                = this->flight().drag_stream();
    this->aero->drag_coeff          = this->flight().drag_coefficient_stream();
    this->aero->mach                = this->flight().mach_stream();
    this->aero->reynolds_number     = this->flight().reynolds_number_stream();
    this->aero->angle_of_attack     = this->flight().angle_of_attack_stream();
    this->aero->sideslip_angle      = this->flight().sideslip_angle_stream();
};

class Streamer {
private:
    RefFrame* srf_vel_frame;
    Flight* srf_vel_flight;
public:
    void init(krpc::services::SpaceCenter::Vessel&);
    DataFrame captureFrame();

};

void Streamer::init(krpc::services::SpaceCenter::Vessel& vessel) {
    this->srf_vel_frame = new RefFrame;
    this->srf_vel_frame->ref_frame = vessel.surface_velocity_reference_frame();
    this->srf_vel_frame->pos_stream = vessel.position_stream(this->srf_vel_frame->ref_frame);

    this->srf_vel_flight = new Flight;
    this->srf_vel_flight->init(*srf_vel_frame, vessel);
};

DataFrame Streamer::captureFrame() {
    DataFrame frame;
    frame.position          = this->srf_vel_frame->pos_stream();
    frame.g_force           = this->srf_vel_flight->g_force();
    frame.mean_altitude     = this->srf_vel_flight->mean_altitude();
    frame.velocity          = this->srf_vel_flight->velocity();
    frame.direction         = this->srf_vel_flight->direction();
    frame.pitch             = this->srf_vel_flight->pitch();
    frame.heading           = this->srf_vel_flight->heading();
    frame.roll              = this->srf_vel_flight->roll();
    frame.prograde          = this->srf_vel_flight->prograde();
    frame.retrograde        = this->srf_vel_flight->retrograde();
    frame.dynamic_pressure  = this->srf_vel_flight->aero->dynamic_pressure();
    frame.aerodynamic_force = this->srf_vel_flight->aero->aerodynamic_force();
    frame.mach              = this->srf_vel_flight->aero->mach();
    frame.angle_of_attack   = this->srf_vel_flight->aero->angle_of_attack();
    frame.sideslip_angle    = this->srf_vel_flight->aero->sideslip_angle();

    return frame;
    //std::cout << "Dataset 0 :    " << this->srf_vel_flight->g_force() << "  " << this->srf_vel_flight->mean_altitude() << "  " << this->srf_vel_flight->pitch() << std::endl;
}