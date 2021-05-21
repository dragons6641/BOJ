/*
13398 연속합 2
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 100000
#define MIN_M -1000
#define MAX_M 1000
#define MAX_DELETE 1
#define MIN_DP (MAX_N * MIN_M)
#define MAX_DP (MAX_N * MAX_M)

int N;
int ans = MIN_DP - 1;
// 1부터 시작
int inputList[MAX_N + 1] = { 0, };
// dp[a][b] : a번째까지의 연속합, b개 삭제
int dp[MAX_N + 1][MAX_DELETE + 1] = { 0, };

void input(void)
{
	scanf("%d", &N);

	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &inputList[i]);
	}

	return;
}

/*
void solve(void)
{
	int max1 = MIN_DP - 1;
	int max2 = MIN_DP - 1;
	int flag = 0;
	int cnt;

	dp[1] = inputList[1];
	ans = inputList[1];

	for (int i = 2; i <= N; i++)
	{
		// 더할 수가 양수이거나 0인 경우
		if (inputList[i] >= 0)
		{
			// 지금까지의 합이 양수이거나 0인 경우
			if (dp[i - 1] >= 0)
			{
				// 기존 합에 추가
				dp[i] = dp[i - 1] + inputList[i];
			}
			// 지금까지의 합이 음수인 경우
			else
			{
				// 새로운 수부터 합 계산
				dp[i] = inputList[i];
			}
		}
		// 더할 수가 음수인 경우
		else
		{
			// 새로운 수가 지금까지의 합보다 더 크다면
			if (inputList[i] > dp[i - 1])
			{
				// 새로운 수부터 합 계산
				dp[i] = inputList[i];
			}
			// 새로운 수가 지금까지의 합보다 작거나 같다면
			else
			{
				// 기존 합에 추가
				dp[i] = dp[i - 1] + inputList[i];
			}
		}

		// 정답 갱신
		if (ans < dp[i])
		{
			ans = dp[i];
		}
	}

	for (cnt = 1; cnt <= N; cnt++)
	{
		if (dp[cnt] <= 0)
		{
			flag = 1;

			break;
		}

		if (max1 < dp[cnt])
		{
			max1 = dp[cnt];
		}
	}

	if (flag == 0)
	{
		return;
	}

	for (int i = cnt + 1; i <= N; i++)
	{
		if (max2 < dp[i])
		{
			max2 = dp[i];
		}

		if ((dp[i] < 0) || (i == N))
		{
			if (ans < max1 + max2)
			{
				ans = max1 + max2;
				max1 = max2;
				max2 = MIN_DP - 1;
			}
		}
	}

	return;
}
*/

void solve(void)
{
	// 초기값
	dp[1][0] = inputList[1];
	dp[1][1] = 0;
	ans = inputList[1];

	for (int i = 2; i <= N; i++)
	{
		/*
		dp[i][0] = (inputList[i] + ((dp[i - 1][0] > 0) ? dp[i - 1][0] : 0));
		dp[i][1] = ((dp[i - 1][0] > dp[i - 1][1] + inputList[i]) ? dp[i - 1][0] : (dp[i - 1][1] + inputList[i]));
		*/

		if (dp[i - 1][0] > 0)
		{
			dp[i][0] = dp[i - 1][0] + inputList[i];
		}
		else
		{
			dp[i][0] = inputList[i];
		}

		if (dp[i - 1][0] > dp[i - 1][1] + inputList[i])
		{
			dp[i][1] = dp[i - 1][0];
		}
		else
		{
			dp[i][1] = dp[i - 1][1] + inputList[i];
		}

		for (int j = 0; j <= MAX_DELETE; j++)
		{
			if (ans < dp[i][j])
			{
				ans = dp[i][j];
			}
		}
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);
	// freopen("input4.txt", "r", stdin);
	// freopen("input5.txt", "r", stdin);
	// freopen("input6.txt", "r", stdin);
	// freopen("input7.txt", "r", stdin);
	// freopen("input8.txt", "r", stdin);
	// freopen("input9.txt", "r", stdin);
	// freopen("input10.txt", "r", stdin);
	// freopen("input11.txt", "r", stdin);
	// freopen("input12.txt", "r", stdin);
	// freopen("input13.txt", "r", stdin);
	// freopen("input14.txt", "r", stdin);
	// freopen("input15.txt", "r", stdin);
	// freopen("input16.txt", "r", stdin);
	// freopen("input17.txt", "r", stdin);
	// freopen("input18.txt", "r", stdin);
	// freopen("input19.txt", "r", stdin);
	// freopen("input20.txt", "r", stdin);
	// freopen("input21.txt", "r", stdin);
	// freopen("input22.txt", "r", stdin);
	// freopen("input23.txt", "r", stdin);
	// freopen("input24.txt", "r", stdin);
	// freopen("input25.txt", "r", stdin);
	// freopen("input26.txt", "r", stdin);

	setbuf(stdout, NULL);

	input();

	solve();

	printf("%d\n", ans);

	return 0;
}
