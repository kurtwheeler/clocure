#define _GNU_SOURCE

#include<stdlib.h>
#include<stdint.h>
#include<listNode.h>
#include<stdio.h>

uint8_t* toString(Value* this) {
    if(this->type == STRING) {
        char* output;
        asprintf(&output, "\"%s\"", (char*)this->contents);
        return (uint8_t*)output;
    }
    else if(this->type == LONG) {
        char* output;
        asprintf(&output, "%lld", *(long long*)this->contents);
        /* asprintf(&output, "*long*%lld", *(long long*)this->contents); */
        return (uint8_t*)output;
    }
    else if(this->type == DECIMAL) {
        char* output;
        asprintf(&output, "%lf", *(double*)this->contents);
        /* asprintf(&output, "*decimal*%lf", *(double*)this->contents); */
        return (uint8_t*)output;
    }
    else if(this->type == SYMBOL) {
        return (uint8_t*)this->contents;
    }
    else if(this->type == LIST) {
        char* output;
        ListNode* head = this->contents;

        if(head->contents != NULL) {
            asprintf(&output, "(%s", (char*)toString(head->contents));
            head = head->next;
        }
        else {
            asprintf(&output, "(");
        }

        while(head->contents != NULL) {
            char* newOutput;
            asprintf(&newOutput, "%s %s", output, (char*)toString(head->contents));
            free(output);
            output = newOutput;

            head = head->next;
        }

        char* finalOutput;
        asprintf(&finalOutput, "%s)", output);
        free(output);
        return (uint8_t*)finalOutput;
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
    case LONG:
    case DECIMAL:
        printf("freeing a value\n");
        free(this->contents);
        break;
    case LIST:
        printf("freeing a list\n");
        freeList(this);
        break;
    }
}
