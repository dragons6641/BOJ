// KJO17142.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 50
#define MAX_M 10
#define MAX_ANS (MAX_N * MAX_N)
#define MAX_DIR 4
#define MAX_W 10

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
	// 상태
	// 비활성 : 0, 활성 : 1
	int s = 0;
	// 시간
	int t = 0;
	int r = 0;
	int c = 0;
}
node;

// 연구소
vector < vector < int > > v;

// 바이러스 위치
vector < node > w;

// 방문 표시
vector < vector < int > > isVisited;

// 4방향
// 상, 하, 좌, 우
int dr[MAX_DIR] = { -1, 1, 0, 0 };
int dc[MAX_DIR] = { 0, 0, -1, 1 };

// 입력값
int n = 0;
int m = 0;

int ans = MAX_ANS + 1;

void init_v()
{
	v.clear();
	v.resize(n);

	for (int r = 0; r < v.size(); r++)
	{
		v[r].resize(n);
	}

	return;
}

void init_isVisited()
{
	isVisited.clear();
	isVisited.resize(n);

	for (int r = 0; r < isVisited.size(); r++)
	{
		isVisited[r].resize(n);
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
		printf("%d, (%d, %d)\n", w[i].s, w[i].r, w[i].c);
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

int check(int i, int r, int c)
{
	int next_r = r + dr[i];
	int next_c = c + dc[i];

	// printf("i = %d, next : (%d, %d)\n", i, next_r, next_c);
	// print_v();

	// 상, 하 확인
	if ((next_r < 0) || (next_r >= v.size()))
	{
		// printf("row\n");

		// 불가능
		return 0;
	}
	// 좌, 우 확인
	else if ((next_c < 0) || (next_c >= v[r].size()))
	{
		// printf("col\n");

		// 불가능
		return 0;
	}
	// 벽인지 확인
	else if (v[next_r][next_c] == 1)
	{
		// printf("V\n");

		// 불가능
		return 0;
	}
	// 더 짧은 시간 이내에 방문했는지 확인
	else if (isVisited[next_r][next_c] > 0)
	{
		// printf("isVisited\n");

		// 불가능
		return 0;
	}

	// 나머지 경우는 가능
	return 1;
}

void bfs()
{
	int result = 0;

	// bfs queue
	queue < node > q;

	// 시작 노드
	node cur;

	// 방문 배열 초기화
	init_isVisited();

	// 활성화된 바이러스 큐에 모두 넣기
	for (int i = 0; i < w.size(); i++)
	{
		// 활성화된 경우
		if (w[i].s == 1)
		{
			// 불러오기
			cur = w[i];

			// 큐에 넣기 전 표시
			isVisited[cur.r][cur.c] = cur.t;

			// 큐에 넣기
			q.push(cur);
		}
	}

	while (!q.empty())
	{
		// 노드 불러오기
		cur = q.front();
		q.pop();

		// printf("t = %d, (%d, %d)\n", cur.t, cur.r, cur.c);

		// 종료 조건
		// 최소 시간이 될 수 없을 경우
		if (cur.t >= ans)
		{
			// 불가능
			break;
		}

		// 각 방향마다 탐색
		for (int i = 0; i < MAX_DIR; i++)
		{
			int isPossible = check(i, cur.r, cur.c);

			// printf("isPossible = %d, i = %d\n", isPossible, i);

			// 확산 가능하다면
			if (isPossible)
			{
				// 다음 노드로 확정
				node next;

				next.s = 1;
				next.t = cur.t + 1;
				next.r = cur.r + dr[i];
				next.c = cur.c + dc[i];

				// 큐에 넣기 전 표시
				isVisited[next.r][next.c] = next.t;

				// 큐에 넣기
				q.push(next);
			}
		}
	}

	return;
}

int make_ans()
{
	// 바이러스가 퍼지는 최대 시간
	int result = 0;

	// print_v();
	// print_isVisited();

	for (int r = 0; r < isVisited.size(); r++)
	{
		for (int c = 0; c < isVisited[r].size(); c++)
		{
			// 모든 칸에는 바이러스가 차 있어야 함
			// 해당 칸이 빈 칸일 경우
			// 그 칸을 방문하지 않았다면
			if ((v[r][c] == 0) && (isVisited[r][c] == 0))
			{
				// 바이러스가 모두 퍼질 수 없는 경우
				// 불가능 알려주고 종료
				return -1;
			}
			// 최댓값 갱신
			// 단, 바이러스 있는 칸은 해당 X
			else if ((v[r][c] != 2) && (isVisited[r][c] > result))
			{
				result = isVisited[r][c];
			}
		}
	}

	// 바이러스가 모두 퍼져 있는 경우
	// 정답 갱신
	if (result < ans)
	{
		ans = result;
	}

	return result;
}

void backtrack(int cur, int depth)
{
	// printf("cur = %d, depth = %d\n", cur, depth);

	// 종료 조건
	// 활성화 바이러스 m개 골랐으면
	if (depth == m)
	{
		// 시뮬레이션
		bfs();

		// 정답 확인
		int result = make_ans();

		// printf("result = %d, ans = %d\n", result, ans);
		// print_w();

		return;
	}
	// 남은 비활성 바이러스를 다 선택해도 m개가 되지 않으면
	else if (w.size() - cur < m - depth)
	{
		// 불가능
		return;
	}

	// 일반적인 경우
	// 1. 해당 바이러스 활성화
	w[cur].s = 1;
	backtrack(cur + 1, depth + 1);

	// 2. 해당 바이러스 비활성화
	w[cur].s = 0;
	backtrack(cur + 1, depth);

	return;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	scanf("%d %d", &n, &m);

	init_v();

	w.reserve(MAX_ANS);

	for (int r = 0; r < v.size(); r++)
	{
		for (int c = 0; c < v[r].size(); c++)
		{
			scanf("%d", &v[r][c]);

			// 바이러스인 경우
			if (v[r][c] == 2)
			{
				node tmp;

				tmp.s = 0;
				tmp.t = 0;
				tmp.r = r;
				tmp.c = c;

				// 해당 위치 기록
				w.push_back(tmp);
			}
		}
	}

	// print_v();
	// print_w();
	// print_isVisited();

	// 하나일 경우에는 예외처리
	if (w.size() == 1)
	{
		// 해당 바이러스 활성화
		w[0].s = 1;

		// 시뮬레이션
		bfs();

		// 정답 확인
		int result = make_ans();

		// printf("result = %d, ans = %d\n", result, ans);
		// print_w();
	}
	// 일반적인 경우
	else
	{
		backtrack(0, 0);
	}

	// 정답이 바뀌지 않았다면
	if (ans == MAX_ANS + 1)
	{
		// 애초에 불가능!
		ans = -1;
	}

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
