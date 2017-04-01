#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

struct Ast {
    char *type;
    char *val;
    struct Ast *firstChild;
    struct Ast *nextSibling;
};

struct Ast *newAst(char *type, char *val, unsigned count, ...);

void printAst(struct Ast* node, unsigned depth);
void freeAst(struct Ast* node);

#endif
