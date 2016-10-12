#include<stdlib.h>
#include<stdint.h>
#include<parser.h>
#include<token.h>

Token parseToToken(uint8_t* p) {
    void* rawText = p;
    struct Token parsedToken;
    parsedToken.type = STRING;
    parsedToken.contents = rawText;
    return parsedToken;
}
