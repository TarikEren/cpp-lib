#include "lib/console.h"

//Example dummy functions
void help() {
    printf("Help\n");
}

void hello() {
    printf("Hello\n");
}

int main() {

    //Example usage
    std::map<std::string, void(*)()> command_list {{"-h", help}};
    command_list.insert({"--hello", hello});
    console::listen(command_list, "exit");
    return 0;
}