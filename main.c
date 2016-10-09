#include<string.h>
#include<stdio.h>
#include<repl.h>

#define REPL_MODE 0
#define COMPILE_MODE 1
#define HELP_MODE 2
#define ERROR_MODE 3

int main(int argc, char *argv[]) {
    int mode = ERROR_MODE;
    if (argc == 1) {
        mode = REPL_MODE;
    }
    else if (argc == 2 && strcmp(argv[1], "repl") == 0) {
        mode = REPL_MODE;
    }
    else if (argc == 2 && strcmp(argv[1], "help") == 0) {
        mode = HELP_MODE;
    }

    if(mode == REPL_MODE) {
        return runRepl();
    }
    else if (mode == HELP_MODE) {
        printf("Look I haven't made another mode yet so just freakin run \"clocjure repl\"!\n");
        return 0;
    }
    else {
        printf("Invalid arguments. Run \"clocure help\" for a help menu.\n");
        return 1;
    }
}
