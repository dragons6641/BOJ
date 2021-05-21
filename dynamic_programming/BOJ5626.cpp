/*
#define _CRT_SECURE_NO_WARNINGS
#define ll long long
#define MOD 1000000007
#define MAX_N 10000
#define MAX_H 10000

#include <stdio.h>
#include <vector>

using namespace std;

typedef struct node
{
	// 값
	ll c;
	// 어디서 왔는지
	ll p;
}
NODE;

// 입력
vector <int> v;

// Sliding Window
// 다음부터는 얌전히 나머지로...
// 높이가 H일 경우의 수
// vector <NODE> odd(MAX_H + 1);
// vector <NODE> even(MAX_H + 1);
vector <ll> odd(MAX_H + 1);
vector <ll> even(MAX_H + 1);

void print_v()
{
	printf("v : ");

	for (int i = 0; i < v.size(); i++)
	{
		printf("%d ", v[i]);
	}

	printf("\n");

	return;
}

void print_dp()
{
	printf("odd : ");

	for (int i = 0; i < 10; i++)
	{
		printf("%lld ", odd[i].c);
	}
	
	printf("\neven : ");

	for (int i = 0; i < 10; i++)
	{
		printf("%lld ", even[i].c);
	}

	printf("\n");

	return;
}

// even(초기값) -> odd -> even -> odd -> ...
ll solve()
{
	ll result = 0;
	int cur_h = 0;

	// 초기값 설정
	even[v[0]] = 1;

	// 점화식 설정
	for (int i = 1; i < v.size(); i++)
	{
		cur_h = v[i];

		// 홀수번째
		// odd <- even
		if (i % 2)
		{
			// 높이를 알고 있으면
			if (cur_h != -1)
			{
				// 초기화 먼저 해줘야한다!
				for (int j = 0; j < cur_h; j++)
				{
					odd[j] = 0;
				}

				// 최소 높이
				if (cur_h == 0)
				{
					odd[cur_h] = even[cur_h] + even[cur_h + 1];
					// printf("%d + %lld + %lld\n", 0, even[cur_h], even[cur_h + 1]);
				}
				// 최대 높이
				else if (cur_h == MAX_H)
				{
					odd[cur_h] = even[cur_h - 1] + even[cur_h];
					// printf("%lld + %lld + %d\n", even[cur_h - 1], even[cur_h], 0);
				}
				// 일반적인 경우
				else
				{
					odd[cur_h] = even[cur_h - 1] + even[cur_h] + even[cur_h + 1];
					// printf("%lld + %lld + %lld\n", even[cur_h - 1], even[cur_h], even[cur_h + 1]);
				}

				// printf("i = %d, cur_h = %d, odd[cur_h] = %lld\n", i, cur_h, odd[cur_h]);
				// printf("%lld + %lld + %lld\n", even[cur_h - 1], even[cur_h], even[cur_h + 1]);
			}
			// 높이를 모르면
			else
			{
				// 모든 높이에 대해서
				for (int j = 0; j <= MAX_H; j++)
				{
					// 최소 높이
					if (j == 0)
					{
						odd[j] = (even[j] + even[j + 1]) % MOD;
					}
					// 최대 높이
					else if (j == MAX_H)
					{
						odd[j] = (even[j - 1] + even[j]) % MOD;
					}
					// 일반적인 경우
					else
					{
						odd[j] = (even[j - 1] + even[j] + even[j + 1]) % MOD;
					}
				}
			}

			// 마지막이면
			if (i == v.size() - 1)
			{
				result = odd[cur_h];

				//
			}
		}
		// 짝수번째
		// even <- odd
		else
		{
			// 높이를 알고 있으면
			if (cur_h != -1)
			{
				// 초기화 먼저 해줘야한다!
				for (int j = 0; j < cur_h; j++)
				{
					even[j] = 0;
				}

				// 최소 높이
				if (cur_h == 0)
				{
					even[cur_h] = (odd[cur_h] + odd[cur_h + 1]) % MOD;
					// printf("%d + %lld + %lld\n", 0, odd[cur_h], odd[cur_h + 1]);
				}
				// 최대 높이
				else if (cur_h == MAX_H)
				{
					even[cur_h] = (odd[cur_h - 1] + odd[cur_h]) % MOD;
					// printf("%lld + %lld + %d\n", odd[cur_h - 1], odd[cur_h], 0);
				}
				// 일반적인 경우
				else
				{
					even[cur_h] = (odd[cur_h - 1] + odd[cur_h] + odd[cur_h + 1]) % MOD;
					// printf("%lld + %lld + %lld\n", odd[cur_h - 1], odd[cur_h], odd[cur_h + 1]);
				}

				// printf("i = %d, cur_h = %d, even[cur_h] = %lld\n", i, cur_h, even[cur_h]);
				// printf("%d + %d + %d\n", odd[cur_h - 1], odd[cur_h], odd[cur_h + 1]);
			}
			// 높이를 모르면
			else
			{
				// 모든 높이에 대해서
				for (int j = 0; j <= MAX_H; j++)
				{
					// 최소 높이
					if (j == 0)
					{
						even[j] = (odd[j] + odd[j + 1]) % MOD;
					}
					// 최대 높이
					else if (j == MAX_H)
					{
						even[j] = (odd[j - 1] + odd[j]) % MOD;
					}
					// 일반적인 경우
					else
					{
						even[j] = (odd[j - 1] + odd[j] + odd[j + 1]) % MOD;
					}
				}
			}

			// 마지막이면
			if (i == v.size() - 1)
			{
				result = even[cur_h];
			}
		}

		// printf("i = %d\n", i);
		// print_dp();
	}

	return result;
}

// even(초기값) -> odd -> even -> odd -> ...
ll new_solve()
{
	ll result = 0;
	int cur_h = 0;
	int prev_h = 0;

	// 초기값 설정
	even[v[0]].c = 1;

	// 점화식 설정
	for (int i = 1; i < v.size(); i++)
	{
		cur_h = v[i];
		prev_h = v[i - 1];

		// 홀수번째
		// odd <- even
		if (i % 2)
		{
			// 높이를 알고 있으면
			if (cur_h != -1)
			{
				// 초기화 먼저 해줘야한다!
				for (int j = 0; j < cur_h; j++)
				{
					odd[j].c = 0;
				}

				odd[cur_h].p = even[cur_h].c;

				// 다시 돌아오는 경우
				if (odd[cur_h].c == even[cur_h].p)
				{
					// 이전보다 커진 경우(101)
					if (odd[cur_h].c > even[cur_h].c)
					{
						// 아래만 더한다
						if (cur_h == 0)
						{
							odd[cur_h].c = even[cur_h].c;
						}
						else
						{
							odd[cur_h].c = even[cur_h - 1].c + even[cur_h].c;
						}
					}
					// 이전보다 작아진 경우(010)
					else if (odd[cur_h].c < even[cur_h].c)
					{
						// 위만 더한다
						if (cur_h == MAX_H)
						{
							odd[cur_h].c = even[cur_h].c;
						}
						else
						{
							odd[cur_h].c = even[cur_h].c + even[cur_h + 1].c;
						}
					}
				}
				// 그런 경우 아닐 때
				else
				{
					// 최소 높이
					if (cur_h == 0)
					{
						odd[cur_h].c = (even[cur_h].c + even[cur_h + 1].c) % MOD;
						// printf("%d + %lld + %lld\n", 0, odd[cur_h].c, odd[cur_h + 1].c);
					}
					// 최대 높이
					else if (cur_h == MAX_H)
					{
						odd[cur_h].c = (even[cur_h - 1].c + even[cur_h].c) % MOD;
						// printf("%lld + %lld + %d\n", odd[cur_h - 1].c, odd[cur_h].c, 0);
					}
					// 일반적인 경우
					else
					{
						odd[cur_h].c = (even[cur_h - 1].c + even[cur_h].c + even[cur_h + 1].c) % MOD;
						// printf("%lld + %lld + %lld\n", odd[cur_h - 1].c, odd[cur_h].c, odd[cur_h + 1].c);
					}

					// printf("i = %d, cur_h = %d, even[cur_h] = %lld\n", i, cur_h, even[cur_h].c);
					// printf("%d + %d + %d\n", odd[cur_h - 1].c, odd[cur_h].c, odd[cur_h + 1].c);
				}
			}
			// 높이를 모르면
			else
			{
				// 모든 높이에 대해서
				for (int j = 0; j <= MAX_H; j++)
				{
					odd[j].p = even[j].c;

					// 다시 돌아오는 경우
					if (odd[j].c == even[j].p)
					{
						// 이전보다 커진 경우(101)
						if (odd[j].c > even[j].c)
						{
							// 아래만 더한다
							if (j == 0)
							{
								odd[j].c = even[j].c;
							}
							else
							{
								odd[j].c = even[j - 1].c + even[j].c;
							}
						}
						// 이전보다 작아진 경우(010)
						else if (odd[j].c < even[j].c)
						{
							// 위만 더한다
							if (j == MAX_H)
							{
								odd[j].c = even[j].c;
							}
							else
							{
								odd[j].c = even[j].c + even[j + 1].c;
							}
						}
					}
					// 그런 경우 아닐 때
					else
					{
						// 최소 높이
						if (j == 0)
						{
							odd[j].c = (even[j].c + even[j + 1].c) % MOD;
						}
						// 최대 높이
						else if (j == MAX_H)
						{
							odd[j].c = (even[j - 1].c + even[j].c) % MOD;
						}
						// 일반적인 경우
						else
						{
							odd[j].c = (even[j - 1].c + even[j].c + even[j + 1].c) % MOD;
						}
					}
				}
			}

			// 마지막이면
			if (i == v.size() - 1)
			{
				result = odd[cur_h].c;
			}
		}

		// 짝수번째
		// even <- odd
		else
		{
			// 높이를 알고 있으면
			if (cur_h != -1)
			{
				// 초기화 먼저 해줘야한다!
				for (int j = 0; j < cur_h; j++)
				{
					even[j].c = 0;
				}

				even[cur_h].p = odd[cur_h].c;

				// 다시 돌아오는 경우
				if (even[cur_h].c == odd[cur_h].p)
				{
					// 이전보다 커진 경우(101)
					if (even[cur_h].c > odd[cur_h].c)
					{
						// 아래만 더한다
						if (cur_h == 0)
						{
							even[cur_h].c = odd[cur_h].c;
						}
						else
						{
							even[cur_h].c = odd[cur_h - 1].c + odd[cur_h].c;
						}
					}
					// 이전보다 작아진 경우(010)
					else if (even[cur_h].c < odd[cur_h].c)
					{
						// 위만 더한다
						if (cur_h == MAX_H)
						{
							even[cur_h].c = odd[cur_h].c;
						}
						else
						{
							even[cur_h].c = odd[cur_h].c + odd[cur_h + 1].c;
						}
					}
				}
				// 그런 경우 아닐 때
				else
				{
					// 최소 높이
					if (cur_h == 0)
					{
						even[cur_h].c = (odd[cur_h].c + odd[cur_h + 1].c) % MOD;
						// printf("%d + %lld + %lld\n", 0, odd[cur_h].c, odd[cur_h + 1].c);
					}
					// 최대 높이
					else if (cur_h == MAX_H)
					{
						even[cur_h].c = (odd[cur_h - 1].c + odd[cur_h].c) % MOD;
						// printf("%lld + %lld + %d\n", odd[cur_h - 1].c, odd[cur_h].c, 0);
					}
					// 일반적인 경우
					else
					{
						even[cur_h].c = (odd[cur_h - 1].c + odd[cur_h].c + odd[cur_h + 1].c) % MOD;
						// printf("%lld + %lld + %lld\n", odd[cur_h - 1].c, odd[cur_h].c, odd[cur_h + 1].c);
					}

					// printf("i = %d, cur_h = %d, even[cur_h] = %lld\n", i, cur_h, even[cur_h].c);
					// printf("%d + %d + %d\n", odd[cur_h - 1].c, odd[cur_h].c, odd[cur_h + 1].c);
				}
			}
			// 높이를 모르면
			else
			{
				// 모든 높이에 대해서
				for (int j = 0; j <= MAX_H; j++)
				{
					even[j].p = odd[j].c;

					// 다시 돌아오는 경우
					if (even[j].c == odd[j].p)
					{
						// 이전보다 커진 경우(101)
						if (even[j].c > odd[j].c)
						{
							// 아래만 더한다
							if (j == 0)
							{
								even[j].c = odd[j].c;
							}
							else
							{
								even[j].c = odd[j - 1].c + odd[j].c;
							}
						}
						// 이전보다 작아진 경우(010)
						else if (even[j].c < odd[j].c)
						{
							// 위만 더한다
							if (j == MAX_H)
							{
								even[j].c = odd[j].c;
							}
							else
							{
								even[j].c = odd[j].c + odd[j + 1].c;
							}
						}
					}
					// 그런 경우 아닐 때
					else
					{
						// 최소 높이
						if (j == 0)
						{
							even[j].c = (odd[j].c + odd[j + 1].c) % MOD;
						}
						// 최대 높이
						else if (j == MAX_H)
						{
							even[j].c = (odd[j - 1].c + odd[j].c) % MOD;
						}
						// 일반적인 경우
						else
						{
							even[j].c = (odd[j - 1].c + odd[j].c + odd[j + 1].c) % MOD;
						}
					}
				}
			}

			// 마지막이면
			if (i == v.size() - 1)
			{
				result = even[cur_h].c;
			}
		}

		// printf("i = %d\n", i);
		// print_dp();
	}

	return result;
}

int main()
{
	int n = 0;
	int num = 0;
	ll ans = 0;

	scanf("%d", &n);

	// 벡터 크기
	v.reserve(n);

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &num);

		if ((i == 0) || (i == n - 1))
		{
			if (num == -1)
			{
				num = 0;
			}
		}

		v.push_back(num);
	}

	// print_v();

	ans = solve();

	// print_dp();

	printf("%lld\n", ans);

	return 0;
}
*/

// 강사님 코드
#include<stdio.h>
#include<algorithm>

using namespace std;

typedef long long int lld;

int n;
int dt[10001];

lld dp[2][5005];

int main()
{
	scanf("%d", &n);
	int i, j;
	for (i = 1; i <= n; i++)
	{
		scanf("%d", &dt[i]);
	}

	if (dt[1] == -1 || dt[1] == 0)
		dp[1][0] = 1;

	for (i = 2; i <= n; i++)
	{
		if (dt[i] != -1)
		{
			for (j = 0; j <= n / 2 + 1; j++)
			{
				dp[i & 1][j] = 0;
			}
			if (dt[i]) {
				dp[i & 1][dt[i]] = (dp[(i - 1) & 1][dt[i]] + dp[(i - 1) & 1][dt[i] - 1] + dp[(i - 1) & 1][dt[i] + 1]) % 1000000007;
			}
			else {
				dp[i & 1][0] = (dp[(i - 1) & 1][1] + dp[(i - 1) & 1][0]) % 1000000007;
			}
			continue;
		}
		dp[i & 1][0] = (dp[(i - 1) & 1][1] + dp[(i - 1) & 1][0]) % 1000000007;
		for (j = 1; j <= n / 2 + 1; j++)
		{
			dp[i & 1][j] = (dp[(i - 1) & 1][j] + dp[(i - 1) & 1][j - 1] + dp[(i - 1) & 1][j + 1]) % 1000000007;
		}
	}

	printf("%d", dp[n & 1][0]);
	return 0;
}
