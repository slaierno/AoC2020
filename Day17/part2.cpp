//1972
#include <iostream>
#include <string>
#include <vector>
#include <utils.hpp>
#include <map>
#include <set>
#include <ranges>

struct point_t {
    int x, y, z, w;
    auto operator<=>(const point_t&) const = default;
};

int main() {
    std::set<point_t> cubes;
    const auto input_lines = AoC::get_input("input.txt", {'\n'});
    for(int x = 0; x < (int)input_lines.size(); x++) {
        for(int y = 0; y < (int)input_lines[x].size(); y++) {
            if(input_lines[x][y] == '#') cubes.emplace(x,y,0,0);
        }
    }
    const auto neighbours = [](const point_t& center) {
        constexpr auto nbh = [](const auto x) {return std::views::iota(x-1) | std::views::take(3);};
        std::set<point_t> neighbours;
        for(int x : nbh(center.x)) for(int y : nbh(center.y))
        for(int z : nbh(center.z)) for(int w : nbh(center.w))
            if(auto nbp = point_t{x,y,z,w}; nbp != center) neighbours.insert(nbp);
        return neighbours;
    };
    for(int i = 0; i < 6; i++) {
        std::map<point_t, unsigned> neighbours_map;
        std::set<point_t> new_cubes;
        for(const auto& c : cubes) {
            for(const auto& n : neighbours(c)) {
                neighbours_map[n]++;
            }
        }
        for(const auto& c : cubes) {
            if(neighbours_map[c] == 2 || neighbours_map[c] == 3) new_cubes.insert(c);
            neighbours_map.erase(c);
        }
        for(const auto& [n, count] : neighbours_map) {
            if(count == 3) new_cubes.insert(n);
        }
        cubes.swap(new_cubes);
    }
    std::cout << cubes.size() << std::endl;
    return 0;
}