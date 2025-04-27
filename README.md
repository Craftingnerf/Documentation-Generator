# Documentation Generator

A C program that I made to generate documentation from code comments <br>
Supports mutli-line and single-line comments for documentation generation <br>
I dont know if it has any vunerabilities or memory leaks <br>
if it does, open an issue and I'll see if I can find it. <br>
I made this on Windows and the only debugging I found that was easy enough to use was gdb (I'm using VS Code not VS Community) <br>

## Example of program output
[exampleLog.txt](log.txt)

## How to use
The documentation comments are denoted by first, being a comment (who would have guessed!) <br>
The primary thing that seperates documentation comments from other comments is the initialiser `@!` in the comment <br>
Immediatly following the initialiser you need a type specifier <br>
Currently there are 8 types
```
Type              'T'
Name              'N'
Misc Info         'I'
Group             'G'
Function argument 'A'
Return type       'R'
helper function   'F'
Date              'D'
```
For each section of comments you need a type tag <br>
An example of a file comment is the following
```
// @!T File
// @!N main.c
// @!I Some misc information about the file
// @!G Grouping for the file (will be used once writing to files is done)
// @!D 21/04/2025 (date)
```
Some of the tags only allow for one entry <br>
A list of single string tags are the following 
```
Type              'T'
Name              'N'
Group             'G'
Return type       'R'
Date              'D'
```
Alternitively the other three tag specifiers are lists of strings allowing for several lines for each documentation entry
```
Misc Info         'I'
Function argument 'A'
helper function   'F'
```
At the moment none of the tags have default values if left blank <br>
I would like to get the group tag to default to default to either the first in the file, the most recent grouping, or the first file type in the file <br>
At the moment the C program just prints out the documentation to the console like the following blurb (with minor debugging)
```
0 - main.c

Opening file : main.c

Name : main.c
Type : File
Group : Main
Date : 21/04/2025
Misc Info :
        - main program file

Name : Main
Type : Main Function
Group : Main
Misc Info :
        - parses arguments
        - sends files to be parsed in parser.c
        - prints out the files once parsed
        - should clean up aswell

Name : parseArgs
Type : Function
Group : Main
Misc Info :
        - Function for parsing arguments
        - Responsible for getting switches and file names/paths
Argument list :
        Arg 1 : int argc (amount of arguments)
        Arg 2 : char** argv (2D array of chars for each word in the command)

Name : argFindr
Type : Function
Group : Main
Misc Info :
        - Function to find a single char in a string
        - Created for the argParser function
Argument list :
        Arg 1 : 'string' to search
        Arg 2 : character to look for

Name : findArgString
Type : Function
Group : Main
Misc Info :
        - Finds a string within another string
        - Created for the argParser function
Argument list :
        Arg 1 : char* (string) to look in
        Arg 2 : char* to search for
```
At the moment you can run `docGen.exe <filename> ...` with as many filenames/filepaths as you want (although I haven't tried using filepaths) <br>
There is support for switches and help info statements, but I havent implemented those yet (probably once I get different output types out such as .md or .html)
