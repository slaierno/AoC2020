//2214
#include <iostream>
#include <string>
#include <vector>
#include <utils.hpp>
#include <algorithm>
#include <numeric>

int main() {
    auto map_now = AoC::get_input("input.txt", '\n', [i = 0](const std::string& s) mutable { 
            std::vector<std::pair<std::pair<int, int>, char>> v;
            for(unsigned j = 0; j < s.length(); j++) {
                v.emplace_back(std::pair{i, j}, s[j]);
            }
            i++;
            return v;
        });
    const int rows = map_now.size(),
              cols = map_now.back().size();
    for(auto map_old = map_now;
        ranges::accumulate(map_old, 0, [&](auto a, const auto& l){
            return a + ranges::accumulate(l, 0, [&](auto a, const auto& seat){
                const auto& [idx, s] = seat;
                const auto  [i, j] = idx;
                if(s == '.') return a;
                const auto update_dir = [](const int dir, int& i, int& j){
                    if(dir & 0b00110001) i++;
                    if(dir & 0b11000010) i--;
                    if(dir & 0b01010100) j++;
                    if(dir & 0b10101000) j--;
                };
                unsigned counter = 0;
                for(int dir = 1; dir <= 1<<7; dir<<=1) {
                    for(int i_n = i, j_n = j; 
                        (0 <= i_n && i_n < cols) && (0 <= j_n && j_n < rows); 
                        update_dir(dir, i_n, j_n)) {
                        if((i_n != i || j_n != j) && map_old[i_n][j_n].second != '.') {
                            counter += map_old[i_n][j_n].second == '#';
                            break;
                        }
                    }
                }
                if((s == 'L' && counter == 0) || (s == '#' && counter >= 5)) {
                    map_now[i][j].second = map_now[i][j].second == '#' ? 'L' : '#';
                    return a + 1;
                } else return a;
            });
        }); 
        map_old = map_now);

    const auto free_seats = ranges::accumulate(map_now, 0, [](auto a, const auto& l) {
        return a + ranges::count_if(l, [](const auto& seat) {
            return seat.second == '#';
        });
    });

    std::cout << free_seats << std::endl;
    return 0;
}