#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 100
#define MAX_S 1000
#define MAX_M 1000

// 곡의 개수
int N;
// 시작 볼륨
int S;
// 최대 볼륨
int M;
// 각 곡이 시작하기 전에 줄 수 있는 볼륨의 차이
// 1부터 시작
int inputList[MAX_N + 1] = { 0, };
// dp[r][c] : r번째 곡을 c의 볼륨으로 연주할 수 있는지 여부
bool dp[MAX_N + 1][MAX_M + 1] = { 0, };

void inputData(void)
{
	scanf("%d %d %d", &N, &S, &M);

	for (register int i = 1; i <= N; i++)
	{
		scanf("%d", &inputList[i]);
	}

	return;
}

int solve(void)
{
	// 최댓값을 가져야 하므로 최솟값으로 초기화
	int result = -1;

	// 초기값
	dp[0][S] = true;

	// r번째 곡
	for (register int r = 0; r < N; r++)
	{
		// c의 볼륨
		for (register int c = 0; c <= M; c++)
		{
			// 가능하다면 다음 곡으로 확장
			if (dp[r][c])
			{
				// 볼륨 줄이는 경우
				if (c - inputList[r + 1] >= 0)
				{
					dp[r + 1][c - inputList[r + 1]] = true;
				}
				// 볼륨 늘리는 경우
				if (c + inputList[r + 1] <= M)
				{
					dp[r + 1][c + inputList[r + 1]] = true;
				}
			}
		}
	}

	// 최댓값 찾기
	for (register int c = 0; c <= M; c++)
	{
		if (dp[N][c])
		{
			result = c;
		}
	}

	return result;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	
	inputData();

	int ans = solve();

	printf("%d\n", ans);

	return 0;
}
