#pragma once

#include<stdint.h>

#define IDENTIFIER 0
#define STRING 1
#define INT 2
#define FLOAT 3
#define DOUBLE 4
#define LIST 5
#define KEYWORD 6
#define NIL 7

typedef struct Value {
    int type;
    void* contents;
} Value;

uint8_t* toString(Value* this);
