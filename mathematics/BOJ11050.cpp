#define _CRT_SECURE_NO_WARNINGS
#define ll long long
#define MAX_N 10

#include <stdio.h>
#include <vector>

using namespace std;

// 조합 DP 배열
vector <vector <ll> > dp;

ll factorial(ll x)
{
	if (x == 1)
	{
		return 1;
	}
	else
	{
		return x * factorial(x - 1);
	}

	return 0;
}

ll def_nCk(ll n, ll k)
{
	ll a = factorial(n);
	ll b = factorial(n - k);
	ll c = factorial(k);
	ll result = a / (b * c);

	return result;
}

void make_dp(ll x)
{
	for (int i = 0; i < dp.size(); i++)
	{
		for (int j = 0; j <= i; j++)
		{
			// printf("i = %d, j = %d\n", i, j);

			if ((j == 0) || (j == i))
			{
				dp[i][j] = 1;
			}
			else
			{
				dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
			}

			// printf("%d ", dp[i][j]);
		}

		// printf("\n");
	}

	return;
}

int main()
{
	ll n = 0;
	ll k = 0;
	ll ans = 0;
	
	vector <ll> tmp;

	scanf("%lld %lld", &n, &k);
	tmp.resize(n + 1);

	// 여기서 size 쓰면 안된다!
	// 초기화도 미리 해주면 안된다!
	for (int i = 0; i <= n; i++)
	{
		// printf("i = %d\n", i);

		dp.push_back(tmp);
	}

	// printf("%d %d\n", dp.size(), dp[0].size());

	// printf("HERE~\n");

	make_dp(n);

	// ans = def_nCk(n, k);

	ans = dp[n][k];

	printf("%lld\n", ans);

	return 0;
}

// 강사님 코드
/*
#include<cstdio>

int n, k, nCk;
int fac(int num)
{
	int ret = 1;
	for (int i = 1; i <= num; i++) ret *= i;
	return ret;
}
int main()
{
	int i;

	scanf("%d %d", &n, &k);

	nCk = fac(n) / (fac(n - k)*fac(k));

	printf("%d", nCk);
	return 0;
}
*/
