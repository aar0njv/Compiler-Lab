

%{

#include <stdio.h>

int yylex();
void yyerror(const char *s);

%}

%token LETTER DIGIT INVALID

%%

input : LETTER sequence'\n'
    {
        printf("Valid Variable.\n");
        return 0;
    }
    ;

sequence : LETTER sequence
    | DIGIT sequence
    | 
    ;

%%

void yyerror(const char *s) {
    printf("Invalid");
}

int main() {
    printf("Enter the variable name: ");
    yyparse();
    return 0;
}