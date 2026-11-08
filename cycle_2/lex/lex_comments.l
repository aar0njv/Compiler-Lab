%{
#include <stdio.h>

char output[100];
int out_index = 0;

%}

%%

"//".*                      { /* Ignore single line comments */ }
"/*".*"*/"                  { /* Ignore multi-line comments */ }
.|\n                        { output[out_index++] = yytext[0]; } /* Buffer valid code characters and newlines */

%%

int yywrap(void) {
    return 1; // Indicates End of File
}

int main() {
    printf("Enter the code (Press Ctrl+D to exit):\n");
    
    // Start scanning
    yylex(); 
    
    output[out_index] = '\0';
    printf("\n--- Output ---\n%s\n", output);
    
    return 0;
}