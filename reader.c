// @!T File
// @!N Reader.c
// @!I Reader file
// @!G Reader
// @!D 21/04/2025
#include "main.h"

#define CNBlockSize 128

void clearStream(char* stream, size_t len);

void extendBlock(char* stream, size_t currentSize) {
    char* streamTmp = (char*)realloc(stream, (currentSize+CNBlockSize)*sizeof(char));
    if (streamTmp) {
        puts("Got an error in realloc!\nreader.c");
    }
}

// @!T function
// @!N readline
// @!I Reads a signle line of input from a file
// @!G Reader
// @!A file (fileptr)
// @!A stream (charptr)
// @!A streamLength (size_t)
// @!R int (-1 (EOF), 0 (Success), 1 (End of stream))
int readline(FILE* file, char* stream, size_t streamLen) {
    char buffer = ' ';
    size_t count = 0;
    char* index = stream;
    clearStream(stream, streamLen);
    int retVal = 0;
    // read through the file
    // stop at every newline, end of str, and end of file
    while ((buffer = fgetc(file)) != '\n' && 
           buffer != '\0' && 
           buffer != EOF &&
           streamLen-1 >= count) {
        *index = buffer;
        index++; count++;
    }
    if (streamLen-1 <= count) {
        retVal = 1;
    }
    *index = '\0';
    if (buffer == EOF) {
        return EOF;
    }
    return retVal;
}

void clearStream(char* stream, size_t len) {
    size_t count;
    char* index;
    for (index = stream, count = 0; count < len; index++, count++) {
        index = '\0';
    }
}
