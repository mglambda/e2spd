

#ifndef __E2SPD_LOG_HPP__
#define __E2SPD_LOG_HPP__

#include <iostream>
#include <fstream>

#include <sstream>

inline void addToStream(std::ostringstream&) {}

template <typename T, typename... Args>
void addToStream(std::ostringstream& a_stream, T&& a_value, Args&&... a_args) {
    a_stream << std::forward<T>(a_value);
    addToStream(a_stream, std::forward<Args>(a_args)...);
}

template <typename... args_T>
auto concat(args_T&&... args) -> std::string {
    std::ostringstream msgText;
    addToStream(msgText, std::forward<args_T>(args)...);
    return msgText.str();
}

template <typename msg_t, typename... args_t>
void log(args_t&&... args) {
    msg_t::write(std::forward<args_t>(args)...);
}

struct Debug {
    static std::ofstream destination;
    template <typename... args_t>
    static void write(args_t&&... args) {
        auto msg = concat(std::forward<args_t>(args)...);
        Debug::destination << msg << std::endl;
    }
};


struct Raw {
    static std::ofstream destination;
    template <typename... args_t>
    static void write(args_t&&... args) {
        auto msg = concat(std::forward<args_t>(args)...);
        Raw::destination << msg << std::endl;
    }
};



struct Error {
    static std::ofstream destination;
    template <typename... args_t>
    static void write(args_t&&... args) {
        auto msg = concat(std::forward<args_t>(args)...);
        Error::destination << msg << std::endl;
    }
};

#endif
