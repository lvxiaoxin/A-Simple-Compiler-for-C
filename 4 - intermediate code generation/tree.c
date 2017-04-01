#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
struct treenode * newtree1(struct treenode * t1, char * type){
	//printf("newtree1: %s\n",t1->type);
	TreeNode * t = malloc(sizeof(TreeNode));
        t->child = t1;
	t->brother = NULL;
	t->type = type;
	t->lineno = yylineno;
        return t;
}
struct treenode * newtree2(struct treenode * t1, struct treenode * t2, char * type){
	//printf("newtree2:%s,%s\n",t1->type,t2->type);
	TreeNode * t = malloc(sizeof(TreeNode));
        t->child = t1;
	t->brother = NULL;
        t1->brother = t2;
	t->type = type;
	t->lineno = yylineno;
        return t;
}
struct treenode * newtree3(struct treenode * t1, struct treenode * t2, struct treenode * t3,char * type){
//	printf("newtree3:%s,%s,%s\n",t1->type,t2->type,t3->type);
	TreeNode * t = malloc(sizeof(TreeNode));
        t->child = t1;
	t->brother = NULL;
        t1->brother = t2;
        t2->brother = t3;
	t->type = type;
	t->lineno = yylineno;
        return t;
}
struct treenode * newtree4(struct treenode * t1,struct treenode * t2,struct treenode * t3, struct treenode * t4,char * type){
//	printf("newtree4:%s,%s,%s,%s\n",t1->type,t2->type,t3->type,t4->type);
	TreeNode * t = malloc(sizeof(TreeNode));
        t->child = t1;
	t->brother = NULL;
        t1->brother = t2;
        t2->brother = t3;
	t3->brother = t4;
	t->type = type;
	t->lineno = yylineno;
        return t;
}
struct treenode * newtree5(struct treenode * t1,struct treenode * t2,struct treenode * t3, struct treenode * t4,struct treenode * t5,char * type){
  //      printf("newtree5:%s,%s,%s,%s\n",t1->type,t2->type,t3->type,t4->type);
        TreeNode * t = malloc(sizeof(TreeNode));
        t->child = t1;
        t->brother = NULL;
        t1->brother = t2;
        t2->brother = t3;
        t3->brother = t4;
	t4->brother = t5;
        t->type = type;
        t->lineno = yylineno;
        return t;
}
struct treenode * newtree7(struct treenode * t1,struct treenode * t2,struct treenode * t3, struct treenode * t4,struct treenode * t5,struct treenode * t6,struct treenode * t7,char * type){
    //    printf("newtree6:%s,%s,%s,%s\n",t1->type,t2->type,t3->type,t4->type);
        TreeNode * t = malloc(sizeof(TreeNode));
        t->child = t1;
        t->brother = NULL;
        t1->brother = t2;
        t2->brother = t3;
        t3->brother = t4;
	t4->brother = t5;
	t5->brother = t6;
	t6->brother = t7;
        t->type = type;
        t->lineno = yylineno;
        return t;
}
struct treenode * newtreenode(char * type,int lineno,char * text) {
	TreeNode * t = malloc(sizeof(TreeNode));
	t->type = type;
	t->child = NULL;
	t->brother = NULL;
	t->lineno = lineno;
	t->text = text;
	return t; 
}
void printtree(struct treenode * t,int tabnum){
	int i;
	if (t->type != NULL){
		for (i=0; i<tabnum; i++){
   	             printf("  ");
        	}
		if (strcmp(t->type,"ID")==0 || strcmp(t->type,"INT")==0 || strcmp(t->type,"HEX")==0 || strcmp(t->type,"OCT") == 0 || strcmp(t->type,"SCIENNUM")==0){
			printf("%s (%d) %s\n",t->type,t->lineno,t->text);
		} else {
        	printf("%s (%d)\n",t->type,t->lineno);
		}
	}	
	if (t->child != NULL) {
		printtree(t->child,tabnum+1);
	}
	if (t->brother != NULL){
		printtree(t->brother,tabnum);
	}
}
