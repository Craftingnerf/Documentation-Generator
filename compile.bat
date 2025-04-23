@echo off
gcc -Wall -Werror -g  ./main.c ./parser.c ./reader.c ./strList.c -o docGen.exe