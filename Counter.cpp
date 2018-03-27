//
//  Counter.cpp
//  words_counter
//

#include "Counter.hpp"

string Counter::read_file(const char filename[]) {
    
    int descriptor = open(filename, O_RDONLY);
    
    if (descriptor == -1) {
        cerr << "Error: cannot open such file, please enter your filename again." << endl;
        exit(EXIT_FAILURE);
    }
    
    const int BUFFERSIZE = 10000;
    string result;
    char buff[BUFFERSIZE];
    ssize_t bytes;
    
    while((bytes = read(descriptor, &buff, BUFFERSIZE)) > 0) {
        for (int i = 0; i < bytes; ++i) {
            result += buff[i];
        }
    }
    close(descriptor);
    return result;
}

int Counter::write_file() {
    
    
    return 0;
}

vector<string> Counter::mapping_string(const string &str) {
    vector<string> str_vector;
    words = {};
    string delimiters(" ;,:.-\n\t");
    
    string str_lower = boost::algorithm::to_lower_copy(str);
    boost::split(str_vector, str_lower, boost::is_any_of(delimiters), boost::token_compress_on);
    
    for (auto& s : str_vector) {
        ++words[s];
    }
    
    words.erase("");
    
    return str_vector;
}

map<string, int> Counter::get_map_and_print() {
    for (auto& m : words) {
        cout << m.first << " - " << m.second << endl;
    }
    return words;
}
