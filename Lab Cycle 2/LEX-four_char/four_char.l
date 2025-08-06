%{
#include <stdio.h>
%}

%%
.*[Aa][Bb][Hh][Ii].*     { printf("Rejected: contains 'Abhi'\n"); }
.*                       { printf("Accepted: %s\n", yytext); }
%%

int main() {
    printf("Enter Strings (press Ctrl+D to exit):\n\n");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}