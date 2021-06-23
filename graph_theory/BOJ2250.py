import sys;
import collections;

MAX_N = 10000;
NONE_VAL = -1;

class TreeNode(object):
    def __init__(self, val = 0, row = 0, col = 0, left = None, right = None) -> None:
        self.val = val;
        self.row = row;
        self.col = col;
        self.left = left;
        self.right = right;

        return None;

    def printTreeNode(self) -> None:
        print(self.val, self.row, self.col, self.left, self.right);

        return None;

def bfs(startNode : int) -> bool:
    dq = collections.deque([startNode]);
    isVisitedList = [False for _ in range(N + 1)];
    isVisitedList[startNode] = True;

    while (dq):
        curNode = dq.popleft();

        for nextNode in inputDict[curNode]:
            if ((nextNode == NONE_VAL) or (isVisitedList[nextNode])):
                continue;

            isVisitedList[nextNode] = True;
            dq.append(nextNode);

    return (not (False in isVisitedList[1 : ]));

def makeTree(curVal : int, curLeft : int, curRight : int, curRow : int) -> TreeNode:
    curNode = TreeNode(val = curVal, row = curRow);

    # print(curVal, curLeft, curRight, curRow);

    if (curLeft != NONE_VAL):
        curNode.left = makeTree(curLeft, inputDict[curLeft][0], inputDict[curLeft][1], curRow + 1);

    if (curRight != NONE_VAL):
        curNode.right = makeTree(curRight, inputDict[curRight][0], inputDict[curRight][1], curRow + 1);

    return curNode;

def inOrder(curNode : TreeNode) -> None:
    if (not curNode):
        return None;

    global curCol;

    inOrder(curNode.left);

    curCol += 1;
    curNode.col = curCol;

    if (curNode.row in colDict.keys()):
        colDict[curNode.row][0] = min(colDict[curNode.row][0], curNode.col);
        colDict[curNode.row][1] = max(colDict[curNode.row][1], curNode.col);
    else:
        colDict[curNode.row] = [curNode.col, curNode.col];

    inOrder(curNode.right);

    return None;

# sys.stdin = open("input1.txt", 'r');

inputDict = dict();

N = int(input());

for _ in range(N):
    val, left, right = map(int, input().split());
    inputDict[val] = (left, right);

# print(inputDict);

minRow = MAX_N;
maxWidth = 0;
rootVal = 0;
curCol = 0;
colDict = dict();

for curKey in inputDict.keys():
    if (bfs(curKey)):
        rootVal = curKey;

        break;

# print(rootVal);

root = makeTree(rootVal, inputDict[rootVal][0], inputDict[rootVal][1], 1);

inOrder(root);

# print(colDict);

for curRow in colDict.keys():
    curWidth = colDict[curRow][1] - colDict[curRow][0] + 1;

    if (maxWidth < curWidth):
        minRow = curRow;
        maxWidth = curWidth;
    elif (maxWidth == curWidth) and (minRow > curRow):
        minRow = curRow;

print(minRow, maxWidth);
