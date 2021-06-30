import sys;

RSP_DICT = {'R' : 0, 'S' : 1, 'P' : 2};
MOD = 3;

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');
# sys.stdin = open("input3.txt", 'r');

(ML, MR, TL, TR) = sys.stdin.readline().split();

# print(ML, MR, TL, TR);

if (ML == MR):
    if (TL == TR):
        result = (RSP_DICT[ML] - RSP_DICT[TL] + MOD) % MOD;

        if (result == 2):
            print('MS');
        elif (result == 1):
            print('TK');
        else:
            print('?');
    else:
        resultL = (RSP_DICT[ML] - RSP_DICT[TL] + MOD) % MOD;
        resultR = (RSP_DICT[MR] - RSP_DICT[TR] + MOD) % MOD;

        if ((resultL == 1) or (resultR == 1)):
            print('TK');
        else:
            print('?');
else:
    if (TL == TR):
        resultL = (RSP_DICT[ML] - RSP_DICT[TL] + MOD) % MOD;
        resultR = (RSP_DICT[MR] - RSP_DICT[TR] + MOD) % MOD;

        if ((resultL == 2) or (resultR == 2)):
            print('MS');
        else:
            print('?');
    else:
        print('?');
