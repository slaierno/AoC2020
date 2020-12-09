//23278925
#include <iostream>
#include <string>
#include <utils.hpp>

int main() {
    const auto input = AoC::get_input("input.txt", '\n', [](auto s) {
        return std::stoll(s);
    });
    for(size_t i = 25; i < input.size(); i++) {
        const auto sum = input[i];
        for(size_t j = i - 25; j < i; j++) {
            for(size_t k = i - 25; k < i; k++) {
                if (j == k) continue;
                if (input[j] + input[k] == sum) goto next;
            }
        }
        std::cout << sum << std::endl;
        break;
        next:;
    }
    return 0;
}