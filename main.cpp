#include <iostream>
#include "Counter.hpp"
#include "Timer.hpp"

std::pair<int, const char*> args_parser(int argc, const char * argv[]) {
    std::pair<int, const char*> tuple;
    string err = "Error: problem with arguments\n\t counter [number of threads, default = 1] <filename>\n";
    if (argc == 3) {
        int n;
        if ((n = atoi(argv[1])) != 0) {
            tuple.first = n;
            tuple.second = argv[2];
        } else {
            cerr << err << endl;
            exit(-1);
        }
    } else if (argc == 2) {
        tuple.first = 1;
        tuple.second = argv[1];
    } else {
        cerr << err << endl;
        exit(-1);
    }
    return tuple;
}

int main(int argc, const char * argv[]) {
    
    if (argc == 1) {
        cerr << "Error: problem with arguments\n\t counter [number of threads, default = 1] <filename>\n" << endl;
        exit(-1);
    }
    
    auto pair = args_parser(argc, argv);
    auto n_threads = pair.first;
    auto filename = pair.second;
    cout << "threads: " << n_threads << endl;
    Timer timer_total;
    Timer timer_reading;
    Timer timer_analyze;
    Counter counter;

    timer_total.start();
    timer_reading.start();
    
    string str = counter.read_file(filename);
    
    timer_reading.stop();
    timer_analyze.start();
    
    counter.mapping_string(str);
    
    timer_analyze.stop();
    timer_total.stop();

    cout << "Loading: " << timer_reading.total_time_ms() << "ms" << endl;
    cout << "Analyzing: " << timer_analyze.total_time_ms() << "ms" << endl;
    cout << "Total: " << timer_total.total_time_ms() << "ms" << endl;
    
    return 0;
}
