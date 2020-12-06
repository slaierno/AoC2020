//196
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <execution>
#include <range/v3/all.hpp>
#include <utils.hpp>

namespace views = ranges::views;

int main() {
    const std::vector<std::string> entries {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", /*"cid"*/};
    const auto input = AoC::get_input("input.txt", "\n\n");
    const auto valid_passport_cnt = std::transform_reduce(
        std::execution::par_unseq,
        std::begin(input), std::end(input), 
        0, std::plus<>(),
        [&entries](const auto& passport) {
            const auto passport_map = 
                ranges::to<std::map<std::string, std::string>>(
                    views::all(passport)
                  | views::replace('\n', ' ')
                  | views::split(' ')
                  | views::transform(ranges::to<std::string>())
                  | views::transform([](auto s) {
                        const auto s_split = ranges::to<std::vector<std::string>>(
                          s 
                        | views::split(':')
                        | views::transform(ranges::to<std::string>())); 
                        return std::pair(s_split[0], s_split[1]);
                    })
                );
            return ranges::all_of(
                entries,
                [&passport_map](const auto& entry) {return passport_map.find(entry) != passport_map.end();});
    });
    std::cout << valid_passport_cnt << std::endl;
    return 0;
}