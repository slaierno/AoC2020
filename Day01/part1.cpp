//1019571
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
    if(std::ifstream input_file("input.txt"); input_file.is_open()) {
        /* O(n) */
        for(std::string num_str; std::getline(input_file, num_str, '\n');) {
            input.push_back(std::stoull(num_str));
        }
    }
    /* O(n*log(n)) */
    std::sort(std::begin(input), std::end(input));
    /* O(n) */
    if(const auto find = find_sum(std::begin(input), std::prev(std::end(input)), 2020); find.has_value()) {
        const auto [a, b] = find.value();
        std::cout << *a * *b << std::endl;
        return 0;
    }
    return -1;
}