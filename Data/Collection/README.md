# Software for collection of mission and launch data
May also include HUD to display telemetry in-flight to user

## Revision
`Music` 0.1

## Structure
There will be 3 major Class representations, a Streamer, an Interchange Format, and a Collector
    * Streamer holds the streams for each of sub-classes per area to be collected
    * Interchange defines the data transfer format between the Streamer and Collector
    * Collector has storage per unit time for each stream to be written out to a file at end of flight

## Telemetry to be Collected
It will be desirable to know flight statistics such as 
    * Flight
        * Position, velocity in different reference frames
            * Flight 
                * For each of 
                    * Vehicle Reference Frame
                    * Surface Reference Frame
                    * Surface Velocity Reference Frame
                    * Orbital Reference Frame
                * The following telemetry
                    * position
                    * g_force
                    * mean_altitude
                    * latitude and longitude
                    * velocity (vector) and speed (scalar) both horizontal and vertical
                    * rotation and direction
                    * pitch, heading, roll
                    * directions: prograde, retrograde, normal, anti-normal, radial, anti-radial

        * Aerodynamic forces and environment
            * For each of 
                    * Vehicle Reference Frame
                    * Surface Reference Frame
                    * Surface Velocity Reference Frame
                    * Orbital Reference Frame
                * The following telemetry
                    * atmosphere density
                    * dynamic and static pressure
                    * aerodynamic force
                    * lift and lift coefficient
                    * drag and drag coefficient
                    * mach
                    * reynold's number (?)
                    * angle of attack and side-slip angle


    * Per Stage
        * Parts
            * Print out part tree via DFS on startup and staging
            * Experiments
            * Types of Parts
            * Skin Temperature
            * Max Skin Temperature
            * Is Fuel Line
            * Fuel Lines From
        * Engine statistics per engine
            * Active?
            * Current Thrust
            * Available Thrust
            * Specific Impulse, vacuum and current
            * Propellant names and ratios
            * Has Fuel?
            * Has Modes? What are modes?
            * Gimbal Range
            * Available Torque
        * Resources
            * Per Propellant
                * Name
                * Current Amount
                * Current Requirement
                * Total Resource Available
                * Ratio
            * Electricity