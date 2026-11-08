
%{

#include <stdio.h>

int yylex();
void yyerror(const char *s);

%}

%token LBRACKET RBRACKET
%token LCURLY RCURLY
%token LSQUARE RSQUARE
%token INVALID

%%

input : sequence'\n' {
        printf("Valid");
    }
    ;

sequence :
    | LBRACKET sequence RBRACKET sequence
    | LSQUARE sequence RSQUARE sequence
    | LCURLY sequence RCURLY sequence
    ;

%%

void yyerror(const char *s) {
    printf("Invalid");
}

int main() {
    printf("Enter the paranthesis string: ");
    yyparse();
    return 0;
}