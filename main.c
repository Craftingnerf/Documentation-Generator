// @!T File
// @!N main.c
// @!I main program file
// @!G Main
// @!D 21/04/2025
#include "main.h"

char* longArgs[] = {"--help", "--time", "--quiet", "\0"};
int longArgRet[] = {1, 0, 0, 0};
int longArgC = 3;
char* shortArgs = "hotq\0";
int shortArgRet[] = {1, 0, 0, 0, 0};
int shortArgC = 4;
struct strList* files = NULL;

char* outputFolder = "./";

int timeFlag = 0;
clock_t start_clock = 0, end_clock = 0;
double runtime = 0.0;

int quietFlag = 0;

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
    if (timeFlag) {
        start_clock = clock();
    }


    struct strList* fileIterator = files;
    if (!fileIterator) {
        printf("No files added!\n\n");
        helpPrintout();
        // clean up memory before exiting
        destroyStrList(files);
        return 0;
    }
    if (loud) printf("Generating documentation from the following files: \n");
    if (loud) printStrList(files);

    if (loud) printf("\n");
    while (fileIterator != NULL) {
        struct dataList* fileDocs = parseFile(fileIterator);
        
        // default currently will be obsidian.md files with the following linkings
        generateObsidianFiles(fileDocs, outputFolder, fileIterator->str, OB_BY_LINK, OB_BY_GROUP, OB_BY_GROUP);
        
        if (loud) printf("\n");
        
        // dont need this (clean it up)
        destroyDataList(fileDocs);
        // go to the next element
        fileIterator = fileIterator->next;
    }
    // clean up memory
    destroyStrList(files);
    if (timeFlag) {
        end_clock = clock();
        runtime = (double)(end_clock - start_clock) / CLOCKS_PER_SEC;
        printf("Program took : %fs\n", runtime);
    }

    if (loud) printf("Documentation generated!\n");
    if (loud) printf("Have fun programming! :D\n");
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
                        case 1:
                            // time flag
                            timeFlag = 1;
                            break;
                        case 2:
                            // quiet flag
                            // printf("Found quiet flag\n");
                            quietFlag = 1;
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
                        case 2:
                            // time flag
                            timeFlag = 1;
                            break;
                        case 3:
                            // quiet flag
                            // printf("Found quiet flag\n");
                            quietFlag = 1;
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
            // need to allocate a new string for it
            usize_t sizeOfStr = 0;
            // get the size
            for (sizeOfStr = 0; *(argv[i]+sizeOfStr) != '\0'; sizeOfStr++);
            // allocate the string + 1 for the null terminator
            char* fname = malloc((sizeOfStr+1) * sizeof(char));
            // go through and copy the string
            for (usize_t k = 0; k < sizeOfStr; k++) { *(fname+k) = *(argv[i]+k); }
            // set the null terminator at the end
            *(fname+sizeOfStr) = '\0';

            struct strList* newFile = genStrElement(fname);
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
    printf("\t-t (--time)\t|\ttimes the programs speed\n");
    printf("\t-q (--quiet)\t|\ttells the program to not print anything\n");
    // printf("\t\n");
}
