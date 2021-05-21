/*
13023 ABCDE
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 2000
#define MAX_M 2000
#define START_LEVEL 0
#define MAX_LEVEL 4

int N;
int M;
int ans = 0;
// 각 정점 방문 여부 표시
int visit[MAX_N] = { 0, };
// 각 정점마다 연결된 선의 개수
int adjCnt[MAX_N] = { 0, };
// 인접 리스트
int adjList[MAX_N][MAX_N] = { 0, };

void input(void)
{
	int A;
	int B;

	scanf("%d %d", &N, &M);

	for (int i = 0; i < M; i++)
	{
		scanf("%d %d", &A, &B);

		// A -> B 경로 표시
		adjList[A][adjCnt[A]++] = B;
		// B -> A 경로 표시
		adjList[B][adjCnt[B]++] = A;
	}

	return;
}

void dfs(int now, int level)
{
	if (level == MAX_LEVEL)
	{
		// 정답 찾았다
		ans = 1;

		return;
	}
	
	// 현재 정점에서 갈 수 있는 목록 탐색
	for (int c = 0; c < adjCnt[now]; c++)
	{
		if (visit[adjList[now][c]] == 0)
		{
			visit[adjList[now][c]] = 1;

			dfs(adjList[now][c], level + 1);

			visit[adjList[now][c]] = 0;
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

	setbuf(stdout, NULL);

	input();

	// 각 사람을 출발점으로 dfs()
	for (int i = 0; i < N; i++)
	{
		if (ans == 1)
		{
			break;
		}

		// 아직 해당 관계를 찾지 못했다면 계속 탐색
		visit[i] = 1;

		dfs(i, START_LEVEL);

		visit[i] = 0;
	}

	printf("%d\n", ans);

	return 0;
}
