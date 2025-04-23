// @!T File
// @!N main.h
// @!I header file with imports
// @!G header
// @!D 21/04/2025
#ifndef DocGen
    #define DocGen

    #define TagInitiator "@!"
    #include <stdio.h>
    #include <stdlib.h>
    struct charIntList {
        int pair;
        struct charIntList *next;
        char* key;
    };
    struct strList {
        struct strList* next;
        char* str;
    };
    
    struct fileData { // just file data
        int miscC; // misc info count
        char* type; // type (file)
        char* name; // name
        char* group; // group
        char* date; // date
        char** miscV; // misc info
    };
    struct funcData { // just function data
        int miscC; // misc info count
        int argC; // argument count
        char* type; // type (function)
        char* name; // name
        char* group; // group
        char* retType; // return type
        char** miscV; // misc info
        char** argV; // arguments
    };
    struct structData { // just struct data
        int miscC; // misc info count
        int helprC; // helper functions count
        char* type; // type (struct)
        char* name; // name
        char* group; // group
        char** miscV; // misc info
        char** helprV; // helper functions
    };
    struct miscData { // has all data elements
        int miscC; // misc info count
        int helprC; // helper functions count
        int argC; // argument count

        char* type; // type (??)
        char* name; // name
        char* group; // group
        char* retType; // return type
        char* date; // date

        char** miscV; // misc info
        char** helprV; // helper functions
        char** argV; // arguments
    };

    int addToList(struct charIntList *first, struct charIntList *value);
    struct charIntList* getListElement(struct charIntList *first, char* listKey);
    struct charIntList* newListElement(char* str);
    void destroyList(struct charIntList *first);
    int containsKey(struct charIntList *first, char* value);
    int readline(FILE* file, char* stream, size_t streamLen);
    void clearStream(char* stream, size_t len);
    int charEquals(char* case1, char* case2);


    // str list functions
    void destroyStrList(struct strList *firstPtr);
    struct strList* getLastInList(struct strList *firstPtr);
    struct strList* addToStrList(struct strList *firstPtr, struct strList* element);
    struct strList* genStrEleemnt(char* name);
    void printStrList(struct strList *firstPtr);
#endif



// Documentation comments

// -- general --
// @!T Type (Function, Struct, File, Misc)
// @!N Name
// @!I Misc info
// @!G grouping (defaults to file)
// ^ folder for the documentation to be in (MD documentation style)

// -- function specific --
// @!A Arguments
// @!R Return type

// -- struct specific --
// @!F helper functions

// -- file specific --
// @!D Date
