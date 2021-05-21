#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_M 40000
#define MAX_N 40000
#define START_M 1
#define START_N 1

int T;
int M;
int N;
int X;
int Y;

int getNext(int v, int w)
{
	if (v == w)
	{
		return 1;
	}

	return w + 1;
}

int solve(void)
{
	/*
	int a = START_M;
	int b = START_N;
	int cnt = 0;

	while ((a < M) || (b < N))
	{
		cnt++;

		if ((a == X) && (b == Y))
		{
			return cnt;
		}

		a = getNext(M, a);
		b = getNext(N, b);
	}
	*/

	int a = X;
	int b = ((X - 1) % N) + 1;
	int startB = ((X - 1) % N) + 1;
	int cnt = X;

	while (true)
	{
		if (b == Y)
		{
			return cnt;
		}

		b = ((b + M - 1) % N) + 1;
		cnt += M;

		if (b == startB)
		{
			break;
		}
	}

	return -1;
}

void inputData(void)
{
	scanf("%d", &T);

	for (register int testCase = 1; testCase <= T; testCase++)
	{
		scanf("%d %d %d %d", &M, &N, &X, &Y);

		int ans = solve();

		printf("%d\n", ans);
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);

	inputData();

	return 0;
}
