class Interchange {
public:
    std::tuple<double,double,double> position;
    //Telemetry
    float g_force;
    double mean_altitude;
    double latitude;
    double longitude;
    std::tuple<double,double,double> velocity;
    std::tuple<double,double,double,double> rotation;
    std::tuple<double,double,double> direction;
    float pitch;
    float heading;
    float roll;
    std::tuple<double,double,double> prograde;
    std::tuple<double,double,double> retrograde;
    std::tuple<double,double,double> normal;
    std::tuple<double,double,double> anti_normal;
    std::tuple<double,double,double> radial;
    std::tuple<double,double,double> anti_radial;

     
    //Aerodynamics
    float atmo_density;
    float static_pressure;
    float dynamic_pressure;
    std::tuple<double,double,double> aerodynamic_force;
    std::tuple<double,double,double> lift;
    std::tuple<double,double,double> drag;
    float lift_coeff;
    float drag_coeff;
    float mach;
    float reynolds_number;
    float angle_of_attack;
    float sideslip_angle;
};