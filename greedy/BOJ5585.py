import sys;

PAYMENT = 1000;
COIN_LIST = [500, 100, 50, 10, 5, 1];

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');

change = PAYMENT - int(sys.stdin.readline());

answer = 0;
coinIdx = 0;

while (change > 0):
    curCoin = COIN_LIST[coinIdx];

    while (change >= curCoin):
        # print(change, curCoin);

        change -= curCoin;
        answer += 1;

    coinIdx += 1;

print(answer);
