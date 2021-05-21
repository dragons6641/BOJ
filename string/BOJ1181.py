max_length = 50;

word_list = [[] for i in range(max_length + 1)];

n = int(input());

# print(n);

for i in range(n):
    word = input();
    length = len(word);

    if (word not in word_list[length]):
        word_list[length].append(word);

for i in word_list:
    i.sort();

# print(word_list);

for i in range(1, max_length + 1):
    for j in word_list[i]:
        print(j);
