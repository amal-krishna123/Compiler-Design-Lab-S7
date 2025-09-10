%{
#include "for.tab.h"
#include <stdlib.h>
%}

%option noyywrap

%%

"for"           { return FOR; }
"("             { return '('; }
")"             { return ')'; }
";"             { return ';'; }
"="             { return '='; }
"<"             { return '<'; }
">"             { return '>'; }
"++"            { return INC; }
"--"            { return DEC; }
"+"             { return '+'; }
"-"             { return '-'; }
"*"             { return '*'; }
"/"             { return '/'; }

[0-9]+          { yylval = atoi(yytext); return NUM; }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.str = strdup(yytext); return ID; }

[ \t\n]+        ;  // ignore whitespace

.               { return yytext[0]; }

%%