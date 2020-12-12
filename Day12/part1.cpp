//1687
#include <iostream>
#include <string>
#include <vector>
#include <utils.hpp>

constexpr auto mod = [](const int a, const int b) { return (a % b + b) % b; };

enum direction_t {
    NORTH = 0,
    EAST  = 1,
    SOUTH = 2,
    WEST  = 3
};
const std::map<char, direction_t> direction_map = {
    {'N', NORTH}, 
    {'E', EAST },  
    {'S', SOUTH}, 
    {'W', WEST },
};

struct Point {
    int x, y;
};
int main() {
    const auto input = AoC::get_input("input.txt", '\n', [](const std::string& s) { 
        return std::pair{s[0], std::stoi(s.substr(1))};
    });
    auto direction = EAST;
    Point ship{0,0};
    const auto move = [&ship](const direction_t dir, const int v) {
        switch(dir) {
        case NORTH: ship.y+=v; break;
        case EAST : ship.x+=v; break;
        case SOUTH: ship.y-=v; break;
        case WEST : ship.x-=v; break;
        default: throw "Invalid input!\n";
        }
    };
    for(const auto& [i, v] : input) {
        switch(i) {
        case 'L':
        case 'R':
            direction = static_cast<direction_t>(mod(direction + (i == 'R' ? v/90 : -v/90), 4));
            break;
        case 'F':
            move(direction, v);
            break;
        case 'N': case 'E': case 'S': case 'W':
            move(direction_map.at(i), v);
            break;
        default: throw "Invalid input!\n";
        }
    }
        
    std::cout << std::abs(ship.x) + std::abs(ship.y) << std::endl;
    return 0;
}