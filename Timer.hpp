//
//  Timer.hpp
//  words_counter
//

#ifndef Timer_hpp
#define Timer_hpp

#include <chrono>
#include <atomic>

typedef std::chrono::steady_clock::time_point mytime_point;
typedef std::chrono::high_resolution_clock::time_point time_point_high_res;

class Timer {
private:
    mytime_point start_point;
    mytime_point stop_point;
    inline time_point_high_res get_current_time();
    template <class T> inline long long time_ms(const T&);
public:
    mytime_point start();
    mytime_point stop();
    long long total_time_ms();
};

#endif /* Timer_hpp */
