//20873
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

struct Waypoint {
    int x, y;

    void move(const direction_t dir, const int v) {
        switch(dir) {
        case NORTH: y+=v; break;
        case EAST : x+=v; break;
        case SOUTH: y-=v; break;
        case WEST : x-=v; break;
        default: throw "Invalid input!\n";
        }
    }
    void move(const char dir, const int v) { return move(direction_map.at(dir), v); }
    
    void rotate(const char dir, const int deg) {
        int cos = 0, sin = 0;
        switch((dir == 'L') ? deg : 360 - deg) {
            case   0: cos =  1; break;
            case  90: sin =  1; break;
            case 180: cos = -1; break;
            case 270: sin = -1; break;
        }
        const auto _x = x * cos - y * sin;
        const auto _y = x * sin + y * cos;
        x = _x, y = _y;
    }
};

struct Ship {
    int x, y;
    Waypoint wp {10,1};
    void move(const int v) {
        x += v * wp.x;
        y += v * wp.y;
    }
};

int main() {
    const auto input = AoC::get_input("input.txt", '\n', [](const std::string& s) { 
        return std::pair{s[0], std::stoi(s.substr(1))};
    });
    Ship ship{0,0};
    Waypoint& waypoint = ship.wp;
    for(const auto& [i, v] : input) {
        switch(i) {
        case 'L': case 'R':
            waypoint.rotate(i, v);
            break;
        case 'N': case 'E': case 'S': case 'W':
            waypoint.move(i, v);
            break;
        case 'F':
            ship.move(v);
            break;
        default: throw "Invalid input!\n";
        }
    }
        
    std::cout << std::abs(ship.x) + std::abs(ship.y) << std::endl;
    return 0;
}