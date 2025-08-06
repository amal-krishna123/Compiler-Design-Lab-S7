%{
#include "y.tab.h"
%}

%%
[a-zA-Z][a-zA-Z0-9]*[\n]   { return IDENTIFIER; }
.*[\n]                          { return INVALID; }
%%

int yywrap(void) {
    return 1;
}