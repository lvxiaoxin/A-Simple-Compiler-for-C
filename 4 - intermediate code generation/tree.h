#ifndef _tree_h_
#define _tree_h_
extern int yylineno;
#include "table.h"
#define TreeNode struct treenode
struct treenode {
	struct treenode * brother;
	struct treenode * child;
	char * type;
	int lineno;
	char * text;
	int  _type;
	StructNode * _struct;
	int _dim;
	char _vt;
	int _place;
	int _label;
};
struct treenode * newtree1(struct treenode * t1, char * type);
struct treenode * newtree2(struct treenode * t1, struct treenode * t2, char * type);
struct treenode * newtree3(struct treenode * t1, struct treenode * t2, struct treenode * t3,char * type);
struct treenode * newtree4(struct treenode * t1,struct treenode * t2,struct treenode * t3, struct treenode * t4,char * type);
struct treenode * newtree5(struct treenode * t1,struct treenode * t2,struct treenode * t3, struct treenode * t4,struct treenode * t5,char * type);
struct treenode * newtree7(struct treenode * t1,struct treenode * t2,struct treenode * t3, struct treenode * t4,struct treenode * t5,struct treenode * t6,struct treenode * t7,char * type);
struct treenode * newtreenode(char * type,int lineno,char * text);
void printtree(struct treenode * t,int tabnum);
#endif
