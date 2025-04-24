// @!T File
// @!N main.h
// @!I header file with imports
// @!G header
// @!D 21/04/2025
#ifndef DocGen
    #define DocGen

    #define TagInitiator "@!"
    #define TagTerminator "!@"

    #define TypeTag     'T'
    #define NameTag     'N'
    #define InfoTag     'I'
    #define GroupTag    'G'
    #define ArgTag      'A'
    #define ReturnTag   'R'
    #define HelpFuncTag 'F'
    #define DateTag     'D'

    #include <stdio.h>
    #include <stdlib.h>
    
    struct strList {
        struct strList* next;
        char* str;
    };
    
    struct miscData { // has all data elements

        char* type; // type (??)
        char* name; // name
        char* group; // group
        char* retType; // return type
        char* date; // date

        struct strList* miscList; // misc info
        struct strList* helprList; // helper functions
        struct strList* argList; // arguments
    };
    struct dataList {
        struct dataList* next;
        struct miscData this;
    };

    // str list functions
    void destroyStrList(struct strList *firstPtr);
    struct strList* getLastInList(struct strList *firstPtr);
    struct strList* addToStrList(struct strList *firstPtr, struct strList* element);
    struct strList* genStrElement(char* name);
    void printStrList(struct strList *firstPtr);

    // data list functions
    void destroyDataList(struct dataList *firstPtr);
    struct dataList* getLastInDataList(struct dataList *firstPtr);
    struct dataList* addToDataList(struct dataList *firstPtr, struct dataList* element);
    struct dataList* genDataElement();
    struct dataList* pushFrontData(struct dataList* first, struct dataList* element);
    void printDataList(struct dataList* front);

    // filesystem functions
    void make_directory(const char* name);

    // file reader functions
    int getLine(FILE* file, char** buffer, size_t* bufferSize);
    // normally internal function
    // using it in parser.c
    void extendBlock(char** buffer, size_t* currentSize, size_t extendBy);

    // parser functions
    struct dataList* parseFile(struct strList* fileList);
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
