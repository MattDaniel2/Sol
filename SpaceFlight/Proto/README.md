# Proto family space-flight control for Explorer Program

## Ascent Profile
For Proto 1 a quasi-linear pitch vs altitude "step" program was used for quick prototyping and ascent past the Karman Line. This was very inefficient.
Proto 2 will use a "pure" gravity-turn guidance control scheme to optimize our trajectory. 

## Class Structure
`ProtoSystem` -- all encompassing class for the Proto launch vehicle. At its top level it provides access to flight navigation functions and streams. Resource and part-specific information streams are encapsulated in sub-classes per stage. These subclasses are implemented from a `Stage` class.
