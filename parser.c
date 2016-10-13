#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<parser.h>
#include<value.h>
#include<token.h>
#include<tokenStack.h>

//REMOVE LATER:
#include<stdio.h>

uint8_t* peelString(uint8_t* remainingText, uint8_t** stringOutput) {
    remainingText++; // move past open double-quote
    uint8_t* stringStart = remainingText;
    uint64_t charsToPeel = 0;

    // You think it's really this easy?
    // You have to support \\, and newlines
    // \\ should be easy, but newlines is the repl's problem
    // Well maybe not only. It has to know when to continue, and it'll only if
    // the parser tells it. Need a way to pass that up. True for parens too
    while(remainingText[0] != '"') {
        if (strlen(remainingText) > 1 && remainingText[0] == '\\'
            && (remainingText[1] == '"' || remainingText[1] == '\\')) {
            charsToPeel += 2;
            remainingText += 2; // This is leaving \\" in the string instead of \"
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

Token parseToToken(uint8_t* rawText) {
    Value* currentValue = NULL;
    Token* currentToken = NULL;
    Token* lastToken = NULL;
    TokenStackNode* stackHead = NULL;
    TokenStackNode* stackLast = NULL;
    uint8_t* remainingText = rawText;
    uint8_t currentCharacter;

    do {
        currentCharacter = remainingText[0];
        currentToken = malloc(sizeof(Token));

        if(currentCharacter == '(') {
            currentToken->type = OPEN_PAREN;

            remainingText++;
        }
        else if (currentCharacter == '"') {
            currentValue = malloc(sizeof(Value));
            currentValue->type = STRING;

            uint8_t* peeledString = NULL;
            remainingText = peelString(remainingText, &peeledString);
            currentValue->contents = peeledString;

            currentToken->type = VALUE;
            currentToken->contents = (void*)currentValue;
        }

        stackHead = malloc(sizeof(TokenStackNode));
        stackHead->token = currentToken;
        stackHead->next = stackLast;
        stackLast = stackHead;

    } while (strlen(remainingText) > 0);

    struct Value parsedValue;
    parsedValue.type = STRING;
    parsedValue.contents = rawText;

    struct Token parsedToken;
    parsedToken.type = VALUE;
    parsedToken.contents = &parsedValue;
    return parsedToken;
}
