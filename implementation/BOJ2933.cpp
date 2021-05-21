// KJO2933.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_R 100
#define MAX_C 100
#define MAX_N 100
#define MAX_DIR 4

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
	int r = -1;
	int c = -1;
}
node;

// 동굴 상태 벡터
vector < vector < char > > v;

// 방문 여부 벡터
vector < vector < int > > isVisited;

// 4방향
// 상, 하, 좌, 우
int dr[MAX_DIR] = { -1, 1, 0, 0 };
int dc[MAX_DIR] = { 0, 0, -1, 1 };

// 파괴된 미네랄 위치
int mine_r = -1;
int mine_c = -1;

// 입력값
int rows = 0;
int cols = 0;

void init_v()
{
	v.resize(rows);

	for (int r = 0; r < rows; r++)
	{
		v[r].resize(cols);
	}

	return;
}

void init_isVisited()
{
	isVisited.resize(rows);

	for (int r = 0; r < rows; r++)
	{
		isVisited[r].resize(cols);
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

void print_ans()
{
	// printf("v : \n");

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

int throw_stick(int i, int h)
{
	// 홀수번째일 경우
	if (i % 2)
	{
		// 왼쪽 -> 오른쪽
		for (int c = 0; c < v[h].size(); c++)
		{
			// 미네랄 만나면
			if (v[h][c] == 'x')
			{
				// 미네랄 파괴
				v[h][c] = '.';

				// 위치 표시
				mine_r = h;
				mine_c = c;

				// 막대도 끝
				return 1;
			}
		}
	}
	// 짝수번째일 경우
	else
	{
		// 오른쪽 -> 왼쪽
		for (int c = v[h].size() - 1; c >= 0; c--)
		{
			// 미네랄 만나면
			if (v[h][c] == 'x')
			{
				// 미네랄 파괴
				v[h][c] = '.';

				// 위치 표시
				mine_r = h;
				mine_c = c;

				// 막대도 끝
				return 1;
			}
		}
	}

	// 파괴된 것 없음
	return 0;
}

int check_bfs(int j, int r, int c)
{
	int next_r = r + dr[j];
	int next_c = c + dc[j];

	// 상, 하 확인
	if ((next_r < 0) || (next_r >= v.size()))
	{
		// 불가능
		return 0;
	}
	// 좌, 우 확인
	else if ((next_c < 0) || (next_c >= v[next_r].size()))
	{
		// 불가능
		return 0;
	}
	// 해당 방향이 빈 공간이라면
	else if (v[next_r][next_c] == '.')
	{
		// 불가능
		return 0;
	}
	// 이미 방문했다면
	else if (isVisited[next_r][next_c])
	{
		// 불가능
		return 0;
	}

	// 나머지 경우에는 가능
	return 1;
}

void bfs(int r, int c)
{
	isVisited.clear();
	init_isVisited();

	// bfs queue
	queue < node > q;

	// 시작 노드 추가
	node cur;

	cur.r = r;
	cur.c = c;

	// 추가하기 전 방문 표시
	isVisited[r][c] = 1;

	q.push(cur);

	while (!q.empty())
	{
		// 다음 노드 읽어오기
		cur = q.front();
		q.pop();

		// printf("(%d, %d)\n", cur.r, cur.c);

		// 종료조건 없음

		// 4방향 가능 여부 확인
		for (int j = 0; j < MAX_DIR; j++)
		{
			int isPossible = check_bfs(j, cur.r, cur.c);

			// 탐색 가능하다면
			if (isPossible)
			{
				// 탐색하자
				node next;

				next.r = cur.r + dr[j];
				next.c = cur.c + dc[j];

				// 아직 방문 안했다면
				if (!isVisited[next.r][next.c])
				{
					// 추가하기 전 방문 표시
					isVisited[next.r][next.c] = 1;

					q.push(next);
				}
			}
		}
	}

	return;
}

int check_float()
{
	// 열 우선 탐색
	for (int c = 0; c < cols; c++)
	{
		// row는 거꾸로 확인!
		for (int r = rows - 1; r >= 0; r--)
		{
			// 클러스터 처음 찾았다
			// 해당 col의 가장 아래에 있는 row
			if (isVisited[r][c])
			{
				// 땅일 경우
				if (r == rows - 1)
				{
					// 클러스터 안전
					return 1;
				}
				// 미네랄일 경우
				else if (v[r + 1][c] == 'x')
				{
					// 클러스터 안전
					return 1;
				}
				// 가장 아래칸만 확인하면 된다
				else
				{
					break;
				}
			}
		}
	}

	// 클러스터 안전하지 않음
	return 0;
}

int check_cluster(int j)
{
	int next_r = mine_r + dr[j];
	int next_c = mine_c + dc[j];

	// 상, 하 확인
	if ((next_r < 0) || (next_r >= v.size()))
	{
		// 떠 있는 클러스터 없음
		return 0;
	}
	// 좌, 우 확인
	else if ((next_c < 0) || (next_c >= v[next_r].size()))
	{
		// 떠 있는 클러스터 없음
		return 0;
	}
	// 해당 방향이 빈 공간이라면
	else if (v[next_r][next_c] == '.')
	{
		// 떠 있는 클러스터 없음
		return 0;
	}

	// BFS로 클러스터 전체 확인
	bfs(next_r, next_c);

	// 해당 클러스터가 안전한지 확인
	int result = check_float();

	// printf("result = %d, (%d, %d)\n", result, next_r, next_c);
	// print_isVisited();

	// 해당 클러스터가 안전하다면
	if (result)
	{
		// 떠 있는 클러스터 없음
		return 0;
	}

	// 떠 있는 클러스터 있음
	return 1;
}

void gravity()
{
	// v만 한 칸 내린다
	// 열 우선 탐색
	for (int c = 0; c < cols; c++)
	{
		// row는 거꾸로 확인!
		for (int r = rows - 1; r >= 0; r--)
		{
			// 해당 클러스터라면
			if (isVisited[r][c])
			{
				// 아래로 한 칸 내린다
				v[r + 1][c] = v[r][c];
				isVisited[r + 1][c] = isVisited[r][c];

				// 빈 공간 표시
				v[r][c] = '.';
				isVisited[r][c] = 0;
			}
		}
	}

	return;
}

void simulate(int i, int h)
{
	// printf("i = %d, h = %d\n", i, h);

	int isDestroyed = 0;
	int isFloating = 0;

	// 1. 막대를 던진다
	isDestroyed = throw_stick(i, h);

	// printf("isDestroyed = %d\n", isDestroyed);
	// print_v();

	// 파괴된 미네랄이 없다면
	if (!isDestroyed)
	{
		// 더 이상 시뮬레이션 필요 없음
		return;
	}

	// 2. 클러스터 확인
	// 파괴된 미네랄 위치 기준 4방향 확인
	// 상, 하, 좌, 우
	for (int j = 0; j < MAX_DIR; j++)
	{
		isFloating = check_cluster(j);

		// printf("j = %d, isFloating = %d\n", j, isFloating);

		// 이미 떠 있는 클러스터 하나 있다면
		if (isFloating)
		{
			// 더 볼 필요 없음
			break;
		}
	}

	// 떠 있는 클러스터 없다면
	if (!isFloating)
	{
		// 더 이상 시뮬레이션 필요 없음
		return;
	}

	// 3. 중력으로 내리기
	// 끝날 때까지 무한 반복
	while (1)
	{
		gravity();

		isFloating = check_float();

		// 안전하면
		if (isFloating)
		{
			// 더 이상 시뮬레이션 필요 없음
			return;
		}
	}

	return;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	int n = 0;
	int h = 0;

	scanf("%d %d", &rows, &cols);

	init_v();

	for (int r = 0; r < v.size(); r++)
	{
		getchar();

		for (int c = 0; c < v[r].size(); c++)
		{
			scanf("%c", &v[r][c]);
		}

		// getchar();
	}

	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &h);

		// 매 턴마다 시뮬레이션
		// 높이는 바꿔줘야 한다!
		simulate(i, rows - h);

		// print_v();
	}

	print_ans();

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
