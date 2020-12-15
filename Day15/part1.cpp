//273
#include <iostream>
#include <string>
#include <vector>
#include <utils.hpp>
#include <algorithm>

int main() {
    auto spoken = AoC::get_input("input.txt", ',', [](const std::string& s) { return std::stoi(s); });
    while(spoken.size() < 2020) {
        auto found = std::find(spoken.rbegin()+1, spoken.rend(), spoken.back());
        spoken.push_back((found == spoken.rend()) ? 0 : spoken.size() - (spoken.rend() - found));
    }
    std::cout << spoken.back() << std::endl;
    return 0;
}