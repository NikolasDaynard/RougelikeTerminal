#include <string>
#include <chrono>
#include <vector>
#include <map>

class Timer {
private:
    std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
public:
    /** returns current time in ms */
    long long readTimer() const {
        auto end_time = std::chrono::system_clock::now();
        auto duration = end_time - startTime;
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }
    void resetTimer() {
        startTime = std::chrono::system_clock::now();
    }
};