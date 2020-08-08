#include <Interchange.hpp>
#include <iostream>
#include <fstream>

class Collector {

private:
    std::ofstream* telem_dump;
    std::vector<Interchange> srf_vel_frameQueue;

public:
    void setup(std::ofstream&);
    void logFrames();
};

void Collector::setup(std::ofstream& fd) {
    this->telem_dump = &fd;
}