#include "defs.h"
#define extern_
#include "data.h"
#undef extern_
#include "decl.h"
#include <errno.h>

// Compiler setup and top-level execution
// Copyright (c) 2019 Warren Toomey, GPL3

// Initialise global variables
static void init() {
  Line = 1;
  Putback = '\n';
  Globs = 0;
}

// Print out a usage if started incorrectly
static void usage(char *prog) {
  fprintf(stderr, "Usage: %s infile\n", prog);
  exit(1);
}

// Main program: check arguments and print a usage
// if we don't have an argument. Open up the input
// file and call scanfile() to scan the tokens in it.
int main(int argc, char *argv[]) {
  struct ASTnode *tree;

  if (argc != 2)
    usage(argv[0]);

  init();

  // Open up the input file
  if ((Infile = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
    exit(1);
  }
  // Create the output file
  if ((Outfile = fopen("out.s", "w")) == NULL) {
    fprintf(stderr, "Unable to create out.s: %s\n", strerror(errno));
    exit(1);
  }

  // For now, ensure that void printint() is defined
  addglob("printint", P_CHAR, S_FUNCTION, 0);

  scan(&Token);			// Get the first token from the input
  genpreamble();		// Output the preamble
  while (1) {			// Parse a function and
    tree = function_declaration();
    genAST(tree, NOREG, 0);	// generate the assembly code for it
    if (Token.token == T_EOF)	// Stop when we have reached EOF
      break;
  }
  genpostamble();
  fclose(Outfile);		// Close the output file and exit
  return(0);
}
