//456
#include <vector>
#include <fstream>
#include <iostream>
#include <regex>
#include <algorithm>
 
int main() {
    std::vector<std::string> input;
    if(std::ifstream input_file("input.txt"); input_file.is_open()) {
        for(std::string password; std::getline(input_file, password, '\n');) {
            input.push_back(password);
        }
    }
    const std::regex pieces_regex("(\\d+)-(\\d+) (\\w): (\\w+)");
    const unsigned valid_cnt = std::ranges::count_if(input, [pieces_regex](auto password) {
        std::smatch match;
        std::regex_match(password, match, pieces_regex);
        const auto&& [min, max, rep_ch, psw] = std::tuple{std::stoul(match[1]), std::stoul(match[2]), match[3].str()[0], match[4].str()};
        const unsigned rep_cnt = std::ranges::count(psw, rep_ch);
        return (rep_cnt >= min) && (rep_cnt <= max);
    });
    std::cout << valid_cnt << std::endl;
    return 0;
}