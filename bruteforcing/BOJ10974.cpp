/*
10974 모든 순열
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 8
#define START_LEVEL 0

int N;
// 1부터 시작
int visit[MAX_N + 1] = { 0, };
int outputList[MAX_N + 1] = { 0, };

void run(int level)
{
	if (level == N)
	{
		for (int i = 1; i <= N; i++)
		{
			printf("%d ", outputList[i]);
		}

		printf("\n");

		return;
	}

	for (int i = 1; i <= N; i++)
	{
		if (visit[i] == 0)
		{
			visit[i] = 1;
			outputList[level + 1] = i;

			run(level + 1);

			visit[i] = 0;
			outputList[level + 1] = 0;
		}
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	// setbuf(stdout, NULL);

	scanf("%d", &N);

	run(START_LEVEL);

	return 0;
}
