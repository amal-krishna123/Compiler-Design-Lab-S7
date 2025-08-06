%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
int yyerror(const char *s);
%}

%token NUMBER
%left '+' '-'
%left '*' '/'

%%
input:
    | input line
    ;

line:
      expr '\n'    { printf("Result = %d\n\n", $1); }
    ;

expr:
      expr '+' expr   { $$ = $1 + $3; }
    | expr '-' expr   { $$ = $1 - $3; }
    | expr '*' expr   { $$ = $1 * $3; }
    | expr '/' expr   { 
                          if ($3 == 0) {
                              printf("Error: Division by zero\n");
                              $$ = 0;
                          } else {
                              $$ = $1 / $3;
                          }
                      }
    | '(' expr ')'     { $$ = $2; }
    | NUMBER           { $$ = $1; }
    ;
%%

int main() {
    printf("Enter expressions (Ctrl+D to exit):\n\n");
    yyparse();
    return 0;
}

int yyerror(const char *s) {
    printf("Syntax error: %s\n", s);
    return 0;
}