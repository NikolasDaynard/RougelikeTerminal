#include <string>
#include <chrono>
#include <vector>

class Timer {
private:
    std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
public:
    /** returns current time in ms */
    long long readTimer(std::string name) const {
        auto end_time = std::chrono::system_clock::now();
        auto duration = end_time - startTime;
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }
    void resetTimer(std::string name) {
        startTime = std::chrono::system_clock::now();
    }
};

class Time {
private:
    std::vector<Timer> timers;
public:
    void createTimer(std::string name) {
        timers.push_back(Timer());
    }
    /** returns current time in ms */
    int readTimer(std::string name) {
        
    }
    void resetTimer(std::string name) {

    }
};