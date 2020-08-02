# Fastball family space-flight control for Fastball Program

## Capabilities
Camera control throughout mission

## Vehicle Stages
Launch Vehicles of the Fastball family are segmented into stages such that the guidance scheme can initialize the rocket into the class structure required.
  - Stage 5 Fairings that cannot be activated through normal RPCs
  - Stage 4 Booster Parts
  - Stage 3 Interstage Parts
  - Stage 2 Upper Stage Parts
  - Stage 1 Payload Parts / Kicker Parts

## Guidance Scheme
There are multiple phases of flight for any kickball vehicle due to the requirement of orbital insertions at different energies
  - Ascent Phase
  - Circularization and Parking Phase
  - Insertion Phase

## Class Structure
`LaunchVehicle` -- all encompassing class for the launch vehicle. At its top level it provides access to flight navigation functions and streams. Resource and part-specific information streams are encapsulated in sub-classes per stage. These subclasses are implemented from a `Stage` class

## History of Operation and Revisions