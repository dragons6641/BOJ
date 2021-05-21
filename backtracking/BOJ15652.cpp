/*
15652 N과 M (4)
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 8
#define MAX_M 8
#define START_NOW 1
#define START_LEVEL 0

int N;
int M;
// 1부터 시작
int outputList[MAX_M + 1] = { 0, };

void run(int now, int level)
{
	if (level == M)
	{
		for (int i = 1; i <= M; i++)
		{
			printf("%d ", outputList[i]);
		}

		printf("\n");

		return;
	}

	for (int i = now; i <= N; i++)
	{
		outputList[level + 1] = i;

		run(i, level + 1);

		outputList[level + 1] = 0;
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);

	// setbuf(stdout, NULL);

	scanf("%d %d", &N, &M);

	run(START_NOW, START_LEVEL);

	return 0;
}
