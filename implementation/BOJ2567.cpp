/*
A1 색종이(중)
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 100
#define MAX_R 100
#define MAX_C 100
#define MAX_DIR 4
#define MAX_LENGTH 10

int N;
int A;
int B;
int ans = 0;
int directR[MAX_DIR] = { -1, 1, 0, 0 };
int directC[MAX_DIR] = { 0, 0, -1, 1 };
int map[MAX_R + 1][MAX_C + 1] = { 0, };

void input(void)
{
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%d %d", &A, &B);

		for (int r = A; r < A + MAX_LENGTH; r++)
		{
			for (int c = B; c < B + MAX_LENGTH; c++)
			{
				map[r][c] = 1;
			}
		}

		int debug = 1;
	}

	return;
}

void solve(void)
{
	for (int r = 0; r <= MAX_R; r++)
	{
		for (int c = 0; c <= MAX_C; c++)
		{
			for (int d = 0; d < MAX_DIR; d++)
			{
				// 현재 칸은 칠해져 있어야 함
				if (map[r][c] == 0)
				{
					continue;
				}

				int dr = r + directR[d];
				int dc = c + directC[d];

				if ((dr < 0) || (dc < 0) || (dr > MAX_R) || (dc > MAX_C))
				{
					continue;
				}

				// 인접한 칸이 칠해져 있지 않다면
				if (map[dr][dc] == 0)
				{
					// 경계선이므로 추가
					ans++;
				}
			}
		}
	}
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	// setbuf(stdout, NULL);

	input();

	solve();

	printf("%d\n", ans);

	return 0;
}
