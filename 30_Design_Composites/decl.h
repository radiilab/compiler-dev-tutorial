// Function prototypes for all compiler files
// Copyright (c) 2019 Warren Toomey, GPL3

// scan.c
void reject_token(struct token *t);
int scan(struct token *t);

// tree.c
struct ASTnode *mkastnode(int op, int type,
			  struct ASTnode *left,
			  struct ASTnode *mid,
			  struct ASTnode *right,
			  struct symtable *sym, int intvalue);
struct ASTnode *mkastleaf(int op, int type,
			  struct symtable *sym, int intvalue);
struct ASTnode *mkastunary(int op, int type, struct ASTnode *left,
			    struct symtable *sym, int intvalue);
void dumpAST(struct ASTnode *n, int label, int parentASTop);

// gen.c
int genlabel(void);
int genAST(struct ASTnode *n, int reg, int parentASTop);
void genpreamble();
void genpostamble();
void genfreeregs();
void genglobsym(struct symtable *node);
int genglobstr(char *strvalue);
int genprimsize(int type);
void genreturn(int reg, int id);

// cg.c
void cgtextseg();
void cgdataseg();
void freeall_registers(void);
void cgpreamble();
void cgpostamble();
void cgfuncpreamble(struct symtable *sym);
void cgfuncpostamble(struct symtable *sym);
int cgloadint(int value, int type);
int cgloadglob(struct symtable *sym, int op);
int cgloadlocal(struct symtable *sym, int op);
int cgloadglobstr(int label);
int cgadd(int r1, int r2);
int cgsub(int r1, int r2);
int cgmul(int r1, int r2);
int cgdiv(int r1, int r2);
int cgshlconst(int r, int val);
int cgcall(struct symtable *sym, int numargs);
void cgcopyarg(int r, int argposn);
int cgstorglob(int r, struct symtable *sym);
int cgstorlocal(int r, struct symtable *sym);
void cgglobsym(struct symtable *node);
void cgglobstr(int l, char *strvalue);
int cgcompare_and_set(int ASTop, int r1, int r2);
int cgcompare_and_jump(int ASTop, int r1, int r2, int label);
void cglabel(int l);
void cgjump(int l);
int cgwiden(int r, int oldtype, int newtype);
int cgprimsize(int type);
void cgreturn(int reg, struct symtable *sym);
int cgaddress(struct symtable *sym);
int cgderef(int r, int type);
int cgstorderef(int r1, int r2, int type);
int cgnegate(int r);
int cginvert(int r);
int cglognot(int r);
int cgboolean(int r, int op, int label);
int cgand(int r1, int r2);
int cgor(int r1, int r2);
int cgxor(int r1, int r2);
int cgshl(int r1, int r2);
int cgshr(int r1, int r2);

// expr.c
struct ASTnode *binexpr(int ptp);

// stmt.c
struct ASTnode *compound_statement(void);

// misc.c
void match(int t, char *what);
void semi(void);
void lbrace(void);
void rbrace(void);
void lparen(void);
void rparen(void);
void ident(void);
void fatal(char *s);
void fatals(char *s1, char *s2);
void fatald(char *s, int d);
void fatalc(char *s, int c);

// sym.c
void appendsym(struct symtable **head, struct symtable **tail,
	       struct symtable *node);
struct symtable *newsym(char *name, int type, int stype, int class,
			int size, int posn);
struct symtable *addglob(char *name, int type, int stype,
			 int class, int size);
struct symtable *addlocl(char *name, int type, int stype,
			 int class, int size);
struct symtable *addparm(char *name, int type, int stype,
			 int class, int size);
struct symtable *findglob(char *s);
struct symtable *findlocl(char *s);
struct symtable *findsymbol(char *s);
struct symtable *findcomposite(char *s);
void clear_symtable(void);
void freeloclsyms(void);

// decl.c
struct symtable *var_declaration(int type, int class);
struct ASTnode *function_declaration(int type);
void global_declarations(void);

// types.c
int inttype(int type);
int ptrtype(int type);
int parse_type(void);
int pointer_to(int type);
int value_at(int type);
struct ASTnode *modify_type(struct ASTnode *tree, int rtype, int op);
