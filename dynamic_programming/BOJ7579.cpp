#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 100
#define MAX_M 10000000
#define MAX_CS 10000
#define ll long long

#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct node
{
	int b = 0;
	int c = 0;
}
NODE;

// 입력 저장
vector <int> byte;
vector <int> cost;

// dp 저장
// 여기에는 cost가 담긴다!
// dp[i][j] : i번째까지 앱에 대해 cost가 j일 때 확보할 수 있는 최대 메모리 값
// 담은 것 : 비활성화할 앱
vector <vector <NODE> > dp;

void print_byte()
{
	printf("byte : ");

	for (int i = 1; i < byte.size(); i++)
	{
		printf("%d ", byte[i]);
	}

	printf("\n");

	return;
}

void print_cost()
{
	printf("cost : ");

	for (int i = 1; i < cost.size(); i++)
	{
		printf("%d ", cost[i]);
	}

	printf("\n");

	return;
}

void print_dp()
{
	printf("dp : ");

	for (int i = 1; i < dp.size(); i++)
	{
		for (int j = 0; j < dp[i].size(); j++)
		{
			printf("%d ", dp[i][j]);
		}

		printf("\n");
	}

	printf("\n");

	return;
}

int knapsack(ll s)
{
	int result = 0;
	int b1 = 0;
	int b2 = 0;
	int c1 = 0;
	int c2 = 0;

	// 초기값 설정
	for (int i = 0; i < dp.size(); i++)
	{
		for (int j = 0; j < dp[i].size(); j++)
		{
			if ((i == 0) || (j == 0))
			{
				dp[i][j].b = 0;
				dp[i][j].c = 0;
			}
		}
	}

	// 점화식 설정
	for (int i = 1; i < dp.size(); i++)
	{
		// 무게는 거꾸로 줄어야 한다
		for (ll j = s; j >= byte[i]; j--)
		{
			// b번째를 선택했을 때와 선택하지 않았을 때로부터 온다
			// dp[i][j] = max(dp[i - 1][j - cost[i]], dp[i - 1][j]);

			b1 = dp[i - 1][j - byte[i]].b + byte[i];
			b2 = dp[i - 1][j].b;
			c1 = dp[i - 1][j - byte[i]].c + cost[i];
			c2 = dp[i - 1][j].c;

			// printf("b1 = %d, b2 = %d, c1 = %d, c2 = %d\n", b1, b2, c1, c2);

			// 일단 더 담을 수 있어야 한다
			if (b1 <= s)
			{
				// i번째를 담는게 더 크면
				if (c1 >= c2)
				{
					dp[i][j].b = b1;
					dp[i][j].c = c1;
				}
				// i번째를 안 담는게 더 크면
				else
				{
					dp[i][j].b = b2;
					dp[i][j].c = c2;
				}
			}
			// 더 담을 수 없을 경우
			else
			{
				dp[i][j].b = b2;
				dp[i][j].c = c2;
			}

			// printf("i = %d, j = %d, b = %d, c = %d\n\n", i, j, dp[i][j].b, dp[i][j].c);
		}
	}

	// dp[i][j] : i번째까지 앱에 대해 j 바이트까지 허용되었을 때의 최대 비용과 바이트
	result = dp[dp.size() - 1][s].c;

	// printf("%d %d\n", dp.size() - 1, s);

	return result;
}

// s는 cost들의 합, k는 제한 바이트
// i는 i번째, j는 cost
int new_knapsack(int s, int k)
{
	int result = 0;
	int b1 = 0;
	int b2 = 0;
	int c1 = 0;
	int c2 = 0;

	// 초기값 설정
	for (int i = 0; i < dp.size(); i++)
	{
		for (int j = 0; j < dp[i].size(); j++)
		{
			if ((i == 0) || (j == 0))
			{
				dp[i][j].b = 0;
				dp[i][j].c = 0;
			}
		}
	}

	// 점화식 설정
	for (int i = 1; i < dp.size(); i++)
	{
		// cost는 거꾸로 줄어야 한다
		for (int j = s; j >= cost[i]; j--)
		{
			// b번째를 선택했을 때와 선택하지 않았을 때로부터 온다
			// dp[i][j] = max(dp[i - 1][j - cost[i]], dp[i - 1][j]);

			b1 = dp[i - 1][j - cost[i]].b + byte[i];
			b2 = dp[i - 1][j].b;
			c1 = dp[i - 1][j - cost[i]].c + cost[i];
			c2 = dp[i - 1][j].c;

			// printf("b1 = %d, b2 = %d, c1 = %d, c2 = %d\n", b1, b2, c1, c2);

			// 일단 담을 수 있어야 한다!
			// if (b1 <= k)
			{
				// i번째를 담는게 더 크면
				if (b1 >= b2)
				{
					dp[i][j].b = b1;
					dp[i][j].c = c1;
				}
				// i번째를 안 담는게 더 크면
				else
				{
					dp[i][j].b = b2;
					dp[i][j].c = c2;
				}
			}
			// 더 담을 수 없을 경우
			/*
			else
			{
				dp[i][j].b = b2;
				dp[i][j].c = c2;
			}
			*/

			// printf("i = %d, j = %d, b = %d, c = %d\n\n", i, j, dp[i][j].b, dp[i][j].c);
		}
	}

	// print_dp();

	// dp[i][j] : i번째까지 앱에 대해 cost가 j일 때 확보할 수 있는 최대 메모리 값
	///*
	for (int j = 0; j <= s; j++)
	{
		// printf("j = %d, b = %d, c = %d\n", j, dp[dp.size() - 1][j].b, dp[dp.size() - 1][j].c);

		// 비우기 성공했으면
		if (dp[dp.size() - 1][j].b >= k)
		{
			result = dp[dp.size() - 1][j].c;

			break;
		}
	}

	// printf("\n");
	//*/

	// result = dp[dp.size() - 1][s].c;

	// printf("%d %d\n", dp.size() - 1, s);

	return result;
}

int my_main()
{
	int n = 0;
	int m = 0;
	int num = 0;
	int byte_sum = 0;
	int cost_sum = 0;
	int ans = 0;

	vector <NODE> tmp;

	scanf("%d %d", &n, &m);

	// 벡터 크기
	byte.reserve(n + 1);
	cost.reserve(n + 1);

	// 쓰레기값
	byte.push_back(0);
	cost.push_back(0);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &num);

		byte_sum += num;

		byte.push_back(num);
	}

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &num);

		cost_sum += num;

		cost.push_back(num);
	}

	// tmp.resize(byte_sum - m + 1);
	tmp.resize(cost_sum + 1);

	// dp 초기화
	for (int i = 0; i <= n; i++)
	{
		dp.push_back(tmp);
	}

	// printf("%d %d\n", dp.size(), dp[0].size());

	// print_byte();
	// print_cost();
	// printf("knapsack : %d\n", byte_sum - m);

	// ans = knapsack(byte_sum - (ll)(m));

	// printf("%d\n", cost_sum - ans);

	// 프로세스가 하나면
	if (n == 1)
	{
		ans = num;
	}
	else
	{
		ans = new_knapsack(cost_sum, m);
	}

	printf("%d\n", ans);

	return 0;
}

// 강사님 코드
#include <stdio.h>
#include <algorithm>
using namespace std;

int a[101], b[101], n, m, d[10001], sum, i, j;

int main() {
	scanf("%d%d", &n, &m);
	for (i = 0; i < n; i++) scanf("%d", &a[i]);
	for (i = 0; i < n; i++) scanf("%d", &b[i]), sum += b[i];
	for (i = 0; i < n; i++) for (j = sum; j >= b[i]; j--) {
		d[j] = max(d[j], d[j - b[i]] + a[i]);
	}
	for (i = 0; i < sum && d[i] < m; i++);
	printf("%d\n", i);
	return 0;
}
