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
