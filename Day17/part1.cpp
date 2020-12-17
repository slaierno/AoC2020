//295
#include <iostream>
#include <string>
#include <vector>
#include <utils.hpp>
#include <map>
#include <set>
#include <ranges>

struct point_t {
    int x, y, z;
    auto operator<=>(const point_t&) const = default;
    constexpr auto neighbours() const {
        constexpr auto nbh = [](const auto x) {return std::views::iota(x-1) | std::views::take(3);};
        std::array<point_t, 26> neighbours;
        size_t i = 0;
        for(const int x : nbh(x)) for(const int y : nbh(y))
        for(const int z : nbh(z))
            if(const point_t nbp = {x,y,z}; nbp != *this) neighbours[i++] = nbp;
        return neighbours;
    }
};

int main() {
    std::set<point_t> cubes;
    const auto input_lines = AoC::get_input("input.txt", {'\n'});
    for(int x = 0; x < (int)input_lines.size(); x++) {
        for(int y = 0; y < (int)input_lines[x].size(); y++) {
            if(input_lines[x][y] == '#') cubes.emplace(x,y,0);
        }
    }
    for(int i = 0; i < 6; i++) {
        std::map<point_t, unsigned> neighbours_map;
        for(const auto& c : std::as_const(cubes)) {
            for(const auto& n : c.neighbours()) {
                neighbours_map[n]++;
            }
        }
        std::set<point_t> new_cubes;
        for(const auto& c : std::as_const(cubes)) {
            if(neighbours_map[c] == 2 || neighbours_map[c] == 3) new_cubes.insert(c);
            neighbours_map.erase(c);
        }
        for(const auto& [n, count] : std::as_const(neighbours_map)) {
            if(count == 3) new_cubes.insert(n);
        }
        cubes.swap(new_cubes);
    }
    std::cout << cubes.size() << std::endl;
    return 0;
}