%{
#include "calc.tab.h"
%}

%%

[0-9]+        { yylval = atoi(yytext); return NUMBER; }
[+\-*/()]     { return yytext[0]; }
[\t ]+        ;
\n            { return '\n'; } 
.             { printf("Invalid character: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}