import sys;

# sys.stdin = open("input1.txt", 'r');

testCase = int(input());

for t in range(testCase):
    """
    inputStr = input();
    cursorIdx = 0;
    passwordStr = [];

    for inputCh in inputStr:
        if (inputCh == '<'):
            cursorIdx = max(cursorIdx - 1, 0);
        elif (inputCh == '>'):
            cursorIdx = min(cursorIdx + 1, len(passwordStr));
        elif (inputCh == '-'):
            passwordStr = passwordStr[ : cursorIdx - 1] + passwordStr[cursorIdx : ];
            cursorIdx -= 1;
        else:
            passwordStr = passwordStr[ : cursorIdx] + [inputCh] + passwordStr[cursorIdx : ];
            cursorIdx += 1;

        # print(inputCh, cursorIdx, passwordStr);

    print(''.join(passwordStr));
    """

    inputStr = input();
    leftStack = [];
    rightStack = [];

    for inputCh in inputStr:
        if (inputCh == '<'):
            if (leftStack):
                rightStack.append(leftStack.pop());
        elif (inputCh == '>'):
            if (rightStack):
                leftStack.append(rightStack.pop());
        elif (inputCh == '-'):
            if (leftStack):
                leftStack.pop();
        else:
            leftStack.append(inputCh);

    print(''.join(leftStack), end = '');
    print(''.join(reversed(rightStack)));
