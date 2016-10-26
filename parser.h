#pragma once

#include<stdint.h>
#include<stdbool.h>
#include<token.h>

typedef struct ParserResult {
    bool completed;
    uint8_t* remainingText;
    Value* parsedValue;
} ParserResult;

uint8_t* parseValue(uint8_t* rawText, Value* output);
