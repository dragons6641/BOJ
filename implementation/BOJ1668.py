import sys;

def solve(heightList : list[int]) -> int:
    answer = 0;
    maxHeight = 0;

    for curHeight in heightList:
        if (maxHeight < curHeight):
            maxHeight = curHeight;
            answer += 1;

    return answer;

# sys.stdin = open("input1.txt", 'r');

N = int(input());
heightList = [int(input()) for _ in range(N)];

# print(N);
# print(inputList);

print(solve(heightList));
print(solve(reversed(heightList)));
