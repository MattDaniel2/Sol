#include <vector>
#include <fstream>

class Collector {

private:
    

public:
    std::vector<DataFrame> srf_vel_frameQueue;
    void collect_frame(DataFrame);
    void dump_log();
    void logger(std::string);
};

void Collector::collect_frame(DataFrame frame) {
    this->srf_vel_frameQueue.push_back(frame);
}

void Collector::logger(std::string logMsg) {
   
}

void Collector::dump_log() {
    std::string filePath = "C:\\Users\\mdani\\source\\repos\\Sol\\Data\\Collection\\Logs\\Music\\log_0.txt";
    std::ofstream ofs(filePath.c_str(), std::ios_base::out | std::ios_base::app);
    
    while (!this->srf_vel_frameQueue.empty()) {
        DataFrame frame = this->srf_vel_frameQueue.back();
        this->srf_vel_frameQueue.pop_back();
        std::string logMsg{
            "ALT: " + std::to_string(frame.mean_altitude)
            + " VEL: " + std::to_string(std::get<0>(frame.velocity)) + " " + std::to_string(std::get<1>(frame.velocity)) + " " + std::to_string(std::get<2>(frame.velocity))
            + " PITCH: " + std::to_string(frame.pitch)
            + " HEADING: " + std::to_string(frame.heading)
            + " ROLL: " + std::to_string(frame.roll)
        };
        ofs << logMsg << '\n';
    }
    ofs.close();
}