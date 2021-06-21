import sys;

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');

N, M = map(int, input().split());
inputList = sorted(list(map(int, input().split())));
answer = 0;
curSum = 0;

# print(N, M);
# print(inputList);

for idx1 in range(N):
    num1 = inputList[idx1];
    curSum += num1;

    for idx2 in range(idx1 + 1, N):
        num2 = inputList[idx2];
        curSum += num2;

        for idx3 in range(N - 1, idx2, -1):
            # print(idx1, idx2, idx3);

            num3 = inputList[idx3];
            curSum += num3;

            if (curSum < M):
                answer = max(answer, curSum);
                curSum -= num3;

                break;
            elif (curSum > M):
                curSum -= num3;

                continue;
            else:
                print(M);

                sys.exit(0);

        curSum -= num2;

    curSum -= num1;

print(answer);
