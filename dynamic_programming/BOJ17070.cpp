// KJO17070.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 16
#define MAX_DIR 3

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

// 3방향
// 3시, 5시, 6시
int dr[MAX_DIR] = { 0, 1, 1 };
int dc[MAX_DIR] = { 1, 1, 0 };

typedef struct NODE
{
	// 방향
	int d = 0;
	int r = 0;
	int c = 0;
}
node;

// 지도 벡터
vector < vector < int > > v;

// 방문 벡터
vector < vector < vector < int > > > isVisited;

// bfs queue
queue < node > q;

void init_v(int n)
{
	v.clear();
	v.resize(n);

	for (int r = 0; r < v.size(); r++)
	{
		v[r].resize(n, 0);
	}

	return;
}

void init_isVisited(int n)
{
	isVisited.resize(MAX_DIR);

	for (int d = 0; d < isVisited.size(); d++)
	{
		isVisited[d].resize(n);

		for (int r = 0; r < v[d].size(); r++)
		{
			isVisited[d][r].resize(n);
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

	for (int d = 0; d < isVisited.size(); d++)
	{
		for (int r = 0; r < isVisited[d].size(); r++)
		{
			for (int c = 0; c < isVisited[d][r].size(); c++)
			{
				printf("%d ", isVisited[d][r][c]);
			}

			printf("\n");
		}

		printf("\n");
	}
}

int check(int i, int d, int r, int c)
{
	int next_r = r + dr[i];
	int next_c = c + dc[i];

	// 방향 먼저 체크
	// 90도 회전일 경우
	if ((i - d == -2) || (i - d == 2))
	{
		// 불가능
		return 0;
	}
	// 아래쪽 행 체크
	else if ((next_r < 0) || (next_r >= v.size()))
	{
		// 불가능
		return 0;
	}
	// 오른쪽 열 체크
	else if ((next_c < 0) || (next_c >= v[next_r].size()))
	{
		// 불가능
		return 0;
	}
	/*
	// 방문 체크
	else if (isVisited[i][next_r][next_c])
	{
		// 불가능
		return 0;
	}
	*/
	// 장애물 체크
	else
	{
		if (v[next_r][next_c])
		{
			// 불가능
			return 0;
		}
		// 5시 방향일 경우 장애물 추가 체크
		else if (i == 1)
		{
			if ((v[next_r][c]) || (v[r][next_c]))
			{
				// 불가능
				return 0;
			}
		}
	}

	// 나머지는 가능
	return 1;
}

int bfs()
{
	int result = 0;

	// 시작 노드 만들기
	node cur;

	cur.d = 0;
	cur.r = 0;
	cur.c = 1;

	// 큐에 넣기 전 표시
	isVisited[cur.d][cur.r][cur.c] = 1;

	// 시작 노드 큐에 넣기
	q.push(cur);

	while (!q.empty())
	{
		// 현재 노드 불러오기
		cur = q.front();
		q.pop();

		// printf("(%d, %d)\n", cur.r, cur.c);

		// 종료 조건 없음
		// 답일 경우
		if ((cur.r == v.size() - 1) && (cur.c == v[cur.r].size() - 1))
		{
			// 정답에 추가
			result += 1;

			// printf("result = %d\n", result);

			// 해당 노드는 더 진행할 필요 없다
			continue;
		}

		// 각 방향마다 체크
		for (int i = 0; i < MAX_DIR; i++)
		{
			int isPossible = check(i, cur.d, cur.r, cur.c);

			// printf("isPossible = %d, d = %d, (%d, %d)\n", isPossible, d, cur.r, cur.c);

			// 이동 가능하다면
			if (isPossible)
			{
				// 다음 노드 만들기
				node next;

				next.d = i;
				next.r = cur.r + dr[i];
				next.c = cur.c + dc[i];

				// 큐에 넣기 전 표시
				isVisited[next.d][next.r][next.c] = 1;

				// 다음 노드 큐에 넣기
				q.push(next);
			}
		}
	}

	return result;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	int n = 0;

	scanf("%d", &n);

	init_v(n);
	init_isVisited(n);

	for (int r = 0; r < v.size(); r++)
	{
		for (int c = 0; c < v[r].size(); c++)
		{
			scanf("%d", &v[r][c]);
		}
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
