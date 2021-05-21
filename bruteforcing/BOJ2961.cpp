/*
A0 퍼킷
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 10
#define MAX_M ((int)1e9)
#define INF MAX_M + 1
#define START_S 1
#define START_B 0
#define START_LEVEL 0

struct Node
{
	// 신맛 정도(곱)
	int s;
	// 쓴맛 정도(합)
	int b;
};

// 재료 개수
int N;
// 최솟값을 가져야 함
// 최대값으로 초기화
int ans = INF;
// 선택한 갯수 체크
int cnt = 0;
// 답을 구했는지 확인
bool isFinished = false;
// 선택했는지 확인
// 1부터 사용
bool isSelected[MAX_N + 1] = { 0, };
// 음식의 정보
// 1부터 사용
Node inputList[MAX_N + 1] = { {0, 0}, };

void inputData(void)
{
	scanf("%d", &N);

	for (register int i = 1; i <= N; i++)
	{
		scanf("%d %d", &inputList[i].s, &inputList[i].b);
	}

	return;
}

// 음식 조합 만들기
void dfs(int s, int b, int level)
{
	// 정답이 0인 경우 가지치기
	if (isFinished)
	{
		return;
	}

	// 모든 음식을 확인했다면
	if (level == N)
	{
		// 하나도 선택하지 않은 경우
		if (cnt == 0)
		{
			// 정답 후보가 될 수 없다
			return;
		}

		int nowDiff = s - b;

		if (nowDiff < 0)
		{
			nowDiff = (-nowDiff);
		}

		// 정답 갱신
		if (ans > nowDiff)
		{
			ans = nowDiff;
		}

		return;
	}

	int nextS = s * inputList[level + 1].s;
	int nextB = b + inputList[level + 1].b;
	int nextDiff = nextS - nextB;

	if (nextDiff == 0)
	{
		ans = nextDiff;

		// 더 볼 필요 없다
		isFinished = true;

		return;
	}
	// 음수인 경우 양수로 바꾼다
	else if (nextDiff < 0)
	{
		nextDiff = (-nextDiff);
	}

	// 1. 선택하지 않거나
	dfs(s, b, level + 1);

	// 2. 선택하거나
	// 답이 될 수 없는 경우는 가지치기
	if (nextDiff < INF)
	{
		isSelected[level + 1] = true;
		cnt++;

		dfs(nextS, nextB, level + 1);

		isSelected[level + 1] = false;
		cnt--;
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	inputData();

	dfs(START_S, START_B, START_LEVEL);

	printf("%d\n", ans);

	return 0;
}
