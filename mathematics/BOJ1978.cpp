/*
1978 소수 찾기
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 100
#define MAX_M 1000

bool notPrimeList[MAX_M + 1] = { true, true, };

void init(void)
{
	for (int i = 2; i <= MAX_M; i++)
	{
		for (int j = 2 * i; j <= MAX_M; j += i)
		{
			notPrimeList[j] = true;
		}
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	setbuf(stdout, NULL);

	int N;
	int M;
	int ans = 0;

	init();

	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &M);

		if (!notPrimeList[M])
		{
			ans++;
		}
	}

	printf("%d\n", ans);

	return 0;
}
