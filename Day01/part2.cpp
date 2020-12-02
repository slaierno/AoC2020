//100655544
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <optional>

std::optional<std::pair<auto, auto>> find_sum(auto first, auto last, const unsigned sum) {
    while(first != last) {
        if (*first + *last < sum) first++;
        else if (*first + *last > sum) last--;
        else return std::pair(first, last);
    }
    return {};
}

int main() {
    std::vector<unsigned> input;
    input.reserve(200);
    if(std::ifstream input_file("input.txt"); input_file.is_open()) {
        for(std::string num_str; std::getline(input_file, num_str, '\n');) {
            input.push_back(std::stoull(num_str));
        }
    }
    std::sort(std::begin(input), std::end(input));
    for(auto it = std::begin(input); it < std::end(input); it++) {
        if(const auto find = find_sum(std::next(it), std::prev(std::end(input)), 2020 - *it); find.has_value()) {
            const auto [a, b] = find.value();
            std::cout << *a * *b * *it << std::endl;
            return 0;
        }
    }
    std::cout << "Result not found!" << std::endl;
    return -1;
}   