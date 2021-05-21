/*
A4 색종이(고)
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

/*
#define MAX_N 100
#define MAX_M 10
#define MAX_R 100
#define MAX_C 100

int map[MAX_R][MAX_C] = { 0, };

void input(void)
{
	int N;
	int R;
	int C;

	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%d %d", &C, &R);
	}

	return;
}

int main(void)
{
	freopen("input1.txt", "r", stdin);

	return 0;
}
*/

#define MAX_N 100
#define LENGTH 10

int paper[MAX_N + 10][MAX_N + 10] = { 0, }; // 테스트 케이스 여러개면 초기화 필요

void fillPaper(int sr, int sc, int er, int ec)
{
	for (register int r = sr; r < er; r++)
	{
		for (register int c = sc; c < ec; c++)
		{
			paper[r][c] = 1;
		}
	}

	return;
}

void inputData(void)
{
	int N;
	int sr;
	int sc;

	scanf("%d", &N);

	for (register int i = 1; i <= N; i++)
	{
		scanf("%d %d", &sc, &sr);

		fillPaper(sr, sc, sr + LENGTH, sc + LENGTH);
	}

	return;
}

int isPossible(int sr, int sc, int er, int ec)
{
	for (register int r = sr; r <= er; r++)
	{
		for (register int c = sc; c <= ec; c++)
		{
			if (paper[r][c] == 0) 
			{
				return 0; // 불가능
			}
		}
	}

	return 1; // 직사각형 가능
}

int solveN6(void)
{
	int maxArea = 100;

	for (int sr = 0; sr < MAX_N; sr++) // 좌상단 세로 좌표
	{
		for (int sc = 0; sc < MAX_N; sc++) // 좌상단 가로 좌표
		{
			if (paper[sr][sc] == 0)
			{
				continue; // 색종이 안 붙어있으므로 skip
			}

			for (int er = sr + 1; er < MAX_N; er++) // 우하단 세로 좌표
			{
				for (int ec = sc + 1; ec < MAX_N; ec++) // 우하단 가로 좌표
				{
					if (paper[er][ec] == 0)
					{
						break;
					}

					int area = (er - sr + 1) * (ec - sc + 1);

					if (maxArea >= area)
					{
						continue;
					}

					if (isPossible(sr, sc, er, ec) == 0)
					{
						break;
					}

					maxArea = area;
				}
			}
		}
	}

	return maxArea;
}

int solveN3(void)
{
	int maxArea = 100;

	// 1. 배열 정리해서 높이 구하기
	for (int c = 0; c < MAX_N; c++) // 가로
	{
		for (int r = 1; r < MAX_N; r++) // 세로
		{
			if (paper[r][c] == 0)
			{
				continue;
			}

			paper[r][c] += paper[r - 1][c];
		}
	}

	// 2. 최대 넓이 구하기
	for (int b = 1; b < MAX_N; b++)
	{
		for (int s = 0; s < MAX_N; s++)
		{
			int h = MAX_N + 1; // 최소 높이를 구해야 하므로 올 수 없는 큰 값

			for (int k = s; k < MAX_N; k++)
			{
				if (h > paper[b][k])
				{
					h = paper[b][k];
				}

				if (h == 0)
				{
					break;
				}

				int area = h * (k - s + 1);

				if (maxArea < area)
				{
					maxArea = area;
				}
			}
		}
	}

	return maxArea;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	inputData();

	// int ans = solveN6();
	int ans = solveN3();

	printf("%d\n", ans);

	return 0;
}
