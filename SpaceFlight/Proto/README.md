# Proto family space-flight control for Explorer Program

## Capabilities
Proto 4 was capable of sending a 187kg payload 1,200km downrange with an apoapsis ~ 311km
<br>
Proto 5D finally achieved the goal of sending payload to 3000km downrange, and introduced HTP RCS for attitude control

## Vehicle Stages
The Proto Vehicle is segmented into stages such that the guidance scheme can initialize the rocket into the class structure required.
  - Stage 5 Fairings that cannot be activated through normal RPCs
  - Stage 4 Booster Parts
  - Stage 3 Interstage Parts
  - Stage 2 Kicker Parts
  - Stage 1 Payload Parts

## Guidance Scheme
For Proto 1 a quasi-linear pitch vs altitude "step" program was used for quick prototyping and ascent past the Karman Line. This was very inefficient.
<br>
Proto 2 used a "pure" gravity-turn guidance control scheme to optimize our trajectory. This was done with an initial pitchover program that and then tracking srfprograde. This was determined to be both inefficient and at the time was believed to contribute to large sideslip. 
<br>
Proto 4-5 later found that large sideslip was a result of too high of TWR, and lowered TWR combined with a sqrt function for pitch program allowed smooth and continuous turn until out of the atmosphere
<br>

## Class Structure
`ProtoSystem` -- all encompassing class for the Proto launch vehicle. At its top level it provides access to flight navigation functions and streams. Resource and part-specific information streams are encapsulated in sub-classes per stage. These subclasses are implemented from a `Stage` class.
