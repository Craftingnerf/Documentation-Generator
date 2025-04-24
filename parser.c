// @!T File
// @!N parser.c
// @!I Line parsing file
// @!G Parser
// @!D 21/04/2025
#include "main.h"

#define LineLength 64
#define CNExtendSize 64
int lineContainsComment(char* line, size_t lineLen, int multilineFlag);
int isDocComment(char* line, size_t lineLen, char** tagTypePtr);
struct dataList* parseFile(struct strList* fileList);
size_t generateStringFromComment(char* lineStartPos, char** string, size_t* size);
int allocateListString(char** string, size_t* size, char* startPtr);

// @!T Function
// @!N parseFile
// @!G Parser
// @!A strList* list of file names/paths
// @!R dataList* list of documentation data
// @!I Reads through a file and generates documentation in a struct
// @!I heavy lifter and current headache for this program :D
struct dataList* parseFile(struct strList* fileList) {
    FILE* filePtr = fopen(fileList->str, "r");
    if (filePtr == NULL) {
        printf("Error opening file");
        return NULL;
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
        return NULL;
    }
    size_t lineNo = 0;
    int strLen = 0;
    int mutliLineComment = 0;
    int lastCommentReturn = 0;
    char* tagTypePtr;
    printf("Opening file : %s\n", fileList->str);
    struct strList* newItem;
    struct dataList* listPtr = genDataElement();
    struct dataList* startPtr = listPtr;
    while (1) {
        /* would put this in the while loop. 
         * However, then I cant read the last line of the file 
         * (getline will return EOF)
         * Need to have the assignment in the while loop and use a break at the end of the loop
         */ 
        lineNo++;
        strLen = getLine(filePtr, line, lineSize);
        // do what we need to do with the line
        if ((lastCommentReturn = lineContainsComment(*line, strLen, mutliLineComment)) && isDocComment(*line, strLen, &tagTypePtr)) {
            if (lastCommentReturn > 1) {
                mutliLineComment = 1;
            } else if (mutliLineComment) {
                mutliLineComment = 0;
            }
            size_t strSize = LineLength;
            switch (*tagTypePtr) {
                case TypeTag:
                    // reset the size of the string
                    strSize = LineLength;
                    // add a new element to the list (of documentation)
                    listPtr = addToDataList(listPtr, genDataElement());
                    // allocate and fill in the type for the new list element
                    if (allocateListString(&(listPtr->this.type), 
                    &strSize, tagTypePtr+1)) {
                        // destroy everything and return
                        printf("Error while allocating string for documentation!");
                        destroyDataList(listPtr);
                        free(line);
                        free(lineSize); 
                        fclose(filePtr);
                        return NULL;
                    }
                    break;

                case NameTag:
                    // reset the size of the string
                    strSize = LineLength;
                    // allocate and fill the name string pointer
                    if (allocateListString(&(listPtr->this.name), 
                    &strSize, tagTypePtr+1)) {
                        // destroy everything and return
                        printf("Error while allocating string for documentation!");
                        destroyDataList(listPtr);
                        free(line);
                        free(lineSize); 
                        fclose(filePtr);
                        return NULL;
                    }
                    // printf("added \"%s\" to name\n", list->this.name);
                    break;

                case InfoTag:
                    // reset the size of the string
                    strSize = LineLength;
                    // generate the new list element
                    newItem = genStrElement(NULL);
                    // allocate and fill the string in the list element
                    if (allocateListString(&(newItem->str), 
                    &strSize, tagTypePtr+1)) {
                        // destroy everything and return
                        printf("Error while allocating string for documentation!");
                        destroyDataList(listPtr);
                        free(line);
                        free(lineSize); 
                        fclose(filePtr);
                        return NULL;
                    }
                    // check to see if there is already an item in the list
                    // if not we set this item to the front of the list
                    // otherwise we add it
                    if (listPtr->this.miscList == NULL) {
                        newItem->next = NULL;
                        listPtr->this.miscList = newItem;
                    } else {
                        addToStrList(listPtr->this.miscList, newItem);
                    }
                    break;

                case GroupTag:
                    // reset the size of the string
                    strSize = LineLength;
                    // allocate and fill in the group item
                    if (allocateListString(&(listPtr->this.group), 
                    &strSize, tagTypePtr+1)) {
                        // destroy everything and return
                        printf("Error while allocating string for documentation!");
                        destroyDataList(listPtr);
                        free(line);
                        free(lineSize); 
                        fclose(filePtr);
                        return NULL;
                    }
                    break;

                case ArgTag:
                    // reset the size of the string
                    strSize = LineLength;
                    // generate/allocate a new list element
                    newItem = genStrElement(NULL);
                    // allocate the string of the list element
                    // and fill it in with needed data
                    if (allocateListString(&(newItem->str), 
                    &strSize, tagTypePtr+1)) {
                        // destroy everything and return
                        printf("Error while allocating string for documentation!");
                        destroyDataList(listPtr);
                        free(line);
                        free(lineSize); 
                        fclose(filePtr);
                        return NULL;
                    }
                    // check to see if there is already an item in the list
                    // if not we set this item to the front of the list
                    // otherwise we add it
                    if (listPtr->this.argList == NULL) {
                        newItem->next = NULL;
                        listPtr->this.argList = newItem;
                    } else {
                        addToStrList(listPtr->this.argList, newItem);
                    }
                    break;
                    
                case ReturnTag:
                    // reset the string size
                    strSize = LineLength;
                    // allocate and fill in the string 
                    if (allocateListString(&(listPtr->this.retType), 
                    &strSize, tagTypePtr+1)) {
                        // destroy everything and return
                        printf("Error while allocating string for documentation!");
                        destroyDataList(listPtr);
                        free(line);
                        free(lineSize); 
                        fclose(filePtr);
                        return NULL;
                    }
                    break;

                case HelpFuncTag:
                    // reset the str length 
                    strSize = LineLength;
                    // create the new list element
                    newItem = genStrElement(NULL);
                    // allocate the list element and fill it
                    if (allocateListString(&(newItem->str), 
                    &strSize, tagTypePtr+1)) {
                        // destroy everything and return
                        printf("Error while allocating string for documentation!");
                        destroyDataList(listPtr);
                        free(line);
                        free(lineSize); 
                        fclose(filePtr);
                        return NULL;
                    }
                    // check to see if there is already an item in the list
                    // if not we set this item to the front of the list
                    // otherwise we add it
                    if (listPtr->this.helprList == NULL) {
                        newItem->next = NULL;
                        listPtr->this.helprList = newItem;
                    } else {
                        addToStrList(listPtr->this.helprList, newItem);
                    }
                    break;

                case DateTag:
                    // reset the length
                    strSize = LineLength;
                    // allocate the new string and fill it with the comment
                    if (allocateListString(&(listPtr->this.date), 
                    &strSize, tagTypePtr+1)) {
                        // destroy everything and return
                        printf("Error while allocating string for documentation!");
                        destroyDataList(listPtr);
                        free(line);
                        free(lineSize); 
                        fclose(filePtr);
                        return NULL;
                    }
                    break;
            }
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
    return startPtr;
}

// @!T Function
// @!N lineContainsComment
// @!G Parser
// @!I figures out if the current line contains a comment
// @!R int (1 or 0) (treat as bool)
// @!A char* | current line
// @!A size_t | line length
// @!A int | flag for if the last line was a multiline comment with no terminator
int lineContainsComment
    (char* line, size_t lineLen, int multilineFlag) {
    if (lineLen < 2) {
        return 0; // cant have a comment with less than two characters
    }
    char* linePtr = line;
    int lastSlashFlag = 0;
    int multilineEndFlag = 0;
    for (int count = 0; count < lineLen && *linePtr != '\0'; 
            count++, linePtr++) {
        // if there is a // or a /* then there is a comment on this line
        // if there is a /* then there is a multiline comment and we need to return 2 for a multiline flag to be set
        
        if (*linePtr == '/') {
            // do / checks
            if (lastSlashFlag && !multilineFlag) {
                // printf("double slash comment | ");
                return 1;
            } else if (multilineFlag && multilineEndFlag) {
                multilineFlag = 0;
                // printf("multiline end | ");
                return 1;
            } else {
                lastSlashFlag = 1;
            }
        } else if (*linePtr == '*') {
            // do * checks
            if (lastSlashFlag && !multilineFlag) {
                // need to check for an end still
                // printf("multiline begin | ");
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

// @!T Function
// @!N isDocComment
// @!G Parser
// @!A char* | current line
// @!A size_t | length of the line
// @!A tagTypePointer | pointer to the tagType pointer to be used for later
// @!R int (1 or 0) treat as bool
// @!I Looks for if the current comment has a documentation initialisor
// @!I changes the char* of the tagTypePtr passed in to the char after the tag is found (the type)
int isDocComment(char* line, size_t lineLen, char** tagTypePtr) {
    char* tagStr = TagInitiator;
    char* tagStrPtr = tagStr;
    for (int i = 0; i < lineLen && *(line+i) != '\0'; i++) {
        
        if (*tagStrPtr == '\0') {
            *tagTypePtr = (line+i);
            return 1;
        } else if (*(line+i) == *tagStrPtr) {
            tagStrPtr++;
        } else {
            tagStrPtr = tagStr;
        }
        
    }
    return 0;
}

// @!T Function
// @!N generateStringFromComment
// @!G Parser
// @!A char* | current line
// @!A char** | pointer to string to change
// @!A size_t* | size of the string we change
// @!R size_t | characters added
// @!I Loops through the current line (from the starting point given)
// @!I It adds each character to the string and if there isnt enough room, we extend the string by allocating more characters to the array
size_t generateStringFromComment(char* lineStartPos, char** string, size_t* size) {
    char ch;
    int charsRead = 0;
    int count = 0;
    int removeLeadingWhitespace = 1;
    while ((ch = *(lineStartPos+(count++))) != '\0') {
        if ((*size)-2 <= charsRead) {
            // extend string
            // printf("Extending the buffer!\n");
            extendBlock(string, size, CNExtendSize);
        }
        if (removeLeadingWhitespace && (ch == ' ' || ch == '\t')) {
            continue;
        }
        removeLeadingWhitespace = 0;
        (*string)[charsRead++] = ch;
        
        (*string)[charsRead] = '\0';
    }
    return charsRead;
}

// @!T Function
// @!N allocateListString
// @!G Parser
// @!A char** | pointer to string to allocate and fill
// @!A size_t* | pointer to the size of the string
// @!A char* | fill starting point
// @!R int | if its a non-zero return we throw a tantrum :D
// @!I Allocates space for the string location given to us.
// @!I Fills in the string at the specified location
int allocateListString(char** string, size_t* size, char* startPtr) {
    *string = malloc((*size)*sizeof(char));
    if (*string == NULL) {
        return 1;
    }
    // generate the string (should size the str)
    generateStringFromComment(startPtr, string, size);
    return 0;
}