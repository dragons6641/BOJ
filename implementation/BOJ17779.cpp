/*
17779 게리맨더링 2
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_DIVIDE 5
#define MAX_N 20
#define MAX_M 100
#define MAX_INT 21e8

struct Node
{
	int r;
	int c;
};

int N;
int ans = MAX_INT;
// 최소 인구수
int minCnt = MAX_INT;
// 최대 인구수
int maxCnt = 0;
// 전체 인구수
int totalCnt = 0;
// 선거구 인구수 목록
// 1부터 사용
int cntList[MAX_DIVIDE + 1] = { 0, };
// 선택한 점 목록
// 1부터 사용
Node selectList[MAX_DIVIDE] = { {0, 0}, };
// 입력
int map[MAX_N][MAX_N] = { 0, };
// 선거구 나눈 결과
int divide[MAX_N][MAX_N] = { 0, };

void input(void)
{
	scanf("%d", &N);

	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			scanf("%d", &map[r][c]);

			totalCnt += map[r][c];
		}
	}

	return;
}

void init(void)
{
	minCnt = MAX_INT;
	maxCnt = 0;

	for (int i = 1; i <= MAX_DIVIDE; i++)
	{
		cntList[i] = 0;
	}

	/*
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			divide[r][c] = MAX_DIVIDE;
		}
	}
	*/

	return;
}

void calc()
{
	// 5번 선거구
	cntList[MAX_DIVIDE] = totalCnt;

	for (int i = 1; i < MAX_DIVIDE; i++)
	{
		cntList[MAX_DIVIDE] -= cntList[i];
	}

	for (int i = 1; i <= MAX_DIVIDE; i++)
	{
		if (minCnt > cntList[i])
		{
			minCnt = cntList[i];
		}

		if (maxCnt < cntList[i])
		{
			maxCnt = cntList[i];
		}
	}

	if (ans > (maxCnt - minCnt))
	{
		ans = (maxCnt - minCnt);
	}

	return;
}

void select()
{
	// 1번 선거구
	for (int r = 0; r < selectList[2].r; r++)
	{
		for (int c = 0; c <= selectList[1].c; c++)
		{
			if (r + c < selectList[1].r + selectList[1].c)
			{
				divide[r][c] = 1;
				cntList[1] += map[r][c];
			}
		}
	}

	// 2번 선거구
	for (int r = 0; r <= selectList[3].r; r++)
	{
		for (int c = selectList[1].c + 1; c < N; c++)
		{
			if (c - r > selectList[1].c - selectList[1].r)
			{
				divide[r][c] = 2;
				cntList[2] += map[r][c];
			}
		}
	}

	// 3번 선거구
	for (int r = selectList[2].r; r < N; r++)
	{
		for (int c = 0; c < selectList[4].c; c++)
		{
			if (r - c > selectList[4].r - selectList[4].c)
			{
				divide[r][c] = 3;
				cntList[3] += map[r][c];
			}
		}
	}

	// 4번 선거구
	for (int r = selectList[3].r + 1; r < N; r++)
	{
		for (int c = selectList[4].c; c < N; c++)
		{
			if (r + c > selectList[4].r + selectList[4].c)
			{
				divide[r][c] = 4;
				cntList[4] += map[r][c];
			}
		}
	}

	calc();

	return;
}

void solve()
{
	// 1. (r, c)
	// 2. (r + a, c - a)
	// 3. (r + b, c + b)
	// 4. (r + a + b, c - a + b)

	// boundary
	// r : (r ~~~ r + a + b)
	// c : (c - a ~~~ c + b)
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			for (int a = 1; a < N; a++)
			{
				if (r + a >= N)
				{
					break;
				}

				if (c - a < 0)
				{
					break;
				}

				for (int b = 1; b < N; b++)
				{
					if (r + a + b >= N)
					{
						break;
					}

					if (c + b >= N)
					{
						break;
					}

					// 좌표 기록
					selectList[1] = { r, c };
					selectList[2] = { r + a, c - a };
					selectList[3] = { r + b, c + b };
					selectList[4] = { r + a + b, c - a + b };

					// int debug = 1;

					init();

					select();
				}
			}
		}
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);

	setbuf(stdout, NULL);

	input();

	solve();

	printf("%d\n", ans);

	return 0;
}
