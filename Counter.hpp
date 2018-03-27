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
#include <boost/algorithm/string.hpp>

using std::string;
using std::cerr;
using std::endl;
using std::cout;
using std::map;
using std::vector;

class Counter {
private:
    map<string, int> words;
public:
    string read_file(const char*);
    int write_file();
    vector<string> mapping_string(const string&);
    map<string, int> get_map_and_print();
};

#endif /* Counter_hpp */
