#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "Counter.hpp"
#include "Timer.hpp"

struct configuration {
    string infile;
    string out_by_a = "res_a.txt";
    string out_by_n = "res_n.txt";
    int threads = 1;
};

configuration args_parser(int argc, const char * argv[]) {
    auto args = configuration();
    string err = "Error: problem with arguments\n\t counter [number of threads, default = 1] <filename>\n";
    if (argc == 3) {
        int n;
        if ((n = atoi(argv[1])) != 0) {
            args.threads = n;
            args.infile = argv[2];
        } else {
            cerr << err << endl;
            exit(-1);
        }
    } else if (argc == 2) {
        args.infile = argv[1];
    } else {
        cerr << err << endl;
        exit(-1);
    }
    
    return args;
}

configuration args_parser_ini(string filename) {
    auto args = configuration();
    boost::property_tree::ptree tree;
    boost::property_tree::ini_parser::read_ini(filename, tree);
    
    try {
        args.infile = tree.get<string>("infile");
        args.out_by_a = tree.get<string>("out_by_a");
        args.out_by_n = tree.get<string>("out_by_n");
        args.threads = tree.get<int>("threads");
    } catch (std::exception &e) {
        cerr << e.what() << endl;
    }
    
    return args;
}

int main(int argc, const char * argv[]) {
    
    configuration Config;
    
    if (argc == 1) {
        Config = args_parser_ini("config.ini");
    } else {
        Config = args_parser(argc, argv);
    }
    
    cout << "threads: " << Config.threads << endl;
    
    Timer timer_total;
    Timer timer_reading;
    Timer timer_analyze;
    Counter counter;

    timer_total.start();
    timer_reading.start();
    
    string str = counter.read_file(Config.infile.c_str());
    
    timer_reading.stop();
    timer_analyze.start();
    
    counter.mapping_string(str, Config.threads);
    
    timer_analyze.stop();
    timer_total.stop();
    
    counter.get_vector_sorted_by_value();
    
    counter.print_map_of_words();

    cout << "Loading: " << timer_reading.total_time_ms() << "ms" << endl;
    cout << "Analyzing: " << timer_analyze.total_time_ms() << "ms" << endl;
    cout << "Total: " << timer_total.total_time_ms() << "ms" << endl;
    
    return 0;
}
