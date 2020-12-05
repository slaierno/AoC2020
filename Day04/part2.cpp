//114
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
#include <functional>
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

template<typename T>
constexpr bool in_bound(const T val, const T min, const T max) {
    return val >= min && val <= max;
}

int main() {
    const std::map<std::string, std::function<bool(std::string)>> entries {
        {"byr", [](std::string s) { return in_bound(std::stoi(s), 1920, 2002); }},
        {"iyr", [](std::string s) { return in_bound(std::stoi(s), 2010, 2020); }},
        {"eyr", [](std::string s) { return in_bound(std::stoi(s), 2020, 2030); }},
        {"hgt", [](std::string s) {
            if(const auto mu_pos = s.find_first_not_of("0123456789"); mu_pos != std::string::npos) {
                if(auto match = s.substr(mu_pos); "cm" == match) {
                    return in_bound(std::stoi(s.substr(0, mu_pos)), 150, 193);
                } else if ("in" == match) {
                    return in_bound(std::stoi(s.substr(0, mu_pos)), 59, 76);
                }
            }
            return false;
        }},
        {"hcl", [](std::string s) {
            return (s[0] == '#') && (std::all_of(std::next(std::begin(s)), std::end(s), ::isxdigit)); //NOTE: ::isxdigit accepts upper case hex value too, be carefule
        }},
        {"ecl", [](std::string s) {
            const std::set<std::string> colors {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
            return colors.find(s) != colors.end();
        }},
        {"pid", [](std::string s) { return (s.length() == 9) && (std::all_of(std::begin(s), std::end(s), ::isdigit)); }},
        /*"cid"*/
    };
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
                [&passport_map](const auto& entry) {
                    if(auto found = passport_map.find(entry.first); found != passport_map.end()) {
                        return entry.second(found->second);
                    } else return false;
                });
        });
    std::cout << valid_passport_cnt << std::endl;
    return 0;
}