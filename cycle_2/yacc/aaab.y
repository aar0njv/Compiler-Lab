%{

#include <stdio.h>

int yylex();
void yyerror(const char *s);

%}

%token A B INVALID

%%

input : sequence B'\n'
    {
    printf("Pattern Matched\n");
    }
    ;

sequence : A sequence
    |
    ;

%%

void yyerror(const char *s) {
    printf("Pattern not matched.\n");
}

int main() {
    printf("Enter a string: ");
    yyparse();
    return 0;
}
