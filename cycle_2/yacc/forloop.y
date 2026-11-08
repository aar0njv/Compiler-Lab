
// not working

%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%token FOR ID NUM RELOP INCR DECR
%left '+' '-'

%%

program: FOR '(' init ';' condition ';' incr ')' body
        {
            printf("Valid Syntax.\n");
        }
        ;

expr: ID 
    | NUM 
    | expr '+' expr 
    | expr '-' expr
    ;

init: ID '=' expr 
    | /* empty */
    ;

condition: expr RELOP expr 
    | /* empty */
    ;

incr: ID INCR 
    | ID DECR 
    | INCR ID 
    | DECR ID 
    | ID '=' expr 
    | /* empty */ 
    ;

body: '{' stmts '}' 
    | assignment
    | /* empty */ 
    ;

stmts: stmts assignment 
    | assignment
    | /* empty */ 
    ; 

assignment: ID '=' expr ';'
    ;

%%

void yyerror(const char *s) {
    printf("Invalid Syntax\n");
}

int main() {
    printf("Enter the looping statement: (CTRL + D to exit)\n");
    yyparse();
    return 0;
}