/*
B1 다각형 그리기
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_M 50
#define MAX_N 100
#define MAX_DIR 4

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	setbuf(stdout, NULL);

	int M;
	int N;
	int ansCnt = 0;
	int sampleList[MAX_M] = { 0, };
	int reverseSampleList[MAX_M] = { 0, };
	int inputList[MAX_N][MAX_M] = { 0, };
	int ansCheck[MAX_N] = { 0 };
	int changeList[MAX_DIR + 1] = {0, 3, 4, 1, 2};

	scanf("%d", &M);

	for (int i = 0; i < M; i++)
	{
		scanf("%d", &sampleList[i]);
	}

	scanf("%d", &N);

	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < M; c++)
		{
			scanf("%d", &inputList[r][c]);
		}
	}

	// 0. 반대로 저장
	for (int i = 0; i < M; i++)
	{
		reverseSampleList[M - i - 1] = changeList[sampleList[i]];
	}

	// 1. 하나씩 밀기
	for (int i = 0; i < M; i++)
	{
		int temp = sampleList[0];

		for (int j = 0; j < M - 1; j++)
		{
			sampleList[j] = sampleList[j + 1];
		}

		sampleList[M - 1] = temp;

		// 2. 정답인지 체크
		for (int r = 0; r < N; r++)
		{
			int flag = 0;

			for (int c = 0; c < M; c++)
			{
				if (sampleList[c] != inputList[r][c])
				{
					flag = 1;

					break;
				}
			}

			if (flag == 0)
			{
				ansCheck[r] = 1;
			}
		}
	}

	// 3. 하나씩 밀기
	for (int i = 0; i < M; i++)
	{
		int temp = reverseSampleList[0];

		for (int j = 0; j < M - 1; j++)
		{
			reverseSampleList[j] = reverseSampleList[j + 1];
		}

		reverseSampleList[M - 1] = temp;

		// 4. 정답인지 체크
		for (int r = 0; r < N; r++)
		{
			int flag = 0;

			for (int c = 0; c < M; c++)
			{
				if (reverseSampleList[c] != inputList[r][c])
				{
					flag = 1;

					break;
				}
			}

			if (flag == 0)
			{
				ansCheck[r] = 1;
			}
		}
	}

	for (int r = 0; r < N; r++)
	{
		if (ansCheck[r] == 1)
		{
			ansCnt++;
		}
	}

	printf("%d\n", ansCnt);

	for (int r = 0; r < N; r++)
	{
		if (ansCheck[r] == 1)
		{
			for (int c = 0; c < M; c++)
			{
				printf("%d ", inputList[r][c]);
			}

			printf("\n");
		}
	}

	return 0;
}
