#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<reader.h>
#include<value.h>
#include<listNode.h>

//REMOVE LATER:
#include<stdio.h>

// May need to go to a utils file at some point
// Returns true if the first char of a is in b
bool firstCharIn(const char* a, const char* b) {
    char* firstOccurance = strpbrk(a, b);
    if(firstOccurance != 0 && a[0] == *firstOccurance) {
        return true;
    }
    else {
        return false;
    }
}

char* parseString(char* remainingText, Value* output) {
    remainingText++; // move past open double-quote
    char* stringStart = remainingText;
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

    char* outputString = malloc(charsToPeel+1);
    if(outputString == NULL) {
        printf("This is a reminder to check malloc's at some point.\n");
    }
    strncpy(outputString, stringStart, charsToPeel);
    outputString[charsToPeel] = '\0';

    output->type = STRING;
    output->contents = outputString;

    return ++remainingText; // remove trailing double-quote
}

// still limited, doesn't handle BIGINT, RATIO, or BIGDECIMAL
char* parseNumber(char* input, Value* output) {
    char* remainingText = input;
    long charsToPeel = 0;

    while(remainingText[0] != '\0' && !firstCharIn(remainingText, " \"\\\()")) {
        charsToPeel++;
        remainingText++;
    }

    char* numberString = malloc(charsToPeel+1);
    if(numberString == NULL) {
        printf("This is a reminder to check malloc's at some point.\n");
    }
    strncpy(numberString, input, charsToPeel);
    numberString[charsToPeel] = '\0';

    if(strpbrk(numberString, ".") != 0) {
        output->type = DECIMAL;
        double* numberValue = malloc(sizeof(double));
        sscanf(numberString, "%lf", numberValue);
        output->contents = numberValue;
    }
    else {
        output->type = LONG;
        long long* numberValue = malloc(sizeof(long long));
        sscanf(numberString, "%lld", numberValue);
        output->contents = numberValue;
    }

    return remainingText;
}

char* parseSymbol(char* input, Value* output) {
    char* remainingText = input;
    uint64_t charsToPeel = 0;

    while(remainingText[0] != '\0' && !firstCharIn(remainingText, " \"\\\()")) {
        charsToPeel++;
        remainingText++;
    }

    char* outputString = malloc(charsToPeel+1);
    if(outputString == NULL) {
        printf("This is a reminder to check malloc's at some point.\n");
    }
    strncpy(outputString, input, charsToPeel);
    outputString[charsToPeel] = '\0';

    output->type = SYMBOL;
    output->contents = outputString;

    return remainingText;
}

char* parseList(char* input, Value* output) {
    input++; // move past open paren
    output->type = LIST;

    ListNode* head = malloc(sizeof(ListNode));
    head->contents = NULL;
    head->next = NULL;
    output->contents = head;

    while(input[0] != ')') {
        Value* nextValue = malloc(sizeof(Value));
        input = readValue(input, nextValue);
        head->contents = nextValue;

        ListNode* nextNode = malloc(sizeof(ListNode));
        nextNode->contents = NULL;
        nextNode->next = NULL;

        head->next = nextNode;
        head = nextNode;
    }

    return ++input; // move past close paren
}

char* readValue(char* rawText, Value* output) {
    //consume whitespace
    while(rawText[0] == ' ') {
        rawText++;
    }

    if(rawText[0] == '(') {
        return parseList(rawText, output);
    }
    else if(rawText[0] == '"') {
        return parseString(rawText, output);
    }
    else if(firstCharIn(rawText, "0123456789")) {
        return parseNumber(rawText, output);
    }
    else {
        return parseSymbol(rawText, output);
    }
}
