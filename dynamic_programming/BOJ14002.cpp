/*
14002 가장 긴 증가하는 부분 수열 4
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 1000
#define MAX_M 1000

struct Node
{
	int length;
	int prevIndex;
};

int N;
int ansValue = 0;
int ansIndex = 0;
// 1부터 시작
int inputList[MAX_N + 1] = { 0, };
// dp[k] : k번째 요소를 포함했을 경우, 가장 긴 증가하는 부분 수열
// 정답을 찾기 위해서는 최댓값을 갱신해 줘야 한다
Node dp[MAX_N + 1] = { 0, };

void input(void)
{
	scanf("%d", &N);

	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &inputList[i]);
	}

	return;
}

void solve(void)
{
	// 초기값
	dp[1].length = 1;
	ansValue = dp[1].length;
	ansIndex = 1;

	for (int i = 2; i <= N; i++)
	{
		int maxValue = 0;
		int maxIndex = 0;

		for (int j = 1; j < i; j++)
		{
			// i번째 요소가 j번째 요소보다 커야 함
			// 최대값 갱신 가능하다면
			if ((inputList[i] > inputList[j]) && (maxValue < dp[j].length))
			{
				maxValue = dp[j].length;
				maxIndex = j;
			}
		}

		dp[i].length = maxValue + 1;
		dp[i].prevIndex = maxIndex;

		if (ansValue < dp[i].length)
		{
			ansValue = dp[i].length;
			ansIndex = i;
		}
	}

	return;
}

void traverse(int now)
{
	if (now == 0)
	{
		return;
	}

	traverse(dp[now].prevIndex);

	printf("%d ", inputList[now]);

	return;
}

void print(void)
{
	printf("%d\n", ansValue);

	traverse(ansIndex);

	printf("\n");

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);
	// freopen("input4.txt", "r", stdin);
	// freopen("input5.txt", "r", stdin);

	setbuf(stdout, NULL);

	input();

	solve();

	print();

	return 0;
}
