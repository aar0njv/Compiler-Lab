%{

#include "y.tab.h"

%}

%%

a   { return A; }
b   { return B; }
\n  { return '\n'; }
.   { return INVALID; }

%%

int yywrap() {
    return 1;
}

