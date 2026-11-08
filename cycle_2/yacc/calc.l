%{

#include "y.tab.h"
#include <stdio.h>

%}

%%

[0-9]+  { yylval.value = atoi(yytext); return NUMBER; }

[ \t]   { } //ignore spaces and Tabs
[\n]    { return '\n'; }
.       { return yytext[0]; }

%%

int yywrap() {
    return 1;
}

