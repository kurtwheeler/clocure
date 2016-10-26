#pragma once

#include<stdint.h>
#include<stdbool.h>
#include<token.h>

typedef struct ParserResult {
    bool completed;
    uint8_t* remainingText;
    Token* parsedToken;
} ParserResult;

uint8_t* parseToken(uint8_t* rawText, Token output);
