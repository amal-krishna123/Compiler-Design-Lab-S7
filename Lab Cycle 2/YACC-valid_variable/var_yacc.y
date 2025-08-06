%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
int yyerror(const char *s);
%}

%token IDENTIFIER INVALID

%%
input:

    | input line
    ;

line:
      IDENTIFIER { printf("Valid variable name\n\n"); }
    | INVALID    { printf("Invalid variable name\n\n"); }
    ;
%%

int main() {
    printf("Enter variable names (press Ctrl+D to exit):\n\n");
    yyparse();
    return 0;
}

int yyerror(const char *s) {
    return 0;
}