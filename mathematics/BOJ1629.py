import sys;

# sys.stdin = open("input1.txt", 'r');    # 4
# sys.stdin = open("input2.txt", 'r');    # 0
# sys.stdin = open("input3.txt", 'r');    # 99999

(A, B, C) = map(int, sys.stdin.readline().split());

"""
answer = 1;

for k in range(B):
    answer = (answer * A) % C;

print(answer);
"""

"""
binB = bin(B)[2 : ];
curNum = A % C;
answer = (curNum if (binB[-1] == '1') else 1);

# print(binB);

for digitIdx in range(len(binB) - 2, -1, -1):
    print(binB[digitIdx], curNum);

    curNum = (curNum ** 2) % C;

    if (binB[digitIdx] == '1'):
        answer = (answer * curNum) % C;

print(answer);
"""

print(pow(A, B, C));
