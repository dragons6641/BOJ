import sys;

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');

N = int(sys.stdin.readline());
XList = list(map(int, sys.stdin.readline().split()));

XDict = dict(zip(sorted(list(set(XList))), [k for k in range(N)]));

# print(XList);
# print(XDict);

print(' '.join([str(XDict[k]) for k in XList]));
