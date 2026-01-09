char* removeOuterParentheses(char* s) {
    int len = strlen(s);
    int depth = 0;
    int j = 0;
    char* result = (char*)malloc(len+1);

    for(int i=0; i<len; i++) {
        printf("the s[%d] is %c\n", i, s[i]);
        if(s[i] == '(') {
            if(depth >= 1) {
                result[j] = s[i];
                j++;
            }
            depth++;
        } else {
            depth--;
            if(depth >= 1) {
                result[j] = s[i];
                j++;
            }
        }
    }

    result[j++] = '\0';

    return result;
}