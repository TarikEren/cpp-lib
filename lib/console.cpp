#include "console.h"

void console::print_color(color bg, color fg, const std::string &str) {
    //If the user provides default values for bg and fg simply print the string
    if (bg == DEFAULT && fg == DEFAULT) {
        std::cout << str;
        return;
    }
    //The beginning characters of the ansi sequence that'll be used and the resulting message
    std::string ansi_sequence = "\x1b[", message{};
    //Check the fg and bg values and append the appropriate values
    switch (fg) {
        case BLACK:
            ansi_sequence.append("30");
            break;
        case WHITE:
            ansi_sequence.append("37");
            break;
        case RED:
            ansi_sequence.append("31");
            break;
        case GREEN:
            ansi_sequence.append("32");
            break;
        case BLUE:
            ansi_sequence.append("34");
            break;
        case YELLOW:
            ansi_sequence.append("33");
            break;
        case CYAN:
            ansi_sequence.append("36");
            break;
        case MAGENTA:
            ansi_sequence.append("35");
            break;
        case DEFAULT:
            break;
    }
    switch (bg) {
        case BLACK:
            ansi_sequence.append(";40m");
            break;
        case WHITE:
            ansi_sequence.append(";47m");
            break;
        case RED:
            ansi_sequence.append(";41m");
            break;
        case GREEN:
            ansi_sequence.append(";42m");
            break;
        case BLUE:
            ansi_sequence.append(";44m");
            break;
        case YELLOW:
            ansi_sequence.append(";43m");
            break;
        case CYAN:
            ansi_sequence.append(";46m");
            break;
        case MAGENTA:
            ansi_sequence.append(";45m");
            break;
        case DEFAULT:
            ansi_sequence.append("m");
            break;
    }
    //The resulting message will be the ansi sequence, the provided message and the reset sequence
    message = ansi_sequence + str + "\x1b[0m";
    //Print the message
    std::cout << message;
}

void console::clear_screen() {
    //Clear the screen
    printf("\033[2J");
}

void console::log(console::level log_level, const std::string& message) {
    //Check the log level and print the corresponding string with appropriate colors
    switch (log_level) {
        case SUCCESS:
            print_color(DEFAULT, GREEN, "OK: ");
            std::cout << message << std::endl;
            break;
        case INFO:
            print_color(DEFAULT, CYAN, "INFO: ");
            std::cout << message << std::endl;
            break;
        case WARNING:
            print_color(DEFAULT, YELLOW, "WARNING: ");
            std::cout << message << std::endl;
            break;
        case ERROR:
            print_color(DEFAULT, RED, "ERROR: ");
            std::cout << message << std::endl;
            break;
    }
}

std::vector<std::string> console::parse_args(std::string line) {
    //Resulting args vector
    std::vector<std::string> args{};
    //String buffer for appending
    std::string buffer{};
    //Index value for the string parsing
    int index = 0;
    //Current character for the string parsing
    char current = line[0];
    //If no arguments were provided, exit the function
    if (line.empty()) {
        log(ERROR, "No command provided");
        return {};
    }
    //Iterate through the string
    while (current != '\0') {
        //If the current character is alphanumeric or a dash
        if (isalnum(current) || current == '-') {
            //Push it onto the buffer
            buffer.push_back(current);
        }
        //If a space is encountered and the buffer isn't empty
        if (current == ' ' && !buffer.empty()) {
            //Push the buffer onto the args vector
            args.push_back(buffer);
            //Clear the buffer for further usage
            buffer.clear();
        }
        //Increment the index value for iterating forward
        index++;
        //Set the current char to the next char
        current = line[index];
    }
    //Push the last token onto the args vector
    args.push_back(buffer);
    //Clear the buffer for the last time
    buffer.clear();
    //Return the vector
    return args;
}

void console::listen(const std::map<std::string, void(*)()>& call_list, const std::string& exit_phrase) {
    //String buffer
    std::string input{};
    //Main loop
    while (input != exit_phrase) {
        //Print input indicator
        std::cout << "> ";
        //Get user input
        std::getline(std::cin, input);
        //Parse user input and return a vector
        std::vector<std::string> args = parse_args(input);
        //If no args were provided, exit the function
        if (args.empty()) {
            return;
        }
        //Get tokens from the vector
        for (const auto& arg: args) {
            //Search the call list
            auto search = call_list.find(arg);
            //If a key has been found
            if (search != call_list.end()) {
                //grab the pointer
                auto ptr = search->second;
                //and dereference the pointer to call the corresponding function
                (*ptr)();
            }
        }
    }
}
