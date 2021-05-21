/*
9613 GCD 합
*/

#define _CRT_SECURE_NO_WARNINGS
#define ll long long

#include <stdio.h>

#define MAX_R 100
#define MAX_C 100

int T;
int N;
int map[MAX_R][MAX_C] = { 0, };

int getGcd(int x, int y)
{
	if (y == 0)
	{
		return x;
	}

	return getGcd(y, x % y);
}

ll solve(int nowR)
{
	int a;
	int b;
	ll result = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = i + 1; j < N; j++)
		{
			a = map[nowR][i];
			b = map[nowR][j];

			if (a > b)
			{
				result += getGcd(a, b);
			}
			else
			{
				result += getGcd(b, a);
			}
		}
	}

	return result;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	setbuf(stdout, NULL);

	ll ans;
	
	scanf("%d", &T);

	for (int r = 0; r < T; r++)
	{
		scanf("%d", &N);

		for (int c = 0; c < N; c++)
		{
			scanf("%d", &map[r][c]);
		}

		ans = solve(r);

		printf("%lld\n", ans);
	}

	return 0;
}
