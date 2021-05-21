/*
12015 가장 긴 증가하는 부분 수열 2
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 1000000
#define MAX_M 1000000

int N;
int ans = 0;
// 1부터 시작
int inputList[MAX_N + 1] = { 0, };
// dp[k] : k번째 요소를 포함했을 경우, 가장 긴 증가하는 부분 수열
// 정답을 찾기 위해서는 최댓값을 갱신해 줘야 한다
// int dp[MAX_N + 1] = { 0, };
// 수열 기록
// 1부터 시작
int outputList[MAX_N + 1] = { 0, };

void input(void)
{
	scanf("%d", &N);

	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &inputList[i]);
	}

	return;
}

int lowerBound(int *data, int start, int end, int *target)
{
	int result = -1;

	while (start <= end)
	{
		int mid = (start + end) / 2;

		if (data[mid] >= *target)
		{
			result = mid;
			end = mid - 1;
		}
		else
		{
			start = mid + 1;
		}
	}

	return result;
}

void solve(void)
{
	/*
	// 초기값
	dp[1] = 1;
	ans = dp[1];

	for (int i = 2; i <= N; i++)
	{
		int maxValue = 0;
		int maxIndex = 0;

		for (int j = 1; j < i; j++)
		{
			// i번째 요소가 j번째 요소보다 커야 함
			// 최대값 갱신 가능하다면
			if ((inputList[i] > inputList[j]) && (maxValue < dp[j]))
			{
				maxValue = dp[j];
			}
		}

		dp[i] = maxValue + 1;

		if (ans < dp[i])
		{
			ans = dp[i];
		}
	}
	*/

	// 초기값
	outputList[1] = inputList[1];
	ans = 1;

	for (int i = 2; i <= N; i++)
	{
		// 현재 수열과 부분 수열 마지막 원소 비교
		// 현재 수열의 원소가 더 크면
		if (inputList[i] > outputList[ans])
		{
			// 부분 수열에 추가
			outputList[++ans] = inputList[i];
		}
		// 현재 수열의 원소가 더 작거나 같으면
		else
		{
			// lower bound를 찾음
			int idx = lowerBound(outputList, 1, ans, &inputList[i]);

			// 찾은 위치에 값 교체
			outputList[idx] = inputList[i];
		}

		int debug = 1;
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);

	setbuf(stdout, NULL);

	input();

	solve();

	printf("%d\n", ans);

	return 0;
}
