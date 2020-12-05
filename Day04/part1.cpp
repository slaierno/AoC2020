//196
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <map>
#include <execution>
#include <range/v3/all.hpp>

namespace views = ranges::views;
auto split(std::string to_split, const std::vector<std::string>& delimiters) {
    std::vector<std::string> ret;
    for(size_t pos = 0; pos != std::string::npos;) {
        const auto it = ranges::min_element(delimiters, [&to_split](auto a, auto b){ return to_split.find(a) < to_split.find(b);});
        pos = to_split.find(*it);
        ret.push_back(to_split.substr(0,pos));
        if(pos != std::string::npos) to_split.erase(0, pos + it->size());
    }
    return ret;
}

int main() {
    const std::vector<std::string> entries {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", /*"cid"*/};
    const auto input = []() -> std::vector<std::string> {
        if(std::ifstream input_file("input.txt"); input_file.is_open()) {
            std::stringstream buffer;
            buffer << input_file.rdbuf();
            return split(buffer.str(), {"\n\n"});
        } else return {};
    }();
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