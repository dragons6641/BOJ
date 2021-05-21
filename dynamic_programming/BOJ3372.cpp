#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 100
#define MAX_M 100
#define MAX_K 10
#define START_R 1
#define START_C 1

int N;
// 1부터 사용
int map[MAX_N + 1][MAX_N + 1] = { 0, };
// 1부터 사용
// dp[r][c] : (r, c) 좌표까지 이동할 수 있는 경우의 수
char dp[MAX_N + 1][MAX_N + 1][MAX_M + 2] = { 0, };

int mstrlen(char* str)
{
	register int i;

	for (i = 0; str[i]; i++);

	return i;
}

void mstrcpy(char* dst, char* src)
{
	register int i;

	for (i = 0; src[i]; i++)
	{
		dst[i] = src[i];
	}

	dst[i + 1] = '\0';

	return;
}

// 항상 lenA >= lenB임이 보장됨
void madd(char* a, char* b, char* result, int lenA, int lenB)
{
	if (lenB == 0)
	{
		mstrcpy(result, a);

		return;
	}

	for (register int i = 0; i < lenA; i++)
	{
		if (b[i])
		{
			result[i] = a[i] + b[i] - '0';
		}
		else
		{
			result[i] = a[i];
		}

		if (result[i] > '9')
		{
			result[i] -= 10;

			if (result[i + 1] == '\0')
			{
				result[i + 1] = '1';
				result[i + 2] = '\0';
			}
			else
			{
				result[i + 1]++;
			}
		}
	}

	return;
}

void inputData(void)
{
	scanf("%d", &N);

	for (register int r = 1; r <= N; r++)
	{
		for (register int c = 1; c <= N; c++)
		{
			scanf("%d", &map[r][c]);
		}
	}

	return;
}

void solve(void)
{
	dp[START_R][START_C][0] = '1';
	dp[START_R][START_C][1] = '\0';

	for (register int r = 1; r <= N; r++)
	{
		for (register int c = 1; c <= N; c++)
		{
			int len = mstrlen(dp[r][c]);

			if ((len > 0) && (map[r][c] > 0))
			{
				int lenR = mstrlen(dp[r + map[r][c]][c]);
				int lenC = mstrlen(dp[r][c + map[r][c]]);

				if (r + map[r][c] <= N)
				{
					if (len < lenR)
					{
						madd(dp[r + map[r][c]][c], dp[r][c], dp[r + map[r][c]][c], lenR, len);
					}
					else
					{
						madd(dp[r][c], dp[r + map[r][c]][c], dp[r + map[r][c]][c], len, lenR);
					}
				}

				if (c + map[r][c] <= N)
				{
					if (len < lenC)
					{
						madd(dp[r][c + map[r][c]], dp[r][c], dp[r][c + map[r][c]], lenC, len);
					}
					else
					{
						madd(dp[r][c], dp[r][c + map[r][c]], dp[r][c + map[r][c]], len, lenC);
					}
				}
			}
		}
	}

	return;
}

void outputData(void)
{
	int len = mstrlen(dp[N][N]);

	if (len == 0)
	{
		printf("0\n");
	}
	else
	{
		for (register int i = len - 1; i >= 0; i--)
		{
			printf("%c", dp[N][N][i]);
		}

		printf("\0\n");
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);	// 3
	// freopen("input2.txt", "r", stdin);	// 70
	// freopen("input3.txt", "r", stdin);	// 48620

	inputData();

	solve();

	outputData();

	return 0;
}
