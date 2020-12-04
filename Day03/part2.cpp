//3316272960
#include <vector>
#include <fstream>
#include <iostream>
#include <regex>
#include <algorithm>
#include <numeric>
 
int main() {
    const auto [input, W, H] = []() {
        unsigned W = 0, H = 0;
        std::vector<bool> input;
        if(std::ifstream input_file("input.txt"); input_file.is_open()) {
            for(std::string map_line; std::getline(input_file, map_line, '\n');) {
                if (!W) W = map_line.length();
                for(const auto ch : map_line) {
                    input.push_back(ch == '#');
                }
                H++;
            }
        }
        return std::tuple{input, W, H};
    }();
    const std::vector<std::pair<unsigned, unsigned>> slopes {{1,1}, {3,1}, {5,1}, {7,1}, {1,2}};
    unsigned prod = std::accumulate(
        std::begin(slopes), 
        std::end(slopes),
        1,
        [W, H, &input](auto lhs, const auto& slope) {
            const auto to_acc = std::views::common(
                std::views::iota(0) 
                | std::views::transform([W, R = slope.first, D = slope.second](auto i){return i*D*W + ((i*R) % W);})
                | std::views::take_while([W,H](auto i) {return i < W*H;})
                | std::views::transform([&input](auto i) {return input[i];})
            );
            return lhs * std::accumulate(std::ranges::begin(to_acc), std::ranges::end(to_acc), 0);
        }
    );
    std::cout << prod << std::endl;
    return 0;
}