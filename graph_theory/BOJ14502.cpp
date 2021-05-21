// KJO14502.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 8
#define MAX_M 8
#define MAX_V 10
#define MAX_W 3

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>
//#include <string>
#include <cstring>
#include <queue>

using namespace std;

typedef struct node {
	int r = 0;
	int c = 0;
} NODE;

int n = 0;
int m = 0;
int cnt = 0;
int ans = 0;

int matrix[MAX_W + 1][MAX_N + 2][MAX_M + 2] = { 1 };
// int matrix[MAX_N + 2][MAX_M + 2] = { 1 };
// int copy[MAX_N + 2][MAX_M + 2] = { 1 };
NODE virus[MAX_V];

void print_matrix(int depth)
{
	printf("matrix : \n");

	for (int row = 1; row <= n; row++)
	{
		for (int col = 1; col <= m; col++)
		{
			printf("%d ", matrix[depth][row][col]);
		}

		printf("\n");
	}

	return;
}

void safe_count(int depth)
{
	int result = 0;

	for (int row = 1; row <= n; row++)
	{
		for (int col = 1; col <= m; col++)
		{
			// 안전 영역일 경우
			if (matrix[depth][row][col] == 0)
			{
				result += 1;
			}
		}
	}

	// print_matrix(depth);

	if (result > ans)
	{
		ans = result;
	}

	return;
}

void bfs(int depth)
{
	int cur_row = 0;
	int cur_col = 0;

	NODE cur;

	queue<NODE> q;

	// 바이러스 위치 push
	for (int i = 0; i < cnt; i++)
	{
		cur.r = virus[i].r;
		cur.c = virus[i].c;

		q.push(cur);
	}

	while (!(q.empty()))
	{
		cur = q.front();
		q.pop();

		cur_row = cur.r;
		cur_col = cur.c;

		// 상
		if (matrix[depth][cur_row - 1][cur_col] == 0)
		{
			// 바이러스 퍼짐
			matrix[depth][cur_row - 1][cur_col] = 2;

			cur.r = cur_row - 1;
			cur.c = cur_col;

			q.push(cur);
		}

		// 하
		if (matrix[depth][cur_row + 1][cur_col] == 0)
		{
			// 바이러스 퍼짐
			matrix[depth][cur_row + 1][cur_col] = 2;

			cur.r = cur_row + 1;
			cur.c = cur_col;

			q.push(cur);
		}

		// 좌
		if (matrix[depth][cur_row][cur_col - 1] == 0)
		{
			// 바이러스 퍼짐
			matrix[depth][cur_row][cur_col - 1] = 2;

			cur.r = cur_row;
			cur.c = cur_col - 1;

			q.push(cur);
		}

		// 우
		if (matrix[depth][cur_row][cur_col + 1] == 0)
		{
			// 바이러스 퍼짐
			matrix[depth][cur_row][cur_col + 1] = 2;

			cur.r = cur_row;
			cur.c = cur_col + 1;

			q.push(cur);
		}
	}

	// 안전영역 계산
	safe_count(depth);

	return;
}

void solve(int depth, int start_row, int start_col)
{
	// 벽을 3개 모두 쌓았을 경우
	if (depth == MAX_W)
	{
		// 바이러스 전파
		bfs(depth);

		return;
	}

	for (int row = start_row; row <= n; row++)
	{
		for (int col = 1; col <= m; col++)
		{
			// 빈 칸일 경우
			if (matrix[depth][row][col] == 0)
			{
				// 상위 맵을 하위 단계에 복사
				memcpy(matrix[depth + 1], matrix[depth], sizeof(matrix[depth]));

				// 벽을 세운다
				matrix[depth + 1][row][col] = 1;

				// printf("wall = (%d, %d), depth = %d\n", row, col, depth);

				// 완전 탐색
				solve(depth + 1, row, col);

				///*
				// 탐색 후 벽 제거
				matrix[depth + 1][row][col] = 0;
				//*/
			}
		}
	}

	return;
}

int main()
{
    // std::cout << "Hello World!\n";

	scanf("%d %d", &n, &m);

	for (int row = 0; row < n + 2; row++)
	{
		for (int col = 0; col < m + 2; col++)
		{
			// 외곽일 경우
			if ((row == 0) || (col == 0) || (row == n + 1) || (col == m + 1))
			{
				matrix[0][row][col] = 1;
			}
			else
			{
				scanf("%d", &matrix[0][row][col]);

				// 바이러스일 경우
				if (matrix[0][row][col] == 2)
				{
					// 위치 기록
					virus[cnt].r = row;
					virus[cnt].c = col;

					cnt += 1;
				}
			}
		}
	}

	// print_matrix(0);

	solve(0, 1, 1);

	printf("%d", ans);

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
