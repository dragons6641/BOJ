import sys;

sys.setrecursionlimit(10000);

def dfs(num):
    for i in range(n):
        if (isVisited[i] == 0 and input_matrix[num][i] == 1):
            isVisited[i] = 1;
            output_matrix[cur][i] = 1;

            """
            print(num, i);
            print(isVisited);
            """

            dfs(i);

    return;

n = int(input());

# print(n);

input_matrix = [];
output_matrix = [[0 for cols in range(n)] for rows in range(n)];
isVisited = [0 for nums in range(n)];

for i in range(n):
    tmp = list(map(int, input().split()));
    input_matrix.append(tmp);

"""
print(input_matrix);
print(output_matrix);
print(isVisited);
"""

for cur in range(n):
    isVisited = [0 for nums in range(n)];

    dfs(cur);

for i in range(n):
    for j in range(n):
        print(output_matrix[i][j], end = ' ');

    print();
