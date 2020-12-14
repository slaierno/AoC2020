//4795970362286
#include <iostream>
#include <string>
#include <vector>
#include <utils.hpp>
#include <algorithm>
#include <variant>
#include <numeric>

enum bit_t {
    ZERO,
    ONE,
    FLOATING,
};
using address_t = size_t;
using mask_t = std::array<bit_t, 36>;
using memset_t = std::pair<address_t, uint64_t>;
using inst_t = std::variant<mask_t, memset_t>;

int main() {
    const auto program = AoC::get_input("input.txt", '\n', [](const std::string& s) {
        if(s.find("mask") != std::string::npos) {
            const auto mask_str = s.substr(s.find('=')+2);
            mask_t mask;
            for(size_t i = 0; i < mask_str.length(); i++) {
                switch(mask_str[i]) {
                    case '0': mask[35 - i] = ZERO    ; break;
                    case '1': mask[35 - i] = ONE     ; break;
                    case 'X': mask[35 - i] = FLOATING; break;
                    default: throw "Invalid mask\n";
                }
            }
            return inst_t { std::in_place_type<mask_t>, mask };
        } else {
            return inst_t { std::in_place_type<memset_t>,
                std::stoull(s.substr(s.find('[') + 1, s.find(']'))),
                std::stoull(s.substr(s.find('=') + 2))
            };
        }
    });
    std::map<address_t, uint64_t> mem;
    mask_t mask;
    for(const auto& inst : program) {
        switch(inst.index()) {
        case 0: mask = std::get<mask_t>(inst); break;
        case 1: {
            const auto& [address_base, value] = std::get<memset_t>(inst);
            std::vector<address_t> addresses = {address_base};
            for(size_t i = 0; i < mask.size(); i++) {
                switch(mask[i]) {
                case ZERO: break;
                case ONE: for(auto& address : addresses) address |= 1ULL << i; break;
                case FLOATING: {
                    std::vector<address_t> new_addresses(addresses);
                    for(auto& address : addresses) new_addresses.emplace_back(address ^ (1ULL << i));
                    addresses.insert(addresses.end(), new_addresses.begin(), new_addresses.end());
                } break;
                default: throw "Invalid mask\n";
                }
            }
            for(const auto address : addresses) mem[address] = value;
        } break;
        default: throw "Invalid alternative?!\n";
        }
    }
    std::cout << ranges::accumulate(mem, 0ULL, [](auto a, const auto& pair) {return a + pair.second;}) << std::endl;
    return 0;
}