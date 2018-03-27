//
//  Counter.hpp
//  words_counter
//

#ifndef Counter_hpp
#define Counter_hpp

#include <iostream>
#include <sstream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <map>
#include <vector>
#include <thread>
#include <mutex>
#include <boost/algorithm/string.hpp>

using std::string;
using std::cerr;
using std::endl;
using std::cout;
using std::map;
using std::vector;
using std::thread;
using std::mutex;

class Counter {
private:
    map<string, int> words;
    void fill_map(const vector<string>&, int, int, map<string, int>&, mutex&);
public:
    string read_file(const char*);
    int write_file();
    bool mapping_string(const string&);
    bool mapping_string(const string&, int);
    map<string, int> get_map();
    map<string, int> get_map_sorted_by_value(); // TODO: make sorting by value with tuples and vector
    void print_map();
};

#endif /* Counter_hpp */
