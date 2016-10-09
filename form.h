#ifndef FORM_HEADER
#define FORM_HEADER

#define FUNCTION 0
#define STRING 1
#define INT 2
#define FLOAT 3
#define DOUBLE 4
#define S_EXPRESSION 5
#define NIL

typedef struct Form {
    int type;
    void *contents;
} Form;

#endif
