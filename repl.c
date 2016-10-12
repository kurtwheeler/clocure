#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<repl.h>
#include<parser.h>
#include<token.h>

void quit() /* write error message and quit */
{
    fprintf(stderr, "memory exhausted\n");
    exit(1);
}

char* getInput() {
    int max = 20;
    char* input = (char*)malloc(max); // allocate buffer
    if (input == 0) quit();

    int i = 0;
    while (1) {
        int c = getchar();
        if (c == '\n' || c == EOF) { // at end, add terminating zero
            input[i] = 0;
            break;
        }
        input[i] = c;
        if (i == max - 1) { /* buffer full */
            max = max + max;
            input = (char*)realloc(input, max); /* get a new and larger buffer */
            if (input == 0) quit();
        }
        i++;
    }

    return input;
}

int runRepl() {
    printf("Welcome to the Clocure REPL, enter your input below:\n");
    char* replInput;
    Token parsedToken;

    while(1) {
        printf("#> ");
        replInput = getInput();
        if (strcmp(replInput, "exit") == 0) {
            break;
        }

        parsedToken = parseToToken(replInput);

        if(parsedToken.type == STRING) {
            printf("%s\n", (char*)parsedToken.contents);
        }
        else {
            printf("It's not a string, and that's all I know how to print so far.\n");
        }

        free(replInput);
    }

    return 0;
}
