// KJO2573.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 300
#define MAX_M 300
#define MAX_ICE 10000
#define MAX_DIR 4

/*
#include "pch.h"
#include <iostream>
*/

typedef struct NODE
{
	// 빙산의 높이
	int h = 0;
	int r = 0;
	int c = 0;
}
node;

#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

// 빙산 높이 정보
vector < vector < int > > v;

// 빙산 위치 정보
vector < node > w;

// 방문 정보
vector < vector < int > > isVisited;

// bfs
queue < node > q;

// 4방향
// 상, 하, 좌, 우
int dr[MAX_DIR] = { -1, 1, 0, 0 };
int dc[MAX_DIR] = { 0, 0, -1, 1 };

int n = 0;
int m = 0;

void init_v()
{
	v.clear();
	v.resize(n);

	for (int r = 0; r < v.size(); r++)
	{
		v[r].resize(m);
	}

	return;
}

void init_isVisited()
{
	isVisited.clear();
	isVisited.resize(n);

	for (int r = 0; r < v.size(); r++)
	{
		isVisited[r].resize(m);
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

void print_w()
{
	printf("w : \n");

	for (int i = 0; i < w.size(); i++)
	{
		printf("%d, (%d, %d)\n", w[i].h, w[i].r, w[i].c);
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
			printf("%d ", isVisited[r][c]);
		}

		printf("\n");
	}

	return;
}

int check_sea(int j, int r, int c)
{
	int next_r = r + dr[j];
	int next_c = c + dc[j];

	// 상, 하 확인
	if ((next_r < 0) || (next_r >= v.size()))
	{
		// 바닷물 없음
		return 0;
	}
	// 좌, 우 확인
	else if ((next_c < 0) || (next_c >= v[r].size()))
	{
		// 바닷물 없음
		return 0;
	}
	// 빙산이 인접한 경우
	else if (v[next_r][next_c])
	{
		// 바닷물 없음
		return 0;
	}

	// 이외에는 바닷물 인접
	return 1;
}

int check_ice(int j, int y, int r, int c)
{
	int next_r = r + dr[j];
	int next_c = c + dc[j];

	// 상, 하 확인
	if ((next_r < 0) || (next_r >= v.size()))
	{
		// 빙산 없음
		return 0;
	}
	// 좌, 우 확인
	else if ((next_c < 0) || (next_c >= v[r].size()))
	{
		// 빙산 없음
		return 0;
	}
	// 바닷물이 인접한 경우
	else if (!v[next_r][next_c])
	{
		// 빙산 없음
		return 0;
	}
	// 현재 년도에 이미 방문한 경우
	else if (isVisited[next_r][next_c] == y)
	{
		// 빙산 없음
		return 0;
	}

	// 이외에는 빙산 인접
	return 1;
}

void simulate()
{
	// 빙산 위치마다
	for (int i = 0; i < w.size(); i++)
	{
		// 인접한 바닷물의 갯수
		int s = 0;
		int h = w[i].h;
		int r = w[i].r;
		int c = w[i].c;

		// 아직 해당 빙산이 남아있다면
		if (h)
		{
			// 4방향 탐색
			for (int j = 0; j < MAX_DIR; j++)
			{
				s += check_sea(j, r, c);
			}

			// 음수일 경우 주의!
			if (h - s < 0)
			{
				w[i].h = 0;
			}
			// 높이 줄여준다
			// 아직 반영은 X
			else
			{
				w[i].h = h - s;
			}
		}
	}

	// 한 바퀴 더 돌면서 높이 반영
	for (int i = 0; i < w.size(); i++)
	{
		v[w[i].r][w[i].c] = w[i].h;
	}

	return;
}

int bfs(int y)
{
	// 전체 빙산 갯수
	int cnt1 = 0;
	// 빙산 한 덩어리 갯수
	int cnt2 = 0;

	// 초기화 필수!
	// init_isVisited();

	node cur;

	// 처음 한 번만 하면 된다!
	for (int i = 0; i < w.size(); i++)
	{
		// 빙산 있다면
		if (w[i].h)
		{
			// 빙산 갯수 세주자
			cnt1 += 1;

			// 큐가 비어있다면
			if (q.empty())
			{
				// 그 곳이 시작점
				// 큐에 넣어주자
				cur.h = w[i].h;
				cur.r = w[i].r;
				cur.c = w[i].c;

				// 큐에 넣기 전 표시
				isVisited[cur.r][cur.c] = y;
				cnt2 += 1;

				q.push(cur);
			}	
		}
	}

	while (!q.empty())
	{
		// 다음 노드 가져오기
		cur = q.front();
		q.pop();

		// printf("cur = %d, (%d, %d)\n", cur.h, cur.r, cur.c);

		// 종료 조건 없음

		// 4방향 탐색
		for (int j = 0; j < MAX_DIR; j++)
		{
			int isPossible = check_ice(j, y, cur.r, cur.c);

			// printf("j = %d, isPossible = %d\n", j, isPossible);

			// 빙산이 인접해 있다면
			if (isPossible)
			{
				// 해당 빙산 탐색
				node next;

				next.r = cur.r + dr[j];
				next.c = cur.c + dc[j];
				next.h = v[next.r][next.c];

				// 아직 방문하지 않은 경우
				// 해당 자리가 빙산일 경우
				// 큐에 넣기 전 표시
				isVisited[next.r][next.c] = y;
				cnt2 += 1;

				q.push(next);
			}
		}
	}

	// printf("cnt1 = %d, cnt2 = %d\n", cnt1, cnt2);

	// 모두 녹았을 경우
	if (!cnt1)
	{
		return -1;
	}
	// 한 덩어리인 경우
	else if (cnt1 == cnt2)
	{
		// 계속 해야됨
		return 0;
	}
	// 두 덩어리 이상인 경우
	else
	{
		// 종료 해야됨
		return 1;
	}

	// error
	return -1;
}

int solve()
{
	int result = 0;

	// 1년마다
	while (1)
	{
		result += 1;

		// 1. 시뮬레이션
		simulate();

		// print_v();

		// 2. BFS
		// 현재 년수로 isVisited 갱신 필요 없이!
		int isFinished = bfs(result);

		// print_isVisited();

		// 이미 모두 녹았다면
		if (isFinished == -1)
		{
			// 답은 0
			result = 0;

			break;
		}
		// 두 덩어리 이상이면
		else if (isFinished == 1)
		{
			break;
		}
	}

	return result;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	scanf("%d %d", &n, &m);

	init_v();
	init_isVisited();

	w.reserve(MAX_ICE);

	for (int r = 0; r < v.size(); r++)
	{
		for (int c = 0; c < v[r].size(); c++)
		{
			scanf("%d", &v[r][c]);

			// 빙산이면
			if (v[r][c])
			{
				node tmp;

				tmp.h = v[r][c];
				tmp.r = r;
				tmp.c = c;

				w.push_back(tmp);
			}
		}
	}

	// print_v();
	// print_w();
	// print_isVisited();

	int ans = solve();

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
