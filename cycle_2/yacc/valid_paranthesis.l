
%{

#include "y.tab.h"

%}

%%

"(" { return LBRACKET; }
")" { return RBRACKET; }
"[" { return LSQUARE; } 
"]" { return RSQUARE; }
"{" { return LCURLY; }
"}" { return RCURLY; }

[ \t]   { }
\n      { return '\n'; }
.       { return INVALID; }

%%

int yywrap() {
    return 1;
}
