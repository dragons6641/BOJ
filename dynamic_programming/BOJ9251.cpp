#define _CRT_SECURE_NO_WARNINGS
#define MAX_LEN 1000

#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

vector <char> a;
vector <char> b;

// dp 벡터
vector <vector <int> > dp;

// 정답 벡터
vector <char> ans;

void print_a()
{
	printf("a : ");

	for (int i = 0; i < a.size(); i++)
	{
		printf("%c ", a[i]);
	}

	printf("\n");

	return;
}

void print_b()
{
	printf("b : ");

	for (int i = 0; i < b.size(); i++)
	{
		printf("%c ", b[i]);
	}

	printf("\n");

	return;
}

void print_dp()
{
	printf("dp : \n");

	for (int i = 0; i < a.size(); i++)
	{
		for (int j = 0; j < b.size(); j++)
		{
			printf("%d ", dp[i][j]);
		}

		printf("\n");
	}

	return;
}

void print_ans(int k)
{
	printf("%d\n", k);

	/*
	// 거꾸로 출력
	for (int i = ans.size() - 1; i >= 0; i--)
	{
		printf("%c", ans[i]);
	}

	printf("\n");
	*/

	return;
}

void make_dp()
{
	// 초기값 설정
	for (int i = 0; i < a.size(); i++)
	{
		for (int j = 0; j < b.size(); j++)
		{
			if ((i == 0) && (j == 0))
			{
				// 두 문자가 같으면
				if (a[i] == b[j])
				{
					// 최장 공통 부분 수열에 포함
					dp[i][j] = 1;
				}
				// 두 문자가 다르면
				else
				{
					// 최장 공통 부분 수열에 미포함
					dp[i][j] = 0;
				}
			}
			else if (i == 0)
			{
				if (dp[i][j - 1] == 0)
				{
					// 두 문자가 같으면
					if (a[i] == b[j])
					{
						// 최장 공통 부분 수열에 포함
						dp[i][j] = dp[i][j - 1] + 1;
					}
					// 두 문자가 다르면
					else
					{
						// 최장 공통 부분 수열에 미포함
						dp[i][j] = dp[i][j - 1];
					}
				}
				else
				{
					// 최장 공통 부분 수열에 미포함
					dp[i][j] = dp[i][j - 1];
				}
			}
			else if (j == 0)
			{
				if (dp[i - 1][j] == 0)
				{
					// 두 문자가 같으면
					if (a[i] == b[j])
					{
						// 최장 공통 부분 수열에 포함
						dp[i][j] = dp[i - 1][j] + 1;
					}
					// 두 문자가 다르면
					else
					{
						// 최장 공통 부분 수열에 미포함
						dp[i][j] = dp[i - 1][j];
					}
				}
				else
				{
					// 최장 공통 부분 수열에 미포함
					dp[i][j] = dp[i - 1][j];
				}
			}
		}
	}

	// 점화식 설정
	for (int i = 1; i < a.size(); i++)
	{
		for (int j = 1; j < b.size(); j++)
		{
			// printf("i = %d, j = %d, a = %c, b = %c\n", i, j, a[i], b[j]);

			// 두 문자가 같으면
			if (a[i] == b[j])
			{
				// 이전까지의 공통 문자열 길이에 1 더해준다
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			// 두 문자가 다르면
			else
			{
				// A의 이전과 B의 이전 중 더 큰 값을 선택한다
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}

	return;
}

int find_ans()
{
	int i = a.size() - 1;
	int j = b.size() - 1;
	int result = dp[i][j];

	while (1)
	{
		// printf("i = %d, j = %d, a = %c, b = %c\n", i, j, a[i], b[j]);

		// 두 문자가 같으면
		if (a[i] == b[j])
		{
			// 정답에 추가
			ans.push_back(a[i]);

			if ((i == 0) || (j == 0))
			{
				break;
			}
			else
			{
				// 이전 정답으로 이동
				i -= 1;
				j -= 1;
			}
		}
		else
		{
			if ((i == 0) && (j == 0))
			{
				break;
			}
			else if (i == 0)
			{
				j -= 1;
			}
			else if (j == 0)
			{
				i -= 1;
			}
			else
			{
				// 더 큰 쪽으로 이동
				if (dp[i - 1][j] > dp[i][j - 1])
				{
					i -= 1;
				}
				else
				{
					j -= 1;
				}
			}
		}
	}

	return result;
}

int main()
{
	int len = 0;
	char ch = 0;

	vector <int> tmp;

	a.reserve(MAX_LEN + 1);
	b.reserve(MAX_LEN + 1);
	ans.reserve(MAX_LEN + 1);

	// 첫번째
	while (1)
	{
		ch = getchar();

		// printf("%c\n", tmp);

		if (ch == '\n')
		{
			// a.push_back('\0');

			break;
		}
		else
		{
			a.push_back(ch);
		}
	}

	// print_a();

	// 두번째
	while (1)
	{
		ch = getchar();

		// printf("%c\n", tmp);

		if (ch == '\n')
		{
			// b.push_back('\0');

			break;
		}
		else
		{
			b.push_back(ch);
		}
	}

	// print_b();

	tmp.resize(b.size());

	for (int i = 0; i < a.size(); i++)
	{
		dp.push_back(tmp);
	}

	make_dp();

	// print_dp();

	len = find_ans();

	print_ans(len);

	return 0;
}

// 강사님 코드
/*
#include<stdio.h>
#include<string.h>
#include<algorithm>

using namespace std;

char a[1001], b[1001], c[1001];
int n, m;
int dp[1001][1001];

int main()
{
	int i, j;
	scanf("%s %s", a + 1, b + 1);
	n = strlen(a + 1);
	m = strlen(b + 1);

	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= m; j++)
		{
			dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			if (a[i] == b[j])dp[i][j] = dp[i - 1][j - 1] + 1;
		}
	}

	int x = n, y = m, cnt = dp[n][m];
	while (dp[x][y])
	{

		if (dp[x][y] == dp[x - 1][y])x--;
		else if (dp[x][y] == dp[x][y - 1])y--;
		else if (dp[x - 1][y - 1] == dp[x][y] - 1)
		{
			c[cnt--] = a[x];
			x--; y--;
		}
	}

	printf("%d\n%s", dp[n][m], c + 1);
	return 0;
}
*/
