/*
10973 이전 순열
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 10000
#define START_LEVEL 0

int N;
int flag = 0;
// 1부터 시작
int inputList[MAX_N + 1] = { 0, };
int outputList[MAX_N + 1] = { 0, };
int visit[MAX_N + 1] = { 0, };

void run(int level)
{
	if (flag == 2)
	{
		return;
	}

	if (level == N)
	{
		if (flag == 0)
		{
			flag = 1;
		}
		else if (flag == 1)
		{
			flag = 2;

			for (int i = 1; i <= N; i++)
			{
				printf("%d ", outputList[i]);
			}

			printf("\n");
		}

		return;
	}

	for (int i = N; i >= 1; i--)
	{
		if (flag == 0)
		{
			if ((visit[i] == 0) && (inputList[level + 1] == i))
			{
				visit[i] = 1;
				outputList[level + 1] = i;

				run(level + 1);

				visit[i] = 0;
				outputList[level + 1] = 0;
			}
		}
		else if (flag == 1)
		{
			if ((visit[i] == 0))
			{
				visit[i] = 1;
				outputList[level + 1] = i;

				run(level + 1);

				visit[i] = 0;
				outputList[level + 1] = 0;
			}
		}
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);

	setbuf(stdout, NULL);

	scanf("%d", &N);

	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &inputList[i]);
	}

	run(START_LEVEL);

	if (flag == 1)
	{
		printf("-1\n");
	}

	return 0;
}
