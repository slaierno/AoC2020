//53660285675207
#include <iostream>
#include <string>
#include <vector>
#include <utils.hpp>
#include <numeric>
#include <stack>

enum token_type_t {
    NUMBER,
    OPEN_PAR,
    CLOSED_PAR,
    PLUS,
    TIMES,
};

constexpr auto token_type = [](const char ch){
    switch(ch) {
    case '(': return OPEN_PAR;
    case ')': return CLOSED_PAR;
    case '+': return PLUS;
    case '*': return TIMES;
    default: if('0'<=ch&&ch<='9') return NUMBER; else throw "Invalid input!\n";
    }
};

constexpr auto compute = [](const auto lhs, const char op, const auto rhs) {
    if(op == '+') return lhs + rhs;
    else          return lhs * rhs;
};

auto to_rpn(std::string_view str) {
    std::stack<char> op_stack;
    std::vector<char> rpn;
    const auto prec = [](const char ch) { return 0; };
    for(const auto ch : str) {
        switch(token_type(ch)){
        case NUMBER: 
            rpn.push_back(ch); 
            break;
        case PLUS: 
        case TIMES:
            while(!op_stack.empty() && token_type(op_stack.top()) != OPEN_PAR && prec(op_stack.top()) >= prec(ch)) {
                rpn.push_back(op_stack.top()); 
                op_stack.pop();
            }
            op_stack.push(ch); 
            break;
        case OPEN_PAR:
            op_stack.push(ch);
            break;
        case CLOSED_PAR:
            for(auto top = op_stack.top(); token_type(top) != OPEN_PAR; top = op_stack.top()) {
                rpn.push_back(top);
                op_stack.pop();
                if(op_stack.empty()) throw "Unbalanced parentheses!\n";
            }
            op_stack.pop(); // Remove open parenthesis
            break;
        default: throw "Unexpected token!\n";
        }
    }
    while(!op_stack.empty()) {
        rpn.push_back(op_stack.top());
        op_stack.pop();
    }
    return rpn;
}

long long calc(std::string_view str) {
    auto rpn = to_rpn(str);
    std::stack<long long> stack;
    for(const auto ch : rpn) {
        switch(token_type(ch)) {
        case PLUS:
        case TIMES: {
            auto a = stack.top(); stack.pop();
            auto b = stack.top(); stack.pop();
            stack.push(compute(a, ch, b));
        } break;
        case NUMBER:
            stack.push(ch - '0');
        break;
        default: throw "Invalid token!\n";
        }
    }
    return stack.top();
}
int main() {
    const auto input = AoC::get_input("input.txt", {'\n'}, [](std::string str) {
        str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
        return calc(str); // evaluate in place
    });
    std::cout << std::accumulate(input.begin(), input.end(), 0ULL) << std::endl;;
    return 0;
}