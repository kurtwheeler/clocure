#include<stdlib.h>
#include<parser.h>
#include<token.h>

Token parseToToken(char* rawText) {
    struct Token parsedToken;
    parsedToken.type = STRING;
    parsedToken.contents = rawText;
    return parsedToken;
}
