@echo off
gcc -Wall -Werror ./main.c ./parser.c ./reader.c ./strList.c ./dataList.c ./filegen.c -o docGen.exe