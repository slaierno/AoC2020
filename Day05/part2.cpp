//705
#include <iostream>
#include <range/v3/all.hpp>
#include <utils.hpp>

namespace views = ranges::views;

struct seat {
    unsigned row, col;
    auto to_id() { return row*8 + col; }
};
template<typename T>
struct range {
    T low, high;
    range() = delete;
    range(T _low, T _high) : low(_low), high(_high) {};
};

int main() {
    const auto input = AoC::get_input("input.txt", '\n');
    const auto ticket_to_id = [&](auto ticket) {
        auto ticket_to_id_impl = [&](auto ticket, auto&& self) -> range<seat> {
            constexpr auto range_update = [](auto s, const char inst) {
                    switch(inst) {
                    case 'L': s.high.col = (s.low.col + s.high.col)     / 2; break;
                    case 'R': s.low .col = (s.low.col + s.high.col + 1) / 2; break;
                    case 'F': s.high.row = (s.low.row + s.high.row)     / 2; break;
                    case 'B': s.low .row = (s.low.row + s.high.row + 1) / 2; break;
                    }
                    return s;
            };
            return range_update(
                (ticket.length() == 1) ? 
                    range<seat>({0,0}, {127,7}) : 
                    self(ticket.substr(0, ticket.length() - 1), self), 
                ticket.back());
        };
        return ticket_to_id_impl(ticket, ticket_to_id_impl).high.to_id();
    };
    const std::vector<bool> seatmap = [&](){
        std::vector<bool> seatmap(8*128, false);
        ranges::for_each(input, [&](const auto& ticket){seatmap[ticket_to_id(ticket)] = true;});
        return seatmap;
    }();
    for(size_t i = 1; i < seatmap.size() - 1; i++) {
        if(!seatmap[i] && seatmap[i-1] && seatmap[i+1]) {
            std::cout << i << std::endl;
            break;
        }
    }
    return 0;
}