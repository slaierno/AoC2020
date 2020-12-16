//27911
#include <iostream>
#include <string>
#include <vector>
#include <utils.hpp>
#include <algorithm>
#include <numeric>

using ticket_t = std::vector<long unsigned>;
using range_t = std::pair<long unsigned, long unsigned>;
using rule_t = std::tuple<std::string, range_t, range_t>;
using input_t = std::tuple<std::vector<rule_t>, ticket_t, std::vector<ticket_t>>;
constexpr auto in_rule = [](const auto v, const rule_t& r) { 
    constexpr auto in_range = [](const auto v, const range_t& r) { 
        const auto& [rm, rM] = r;
        return rm <= v&&v <=rM;
    };
    const auto& [_, r1, r2] = r;
    return in_range(v,r1) || in_range(v,r2);
};

int main() {
    const auto [rules, my_ticket, tickets] = [](){
        const auto input = AoC::get_input("input.txt", {"\n\n"});
        const auto& rules_string = input[0];
        const auto& my_ticket_string = input[1];
        const auto& tickets_string = input[2];

        const std::vector<rule_t> rules = AoC::split(rules_string, '\n', [](const auto& s) {
            const auto rules_str = AoC::split(s, ": ");
            const auto ranges_str = AoC::split(rules_str[1], ' ');
            const auto make_range = [](const auto& str) {
                const auto range_vec = AoC::split(str, '-', [](const auto& s) {return std::stoul(s);});
                return range_t {range_vec[0], range_vec[1]};
            };
            return rule_t{rules_str[0], make_range(ranges_str[0]), make_range(ranges_str[2])};
        });
        const auto make_ticket = [](const auto& s) {
            return AoC::split(s, ',', [](const auto& s) {return std::stoul(s);});
        };
        return input_t{
            rules,
            make_ticket(AoC::split(my_ticket_string, '\n')[1]),
            AoC::split(AoC::split(tickets_string, ":\n")[1], '\n', make_ticket),
        };
    }();
    const auto error_rate = [&rules](const ticket_t& t) {
        return std::accumulate(t.begin(), t.end(), 0, [&](const auto a, const auto v) {
            return a + (std::any_of(rules.begin(), rules.end(), [&](const auto& r) { return in_rule(v, r); }) ? 0 : v);
        });
    };
    std::cout << std::accumulate(tickets.begin(), tickets.end(), 0, [&error_rate](const auto a, const auto& t) {
        return a + error_rate(t);}
    ) << std::endl;
    return 0;
}