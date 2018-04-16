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

int Counter::write_file(vector<pair<string, int>> vect, string filename) {
    std::ofstream outfile(filename);
    int index = 0;
    
    for (auto& v : vect) {
        ++index;
        outfile << index << ". " << v.first << "\t" << v.second << endl;
    }
    
    outfile.close();
    return 0;
}

void Counter::fill_map(const vector<string> &vect, int from, int to, map<string, int> &part_map, mutex &m) {
    for (auto it = vect.begin() + from; it < vect.begin() + to; it++) {
        ++part_map[*it];
    }
}

bool Counter::mapping_string(const string &str, int n_threads) {
    vector<string> str_vector;
    vector<thread> threads;
    vector<map<string, int>> maps(n_threads);
    mutex m;
    words = {};
    string delimiters(" ;,:.\n\t");
    
    string str_lower = boost::algorithm::to_lower_copy(str);
    boost::split(str_vector, str_lower, boost::is_any_of(delimiters), boost::token_compress_on);
    
    try {
        size_t max = str_vector.size();
        const size_t step = max / n_threads;
        size_t from = 0, to = from + step;
        
        for (int i = 0; i < n_threads; ++i) {
//            cout << "from: " << from << ", to: " << to << endl;
            threads.emplace_back(&Counter::fill_map, this, std::ref(str_vector), from, to, std::ref(maps[i]), std::ref(m));

            from = to;
            to += step;
            if (i == n_threads - 2) { to = max; }
        }
        
        for (auto& t : threads) {
            t.join();
        }
        
        for (auto &m : maps) {
            for (auto it = m.begin(); it != m.end(); it++) {
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

bool Counter::mapping_string(const string &str) {
    vector<string> str_vector;
    words = {};
    string delimiters(" ;?“!_()‘—`\"\',:.-\n\t");
    
    string str_lower = boost::algorithm::to_lower_copy(str);
    boost::split(str_vector, str_lower, boost::is_any_of(delimiters), boost::token_compress_on);
    
    for (auto& s : str_vector) {
        ++words[s];
    }
    
    words.erase("");
    
    return true;
}

vector<pair<string, int>> Counter::get_vector_sorted_by_value() {
    auto vector_pairs = get_vector_sorted_by_key();
    
    std::sort(vector_pairs.begin(), vector_pairs.end(), [](auto &left, auto& right) {
        if (left.second < right.second) {
            return true;
        } else if (left.second == right.second) {
            if (left.first < right.first) {
                return true;
            }
        }
        return false;
    });
    
//    for (auto & v : vector_pairs) {
//        cout << v.first << " - " << v.second << endl;
//    }
    
    return vector_pairs;
}

vector<pair<string, int>> Counter::get_vector_sorted_by_key() {
    if (words.empty()) {
        cerr << "Error: map of words is empty, try func mapping_string() first" << endl;
        exit(-1);
    }
    
    vector<pair<string, int>> vector_pairs;
    
    for (auto& w : words) {
        vector_pairs.push_back(pair<string, int> (w.first, w.second));
    }
    return vector_pairs;
}

map<string, int> Counter::get_map() {
    return words;
}

void Counter::print_map_of_words() {
    if (words.empty()) {
        cerr << "Error: map of words is empty, try func mapping_string() first" << endl;
    }
    
    for (auto& m : words) {
        cout << m.first << " - " << m.second << endl;
    }
}
