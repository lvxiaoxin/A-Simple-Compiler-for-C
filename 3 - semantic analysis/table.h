#ifndef _TABLE_H_
#define _TABLE_H_
#define StructNode struct structNode
#define VarNode struct varNode
#define FuncNode struct funcNode
struct varNode {
	int type;
	char * name;
	int dimension;
	StructNode * structType;
	VarNode * next;
};
struct funcNode {
	int rtType;
	StructNode * rtStructType;
	char * funcName;
	VarNode * beginParam;
	int paramNum;
	FuncNode * next;
};
struct structNode {
	char * structName;
	VarNode * varList;
	StructNode * next;
};
void insertVarTable(int type, char * name, StructNode * _struct,int dimension);
VarNode * findVarTable(char * name);
StructNode * findStructTable(char * structName);
void insertStructTable(char * structName);
VarNode * findStructVar(char * name, char * structName);
void insertStructVar(int type,char * name,StructNode * _struct,int dimension,char * structName);
FuncNode * findFuncTable(char * funcName);
void insertFuncTable(char * funcName);
void insertFuncRtType(char * funcName,int rtType,StructNode * rtStructType);
void insertFuncParam(int type, char * name, StructNode * _struct,int dimension,char * funcName);
void printVarTable();
void printStructTable();
void printFuncTable();
#endif
