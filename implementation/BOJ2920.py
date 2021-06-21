MAX_NUM = 8;
ASCENDING_LIST = [_ for _ in range(1, MAX_NUM + 1)];
DESCENDING_LIST = [_ for _ in range(MAX_NUM, 0, -1)];

import sys;

answer = "";

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');
# sys.stdin = open("input3.txt", 'r');

inputList = list(map(int, input().split()));

# print(ASCENDING_LIST);
# print(DESCENDING_LIST);
# print(inputList);

if (inputList == ASCENDING_LIST):
    answer = "ascending";
elif (inputList == DESCENDING_LIST):
    answer = "descending";
else:
    answer = "mixed";

print(answer);
