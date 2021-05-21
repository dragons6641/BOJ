ban_list = ['C', 'A', 'M', 'B', 'R', 'I', 'D', 'G', 'E'];

word = list(input());

# print(word);

for i in range(len(word)):
    if (word[i] in ban_list):
        word[i] = ' ';

for i in word:
    if (i != ' '):
        print(i, end = '');
