/*
F3 자동차경주대회
*/

#define _CRT_SECURE_NO_WARNINGS
#define ll long long

#include <stdio.h>

#define MAX_N 100
#define MAX_TIME (int)(((ll)1 << (ll)31) - (ll)1)
#define START_DIST 0
#define START_TIME 0
#define START_LEVEL 0

// 정비를 받지 않고 갈 수 있는 최대 거리
int M;
// 정비소의 갯수
int N;
// 최소 시간
int minTime = MAX_TIME;
// 최소 정비소
int minN = MAX_N;
// 거리
// 1부터 시작
int distList[MAX_N + 2] = { 0, };
// 시간
// 1부터 시작
int timeList[MAX_N + 2] = { 0, };
// 거리 prefixSum
int prefixDist[MAX_N + 2] = { 0, };
// 방문한 정비소 목록
// 1부터 시작
int outputList[MAX_N + 2] = { 0, };
// DP[k] : k번째 정비소를 마지막으로 정비하게 될 때의 최소 시간
int dp[MAX_N + 2] = { 0, };
// 이전에 방문한 정비소 표시
int prevList[MAX_N + 2] = { 0, };
// 방문한 정비소는 True로 표시
// bool visit[MAX_N + 2] = { 0, };

void inputData(void)
{
	scanf("%d", &M);
	scanf("%d", &N);

	for (register int i = 1; i <= N + 1; i++)
	{
		scanf("%d", &distList[i]);

		prefixDist[i] = prefixDist[i - 1] + distList[i];
	}

	for (register int i = 1; i <= N; i++)
	{
		scanf("%d", &timeList[i]);
	}

	return;
}

/*
// DFS : Time Limit Exceed
void run(int nowDist, int nowTime, int level)
{
	// 갈 수 있는 거리를 초과했다면
	if (M < nowDist)
	{
		// 불가능
		return;
	}

	// 이미 정답이 될 수 없다면
	if (minTime <= nowTime)
	{
		// 불가능
		return;
	}

	// 끝까지 왔다면
	if (level == N)
	{
		// 정답 갱신
		int cnt = 0;

		minTime = nowTime;

		// 목록도 함께 갱신
		for (register int i = 1; i <= N; i++)
		{
			if (visit[i])
			{
				outputList[++cnt] = i;
			}
		}

		minN = cnt;

		return;
	}

	// 1. 방문하지 않는 경우
	// 거리는 증가, 시간은 그대로
	run(nowDist + distList[level + 1], nowTime, level + 1);

	// 2. 방문하는 경우
	// 거리는 0, 시간은 증가
	visit[level + 1] = true;

	run(distList[level + 1], nowTime + timeList[level + 1], level + 1);

	visit[level + 1] = false;

	return;
}
*/

// DP
void solve(void)
{
	// 시작점과 도착점 포함
	for (register int i = 1; i <= N + 1; i++)
	{
		int minIndex = 0;
		int minValue = MAX_TIME;

		for (register int j = 0; j < i; j++)
		{
			// 거리가 최대 이동 거리를 초과하면
			if (prefixDist[i] - prefixDist[j] > M)
			{
				// 불가능
				continue;
			}

			// 최소 시간이라면
			if (minValue >= dp[j])
			{
				// 갱신
				minIndex = j;
				minValue = dp[j];
			}
		}

		dp[i] = minValue + timeList[i];
		prevList[i] = minIndex;
	}

	return;
}

void traverse(int now, int level)
{
	if (prevList[now] == 0)
	{
		printf("%d\n", level);

		return;
	}

	traverse(prevList[now], level + 1);

	printf("%d ", prevList[now]);

	return;
}

void print(void)
{
	/*
	printf("%d\n", minTime);
	printf("%d\n", minN);

	for (register int i = 1; i <= minN; i++)
	{
		printf("%d ", outputList[i]);
	}
	*/

	printf("%d\n", dp[N + 1]);

	/*
	if (dp[N + 1] == 0)
	{
		return;
	}
	*/

	// 재귀 순회로 정답 출력
	traverse(N + 1, START_LEVEL);

	printf("\n");

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);

	inputData();

	// run(distList[0], START_TIME, START_LEVEL);

	solve();

	print();

	return 0;
}
