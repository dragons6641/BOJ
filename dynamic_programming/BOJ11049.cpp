#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 500
#define ll long long
#define INF 10000000000

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

// 행렬 저장 벡터
vector < pair <ll, ll> > pii;

// dp 벡터
// dp[i][j] : i번째 행렬부터 j번째 행렬까지 곱할 때 연산 횟수
vector < vector <ll> > dp;

void print_pii()
{
	printf("pii : \n");

	for (int i = 0; i < pii.size(); i++)
	{
		printf("x = %lld, y = %lld\n", pii[i].first, pii[i].second);
	}

	return;
}

void print_dp()
{
	printf("dp : \n");

	for (int i = 0; i < dp.size(); i++)
	{
		for (int j = 0; j < dp[i].size(); j++)
		{
			printf("%lld ", dp[i][j]);
		}

		printf("\n");
	}

	return;
}

ll solve()
{
	ll result = 0;
	ll a = 0;
	ll b = 0;

	// 초기값 설정
	for (int i = 1; i < dp.size(); i++)
	{
		// 바로 붙어있는 것끼리 곱할 때
		dp[i - 1][i] = pii[i - 1].first * pii[i].first * pii[i].second;
	}

	// printf("%d %d\n", dp.size(), dp[0].size());

	// 점화식 설정
	// i는 거꾸로 돌아야 한다!
	for (int i = dp.size() - 3; i >= 0; i--)
	{
		// printf("i = %d\n", i);

		for (int j = i + 2; j < dp[i].size(); j++)
		{
			// printf("j = %d\n", j);

			a = dp[i][j - 1] + (pii[i].first * pii[j - 1].second * pii[j].second);
			b = (pii[i].first * pii[i + 1].first * pii[j].second) + dp[i + 1][j];

			printf("a = %lld, b = %lld\n", a, b);

			dp[i][j] = min(a, b);
		}
	}

	result = dp[0][dp.size() - 1];

	return result;
}

ll new_solve()
{
	ll result = 0;
	ll cur = 0;

	// 초기값 설정
	for (int i = 0; i < dp.size(); i++)
	{
		for (int j = i + 1; j < dp[i].size(); j++)
		{
			dp[i][j] = INF;
		}
	}

	// 점화식 설정
	for (int i = dp.size() - 2; i >= 0; i--)
	{
		// printf("i = %d\n", i);

		for (int j = i + 1; j < dp[i].size(); j++)
		{
			// printf("j = %d\n", j);

			for (int k = i; k < j; k++)
			{
				cur = dp[i][k] + dp[k + 1][j] + (pii[i].first * pii[k].second * pii[j].second);

				if (cur < dp[i][j])
				{
					dp[i][j] = cur;
				}
			}
		}
	}

	result = dp[0][dp.size() - 1];

	return result;
}

int main()
{
	int n = 0;
	ll r = 0;
	ll c = 0;
	ll ans = 0;

	vector <ll> tmp;

	scanf("%d", &n);

	// 벡터 초기화
	pii.reserve(n);
	tmp.resize(n);

	for (int i = 0; i < n; i++)
	{
		dp.push_back(tmp);
	}

	for (int i = 0; i < n; i++)
	{
		scanf("%lld %lld", &r, &c);

		pii.push_back(make_pair(r, c));
	}

	// print_pii();

	if (n == 1)
	{
		ans = 0;
	}
	else
	{
		// ans = solve();
		ans = new_solve();
	}

	// print_dp();

	printf("%lld\n", ans);

	return 0;
}

// 강사님 코드
/*
#include<stdio.h>
#include<algorithm>

using namespace std;

int n, list[501][2], dp[501][501];

int main()
{
	int i, j, l, k, c;
	scanf("%d", &n);

	for (i = 1; i <= n; i++)
	{
		for (j = 0; j<2; j++) scanf("%d", &list[i][j]);
	}

	for (i = 0; i<n; i++) dp[i][i + 1] = list[i][0] * list[i][1] * list[i + 1][1];
	for (l = 2; l <= n; l++) {
		for (i = 1; i <= n - l; i++) {
			j = i + l;
			for (k = i; k<j; k++) {
				c = dp[i][k] + dp[k + 1][j] + (list[i][0] * list[k][1] * list[j][1]);
				if (dp[i][j] == 0 || dp[i][j] > c) dp[i][j] = c;
			}
		}
	}

	printf("%d", dp[1][n]);
	return 0;
}
*/
