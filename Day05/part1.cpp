//822
#include <fstream>
#include <iostream>
#include <sstream>
#include <numeric>
#include <range/v3/all.hpp>

namespace views = ranges::views;

struct seat {
    unsigned row, col;
};
template<typename T>
struct range {
    T low, high;
    range() = delete;
    range(T _low, T _high) : low(_low), high(_high) {};
};

int main() {
    const auto input = []() {
        if(std::ifstream input_file("input.txt"); input_file.is_open()) {
            std::stringstream buffer;
            buffer << input_file.rdbuf();
            const auto s = buffer.str();
            return ranges::to<std::vector<std::string>>(
                  views::all(s)
                | views::split('\n')
                | views::transform(ranges::to<std::string>())
            );
        } else throw "Invalid input\n";
    }();
    const auto ticket_to_id = [](auto ticket) {
        range<seat> s {{0,0}, {127,7}};
        for(const auto c : ticket) {
            switch(c) {
            case 'L':
                s.high.col = (s.low.col + s.high.col)/2;
                break;
            case 'R':
                s.low.col = (s.low.col + s.high.col + 1)/2;
                break;
            case 'F':
                s.high.row = (s.low.row + s.high.row)/2;
                break;
            case 'B':
                s.low.row = (s.low.row + s.high.row + 1)/2;
                break;
            }
        }
        return s.high.row*8 + s.high.col;
    };
    std::cout << ranges::max(input | views::transform(ticket_to_id)) << std::endl;
    return 0;
}