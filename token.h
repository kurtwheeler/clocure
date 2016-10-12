#pragma once

#include<stdint.h>

#define IDENTIFIER 0
#define STRING 1
#define INT 2
#define FLOAT 3
#define DOUBLE 4
#define S_EXPRESSION 5
#define KEYWORD 6
#define NIL 7
#define OPEN_PAREN 8

typedef struct Token {
    int type;
    void* contents;
    void* next;
    int lineNumber;
    int columnNumber;
} Token;
