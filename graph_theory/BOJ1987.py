import sys;

sys.setrecursionlimit(10000);

matrix = [];

ans = 0;

tmp = input().split();

r, c = int(tmp[0]), int(tmp[1]);

# isVisited = [[0 for cols in range(c)] for rows in range(r)]
alphabet_dict = {'A' : 0, 'B' : 0, 'C' : 0, 'D' : 0, 'E' : 0, 'F' : 0, 'G' : 0,
                 'H': 0, 'I': 0, 'J': 0, 'K': 0, 'L': 0, 'M': 0, 'N': 0,
                 'O': 0, 'P': 0, 'Q': 0, 'R': 0, 'S': 0, 'T': 0, 'U': 0,
                 'V': 0, 'W': 0, 'X': 0, 'Y': 0, 'Z': 0}

for i in range(r):
    tmp = list(input());

    matrix.append(tmp);

"""
print(matrix);
# print(isVisited);
print(alphabet_dict);
"""

def dfs(row, col, cnt):
    global ans;

    # isVisited[row][col] = 1;
    alphabet_dict[matrix[row][col]] = 1;

    """
    print(row, col, cnt);
    print(alphabet_dict);
    """

    if (cnt == 26):
        print(26);

        exit(0);

    if (row - 1 >= 0
        # and isVisited[row - 1][col] == 0
        and alphabet_dict[matrix[row - 1][col]] == 0):
        # isVisited[row - 1][col] = 1;
        alphabet_dict[matrix[row - 1][col]] = 1;

        dfs(row - 1, col, cnt + 1);

    if (col - 1 >= 0
        # and isVisited[row][col - 1] == 0
        and alphabet_dict[matrix[row][col - 1]] == 0):
        # isVisited[row][col - 1] = 1;
        alphabet_dict[matrix[row][col - 1]] = 1;

        dfs(row, col - 1, cnt + 1);

    if (row + 1 <= r - 1
        # and isVisited[row + 1][col] == 0
        and alphabet_dict[matrix[row + 1][col]] == 0):
        # isVisited[row + 1][col] = 1;
        alphabet_dict[matrix[row + 1][col]] = 1;

        dfs(row + 1, col, cnt + 1);

    if (col + 1 <= c - 1
        #and isVisited[row][col + 1] == 0
        and alphabet_dict[matrix[row][col + 1]] == 0):
        # isVisited[row][col + 1] = 1;
        alphabet_dict[matrix[row][col + 1]] = 1;

        dfs(row, col + 1, cnt + 1);

    if (cnt > ans):
        ans = cnt;

    # isVisited[row][col] = 0;
    alphabet_dict[matrix[row][col]] = 0;

    return;

dfs(0, 0, 1);

print(ans);
