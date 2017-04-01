%option yylineno

%x COMMENT

EXP ([Ee][-+]?[0-9]+)

%{
struct symbol {
	struct ref *reflist;
	char *name;
};

struct ref {
	struct ref *next;
	char *filename;
	int flags;
	int lineno;
	char* class;
};

#define NHASH 9999
struct symbol symtab[NHASH];

struct symbol *lookup(char*);
void addref(int, char*, char*, int, char*);

char *curfilename;

struct bufstack {
	struct bufstack *prev;
	YY_BUFFER_STATE bs;
	int lineno;
	char *filename;
	FILE *f;
}*curbs;


int defining;

%}

%%
"/*" { BEGIN(COMMENT); }
<COMMENT>("*/") { BEGIN(INITIAL); }
<COMMENT>([^*]|\n)+|.
<COMMENT><<EOF>> { printf("%s: %d: Unterminated comment\n", curfilename, yylineno); return 0; }
"//".*\n { }


int|float|typedef|void|struct { 
	defining = 1;
	addref(yylineno, curfilename, yytext, defining, "define keywords"); 
}

break|case|continue|default|do|else|for|if|return|switch|while  {
 addref(yylineno, curfilename, yytext, defining, "keywords"); 
}
0 {
  addref(yylineno, curfilename, yytext, defining, " 10 science number");
}
0[0-7]*? {
  addref(yylineno, curfilename, yytext, defining, "8  number system"); 
}
[1-9][0-9]*? {
  addref(yylineno, curfilename, yytext, defining, "10  number system"); 
}
0[Xx][0-9a-fA-F]+? {
  addref(yylineno, curfilename, yytext, defining, "16  number system"); 
}

([1-9]*\.[0-9]+|[0-9]+\.){EXP}?[flFL]?|[0-9]+{EXP}[flFL]? {
  addref(yylineno, curfilename, yytext, defining, " 10 science number");
}

0[Xx]*([0-9a-fA-F]*\.[0-9a-fA-F]+|[0-9a-fA-F]+\.?) {
  addref(yylineno, curfilename, yytext, defining, "16 hexadecimal");
}
0[Xx]*[0-9a-fA-F]+ {
  addref(yylineno, curfilename, yytext, defining, "16 hexadecimal");
}

"{"|";" { defining = 0; }
"["|"]"|"("|")"|"{"|"}"|"."|"->" {   addref(yylineno, curfilename, yytext, defining, "operation"); }
"!" { addref(yylineno, curfilename, yytext, defining, "operation"); }
"*"|"/"  { addref(yylineno, curfilename, yytext, defining, "operation"); }
"+"|"-"  { addref(yylineno, curfilename, yytext, defining, "operation"); }
"<"|">"|">="|"<="|"=="|"!="  { addref(yylineno, curfilename, yytext, defining, "operation"); }
"&&" { addref(yylineno, curfilename, yytext, defining, "operation"); }
"||" { addref(yylineno, curfilename, yytext, defining, "operation"); }
"=" { addref(yylineno, curfilename, yytext, defining, "operation"); }

[_a-zA-Z]([_a-zA-Z0-9])* { 
 addref(yylineno, curfilename, yytext, defining, "identifier"); 
}

[ \t\n]+ { }

. { printf(" %d: Mystery character '%s'\n", yylineno, yytext); }
%%

static unsigned symhash(char *sym) {
	unsigned int hash = 0;
	unsigned c;
	
	while(c == *sym++) hash = hash*9^c;

	return hash;
}

struct symbol* lookup(char* sym) {
	struct symbol *sp = &symtab[symhash(sym)%NHASH];
	int scount = NHASH;
	while(--scount >= 0) {
		if(sp->name && !strcmp(sp->name, sym)) return sp;

		if(!sp->name) {
			sp->name = strdup(sym);
			sp->reflist = 0;
			return sp;
		}
		if(++sp >= symtab+NHASH) sp = symtab;
	}
	fputs("symbol table overflow\n", stderr);
	abort();
}

void addref(int lineno, char* filename, char* word, int flags, char* class) {
	struct ref *r;
	struct symbol *sp = lookup(word);
	
	if(sp->reflist && sp->reflist->lineno == lineno && sp->reflist->filename == filename) return;

	r = malloc(sizeof(struct ref));
	if(!r) {
		fputs("out of space\n", stderr); 
		abort(); 
	}
	r->next = sp->reflist;
	r->filename = filename;
	r->lineno = lineno;
	r->flags = flags;
	r->class = class;
	sp->reflist = r;
}

static int symcompare(const void *xa, const void *xb) {
	const struct symbol *a = xa;
	const struct symbol *b = xb;
	if(!a->name) {
		if(!b->name) return 0;
		return 1;
	}
	if(!b->name) return -1;
	return strcmp(a->name, b->name);
}

void printrefs() {
	struct symbol *sp;
	qsort(symtab, NHASH, sizeof(struct symbol), symcompare); 
	for(sp = symtab; sp->name && sp < symtab+NHASH; sp++) {
		char *prevfn = NULL;
		struct ref *rp = sp->reflist;
		struct ref *rpp = 0;
		struct ref *rpn;

		do {
			rpn = rp->next;
			rp->next = rpp;
			rpp = rp;
			rp = rpn;
		}while(rp);	
	
		printf("%s", sp->name);
		for(rp = rpp; rp; rp = rp->next) {
			if(rp->filename == prevfn) printf(" %d, %s", rp->lineno, rp->class);
			else {
				printf(" %d, %s", rp->lineno, rp->class);
				prevfn = rp->filename;
			}
			if(rp->flags & 01) printf("*");
		}
		printf("\n");
	} 
}

int yywrap() {
	return 1;
}

int main(int argc, char** argv) {
	yylineno = 1;
	if(argc > 1) yyin = fopen(argv[1], "r");
	else yyin = stdin;
	yylex();
	printrefs();
	return 0;
}
