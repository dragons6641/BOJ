import sys;

ALPHABET_LIST = [3, 2, 1, 2, 4, 3, 1, 3, 1, 1, 3, 1, 3, 2, 1, 2, 2, 2, 1, 2, 1, 1, 1, 2, 2, 1];
BIAS = ord("A");
DIGIT = 2;
MOD = 10;

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');
# sys.stdin = open("input3.txt", 'r');

(N, M) = map(int, sys.stdin.readline().split());
(A, B) = sys.stdin.readline().split();

# print(N, M);
# print(A, B);

(idxA, idxB) = (0, 0);
(lenA, lenB) = (len(A), len(B));
compatibilityStr = '';

while ((idxA < lenA) and (idxB < lenB)):
    compatibilityStr += A[idxA];
    idxA += 1;
    compatibilityStr += B[idxB];
    idxB += 1;

while (idxA < lenA):
    compatibilityStr += A[idxA];
    idxA += 1;

while (idxB < lenB):
    compatibilityStr += B[idxB];
    idxB += 1;

compatibilityList = [ALPHABET_LIST[ord(curCh) - BIAS] for curCh in compatibilityStr];

while (len(compatibilityList) > DIGIT):
    for curIdx in range(len(compatibilityList) - 1):
        compatibilityList[curIdx] = (compatibilityList[curIdx] + compatibilityList[curIdx + 1]) % MOD;

    compatibilityList.pop();

# print(compatibilityStr);
# print(compatibilityList);

if (compatibilityList[0] == 0):
    compatibilityList[0] = '';

print(''.join(map(str, compatibilityList)) + '%');
