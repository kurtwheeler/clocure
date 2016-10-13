#pragma once

#include<token.h>

typedef struct TokenStackNode {
    Token* token;
    void* next;
} TokenStackNode;
