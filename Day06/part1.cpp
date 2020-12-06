//6911
#include <iostream>
#include <range/v3/all.hpp>
#include <utils.hpp>

int main() {
    const auto input = AoC::get_input("input.txt", "\n\n");
    std::cout << ranges::accumulate(input, 0, [](auto sum, auto s){
        ranges::sort(s);
        auto last = ranges::unique(s);
        s.erase(last, s.end());
        s.erase(ranges::remove(s, '\n'), s.end());
        return sum + s.length();
    }) << std::endl;
    return 0;
}