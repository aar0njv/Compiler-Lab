
%{
#include "y.tab.h"
%}

%%

"while"             { return WHILE; }
"("                  { return LP; }
")"                  { return RP; }
"{"                  { return LB; }
"}"                  { return RB; }
"="                  { return ASSIGN; }
"<="|">="|"=="|"!="|"<"|">" { return RELOP; }
"++"|"--"            { return INC; }
"+"|"-"|"*"|"/"      { return OP; }
[0-9]+               { return NUM; }
[a-zA-Z][a-zA-Z0-9]* { return ID; }
";"                  { return SEMI; }
[ \t\n]              { /* Ignore whitespace */ }
.                    { return INVALID; }

%%

int yywrap()
{
    return 1;
}
