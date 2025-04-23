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
    struct dataList {
        struct miscData* next;
        struct miscData this;
    };

    // str list functions
    void destroyStrList(struct strList *firstPtr);
    struct strList* getLastInList(struct strList *firstPtr);
    struct strList* addToStrList(struct strList *firstPtr, struct strList* element);
    struct strList* genStrEleemnt(char* name);
    void printStrList(struct strList *firstPtr);

    // filesystem functions
    void make_directory(const char* name);

    // file reader functions
    int getLine(FILE* file, char** buffer, size_t* bufferSize);

    // parser functions
    void parseFile(struct strList* fileList);
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
