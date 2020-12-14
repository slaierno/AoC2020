//5055782549997
#include <iostream>
#include <string>
#include <vector>
#include <utils.hpp>
#include <algorithm>
#include <variant>
#include <numeric>

using bit_t = bool;
using mask_t = std::vector<std::pair<size_t, bit_t>>;
using memset_t = std::pair<size_t, uint64_t>;
using inst_t = std::variant<mask_t, memset_t>;

int main() {
    const auto program = AoC::get_input("input.txt", '\n', [](const std::string& s) {
        if(s.find("mask") != std::string::npos) {
            auto mask_str = s.substr(s.find('=')+2);
            mask_t mask;
            for(size_t i = 0; i < mask_str.length(); i++) 
                if(mask_str[i] != 'X') mask.emplace_back(35 - i, mask_str[i] == '1');
            return inst_t { std::in_place_type<mask_t>, mask };
        } else {
            return inst_t {
                std::in_place_type<memset_t>,
                std::stoull(s.substr(s.find('[') + 1, s.find(']'))),
                std::stoull(s.substr(s.find('=') + 2))
            };
        }
    });
    std::map<size_t, uint64_t> mem;
    mask_t mask;
    for(const auto& inst : program) {
        switch(inst.index()) {
        case 0: mask = std::get<mask_t>(inst); break;
        case 1: {
            const auto& [address, value] = std::get<memset_t>(inst);
            mem[address] = value;
            for(const auto& [pos, bit] : mask)
                mem[address] ^= (-(uint64_t)bit ^ mem[address]) & (1ULL << pos);
        } break;
        default: throw "Invalid alternative?!\n";
        }
    }
    std::cout << std::accumulate(mem.begin(), mem.end(), 0ULL, [](const auto a, const auto& pair) {return a + pair.second;}) << std::endl;
    return 0;
}