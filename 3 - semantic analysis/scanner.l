%{
	#include<stdio.h>
	#include<string.h>
	#include"tree.h"
	#include"table.h"
	#include"parser.tab.h"
	void printResult(char * keyword){
	//	printf("( %s , %d , %s )\n", keyword ,yylineno, yytext);
		int i = 1;
		while (yytext[i]!='\0'){
			i++;	
		}
		char * tmp = malloc(sizeof(char)*i);
		strcpy(tmp,yytext);
		yylval.t = newtreenode(keyword,yylineno,tmp);
	}
%}
%option yylineno
ANNOTATION (\/\*([^*]|[\r\n]|(\*+([^\*\/]|[\r\n])))*\*+\/)|(\/\/.*)
ILLEGALANNO (\/\*)|(\*\/)
TYPE int|float
STRUCT struct
RETURN return
IF if
ELSE else
WHILE while
HEX 0[Xx][0-9A-Za-z]*
OCTAL 0[0-9A-Za-z]+
SCIENNUM [+-]?[0-9]+(\.[0-9]+)?[eE][+\-0-9a-zA-Z]*
INT [1-9]+[0-9]*|0 
FLOAT [+-]?[0-9]+"."[0-9]+
ID [A-Za-z_][A-Za-z_0-9]*
SEMI ;
COMMA ,
ASSIGNOP =
RELOP >|<|>=|<=|==|!=
PLUS "+"
MINUS -
STAR "*"
DIV "/"
AND &&
OR "||"
DOT "."
NOT "!"
LP "("
RP ")"
LB "["
RB "]"
LC "{"
RC "}"

%%
{ANNOTATION} {printResult("ANNOTATION");}
{ILLEGALANNO} { printf("Error Type A at line %d : Can't identify symbol %s.\n",yylineno, yytext);}
{TYPE} {printResult("TYPE");
	if(strcmp(yylval.t->text,"int")==0){
		yylval.t->_type = 0;
	} else if(strcmp(yylval.t->text,"float")==0){
		yylval.t->_type = 1;
	} 
	 return TYPE;}
{STRUCT} {printResult("STRUCT"); return STRUCT;}
{RETURN} { printResult("RETURN"); return RETURN;}
{IF} { printResult("IF"); return IF;}
{ELSE} { printResult("ELSE"); return ELSE;}
{WHILE} { printResult("WHILE"); return WHILE;}
{SCIENNUM} {
	char * point = NULL;
	int tag = 0;
	point = strchr(yytext, 'e');
	if (point == NULL) {
		point = strchr(yytext, 'E');
	}
	if (point != NULL) {
		point = point + sizeof(char);
		if (*point == '+' || *point == '-') {
			while (*(point = point + sizeof(char)) != '\0'){
				if (*point > '0' && *point <'9') {
				} else {
					printf("Error type A at line %d: Can't indentify Scientific number %s\n",yylineno,yytext);
					tag = 1;
					break;
				}
			}
		} else {
			printf("Error type A at line %d: Can't indentify Scientific number %s\n",yylineno,yytext);
		tag = 1;
		}
	}
	if (tag == 0) {
		printResult("SCIENNUM");
		return FLOAT;
	}
}
{HEX} { 
	int len = strlen(yytext);
	int i;
	int tag = 0;
	if (len <= 2) {
		tag = 1;
		printf("Error type A at line %d:Can't indentify Hexadecimal number %s\n",yylineno,yytext);
	}
	for (i=2; i<len; i++){
		if (!isxdigit(yytext[i])) {
			printf("Error type A at line %d: Can't indentify Hexadecimal number %s\n",yylineno,yytext);
			tag = 1;	
			break;
		}
	}	
	if (tag == 0) {
		printResult("HEX");
		return INT;
	}
}
{OCTAL} {
	int len = strlen(yytext);
	int i;
	int tag = 0;
	for (i=1; i<len; i++){
		if (yytext[i]<'0' || yytext[i]>'9'){
			printf("Error type A at line %d: Can't identify Octal number %s\n",yylineno,yytext);
			tag = 1;	
			break;
		}
	}
	if (tag == 0) {
		printResult("OCT");
		return INT;
	}
}
{INT} { printResult("INT"); yylval.t->_type = 0;  return INT;}
{FLOAT} { printResult("FLOAT"); yylval.t->_type = 1; return FLOAT;}
{ID} { printResult("ID"); return ID;}
{SEMI} { printResult("SEMI"); return SEMI;}
{COMMA} { printResult("COMMA"); return COMMA;}
{ASSIGNOP} { printResult("ASSIGNOP"); return ASSIGNOP;}
{RELOP} { printResult("RELOP"); return RELOP;}
{PLUS} { printResult("PLUS"); return PLUS;}
{MINUS} { printResult("MINUS"); return MINUS;}
{STAR} { printResult("STAR"); return STAR;}
{DIV} { printResult("DIV"); return DIV;}
{AND} { printResult("AND"); return AND;}
{OR} { printResult("OR"); return OR;}
{DOT} { printResult("DOT"); return DOT;}
{NOT} { printResult("NOT"); return NOT;}
{LP} { printResult("LP"); return LP;}
{RP} { printResult("RP"); return RP;}
{LB} { printResult("LB"); return LB;}
{RB} { printResult("RB"); return RB;}
{LC} { printResult("LC"); return LC;}
{RC} { printResult("RC"); return RC;}
[\t]+ {}
[ ]+ {}
\n {}
. { printf("Error type A at line %d: Mysterious character '%s'.\n",yylineno,yytext); }
%%

/*void main(int argc, char ** argv){

	if (argc > 1){
		if (!(yyin = fopen(argv[1],"r"))){
			perror(argv[1]);
			return 1;
		}
	}
	while (yylex()!=0){
		return 0;
	}
}*/

int yywrap(){
	return 1;
}

