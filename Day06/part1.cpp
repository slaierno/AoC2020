//6911
#include <fstream>
#include <iostream>
#include <sstream>
#include <numeric>
#include <range/v3/all.hpp>

namespace views = ranges::views;
auto split(std::string to_split, const std::vector<std::string>& delimiters) {
    std::vector<std::string> ret;
    for(size_t pos = 0; pos != std::string::npos;) {
        const auto it = ranges::min_element(delimiters, [&to_split](auto a, auto b){ return to_split.find(a) < to_split.find(b);});
        pos = to_split.find(*it);
        ret.push_back(to_split.substr(0,pos));
        if(pos != std::string::npos) to_split.erase(0, pos + it->size());
    }
    return ret;
}

int main() {
    const auto input = []() -> std::vector<std::string> {
        if(std::ifstream input_file("input.txt"); input_file.is_open()) {
            std::stringstream buffer;
            buffer << input_file.rdbuf();
            return split(buffer.str(), {"\n\n"});
        } else return {};
    }();
    std::cout << ranges::accumulate(input, 0, [](auto sum, auto s){
        ranges::sort(s);
        auto last = ranges::unique(s);
        s.erase(last, s.end());
        s.erase(ranges::remove(s, '\n'), s.end()) ;
        return sum + s.length();
    }) << std::endl;
    return 0;
}