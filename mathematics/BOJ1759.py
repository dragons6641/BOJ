import sys;
import itertools;

VOWEL_LIST = ['a', 'e', 'i', 'o', 'u'];

# sys.stdin = open("input1.txt", 'r');

(L, C) = map(int, sys.stdin.readline().split());
inputList = sorted(sys.stdin.readline().split());

# print(L, C);
# print(inputList);

combinationList = list(itertools.combinations(inputList, L));

# print(combinationList);

for curCombination in combinationList:
    consonantCnt = 0;
    vowelCnt = 0;

    for curIdx in range(L):
        if (curCombination[curIdx] in VOWEL_LIST):
            vowelCnt += 1;
        else:
            consonantCnt += 1;

    if ((vowelCnt >= 1) and (consonantCnt >= 2)):
        print(''.join(curCombination));
