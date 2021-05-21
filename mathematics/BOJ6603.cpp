/*
Pro입문 3주차 Problem H 로또
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_K 13
#define MAX_LEVEL 6

int N;
int path[MAX_LEVEL] = { 0, };
int vect[MAX_K] = { 0, };

void print(void)
{
	for (int i = 0; i < MAX_LEVEL; i++)
	{
		printf("%d ", path[i]);
	}

	printf("\n");

	return;
}

void run(int level, int start)
{
	if (level == MAX_LEVEL)
	{
		print();

		return;
	}

	for (int i = start; i < N; i++)
	{
		path[level] = vect[i];

		run(level + 1, i + 1);

		path[level] = 0;
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	setbuf(stdout, NULL);

	/*
	// 4개의 숫자
	// {1, 4, 6, 9}
	// 2개를 뽑는데, 
	// 모든 경우를 오름차순으로 출력
	// 1 4
	// 1 6
	// 1 9
	// 4 6
	// 4 9
	// 6 9
	// for문으로 구현

	int vect[4] = { 1, 4, 6, 9 };

	for (int a = 0; a < 4; a++)
	{
		for (int b = a + 1; b < 4; b++)
		{
			printf("%d %d\n", vect[a], vect[b]);
		}
	}
	*/

	/*
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &vect[i]);
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = i + 1; j < N; j++)
		{
			if (vect[i] > vect[j])
			{
				int temp = vect[i];
				vect[i] = vect[j];
				vect[j] = temp;
			}
		}
	}
	*/

	/*
	for (int m1 = 0; m1 < N; m1++)
	{
		for (int m2 = m1 + 1; m2 < N; m2++)
		{
			for (int m3 = m2 + 1; m3 < N; m3++)
			{
				for (int m4 = m3 + 1; m4 < N; m4++)
				{
					for (int m5 = m4 + 1; m5 < N; m5++)
					{
						for (int m6 = m5 + 1; m6 < N; m6++)
						{
							printf("%d %d %d %d %d %d\n", vect[m1], vect[m2], vect[m3], vect[m4], vect[m5], vect[m6]);
						}
					}
				}
			}
		}
	}
	*/

	// run(0, 0);

	while (true)
	{
		scanf("%d", &N);

		if (N == 0)
		{
			break;
		}

		for (int i = 0; i < N; i++)
		{
			scanf("%d", &vect[i]);
		}

		run(0, 0);

		printf("\n");
	}

	return 0;
}
