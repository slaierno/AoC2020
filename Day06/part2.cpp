//3473
#include <iostream>
#include <range/v3/all.hpp>
#include <utils.hpp>

namespace views = ranges::views;

int main() {
    const auto input = AoC::get_input("input.txt", "\n\n");
    std::cout << ranges::accumulate(input, 0, [](auto sum, const auto& s){
        const auto s_vec = AoC::split(s, {"\n"});
        return sum + ranges::count_if(s_vec[0], [&s_vec](const auto ch){
            return ranges::all_of(s_vec, [ch](const auto& s){ return s.find(ch) != std::string::npos; });
        });
    }) << std::endl;
    return 0;
}