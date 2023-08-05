#ifndef __E2SPD_UTILITY_HPP__
#define __E2SPD_UTILITY_HPP__

#include <iostream>
#include <optional>
#include <string_view>

inline std::pair<std::string, std::string> split1(const std::string w,
                                                  const std::string delimiter) {
    auto i = w.find(delimiter);
    if (i == std::string::npos) {
        return std::make_pair(w, "");
    }

    return std::make_pair(w.substr(0, i), w.substr(i));
}

inline void log(std::string w) { std::cout << w << std::endl; }

inline std::optional<int> strToInt(const std::string& w) {
    int i;
    try {
        i = stoi(w);
    } catch (...) {  // FIXME: specify exceptions
        log("error: couldn't convert string to integer.");
        return std::optional<int>();
    }

    return std::optional(i);
}



inline std::string_view ltrim(std::string_view str) {
    const auto pos(str.find_first_not_of(" \t\n\r\f\v"));
    str.remove_prefix(std::min(pos, str.length()));
    return str;
}

inline std::string_view rtrim(std::string_view str) {
    const auto pos(str.find_last_not_of(" \t\n\r\f\v"));
    str.remove_suffix(std::min(str.length() - pos - 1, str.length()));
    return str;
}

inline std::string_view trim(std::string_view str) {
    str = ltrim(str);
    str = rtrim(str);
    return str;
}


#endif
