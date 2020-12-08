//969
#include <iostream>
#include <string>
#include <execution>
#include <utils.hpp>

enum op_enum {
    ACC,
    JMP,
    NOP
};
const std::map<std::string, op_enum> op_map {
    {"acc", ACC},
    {"jmp", JMP},
    {"nop", NOP},
};

using inst_t = std::pair<op_enum, int>;
const auto str_to_inst = [](const std::string& s) -> inst_t {
    const auto inst = AoC::split(s, ' ');
    return {op_map.at(inst[0]), std::stoi(inst[1])};
};

int main() {
    const auto input = AoC::get_input("input.txt", '\n', [i = 0] (auto line) mutable {
        const auto [op, arg] = str_to_inst(line);
        return std::tuple<size_t, op_enum, int>{i++, op, arg};
    });
    std::any_of(
        std::execution::par_unseq, 
        input.begin(), input.end(), 
        [&input](const auto& input_tuple){
            const auto [address_sub, op, arg] = input_tuple;
            
            if(op != NOP && (op != JMP || (op == JMP && arg == 0))) return false;;
            
            std::vector<bool> executed(input.size(), false);
            int acc = 0;
            for(size_t address = 0; address < input.size();) {
                auto [_, op, arg] = input[address];
                if(executed[address]) return false;
                executed[address] = true;
                if(address == address_sub) op = (op == JMP) ? NOP : JMP;
                switch(op){
                    case ACC: acc+= arg; address++;    break;
                    case NOP:            address++;    break;
                    case JMP:            address+=arg; break;
                    default: throw "Invalid opcode\n";
                }
            }
            std::cout << acc << std::endl;
            return true;
        }
    );
    return 0;
}