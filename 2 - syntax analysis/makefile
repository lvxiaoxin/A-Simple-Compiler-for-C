make:
	bison -d parser.y
	flex scanner.l
	gcc parser.tab.c tree.c -lfl -ly -o parser
