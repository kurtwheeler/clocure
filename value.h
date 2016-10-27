#pragma once

#include<stdint.h>

#define SYMBOL 0
#define KEYWORD 1
#define NIL 2
#define LIST 3
#define STRING 4
#define LONG 5
#define BIGINT 6
#define RATIO 7
#define DECIMAL 8
#define FLOAT 9
#define BIGDECIMAL 10
#define BOOLEAN 11
#define CHARACTER 12

typedef struct Value {
    int type;
    void* contents;
} Value;

char* toString(Value* this);
void freeValueContents(Value* this);
