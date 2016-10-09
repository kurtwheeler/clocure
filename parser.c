#include<stdlib.h>
#include<parser.h>
#include<form.h>

Form parseToForm(char* rawText) {
    struct Form parsedForm;
    parsedForm.type = STRING;
    parsedForm.contents = rawText;
    return parsedForm;
}
