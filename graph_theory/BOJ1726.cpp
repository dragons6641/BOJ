/*
Problem D 로봇
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

struct Data
{
	int r;
	int c;
	int d;
	int lev;
};

const int LM = 105;
int M;
int N;
int sr;
int sc;
int sd;
int er;
int ec;
int ed;
int fr;
int re;
int dr[] = { 0, 0, 0, 1, -1 };
int dc[] = { 0, 1, -1, 0, 0 };
int map[LM][LM];
int visit[LM][LM][5];
Data que[LM * LM * 5];

void inputData(void)
{
	scanf("%d %d", &M, &N);

	for (register int r = 1; r <= M; r++)
	{
		for (register int c = 1; c <= N; c++)
		{
			scanf("%d", map[r] + c); // &Map[r][c]

			// map[r][c] = 1 - map[r][c];
			map[r][c] = !map[r][c];
		}
	}

	scanf("%d %d %d", &sr, &sc, &sd);
	scanf("%d %d %d", &er, &ec, &ed);

	return;
}

int push(int r, int c, int d, int lev)
{
	if (map[r][c] == 0)
	{
		return -1;
	}

	if (visit[r][c][d] == 1)
	{
		return 0;
	}

	visit[r][c][d] = 1;
	que[re++] = { r, c, d, lev };

	return 0;
}

int bfs(void)
{
	while (fr < re)
	{
		Data t = que[fr++];

		if ((t.r == er) && (t.c == ec) && (t.d == ed))
		{
			return t.lev;
		}

		// Go K
		for (register int k = 1; k <= 3; k++)
		{
			int rv = push(t.r + (dr[t.d] * k), t.c + (dc[t.d] * k), t.d, t.lev + 1);

			if (rv < 0)
			{
				break;
			}
		}

		// Change Dir
		int nd = (t.d <= 2) ? 3 : 1;

		push(t.r, t.c, nd, t.lev + 1);
		push(t.r, t.c, nd + 1, t.lev + 1);
	}

	return 0;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	inputData();

	push(sr, sc, sd, 0);

	printf("%d\n", bfs());

	return 0;
}
