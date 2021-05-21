// KJO7569.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_M 100
#define MAX_N 100
#define MAX_H 100
#define MAX_DIR 6

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
	// 날짜
	int d = -1;
	int z = -1;
	int r = -1;
	int c = -1;
}
node;

// 입력 저장 벡터
vector < vector < vector < int > > > v;

// 방문 체크 벡터
vector < vector < vector < int > > > isVisited;

// BFS 큐
queue < node > q;

// 6방향 저장
// 상, 하, 앞, 뒤, 좌, 우
int dz[MAX_DIR] = { -1, 1, 0, 0, 0, 0 };
int dr[MAX_DIR] = { 0, 0, -1, 1, 0, 0 };
int dc[MAX_DIR] = { 0, 0, 0, 0, -1, 1 };

void init(int m, int n, int h)
{
	isVisited.resize(h);

	for (int z = 0; z < isVisited.size(); z++)
	{
		isVisited[z].resize(n);

		for (int r = 0; r < isVisited[z].size(); r++)
		{
			isVisited[z][r].resize(m);
		}
	}

	return;
}

void print_v()
{
	printf("v : \n");

	for (int z = 0; z < v.size(); z++)
	{
		for (int r = 0; r < v[z].size(); r++)
		{
			for (int c = 0; c < v[z][r].size(); c++)
			{
				printf("%d ", v[z][r][c]);
			}

			printf("\n");
		}
	}

	return;
}

int check(int i, int z, int r, int c)
{
	// printf("check : (%d, %d, %d, %d)\n", i, z, r, c);

	// 상, 하 검사
	if ((i == 0) || (i == 1))
	{
		// 범위 벗어나면
		if ((z + dz[i] < 0) || (z + dz[i] >= v.size()))
		{
			// printf("case 1\n");

			return 0;
		}
		// 토마토가 없거나 이미 익은 토마토라면
		else if (v[z + dz[i]][r][c] != 0)
		{
			// printf("case 2\n");

			return 0;
		}
		// 이미 방문했다면
		else if (isVisited[z + dz[i]][r][c] != 0)
		{
			return 0;
		}
	}

	// 앞, 뒤 검사
	else if ((i == 2) || (i == 3))
	{
		// 범위 벗어나면
		if ((r + dr[i] < 0) || (r + dr[i] >= v[z].size()))
		{
			// printf("case 3\n");

			return 0;
		}
		// 토마토가 없거나 이미 익은 토마토라면
		else if (v[z][r + dr[i]][c] != 0)
		{
			// printf("case 4\n");

			return 0;
		}
		// 이미 방문했다면
		else if (isVisited[z][r + dr[i]][c] != 0)
		{
			return 0;
		}
	}

	// 좌, 우 검사
	else if ((i == 4) || (i == 5))
	{
		// 범위 벗어나면
		if ((c + dc[i] < 0) || (c + dc[i] >= v[z][r].size()))
		{
			// printf("case 5\n");

			return 0;
		}
		// 토마토가 없거나 이미 익은 토마토라면
		else if (v[z][r][c + dc[i]] != 0)
		{
			// printf("case 6\n");

			return 0;
		}
		// 이미 방문했다면
		else if (isVisited[z][r][c + dc[i]] != 0)
		{
			return 0;
		}
	}

	// 정상
	return 1;
}

int bfs()
{
	int result = 0;

	// printf("q : %d\n", q.size());

	while (!q.empty())
	{
		// 현재 노드 정보 불러오기
		node cur = q.front();
		q.pop();

		int d = cur.d;
		int z = cur.z;
		int r = cur.r;
		int c = cur.c;

		// printf("cur : (%d, %d, %d, %d)\n", d, z, r, c);

		// 가장 늦게 익는 토마토 일수 기록
		result = d - 1;

		// 입력 벡터에도 갱신
		v[z][r][c] = d;

		// 6방향 검사
		for (int i = 0; i < MAX_DIR; i++)
		{
			// 가능한지 검사 함수
			int isPossible = check(i, z, r, c);

			// printf("isPossible = %d\n", isPossible);

			// 해당 방향 인접한 토마토가 익었다면
			if (isPossible)
			{
				// 그 토마토를 큐에 추가
				node next;

				next.d = d + 1;
				next.z = z + dz[i];
				next.r = r + dr[i];
				next.c = c + dc[i];

				// 방문 체크 해주자!
				isVisited[next.z][next.r][next.c] = 1;

				q.push(next);
			}
		}
	}

	// 검사
	for (int z = 0; z < v.size(); z++)
	{
		for (int r = 0; r < v[z].size(); r++)
		{
			for (int c = 0; c < v[z][r].size(); c++)
			{
				// 안 익은 토마토가 있다면 -1
				if (v[z][r][c] == 0)
				{
					return -1;
				}
			}
		}
	}

	// 모두 익을 때까지 걸리는 시간
	return result;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	int m = 0;
	int n = 0;
	int h = 0;
	int ans = 0;
	int cnt = 0;

	scanf("%d %d %d", &m, &n, &h);

	init(m, n, h);

	v.reserve(h);

	for (int z = 0; z < h; z++)
	{
		vector < vector < int > > z_tmp;

		z_tmp.reserve(n);

		for (int r = 0; r < n; r++)
		{
			vector < int > r_tmp;

			r_tmp.reserve(m);

			for (int c = 0; c < m; c++)
			{
				int c_tmp = 0;

				scanf("%d", &c_tmp);

				// 안 익은 토마토 개수 세기
				if (c_tmp == 0)
				{
					cnt += 1;
				}
				// 익은 토마토는 큐에 대기
				else if (c_tmp == 1)
				{
					node n_tmp;

					// 첫날은 1, 나중에 하나 빼주자!
					n_tmp.d = 1;
					n_tmp.z = z;
					n_tmp.r = r;
					n_tmp.c = c;

					q.push(n_tmp);
				}

				r_tmp.push_back(c_tmp);
			}

			// printf("r_tmp : %d\n", r_tmp.size());

			z_tmp.push_back(r_tmp);
		}

		// printf("z_tmp : %d\n", z_tmp.size());

		v.push_back(z_tmp);
	}

	// printf("v : %d\n", v.size());

	// print_v();

	// 모든 토마토가 익어있는 상태
	if (cnt == 0)
	{
		ans = 0;
	}
	else
	{
		ans = bfs();
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
