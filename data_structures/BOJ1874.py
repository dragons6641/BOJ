import sys;

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');

N = int(input());
inputList = [int(input()) for _ in range(N)];
outputList = ['+'];
inputIdx = 0;
pushNum = 2;
stack = [1];

# print(N);
# print(inputList);

while (pushNum <= N):
    # print(stack);

    if (not stack) or (stack[-1] != inputList[inputIdx]):
        stack.append(pushNum);
        outputList.append('+');
        pushNum += 1;
    else:
        stack.pop();
        outputList.append('-');
        inputIdx += 1;

while (stack):
    if (stack[-1] != inputList[inputIdx]):
        print("NO");

        sys.exit(0);
    else:
        stack.pop();
        outputList.append('-');
        inputIdx += 1;

# print(outputList);

for outputCh in outputList:
    print(outputCh);
