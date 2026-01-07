#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#define MAX 100

int getPrecedence(char operator) {
    if(operator == '*' || operator == '/') return 2;
    if(operator == '+' || operator == '-') return 1;

    return 0;
}

// 視覺化堆疊狀態的函式
void printStackStatus(char* operandStack[], char operatorStack[], int* operandTop, int* operatorTop) {
    printf("\n==== [Stack Status] ====\n");
    printf("operandTop: %d\n", *operandTop);
    printf("operatorTop: %d\n", *operatorTop);

    // 印出運算元堆疊 (operandStack)
    printf("Operand Stack: ");
    if (*operandTop == -1) {
        printf("[Empty]");
    } else {
        for (int i = 0; i <= *operandTop; i++) {
            printf("[%s] ", operandStack[i]);
        }
    }
    printf("\n");

    // 印出運算子堆疊 (operatorStack)
    printf("Operator Stack: ");
    if (*operatorTop == -1) {
        printf("[Empty]");
    } else {
        for (int i = 0; i <= *operatorTop; i++) {
            printf("[%c] ", operatorStack[i]);
        }
    }
    printf("\n========================\n\n");
}

void popOut(char* operandStack[], char operatorStack[], int* operandTop, int* operatorTop) {
    if (*operandTop < 1) return;

    // 先彈出 (Pop) 並遞減指標，這是停止 while 迴圈的關鍵
    char* right = operandStack[(*operandTop)--]; 
    char* left = operandStack[(*operandTop)--];
    char op = operatorStack[(*operatorTop)--];

    printf(">> 執行結合: %s %c %s\n", left, op, right);

    char* newExpr = (char*) malloc(sizeof(char) * MAX);
    sprintf(newExpr, "(%s%c%s)", left, op, right);

    // 再推入 (Push)
    operandStack[++(*operandTop)] = newExpr;
}

int main() {
    SetConsoleOutputCP(65001); // 解決 Windows 亂碼
    char infix[] = "A/B-C+D*E-A*C/D";
    printf("處理的中序算式: %s\n", infix);

    char* operandStack[MAX];
    char operatorStack[MAX];
    int operandTop = -1;
    int operatorTop = -1;

    for(int i = 0; i < strlen(infix); i++) {
        // printf("char is %c\n", infix[i]);
        char token = infix[i];

        printStackStatus(operandStack, operatorStack, &operandTop, &operatorTop);

        if(isalpha(token)) {
            char* str = (char*) malloc(sizeof(char) * 2);
            str[0] = token;
            str[1] = '\0';
            operandStack[++operandTop] = str;
        } else {
            while ( operatorTop != -1 && (getPrecedence(operatorStack[operatorTop]) >= getPrecedence(token)))
            {
                printf("when token is not an alpah the token is %c\n", token);
                // pop out two elements of operandStack and one operatorStack, combine with ()
                popOut(operandStack, operatorStack, &operandTop, &operatorTop);
            }
            operatorStack[++operatorTop] = token;
            
        }
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
    
    printf("\n=== 掃描完畢，處理剩餘運算子 ===\n");
    while (operatorTop != -1) {
        popOut(operandStack, operatorStack, &operandTop, &operatorTop);
        // printStackStatus(operandStack, operatorStack, &operandTop, &operatorTop);
    }



    // printf("結束後 opnTop 的值: %d\n", operandTop);
    // for (int j = 0; j <= operandTop; j++) {
    //     printf("operandStack[%d] 內容: %s\n", j, operandStack[j]);
    // }
    // printf("\n最終結果: %s\n", operandStack[operandTop]);
    
    return 0;
}