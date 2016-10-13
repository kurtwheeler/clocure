#pragma once

#include<stdint.h>

#define VALUE 0
#define S_EXPRESSION 1
#define OPEN_PAREN 2

typedef struct Token {
    // consider changing ints to stdint types, but doesn't seem necessary
    int type;
    void* contents;
    void* next;
    int lineNumber;
    int columnNumber;
} Token;
