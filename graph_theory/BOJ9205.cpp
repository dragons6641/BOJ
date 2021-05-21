/*
9205 맥주 마시면서 걸어가기
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_T 50
#define MAX_N 100
#define MAX_R 65536
#define MAX_C 65536
#define MAX_DIST 1000
#define START_POS 0

struct Node
{
	int r;
	int c;
};

int N;
int distList[MAX_N + 2] = { 0, };
// 0번째 : 출발지
// 1 ~ N번째 : 편의점
// N + 1번째 : 도착지
int distMap[MAX_N + 2][MAX_N + 2] = { 0, };
// 입력 위치 기록
Node posList[MAX_N + 2] = { {0, 0} };

int abs(int a, int b)
{
	return (a > b) ? (a - b) : (b - a);
}

// now번째 좌표와 그 이전 좌표들간의 거리 구하기
void calcDist(int now)
{
	for (int i = 0; i < now; i++)
	{
		int dist = abs(posList[now].r, posList[i].r) + abs(posList[now].c, posList[i].c);

		if (dist <= MAX_DIST)
		{
			distMap[now][i] = dist;
			distMap[i][now] = dist;
		}
	}

	return;
}

void initDistMap(void)
{
	for (int r = 0; r <= MAX_N + 1; r++)
	{
		for (int c = 0; c <= MAX_N + 1; c++)
		{
			distMap[r][c] = -1;
		}
	}

	return;
}

void initDistList(void)
{
	distList[START_POS] = 0;

	for (int i = 1; i <= MAX_N + 1; i++)
	{
		distList[i] = -1;
	}

	return;
}

void input(void)
{
	scanf("%d", &N);

	for (int i = 0; i <= N + 1; i++)
	{
		scanf("%d %d", &posList[i].r, &posList[i].c);

		calcDist(i);
	}

	return;
}

bool dijkstra(void)
{
	int debug = 1;
	bool visit[MAX_N + 2] = { false, };

	initDistList();

	while (true)
	{
		int minDist = MAX_DIST + 1;
		int minIndex = -1;

		// 가장 dist값이 낮은 인덱스를 선택
		for (int i = 0; i <= N + 1; i++)
		{
			if (visit[i])
			{
				continue;
			}
			else if ((distList[i] >= 0) && (minDist > distList[i]))
			{
				minDist = distList[i];
				minIndex = i;
			}
		}

		if (minIndex == -1)
		{
			break;
		}

		visit[minIndex] = true;

		// 해당 인덱스와 이어져 있는 다른 인덱스를 선택
		for (int i = 0; i <= N + 1; i++)
		{
			if (distMap[minIndex][i] == -1)
			{
				continue;
			}
			else if (distList[i] == -1)
			{
				distList[i] = distList[minIndex] + distMap[minIndex][i];
			}
			else if (distList[i] > distList[minIndex] + distMap[minIndex][i])
			{
				distList[i] = distList[minIndex] + distMap[minIndex][i];
			}

			if (distList[i] > MAX_DIST)
			{
				distList[i] = MAX_DIST;
			}
		}

		int debug = 1;
	}

	if (visit[N + 1])
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	setbuf(stdout, NULL);

	int T;
	bool ans;

	scanf("%d", &T);

	for (int test_case = 1; test_case <= T; test_case++)
	{
		initDistMap();

		input();

		ans = dijkstra();

		if (ans)
		{
			printf("happy\n");
		}
		else
		{
			printf("sad\n");
		}

		int debug = 1;
	}

	return 0;
}
