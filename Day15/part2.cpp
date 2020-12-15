//47205
#include <iostream>
#include <string>
#include <vector>
#include <utils.hpp>

int main() {
    const auto input = AoC::get_input("input.txt", ',', [](const std::string& s) { return std::stoi(s); });
    std::map<int, size_t> last_insertion;
    size_t idx = 0;
    int last_say = input[0];
    const auto map_insert = [&last_insertion, &last_say, &idx](const auto val) {
        last_insertion[last_say] = idx++;
        last_say = val;
    };
    while(idx < input.size() - 1) map_insert(input[idx+1]);
    while(idx < 30000000 - 1) map_insert(last_insertion.find(last_say) != last_insertion.end() ? idx - last_insertion[last_say] : 0);
    std::cout << last_say << std::endl;
    return 0;
}