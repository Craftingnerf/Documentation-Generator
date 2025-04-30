#!/bin/bash
gdb -x gdbCmd.txt --batch docGen
valgrind --leak-check=full -s ./docGen -o ./output/ ./main.c ./main.h ./dataList.c ./filegen.c ./parser.c ./reader.c ./strList.c

