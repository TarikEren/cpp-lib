#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace console {
    //Defined colors for the colored printing function
    typedef enum colors {
        BLACK,
        WHITE,
        RED,
        GREEN,
        BLUE,
        YELLOW,
        CYAN,
        MAGENTA,
        DEFAULT
    }color;

    //Defined levels for the logging function
    typedef enum levels {
        SUCCESS,
        INFO,
        WARNING,
        ERROR
    }level;

    //Colored printing
    void print_color(color bg, color fg, const std::string &str);

    //Clears screen
    void clear_screen();

    //Prints out the provided message with the appropriate log level
    void log(level log_level, const std::string& message);

    //Parses the provided line parameter, tokenizes it and returns a string vector that contains said tokens
    std::vector<std::string> parse_args(std::string line);

    //Listens user inputs with a while loop.
    //Parses the user input and tokenizes it.
    //Checks if any valid tokens exist. If there are any, program calls the corresponding function.
    //If the exit_phrase is detected, the loop ends.
    void listen(const std::map<std::string, void(*)()>& call_list, const std::string& exit_phrase);
}

