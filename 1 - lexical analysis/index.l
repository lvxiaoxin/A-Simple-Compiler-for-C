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
};

#define NHASH 9999
struct symbol symtab[NHASH];

struct symbol *lookup(char*);
void addref(int, char*, char*, int);

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


int|float|typedef|void|struct { defining = 1; }

break|case|continue|default|do|else|for|if|return|switch|while

0[0-7]*? 
[1-9][0-9]*? 
0[Xx][0-9a-fA-F]+? 

([0-9]*\.[0-9]+|[0-9]+\.){EXP}?[flFL]? 
[0-9]+{EXP}[flFL]? 

0[Xx](0-9a-fA-F]*\.[0-9a-fA-F]+|[0-9a-fA-F]+\.?)[Pp][-+]?[0-9]+[flFL]? 



\'([^'\\]\\['"?\\abfnrtv]|\\[0-7]{1,3}|\\[Xx\][0-9a-fA-F]+)+\' 
L?\"([^"\\]|\\['"?\\abfnrtv]|\\[0-7]{1,3}|\\[Xx][0-9a-fA-F]+)*\" 

"{"|";" { defining = 0; }
"["|"]"|"("|")"|"{"|"}"|"."|"->" 
"!"
"*"|"/" 
"+"|"-" 
"<"|">"|">="|"<="|"=="|"!=" 
"&&" 
"||"
"=" 

[_a-zA-Z]([_a-zA-Z0-9])* { 
// the problem is here
 addref(yylineno, curfilename, yytext, defining); 
}

[ \t\n]+ { }

. { printf("%s:%d: Mystery character '%s'\n", curfilename, yylineno, yytext); }
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

void addref(int lineno, char* filename, char* word, int flags) {
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
	
		printf("%10s", sp->name);
		for(rp = rpp; rp; rp = rp->next) {
			if(rp->filename == prevfn) printf(" %d", rp->lineno);
			else {
				printf(" %s:%d", rp->filename, rp->lineno);
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
	//printrefs();
	return 0;
}
