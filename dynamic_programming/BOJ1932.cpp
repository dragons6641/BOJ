#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 500

#include <stdio.h>
#include <vector>

using namespace std;

// dp를 채워나갈 벡터
vector <vector <int> >dp;

int main()
{
	int n = 0;
	int input = 0;
	// 왼쪽 위
	int left = 0;
	// 오른쪽 위
	int right = 0;
	int cur = 0;
	int ans = 0;

	vector <int> tmp;

	scanf("%d", &n);

	// 벡터 사이즈
	tmp.resize(n + 1);

	for (int i = 0; i <= n; i++)
	{
		dp.push_back(tmp);
	}

	// 초기값은 따로 받는다
	scanf("%d", &dp[1][1]);

	// 입력 받으면서 바로 만들자
	for (int i = 2; i < dp.size(); i++)
	{
		for (int j = 1; j <= i; j++)
		{
			left = dp[i - 1][j - 1];
			right = dp[i - 1][j];

			scanf("%d", &input);

			// 삼각형의 왼쪽 끝이라면
			if (j == 1)
			{
				// 더해서 만들어 준다
				dp[i][j] = right + input;
			}
			// 삼각형의 오른쪽 끝이라면
			else if (j == i)
			{
				// 더해서 만들어 준다
				dp[i][j] = left + input;
			}
			// 삼각형의 가운데라면
			else
			{
				// 오른쪽이 더 크면
				if (left < right)
				{
					// 오른쪽 더한다
					dp[i][j] = right + input;
				}
				// 왼쪽이 더 크면
				else
				{
					// 왼쪽 더한다
					dp[i][j] = left + input;
				}
			}

			// 삼각형 다 만들고 마지막에
			if (i == dp.size() - 1)
			{
				cur = dp[i][j];

				// 최댓값 찾았으면
				if (cur > ans)
				{
					// 갱신
					ans = cur;
				}
			}
		}
	}

	printf("%d\n", ans);

	return 0;
}

// 강사님 코드
/*
#include<stdio.h>
#include<algorithm>

using namespace std;

int A[501][501];
int D[501][501];

int main()
{
	int i, j, n;
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= i; j++)
		{
			scanf("%d", &A[i][j]);
		}
	}

	int answer = 0;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= i; j++)
		{
			D[i][j] = max(D[i - 1][j - 1], D[i - 1][j]) + A[i][j];
			answer = max(answer, D[i][j]);
		}
	}

	printf("%d\n", answer);
	return 0;
}
*/
