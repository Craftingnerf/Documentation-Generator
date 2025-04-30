// @!T File
// @!N strList.c
// @!I File with all the strlist functions I need
// @!G Helper/strList
// @!D 22/04/2025

#include "main.h"


// @!T function
// @!N destroyStrList
// @!G Parser
// @!I goes through and frees all elements in a list
// @!G Helper/strList
// @!A firstPtr (struct strList) (First element in the list)
// @!R Void
void destroyStrList(struct strList *firstPtr) {
    if (firstPtr == NULL) {
        return;
    }
    struct strList *current = firstPtr;
    struct strList *last;
    
    while (current->next != NULL) {
        last = current;
        current = current->next;
        free(last);
    }
    free(current);
}

// @!T function
// @!N getLastInList
// @!G Parser
// @!I goes through entire list to get the last element
// @!G Helper/strList
// @!A firstPtr (struct strList*) (First element in the list)
// @!R struct strList* (strList pointer) (to the last element)
struct strList* getLastInList(struct strList *firstPtr) {
    struct strList* current = firstPtr;
    if (current == NULL) {
        return NULL;
    }
    while (current->next != NULL) {
        current = current->next;
    }
    return current;
}

// @!T function
// @!N addToStrList
// @!G Parser
// @!I goes to the last element in the list and adds the element argument to the next pointer of the current last element (appends the element to the list)
// @!G Helper/strList
// @!A firstPtr (struct strList*) (First element in the list)
// @!A element (struct strList*) (element to append)
// @!R struct strList* (strList pointer) (to the element)
struct strList* addToStrList(struct strList *firstPtr, struct strList* element) {
    if (firstPtr == NULL) {
        return NULL;
    }
    struct strList* last = getLastInList(firstPtr);
    last->next = element;
    return element;
}

// @!T function
// @!N genStrElement
// @!G Parser
// @!I generates a new strList element
// @!G Helper/strList
// @!A name (char* (string)) (String value for the element)
// @!R struct strList (element generated)
struct strList* genStrElement(char* name) {
    struct strList* new;
    new = malloc(1*sizeof(struct strList));
    new->str = name;
    new->next = NULL;
    return new;
}

// @!T function
// @!N printStrList
// @!G Parser
// @!I Goes through a strlist and prints out each element # and string
// @!G Helper/strList
// @!A firstPtr (struct strList*) (First element in the list)
// @!R void
void printStrList(struct strList *firstPtr) {
    usize_t count = 0;
    struct strList *current = firstPtr;
    while (current->next != NULL) {
        printf("%lld - %s\n", ++count, current->str);
        current = current->next;
    }
    printf("%lld - %s\n", ++count, current->str);
    current = current->next;
}