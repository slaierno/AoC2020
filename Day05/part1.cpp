//822
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <map>
#include <execution>

namespace ranges = std::ranges;
auto split(std::string to_split, const std::vector<std::string>& delimiters) {
    std::vector<std::string> ret;
    for(size_t pos = 0; pos != std::string::npos;) {
        std::vector<size_t> findings(delimiters.size());
        ranges::transform(delimiters, std::begin(findings), [&to_split](auto d){ return to_split.find(d);});
        auto it = ranges::min_element(findings);
        auto delimiter = delimiters.at(std::distance(std::begin(findings), it));
        pos = *it;
        ret.push_back(to_split.substr(0,pos));
        if(pos != std::string::npos) to_split.erase(0, pos + delimiter.size());
    }
    return ret;
}

struct seat {
    unsigned row, col;
};
template<typename T>
struct range {
    T low, high;
    range() = delete;
    range(T _low, T _high) : low(_low), high(_high) {};
};

int main() {
    const auto input = []() -> std::vector<std::string> {
        if(std::ifstream input_file("input.txt"); input_file.is_open()) {
            std::stringstream buffer;
            buffer << input_file.rdbuf();
            return split(buffer.str(), {"\n"});
        } else return {};
    }();
    unsigned highest = 0;
    for(const auto& i : input) {
        range<seat> s {{0,0}, {127,7}};
        for(const auto c : i) {
            switch(c) {
            case 'L':
                s.high.col = (s.low.col + s.high.col)/2;
                break;
            case 'R':
                s.low.col = (s.low.col + s.high.col + 1)/2;
                break;
            case 'F':
                s.high.row = (s.low.row + s.high.row)/2;
                break;
            case 'B':
                s.low.row = (s.low.row + s.high.row + 1)/2;
                break;
            }
        }
        if(s.high.row != s.low.row || s.high.col != s.low.col) {
            std::cout << "WHOOOPS" << std::endl;
            return -1;
        }
        highest = std::max(highest, s.high.row*8 + s.high.col);
    };
    std::cout << highest << std::endl;
    return 0;
}