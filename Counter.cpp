//
//  Counter.cpp
//  words_counter
//

#include "Counter.hpp"

string Counter::read_file(const char *filename) {
    
    int descriptor = open(filename, O_RDONLY);
    
    if (descriptor == -1) {
        cerr << "Error: cannot open such file, please enter your filename again." << endl;
        exit(EXIT_FAILURE);
    }
    
    const int BUFFERSIZE = 1000000;
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

int Counter::write_file() {     // TODO: Kachka is working on
    
    return 0;
}

void Counter::fill_map(const vector<string> &vect, int from, int to, map<string, int> *part_map, mutex &m) {
    map<string, int> temp_map;
    for (auto it = vect.begin() + from; it < vect.begin() + to; it++) {
        ++temp_map[*it];
    }
    std::lock_guard<std::mutex> lock(m);
    
    for(auto &it: temp_map)
        (*part_map)[it.first] += it.second;
}

bool Counter::mapping_string(const string &str, int n_threads) { // TODO: fix multiple threading
    vector<string> str_vector;
    vector<thread> threads;
    vector<map<string, int>*> maps;
    mutex m;
    words = {};
    string delimiters(" ;,:.-\n\t");
    
    string str_lower = boost::algorithm::to_lower_copy(str);
    boost::split(str_vector, str_lower, boost::is_any_of(delimiters), boost::token_compress_on);
    
    try {
        size_t max = str_vector.size();
        const size_t step = max / n_threads;
        size_t from = 0, to = from + step;
        
        for (int i = 0; i < n_threads; ++i) {
            cout << "from: " << from << ", to: " << to << endl;
            maps.push_back(new map<string, int>);
            threads.push_back(thread(Counter::fill_map, std::ref(str_vector), from, to, maps[i], std::ref(m)));

            from = to + 1;
            to += step;
            if (i == n_threads - 2) { to = max; }
        }
        
        for (auto& t : threads) {
            t.join();
        }
        
        for (map<string, int> *m : maps) {
            for (auto it = m->begin(); it != m->end(); it++) {
//                cout << it->first << " - " << it->second << endl;
                words[it->first] += it->second;
            }
        }
        
    } catch (std::exception &e) {
        std::cerr << "exception: " << e.what() << endl;
    }
    
    words.erase("");
    
    return true;
}

bool Counter::mapping_string(const string &str) { // TODO: make it with multiple threads
    vector<string> str_vector;
    words = {};
    string delimiters(" ;,:.-\n\t");
    
    string str_lower = boost::algorithm::to_lower_copy(str);
    boost::split(str_vector, str_lower, boost::is_any_of(delimiters), boost::token_compress_on);
    
    for (auto& s : str_vector) {
        ++words[s];
    }
    
    words.erase("");
    
    return true;
}

map<string, int> Counter::get_map() {
    return words;
}

void Counter::print_map_of_words() {
    for (auto& m : words) {
        cout << m.first << " - " << m.second << endl;
    }
}
