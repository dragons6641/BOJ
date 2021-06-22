import sys;

# sys.stdin = open("input1.txt", 'r');

N = int(input());
locationList = sorted([list(map(int, input().split())) for _ in range(N)], key = lambda k : (k[0], k[1]));

# print(N);
# print(coordList);

for curlocation in locationList:
    print(' '.join(map(str, curlocation)));
