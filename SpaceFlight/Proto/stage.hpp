#pragma once
#include <krpc/services//space_center.hpp>

class Stage {
private:
    //Engines
    std::vector<krpc::services::SpaceCenter::Engine> engines;
    //RCS
    std::vector<krpc::services::SpaceCenter::RCS> rcs;
    //Fairings

    //Decouplers
    std::vector<krpc::services::SpaceCenter::Decoupler> decouplers;
    //Parachutes
    std::vector<krpc::services::SpaceCenter::Parachute> parachutes;

public:
    void addRCS(krpc::services::SpaceCenter::RCS);
    void addEngine(krpc::services::SpaceCenter::Engine);
    void addDecoupler(krpc::services::SpaceCenter::Decoupler);
    void addParachute(krpc::services::SpaceCenter::Parachute);
    void activateRCS();
    void activateEngines();
    void armParachutes();
    bool engineFuelCheck();

    //For interstages
    void separate();
};

void Stage::addRCS(krpc::services::SpaceCenter::RCS rcs_in) {
    this->rcs.push_back(rcs_in);
}

void Stage::addEngine(krpc::services::SpaceCenter::Engine engine_in) {
    this->engines.push_back(engine_in);
}

void Stage::addDecoupler(krpc::services::SpaceCenter::Decoupler decoupler_in) {
    this->decouplers.push_back(decoupler_in);
}

void Stage::addParachute(krpc::services::SpaceCenter::Parachute chute_in) {
    this->parachutes.push_back(chute_in);
}

void Stage::activateRCS() {
    for (auto rcs_thruster : this->rcs) {
        rcs_thruster.set_enabled(true);
    }
}

void Stage::activateEngines() {
    for (auto eng : this->engines) {
        eng.set_active(true);
    }
}

void Stage::armParachutes() {
    for (auto chute : this->parachutes) {
        chute.arm();
    }
}

bool Stage::engineFuelCheck() {
    for (auto eng : this->engines) {
        for (auto engFuel : eng.propellants()) {
            if ((engFuel.total_resource_available() / engFuel.total_resource_capacity() < 0.05)) {
                return false;
            }
        }
    }
    return true;
}

void Stage::separate() {
    for (auto eng : this->engines) {
        eng.set_active(true);
    }
    for (auto dec : this->decouplers) {
        dec.decouple();
    }
}