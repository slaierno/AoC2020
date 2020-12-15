//47205
#include <iostream>
#include <string>
#include <vector>
#include <utils.hpp>

int main() {
    const auto input = AoC::get_input("input.txt", ',', [](const std::string& s) { return std::stoul(s); });
    std::vector<unsigned> last_insertion(30000000);
    unsigned idx = 1;
    unsigned last_say = input[0];
    const auto map_insert = [&last_insertion, &last_say, &idx](const unsigned val) {
        last_insertion[last_say] = idx++;
        last_say = val;
    };
    while(idx < input.size()) map_insert(input[idx]);
    while(idx < 30000000) map_insert(last_insertion[last_say] ? idx - last_insertion[last_say] : 0);
    std::cout << last_say << std::endl;
    return 0;
}