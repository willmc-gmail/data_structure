#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#define MAX 100

int main() {
    SetConsoleOutputCP(65001); // 解決 Windows 亂碼
    char infix[] = "A/B-C+D*E-A*C/D";
    printf("處理的中序算式: %s\n", infix);



    return 0;
}