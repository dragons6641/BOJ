#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 2000
#define MAX_M 1000000

int N;
int M;
// 1부터 사용
int inputList[MAX_N + 1] = { 0, };
// dp[S][E] : S번째부터 E번째까지 수열이 팰린드롬인지 아닌지
bool dp[MAX_N + 1][MAX_N + 1] = { 0, };

void solve(void)
{
	int S;
	int E;

	scanf("%d", &N);

	for (register int i = 1; i <= N; i++)
	{
		scanf("%d", &inputList[i]);
	}

	scanf("%d", &M);

	// 길이가 1인 경우
	for (register int i = 1; i <= N; i++)
	{
		dp[i][i] = true;
	}

	// 길이가 2인 경우
	for (register int i = 1; i < N; i++)
	{
		if (inputList[i] == inputList[i + 1])
		{
			dp[i][i + 1] = true;
		}
	}

	// 길이가 3 이상인 경우
	for (register int i = 3; i <= N; i++)
	{
		S = 1;
		E = S + i - 1;

		while (E <= N)
		{
			if ((dp[S + 1][E - 1]) && (inputList[S] == inputList[E]))
			{
				dp[S][E] = true;
			}

			S++;
			E++;
		}
	}

	for (register int i = 1; i <= M; i++)
	{
		scanf("%d %d", &S, &E);

		printf("%d\n", dp[S][E]);
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	solve();

	return 0;
}
