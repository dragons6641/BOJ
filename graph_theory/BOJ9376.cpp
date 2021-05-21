// KJO9376.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_TESTCASE 100
#define MAX_H 100
#define MAX_W 100
#define MAX_ANS (MAX_H * MAX_W)
#define JS 2
#define MAX_DIR 4

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef struct NODE
{
	// 연 문의 갯수
	int d = 0;
	int r = 0;
	int c = 0;
}
node;

bool operator < (node x, node y)
{
	return x.d > y.d;
}

// 입력 벡터
vector < vector < char > > v;

// 방문 벡터
vector < vector < int > > isVisited;

// 정답 벡터
vector < vector < int > > a;

// 조력자 기준 bfs
// 죄수 1 기준 bfs
// 죄수 2 기준 bfs
vector < vector < int > > b;

// 시작점 저장 벡터
vector < node > s;

// 4방향
// 상, 하, 좌, 우
int dr[MAX_DIR] = { -1, 1, 0, 0 };
int dc[MAX_DIR] = { 0, 0, -1, 1 };

void init_v(int h, int w)
{
	// 바깥에 한 칸씩 추가로 만들어준다!
	v.resize(h + 2);

	for (int r = 0; r < v.size(); r++)
	{
		v[r].resize(w + 2, '.');
	}

	return;
}

void init_isVisited(int h, int w)
{
	// 바깥에 한 칸씩 추가로 만들어준다!
	isVisited.resize(h + 2);

	for (int r = 0; r < isVisited.size(); r++)
	{
		isVisited[r].resize(w + 2, 0);
	}

	return;
}

void init_a(int h, int w)
{
	// 바깥에 한 칸씩 추가로 만들어준다!
	a.resize(h + 2);

	for (int r = 0; r < a.size(); r++)
	{
		a[r].resize(w + 2, 0);
	}

	return;
}

void init_b(int h, int w)
{
	// 바깥에 한 칸씩 추가로 만들어준다!
	b.resize(h + 2);

	for (int r = 0; r < b.size(); r++)
	{
		b[r].resize(w + 2, 0);
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
			printf("%d ", isVisited[r][c]);
		}

		printf("\n");
	}

	return;
}

void print_a()
{
	printf("a : \n");

	for (int r = 0; r < a.size(); r++)
	{
		for (int c = 0; c < a[r].size(); c++)
		{
			printf("%d ", a[r][c]);
		}

		printf("\n");
	}

	return;
}

void print_b()
{
	printf("b : \n");

	for (int r = 0; r < b.size(); r++)
	{
		for (int c = 0; c < b[r].size(); c++)
		{
			printf("%d ", b[r][c]);
		}

		printf("\n");
	}

	return;
}

void print_ans()
{
	int ans = MAX_ANS;

	for (int r = 0; r < v.size(); r++)
	{
		for (int c = 0; c < v.size(); c++)
		{
			// 문만 확인!
			if (v[r][c] == '#')
			{
				ans = min(ans, a[r][c] - 2);
			}
		}
	}

	printf("%d\n", ans);

	return;
}

int check(int i, int r, int c)
{
	int next_r = r + dr[i];
	int next_c = c + dc[i];

	// 상, 하 체크
	if ((next_r < 0) || (next_r >= v.size()))
	{
		// 불가능
		return 0;
	}
	// 좌, 우 체크
	else if ((next_c < 0) || (next_c >= v[r].size()))
	{
		// 불가능
		return 0;
	}
	// 장애물 체크
	// 벽만 장애물!
	else if (v[next_r][next_c] == '*')
	{
		// 불가능
		return 0;
	}
	// 방문 여부 체크
	else if (isVisited[next_r][next_c])
	{
		// 불가능
		return 0;
	}

	// 나머지는 가능
	return 1;
}

void bfs(int i, int h, int w)
{
	// priority queue
	priority_queue < node > pq;

	// 귀찮아도 초기화는 각각 해주자!
	init_isVisited(h, w);
	init_b(h, w);

	// 첫 노드 큐에 넣자
	node cur = s[i];

	// 넣기 전 방문 표시
	isVisited[cur.r][cur.c] = 1;

	pq.push(cur);

	while (!pq.empty())
	{
		// 다음 노드 읽어오기
		cur = pq.top();
		pq.pop();

		// bfs 정답 기록
		b[cur.r][cur.c] = cur.d;

		// printf("d = %d, (%d, %d)\n", cur.d, cur.r, cur.c);

		// 종료 조건 없음

		// 각 방향마다 탐색
		for (int i = 0; i < MAX_DIR; i++)
		{
			int isPossible = check(i, cur.r, cur.c);

			// 이동 가능하면
			if (isPossible)
			{
				node next;

				next.r = cur.r + dr[i];
				next.c = cur.c + dc[i];

				// 다음 위치가 문일 경우
				if (v[next.r][next.c] == '#')
				{
					next.d = cur.d + 1;
				}
				// 다음 위치가 문이 아닐 경우
				else
				{
					next.d = cur.d;
				}

				// 방문하지 않았다면
				if (!isVisited[next.r][next.c])
				{
					// 넣기 전 방문 표시
					isVisited[next.r][next.c] = 1;

					// 해당 노드 큐에 넣자
					pq.push(next);
				}
			}
		}
	}

	// 정답 벡터에 반영
	for (int r = 0; r < v.size(); r++)
	{
		for (int c = 0; c < v[r].size(); c++)
		{
			a[r][c] += b[r][c];
		}
	}

	// print_a();
	// print_b();

	// 테스트 케이스 여러개일때는 꼭 마지막에 벡터 초기화!
	isVisited.clear();
	b.clear();

	return;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	int testcase = 0;

	scanf("%d", &testcase);

	for (int t = 1; t <= testcase; t++)
	{
		int h = 0;
		int w = 0;

		node tmp;

		scanf("%d %d", &h, &w);

		// 귀찮아도 초기화는 각각 해주자!
		init_v(h, w);
		init_a(h, w);

		s.reserve(JS + 1);

		tmp.d = 0;
		tmp.r = 0;
		tmp.c = 0;

		s.push_back(tmp);

		for (int r = 1; r < v.size() - 1; r++)
		{
			getchar();

			for (int c = 1; c < v[r].size() - 1; c++)
			{
				scanf("%c", &v[r][c]);

				// 죄수 위치 기록
				if (v[r][c] == '$')
				{
					tmp.d = 0;
					tmp.r = r;
					tmp.c = c;

					s.push_back(tmp);
				}
			}

			// getchar();
		}

		// print_v();
		
		// 조력자 기준 bfs
		// 죄수 1 기준 bfs
		// 죄수 2 기준 bfs
		for (int i = 0; i < s.size(); i++)
		{
			// printf("i = %d, (%d, %d)\n", i, s[i].r, s[i].c);

			bfs(i, h, w);
		}

		// print_a();

		// 문을 열 필요가 없다면
		if ((a[s[1].r][s[1].c] == 0) && (a[s[2].r][s[2].c] == 0))
		{
			// 0 출력
			printf("0\n");
		}
		// 하나라도 문을 열어야 한다면
		else
		{
			print_ans();
		}
		

		// 테스트 케이스 여러개일때는 꼭 마지막에 벡터 초기화!
		v.clear();
		a.clear();
		s.clear();
	}

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
