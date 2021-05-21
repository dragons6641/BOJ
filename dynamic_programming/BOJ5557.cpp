#define _CRT_SECURE_NO_WARNINGS
#define ll long long
#define MAX_NUM 20

#include <stdio.h>
#include <vector>
// #include <algorithm>

using namespace std;

// 숫자들을 모아둔 벡터
vector <ll> v;

// DP 저장 벡터
vector < vector <ll> > dp;

void print_v()
{
	printf("v : ");

	for (int i = 0; i < v.size(); i++)
	{
		printf("%lld ", v[i]);
	}

	printf("\n");

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

ll solve(int end)
{
	ll result = 0;

	// 초기값 설정
	for (int j = 0; j < dp[0].size(); j++)
	{
		dp[0][j] = 0;
	}

	dp[0][v[0]] = 1;

	// 점화식 설정
	for (int i = 1; i < dp.size(); i++)
	{
		for (int j = 0; j < dp[i].size(); j++)
		{
			// printf("i = %d, j = %d\n", i, j);
			// print_dp();

			// 20 이하여야 함
			if (j + v[i] <= 20)
			{
				// 양수인 경우
				dp[i][j] += dp[i - 1][j + v[i]];
			}

			// 0 이상이어야 함
			if(j - v[i] >= 0)
			{
				// 음수인 경우
				dp[i][j] += dp[i - 1][j - v[i]];
			}
		}
	}

	result = dp[dp.size() - 1][end];

	return result;
}

int main()
{
	ll n = 0;
	ll input = 0;
	// int sum = 0;
	ll last = 0;
	ll ans = 0;

	vector <ll> tmp;

	scanf("%lld", &n);

	v.reserve(n);
	tmp.resize(MAX_NUM + 1);

	for (int i = 1; i < n; i++)
	{
		dp.push_back(tmp);
	}

	// 나머지는 음수 또는 양수
	for (int i = 0; i < n - 1; i++) 
	{
		scanf("%lld", &input);

		// printf("input : %d\n", input);

		// 전체 합을 구해준다
		// sum += input;

		v.push_back(input);
	}

	// 마지막은 답
	scanf("%lld", &last);

	// sort(v.begin(), v.end());

	// printf("sum = %d\n", sum);
	// print_v();

	ans = solve(last);

	// print_dp();

	printf("%lld\n", ans);

	return 0;
}

// 강사님 코드
/*
#include <stdio.h>
int N;
int P[100];
long long D[100][21];

int main()
{
	scanf("%d", &N);
	for (int i = 0; i<N; i++)
	{
		scanf("%d", P + i);
		for (int j = 0; j<21; j++) D[i][j] = 0;
	}
	D[0][P[0]] = 1;
	for (int i = 1; i<N; i++)
	{
		for (int j = 0; j<21; j++)
		{
			if (j + P[i]<21) D[i][j + P[i]] += D[i - 1][j];
			if (j - P[i] >= 0) D[i][j - P[i]] += D[i - 1][j];
		}
	}
	printf("%lld", D[N - 2][P[N - 1]]);
}
*/
