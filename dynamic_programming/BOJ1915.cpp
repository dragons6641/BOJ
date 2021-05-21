#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

// 입력 받는 벡터
vector <vector <int> > v;

// dp 생성 벡터
vector <vector <int> > dp;

void print_v()
{
	printf("v : \n");

	for (int i = 0; i < v.size(); i++)
	{
		for (int j = 0; j < v[i].size(); j++)
		{
			printf("%d ", v[i][j]);
		}

		printf("\n");
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
			printf("%d ", dp[i][j]);
		}

		printf("\n");
	}

	return;
}

int solve()
{
	int result = dp[0][0];

	// printf("%d %d\n", dp.size(), dp[0].size());

	// 점화식 설정
	for (int i = 1; i < dp.size(); i++)
	{
		for (int j = 1; j < dp[i].size(); j++)
		{
			// 1일 경우
			if (dp[i][j])
			{
				dp[i][j] = min(min(dp[i - 1][j - 1], dp[i - 1][j]), dp[i][j - 1]) + 1;

				if (dp[i][j] > result)
				{
					result = dp[i][j];
				}
			}
		}
	}

	// print_dp();

	return result;
}

int main()
{
	int n = 0;
	int m = 0;
	int ans = 0;
	char ch = '\0';

	vector <int> tmp;

	scanf("%d %d\n", &n, &m);

	///*
	while (1)
	{
		ch = getchar();

		// printf("ch = %d\n", (int)(ch - '0'));

		if (ch == EOF)
		{
			break;
		}
		else if (ch == '\n')
		{
			dp.push_back(tmp);

			// printf("v.size() : %d\n", v.size());

			tmp.clear();
		}
		else
		{
			tmp.push_back((int)(ch - '0'));

			// printf("tmp.size() : %d\n", tmp.size());
		}

		// print_dp();
	}
	//*/

	// print_v();

	// print_dp();

	ans = solve();

	printf("%d\n", ans * ans);

	return 0;
}

// 강사님 코드
/*
#include<stdio.h>
#include<algorithm>

using namespace std;

int n, m, mp[1001][1001], dp[1001][1001];
char tmp[1001];

int main()
{
	int i, j;
	scanf("%d%d", &n, &m);

	for (i = 1; i <= n; i++)
	{
		scanf("%s", tmp);
		for (j = 0; j<m; j++)
			mp[i][j + 1] = tmp[j] - '0';
	}
	int mx = 0;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= m; j++)
		{
			if (mp[i][j] == 0)dp[i][j] = 0;
			else
			{
				dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
				mx = max(dp[i][j], mx);
			}
		}
	}

	printf("%d", mx*mx);
	return 0;
}
*/
