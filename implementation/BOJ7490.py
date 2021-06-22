import sys;

DIGIT = 10;

def dfs(outputStr : str, prevOperation : str, calcResult : int, prevNum : int, curDepth : int) -> None:
    if (curDepth == N):
        calcResult = (calcResult + prevNum) if (prevOperation == "+") else (calcResult - prevNum);

        if (calcResult == 0):
            print(outputStr);

        return None;

    nextDepth = curDepth + 1;

    dfs(outputStr + " " + str(nextDepth), prevOperation, calcResult, (prevNum * DIGIT) + nextDepth, nextDepth);
    dfs(outputStr + "+" + str(nextDepth), "+", (calcResult + prevNum) if (prevOperation == "+") else (calcResult - prevNum), nextDepth, nextDepth);
    dfs(outputStr + "-" + str(nextDepth), "-", (calcResult + prevNum) if (prevOperation == "+") else (calcResult - prevNum), nextDepth, nextDepth);

    return None;

# sys.stdin = open("input1.txt", 'r');

testCase = int(sys.stdin.readline());

for t in range(testCase):
    N = int(sys.stdin.readline());

    dfs("1", "+", 0, 1, 1);

    print();
