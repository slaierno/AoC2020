//2214
#include <iostream>
#include <string>
#include <vector>
#include <utils.hpp>
#include <algorithm>
#include <execution>

int main() {
    auto map_now = AoC::get_input("input.txt", '\n');
    int occupied_seats;
    AoC::profile([&](){
        const int rows = map_now.size(),
                cols = map_now.back().size();
        for(auto map_old = map_now;
            std::transform_reduce(std::execution::par_unseq, map_old.begin(), map_old.end(), 0, std::plus<>(), [&](const auto& l){
                const int i = &l - &map_old[0];
                return ranges::accumulate(l, 0, [&](auto a, const auto& s){
                    const int j = &s - &l[0];
                    const auto update_dir = [](const int dir, int& i, int& j){
                        if(dir & 0b00110001) i++;
                        if(dir & 0b11000010) i--;
                        if(dir & 0b01010100) j++;
                        if(dir & 0b10101000) j--;
                    };
                    if(s == '.') return a;
                    unsigned counter = 0;
                    for(int dir = 1; dir <= 1<<7; dir<<=1) {
                        for(int i_n = i, j_n = j; 
                            (0 <= i_n && i_n < cols) && (0 <= j_n && j_n < rows); 
                            update_dir(dir, i_n, j_n)) {
                            if((i_n != i || j_n != j) && map_old[i_n][j_n] != '.') {
                                counter += map_old[i_n][j_n] == '#';
                                break;
                            }
                        }
                    }
                    if((s == 'L' && counter == 0) || (s == '#' && counter >= 5)) {
                        map_now[i][j] = map_now[i][j] == '#' ? 'L' : '#';
                        return a + 1;
                    } else return a;
                });
            }); 
            map_old = map_now);
        occupied_seats = ranges::accumulate(map_now, 0, [](auto a, const auto& l) { return a + ranges::count(l, '#');});
    });
    
    std::cout << occupied_seats << std::endl;
    return 0;
}