import sys;
import math;

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');

N = int(sys.stdin.readline());
solutionList = sorted(list(map(int, sys.stdin.readline().split())));

# print(solutionList);

answer = [];
minValue = math.inf;

for idx1 in range(N - 2):
    for idx2 in range(idx1 + 1, N - 1):
        # print(idx1, idx2);

        (left, right) = (idx2 + 1, N - 1);

        while (left <= right):
            mid = (left + right) // 2;
            curValue = solutionList[idx1] + solutionList[idx2] + solutionList[mid];
            absCurValue = abs(curValue);

            if (minValue > absCurValue):
                answer = [str(solutionList[idx1]), str(solutionList[idx2]), str(solutionList[mid])];
                minValue = absCurValue;

            # print(idx1, idx2, mid, minValue);

            if (curValue < 0):
                left = mid + 1;
            elif (curValue > 0):
                right = mid - 1;
            else:
                print(' '.join(answer));
                print();
                sys.exit(0);

print(' '.join(answer));
print();
