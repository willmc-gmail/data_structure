int calculate(char* s) {
    int len = strlen(s);
    if (len == 0) return 0;

    int stack[len]; // 用於存放準備加總的數字
    int top = -1;
    long currentNumber = 0;
    char lastOperator = '+'; // 預設第一個數字視為被 '+' 處理

    for (int i = 0; i < len; i++) {
        char ch = s[i];

        // 1. 解析數字
        if (isdigit(ch)) {
            currentNumber = currentNumber * 10 + (ch - '0');
        }

        // 2. 當遇到運算子或是字串結尾時
        if ((!isdigit(ch) && !isspace(ch)) || i == len - 1) {
            if (lastOperator == '+') {
                stack[++top] = (int)currentNumber;
            } else if (lastOperator == '-') {
                stack[++top] = (int)-currentNumber; // 減法視為加負數
            } else if (lastOperator == '*') {
                stack[top] = stack[top] * (int)currentNumber; // 立刻乘
            } else if (lastOperator == '/') {
                stack[top] = stack[top] / (int)currentNumber; // 立刻除
            }
            lastOperator = ch;
            currentNumber = 0;
        }
    }

    // 3. 最後將堆疊中所有數字相加
    long result = 0;
    while (top != -1) {
        result += stack[top--];
    }
    return (int)result;
}
/*
// method 1
bool isOperator(char op) {
    if(op == '+' || op == '-' || op == '*' || op == '/') return true;
    return false;
}

int getPrecedence(int operator) {
    if(operator == '*' || operator == '/') return 2;
    if(operator == '+' || operator == '-') return 1;
    return 0;
}

void popOutAndCalculate(int operandStack[], char operatorStack[], int* operandTop, int* operatorTop) {
    int right = operandStack[(*operandTop)--];
    int left = operandStack[(*operandTop)--];

    char operator = operatorStack[(*operatorTop)--];
    
    int result = 0;
    if(operator == '+') result = left + right;
    else if(operator == '-') result = left - right;
    else if(operator == '*') result = left * right;
    else if(operator == '/') result = left / right;

    operandStack[++(*operandTop)] = result;
}

int calculate(char* s) {
    int len = strlen(s);
    int operandStack[len+1];
    char operatorStack[len+1];
    int operandTop = -1;
    int operatorTop = -1;

    for(int i=0; i<len; i++) {
        char op = s[i];
        if(isdigit(op)) {
            printf("this isalpha s[%d] is %c\n", i, op);
            long val = 0;
            while(i<len && isdigit(s[i])) {
                val = val * 10 + (s[i] - '0');
                i++;
            }
            i--;

            operandStack[++operandTop] = (int)val;
        }

        if(isOperator(op)) {
            printf("this isOperator s[%d] is %c\n", i, op);
            while(operatorTop != -1 && ( getPrecedence(operatorStack[operatorTop]) >= getPrecedence(op) )) {
                popOutAndCalculate(operandStack, operatorStack, &operandTop, &operatorTop);
            }
            operatorStack[++operatorTop] = op;
        }
    }

    while(operatorTop != -1) {
        popOutAndCalculate(operandStack, operatorStack, &operandTop, &operatorTop);
    }

    return operandStack[0];
}
*/