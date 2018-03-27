//
//  Timer.hpp
//  words_counter
//

#ifndef Timer_hpp
#define Timer_hpp

#include <chrono>
#include <atomic>

typedef std::chrono::time_point<std::chrono::steady_clock> time_point;
typedef std::chrono::high_resolution_clock::time_point time_point_high_res;

class Timer {
private:
    time_point start_point;
    time_point stop_point;
    inline time_point_high_res get_current_time();
    template <class T> inline long long time_ms(const T&);
public:
    time_point start();
    time_point stop();
    long long total_time_ms();
};

#endif /* Timer_hpp */
