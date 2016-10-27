#define _GNU_SOURCE

#include<stdlib.h>
#include<stdint.h>
#include<listNode.h>
#include<stdio.h>

char* toString(Value* this) {
    if(this->type == STRING) {
        char* output;
        asprintf(&output, "\"%s\"", (char*)this->contents);
        return output;
    }
    else if(this->type == LONG) {
        char* output;
        asprintf(&output, "%lld", *(long long*)this->contents);
        /* asprintf(&output, "*long*%lld", *(long long*)this->contents); */
        return output;
    }
    else if(this->type == DECIMAL) {
        char* output;
        asprintf(&output, "%lf", *(double*)this->contents);
        /* asprintf(&output, "*decimal*%lf", *(double*)this->contents); */
        return output;
    }
    else if(this->type == SYMBOL || this->type == NIL || this->type == BOOLEAN
            || this->type == KEYWORD) {
        return (char*)this->contents;
    }
    else if(this->type == LIST) {
        char* output;
        ListNode* head = this->contents;

        if(head->contents != NULL) {
            asprintf(&output, "(%s", toString(head->contents));
            head = head->next;
        }
        else {
            asprintf(&output, "(");
        }

        while(head->contents != NULL) {
            char* newOutput;
            asprintf(&newOutput, "%s %s", output, toString(head->contents));
            free(output);
            output = newOutput;

            head = head->next;
        }

        char* finalOutput;
        asprintf(&finalOutput, "%s)", output);
        free(output);
        return finalOutput;
    }
    else {
        return "It's neither a string nor a list, and that's all I know how to print so far.";
    }
}

void freeList(Value* this) {
    ListNode* head = this->contents;
    while(head != NULL) {
        if(head->contents != NULL){
            freeValueContents(head->contents);
            free(head->contents);
        }

        ListNode* next = head->next;
        free(head);
        head = next;
    }
}

void freeValueContents(Value* this) {
    switch(this->type) {
    case STRING:
    case SYMBOL:
    case KEYWORD:
    case LONG:
    case DECIMAL:
    case NIL:
    case BOOLEAN:
        free(this->contents);
        break;
    case LIST:
        freeList(this);
        break;
    }
}
