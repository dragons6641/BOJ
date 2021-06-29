import sys;

def pourMilk() -> None:
    milkSum = mixList[src][1] + mixList[dst][1];

    if (milkSum > mixList[dst][0]):
        mixList[src][1] = milkSum - mixList[dst][0];
        mixList[dst][1] = mixList[dst][0];
    else:
        mixList[src][1] = 0;
        mixList[dst][1] = milkSum;

    return None;

COW_CNT = 3;
OPERATION_CNT = 100;

# sys.stdin = open("input1.txt", 'r');

mixList = [list(map(int, sys.stdin.readline().split())) for _ in range(COW_CNT)];

# print(mixList);

src = 0;
dst = 1;

for _ in range(OPERATION_CNT):
    pourMilk();

    src = (src + 1) % COW_CNT;
    dst = (dst + 1) % COW_CNT;

for (curBucket, curMilk) in mixList:
    print(curMilk);
