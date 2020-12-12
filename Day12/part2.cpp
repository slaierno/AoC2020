//20873
#include <iostream>
#include <string>
#include <vector>
#include <utils.hpp>

constexpr auto mod = [](const int a, const int b) { return (a % b + b) % b; };

struct Point {
    int x, y;
};

int main() {
    const auto input = AoC::get_input("input.txt", '\n', [](const std::string& s) { 
        return std::pair{s[0], std::stoi(s.substr(1))};
    });
    Point waypoint{10,1};
    Point ship{0,0};
    const auto rotate_wp = [&waypoint](const char dir, int deg) {
        if(dir == 'R') deg = -deg;
        if(deg < 0)    deg += 360;
        int cos = 0, sin = 0;
        switch(deg) {
            case   0: cos =  1; break;
            case  90: sin =  1; break;
            case 180: cos = -1; break;
            case 270: sin = -1; break;
        }
        waypoint = Point{
            waypoint.x * cos - waypoint.y * sin, 
            waypoint.x * sin + waypoint.y * cos
        };
    };
    const auto move_wp = [&waypoint](const char dir, int v) {
        switch(dir) {
        case 'N': waypoint.y+=v; break;
        case 'E': waypoint.x+=v; break;
        case 'S': waypoint.y-=v; break;
        case 'W': waypoint.x-=v; break;
        default: throw "Invalid input!\n";
        }
    };
    const auto move_ship = [&waypoint, &ship](const int v) {
        ship.x += v * waypoint.x;
        ship.y += v * waypoint.y;
    };
    for(const auto& [i, v] : input) {
        switch(i) {
        case 'L': case 'R':
            rotate_wp(i, v);
            break;
        case 'N': case 'E': case 'S': case 'W':
            move_wp(i, v);
            break;
        case 'F':
            move_ship(v);
            break;
        default: throw "Invalid input!\n";
        }
    }
        
    std::cout << std::abs(ship.x) + std::abs(ship.y) << std::endl;
    return 0;
}