#define _CRT_SECURE_NO_WARNINGS
#define MAX_C 1000
#define MAX_N 1000

#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

// dp 저장 벡터
vector <int> dp(MAX_N + 1, 0);

// 오일러 파이 저장 벡터
// pi[i][j] = i번째 저장
// vector <vector <int> > pi(MAX_N + 1, vector <int>(MAX_N + 1, 0));
vector <int> pi(MAX_N + 1);

// 소수 표시
vector <int> check(MAX_N + 1);

void print_pi()
{
	printf("pi : ");

	for (int i = 0; i < pi.size(); i++)
	{
		printf("%d ", pi[i]);
	}

	printf("\n");

	return;
}

void print_check()
{
	printf("check : ");

	for (int i = 0; i < check.size(); i++)
	{
		printf("%d ", check[i]);
	}

	printf("\n");

	return;
}

void sieve(int k)
{
	// i는 시작 위치
	for (int i = 2; i <= k; i++)
	{
		// 시작점은 따로 처리
		if (check[i] == 0)
		{
			// 소수임
			// prime.push_back(i);

			check[i] = 1;

			// 곱해주자!
			pi[i] *= (i - 1);
			pi[i] /= i;

			// j는 현재 위치
			for (int j = 2 * i; j <= k; j += i)
			{
				// 곱해주자!
				pi[j] *= (i - 1);
				pi[j] /= i;

				// 아직 표시 안 되어있다면
				if (check[j] == 0)
				{
					check[j] = 1;
				}
			}
		}

		// printf("i = %d\n", i);
		// print_pi();
		// print_check();
	}

	return;
}

void make_dp(int k)
{
	// 초기값 설정
	dp[0] = 0;
	dp[1] = 3;

	for (int i = 2; i < dp.size(); i++)
	{
		// 앞에거에 해당 서로소 더해준다
		dp[i] = dp[i - 1] + (pi[i] * 2);

		// printf("i = %d, dp = %d\n", i, dp[i]);
	}

	return;
}

int main()
{
	int c = 0;
	int n = 0;
	int ans = 0;

	// 초기화
	for (int i = 0; i < pi.size(); i++)
	{
		pi[i] = i;
		check[i] = 0;
	}

	// print_pi();
	// print_check();

	// 오일러 파이 미리 만들자
	sieve(MAX_N);

	// print_pi();
	// print_check();

	// dp 미리 만들자
	make_dp(MAX_N);

	scanf("%d", &c);

	for (int i = 0; i < c; i++)
	{
		scanf("%d", &n);

		ans = dp[n];

		printf("%d\n", ans);
	}

	return 0;
}

// 강사님 코드
//C++
/*
#include<stdio.h>

int n, m;
int pi[1001];
int prime[500], c;

int main()
{
	int i, j;
	prime[++c] = 2;
	for (i = 3; i <= 999; i += 2)
	{
		for (j = 1; j <= c; j++)
		{
			if (i%prime[j] == 0)
				break;
		}
		if (j>c)
		{
			prime[++c] = i;
			pi[i] = i - 1;
		}
	}
	pi[1] = pi[2] = 1;
	for (i = 4; i <= 1000; i++)
	{
		if (pi[i] == 0)
		{
			int tmp = i;
			int fcnt = 1;
			for (j = 1; j <= c; j++)
			{
				if (tmp%prime[j] == 0)
				{
					while (tmp%prime[j] == 0)
					{
						tmp /= prime[j];
						fcnt *= prime[j];
					}
					break;
				}
			}
			if (tmp == 1)
			{
				pi[i] = i / prime[j] * pi[prime[j]];
			}
			else
			{
				pi[i] = pi[fcnt] * pi[i / fcnt];
			}
		}
	}
	scanf("%d", &m);
	for (i = 1; i <= m; i++)
	{
		scanf("%d", &n);
		int su = 0;
		for (j = 1; j <= n; j++)
		{
			su += pi[j];
		}

		printf("%d\n", su * 2 + 1);
	}
	return 0;
}
*/
