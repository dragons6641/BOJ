/*
12101 1, 2, 3 더하기 2
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 10
#define START_LEVEL 0

int N;
int K;
int cnt = 0;
int outputList[MAX_N] = { 0, };

void print(void)
{
	bool flag = false;

	for (int i = 0; i < MAX_N; i++)
	{
		if (outputList[i] > 0)
		{
			if (flag)
			{
				printf("+");
			}
			else
			{
				flag = true;
			}

			printf("%d", outputList[i]);
		}
	}
	
	printf("\n");

	return;
}

void run(int level)
{
	if (cnt == K)
	{
		return;
	}

	if (level == N)
	{
		cnt++;

		if (cnt == K)
		{
			print();
		}

		return;
	}
	else if (level > N)
	{
		return;
	}

	outputList[level] = 1;
	run(level + 1);
	outputList[level] = 0;

	outputList[level] = 2;
	run(level + 2);
	outputList[level] = 0;

	outputList[level] = 3;
	run(level + 3);
	outputList[level] = 0;

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);
	// freopen("input4.txt", "r", stdin);

	setbuf(stdout, NULL);

	scanf("%d %d", &N, &K);

	run(START_LEVEL);

	if (cnt < K)
	{
		printf("-1\n");
	}

	return 0;
}
