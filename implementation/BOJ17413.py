import sys;

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');
# sys.stdin = open("input3.txt", 'r');
# sys.stdin = open("input4.txt", 'r');
# sys.stdin = open("input5.txt", 'r');
# sys.stdin = open("input6.txt", 'r');
# sys.stdin = open("input7.txt", 'r');
# sys.stdin = open("input8.txt", 'r');

S = input();

# print(S);

answer = '';
curWord = '';
isTag = False;

for curCh in S:
    if (curCh == ' '):
        if (isTag):
            curWord += ' ';
        else:
            answer += (curWord[ : : -1] + ' ');
            curWord = '';
    elif (curCh == '<'):
        answer += (curWord[ : : -1]);
        curWord = '<';
        isTag = True;
    elif (curCh == '>'):
        answer += (curWord + '>');
        curWord = '';
        isTag = False;
    else:
        curWord += curCh;

answer += curWord[ : : -1];

print(answer);
