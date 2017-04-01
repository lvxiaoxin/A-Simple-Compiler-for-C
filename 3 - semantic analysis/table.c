#include <stdio.h>
#include <stdlib.h>
#include "table.h"
VarNode * varTable;
VarNode * varP;
StructNode * structTable;
StructNode * structP;
FuncNode * funcTable;
FuncNode * funcP;
const int INT = 0;
const int FLOAT = 1;
const int STRUCT = 3;

void init(){
	varTable = malloc(sizeof(VarNode));
	varTable->name = NULL;
	varP = varTable;
	structTable = malloc(sizeof(StructNode));
	structP = structTable;
	funcTable = malloc(sizeof(FuncNode));	
	funcP = funcTable;
}

int string2type(char * cType){
	if (strcmp(cType,"INT")) return INT;
	if (strcmp(cType,"FLOAT")) return FLOAT;
	if (strcmp(cType,"STRUCT")) return STRUCT;
	return -1; 		
}

VarNode * findVarTable(char * name){
	VarNode * p = varTable->next;
	while (p != NULL && strcmp(p->name,name)!=0){
		p = p->next;
	}
	if (p==varTable){
		return NULL;
	}
	return p;
}
void insertVarTable(int type, char * name, StructNode * _struct, int dimension) {
	VarNode * tmp = malloc(sizeof(VarNode));
	StructNode * s =NULL;
	tmp->next = NULL;
	tmp->dimension = dimension;
	tmp->name = name;
	tmp->type = type;
	tmp->structType = _struct;
	varP->next = tmp;
	varP = tmp;
}
StructNode * findStructTable(char * structName){
	StructNode * p = structTable->next;
        while (p != NULL && strcmp(p->structName,structName)!=0){
                p = p->next;
        }
	if  (p == structTable ){
		return NULL;
	}
        return p;

}
VarNode * findStructVar(char * name,char * structName){
	StructNode * s = findStructTable(structName);
	if (s != NULL){
		VarNode * p = s->varList->next;
		while (p!=NULL && strcmp(p->name,name)!=0){
			p = p->next;
		}
		return p;
	}
	return NULL;
}
void insertStructTable(char * structName){
	StructNode * tmp = malloc(sizeof(StructNode));
	tmp->structName = structName;
	tmp->varList = malloc(sizeof(VarNode));
	structP->next = tmp;
	structP = tmp;
}
void insertStructVar(int type,char * name,StructNode * _struct,int dimension,char * structName){
	StructNode *s =findStructTable(structName);
	VarNode * p = s->varList;
	while (p->next != NULL){
		p=p->next;
	}
	VarNode * tmp  = malloc(sizeof(VarNode));
	tmp->type = type;
	tmp->name = name;
	tmp->structType = _struct;
	tmp->dimension = dimension;
	p->next = tmp;
}
FuncNode * findFuncTable(char * funcName){
        FuncNode * p = funcTable->next;
        while (p != NULL && strcmp(p->funcName,funcName)!=0){
                p = p->next;
        }
        if  (p == funcTable ){
                return NULL;
        }
        return p;

}
void insertFuncTable(char * funcName){
       	FuncNode * tmp = malloc(sizeof(FuncNode));
        tmp->funcName = funcName;
        funcP->next = tmp;
        funcP = tmp;
}
void insertFuncParam(int type, char * name, StructNode * _struct,int dimension,char * funcName){
	VarNode * tmp = malloc(sizeof(VarNode));
        StructNode * s =NULL;
        tmp->next = NULL;
        tmp->dimension = dimension;
        tmp->name = name;
        tmp->type = type;
        tmp->structType = _struct;
        varP->next = tmp;
        varP = tmp;
	FuncNode * f = findFuncTable(funcName);
	if (f->beginParam == NULL){
		f->beginParam = tmp;
	}
	f->paramNum++;	
}
void insertFuncRtType(char * funcName,int rtType,StructNode * rtStructType) {
	FuncNode * f = findFuncTable(funcName);
	if (f!=NULL){
		f->rtType = rtType;
		f->rtStructType = rtStructType;
	}
}
void printVarTable(){
	VarNode * p = varTable->next;
	while (p!=NULL){
		printf("%s  %d  %d\n",p->name,p->type,p->dimension);
		p= p->next;
	}
}
void printStructTable(){
	StructNode * s = structTable->next;
	while (s!=NULL){
		printf("Struct: %s  \n",s->structName);
		VarNode * p = s->varList->next;
		while (p!=NULL){
			printf("\t%s  %d  %d\n",p->name,p->type,p->dimension);
			p=p->next;
		}
	 	s= s->next;
	}
}
void printFuncTable(){
	FuncNode * p = funcTable->next;
        while (p!=NULL){
                printf("%s  \n",p->funcName);
                p= p->next;
        }
}
