
%{
#include <stdio.h>
int yylex();
void yyerror(char *s);
%}

%token WHILE LP RP LB RB ASSIGN RELOP
%token INC OP NUM ID SEMI INVALID

%%

program:
    WHILE LP condition RP LB statements RB
    {
        printf("Valid while loop\n");
    }
    ;

condition:
    ID RELOP ID
    | ID RELOP NUM
    | NUM RELOP ID
    | ID
    ;

statements:
    statement
    | statements statement
    ;

statement:
    ID ASSIGN expression SEMI
    | ID INC SEMI
    ;

expression:
    ID
    | NUM
    | expression OP ID
    | expression OP NUM
    ;

%%

void yyerror(char *s)
{
    printf("Invalid while loop\n");
}

int main()
{
    printf("Enter a while loop:\n");
    yyparse();
    return 0;
}
