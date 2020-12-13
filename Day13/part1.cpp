//161
#include <iostream>
#include <string>
#include <vector>
#include <utils.hpp>
#include <algorithm>
#include <limits>

int main() {
    const auto input = AoC::get_input("input.txt", '\n');
    const int timestamp = std::stoi(input[0]);
    const auto departures = AoC::split(input[1], {",", "x"}, [](const auto s) {return std::stoi(s);});
    
    int min_time = std::numeric_limits<int>::max();
    int best_bus = 0;
    for(const auto dep_time : departures) {
        const auto next = dep_time * ((timestamp + dep_time - 1) / dep_time);
        min_time = std::min(next, min_time);
        if (next == min_time) best_bus = dep_time;
    }
    std::cout << (min_time - timestamp) * best_bus << std::endl;
    return 0;
}