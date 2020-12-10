//259172170858496
#include <iostream>
#include <vector>
#include <utils.hpp>

int main() {
    const auto input = [](){
        auto input = AoC::get_input("input.txt", '\n', [](auto s) { return std::stoi(s); });
        input.push_back(0);
        ranges::sort(input);
        input.push_back(input.back() + 3);
        return input;
    }();
    std::vector<unsigned long> in_paths(input.size(), 0);
    in_paths[0] = 1;
    
    for(size_t i = 0; i < input.size(); i++)
        for(size_t j = i+1; j < input.size() && input[j] - input[i] <= 3 ; j++)
            in_paths[j]+=in_paths[i];

    std::cout << in_paths.back() << std::endl;
    return 0;
}