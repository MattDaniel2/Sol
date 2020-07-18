#pragma once

class Stage {
private:
    //Engines

    //Fuel Resources

    //Fairings
    
    //Decouplers


public:
    bool engineFuelCheck();

}

bool Stage::engineFuelCheck() {
	return this->engines.front().has_fuel();