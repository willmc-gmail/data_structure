#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#define MAX 100

int getPrecedence(int operator) {
    if(operator == '*' || operator == '/') return 2;
    if(operator == '+' || operator == '-') return 1;
    return 0;
}

void popOutAndCombine(char* operandStack[], char operatorStack[], int* operandTop, int* operatorTop) {
    char* right = operandStack[(*operandTop)--];
    char* left = operandStack[(*operandTop)--];
    char operator = operatorStack[(*operatorTop)--];

    char* newExpress = (char*) malloc(sizeof(char) * MAX);

    sprintf(newExpress, "(%s%c%s)", left, operator, right);
    
    operandStack[++(*operandTop)] = newExpress;
}

int main() {
    SetConsoleOutputCP(65001); // 解決 Windows 亂碼
    char infix[] = "A/B-C+D*E-A*C/D";
    // printf("處理的中序算式: %s\n", infix);
    
    char* operandStack[MAX];
    char operatorStack[MAX];
    int operandTop = -1;
    int operatorTop = -1;

    for(int i = 0; i < strlen(infix); i++) {
    // for(int i = 0; i < sizeof(infix); i++) {
        // printf("www-check-print infix %c\n", infix[i]);
        char token = infix[i];
        if(isalpha(token)) {
            printf("www-check-print %c is alpha\n", token);
            char* str = (char*) malloc(sizeof(char) * 2);
            str[0] = token;
            str[1] = '\0';
            operandStack[++operandTop] = str;
        } else {
            printf("www-check-print %c is not alpha\n", token);
            while( (operatorTop != -1) &&  (getPrecedence(operatorStack[operatorTop]) >= getPrecedence(token)) ) 
            {
                // pop out
                popOutAndCombine(operandStack, operatorStack, &operandTop, &operatorTop);
            }
            operatorStack[++operatorTop] = token;
        }
    }

    while(operatorTop != -1) {
        popOutAndCombine(operandStack, operatorStack, &operandTop, &operatorTop);
    }

    printf("============================\n");
    for(int j = 0; j <= operandTop; j++) {
        printf("www-check-operandStack[j] is %s\n", operandStack[j]);
    }
    for(int j = 0; j <= operatorTop; j++) {
        printf("www-check-operatorStack[j] is %c\n", operatorStack[j]);
    }
    printf("www-check-operandTop is %d\n", operandTop);
    printf("www-check-operatorTop is %d\n", operatorTop);
    
    return 0;
}