//1810
#include <iostream>
#include <string>
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

const auto str_to_inst = [](const auto& s) ->inst_t {
    const auto inst = AoC::split(s, ' ');
    return {op_map.at(inst[0]), std::stoi(inst[1])};
};

using inst_t = std::pair<op_enum, int>;

int main() {
    const auto input = AoC::get_input("input.txt", '\n');
    std::vector<bool> executed(input.size(), false);
    int acc = 0;
    for(size_t address = 0; address < input.size();) {
        if(!executed[address]) executed[address] = true;
        else {
            std::cout << acc << std::endl;
            break;
        }
        const auto [op, arg] = str_to_inst(input[address]);
        switch(op){
            case ACC: acc+= arg; address++;    break;
            case NOP:            address++;    break;
            case JMP:            address+=arg; break;
            default: throw "Invalid opcode\n";
        }
    }
    return 0;
}