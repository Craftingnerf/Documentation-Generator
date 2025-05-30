// @!T File
// @!N main.h
// @!I header file with imports for the docGen program
// @!G header
// @!D 21/04/2025
#ifndef DocGen
    #define DocGen

    #define TagInitiator "@!"
    #define TagTerminator "!@"
    // keep the tags capitalized!
    // if they arent capitalized then case insensitivity will need to be turned off
    // set the following define to 0 if case insensitivity isnt needed
    #define caseInsensitivity 1
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
    #include <time.h>

    
    extern int quietFlag;
    #define loud (!quietFlag)

    #define usize_t unsigned long long
    #define USIZE_MAX 0xFFFFFFFFFFFFFFFF
    
    // @!T Struct
    // @!N StrList
    // @!G header
    // @!I String list for data storage
    // @!A strList for the next element
    // @!A char* for current string
    // @!F destroyStrList
    // @!F getLastInList
    // @!F addToStrList
    // @!F genStrElement
    // @!F printStrList
    struct strList {
        struct strList* next;
        char* str;
    };
    
    // @!T Struct
    // @!N misc Data
    // @!G header
    // @!I Struct to hold the data of each documentation comment
    // @!A char* for type
    // @!A char* for name
    // @!A char* for group
    // @!A char* for return type
    // @!A char* for date
    // @!A Str list for info
    // @!A Str list for helper functions
    // @!A Str list for arguments
    // @!F printMiscData
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

    // @!T Struct
    // @!N dataList
    // @!G header
    // @!I allows miscData struct to go into its own list format
    // @!A dataList* for the next element
    // @!A miscData - for the current elements data
    // @!F destroyDataList
    // @!F getLastInDataList
    // @!F addToDataList
    // @!F genDataElement
    // @!F pushFrontData
    // @!F printDataList
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
    void printMiscData(struct miscData* misc);

    // filesystem functions
    void make_directory(const char* name);

    // file reader functions
    int getLine(FILE* file, char** buffer, usize_t* bufferSize);
    // normally internal function
    // using it in parser.c
    void extendBlock(char** buffer, usize_t* currentSize, usize_t extendBy);

    // parser functions
    struct dataList* parseFile(struct strList* fileList);
    // fileGenFunctions
    int generateObsidianFiles(struct dataList* doc, char* location, char* parentFile, int fileConn, int typeConn, int groupConn);
    // declarations
    #define OB_NO_CONN 0
    #define OB_BY_GROUP 1
    #define OB_BY_LINK 2
#endif

