#include <sstream>
#include <fstream>
#include <vector>
#include <range/v3/all.hpp>

namespace AoC{
    namespace views = ranges::views;

    auto idem_return = [](const std::string& s) -> std::string {return s;};

    template<typename L = decltype(idem_return)>
    auto split(std::string to_split, const std::initializer_list<std::string>& delimiters,
               L l = idem_return) {
        std::vector<decltype(l(""))> ret;
        for(size_t pos = 0; pos != std::string::npos;) {
            const auto it = ranges::min_element(delimiters, [&to_split](auto a, auto b){ return to_split.find(a) < to_split.find(b);});
            pos = to_split.find(*it);
            const auto token = to_split.substr(0,pos);
            if(token.length() > 0) ret.push_back(l(token));
            if(pos != std::string::npos) to_split.erase(0, pos + it->size());
        }
        return ret;
    }

    template<typename L = decltype(idem_return)>
    auto split(std::string to_split, const std::string& delimiter,
               L l = idem_return) {
        return AoC::split(to_split, {delimiter}, l);
    }

    template<typename L = decltype(idem_return)>
    auto split(std::string to_split, const char delimiter,
               L l = idem_return) {
        return AoC::split(to_split, std::string(1, delimiter), l);
    }

    template<typename L = decltype(idem_return)>
    auto get_input(const std::string& filename, const std::initializer_list<std::string>& delimiters,
               L l = idem_return) {
        if(std::ifstream input_file(filename); input_file.is_open()) {
            std::stringstream buffer;
            buffer << input_file.rdbuf();
            return AoC::split(buffer.str(), delimiters, l);
        } else throw "Invalid input\n";
    };

    template<typename L = decltype(idem_return)>
    auto get_input(const std::string& filename, const std::string& delimiter,
               L l = idem_return) {
        return AoC::get_input(filename, {delimiter}, l);
    }

    template<typename L = decltype(idem_return)>
    auto get_input(const std::string& filename, const char delimiter,
               L l = idem_return) {
        return AoC::get_input(filename, std::string(1, delimiter), l);
    };
}