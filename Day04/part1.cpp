//196
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <map>
#include <execution>

auto split(std::string to_split, const std::vector<std::string>& delimiters) {
    std::vector<std::string> ret;
    for(size_t pos = 0; pos != std::string::npos;) {
        std::vector<size_t> findings(delimiters.size());
        std::transform(
            std::execution::par_unseq,
            std::begin(delimiters), std::end(delimiters), 
            std::begin(findings), 
            [&to_split](auto d){ return to_split.find(d);});
        auto it = std::min_element(
            std::execution::par_unseq, 
            std::begin(findings), std::end(findings));
        pos = *it;
        auto delimiter = delimiters.at(std::distance(std::begin(findings), it));
        ret.push_back(to_split.substr(0,pos));
        if(pos != std::string::npos) to_split.erase(0, pos + delimiter.size());
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
            const auto passport_map = [&]() {
                const auto passport_split = split(passport, {"\n", " "});
                std::map<std::string, std::string> passport_map;
                std::ranges::transform(
                    std::begin(passport_split), std::end(passport_split), 
                    std::inserter(passport_map, std::end(passport_map)), 
                    [](auto s) {
                        auto s_split = split(s, {":"});
                        return std::pair(s_split[0], s_split[1]);
                    });
                return passport_map;
            }();
            return std::all_of(
                std::begin(entries), 
                std::end(entries), 
                [&passport_map](const auto& entry) {return passport_map.find(entry) != passport_map.end();});
    });
    std::cout << valid_passport_cnt << std::endl;
    return 0;
}