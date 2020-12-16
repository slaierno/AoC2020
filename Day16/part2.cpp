//737176602479
#include <iostream>
#include <string>
#include <vector>
#include <utils.hpp>
#include <map>
#include <algorithm>
#include <numeric>

using ticket_t = std::vector<long unsigned>;
using range_t = std::pair<long unsigned, long unsigned>;
using rule_t = std::tuple<std::string, range_t, range_t>;
using input_t = std::tuple<std::vector<rule_t>, ticket_t, std::vector<ticket_t>>;
using rule_map_t = std::map<size_t, rule_t>;
const auto in_rule = [](const auto v, const rule_t& r) { 
    const auto in_range = [](const auto v, const range_t& r) { 
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
    std::vector<std::map<size_t, rule_t>> rule_matrix(rules.size(), [&rules](){
        rule_map_t rmap;
        for(size_t i = 0; i < rules.size(); i++) rmap[i] = rules[i];
        return rmap;
    }());
    const auto valid_tickets = [&](){
        std::vector<ticket_t> valid_tickets;
        std::copy_if(tickets.begin(), tickets.end(), std::back_inserter(valid_tickets), [&](const ticket_t& t) {
            return std::all_of(t.begin(), t.end(), [&rules](const auto v) {
                return std::any_of(rules.begin(), rules.end(), [&](const auto& r){ return in_rule(v, r); });
            });
        });
        valid_tickets.push_back(my_ticket);
        return valid_tickets;
    }();
    const auto remove_idx = [&rule_matrix](const auto idx, const auto& self) -> void{
        for(auto& position : rule_matrix) {
            if (position.size() == 1) continue;
            if (auto found = position.find(idx); found != position.end()) {
                position.erase(found);
                if(position.size() == 1) self(position.begin()->first, self);
            }
        }
    };
    for(const auto& t : valid_tickets) {
        for(size_t i = 0; i < t.size(); i++) {
            const auto& v = t[i];
            auto& rules = rule_matrix[i];
            std::erase_if(rules, [&v](const auto& rule){ return !in_rule(v, rule.second); });
            if(rules.size() == 1) remove_idx(rules.begin()->first, remove_idx);
        }
    }
    std::cout << std::accumulate(my_ticket.begin(), my_ticket.end(), 1ULL, [&, i = 0](const auto a, const auto v) mutable {
        const auto& [name, _1, _2] = rules[rule_matrix[i++].begin()->first];
        return a * ((name.find("departure") != std::string::npos) ? v : 1);
    }) << std::endl;
    return 0;
}