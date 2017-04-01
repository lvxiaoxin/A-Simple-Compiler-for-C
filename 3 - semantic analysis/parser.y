%{
	#include<stdio.h>
	#include"tree.h"
	#include"table.h"
	char * _structName = NULL;
	char * _funcName = NULL;
	void loginVar(TreeNode * decList){
		TreeNode * dec = decList->child;
		TreeNode * id = dec->child;
		int dimension = -1;
		while (id->child !=NULL){
			id = id->child;
			dimension = dimension +1;
		}
		if (findVarTable(id->text)!=NULL || findStructTable(id->text)!=NULL){
			printf("Error type 3 at Line %d: Redefined variable \"%s\".\n",id->lineno,id->text);
		}else{
			int type = -1;
			if (decList->_struct == NULL){
				type = decList->_type;
			} else{
				type = 3;
			}
			insertVarTable(type,id->text,decList->_struct,dimension);	
		} 
		if (dec->brother !=NULL && dec->brother->brother != NULL){
			dec->brother->brother->_type = decList->_type;
			dec->brother->brother->_struct = decList->_struct;
			loginVar(dec->brother->brother);
		}
	}

	 void loginVars(TreeNode * defList){
                TreeNode * def = defList->child;
                if ( def != NULL){
                        loginVar(def->child->brother);
			loginVars(def->brother);
                }
        }
	 void loginStructVar(TreeNode * decList,char * structName){
                TreeNode * dec = decList->child;
                TreeNode * id = dec->child;
                int dimension = -1;
                while (id->child !=NULL){
                        id = id->child;
                        dimension = dimension +1;
                }
                if (findStructVar(id->text,structName)!=NULL){
                        printf("Error type 15 at Line %d: Redefined variable \"%s\" in struct \"%s\".\n",id->lineno,id->text,structName);
                }else{
			int type = -1;
                        if (decList->_struct == NULL){
                                type = decList->_type;
                        } else{
                                type = 3;
                        }
                        insertStructVar(type,id->text,decList->_struct,dimension,structName);
                }
                if (dec->brother !=NULL && dec->brother->brother != NULL){
                        dec->brother->brother->_type = decList->_type;
                        loginStructVar(dec->brother->brother,structName);
                }
        }
         void loginStructVars(TreeNode * defList,char * structName){
                TreeNode * def = defList->child;
                if ( def != NULL){
                        loginStructVar(def->child->brother,structName);
                        loginStructVars(def->brother,structName);
                }
        }
	

	 void loginParamVar(TreeNode * varDec,char * funcName){
                TreeNode * id = varDec;
                int dimension = -1;
                while (id->child !=NULL){
                        id = id->child;
                        dimension = dimension +1;
                }
                if (findVarTable(id->text)!=NULL || findStructTable(id->text)!=NULL){
                        printf("Error type 3 at Line %d: Redefined variable \"%s\".\n",id->lineno,id->text);
                }else{
                        int type = -1;
                        if (varDec->_struct == NULL){
                                type = varDec->_type;
                        } else{
                                type = 3;
                        }
                        insertFuncParam(type,id->text,varDec->_struct,dimension,funcName);
                }
        }
	void loginParamVars(TreeNode * VarList,char * funcName){
		TreeNode * paramDec = VarList->child;
		if (paramDec != NULL){
			loginParamVar(paramDec->child->brother,funcName);
			if (paramDec->brother != NULL && paramDec->brother->brother != NULL){
				loginParamVars(paramDec->brother->brother,funcName);
			}
		}
	}
	void paramMatch(TreeNode * args,FuncNode * funcNode){
		int v=1;
		TreeNode * t = args->child;
		while (t->brother!=NULL){
			v++;
			t = t->brother->brother->child;
		}
		if (funcNode->paramNum!= v){
			printf("Error type 9 at Line %d: Params in function \"%s\" can't match.\n",args->lineno,funcNode->funcName);
		} else {
			VarNode * p = funcNode->beginParam;
			TreeNode * a = args;
			 while ( 1 == 1 ){
	                        TreeNode * exp = a->child;
                	        if (exp->_type != p-> type || exp->_struct != p->structType || exp->_dim != p->dimension){
                        	        printf("Error type 9 at Line %d: Params in function \"%s\" can't match.\n",exp->lineno,funcNode->funcName);
                        	}
				if (exp->brother == NULL){
					break;
				} else {
	                                a = exp->brother->brother;
        	                	p = p->next;
				}
                	}
		}
}
%}
%union{
	struct treenode * t;
}
%token <t>TYPE
%token <t>INT
%token <t> FLOAT 
%token <t>ID
%token <t>SEMI COMMA ASSIGNOP RELOP PLUS MINUS STAR DIV AND OR DOT NOT
%token <t>LP RP LB RB LC RC STRUCT RETURN IF ELSE WHILE

%type <t> ExtDefList ExtDef Specifier ExtDecList VarDec StructSpecifier OptTag Tag DefList Def FunDec VarList ParamDec CompSt StmtList Stmt Exp Args DecList Dec StructSpecifierBegin CompStBegin FuncBegin

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right UMINUS NOT
%left LP RP LB RB DOT 

%%
Program: ExtDefList {
//printf("Program (%d)\n",yylineno);
/*printtree($1,1);*/}
;
ExtDefList: { $$=newtreenode(NULL, yylineno, ""); }
| ExtDef ExtDefList {$$=newtree2($1,$2,"ExtDefList");}
;
ExtDef:Specifier ExtDecList SEMI {$$=newtree3($1,$2,$3,"ExtDef");}
|Specifier SEMI {$$=newtree2($1,$2,"ExtDef");}
|FuncBegin CompSt{$$=newtree2($1,$2,"ExtDef");}
;
FuncBegin: Specifier FunDec {$$=newtree2($1,$2,"FuncBegin");
                        insertFuncRtType($2->child->text,$1->_type,$2->_struct);
			_funcName = $2->child->text;
}
;
ExtDecList:VarDec {$$=newtree1($1,"ExtDecList");}
|VarDec COMMA ExtDecList {$$=newtree3($1,$2,$3,"ExtDecList");}
;
Specifier: TYPE {$$=newtree1($1,"Specifier");
			 $$->_type = $1->_type;}
|StructSpecifier {$$=newtree1($1,"Specifier");
		$$->_struct = $1->_struct;
		$$->_type = 2;}
;
StructSpecifier: StructSpecifierBegin DefList RC{$$=newtree3($1,$2,$3,"StructSpecifier");}
|STRUCT Tag {$$=newtree2($1,$2,"StructSpecifier");
	StructNode * _struct = findStructTable($2->child->text);
	if (_struct==NULL){
		printf("Error type 17 at Line %d: Undefined struct \"%s\".\n",$2->lineno,$2->child->text);
	}else {
		$$->_struct = _struct;
	}
}
;
StructSpecifierBegin: STRUCT OptTag LC {$$=newtree3($1,$2,$3,"StructSpecifierBegin");
	char * structName = $2->child->text;	
	if (findStructTable(structName)!=NULL || findVarTable(structName)!=NULL){
		printf("Error type 16 at Line %d: Redefined struct \"%s\".\n",$2->lineno,structName);
	} else {
		insertStructTable(structName);
		_structName = structName;
		//loginStructVars($4,structName);
		//printStructTable();
	}
}
;
OptTag: {$$=newtreenode(NULL,yylineno,"");}
|ID {$$=newtree1($1,"OptTag");}
;
Tag : ID {$$=newtree1($1,"Tag");}
;
VarDec: ID {$$=newtree1($1,"VarDec");}
|VarDec LB INT RB {$$=newtree4($1,$2,$3,$4,"VarDec");}
;
FunDec: ID LP VarList RP {$$=newtree4($1,$2,$3,$4,"FunDec");
	if (findFuncTable($1->text)!=NULL){
		printf("Error type 4 at Line %d: Redefined function \"%s\".\n",$1->lineno,$1->text);
	}else{
		insertFuncTable($1->text);
		loginParamVars($3,$1->text);
	}
}	
|ID LP RP {$$=newtree3($1,$2,$3,"FunDec");
	if (findFuncTable($1->text)!=NULL){
                printf("Error type 4 at Line %d: Redefined function \"%s\".\n",$1->lineno,$1->text);
        }else{
                insertFuncTable($1->text);
        }       
}
;
VarList: ParamDec COMMA VarList {$$=newtree3($1,$2,$3,"VarList");}
|ParamDec {$$=newtree1($1,"VarList");}
;
ParamDec: Specifier VarDec {$$=newtree2($1,$2,"ParamDec");
		$2->_type = $1->_type;
		$2->_struct = $1->_struct;
}
;
CompSt :CompStBegin DefList StmtList RC{$$=newtree4($1,$2,$3,$4,"CompSt");}
;
CompStBegin: LC  {$$=newtree1($1,"CompStBegin");
	_structName = NULL;}
;
StmtList :{$$=newtreenode(NULL,yylineno,"");}
|Stmt StmtList {$$=newtree2($1,$2,"StmtList");}
;
Stmt: Exp SEMI {$$=newtree2($1,$2,"Stmt");}
|CompSt {$$=newtree1($1,"Stmt");}
|RETURN Exp SEMI {$$=newtree3($1,$2,$3,"Stmt");
		if (_funcName== NULL){
			
		}else {
			FuncNode *f = findFuncTable(_funcName);
			if (f->rtType != $2->_type || f->rtStructType != $2->_struct){
				printf("Error type 8 at Line %d: Return value can't match.\n",$2->lineno);
			}
		}
}
|IF LP Exp RP Stmt %prec LOWER_THAN_ELSE{$$=newtree5($1,$2,$3,$4,$5,"Stmt");}
|IF LP Exp RP Stmt ELSE Stmt {$$=newtree7($1,$2,$3,$4,$5,$6,$7,"Stmt");}
|WHILE LP Exp RP Stmt {$$=newtree5($1,$2,$3,$4,$5,"Stmt");}
;
DefList:{$$=newtreenode(NULL,yylineno,"");}
|Def DefList {$$=newtree2($1,$2,"DefList");}
;
Def: Specifier DecList SEMI {$$=newtree3($1,$2,$3,"Def");
		$2->_type = $1->_type;
		$2->_struct = $1->_struct;
		 if (_structName == NULL){
                        loginVar($2);
                }else {
                        loginStructVar($2,_structName);
                }

}
;
DecList : Dec {$$=newtree1($1,"DecList");}
|Dec COMMA DecList {$$=newtree3($1,$2,$3,"DecList");}
;
Dec:VarDec {$$=newtree1($1,"Dec");}
|VarDec ASSIGNOP Exp {$$=newtree3($1,$2,$3,"Dec");}
;
Exp: Exp ASSIGNOP Exp {$$=newtree3($1,$2,$3,"Exp");
	     if ($1->_type == $3->_type && $1->_struct == $3->_struct && $1->_dim == $3->_dim){
		$$->_type = $1->_type;
		$$->_struct = $1->_struct;
		$$->_dim = $1->_dim;
	} else {
		printf("Error type 5 at Line %d: Symbol type left side of \"%s\" can't match the right side.\n",$2->lineno,$2->text);
	}
}
|Exp AND Exp {$$=newtree3($1,$2,$3,"Exp");}
|Exp PLUS Exp {$$=newtree3($1,$2,$3,"Exp");
	if ($1->_struct == NULL && $3->_struct==NULL && $1->_type == $3->_type  && $1->_dim == $3->_dim){
		$$->_type = $1->_type;
		$$->_dim = $1->_dim;
		$$->_struct = $1->_struct;
	} else {
		printf("Error type 7 at Line %d: Type can't match.\n",$2->lineno);
	}
}
|Exp OR Exp {$$=newtree3($1,$2,$3,"Exp");}
|Exp RELOP Exp {$$=newtree3($1,$2,$3,"Exp");}
|Exp MINUS Exp {$$=newtree3($1,$2,$3,"Exp");
		if ($1->_struct == NULL && $3->_struct==NULL && $1->_type == $3->_type  && $1->_dim == $3->_dim){
                $$->_type = $1->_type;
                $$->_dim = $1->_dim;
                $$->_struct = $1->_struct;
        } else {
                printf("Error type 7 at Line %d: Type can't match.\n",$2->lineno);
        }
}
|Exp STAR Exp {$$=newtree3($1,$2,$3,"Exp");
	if ($1->_struct == NULL && $3->_struct==NULL && $1->_type == $3->_type  && $1->_dim == $3->_dim){
                $$->_type = $1->_type;
                $$->_dim = $1->_dim;
                $$->_struct = $1->_struct;
        } else {
                printf("Error type 7 at Line %d: Type can't match.\n",$2->lineno);
        }
}
|Exp DIV Exp {$$=newtree3($1,$2,$3,"Exp");
	if ($1->_struct == NULL && $3->_struct==NULL && $1->_type == $3->_type  && $1->_dim == $3->_dim){
                $$->_type = $1->_type;
                $$->_dim = $1->_dim;
                $$->_struct = $1->_struct;
        } else {
                printf("Error type 7 at Line %d: Type can't match.\n",$2->lineno);
        }
}
|LP Exp RP {$$=newtree3($1,$2,$3,"Exp");}
|MINUS Exp %prec UMINUS {$$=newtree2($1,$2,"Exp");}
|NOT Exp {$$=newtree2($1,$2,"Exp");}
|ID LP Args RP {$$=newtree4($1,$2,$3,$4,"Exp");
	VarNode * v = findVarTable($1->text);
	FuncNode * f = findFuncTable($1->text);
	if (f== NULL && v!=NULL){
                printf("Error type 11 at Line %d: Can't use \"()\" at a Variable.\n",$1->lineno);
        } else if (f==NULL && v==NULL){
		printf("Error type 2 at Line %d: Undefined funcition \"%s\".\n",$1->lineno,$1->text);
	} else {
		paramMatch($3,f);
	}
}
|ID LP RP {$$=newtree3($1,$2,$3,"Exp");
	VarNode * v = findVarTable($1->text);
	FuncNode * f = findFuncTable($1->text);
	if (f== NULL && v!=NULL){
		printf("Error type 11 at Line %d: Can't use \"()\" at a Variable.\n",$1->lineno);
	} else if (f== NULL && v== NULL){
                printf("Error type 2 at Line %d: Undefined funcition \"%s\".\n",$1->lineno,$1->text);
        }else{
		if (f->beginParam!=NULL){
			printf("Error type 9 at Line %d: Params in function \"%s\" can't match.\n",$2->lineno,$1->text);
		}
	}

}
|Exp LB Exp RB {$$=newtree4($1,$2,$3,$4,"Exp");
		if ($3->_type != 0 || $3->_dim != 0){
			printf("Error type 12 at Line %d: number in \"[ ]\" is not an integer.\n",$3->lineno);
		} else {
			int dim = $1->_dim - 1;
			if (dim < 0){
				printf("Error type 10 at Line %d: Can't use \"[ ]\" at an not array symbol.\n",$1->lineno);
			}else {
				$$->_type = $1->_type;
				$$->_struct = $1->_struct;
				$$->_dim = dim;
			}		
		}
}
|Exp DOT ID {$$=newtree3($1,$2,$3,"Exp");
	if ($1->_struct == NULL){
		printf("Error type 13 at Line %d: Symbol before \".\" is not a struct.\n",$2->lineno);
	}else {
		VarNode * v = findStructVar($3->text,$1->_struct->structName);		if (v == NULL){
			printf("Error type 14 at Line %d: \"%s\" is undefined in the struct.\n",$3->lineno,$3->text);
		} else {
			$$->_type = v->type;
			$$->_struct = v->structType;
			$$->_dim = v->dimension;
		}	
	}
}
|ID {$$=newtree1($1,"Exp");
	VarNode *t =findVarTable($1->text);
	if (t==NULL){
		printf("Error type 1 at Line %d: Undefined variable \"%s\".\n",$1->lineno,$1->text);
	} else {
		$$->_type = t->type;
		$$->_struct = t->structType;
		$$->_dim = t->dimension;
	}
	//printVarTable();
}
|INT {$$=newtree1($1,"Exp");
	$$->_type = $1->_type;
	$$->_dim = 0;
	$$->_struct=NULL;}
|FLOAT {$$=newtree1($1,"Exp");
	$$->_type = $1->_type;
	$$->_struct = NULL;
	$$->_dim = 0;
}
;
Args: Exp COMMA Args {$$=newtree3($1,$2,$3,"Args");}
|Exp {$$=newtree1($1,"Args");}
;
%%
#include "lex.yy.c"
int main(int argc, int ** argv) {
	init();
	 if (argc > 1){
                if (!(yyin = fopen((const char *)argv[1],"r"))){
                        perror((const char *)argv[1]);
                        return 1;
                }
        }
	yyparse();
	return 0;
}
yyerror(char * msg){
	fprintf(stderr,"Error type B at Line %d: %s\n",yylineno,msg);
}
