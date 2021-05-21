/*
Problem C 화염에서 탈출
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

struct Data
{
	int r;
	int c;
	int lev;
};

const int LM = 55;
const int INF = LM * LM;
int R;
int C;
int timeMap[LM][LM];
int sr;
int sc;
int er;
int ec;
int fr;
int re;
int dr[] = {-1, 1, 0, 0};
int dc[] = { 0, 0, -1, 1 };
Data que[INF];

void push(int r, int c, int lev)
{
	if (timeMap[r][c] <= lev)
	{
		return;
	}

	que[re++] = { r, c, lev };
	timeMap[r][c] = lev;

	return;
}

int bfs(void)
{
	while (fr < re)
	{
		Data t = que[fr++];

		if ((t.r == er) && (t.c == ec))
		{
			return t.lev;
		}

		for (register int d = 0; d < 4; d++)
		{
			push(t.r + dr[d], t.c + dc[d], t.lev + 1);
		}
	}

	return INF;
}

void inputData(void)
{
	char ch;

	scanf("%d %d", &R, &C);

	for (register int r = 1; r <= R; r++)
	{
		for (register int c = 1; c <= C; c++)
		{
			scanf(" %c", &ch);

			timeMap[r][c] = INF;

			if (ch == 'X')
			{
				timeMap[r][c] = 0;
			}
			else if (ch == 'D')
			{
				timeMap[r][c] = 0; // ****
				er = r;
				ec = c;
			}
			else if (ch == 'S')
			{
				sr = r;
				sc = c;
			}
			else if (ch == '*')
			{
				push(r, c, 0);
			}
		}
	}
	
	return;
}

void init(void)
{
	timeMap[er][ec] = INF; // ****
	fr = 0;
	re = 0;
	que[re++] = { sr, sc, 0 };

	return;
}

void printAns(int ret)
{
	if (ret == INF)
	{
		puts("KAKTUS");
	}
	else
	{
		printf("%d\n", ret);
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);
	// freopen("input4.txt", "r", stdin);

	inputData();

	bfs();

	init();

	int ret = bfs();

	printAns(ret);

	return 0;
}
