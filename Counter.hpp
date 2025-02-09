//
//  Counter.hpp
//  words_counter
//

#ifndef Counter_hpp
#define Counter_hpp

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <fstream>
#include <map>
#include <vector>
#include <thread>
#include <mutex>
#include <boost/algorithm/string.hpp>
#include <boost/range/algorithm/remove_if.hpp>

using std::string;
using std::cerr;
using std::endl;
using std::cout;
using std::map;
using std::vector;
using std::thread;
using std::mutex;
using std::pair;

class Counter {
private:
    map<string, int> words;
    void fill_map(vector<string>&, int, int, map<string, int>&);
public:
    vector<string> read_file(string);
    int write_file(vector<pair<string, int>>, string);
    bool mapping_string(vector<string>&, int);
    map<string, int> get_map();
    vector<pair<string, int>> get_vector_sorted_by_key();
    vector<pair<string, int>> get_vector_sorted_by_value();
    void print_map_of_words();
};

#endif /* Counter_hpp */
