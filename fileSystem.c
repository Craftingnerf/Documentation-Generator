// @!T File
// @!N fileSystem.c
// @!I A bunch of filesystem functions (i.e. making dirs that are platform independent (kinda))
// @!G Helper/Filesystem
// @!D 23/04/2025
#include "main.h"


// @!T function
// @!N makeDirectory
// @!I Creates a directory using the specific function for linux or Windows (IDK I got it on stack overflow)
// @!G Helper/Filesystem
// @!A directory name (const char*)
// @!R void
void makeDirectory(const char* name) {
    #ifdef __linux__
        mkdir(name, 777); 
    #else
        _mkdir(name);
    #endif
}