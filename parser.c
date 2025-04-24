// @!T File
// @!N parser.c
// @!I Line parsing file
// @!G Parser
// @!D 21/04/2025
#include "main.h"

#define LineLength 64
int lineContainsComment(char* line, size_t lineLen, int multilineFlag);

void parseFile(struct strList* fileList) {
    FILE* filePtr = fopen(fileList->str, "r");
    if (filePtr == NULL) {
        printf("Error opening file");
        return;
    }
    size_t* lineSize;
    lineSize = malloc(1*sizeof(size_t));
    *lineSize = LineLength;
    char** line;
    line = (char**)malloc(1*sizeof(char*));
    

    *line = (char*)malloc((*lineSize)*sizeof(char));
    if (!line) {
        printf("Error allocating memory for the line!");
        fclose(filePtr);
        return;
    }

    int strLen = 0;
    int mutliLineComment = 0;
    int lastCommentReturn = 0;
    printf("Opening file : %s\n", fileList->str);
    while (1) {
        /* would put this in the while loop. 
         * However, then I cant read the last line of the file 
         * (getline will return EOF)
         * Need to have the assignment in the while loop and use a break at the end of the loop
         */ 
        strLen = getLine(filePtr, line, lineSize);
        // do what we need to do with the line
        if ((lastCommentReturn = lineContainsComment(*line, strLen, mutliLineComment))) {
            if (lastCommentReturn > 1) {
                mutliLineComment = 1;
            } else if (mutliLineComment) {
                mutliLineComment = 0;
            }
            printf("Multiline: %d, last return val : %d | ", mutliLineComment, lastCommentReturn);
            printf("%s\n", *line);
        } else {
            // printf("%s\n", *line);
        }
        // need this and the assignment at the top of the loop for last line in file to be read
        if (strLen == EOF) {
            break;
        }
    }
    // free the line ptr
    // line size ptr
    // and close the file
    free(line); /* This is a slash-star comment with code before it! */
    free(lineSize); // this is a doubleshash comment with code before it!
    fclose(filePtr);
    /*  This is a multi line comment
     *  If my code works well it should pick this up!
     *  IF it works well that is...
     */
}

int lineContainsComment
    (char* line, size_t lineLen, int multilineFlag) {

    char* linePtr = line;
    int lastSlashFlag = 0;
    int multilineEndFlag = 0;
    for (int count = 0; count < lineLen; count++, linePtr++) {
        // if there is a // or a /* then there is a comment on this line
        // if there is a /* then there is a multiline comment and we need to return 2 for a multiline flag to be set
        
        if (*linePtr == '/') {
            // do / checks
            if (lastSlashFlag && !multilineFlag) {
                return 1;
            } else if (multilineFlag && multilineEndFlag) {
                multilineFlag = 0;
                return 1;
            } else {
                lastSlashFlag = 1;
            }
        } else if (*linePtr == '*') {
            // do * checks
            if (lastSlashFlag && !multilineFlag) {
                // need to check for an end still
                multilineFlag = 1;
            } else if (multilineFlag) {
                multilineEndFlag = 1;
            }
        } else if (lastSlashFlag) {
            lastSlashFlag = 0;
        } else if (multilineEndFlag) {
            multilineEndFlag = 0;
        }
    }
    if (multilineFlag) {
        return 2;
    } else {
        return 0;
    }
}