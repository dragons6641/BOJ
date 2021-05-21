// KJO16235.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 10
#define MAX_M MAX_N * MAX_N
#define MAX_K 1000
#define MAX_A 100
#define MAX_Z 10
#define MAX_I 1000000
#define CHILDS 8
#define START_A 5

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>
#include <cstring>
#include <vector>

using namespace std;

typedef struct tree {
	// 살아있는지
	int isAlive = 0;
	// 나이
	int a = 0;
	// row
	int r = 0;
	// col
	int c = 0;
} TREE;

int n = 0;
int m = 0;
int k = 0;
int ans = 0;
int cnt = 0;

int matrix[MAX_N + 2][MAX_N + 2] = { 0 };
int nut_list[MAX_N + 2][MAX_N + 2] = { 0 };
vector<TREE> v[MAX_N + 2][MAX_N + 2];
// TREE info_list[MAX_I];
// TREE info_copy[MAX_I];

void init()
{
	/*
	for (int i = 0; i < MAX_I; i++)
	{
		info_list[i].isAlive = 0;
		info_list[i].a = 0;
		info_list[i].r = 0;
		info_list[i].c = 0;
	}

	for (int i = 0; i < MAX_I; i++)
	{
		info_copy[i].isAlive = 0;
		info_copy[i].a = 0;
		info_copy[i].r = 0;
		info_copy[i].c = 0;
	}
	*/

	for (int row = 0; row < n + 2; row++)
	{
		for (int col = 0; col < n + 2; col++)
		{
			if ((row == 0) || (row == n + 1) || (col == 0) || (col == n + 1))
			{
				matrix[row][col] = 0;
			}
			else
			{
				matrix[row][col] = START_A;
			}
		}
	}

	return;
}

void print_matrix()
{
	printf("matrix : \n");

	for (int row = 1; row <= n; row++)
	{
		for (int col = 1; col <= n; col++)
		{
			printf("%d ", matrix[row][col]);
		}

		printf("\n");
	}

	printf("\n");

	return;
}

void print_nut()
{
	printf("nut_list : \n");

	for (int row = 1; row <= n; row++)
	{
		for (int col = 1; col <= n; col++)
		{
			printf("%d ", nut_list[row][col]);
		}

		printf("\n");
	}

	printf("\n");

	return;
}

/*
void print_info()
{
	printf("info_list : \n");

	for (int i = 0; i < m; i++)
	{
		printf("(%d %d) %d %d\n", info_list[i].r, info_list[i].c, info_list[i].a, info_list[i].isAlive);
	}
	
	printf("\n");

	return;
}
*/

/*
void spring()
{
	int cur_row = 0;
	int cur_col = 0;
	int cur_age = 0;
	int nutrient = 0;
	int diff = 0;

	// 어린 나무부터 나이만큼 양분 먹기
	for (int i = cnt - 1; i >= 0; i--)
	{
		// 살아있다면
		if (info_list[i].isAlive == 1)
		{
			cur_row = info_list[i].r;
			cur_col = info_list[i].c;
			cur_age = info_list[i].a;
			nutrient = matrix[cur_row][cur_col];
			diff = nutrient - cur_age;

			// printf("(%d, %d), age = %d, nutrient = %d, diff = %d\n", cur_row, cur_col, cur_age, nutrient, diff);

			// 양분을 먹을 수 없다면
			if (diff < 0)
			{
				// 죽음뿐
				info_list[i].isAlive = 0;
			}
			// 양분을 먹을 수 있다면
			else
			{
				// 양분 흡수
				matrix[cur_row][cur_col] -= cur_age;
			}

			// 살아있다면
			if (info_list[i].isAlive == 1)
			{
				// 나이 증가
				info_list[i].a += 1;
			}
		}
	}

	return;
}

void summer()
{
	int cur_row = 0;
	int cur_col = 0;
	int cur_age = 0;

	// 봄에 죽은 나무가 양분이 됨
	for (int i = 0; i < cnt; i++)
	{
		// 죽었다면
		if (info_list[i].isAlive == 0)
		{
			cur_row = info_list[i].r;
			cur_col = info_list[i].c;
			cur_age = info_list[i].a;

			// printf("(%d, %d), age = %d\n", cur_row, cur_col, cur_age);

			// 양분으로
			matrix[cur_row][cur_col] += (int)(cur_age / 2);

			// 이제 이세상에 없음~
			info_list[i].isAlive = -1;
		}
	}

	return;
}

void fall()
{
	int cur_row = 0;
	int cur_col = 0;
	int cur_age = 0;
	int tmp = cnt;

	// 나이 5의 배수인 나무 번식
	for (int i = 0; i < cnt; i++)
	{
		cur_age = info_list[i].a;

		// 살아있는 나무의 나이가 5의 배수라면
		if (((cur_age % 5) == 0) && (info_list[i].isAlive == 1))
		{
			cur_row = info_list[i].r;
			cur_col = info_list[i].c;

			// 번식
			// (-1, -1)
			if ((cur_row > 1) && (cur_col > 1))
			{
				info_list[tmp].r = cur_row - 1;
				info_list[tmp].c = cur_col - 1;
				info_list[tmp].a = 1;
				info_list[tmp].isAlive = 1;

				tmp += 1;
			}

			// (-1, 0)
			if ((cur_row > 1))
			{
				info_list[tmp].r = cur_row - 1;
				info_list[tmp].c = cur_col;
				info_list[tmp].a = 1;
				info_list[tmp].isAlive = 1;

				tmp += 1;
			}

			// (-1, 1)
			if ((cur_row > 1) && (cur_col < n))
			{
				info_list[tmp].r = cur_row - 1;
				info_list[tmp].c = cur_col + 1;
				info_list[tmp].a = 1;
				info_list[tmp].isAlive = 1;

				tmp += 1;
			}

			// (0, -1)
			if ((cur_col > 1))
			{
				info_list[tmp].r = cur_row;
				info_list[tmp].c = cur_col - 1;
				info_list[tmp].a = 1;
				info_list[tmp].isAlive = 1;

				tmp += 1;
			}

			// (0, 1)
			if ((cur_col < n))
			{
				info_list[tmp].r = cur_row;
				info_list[tmp].c = cur_col + 1;
				info_list[tmp].a = 1;
				info_list[tmp].isAlive = 1;

				tmp += 1;
			}

			// (1, -1)
			if ((cur_row < n) && (cur_col > 1))
			{
				info_list[tmp].r = cur_row + 1;
				info_list[tmp].c = cur_col - 1;
				info_list[tmp].a = 1;
				info_list[tmp].isAlive = 1;

				tmp += 1;
			}

			// (1, 0)
			if ((cur_row < n))
			{
				info_list[tmp].r = cur_row + 1;
				info_list[tmp].c = cur_col;
				info_list[tmp].a = 1;
				info_list[tmp].isAlive = 1;

				tmp += 1;
			}

			// (1, 1)
			if ((cur_row < n) && (cur_col < n))
			{
				info_list[tmp].r = cur_row + 1;
				info_list[tmp].c = cur_col + 1;
				info_list[tmp].a = 1;
				info_list[tmp].isAlive = 1;

				tmp += 1;
			}
		}
	}

	// 결과 반영
	cnt = tmp;

	return;
}
*/

/*
void winter()
{
	for (int row = 1; row <= n; row++)
	{
		for (int col = 1; col <= n; col++)
		{
			// 땅에 양분 추가
			matrix[row][col] += nut_list[row][col];
		}
	}

	return;
}
*/

/*
void calc_ans()
{
	for (int i = 0; i < cnt; i++)
	{
		// 살아있다면
		if (info_list[i].isAlive == 1)
		{
			// 세준다
			ans += 1;
		}
	}

	return;
}

void renew_info()
{
	int tmp = 0;

	for (int i = 0; i < cnt; i++)
	{
		// 살아있는 경우만
		if (info_list[i].isAlive == 1)
		{
			// 복사
			info_copy[tmp].isAlive = info_list[i].isAlive;
			info_copy[tmp].a = info_list[i].a;
			info_copy[tmp].r = info_list[i].r;
			info_copy[tmp].c = info_list[i].c;

			tmp += 1;
		}
	}

	// 정보 갱신
	memcpy(info_list, info_copy, sizeof(info_list));

	cnt = tmp;

	return;
}
*/

/*
void simulate()
{
	for (int i = 0; i < k; i++)
	{
		// printf("cnt = %d\n", cnt);
		// print_matrix();
		// print_info();

		// 봄
		spring();

		// print_matrix();
		// print_info();

		// 여름
		summer();

		// print_matrix();
		// print_info();

		// 가을
		fall();

		// print_matrix();
		// print_info();

		// 겨울
		winter();

		// print_matrix();
		// print_info();

		renew_info();
	}

	calc_ans();

	return;
}
*/

void spring_vector()
{
	int cur_row = 0;
	int cur_col = 0;
	int cur_age = 0;
	int nutrient = 0;
	int diff = 0;

	TREE tmp;

	for (int row = 1; row <= n; row++)
	{
		for (int col = 1; col <= n; col++)
		{
			// printf("\n");

			for (vector<TREE>::reverse_iterator riter = v[row][col].rbegin(); riter != v[row][col].rend(); riter++)
			{
				nutrient = matrix[row][col];
				tmp = *riter;
				diff = nutrient - tmp.a;

				// printf("nutrient : %d, tmp.a : %d, diff : %d\n", nutrient, tmp.a, diff);

				// printf("(%d %d), age = %d, isAlive = %d\n", tmp.r, tmp.c, tmp.a, tmp.isAlive);

				// 양분을 먹을 수 없다면
				if (diff < 0)
				{
					// 죽음뿐
					tmp.isAlive = 0;
				}
				// 양분을 먹을 수 있다면
				else
				{
					// 양분 흡수
					matrix[row][col] -= tmp.a;

					// 나이 증가
					tmp.a += 1;
				}

				*riter = tmp;
			}
		}
	}

	return;
}

void summer_vector()
{
	int cur_row = 0;
	int cur_col = 0;
	int cur_age = 0;

	TREE tmp;

	for (int row = 1; row <= n; row++)
	{
		for (int col = 1; col <= n; col++)
		{
			for (vector<TREE>::iterator iter = v[row][col].begin(); iter != v[row][col].end();)
			{
				tmp = *iter;

				 // printf("(%d %d), age = %d, isAlive = %d\n", tmp.r, tmp.c, tmp.a, tmp.isAlive);
				
				// 죽었다면
				if (tmp.isAlive == 0)
				{
					// 양분으로
					matrix[row][col] += (int)(tmp.a / 2);

					// 이제 이세상에 없음~
					iter = v[row][col].erase(iter);
				}
				// 죽지 않으면
				else
				{
					// 증가
					iter++;
				}
			}
		}
	}

	return;
}

void fall_vector()
{
	int cur_row = 0;
	int cur_col = 0;
	int cur_age = 0;
	// int tmp = cnt;

	TREE tmp;
	TREE next;

	for (int row = 1; row <= n; row++)
	{
		for (int col = 1; col <= n; col++)
		{
			for (vector<TREE>::iterator iter = v[row][col].begin(); iter != v[row][col].end(); iter++)
			{
				tmp = *iter;

				// 살아있는 나무의 나이가 5의 배수라면
				if (((tmp.a % 5) == 0) && (tmp.isAlive == 1))
				{
					cur_row = row;
					cur_col = col;

					// 번식
					// (-1, -1)
					if ((cur_row > 1) && (cur_col > 1))
					{
						next.isAlive = 1;
						next.a = 1;
						next.r = cur_row - 1;
						next.c = cur_col - 1;

						v[cur_row - 1][cur_col - 1].push_back(next);
					}

					// (-1, 0)
					if ((cur_row > 1))
					{
						next.isAlive = 1;
						next.a = 1;
						next.r = cur_row - 1;
						next.c = cur_col;

						v[cur_row - 1][cur_col].push_back(next);
					}

					// (-1, 1)
					if ((cur_row > 1) && (cur_col < n))
					{
						next.isAlive = 1;
						next.a = 1;
						next.r = cur_row - 1;
						next.c = cur_col + 1;

						v[cur_row - 1][cur_col + 1].push_back(next);
					}

					// (0, -1)
					if ((cur_col > 1))
					{
						next.isAlive = 1;
						next.a = 1;
						next.r = cur_row;
						next.c = cur_col - 1;

						v[cur_row][cur_col - 1].push_back(next);
					}

					// (0, 1)
					if ((cur_col < n))
					{
						next.isAlive = 1;
						next.a = 1;
						next.r = cur_row;
						next.c = cur_col + 1;

						v[cur_row][cur_col + 1].push_back(next);
					}

					// (1, -1)
					if ((cur_row < n) && (cur_col > 1))
					{
						next.isAlive = 1;
						next.a = 1;
						next.r = cur_row + 1;
						next.c = cur_col - 1;

						v[cur_row + 1][cur_col - 1].push_back(next);
					}

					// (1, 0)
					if ((cur_row < n))
					{
						next.isAlive = 1;
						next.a = 1;
						next.r = cur_row + 1;
						next.c = cur_col;

						v[cur_row + 1][cur_col].push_back(next);
					}

					// (1, 1)
					if ((cur_row < n) && (cur_col < n))
					{
						next.isAlive = 1;
						next.a = 1;
						next.r = cur_row + 1;
						next.c = cur_col + 1;

						v[cur_row + 1][cur_col + 1].push_back(next);
					}
				}
			}
		}
	}

	return;
}

void calc_vector()
{
	for (int row = 1; row <= n; row++)
	{
		for (int col = 1; col <= n; col++)
		{
			ans += v[row][col].size();
		}
	}

	return;
}

///*
void simulate_vector()
{
	for (int i = 0; i < k; i++)
	{
		// printf("cnt = %d\n", cnt);
		/*
		print_matrix();
		// print_info();
		*/

		// 봄
		spring_vector();

		/*
		print_matrix();
		// print_info();
		*/

		// 여름
		summer_vector();

		/*
		print_matrix();
		// print_info();
		*/

		// 가을
		fall_vector();

		/*
		print_matrix();
		// print_info();
		*/

		// 겨울
		// winter();

		/*
		print_matrix();
		// print_info();
		*/

		// renew_info();
	}

	calc_vector();

	return;
}
//*/

int my_main()
{
    // std::cout << "Hello World!\n"; 

	int rr = 0;
	int cc = 0;
	int aa = 0;

	TREE tmp;

	scanf("%d %d %d", &n, &m, &k);

	init();

	for (int row = 0; row < n + 2; row++)
	{
		for (int col = 0; col < n + 2; col++)
		{
			if ((row == 0) || (row == n + 1) || (col == 0) || (col == n + 1))
			{
				nut_list[row][col] = 0;
			}
			else
			{
				scanf("%d", &nut_list[row][col]);
			}
		}
	}

	/*
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &info_list[i].r, &info_list[i].c, &info_list[i].a);

		info_list[i].isAlive = 1;

		cnt += 1;
	}
	*/

	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &rr, &cc, &aa);

		tmp.isAlive = 1;
		tmp.a = aa;
		tmp.r = rr;
		tmp.c = cc;

		v[rr][cc].push_back(tmp);

		// info_list[i].isAlive = 1;

		// cnt += 1;
	}

	// memcpy(nut_list, matrix, sizeof(matrix));

	/*
	print_matrix();
	print_nut();
	print_info();
	*/

	// simulate();

	simulate_vector();

	printf("%d", ans);

	return 0;
}

// 일단 제출하고 나중에 다시 풀어보자!

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <memory.h>

using namespace std;

int land[12][12];
vector<int> tree[12][12];
int summer[12][12];
int winter[12][12];

int dy[8] = { -1,-1,-1,0,0,1,1,1 };
int dx[8] = { -1,0,1,-1,1,-1,0,1 };

int main() {
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);

	// 놀랍게도 양분은 모든 칸이 5만큼 들어있었다.
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			land[i][j] = 5;
			scanf("%d", &winter[i][j]);
		}

	// r과 c는 1부터 시작한다.
	for (int i = 0; i < m; i++) {
		int y, x, age;
		scanf("%d %d %d", &y, &x, &age);
		y--, x--;
		tree[y][x].push_back(age);
	}

	while (k--) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (!tree[i][j].empty()) {
					// 하나의 칸에 여러 개의 나무가 있다면, 나이가 어린 나무부터 양분을 먹는다.
					sort(tree[i][j].begin(), tree[i][j].end());
					for (int t = 0; t < tree[i][j].size(); t++) {
						int cur = tree[i][j][t];

						// 봄에는 나무가 자신의 나이만큼 양분을 먹고, 나이가 1 증가한다. 
						// 각각의 나무는 나무가 있는 1×1 크기의 칸에 있는 양분만 먹을 수 있다.
						if (cur <= land[i][j]) {
							land[i][j] -= cur;
							tree[i][j][t]++;
						}
						// 만약, 땅에 양분이 부족해 자신의 나이만큼 양분을 먹을 수 없는 나무는 
						// 양분을 먹지 못하고 즉시 죽는다.
						// 봄에 죽은 나무가 양분으로 변하게 된다. 
						// 소수점 아래는 버린다.
						else {
							tree[i][j].erase(tree[i][j].begin() + t);
							summer[i][j] += (cur / 2);
							t--;
						}
					}
				}
			}
		}

		// 각각의 죽은 나무마다 나이를 2로 나눈 값이 나무가 있던 칸에 양분으로 추가된다. 
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				land[i][j] += summer[i][j];

		memset(summer, 0, sizeof(summer));

		vector<int> tmpTree[12][12];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				for (int t = 0; t < tree[i][j].size(); t++) {
					tmpTree[i][j].push_back(tree[i][j][t]);
				}

		// 가을에는 나무가 번식한다. 번식하는 나무는 나이가 5의 배수이어야 하며, 
		// 인접한 8개의 칸에 나이가 1인 나무가 생긴다. 
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {

				for (int t = 0; t < tree[i][j].size(); t++) {
					if (tree[i][j][t] % 5)
						continue;

					for (int q = 0; q < 8; q++) {
						int ny = dy[q] + i;
						int nx = dx[q] + j;

						if ((0 <= ny && ny < n) && (0 <= nx && nx < n))
							tmpTree[ny][nx].push_back(1);
					}
				}
			}
		}

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				tree[i][j].clear();
				for (int t = 0; t < tmpTree[i][j].size(); t++)
					tree[i][j].push_back(tmpTree[i][j][t]);
			}

		// 겨울에는 S2D2가 땅을 돌아다니면서 땅에 양분을 추가한다. 
		// 각 칸에 추가되는 양분의 양은 A[r][c]
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				land[i][j] += winter[i][j];
	}

	// K년이 지난 후 상도의 땅에 살아있는 나무의 개수
	int ans = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			ans += tree[i][j].size();

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
