#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N ((int)1e8)
#define DIGIT 10

typedef long long LL;

int N;

int calcDigit(int k)
{
	register int cnt = 0;

	while (k > 0)
	{
		k /= DIGIT;
		cnt++;
	}

	return cnt;
}

/*
int solve(void)
{
	int cnt = 0;

	for (register int i = 1; i <= N; i++)
	{
		int ret = calcDigit(i);

		cnt += ret;
	}

	return cnt;
}
*/

LL solve(void)
{
	int pow = 1;
	LL result = 0;

	int digit = calcDigit(N);

	for (register int i = 1; i < digit; i++)
	{
		result += (LL)(DIGIT - 1) * pow * i;

		pow *= DIGIT;
	}

	result += (LL)(N - pow + 1) * digit;

	return result;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	scanf("%d", &N);

	LL ans = solve();

	printf("%lld\n", ans);

	return 0;
}
