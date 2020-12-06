#include <sstream>
#include <fstream>
#include <vector>
#include <range/v3/all.hpp>

namespace AoC{
    namespace views = ranges::views;

    auto split(std::string to_split, const std::vector<std::string>& delimiters) {
        std::vector<std::string> ret;
        for(size_t pos = 0; pos != std::string::npos;) {
            const auto it = ranges::min_element(delimiters, [&to_split](auto a, auto b){ return to_split.find(a) < to_split.find(b);});
            pos = to_split.find(*it);
            ret.push_back(to_split.substr(0,pos));
            if(pos != std::string::npos) to_split.erase(0, pos + it->size());
        }
        return ret;
    }

    auto get_input(const std::string& filename, const std::vector<std::string>& delimiters) {
        if(std::ifstream input_file(filename); input_file.is_open()) {
            std::stringstream buffer;
            buffer << input_file.rdbuf();
            return AoC::split(buffer.str(), {"\n\n"});
        } else throw "Invalid input\n";
    };

    auto get_input(const std::string& filename, const char delimiter) {
        if(std::ifstream input_file(filename); input_file.is_open()) {
            std::stringstream buffer;
            buffer << input_file.rdbuf();
            const auto s = buffer.str();
            return ranges::to<std::vector<std::string>>(
                  views::all(s)
                | views::split(delimiter)
                | views::transform(ranges::to<std::string>())
            );
        } else throw "Invalid input\n";
    };

    auto get_input(const std::string& filename, const std::string& delimiter) {
        if (delimiter.length() == 1) {
            return AoC::get_input(filename, delimiter[0]);
        } else {
            return AoC::get_input(filename, {delimiter});
        }
    }
}