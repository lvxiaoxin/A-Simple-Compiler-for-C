%{
	#include<stdio.h>
	#include"tree.h"
%}

//union 符号值
%union{
	struct ast * t;
}

//终结符
%token <t>TYPE
%token <t>INT
%token <t> FLOAT
%token <t>ID
%token <t>SEMI COMMA ASSIGNOP RELOP PLUS MINUS STAR DIV AND OR DOT NOT
%token <t>LP RP LB RB LC RC STRUCT RETURN IF ELSE WHILE

%type <t> ExtDefList ExtDef Specifier ExtDecList VarDec StructSpecifier OptTag Tag DefList Def FunDec VarList ParamDec CompSt StmtList Stmt Exp Args DecList Dec

//优先级
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
//High level definition
Program:
				ExtDefList { printf("Program (%d)\n",yylineno); printtree($1,1); }
				;
ExtDefList:
				{ $$=newtreenode(NULL, yylineno, ""); }
				| ExtDef ExtDefList {$$=newtree2($1,$2,"ExtDefList");}
				;
ExtDef:
				Specifier ExtDecList SEMI {$$=newtree3($1,$2,$3,"ExtDef");}
			  |Specifier SEMI {$$=newtree2($1,$2,"ExtDef");}
				|Specifier FunDec CompSt {$$=newtree3($1,$2,$3,"ExtDef");}
				;
ExtDecList:
				VarDec {$$=newtree1($1,"ExtDecList");}
				|VarDec COMMA ExtDecList {$$=newtree3($1,$2,$3,"ExtDecList");}
				;

//Specifier
Specifier:
 				TYPE {$$=newtree1($1,"Specifier");}
				|StructSpecifier {$$=newtree1($1,"Specifier");}
				;
StructSpecifier:
				STRUCT OptTag LC DefList RC {$$=newtree5($1,$2,$3,$4,$5,"StructSpecifier");}
				|STRUCT Tag {$$=newtree2($1,$2,"StructSpecifier");}
				;
OptTag:
				{$$=newtreenode(NULL,yylineno,"");}
				|ID {$$=newtree1($1,"OptTag");}
				;
Tag :
				ID {$$=newtree1($1,"Tag");}
				;

// Declarator
VarDec:
				ID {$$=newtree1($1,"VarDec");}
				|VarDec LB INT RB {$$=newtree4($1,$2,$3,$4,"VarDec");}
				;
FunDec:
				ID LP VarList RP {$$=newtree4($1,$2,$3,$4,"FunDec");}
				|ID LP RP {$$=newtree3($1,$2,$3,"FunDec");}
				;
VarList:
				ParamDec COMMA VarList {$$=newtree3($1,$2,$3,"VarList");}
			  |ParamDec {$$=newtree1($1,"VarList");}
				;
ParamDec:
				Specifier VarDec {$$=newtree2($1,$2,"ParamDec");}
				;

//Statement
CompSt :
				LC DefList StmtList RC {$$=newtree4($1,$2,$3,$4,"CompSt");}
				;
StmtList :
				{$$=newtreenode(NULL,yylineno,"");}
				|Stmt StmtList {$$=newtree2($1,$2,"StmtList");}
				;
Stmt:
				Exp SEMI {$$=newtree2($1,$2,"Stmt");}
				|CompSt {$$=newtree1($1,"Stmt");}
				|RETURN Exp SEMI {$$=newtree3($1,$2,$3,"Stmt");}
				|IF LP Exp RP Stmt %prec LOWER_THAN_ELSE{$$=newtree5($1,$2,$3,$4,$5,"Stmt");}
				|IF LP Exp RP Stmt ELSE Stmt {$$=newtree7($1,$2,$3,$4,$5,$6,$7,"Stmt");}
				|WHILE LP Exp RP Stmt {$$=newtree5($1,$2,$3,$4,$5,"Stmt");}
				;

//local definition
DefList:
				{$$=newtreenode(NULL,yylineno,"");}
				|Def DefList {$$=newtree2($1,$2,"DefList");}
				;
Def:
				Specifier DecList SEMI {$$=newtree3($1,$2,$3,"Def");}
				;
DecList :
				Dec {$$=newtree1($1,"DecList");}
				|Dec COMMA DecList {$$=newtree3($1,$2,$3,"DecList");}
				;
Dec :
				VarDec {$$=newtree1($1,"Dec");}
				|VarDec ASSIGNOP Exp {$$=newtree3($1,$2,$3,"Dec");}
				;

//expression
Exp:
				Exp ASSIGNOP Exp {$$=newtree3($1,$2,$3,"Exp");}
				|Exp AND Exp {$$=newtree3($1,$2,$3,"Exp");}
				|Exp PLUS Exp {$$=newtree3($1,$2,$3,"Exp");}
				|Exp OR Exp {$$=newtree3($1,$2,$3,"Exp");}
				|Exp RELOP Exp {$$=newtree3($1,$2,$3,"Exp");}
				|Exp MINUS Exp {$$=newtree3($1,$2,$3,"Exp");}
				|Exp STAR Exp {$$=newtree3($1,$2,$3,"Exp");}
				|Exp DIV Exp {$$=newtree3($1,$2,$3,"Exp");}
				|LP Exp RP {$$=newtree3($1,$2,$3,"Exp");}
				|MINUS Exp %prec UMINUS {$$=newtree2($1,$2,"Exp");}
				|NOT Exp {$$=newtree2($1,$2,"Exp");}
				|ID LP Args RP {$$=newtree4($1,$2,$3,$4,"Exp");}
				|ID LP RP {$$=newtree3($1,$2,$3,"Exp");}
				|Exp LB Exp RB {$$=newtree4($1,$2,$3,$4,"Exp");}
				|Exp DOT ID {$$=newtree3($1,$2,$3,"Exp");}
				|ID {$$=newtree1($1,"Exp");}
				|INT {$$=newtree1($1,"Exp");}
				|FLOAT {$$=newtree1($1,"Exp");}
				;
Args:
				Exp COMMA Args {$$=newtree3($1,$2,$3,"Args");}
				|Exp {$$=newtree1($1,"Args");}
				;

%%
#include "lex.yy.c"
int main(int argc, char ** argv) {
	 if (argc > 1){
	 		if (!(yyin = fopen(argv[1],"r"))) {
         perror(argv[1]);
            return 1;
      }
   }
	yyparse();
	return 0;
}

yyerror(char * msg) {
	fprintf(stderr,"Error type B at Line %d: %s\n",yylineno,msg);
}
