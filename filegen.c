// @!T File
// @!N filegen.c
// @!G fileGenerator
// @!I file with functions for generating all the files and folders (maybe) for the documentation
// @!D 26/04/2025
#include "main.h"
char* getFilename(char* name, char* extension, char* path, size_t* newStrSize);
int appendPath(char** strToAppend, size_t* strSize, char* path);
int toLower(char* toLowerStr);
int toUpper(char* toUpperStr);

// @!T Function
// @!N generateObsidianFiles
// @!G fileGenerator
// @!A struct dataList* | documentation data to pull from
// @!A char* | location to put the file
// @!A char* | parent file name
// @!A int | File connection | how to link the file to its parent file (none, group, link)
// @!A int | type connection | how to link the file to its type (none, group, link)
// @!A int | group connection | how to link the file to its group (none, group, link)
// @!R int | 0 if ran normally, anything else is a different problem
int generateObsidianFiles(struct dataList* doc, char* location, char* parentFile, int fileConn, int typeConn, int groupConn) {
    printf("Generating Obsidian files at %s\n", location);
    printf("Not currently implemented!\n");
    struct miscData data;
    size_t counter = 0;
    FILE* file;
    while (doc != NULL) {
        data = doc->this;
        size_t filenameSize = 0;
        char* filename;
        
        if (data.name != NULL) {
            printf("Generating filename for : %s\n", data.name);
            filename = getFilename(data.name, "md", location, &filenameSize);
            // if (appendPath(&filename, &filenameSize, location)) {
            //     free(filename);
            //     printf("Something went wrong!\n");
            //     printf("\n");
            //     doc = doc->next;
            //     continue;
            // }
            // printf("Filename : %s, size: %lld\nAt : %p\n", filename, filenameSize, filename);
            file = fopen(filename, "w");
        } else {
            printf("documentation name not found!\n");
            printMiscData(&(doc->this));
            doc = doc->next;
            continue;
        }
        
        printf("Adding data for the file\n");
        file = fopen(filename, "w");
        printf("\tparent file\n");
        if (parentFile != NULL) {
            switch (fileConn) {
                case 0:
                    fprintf(file, "Found in file : %s\n", parentFile);
                    break;
                case 1:
                    fprintf(file, "Found in file : #%s\n", parentFile);
                    break;
                case 2:
                    fprintf(file, "Found in file : [[%s]]\n", parentFile);
                    break;
            }
        }
        printf("\tdoc type\n");
        if (data.type != NULL) {
            toLower(data.type);
            switch (typeConn) {
                case 0:
                    fprintf(file, "Type : %s\n", data.type);
                    break;
                case 1:
                    fprintf(file, "Type : #%s\n", data.type);
                    break;
                case 2:
                    fprintf(file, "Type : [[%s]]\n", data.type);
                    break;
            }
        }
        printf("\tdoc group\n");
        if (data.group != NULL) {
            toLower(data.group);
            switch (groupConn) {
                case 0:
                    fprintf(file, "Group : %s\n", data.group);
                    break;
                case 1:
                    fprintf(file, "Group : #%s\n", data.group);
                    break;
                case 2:
                    fprintf(file, "Group : [[%s]]\n", data.group);
                    break;
            }
            
        }
        printf("\tdoc date\n");
        if (data.date != NULL) {
            fprintf(file, "Date : %s\n", data.date);
        }
        printf("\tdoc info list\n");
        if (data.miscList != NULL) {
            fprintf(file, "Misc Info :\n");
            counter = 0;
            while (data.miscList != NULL) {
                counter++;
                fprintf(file, "\t- %s\n", data.miscList->str);
                data.miscList = data.miscList->next;
            }
        }
        printf("\targument list\n");
        if (data.argList != NULL) {
            fprintf(file, "Argument list :\n");
            counter = 0;
            while (data.argList != NULL) {
                counter++;
                fprintf(file, "\tArg %lld : %s\n",counter, data.argList->str);
                data.argList = data.argList->next;
            }
        }
        printf("\thelper functions\n");
        if (data.helprList != NULL) {
            fprintf(file, "Helper functions :\n");
            counter = 0;
            while (data.helprList != NULL) {
                counter++;
                fprintf(file, "\tFunction %lld : [[%s]]\n",counter, data.helprList->str);
                data.helprList = data.helprList->next;
            }
        }
        printf("Closing file\n");
        fclose(file);
        printf("freeing filename\n");
        free(filename);
        printf("going to next item\n");
        doc = doc->next;
    }
    return 0;
}

// @!T Function
// @!N getFilename
// @!G fileGenerator
// @!A char* | name of the file
// @!A char* | extension to add to the file
// @!A size_t* | ptr for the new strings length
// @!R char* | filename string
char* getFilename(char* name, char* extension, char* path, size_t* newStrSize) {
    size_t nameLen;
    size_t extensionLen;
    size_t pathLen;
    // find the lengths of both the name string and the extension string
    for (pathLen = 0; *(path+pathLen) != '\0'; pathLen++);
    for (nameLen = 0; *(name+nameLen) != '\0'; nameLen++);
    for (extensionLen = 0; *(extension+extensionLen) != '\0'; extensionLen++);

    size_t sizeOfNewStr = (pathLen+nameLen+extensionLen+2); // need the '\0' and '.' still :) (why we add 2 here)
    // allocate new string (needs to be free'd later);
    char* str = malloc(sizeOfNewStr*sizeof(char)); 

    // setup the string index for assymetrical copying
    size_t strIndex = 0;
    str[sizeOfNewStr-1] = '\0';
    // copy in the path
    for (int i = 0; i < pathLen; i++) {
        *(str+strIndex) = *(path+i);
        strIndex++;
    }
    // printf("path should be here : %s\n", str);
    // loop through the first string adding every character (except for the null terminator)
    for (int i = 0; i < nameLen; i++) {
        *(str+strIndex) = *(name+i);
        strIndex++;
    }
    // printf("filename should be here : %s\n", str);
    // insert the period
    *(str+strIndex) = '.';
    strIndex++;
    // loop through the seccond string adding everything but the null terminator again
    for (int i = 0; i < extensionLen; i++) {
        *(str+strIndex) = *(extension+i);
        strIndex++;
    }
    // printf("ENTIRE STRING should be here : %s\n", str);
    // insert a null terminator :)
    str[sizeOfNewStr-1] = '\0';
    // set the size of the new string
    *newStrSize = sizeOfNewStr;
    return str;
}


// @!T Function
// @!N toLower
// @!G fileGenerator
// @!A char* | string to make lowercase
// @!R int | returns an int based off of function success
// @!I This function is distructive
// @!I #DESTRUCTIVE
int toLower(char* toLowerStr) {
    for (; *toLowerStr != '\0'; toLowerStr++) {
        if (*toLowerStr >= 'A' && *toLowerStr <= 'Z') {
            *toLowerStr = (*toLowerStr - 'A') + 'a';
        }
    }
    return 0;
}

// @!T Function
// @!N toUpper
// @!G fileGenerator
// @!A char* | string to make uppercase
// @!R int | returns an int based off of function success
// @!I This function is distructive
// @!I #DESTRUCTIVE
int toUpper(char* toUpperStr) {
    for (; *toUpperStr != '\0'; toUpperStr++) {
        if (*toUpperStr >= 'a' && *toUpperStr <= 'z') {
            *toUpperStr = (*toUpperStr - 'a') + 'A';
        }
    }
    return 0;
}