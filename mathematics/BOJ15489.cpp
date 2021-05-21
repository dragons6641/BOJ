/*
Pro입문 1일차 Problem A 파스칼 삼각형

- F10 : 한 줄씩 실행(Trace)

- for문 설계 방법
1. 몇 중 for문인지
2. r과 c의 범위
3. if문 조건은 무엇인지
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 30
#define MAX_M 3
// #define MAX_M 30
#define MAX_R 30
#define MAX_C 30
#define MAX_W 30

int N;
int M;
int R;
int C;
int W;
int map[MAX_N + 2][MAX_N + 2] = { 0, };

void solve_1(void)
{
	// 종류 1
	map[0][0] = 1;

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			map[r][c] = map[r - 1][c - 1] + map[r - 1][c];
		}
	}

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= r; c++)
		{
			printf("%d ", map[r][c]);
		}

		printf("\n");
	}

	return;
}

void solve_2(void)
{
	// 종류 2
	map[N + 1][0] = 1;

	for (int r = N; r >= 1; r--)
	{
		for (int c = 1; c <= N; c++)
		{
			map[r][c] = map[r + 1][c - 1] + map[r + 1][c];
		}
	}

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c < r; c++)
		{
			printf(" ");
		}

		for (int c = 1; c <= N - r + 1; c++)
		{
			printf("%d ", map[r][c]);
		}

		printf("\n");
	}

	return;
}

void solve_3(void)
{
	// 종류 3
	map[N + 1][N + 1] = 1;

	for (int r = N; r >= 1; r--)
	{
		for (int c = N; c >= 1; c--)
		{
			map[r][c] = map[r + 1][c + 1] + map[r][c + 1];
		}
	}

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= r; c++)
		{
			printf("%d ", map[r][c]);
		}

		printf("\n");
	}

	return;
}

void solve_4(void)
{
	int sum = 0;

	// 종류 1
	map[0][0] = 1;

	for (int r = 1; r <= MAX_N; r++)
	{
		for (int c = 1; c <= MAX_N; c++)
		{
			map[r][c] = map[r - 1][c - 1] + map[r - 1][c];
		}
	}

	int debug = 1;

	for (int r = R; r < R + W; r++)
	{
		for (int c = C; (r - c) >= (R - C); c++)
		{
			sum += map[r][c];
		}
	}

	printf("%d\n", sum);

	return;
}

void solve_5(void)
{
	// 종류 1
	map[0][0] = 1;

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			map[r][c] = map[r - 1][c - 1] + map[r - 1][c];
		}
	}

	printf("%d\n", map[N][M]);

	return;
}

int main(void)
{
	/*
	scanf("%d %d", &N, &M);

	// printf("N : %d, M : %d\n", N, M);

	switch (M)
	{
		case 1:
		{
			solve_1();

			break;
		}
		case 2:
		{
			solve_2();

			break;
		}
		case 3:
		{
			solve_3();

			break;
		}
		default:
		{
			break;
		}
	}
	*/

	///*
	scanf("%d %d %d", &R, &C, &W);

	solve_4();
	//*/

	/*
	scanf("%d %d", &N, &M);

	solve_5();
	*/

	return 0;
}
