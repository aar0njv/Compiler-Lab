%{
#include <stdio.h>

int yylex();
void yyerror(const char *s);

%}


// declares the data type used for semantic values
%union {
    double value;
}

%token <value> NUMBER
%type <value> expression

// declares the associativity
%left '+' '-'
%left '*' '/'
%right UMINUS

%%

input : expression '\n'
    { printf("Result = %g\n", $1); }
    ;

expression : expression '+' expression
    { $$ = $1 + $3; }
    
    | expression '-' expression
    { $$ = $1 - $3; }

    | expression '*' expression
    { $$ = $1 * $3; }
    
    | expression '/' expression
    {
        if ($3 == 0) {
            printf("Division by zero error\n");
            YYABORT;
        }
        $$ = $1 / $3;
    }

    | '(' expression ')'
    { $$ = $2; }
    
    | '-' expression %prec UMINUS
    { $$ = -$2; }
    
    | NUMBER
    { $$ = $1; }
    ;



%%

void yyerror(const char *s)
{
    printf("Invalid expression\n");
}

int main()
{
    printf("Enter an expression: ");
    yyparse();
    return 0;
}