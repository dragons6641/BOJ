import sys;

sys.setrecursionlimit(10 ** 5);

def preOrder(inOrderStartIdx : int, inOrderEndIdx : int, postOrderStartIdx : int, postOrderEndIdx : int) -> list:
    if (postOrderStartIdx > postOrderEndIdx):
        # print(postOrderList[postOrderStartIdx], end = ' ');

        return;
        # return [postOrderList[postOrderStartIdx]];

    rootIdx = inOrderList.index(postOrderList[postOrderEndIdx]);

    # print(inOrderStartIdx, inOrderEndIdx, postOrderStartIdx, postOrderEndIdx, rootIdx);
    # print(inOrderList[inOrderStartIdx : inOrderEndIdx + 1], postOrderList[postOrderStartIdx : postOrderEndIdx + 1]);
    print(inOrderList[rootIdx], end = ' ');

    if (rootIdx == 0):
        # print("CASE 1");

        preOrder(inOrderStartIdx + 1, inOrderEndIdx, postOrderStartIdx, postOrderEndIdx - 1);

        return;
        # return ([inOrderList[rootIdx]] + preOrder(inOrderStartIdx + 1, inOrderEndIdx, postOrderStartIdx, postOrderEndIdx - 1));
    elif (rootIdx == inOrderEndIdx):
        # print("CASE 2");

        preOrder(inOrderStartIdx, inOrderEndIdx - 1, postOrderStartIdx, postOrderEndIdx - 1);

        return;
        # return ([inOrderList[rootIdx]] + preOrder(inOrderStartIdx, inOrderEndIdx - 1, postOrderStartIdx, postOrderEndIdx - 1));

    # print("CASE 3");

    divideIdx = postOrderStartIdx + rootIdx - inOrderStartIdx;
    preOrder(inOrderStartIdx, rootIdx - 1, postOrderStartIdx, divideIdx - 1);
    preOrder(rootIdx + 1, inOrderEndIdx, divideIdx, postOrderEndIdx - 1);

    return;
    # return ([inOrderList[rootIdx]] + preOrder(inOrderStartIdx, rootIdx - 1, postOrderStartIdx, divideIdx - 1) + preOrder(rootIdx + 1, inOrderEndIdx, divideIdx, postOrderEndIdx - 1));

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');
# sys.stdin = open("input3.txt", 'r');
# sys.stdin = open("input4.txt", 'r');
# sys.stdin = open("input5.txt", 'r');
# sys.stdin = open("input6.txt", 'r');
# sys.stdin = open("input7.txt", 'r');
# sys.stdin = open("input8.txt", 'r');
# sys.stdin = open("input9.txt", 'r');

N = int(sys.stdin.readline());
inOrderList = list(sys.stdin.readline().split());
postOrderList = list(sys.stdin.readline().split());

# print(inOrderList);
# print(postOrderList);

preOrder(0, N - 1, 0, N - 1);

print();
# print(' '.join(preOrder(0, N - 1, 0, N - 1)));
