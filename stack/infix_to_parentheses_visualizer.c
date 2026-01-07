#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#define MAX 100

// 定義運算子優先權
int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 視覺化當前堆疊狀態的函式
void printStatus(char* operandStack[], char operatorStack[], int opnTop, int optTop, char token) {
    printf("\n--- 讀取字元: [%c] ---\n", token);
    
    printf("運算子堆疊 (optTop=%d): ", optTop);
    for (int i = 0; i <= optTop; i++) printf("[%c] ", operatorStack[i]);
    
    printf("\n運算元堆疊 (opnTop=%d): \n", opnTop);
    for (int i = 0; i <= opnTop; i++) printf("  index %d: %s\n", i, operandStack[i]);
    printf("--------------------------\n");
}

void printApplyDetail(const char* label, char* operandStack[], char operatorStack[], int opnTop, int optTop) {
    printf("   [ %s ]\n", label);
    printf("     運算子堆疊 (Top:%d): ", optTop);
    if (optTop == -1) printf("Empty");
    for (int i = 0; i <= optTop; i++) printf("[%c] ", operatorStack[i]);
    
    printf("\n     運算元堆疊 (Top:%d): ", opnTop);
    if (opnTop == -1) printf("Empty");
    for (int i = 0; i <= opnTop; i++) printf(" index %d: %s |", i, operandStack[i]);
    printf("\n   ----------------------------------\n");
}

// 執行一次「加上括號」的操作
void applyOperator(char* operandStack[], char operatorStack[], int* opnTop, int* optTop) {
    char* right = operandStack[(*opnTop)--];
    char* left = operandStack[(*opnTop)--];
    char op = operatorStack[(*optTop)--];
    char leftBracket = '(';
    char rightBracket = ')';

    printf(">> 觸發結合: 將 %s 與 %s 用 %c 結合\n", left, right, op);

    char* newExpr = (char*)malloc(MAX * sizeof(char));

    sprintf(newExpr, "%c%s%c%s%c", leftBracket, left, op, right, rightBracket);
    // sprintf(newExpr, "(%s%c%s)", left, op, right);

    printf("   >> 短暫結合後, newExpr: %s\n", newExpr);

    printApplyDetail("Apply 中間態 (已彈出，未推回)", operandStack, operatorStack, *opnTop, *optTop);
    operandStack[++(*opnTop)] = newExpr;
    // 3. 壓入新結果後，印出狀態 (After Apply)
    printApplyDetail("Apply 後狀態 (已推回新結果)", operandStack, operatorStack, *opnTop, *optTop);
}

int main() {
    SetConsoleOutputCP(65001); // 解決 Windows 亂碼

    char infix[] = "A/B-C+D*E-A";
    char* operandStack[MAX];
    char operatorStack[MAX];
    int opnTop = -1;
    int optTop = -1;

    printf("開始處理算式: %s\n", infix);

    for (int i = 0; i < strlen(infix); i++) {
        char token = infix[i];

        if (isalpha(token)) {
            // --- 處理運算元 ---
            char* str = (char*)malloc(2 * sizeof(char));
            str[0] = token; str[1] = '\0';
            printf("opnTop 為 %d\n", opnTop);
            printf("optTop 為 %d\n", optTop);
            
            printf("[Step: 讀取運算元] 遇到 '%c'，直接推入運算元堆疊。\n", token);
            operandStack[++opnTop] = str;
            printf("   >> 目前運算元堆疊頂端 (opnTop=%d): %s\n", opnTop, operandStack[opnTop]);
            
        } else {
            printf("opnTop 為 %d\n", opnTop);
            printf("optTop 為 %d\n", optTop);
            // --- 處理運算子 ---
            printf("[Step: 讀取運算子] 遇到 '%c' (優先權: %d)\n", token, getPrecedence(token));

            // 當前符號優先權 <= 堆疊頂端時，觸發 LIFO 結合
            while (optTop != -1 && getPrecedence(operatorStack[optTop]) >= getPrecedence(token)) {
                printf("   !! 優先權檢查: 堆疊頂端 [%c](%d) >= 當前 [%c](%d) -> 必須先處理舊的運算！\n", 
                        operatorStack[optTop], getPrecedence(operatorStack[optTop]), 
                        token, getPrecedence(token));
                
                // 呼叫結合函式
                applyOperator(operandStack, operatorStack, &opnTop, &optTop);
                
                printf("   >> 結合後，目前運算元堆疊新頂端: %s\n", operandStack[opnTop]);
            }

            // 將當前符號推入，等待後方運算元
            operatorStack[++optTop] = token;
            printf("   >> 將當前運算子 [%c] 推入運算子堆疊 (optTop=%d)\n", token, optTop);
        }

        printStatus(operandStack, operatorStack, opnTop, optTop, token);
    }

    printf("\n=== 掃描完畢，處理剩餘運算子 ===\n");
    while (optTop != -1) {
        applyOperator(operandStack, operatorStack, &opnTop, &optTop);
        printStatus(operandStack, operatorStack, opnTop, optTop, ' ');
    }

    printf("\n最終括號化結果: %s\n", operandStack[opnTop]);

    printf("結束後 opnTop 的值: %d\n", opnTop);
    for (int j = 0; j <= opnTop; j++) {
        printf("operandStack[%d] 內容: %s\n", j, operandStack[j]);
    }

    return 0;
}