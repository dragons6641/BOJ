/*
2420 사파리월드
*/

#define _CRT_SECURE_NO_WARNINGS
#define ll long long

#include <stdio.h>

#define MIN_VALUE ((int)-2e9)
#define MAX_VALUE ((int)2e9)

int main(void)
{
	ll N;
	ll M;
	ll ans = 0;

	scanf("%lld %lld", &N, &M);

	if (M > N)
	{
		ans = M - N;
	}
	else
	{
		ans = N - M;
	}

	printf("%lld\n", ans);

	return 0;
}
