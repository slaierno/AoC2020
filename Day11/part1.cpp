//2468
#include <iostream>
#include <string>
#include <vector>
#include <utils.hpp>
#include <algorithm>
#include <numeric>

int main() {
    auto map_now = AoC::get_input("input.txt", '\n', [i = 0](const std::string& s) mutable { 
            std::vector<std::pair<std::pair<size_t, size_t>, char>> v;
            for(size_t j = 0; j < s.length(); j++) {
                v.emplace_back(std::pair{i, j}, s[j]);
            }
            i++;
            return v;
        });
    const size_t rows = map_now.size(), cols = map_now.back().size();
    auto map_old = map_now;
    while(ranges::accumulate(
        map_old, 0,
        [&](auto a, const auto& l){
            return a + std::accumulate(l.begin(), l.end(), 0, [&](auto a, const auto& seat){
                const auto& [idx, s] = seat;
                if(s == '.') return a;
                const auto [i, j] = idx;
                const auto i_min = i > 0 ? i-1 : i;
                const auto j_min = j > 0 ? j-1 : j;
                const auto i_max = i < cols-1 ? i+1 : i;
                const auto j_max = j < rows-1 ? j+1 : j;
                unsigned counter = 0;
                for(size_t i_n = i_min; i_n <= i_max; i_n++) {
                    for(size_t j_n = j_min; j_n <= j_max; j_n++) {
                        counter += (i_n != i || j_n != j) && (map_old[i_n][j_n].second == '#');
                    }
                }
                if((s == 'L' && counter == 0) || (s == '#' && counter >= 4)) {
                    map_now[i][j].second = map_now[i][j].second == '#' ? 'L' : '#';
                    return a + 1;
                } else return a;
            });
        })) {
        map_old = map_now;
    }
    const auto free_seats = ranges::accumulate(map_now, 0, [](auto a, const auto& l) {
        return a + ranges::count_if(l, [](const auto& seat) {
            return seat.second == '#';
        });
    });

    std::cout << free_seats << std::endl;
    return 0;
}