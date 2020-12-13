//213890632230818
#include <iostream>
#include <string>
#include <vector>
#include <utils.hpp>
#include <cstdint>

uint64_t search_sync_time(const uint64_t bus_1, const uint64_t bus_2, const uint64_t bus_off, const uint64_t t_fac, const uint64_t t_off) {
    for(uint64_t t = 0; t < bus_1 * bus_2; t++)
        if(auto time = t_fac * t + t_off; (time + bus_off) % bus_2 == 0) return time;
    throw "No solution found\n";
}

int main() {
    const auto input = AoC::get_input("input.txt", '\n');
    const auto departures = AoC::split(input[1], ",", [](const auto s) {if (s[0] == 'x') return 0; else return std::stoi(s);});

    const auto buses = [&departures]() {
        std::vector<std::pair<uint64_t, uint64_t>> buses;
        for(size_t i = 0; i < departures.size(); i++)
            if(departures[i]) buses.emplace_back(departures[i], i);
        return buses;
    }();
    uint64_t t_fac = 1, t_off = 0;
    for(const auto& [bus_2, bus_2_off] : buses) {
        t_off = search_sync_time(buses.front().first, bus_2, bus_2_off, t_fac, t_off);
        t_fac *= bus_2;
    }

    std::cout << t_off << std::endl;
    return 0;
}