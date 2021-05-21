/*
15663 N과 M (9)
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 8
#define MAX_M 8
#define MAX_K 10000
#define MAX_OUTPUT 100000
#define START_LEVEL 0

int N;
int M;
int cnt = 0;
// 1부터 시작
int visit[MAX_N + 1] = { 0, };
// 1부터 시작
int inputList[MAX_N + 1] = { 0, };
// 1부터 시작
int nowList[MAX_M + 1] = { 0, };
// 1부터 시작
int outputList[MAX_OUTPUT + 1][MAX_M + 1] = { 0, };

void run(int level)
{
	if (level == M)
	{
		for (int r = 1; r <= cnt; r++)
		{
			int flag = 0;

			for (int c = 1; c <= M; c++)
			{
				if (outputList[r][c] != nowList[c])
				{
					flag = 1;

					break;
				}
			}

			if (flag == 0)
			{
				return;
			}
		}

		cnt++;

		for (int c = 1; c <= M; c++)
		{
			outputList[cnt][c] = nowList[c];
		}

		return;
	}

	for (int i = 1; i <= N; i++)
	{
		if (visit[i] == 0)
		{
			visit[i] = 1;
			nowList[level + 1] = inputList[i];

			run(level + 1);

			visit[i] = 0;
			nowList[level + 1] = 0;
		}
	}

	return;
}

void quickSort(int first, int last)
{
	int pivot;
	int temp;

	if (first < last)
	{
		int i = first;
		int j = last;

		pivot = first;

		while (i < j)
		{
			while ((inputList[i] <= inputList[pivot]) && (i < last))
			{
				i++;
			}

			while ((inputList[j] > inputList[pivot]) && (j > first))
			{
				j--;
			}

			if (i < j)
			{
				temp = inputList[i];
				inputList[i] = inputList[j];
				inputList[j] = temp;
			}
		}

		temp = inputList[pivot];
		inputList[pivot] = inputList[j];
		inputList[j] = temp;

		quickSort(first, j - 1);
		quickSort(j + 1, last);
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

	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &inputList[i]);
	}

	quickSort(1, N);

	run(START_LEVEL);

	for (int r = 1; r <= cnt; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			printf("%d ", outputList[r][c]);
		}

		printf("\n");
	}

	return 0;
}
