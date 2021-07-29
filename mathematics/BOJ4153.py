import sys;

# sys.stdin = open("input1.txt", 'r');

while (True):
    edgeList = sorted(list(map(int, sys.stdin.readline().split())));

    # print(edgeList);

    if (edgeList == [0, 0, 0]):
        break;

    print('right' if ((edgeList[0] ** 2) + (edgeList[1] ** 2) == (edgeList[2] ** 2)) else 'wrong');
