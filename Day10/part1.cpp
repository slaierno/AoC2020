//3034
#include <iostream>
#include <string>
#include <utils.hpp>
#include <algorithm>
#include <numeric>

int main() {
    auto input = AoC::get_input("input.txt", '\n', [](auto s) { return std::stoi(s); });
    ranges::sort(input);
    input.push_back(input.back() + 3);
    std::adjacent_difference(input.begin(), input.end(), input.begin());
    std::cout << ranges::count(input, 1) * ranges::count(input, 3) << std::endl;
    return 0;
}