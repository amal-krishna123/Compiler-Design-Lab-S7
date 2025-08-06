%{
#include <stdio.h>
#include <stdlib.h>
%}

%token FOR ID NUM INC DEC

%%

stmt:
    FOR '(' expr ';' expr ';' expr ')' ';' { printf("Valid FOR loop\n\n"); }
    ;

expr:
    ID '=' NUM
    | ID '<' NUM
    | ID '>' NUM
    | ID INC
    | ID DEC
    | ID '=' ID '+' NUM
    | ID '=' ID '-' NUM
    | ID
    | NUM
    ;

%%

int main() {
    printf("Enter a FOR loop:\n\n");
    yyparse();
    return 0;
}

int yyerror(const char *s) {
    printf("Syntax Error: %s\n", s);
    return 0;
}