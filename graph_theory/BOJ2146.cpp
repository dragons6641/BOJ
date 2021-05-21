// KJO2146.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 100
#define MAX_DIR 4
#define MAX_ANS (MAX_N * MAX_N)

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
	// 다리 길이
	int d = 0;
	int r = 0;
	int c = 0;
}
node;

bool operator< (node a, node b)
{
	return a.d > b.d;
}

// 지도 저장 벡터
vector < vector < int > > v;

// 방문 표시 벡터
vector < vector < int > > isVisited;

// bfs
// queue < node > q;
priority_queue < node, vector <node> > pq;

// 이동 방향
// 상, 하, 좌, 우
int dr[MAX_DIR] = { -1, 1, 0, 0 };
int dc[MAX_DIR] = { 0, 0, -1, 1 };

void init(int n)
{
	v.resize(n);
	isVisited.resize(n);

	for (int r = 0; r < v.size(); r++)
	{
		v[r].resize(n);
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

int check_dfs(int i, int r, int c)
{
	// 상, 하 체크
	if ((i == 0) || (i == 1))
	{
		// 범위 확인
		if ((r + dr[i] < 0) || (r + dr[i] >= v.size()))
		{
			return 0;
		}
		// 방문 확인
		else if (v[r + dr[i]][c] != 1)
		{
			return 0;
		}
	}

	// 좌, 우 체크
	if ((i == 2) || (i == 3))
	{
		// 범위 확인
		if ((c + dc[i] < 0) || (c + dc[i] >= v[r].size()))
		{
			return 0;
		}
		// 방문 확인
		else if (v[r][c + dc[i]] != 1)
		{
			return 0;
		}
	}

	// 가능
	return 1;
}

int check_bfs(int i, int r, int c)
{
	// 상, 하 체크
	if ((i == 0) || (i == 1))
	{
		// 범위 확인
		if ((r + dr[i] < 0) || (r + dr[i] >= v.size()))
		{
			return 0;
		}
		// 방문 확인
		else if (isVisited[r + dr[i]][c])
		{
			return 0;
		}
	}

	// 좌, 우 체크
	if ((i == 2) || (i == 3))
	{
		// 범위 확인
		if ((c + dc[i] < 0) || (c + dc[i] >= v[r].size()))
		{
			return 0;
		}
		// 방문 확인
		else if (isVisited[r][c + dc[i]])
		{
			return 0;
		}
	}

	// 가능
	return 1;
}

void dfs(int r, int c, int cnt)
{
	// printf("cnt = %d, (%d, %d)\n", cnt, r, c);

	// 영역 표시 해주고
	// 하나 크게 표시해 줘야한다!
	v[r][c] = cnt + 1;

	// 각 방향마다
	for (int i = 0; i < MAX_DIR; i++)
	{
		// 이동 가능한지 체크
		int isPossible = check_dfs(i, r, c);

		// 이동 가능하다면
		if (isPossible)
		{
			// 해당 위치 탐색
			dfs(r + dr[i], c + dc[i], cnt);
		}
	}

	return;
}

int bfs(int idx, int r, int c)
{
	int result = 0;

	// 첫 노드는 큐에 넣자
	node cur;

	cur.d = 0;
	cur.r = r;
	cur.c = c;

	// 큐에 넣기 전 방문 표시
	isVisited[r][c] = 1;

	pq.push(cur);

	while (!pq.empty())
	{
		// 하나 빼자
		cur = pq.top();
		pq.pop();

		// 큐에서 뺼 때 방문 표시
		// isVisited[cur.r][cur.c] = 1;

		// printf("start = %d, cur = %d, d = %d, (%d, %d)\n", v[r][c], v[cur.r][cur.c], cur.d, cur.r, cur.c);
		// print_isVisited();

		// 다른 섬에 도착했고 바다가 아니면
		if ((v[r][c] != v[cur.r][cur.c]) && (v[cur.r][cur.c] > 1))
		{
			// 다리 길이 나왔다
			result = cur.d - 1;

			// 더 이상 할 필요 없음
			return result;
		}

		// 일반적인 경우
		// 4방향 확인
		for (int i = 0; i < MAX_DIR; i++)
		{
			// 이동 가능한지 체크
			int isPossible = check_bfs(i, cur.r, cur.c);

			// printf("i = %d, r = %d, c = %d, isPossible = %d\n", i, cur.r, cur.c, isPossible);

			// 이동 가능하다면
			if (isPossible)
			{
				// 큐에 넣을 노드 생성
				node next;
				next.r = cur.r + dr[i];
				next.c = cur.c + dc[i];

				// printf("start : %d, next : %d\n", v[r][c], v[next.r][next.c]);

				// 같은 구역일 경우
				if (v[r][c] == v[next.r][next.c])
				{
					// 거리는 따로 추가하지 않는다!
					next.d = cur.d;

					// 큐에 넣기 전 방문 표시
					isVisited[next.r][next.c] = 1;
				}
				// 같은 구역이 아닐 경우
				else
				{
					// 거리에 추가
					next.d = cur.d + 1;

					// 바다인 경우에만 큐에 넣기 전 방문 표시
					if (v[next.r][next.c] == 0)
					{
						isVisited[next.r][next.c] = 1;
					}
				}

				pq.push(next);
			}
		}
	}

	// 찾지 못하는 경우
	return MAX_ANS;
}

int main()
{
	// std::cout << "Hello World!\n"; 

	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);
	// freopen("input4.txt", "r", stdin);
	// freopen("input5.txt", "r", stdin);

	setbuf(stdout, NULL);

	int n = 0;
	int cnt = 0;
	int ans = MAX_ANS;
	int result = 0;
	int idx = 1;

	scanf("%d", &n);

	init(n);

	// print_isVisited();

	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < n; c++)
		{
			scanf("%d", &v[r][c]);
		}
	}

	// print_v();

	// 1. 섬 개수 세기 : DFS
	for (int r = 0; r < v.size(); r++)
	{
		for (int c = 0; c < v[r].size(); c++)
		{
			// 1일 경우 아직 안 센 육지이다
			if (v[r][c] == 1)
			{
				// 새로운 섬 추가
				cnt += 1;

				// 해당 위치 시작으로 dfs
				dfs(r, c, cnt);

				// printf("cnt = %d, (%d, %d)\n", cnt, r, c);
				// print_v();
			}
		}
	}

	// printf("cnt = %d\n", cnt);
	// print_v();

	// 2. 최단 거리 찾기 : BFS
	for (int r = 0; r < v.size(); r++)
	{
		for (int c = 0; c < v[r].size(); c++)
		{
			// 나누어진 영역이고 아직 방문하지 않았다면
			if ((v[r][c] > 1) && (!isVisited[r][c]))
			{
				for (int a = 0; a < n; a++)
				{
					for (int b = 0; b < n; b++)
					{
						isVisited[a][b] = 0;
					}
				}

				// print_isVisited();

				idx += 1;

				result = bfs(idx, r, c);

				// printf("result = %d, ans = %d, idx = %d, (%d, %d)\n", result, ans, idx, r, c);
				// print_v();
				// print_isVisited();

				// 최솟값이 정답
				if (result < ans)
				{
					ans = result;
				}
			}
		}
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
