// KJO1600.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_W 200
#define MAX_H 200
#define MAX_K 30
#define MAX_DIR 12

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

typedef struct NODE
{
	// 동작 수
	int n = 0;
	// 사용한 말 이동 횟수
	int m = 0;
	int r = 0;
	int c = 0;
}
node;

// 격자판 벡터
vector < vector < int > > v;

// 방문 여부 표시
vector < vector < vector < int > > > isVisited;

// bfs
queue  < node > q;

// 이동 방향 4 + 8 = 12개
// 상, 하, 좌, 우, 1, 2, 4, 5, 7, 8, 10, 11
int dr[MAX_DIR] = { -1, 1, 0, 0, -2, -1, 1, 2, 2, 1, -1, -2 };
int dc[MAX_DIR] = { 0, 0, -1, 1, 1, 2, 2, 1, -1, -2, -2, -1 };

void init(int k, int w, int h)
{
	v.resize(h);
	isVisited.resize(h);

	for (int r = 0; r < v.size(); r++)
	{
		v[r].resize(w);
		isVisited[r].resize(w);

		for (int c = 0; c < v[r].size(); c++)
		{
			isVisited[r][c].resize(k + 1);
		}
	}

	return;
}

void print_v()
{
	printf("v : \n");

	for (int r = 0; r < v.size(); r++)
	{
		for (int c = 0; c < v[r].size(); c++)
		{
			printf("%d ", v[r][c]);
		}

		printf("\n");
	}

	return;
}

void print_isVisited()
{
	printf("isVisited : \n");

	for (int r = 0; r < isVisited.size(); r++)
	{
		for (int c = 0; c < isVisited[r].size(); c++)
		{
			for (int d = 0; d < isVisited[r][c].size(); d++)
			{
				printf("%d ", isVisited[r][c][d]);
			}

			printf("\n");
		}

		printf("\n");
	}

	return;
}

int check(int i, int k, int m, int r, int c)
{
	// 말 이동 횟수 다 사용했을 때
	if ((k == m) && (i >= 4))
	{
		// 불가능
		return 0;
	}
	// 말 이동 횟수 남아있을 때
	else
	{
		int next_r = r + dr[i];
		int next_c = c + dc[i];

		// row 범위 초과
		if ((next_r < 0) || (next_r >= v.size()))
		{
			// 불가능
			return 0;
		}
		// col 범위 초과
		else if ((next_c < 0) || (next_c >= v[r].size()))
		{
			// 불가능
			return 0;
		}
		// 장애물
		else if (v[next_r][next_c])
		{
			// 불가능
			return 0;
		}
		// 더 적거나 같은 말 이동 횟수를 사용하여 이미 방문했다면
		else
		{
			for (int j = 0; j <= m; j++)
			{
				if (isVisited[next_r][next_c][j])
				{
					// 불가능
					return 0;
				}
			}
		}
	}

	// 나머지는 이동 가능
	return 1;
}

int bfs(int k)
{
	// 첫 노드 큐에 넣기
	node cur;

	cur.n = 0;
	cur.m = 0;
	cur.r = 0;
	cur.c = 0;

	// 큐에 넣기 전 방문 표시
	isVisited[cur.r][cur.c][cur.m] = 1;

	q.push(cur);

	while (!q.empty())
	{
		// 현재 노드 정보 읽기
		cur = q.front();
		q.pop();

		// printf("n = %d, m = %d, (%d, %d)\n", cur.n, cur.m, cur.r, cur.c);

		// 도착했다면
		if ((cur.r == v.size() - 1) && (cur.c == v[cur.r].size() - 1))
		{
			// 동작 수가 답
			return cur.n;
		}

		// 각 방향마다 이동 가능 여부 체크
		for (int i = 0; i < MAX_DIR; i++)
		{
			int isPossible = check(i, k, cur.m, cur.r, cur.c);

			// 이동 가능하다면
			if (isPossible)
			{
				// 해당 정보를 큐에 추가
				node next;

				next.n = cur.n + 1;
				next.r = cur.r + dr[i];
				next.c = cur.c + dc[i];

				// 말 방법으로 이동
				if (i >= 4)
				{
					next.m = cur.m + 1;

					// 이미 들어가 있을수도 있다!
					// 들어가 있다면
					if (isVisited[next.r][next.c][next.m])
					{
						// 넣지 않는다
						continue;
					}
				}
				// 일반 이동
				else
				{
					next.m = cur.m;
				}

				// 큐에 넣기 전 방문 표시
				isVisited[next.r][next.c][next.m] = 1;

				q.push(next);
			}
		}
	}

	// 갈 수 없으면 -1
	return -1;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	int k = 0;
	int w = 0;
	int h = 0;
	int ans = 0;

	scanf("%d", &k);

	scanf("%d %d", &w, &h);

	init(k, w, h);

	for (int r = 0; r < v.size(); r++)
	{
		for (int c = 0; c < v[r].size(); c++)
		{
			scanf("%d", &v[r][c]);
		}
	}

	// print_v();
	// print_isVisited();

	ans = bfs(k);

	printf("%d\n", ans);

	return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
