/*
15656 N과 M (7)
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 7
#define MAX_M 7
#define MAX_K 10000
#define START_LEVEL 0

int N;
int M;
// 1부터 시작
int inputList[MAX_N + 1] = { 0, };
// 1부터 시작
int outputList[MAX_M + 1] = { 0, };

void run(int level)
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

	for (int i = 1; i <= N; i++)
	{
		outputList[level + 1] = inputList[i];

		run(level + 1);

		outputList[level + 1] = 0;
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

	return 0;
}
