bool isValid(char* s) {
    int top = 0;
    int len = strlen(s);

    if(len % 2 != 0) return false;

    char* stack = malloc(len);

    for(int i=0; i<len; i++) {
        if(s[i] == '(') stack[top++] = ')';
        else if(s[i] == '[') stack[top++] = ']';
        else if(s[i] == '{') stack[top++] = '}';
        else {
            if(top == 0 || s[i] != stack[--top]) {
                free(stack);
                return false;
            }
        }
    }

    if(top != 0) {
        free(stack);
        return false;
    }

    free(stack);
    return true;






















    /*
    int top = 0;
    int len = strlen(s);

    if((len % 2) != 0) return false;

    char* stack = (char*)malloc(len);

    for(int i = 0; i < len; i++) {
        if( s[i] == '(' || s[i] == '[' || s[i] == '{' ) {
            stack[top] = s[i];
            top++;
        } else {
            if(top == 0) {
                free(stack);
                return false;
            }
            if( s[i] == ')' && stack[top-1] == '(') {
                top--;
            } else if( s[i] == ']' && stack[top-1] == '[') {
                top--;
            } else if( s[i] == '}' && stack[top-1] == '{') {
                top--;
            } else {
                free(stack);
                return false;
            }
        }
    }

    if(top != 0) return false;

    free(stack);

    return true;
    */
}