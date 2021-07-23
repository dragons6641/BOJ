import sys;

OPERATOR_DICT = {'+' : 2, '-' : 2, '*' : 3, '/' : 3};

# sys.stdin = open("input1.txt", 'r');    # ABC+*
# sys.stdin = open("input2.txt", 'r');    # AB*C*D*
# sys.stdin = open("input3.txt", 'r');    # AB+C+D+
# sys.stdin = open("input4.txt", 'r');    # ABC*DE-G**+

(infixStr, postfixStr) = (input(), "");

stack = [];

for curCh in infixStr:
    if (curCh == '('):
        stack.append(curCh);
    elif (curCh == ')'):
        while (stack[-1] != '('):
            postfixStr += stack.pop();

        stack.pop();
    elif (curCh in OPERATOR_DICT):
        while ((stack) and (stack[-1] != '(') and (OPERATOR_DICT[curCh] <= OPERATOR_DICT[stack[-1]])):
            postfixStr += stack.pop();

        stack.append(curCh);
    else:
        postfixStr += curCh;

    # print(curCh, stack);

while (stack):
    postfixStr += stack.pop();

print(postfixStr);
