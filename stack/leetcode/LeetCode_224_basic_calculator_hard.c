int calculate(char* s) {
    int len = strlen(s);
    // 準備一個堆疊來存放 (result, sign)
    // 224 題中，數字、括號交替出現，堆疊深度不超過 len 是一定夠的
    int stack[len]; 
    int top = -1;

    long result = 0;    // 目前累加的結果
    int sign = 1;       // 1 代表正，-1 代表負

    for (int i = 0; i < len; i++) {
        char ch = s[i];

        if (isdigit(ch)) {
            // 1. 解析數字（處理多位數）
            long num = 0;
            while (i < len && isdigit(s[i])) {
                num = num * 10 + (s[i] - '0');
                i++;
            }
            i--; // 回補 i++
            result += num * sign; // 將數字乘以目前的符號加進總結

        } else if (ch == '+') {
            sign = 1; //

        } else if (ch == '-') {
            sign = -1; //

        } else if (ch == '(') {
            // 2. 進入括號：存檔目前的狀態
            stack[++top] = (int)result; // 存入目前的 result
            stack[++top] = sign;        // 存入目前的 sign
            
            // 重置環境開始算括號裡的東西
            result = 0;
            sign = 1;

        } else if (ch == ')') {
            // 3. 結束括號：還原之前的狀態並計算
            int prevSign = stack[top--];   // 彈出括號前的正負號
            int prevResult = stack[top--]; // 彈出括號前的累積結果
            
            // 將括號內的結果(result) 乘以 括號外的符號，再加上 括號外的舊結果
            result = prevResult + (long)prevSign * result;
        }
        // 空白字元 (space) 則會被自動跳過
    }

    return (int)result;
}