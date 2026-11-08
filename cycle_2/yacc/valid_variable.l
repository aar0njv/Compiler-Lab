
%{

#include "y.tab.h"

%}

%%

[a-zA-Z]    { return LETTER; }
[0-9]       { return DIGIT; }

[ \t]   { }
\n      { return '\n'; }
.       { return INVALID; }

%%

int yywrap() {
    return 1;
}
