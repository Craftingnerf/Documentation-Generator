// @!T File
// @!N dataList.c
// @!I File with all the strlist functions I need
// @!G Helper/dataList
// @!D 22/04/2025
#include "main.h"

void destroyDataList(struct dataList *firstPtr);
struct dataList* getLastInDataList(struct dataList *firstPtr);
struct dataList* addToDataList(struct dataList *firstPtr, struct dataList* element);
struct dataList* genDataElement();
struct dataList* pushFrontData(struct dataList* first, struct dataList* element);
void printMiscData(struct miscData* misc);

// @!T Function
// @!N destroyDataList
// @!I goes through and frees all elements in a list
// @!G Helper/dataList
// @!A firstPtr (struct dataList) (First element in the list)
// @!R Void
void destroyDataList(struct dataList *firstPtr) {
    struct dataList *current = firstPtr;
    struct dataList *last;
    while (current->next != NULL) {
        last = current;
        current = current->next;

        free(last->this.type);
        free(last->this.name);
        free(last->this.group);
        free(last->this.retType);
        free(last->this.date);
        destroyStrList(last->this.miscList);
        destroyStrList(last->this.helprList);
        destroyStrList(last->this.argList);

        free(last);
    }
    free(current->this.type);
    free(current->this.name);
    free(current->this.group);
    free(current->this.retType);
    free(current->this.date);
    destroyStrList(current->this.miscList);
    destroyStrList(current->this.helprList);
    destroyStrList(current->this.argList);
    free(current);
}

// @!T function
// @!N getLastInDataList
// @!I goes through entire list to get the last element
// @!G Helper/dataList
// @!A firstPtr (struct dataList*) (First element in the list)
// @!R struct dataList* (dataList pointer) (to the last element)
struct dataList* getLastInDataList(struct dataList *firstPtr) {
    struct dataList* current = firstPtr;
    while (current->next != NULL) {
        current = current->next;
    }
    return current;
}

// @!T function
// @!N addToDataList
// @!I goes to the last element in the list and adds the element argument to the next pointer of the current last element (appends the element to the list)
// @!G Helper/dataList
// @!A firstPtr (struct dataList*) (First element in the list)
// @!A element (struct dataList*) (element to append)
// @!R struct dataList* (dataList pointer) (to the element)
struct dataList* addToDataList(struct dataList *firstPtr, struct dataList* element) {
    struct dataList* last = getLastInDataList(firstPtr);
    last->next = element;
    return element;
}
// @!T function

// @!N genDataElement
// @!I generates a new dataList element
// @!G Helper/dataList
// @!R struct dataList* (element generated)
struct dataList* genDataElement() {
    struct dataList* new;
    new = malloc(1*sizeof(struct dataList));

    // char*'s
    new->this.type    = NULL;
    new->this.name    = NULL;
    new->this.group   = NULL;
    new->this.retType = NULL;
    new->this.date    = NULL;
    
    // lists
    new->this.miscList = NULL;
    new->this.helprList = NULL;
    new->this.argList = NULL;

    new->next         = NULL;
    return new;
}

// @!T function
// @!N pushFrontData
// @!I pushes an element to the front of the list
// @!G Helper/dataList
// @!A datalist* (first element)
// @!A datalist* (seccond element)
// @!R struct dataList* a pointer to the new first element
struct dataList* pushFrontData(struct dataList* first, struct dataList* element) {
    element->next = first;
    return element;
}

// @!T function
// @!N printDataList
// @!I Prints out the information in a datalist :D
// @!G Helper/dataList
// @!A datalist* (first element)
// @!R void
void printDataList(struct dataList* front) {
    struct miscData data;
    usize_t counter = 0;
    while (front != NULL) {
        data = front->this;

        if (data.name != NULL) {
            printf("Name : %s\n", data.name);
        }
        if (data.type != NULL) {
            printf("Type : %s\n", data.type);
        }
        if (data.group != NULL) {
            printf("Group : %s\n", data.group);
        }
        if (data.date != NULL) {
            printf("Date : %s\n", data.date);
        }
        if (data.miscList != NULL) {
            printf("Misc Info :\n");
            counter = 0;
            while (data.miscList != NULL) {
                counter++;
                printf("\t- %s\n", data.miscList->str);
                data.miscList = data.miscList->next;
            }
        }
        if (data.argList != NULL) {
            printf("Argument list :\n");
            counter = 0;
            while (data.argList != NULL) {
                counter++;
                printf("\tArg %lld : %s\n",counter, data.argList->str);
                data.argList = data.argList->next;
            }
        }
        if (data.helprList != NULL) {
            printf("Helper functions :\n");
            counter = 0;
            while (data.helprList != NULL) {
                counter++;
                printf("\tFunction %lld : %s\n",counter, data.helprList->str);
                data.helprList = data.helprList->next;
            }
        }
        printf("\n");
        front = front->next;
    }
}

// @!T function
// @!N printMiscData
// @!I Prints out the information from a miscData struct
// @!G Helper/dataList
// @!A miscData* (data to print)
// @!R void
void printMiscData(struct miscData* misc) {
    struct miscData data = *misc;
    usize_t counter = 0;
    if (data.name != NULL) {
        printf("Name : %s\n", data.name);
    }
    if (data.type != NULL) {
        printf("Type : %s\n", data.type);
    }
    if (data.group != NULL) {
        printf("Group : %s\n", data.group);
    }
    if (data.date != NULL) {
        printf("Date : %s\n", data.date);
    }
    if (data.miscList != NULL) {
        printf("Misc Info :\n");
        counter = 0;
        while (data.miscList != NULL) {
            counter++;
            printf("\t- %s\n", data.miscList->str);
            data.miscList = data.miscList->next;
        }
    }
    if (data.argList != NULL) {
        printf("Argument list :\n");
        counter = 0;
        while (data.argList != NULL) {
            counter++;
            printf("\tArg %lld : %s\n",counter, data.argList->str);
            data.argList = data.argList->next;
        }
    }
    if (data.helprList != NULL) {
        printf("Helper functions :\n");
        counter = 0;
        while (data.helprList != NULL) {
            counter++;
            printf("\tFunction %lld : %s\n",counter, data.helprList->str);
            data.helprList = data.helprList->next;
        }
    }
}