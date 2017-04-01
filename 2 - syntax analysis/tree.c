#include "ast.h"

struct Ast *newAst(char *type, char *text, unsigned count, ...) {
    va_list args;
    va_start(args, count);

    char *val = NULL;
    if (text) {
        val = (char *)malloc(strlen(text));
        strcpy(val, text);
    }

    struct Ast *node = (struct Ast *)malloc(sizeof(struct Ast));
    if (NULL == node) {
        exit(1);
    }
    node->type = type;
    node->val = val;
    node->nextSibling = NULL;
    if (count) {
        struct Ast * pNode = node->firstChild = va_arg(args, struct Ast*);
        for(int i = 1; i < count; ++i) {
            pNode = pNode->nextSibling = va_arg(args, struct Ast*);
        }
        pNode->nextSibling = NULL;
    } else {
        node->firstChild = NULL;
    }

    va_end (args);
    return node;
}

void printTabs(unsigned depth) {
    while (depth--) {
        printf("\t");
    }
}

void printAst(struct Ast* node, unsigned depth) {
    printTabs(depth);
    if (node->val) {
        printf("%s: %s\n", node->type, node->val);
    } else {
        printf("%s\n", node->type);
    }
    struct Ast *pNode = node->firstChild;
    while (pNode) {
        printAst(pNode, depth + 1);
        pNode = pNode->nextSibling;
    }
}

void freeAst(struct Ast* node) {
    free(node->val);
    if (node->firstChild) {
        freeAst(node->firstChild);
    }
    if (node->nextSibling) {
        freeAst(node->nextSibling);
    }
}
