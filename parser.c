// @!T File
// @!N parser.c
// @!I Line parsing file
// @!G Parser
// @!D 21/04/2025
#include "main.h"

#define LineLength 64

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

    printf("Pointer printout:\n");
    printf("\tline : %p\n", line);
    printf("\texpected line end : %p\n", line + *lineSize);
    printf("\t*line : %p\n", *line);
    printf("\tlineSize : %p\n", lineSize);
    printf("\tFile : %p\n", filePtr);

    int val = 0;
    printf("\t&val : %p\n", &val);
    printf("Opening file : %s\n", fileList->str);
    while ((val = getLine(filePtr, line, lineSize)) != EOF) {
        // do what we need to do with the line
        
        printf("%s\n", *line);
    }
    // free the line ptr
    // line size ptr
    // and close the file
    free(line);
    free(lineSize);
    fclose(filePtr);
}
