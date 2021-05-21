// KJO1389.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 100
#define MAX_M 5000
#define MAX_KB (MAX_N * MAX_N)

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
	// 케빈 베이컨의 수
	int num = 0;
	// 현재 사람
	int idx = 0;
}
node;

// 인접 행렬
// 인덱스는 1부터 시작!
vector < vector < int > > v;

// 케빈 베이컨의 수
// 인덱스는 1부터 시작!
vector < int > kb;

// 유저의 수
int n = 0;
// 친구 관계의 수
int m = 0;

void init(int n)
{
	v.resize(n + 1);
	kb.resize(n + 1);

	for (int r = 0; r < v.size(); r++)
	{
		v[r].resize(n + 1);
	}

	return;
}

void print_v()
{
	printf("v : \n");

	for (int r = 1; r < v.size(); r++)
	{
		for (int c = 1; c < v[r].size(); c++)
		{
			printf("%d ", v[r][c]);
		}

		printf("\n");
	}

	return;
}

void print_kb()
{
	printf("kb : ");

	for (int i = 1; i < kb.size(); i++)
	{
		printf("%d ", kb[i]);
	}

	printf("\n");

	return;
}

int bfs(int start, int end)
{
	// 최단 연결 찾을 큐
	queue < node > q;

	// 방문 표시 벡터
	// n + 1개만큼 0으로 초기화
	vector < int > isVisited(n + 1, 0);

	// 시작점 큐에 넣기
	node cur;
	cur.num = 0;
	cur.idx = start;

	q.push(cur);

	while (!q.empty())
	{
		// 현재 노드 불러오기
		cur = q.front();
		q.pop();

		int num = cur.num;
		int idx = cur.idx;

		// printf("num = %d, idx = %d\n", num, idx);

		// 방문 표시
		isVisited[idx] = 1;

		// 원하는 답을 찾았다면 끝
		if (idx == end)
		{
			return num;
		}

		// 모든 사람에 대해
		for (int b = 1; b < v[idx].size(); b++)
		{
			// printf("%d, %d\n", v[idx][b], isVisited[b]);

			// 이 사람과 친구라면
			// 아직 확인하지 않았다면
			if ((v[idx][b]) && (!isVisited[b]))
			{
				// printf("a = %d, b = %d\n", idx, b);

				// 큐에 넣기
				node next;
				next.num = num + 1;
				next.idx = b;

				q.push(next);
			}
		}
	}

	// 불가능
	return 0;
}

int solve()
{
	int value = MAX_KB;
	int index = 0;
	int result = 0;

	for (int a = 1; a < v.size(); a++)
	{
		for (int b = a + 1; b < v[a].size(); b++)
		{
			// 이미 친구 관계라면
			if (v[a][b])
			{
				// 1단계만에 가능
				kb[a] += 1;
				kb[b] += 1;
			}
			// 직속 친구 아니라면
			else
			{
				// 탐색하자
				result = bfs(a, b);

				// printf("result = %d, (%d, %d)\n", result, a, b);

				// 해당 단계만에 가능
				kb[a] += result;
				kb[b] += result;
			}
		}
	}

	// 최종 결과 확인
	for (int i = 1; i < kb.size(); i++)
	{
		// 새로운 최소인 사람
		if (kb[i] < value)
		{
			value = kb[i];
			index = i;
		}
	}

	return index;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	int ans = 0;

	scanf("%d %d", &n, &m);

	init(n);

	for (int i = 0; i < m; i++)
	{
		int a = 0;
		int b = 0;

		scanf("%d %d", &a, &b);

		// 양쪽 모두에 표시
		v[a][b] = 1;
		v[b][a] = 1;
	}

	// print_v();

	ans = solve();

	// print_kb();

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
