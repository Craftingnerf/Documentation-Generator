// @!T File
// @!N Reader.c
// @!I Reader file
// @!G Reader
// @!D 21/04/2025
#include "main.h"

#define CNBlockSize 128
#define CNExtendSize 64

void clearStream(char* buffer, usize_t len);


// @!T Function
// @!N extendBlock
// @!G Reader
// @!A char** | pointer to the string/buffer to resize
// @!A usize_t* | pointer to the size of the buffer
// @!A usize_t | size it will extend the buffer by
// @!R void
void extendBlock(char** buffer, usize_t* currentSize, usize_t extendBy) {
    // validating data passed
    if (!buffer || !*buffer || !currentSize)  {
        printf("Something was null in the extend block call!\n");
        return;
    }
    if (SIZE_MAX - *currentSize < extendBy) {
        printf("Attempting to extend by too much!\n");
        return;
    }
    usize_t newSize = ((*currentSize)+extendBy)*sizeof(char);
    char* bufferTmp = realloc((*buffer), newSize);
    // error checking
    if (bufferTmp == NULL) {
        puts("Got an error in realloc!\nreader.c");
        return;
    }
    
    *buffer = bufferTmp;
    *currentSize = newSize;
    
}

// @!T function
// @!N readline
// @!I Reads a signle line of input from a file
// @!G Reader
// @!A file (fileptr)
// @!A buffer (char**)
// @!A bufferLength (usize_t*)
// @!R int (-1 (EOF), 0 (Success)
int getLine(FILE* file, char** buffer, usize_t* bufferSize) {
    // if the file is NULL return end of file (it doesnt exist)
    if (file == NULL) return EOF;
    // comment of shame
    // this comment causes a memory corruption bug
    // it filled in string[size] which went over by one
    // // clearStream(*buffer, *bufferSize);

    // variable initialization
    int charRead = 0;
    usize_t charsRead = 0;

    // readloop
    // if its a newline, string terminator, or end of file ...
    //    we dont want to continue
    while ((charRead = fgetc(file)) != EOF &&
            charRead != '\n' &&
            charRead != '\0') {
        // if the buffer is full (or almost full)
        // extend it (and update the values)
        // this is why pointers are great :)
        if ((*bufferSize)-2 <= charsRead) {
            // extend the buffer
            // printf("Extending the buffer!\n");
            extendBlock(buffer, bufferSize, CNExtendSize);
            // printf("Buffer extended?\n");
        }
        // set the character in the buffer to the new character
        (*buffer)[charsRead++] = charRead;
        // update the next character with a null terminator
        // could nove this just outside with the same effect, but this is safer I think
        (*buffer)[charsRead] = '\0';
        
    }
    // if we read a newline immediatly we return an empty string
    if (charRead == '\n' && charsRead == 0) {
        // go to the string and set the first character to '\0'
        // this is equal to "*buffer[0] = '\0';"
        **buffer = '\0';
    }
    // (*buffer)[charsRead] = '\0';
    // if we read the EOF return EOF
    if (charRead == EOF) {
        return EOF;
    }
    // return 0 :D
    return charsRead;
}

