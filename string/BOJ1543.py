import sys;

# sys.stdin = open("input1.txt", 'r');
# sys.stdin = open("input2.txt", 'r');
# sys.stdin = open("input3.txt", 'r');
# sys.stdin = open("input4.txt", 'r');
# sys.stdin = open("input5.txt", 'r');
# sys.stdin = open("input6.txt", 'r');
# sys.stdin = open("input7.txt", 'r');
# sys.stdin = open("input8.txt", 'r');
# sys.stdin = open("input9.txt", 'r');
# sys.stdin = open("input10.txt", 'r');
# sys.stdin = open("input11.txt", 'r');
# sys.stdin = open("input12.txt", 'r');

"""
inputDocument = sys.stdin.readline().replace(" ", "_");
inputWord = sys.stdin.readline().replace(" ", "_");

print(inputDocument);
print(inputWord);

answer = 0;
curIdx = 0;
inputDocumentLen = len(inputDocument);
inputWordLen = len(inputWord);

while (curIdx < inputDocumentLen):
    findIdx = inputDocument.find(inputWord, curIdx);

    # print(curIdx, findIdx);

    if (findIdx == -1):
        break;

    answer += 1;
    curIdx = findIdx + inputWordLen;

print(answer);
"""

inputDocument = input();
inputWord = input();

print(inputDocument.count(inputWord));
