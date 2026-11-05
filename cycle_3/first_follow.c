
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char prod[10][10];
int n;

void FIRST(char ch){
    int i, j;

    for(i = 0; i < n; i++){
        if(prod[i][0] == ch){
            if(!isupper(prod[i][2]))
                printf("%c ", prod[i][2]);
            else
                FIRST(prod[i][2]);
        }
    }
}

void FOLLOW(char ch){
    int i, j;

    if(prod[0][0] == ch)
        printf("$ ");

    for(i = 0; i < n; i++){
        for(j = 2; prod[i][j] != '\0'; j++){
            if(prod[i][j] == ch){
                if(prod[i][j+1] != '\0'){
                    if(!isupper(prod[i][j+1]))
                        printf("%c ", prod[i][j+1]);
                    else
                        FIRST(prod[i][j+1]);
                }
                else if(prod[i][0] != ch){
                    FOLLOW(prod[i][0]);
                }
            }
        }
    }
}

int main(){
    int i;
    char ch;

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions:\n");

    for(i = 0; i < n; i++)
        scanf("%s", prod[i]);

    printf("\nFIRST and FOLLOW:\n");

    for(i = 0; i < n; i++){
        ch = prod[i][0];

        printf("\nFIRST(%c) = { ", ch);
        FIRST(ch);
        printf("}");

        printf("\nFOLLOW(%c) = { ", ch);
        FOLLOW(ch);
        printf("}\n");
    }

    return 0;
}
