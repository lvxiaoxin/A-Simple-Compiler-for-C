#! /bin/bash
# makefil
bison -d ./parser.y
flex ./scanner.l
gcc parser.tab.c tree.c table.c -lfl -ly -o parser

