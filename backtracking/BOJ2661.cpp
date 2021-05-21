/*
Pro입문 3주차 Problem L 좋은 수열
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 80
#define MAX_M 3

int N;
int path[MAX_N + 20] = { 0, };

int badNums(int now)
{
	if (now <= 0)
	{
		return 0;
	}

	for (int N = 1; ; N++)
	{
		int a = now;
		int b = now - N;
		int flag = 0;

		if (b - (N - 1) < 0)
		{
			return 0;
		}

		for (int i = 0; i < N; i++)
		{
			if (path[a - i] != path[b - i])
			{
				flag = 1;

				break;
			}
		}

		if (flag == 0)
		{
			return 1;
		}
	}
}

int run(int level)
{
	/*
	if (path[4] == 1)
	{
		int debug = 1;
	}
	*/

	int ret;

	if (badNums(level - 1) == 1)
	{
		return 0;
	}

	if (level == N)
	{
		for (int i = 0; i < N; i++)
		{
			printf("%d", path[i]);
		}

		printf("\n");

		return 1;
	}

	for (int i = 1; i <= MAX_M; i++)
	{
		path[level] = i;

		ret = run(level + 1);

		if (ret == 1)
		{
			return ret;
		}

		path[level] = 0;
	}

	return 0;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	setbuf(stdout, NULL);

	scanf("%d", &N);

	run(0);

	return 0;
}
