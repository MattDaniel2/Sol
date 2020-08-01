# Sol
A data-driven approach to a space agency in Kerbal Space Program using C++ guidance software and kRPC to control in-game spaceflight

## Very Useful Resource on C++ Windows Setup
https://www.youtube.com/watch?v=XE8GB1vOLyI

## Explorer Program
The Explorer Program encompasses my prototyping efforts across vehicle GN&C, science-experiments, and data-driven planning. This branch will work across the three projects to explore basic ways to
  - Launch vehicles on sub-orbital trajectories in excess of 200km Apogee, 3000km downrange distance
  - Recover unmanned probes or upper stages
  - Test components from the launch site
  - Activate, record, and transmit or recover scientific experiments
  - Log vehicle lifetime telemetry and perform rudimentary analysis on it
  
There will be a `Proto` launch-vehicle family designed and constructed for the Explorer program as well as related test-stations and platforms

## FastBall Program
The FastBall program will be my first real go at getting into orbit and launching artificial satellites. It will build off of the knowledge and libraries built in the Explorer Program for launch, telemetry, and analysis. Some high level requirements of a launch-vehicle for the FastBall program
  * 500kg to LEO with run-time parametrized
    * Apogee
    * Perigee
    * Inclination
    * Longitude of Ascending Node
    * Payload varying up to 1.75m diameter and 4.0m length
      * Allows us to tool fairing to a max size, possibly also one smaller fairing variant
  * Estimated 10km/s delta-v required
  * Estimated 30-ton launch vehicle
  * Targeted 33% margin per launch after tooling on regular contracts
  
 ### Launch Vehicles
 * Curveball -- branches off of proven technologies in the Explorer program, using RD-100 variant booster at 2.0m in diameter, with AJ10 powered upper stage and HTP RCS. May contain 3rd "kicker" stage for orbital insertion
 * Kickball -- uses a kerolox booster at 2.0m in diameter, with AJ10 powered upper stage
