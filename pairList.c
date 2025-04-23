// @!T File
// @!N pairList.c
// @!I File with all the pairlist data I need
// @!G Helper/pairList
// @!D 21/04/2025
#include "main.h"


struct charIntList;
struct strList;

int addToList(struct charIntList *first, struct charIntList *value) {
    struct charIntList* current = first;
    while (current->next != NULL && !charEquals(current->key, value->key)) {
        current = current->next;
    }
    if (!charEquals(current->key, value->key)) {
        current->next = value; 
    } else {
        current->pair = value->pair;
    }

    return 0;
}
struct charIntList* getListElement(struct charIntList *first, char* listKey)  {
    struct charIntList* current = first;
    while (!charEquals(current->key, listKey) && current->next != NULL) {
        current = current->next;
    }
    if (charEquals(current->key, listKey)) {
        return current;
    } else {
        return NULL;
    }
}


struct charIntList* newListElement(char* str) {
    struct charIntList* elemnt;
    elemnt = malloc(1*sizeof(struct charIntList));
    elemnt->key = str;
    elemnt->pair = 0;
    elemnt->next = NULL;
    return elemnt;
}

void destroyList(struct charIntList *first) {
    struct charIntList *current = first;
    struct charIntList *last;
    while (current->next != NULL) {
        last = current;
        current = current->next;
        free(last);
    }
    free(current);
}

int containsKey(struct charIntList *first, char* value) {
    struct charIntList *current = first;
    while (current->next != NULL && !charEquals(current->key, value)) {
        current = current->next;
    }
    return charEquals(current->key, value);
}

int charEquals(char* case1, char* case2) {
    while (*case1 == *case2 && *case1 != '\0' && *case2 != '\0') {
        case1++;
        case2++;
    }
    return (*case1 == *case2);
}



