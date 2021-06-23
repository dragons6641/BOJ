import sys;

ROOT_VAL = 'A';
NONE_VAL = '.'

class TreeNode(object):
    def __init__(self, val = None, left = None, right = None) -> None:
        self.val = val;
        self.left = left;
        self.right = right;

        return None;

    def printTreeNode(self):
        print(self.val, self.left, self.right);

def makeTree(curVal = int, curLeft = str, curRight = str) -> TreeNode:
    curNode = TreeNode(curVal);

    if (curLeft != NONE_VAL):
        curNode.left = makeTree(curLeft, inputDict[curLeft][0], inputDict[curLeft][1]);

    if (curRight != NONE_VAL):
        curNode.right = makeTree(curRight, inputDict[curRight][0], inputDict[curRight][1]);

    return curNode;

def preOrder(curNode : TreeNode) -> None:
    if (not curNode):
        return None;

    print(curNode.val, end = '');
    preOrder(curNode.left);
    preOrder(curNode.right);

    return None;

def inOrder(curNode : TreeNode) -> None:
    if (not curNode):
        return None;

    inOrder(curNode.left);
    print(curNode.val, end='');
    inOrder(curNode.right);

    return None;

def postOrder(curNode : TreeNode) -> None:
    if (not curNode):
        return None;

    postOrder(curNode.left);
    postOrder(curNode.right);
    print(curNode.val, end='');

    return None;

# sys.stdin = open("input1.txt", 'r');

inputDict = dict();

N = int(input());

for _ in range(N):
    val, left, right = input().split();
    inputDict[val] = (left, right);

# print(inputDict);

root = makeTree(ROOT_VAL, inputDict[ROOT_VAL][0], inputDict[ROOT_VAL][1]);

preOrder(root);
print();

inOrder(root);
print();

postOrder(root);
print();
