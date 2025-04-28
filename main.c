// @!T File
// @!N main.c
// @!I main program file
// @!G Main
// @!D 21/04/2025
#include "main.h"

char* longArgs[] = {"--help", "\0"};
int longArgRet[] = {1, 0};
int longArgC = 1;
char* shortArgs = "ho\0";
int shortArgRet[] = {1, 0, 0};
int shortArgC = 2;
struct strList* files = NULL;

char* outputFolder = "./";

int parseArgs(int argc, char** argv);
short argFindr(char* str, char arg);
short findArgString(char* lookStr, char* findStr);
void helpPrintout();

// @!T Function
// @!N Main
// @!G Main
// @!I parses arguments
// @!I sends files to be parsed in parser.c
// @!I prints out the files once parsed
// @!I should clean up aswell
int main(int argc, char** argv) {
    int retVal;
    if ((retVal = parseArgs(argc, argv))) {
        return retVal;
    }

    struct strList* fileIterator = files;
    if (!fileIterator) {
        printf("No files added!\n\n");
        helpPrintout();
        // clean up memory before exiting
        destroyStrList(files);
        return 0;
    }
    printf("Generating documentation from the following files: \n");
    printStrList(files);

    printf("\n");
    while (fileIterator != NULL) {
        struct dataList* fileDocs = parseFile(fileIterator);
        
        // default currently will be obsidian.md files with the following linkings
        generateObsidianFiles(fileDocs, outputFolder, fileIterator->str, OB_BY_LINK, OB_BY_GROUP, OB_BY_GROUP);
        
        printf("\n");
        
        // dont need this (clean it up)
        destroyDataList(fileDocs);
        // go to the next element
        fileIterator = fileIterator->next;
    }
    // clean up memory
    destroyStrList(files);
    return 0;
}

// @!T Function
// @!N parseArgs
// @!G Main
// @!I Function for parsing arguments
// @!I Responsible for getting switches and file names/paths
// @!R int
// @!A int argc (amount of arguments)
// @!A char** argv (2D array of chars for each word in the command)
int parseArgs(int argc, char** argv) {
    int outputFlag = 0;
    for (int i = 1; i < argc; i++) { 
        // if the first two characters are '--'
        if (argv[i][0] == '-' && argv[i][1] == '-') {
            // check for long args
            for (int j = 0; j < shortArgC; j++) {
                if (findArgString(argv[i], longArgs[j])) {
                    switch (j) {
                        case 0:
                            // help printout
                            helpPrintout();
                            break;
                    }
                    if (longArgRet[j] != 0) {return longArgRet[j];}
                }
            }
        } // else if only the first character is a '-'
        else if (argv[i][0] == '-') {
            //check for small args
            for (int j = 0; j < shortArgC; j++) {
                if (argFindr(argv[i], shortArgs[j])) {
                    switch (j) {
                        case 0:
                            // help printout
                            helpPrintout();
                            break;
                        case 1:
                            // output folder switch (defaults to current directory)
                            outputFolder = argv[i+1];
                            outputFlag = 1;
                            break;
                    }
                    if (shortArgRet[j] != 0) { return shortArgRet[j]; }
                }
            }
        }
        else if (outputFlag) {
            outputFlag = 0;
        }
        else {
            // assuming its a file to be parsed
            struct strList* newFile = genStrElement(argv[i]);
            if (files == NULL) {
                files = newFile;
            } else {
                (void)addToStrList(files, newFile);
            }
        }
    }
    
    return 0; 
}

// @!T Function
// @!N argFindr
// @!G Main
// @!I Function to find a single char in a string
// @!I Created for the argParser function
// @!A 'string' to search
// @!A character to look for
// @!R short (1 or a 0) (as a boolean)
short argFindr(char* str, char arg) {
    char* currentChar = str; // pointer to the first element
    // iterate through the string
    for (; *currentChar != '\0'; currentChar++) {
        // if we find the argument character, return 1
        if (*currentChar == arg) {
            return 1;
        }
    }
    // if we didnt find anything return 0
    return 0;
}

// @!T Function
// @!N findArgString
// @!G Main
// @!I Finds a string within another string
// @!I Created for the argParser function
// @!A char* (string) to look in
// @!A char* to search for
// @!R short (1 or 0) (treat it like a bool)
short findArgString(char* lookStr, char* findStr) {
    // setup temp pointers to the start of each string
    char* lookStrPtr = lookStr;
    char* findStrPtr = findStr;
    // iterate through the string we are searching against
    for (; *lookStrPtr != '\0'; lookStrPtr++) {
        // if the string we are looking for (or trying to find) has reached its end ('\0')
        // we have found it and can return 1
        if (*findStrPtr == '\0') {
            return 1;
        }
        // if the lookstr char and the findStr char are the same then we increment the findStrPtr
        if (*lookStrPtr == *findStrPtr) {
            findStrPtr++;
        } else {
            // if the characters arent the same, then symmetry is broken and we need to restart
            findStrPtr = findStr;
        }
    }
    // check for if they are both equal to the null ptr for exact string matching
    if (*lookStrPtr == '\0' && *findStrPtr == '\0') { return 1; }
    return 0;
}

void helpPrintout() {
    printf("Jared Van Meppelen Scheppink - 26/04/2025 - v0.1\n");
    printf("Program usage:\n");
    printf("\tdocGen [switches] fileA.a fileB.b fileC.c ...\n");
    printf("Available switches:\n");
    printf("\t-h (--help)\t|\tprintout this menu\n");
    printf("\t-o [Folder]\t|\tset documentation output folder\n");
    // printf("\t\n");
}



// this is going to be a super long line that 'breaks' my code and causes it to fail somehow. However, I have no idea how that will happen. WHICH is why I am typing out this line :)
// it worked :D