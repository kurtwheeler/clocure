#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<parser.h>
#include<value.h>
#include<token.h>
#include<tokenStack.h>

//REMOVE LATER:
#include<stdio.h>

// Why not have this use Value* as second parameter?
uint8_t* peelString(uint8_t* remainingText, uint8_t** stringOutput) {
    remainingText++; // move past open double-quote
    uint8_t* stringStart = remainingText;
    uint64_t charsToPeel = 0;

    while(remainingText[0] != '"') {
        if (strlen(remainingText) > 1 && remainingText[0] == '\\'
            && (remainingText[1] == '"' || remainingText[1] == '\\')) {
            charsToPeel += 2;
            remainingText += 2;
        }
        else {
            charsToPeel++;
            remainingText++;
        }
    }

    uint8_t* outputTemp = malloc(charsToPeel+1);
    if(outputTemp == NULL) {
        printf("This is a reminder to check malloc's at some point.\n");
    }
    strncpy(outputTemp, stringStart, charsToPeel);
    outputTemp[charsToPeel] = '\0';
    *stringOutput = outputTemp;

    return ++remainingText; // remove trailing double-quote
}

uint8_t* parseList(uint8_t* input, Value* output) {
    input++; // move past open paren
    output->type = LIST;
    ListNode* head = malloc(sizeof(ListNode));
    output->contents = head;

    while(input[0] != ')') {
        Value* nextValue = malloc(sizeof(Value));
        input = parseValue(input, nextValue);
        head->contents = nextValue;
        ListNode* nextNode = malloc(sizeof(ListNode));
        head->next = nextNode;
        head = nextNode;
    }

    return input++; // move past close paren
}

uint8_t* parseValue(uint8_t* rawText, Value* output) {
    Value* currentValue = NULL;

    //consume whitespace
    while(rawText[0] == ' ') {
        rawText++;
    }

    if(rawText[0] == '(') {
        return parseList(rawText, output);
    }
    else if(currentCharacter == '"') {
        currentValue = malloc(sizeof(Value));
        currentValue->type = STRING;

        uint8_t* peeledString = NULL;
        remainingText = peelString(remainingText, &peeledString);
        currentValue->contents = peeledString;
        printf("%s\n", currentValue->contents);

        currentToken->type = VALUE;
        currentToken->contents = (void*)currentValue;
    }

    struct Value parsedValue;
    parsedValue.type = STRING;
    parsedValue.contents = rawText;

    struct Token parsedToken;
    parsedToken.type = VALUE;
    parsedToken.contents = &parsedValue;
    return parsedToken;
}
