//4011064
#include <iostream>
#include <string>
#include <algorithm>
#include <execution>
#include <utils.hpp>

int main() {
    const auto input = AoC::get_input("input.txt", '\n', [i = 0] (auto s) mutable {
        return std::pair<size_t, long long>{i++, std::stoll(s)};
    });
    const auto [_, weakness] = *std::find_if(
        std::next(std::begin(input), 25), std::end(input),
        [&input](const auto& i_pair){
            const auto [i, sum] = i_pair;
            for(size_t j = i - 25; j < i; j++) {
                for(size_t k = i - 25; k < i; k++) {
                    if (j == k) continue;
                    if (input[j].second + input[k].second == sum) return false;
                }
            }
            return true;
        }
    );

    AoC::profile([&](){
        for(size_t i = 0; i < input.size(); i++) {
            long long sum = input[i].second;
            for(size_t j = i+1; sum < weakness && j < input.size(); j++) {
                sum += input[j].second;
                if(sum == weakness) {
                    const auto& [min_el, max_el] = std::minmax_element(input.begin() + i, input.begin() + j, [](const auto a, const auto b){ return a.second < b.second; });
                    std::cout << min_el->second + max_el->second << std::endl;
                    break;
                }
            }
        }
    }, "Dummy sequenced version, recomputed sums - O(n^2)");
    
    AoC::profile([&](){
        std::any_of(
            std::execution::par_unseq,
            std::next(std::begin(input), 25), std::end(input),
            [&](const auto& i_pair){
                auto [i, sum] = i_pair;
                for(size_t j = i+1; sum < weakness && j < input.size(); j++) {
                    sum += input[j].second;
                    if(sum == weakness) {
                        const auto& [min_el, max_el] = std::minmax_element(input.begin() + i, input.begin() + j, [](const auto a, const auto b){ return a.second < b.second; });
                        std::cout << min_el->second + max_el->second << std::endl;
                        return true;
                    }
                }
                return false;
            }
        );
    }, "Dummy parallelized version - O(n^2)");

    AoC::profile([&](){
        long long sum = input[0].second;
        for(size_t i = 0, j = 0; i < input.size() && j < input.size();) {
            if (sum < weakness || j == i) {
                sum += input[++j].second;
            } else if(sum > weakness) {
                sum -= input[i++].second;
            } else {
                const auto& [min_el, max_el] = std::minmax_element(input.begin() + i, input.begin() + j, [](const auto a, const auto b){ return a.second < b.second; });
                std::cout << min_el->second + max_el->second << std::endl;
                break;
            }
        }
    }, "Better sequenced version, updated sums - O(n)");
    return 0;
}