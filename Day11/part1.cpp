//2468
#include <iostream>
#include <string>
#include <vector>
#include <utils.hpp>

int main() {
    auto map_now = AoC::get_input("input.txt", '\n');
    const int rows = map_now.size(),
              cols = map_now.back().size();
    auto map_old = map_now;
    for(auto map_old = map_now;
        ranges::accumulate(map_old, 0, [&](auto a, const auto& l) mutable {
            const int i = &l - &map_old[0];
            return a + ranges::accumulate(l, 0, [&](auto a, const auto& s) mutable {
                const int j = &s - &l[0];
                if(s == '.') return a;
                unsigned counter = 0;
                for(int i_n = std::max(i-1, 0); i_n <= std::min(i+1, cols-1); i_n++) {
                    for(int j_n = std::max(j-1, 0); j_n <= std::min(j+1, rows-1); j_n++) {
                        counter += (i_n != i || j_n != j) && (map_old[i_n][j_n] == '#');
                    }
                }
                if((s == 'L' && counter == 0) || (s == '#' && counter >= 4)) {
                    map_now[i][j] = map_now[i][j] == '#' ? 'L' : '#';
                    return a + 1;
                } else return a;
            });
        });
        map_old = map_now);
        
    std::cout << 
        ranges::accumulate(map_now, 0, [](auto a, const auto& l) { return a + ranges::count(l, '#');}) 
    << std::endl;
    return 0;
}