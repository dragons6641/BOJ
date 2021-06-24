import sys;

class BrickNode(object):
    def __init__(self, idx = 0, area = 0, height = 0, weight = 0) -> None:
        self.num = idx;
        self.area = area;
        self.height = height;
        self.weight = weight;

        return None;

    def printBrickNode(self) -> None:
        print('num :', self.num, 'area :', self.area, 'height :', self.height, 'weight :', self.weight);

        return None;

# sys.stdin = open("input1.txt", 'r');

answerList = [];
brickList = [BrickNode()];

N = int(sys.stdin.readline());

for num in range(1, N + 1):
    area, height, weight = map(int, sys.stdin.readline().split());
    brickList.append(BrickNode(num, area, height, weight));

dp = [0 for k in range(N + 1)];
brickList.sort(key = lambda k : k.area);

# for curBrick in brickList:
#     curBrick.printBrickNode();

for i in range(1, N + 1):
    for j in range(i):
        # print(i, j);

        if (brickList[i].weight > brickList[j].weight):
            # brickList[i].printBrickNode();
            # brickList[j].printBrickNode();
            # print();

            dp[i] = max(dp[i], dp[j] + brickList[i].height);

maxHeight = max(dp);
curIdx = dp.index(maxHeight);

while (curIdx > 0):
    if (dp[curIdx] == maxHeight):
        answerList.append(str(brickList[curIdx].num));
        maxHeight -= brickList[curIdx].height;

    curIdx -= 1;

# print(dp);
# print(curIdx);
# print(answerList);

print(len(answerList));
print('\n'.join(answerList[ : : -1]));
