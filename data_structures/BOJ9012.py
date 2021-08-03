import sys;

def checkValid(PS : str) -> None:
    stack = [];

    for curParenthesis in PS:
        if (curParenthesis == '('):
            stack.append(curParenthesis);
            continue;

        if (not stack):
            print("NO");
            return;

        stack.pop();

    print("YES" if (not stack) else "NO");
    return;

# sys.stdin = open("input1.txt", 'r')
# sys.stdin = open("input2.txt", 'r')

T = int(input());

for testcase in range(T):
    checkValid(input());
