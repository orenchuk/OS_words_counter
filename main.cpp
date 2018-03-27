#include <iostream>
#include <string>
#include "Counter.hpp"

using std::string;

int main(int argc, const char * argv[]) {
    Counter c;
    string s = c.read_file(argv[1]);
    c.mapping_string(s);
    c.get_map_and_print();
    
    return 0;
}
