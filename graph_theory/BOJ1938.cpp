// KJO1938.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 50
#define MAX_DIR 4
#define LEN 3
#define DIR 2

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
	// 이동 횟수
	int m = 0;
	// 0 : 가로, 1 : 세로
	int d = 0;
	int r = 0;
	int c = 0;
}
node;

// 지도 저장 벡터
vector < vector < char > > v;

// 이동 표시 벡터
vector < vector < vector < int > > > isVisited;

// 시작점
vector < node > b;

// 도착점
vector < node > e;

// bfs
queue < node > q;

// 4방향 + 회전
// 상, 하, 좌, 우
int dr[MAX_DIR] = { -1, 1, 0, 0 };
int dc[MAX_DIR] = { 0, 0, -1, 1 };

void init(int n)
{
	b.reserve(LEN);
	e.reserve(LEN);

	v.resize(n);
	isVisited.resize(n);

	for (int r = 0; r < isVisited.size(); r++)
	{
		v[r].resize(n);
		isVisited[r].resize(n);

		for (int c = 0; c < isVisited[r].size(); c++)
		{
			isVisited[r][c].resize(DIR);
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
			printf("%c", v[r][c]);
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

int check_m(int i, int d, int r, int c)
{
	// 가로
	if (d == 0)
	{
		// 1칸 상, 하 체크
		if ((r + dr[i] < 0) || (r + dr[i] >= v.size()))
		{
			// 불가능
			return 0;
		}
		// 3칸 좌, 우 체크
		else if ((c + dc[i] < 1) || (c + dc[i] >= v[r].size() - 1))
		{
			// 불가능
			return 0;
		}

		// 장애물 체크
		for (int j = -1; j < LEN - 1; j++)
		{
			if (v[r + dr[i]][c + dc[i] + j] == '1')
			{
				// 불가능
				return 0;
			}
		}
	}
	// 세로
	else if (d == 1)
	{
		// 3칸 상, 하 체크
		if ((r + dr[i] < 1) || (r + dr[i] >= v.size() - 1))
		{
			// 불가능
			return 0;
		}
		// 1칸 좌, 우 체크
		else if ((c + dc[i] < 0) || (c + dc[i] >= v[r].size()))
		{
			// 불가능
			return 0;
		}

		// 장애물 체크
		for (int j = -1; j < LEN - 1; j++)
		{
			if (v[r + dr[i] + j][c + dc[i]] == '1')
			{
				// 불가능
				return 0;
			}
		}
	}

	// 방문 여부 체크
	if (isVisited[r + dr[i]][c + dc[i]][d])
	{
		// 불가능
		return 0;
	}

	// 나머지는 가능
	return 1;
}

int check_t(int d, int r, int c)
{
	// 3칸 상, 하 체크
	if ((r < 1) || (r >= v.size() - 1))
	{
		// 불가능
		return 0;
	}
	// 3칸 좌, 우 체크
	else if ((c < 1) || (c >= v[r].size() - 1))
	{
		// 불가능
		return 0;
	}

	// 방문 여부 체크
	if (isVisited[r][c][(d + 1) % DIR])
	{
		// 불가능
		return 0;
	}
	// 장애물 체크
	else
	{
		// 3 * 3 구역 체크
		for (int i = r - (int)(LEN / 2); i <= r + (int)(LEN / 2); i++)
		{
			for (int j = c - (int)(LEN / 2); j <= c + (int)(LEN / 2); j++)
			{
				if (v[i][j] == '1')
				{
					// 불가능
					return 0;
				}
			}
		}
	}

	// 나머지는 가능
	return 1;
}

int bfs()
{
	// 끝 점 방향
	int dir = -1;

	// 넣을 노드
	node next;

	// 첫 중심점 찾기
	node cur = b[(int)(LEN / 2)];

	// 시작 방향 찾기
	// row가 같으면
	if (b[0].r == b[b.size() - 1].r)
	{
		// 가로 0
		cur.d = 0;
	}
	// col이 같으면
	else if (b[0].c == b[b.size() - 1].c)
	{
		// 세로 1
		cur.d = 1;
	}

	// 끝 방향 찾기
	// row가 같으면
	if (e[0].r == e[e.size() - 1].r)
	{
		// 가로 0
		dir = 0;
	}
	// col이 같으면
	else if (e[0].c == e[e.size() - 1].c)
	{
		// 세로 1
		dir = 1;
	}

	// 큐에 넣기 전 방향으로 표시
	isVisited[cur.r][cur.c][cur.d] = 1;

	q.push(cur);

	while (!q.empty())
	{
		int isPossible = 0;

		// 다음 노드 꺼내기
		cur = q.front();
		q.pop();

		// printf("m = %d, d = %d, (%d, %d)\n", cur.m, cur.d, cur.r, cur.c);

		// 도착했다면
		if ((cur.r == e[(int)(LEN / 2)].r) && (cur.c == e[(int)(LEN / 2)].c) && (cur.d == dir))
		{
			// 최소 동작 횟수
			return cur.m;
		}

		// 각 방향마다 체크
		for (int i = 0; i < MAX_DIR; i++)
		{
			isPossible = check_m(i, cur.d, cur.r, cur.c);

			// 가능하다면
			if (isPossible)
			{
				// 해당 정보를 큐에 넣기
				next.m = cur.m + 1;
				next.d = cur.d;
				next.r = cur.r + dr[i];
				next.c = cur.c + dc[i];

				// 큐에 넣기 전 방향으로 표시
				isVisited[next.r][next.c][next.d] = 1;

				q.push(next);
			}
		}

		// 회전 체크
		isPossible = check_t(cur.d, cur.r, cur.c);

		// 가능하다면
		if (isPossible)
		{
			// 해당 정보를 큐에 넣기
			next.m = cur.m + 1;
			next.d = (cur.d + 1) % DIR;
			next.r = cur.r;
			next.c = cur.c;

			// 큐에 넣기 전 방향으로 표시
			isVisited[next.r][next.c][next.d] = 1;

			q.push(next);
		}
	}

	// 이동이 불가능할 경우
	return 0;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	int n = 0;

	scanf("%d", &n);

	init(n);

	for (int r = 0; r < v.size(); r++)
	{
		getchar();

		for (int c = 0; c < v[r].size(); c++)
		{
			scanf("%c", &v[r][c]);

			// 시작점일 경우
			if (v[r][c] == 'B')
			{
				node bb;

				bb.m = 0;
				bb.d = -1;
				bb.r = r;
				bb.c = c;

				b.push_back(bb);
			}

			// 도착점일 경우
			if (v[r][c] == 'E')
			{
				node ee;

				ee.m = 0;
				ee.d = -1;
				ee.r = r;
				ee.c = c;

				e.push_back(ee);
			}
		}

		// getchar();
	}

	// print_v();
	// print_isVisited();

	int ans = bfs();

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
