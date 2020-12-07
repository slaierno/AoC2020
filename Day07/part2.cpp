//39645
#include <iostream>
#include <string>
#include <range/v3/all.hpp>
#include <utils.hpp>
#include <map>
#include <queue>
#include <execution>
#include <algorithm>

namespace views = ranges::views;
using color_t = std::string;
using color_map = std::map<color_t, unsigned>;
using color_map_t = std::map<color_t, unsigned>;

int main() {
    const auto input = AoC::get_input("input.txt", '\n');
    const auto color_map_map = 
        ranges::to<std::map<color_t, color_map_t>>(views::transform(input, [](const auto& i) {
                const std::string contains_str = " bags contain ";
                const auto contains_pos = i.find(contains_str);
                const auto split_str = AoC::split(i.substr(contains_pos + contains_str.length()), {", ", "."});
                return std::pair {
                    i.substr(0, contains_pos), 
                    (split_str.front() == "no other bags") ? 
                        color_map_t{} : 
                        ranges::to<color_map_t>(views::transform(split_str, [](auto bag_info) {
                                const auto count = std::stoi(bag_info.substr(0, bag_info.find_first_not_of("1234567890")));
                                const auto color_pos = bag_info.find_first_of("abcdefghijklmnopqrstuvwxyz");
                                const auto bags_pos = bag_info.find("bag");
                                const auto color_str = bag_info.substr(color_pos, bags_pos - color_pos - 1 );
                                return std::pair { color_str, count };
                            })
                        )
                    };
            })
        );
    const color_t required_color = "shiny gold";
    const auto color_map = color_map_map.at(required_color);
    std::cout << std::transform_reduce(
        std::execution::par_unseq,
        color_map.begin(), color_map.end(),
        0, std::plus<>(),
        [&color_map_map](const auto& bag_info) {
            //BFS
            auto [bag_color, found_cnt] = bag_info;
            std::queue<std::pair<color_t, unsigned>> cmap_queue;
            ranges::for_each(color_map_map.at(bag_color), [&](const auto& p) { cmap_queue.emplace(p.first, found_cnt * p.second); });
            while (!cmap_queue.empty())
            {
                const auto& [color, cnt] = cmap_queue.front();
                found_cnt += cnt;
                ranges::for_each(color_map_map.at(color), [&](const auto& p) { cmap_queue.emplace(p.first, cnt * p.second); });
                cmap_queue.pop();
            }
            return found_cnt;
    }) << std::endl;
    return 0;
}