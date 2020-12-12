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

struct Ship {
    int x, y;
    direction_t d;

    void move(direction_t dir, int v) {
        switch(dir) {
        case NORTH: y+=v; break;
        case EAST : x+=v; break;
        case SOUTH: y-=v; break;
        case WEST : x-=v; break;
        default: throw "Invalid input!\n";
        }
    }
    void move(char dir, int v) { return move(direction_map.at(dir), v); }
    void move(int v) { return move(d, v); }

};

int main() {
    const auto input = AoC::get_input("input.txt", '\n', [](const std::string& s) { 
        return std::pair{s[0], std::stoi(s.substr(1))};
    });
    Ship ship{0, 0, EAST};
    for(const auto& [i, v] : input) {
        switch(i) {
        case 'L': case 'R':
            ship.d = static_cast<direction_t>(mod(ship.d + (i == 'R' ? v/90 : -v/90), 4));
            break;
        case 'F':
            ship.move(v);
            break;
        case 'N': case 'E': case 'S': case 'W':
            ship.move(i, v);
            break;
        default: throw "Invalid input!\n";
        }
    }
        
    std::cout << std::abs(ship.x) + std::abs(ship.y) << std::endl;
    return 0;
}