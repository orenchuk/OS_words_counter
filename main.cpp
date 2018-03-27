#include <iostream>
#include "Counter.hpp"
#include "Timer.hpp"

int main(int argc, const char * argv[]) {
    Timer timer_total;
    Timer timer_reading;
    Timer timer_analyze;
    Counter counter;
    
    timer_total.start();
    timer_reading.start();
    
    string s = counter.read_file(argv[1]); // TODO: make parser for multiple arguments
    
    timer_reading.stop();
    timer_analyze.start();
    
    counter.mapping_string(s);
    
    timer_analyze.stop();
    timer_total.stop();
    
    cout << "Loading: " << timer_reading.total_time_ms() << "ms" << endl;
    cout << "Analyzing: " << timer_analyze.total_time_ms() << "ms" << endl;
    cout << "Total: " << timer_total.total_time_ms() << "ms" << endl;
    
    return 0;
}
