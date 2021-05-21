// KJO16234.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 50
#define MAX_L 100
#define MAX_R 100

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>
#include <queue>
#include <cmath>

using namespace std;

typedef struct nation {
	int p = -1;
	int r = -1;
	int c = -1;
} NATION;

typedef struct node {
	int index = 0;
	int nations = 0;
	int populations = 0;
} NODE;

int n = 0;
int l = 0;
int r = 0;
int ans = 0;
int cnt = 0;

int population_list[MAX_N][MAX_N] = { 0 };
int union_list[MAX_N][MAX_N] = { 0 };
NODE tmp_list[(MAX_N * MAX_N) + 1] = { 0 };

vector<NATION> v;

void print_population()
{
	printf("population_list : \n");

	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			printf("%d ", population_list[row][col]);
		}

		printf("\n");
	}

	printf("\n");

	return;
}

void print_union()
{
	printf("union_list : \n");

	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			printf("%d ", union_list[row][col]);
		}

		printf("\n");
	}

	printf("\n");

	return;
}

///*
void print_tmp()
{
	printf("tmp : \n");
	
	for (int i = 1; i < cnt; i++)
	{
		printf("%d %d %d", tmp_list[i].index, tmp_list[i].nations, tmp_list[i].populations);
	}

	printf("\n");

	return;
}
//*/

int calc_diff(int a, int b)
{
	return abs(a - b);
}

void bfs(int union_num, int start_row, int start_col)
{
	int cur_row = start_row;
	int cur_col = start_col;
	int cur_pop = population_list[start_row][start_col];
	///*
	int next_row = -1;
	int next_col = -1;
	int next_pop = -1;
	//*/
	int pop_diff = 0;

	NATION cur;
	NATION next;

	// queue<NATION> q;

	cur.p = cur_pop;
	cur.r = cur_row;
	cur.c = cur_col;

	// q.push(cur);
	v.push_back(cur);

	// while (!(q.empty()))
	while (!(v.empty()))
	{
		/*
		cur = q.front();
		q.pop();
		*/

		cur = v.back();
		v.pop_back();

		cur_pop = cur.p;
		cur_row = cur.r;
		cur_col = cur.c;

		// printf("cur : %d, (%d, %d)\n", cur_pop, cur_row, cur_col);

		// 연합 기록
		union_list[cur_row][cur_col] = union_num;

		// 상
		if (cur_row > 0)
		{
			next_row = cur_row - 1;
			next_col = cur_col;
			next_pop = population_list[next_row][next_col];

			if (union_list[next_row][next_col] == 0)
			{
				// 차이 계산
				pop_diff = calc_diff(cur_pop, next_pop);

				/*
				printf("next : %d, (%d, %d)\n", next_pop, next_row, next_col);
				printf("pop_diff : %d\n", pop_diff);
				*/

				// 차이가 범위 안이면
				if ((pop_diff >= l) && (pop_diff <= r))
				{
					// 연합 형성 후 계속 탐색
					next.p = next_pop;
					next.r = next_row;
					next.c = next_col;

					// q.push(next);
					v.push_back(next);
				}
			}
		}

		// 하
		if (cur_row < n - 1)
		{
			next_row = cur_row + 1;
			next_col = cur_col;
			next_pop = population_list[next_row][next_col];

			if (union_list[next_row][next_col] == 0)
			{
				// 차이 계산
				pop_diff = calc_diff(cur_pop, next_pop);

				/*
				printf("next : %d, (%d, %d)\n", next_pop, next_row, next_col);
				printf("pop_diff : %d\n", pop_diff);
				*/

				// 차이가 범위 안이면
				if ((pop_diff >= l) && (pop_diff <= r))
				{
					// 연합 형성 후 계속 탐색
					next.p = next_pop;
					next.r = next_row;
					next.c = next_col;

					// q.push(next);
					v.push_back(next);
				}
			}
		}

		// 좌
		if (cur_col > 0)
		{
			next_row = cur_row;
			next_col = cur_col - 1;
			next_pop = population_list[next_row][next_col];

			if (union_list[next_row][next_col] == 0)
			{
				// 차이 계산
				pop_diff = calc_diff(cur_pop, next_pop);

				/*
				printf("next : %d, (%d, %d)\n", next_pop, next_row, next_col);
				printf("pop_diff : %d\n", pop_diff);
				*/

				// 차이가 범위 안이면
				if ((pop_diff >= l) && (pop_diff <= r))
				{
					// 연합 형성 후 계속 탐색
					next.p = next_pop;
					next.r = next_row;
					next.c = next_col;

					// q.push(next);
					v.push_back(next);
				}
			}
		}

		// 우
		if (cur_col < n - 1)
		{
			next_row = cur_row;
			next_col = cur_col + 1;
			next_pop = population_list[next_row][next_col];

			if (union_list[next_row][next_col] == 0)
			{
				// 차이 계산
				pop_diff = calc_diff(cur_pop, next_pop);

				/*
				printf("next : %d, (%d, %d)\n", next_pop, next_row, next_col);
				printf("pop_diff : %d\n", pop_diff);
				*/

				// 차이가 범위 안이면
				if ((pop_diff >= l) && (pop_diff <= r))
				{
					// 연합 형성 후 계속 탐색
					next.p = next_pop;
					next.r = next_row;
					next.c = next_col;

					// q.push(next);
					v.push_back(next);
				}
			}
		}
	}

	return;
}

void open()
{
	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < n; c++)
		{
			// 연합이 없으면
			if (union_list[r][c] == 0)
			{
				// 연합 수 증가
				cnt += 1;

				// 연합 확인
				bfs(cnt, r, c);
			}
		}
	}

	return;
}

void move()
{
	int union_num = 0;

	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < n; c++)
		{
			///*
			union_num = union_list[r][c];

			// 각 연합별 인구 기록
			tmp_list[union_num].index = union_num;
			tmp_list[union_num].nations += 1;
			tmp_list[union_num].populations += population_list[r][c];
			//*/
		}
	}

	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < n; c++)
		{
			///*
			union_num = union_list[r][c];

			// 각 연합별 인구 수정
			population_list[r][c] = (int)(tmp_list[union_num].populations / tmp_list[union_num].nations);
			//*/
		}
	}

	return;
}

void init_union()
{
	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			union_list[row][col] = 0;
		}
	}

	///*
	for (int i = 0; i < (MAX_N * MAX_N) + 1; i++)
	{
		tmp_list[i].index = i;
		tmp_list[i].nations = 0;
		tmp_list[i].populations = 0;
	}
	//*/

	return;
}

void simulate()
{
	while (1)
	{
		// 초기화
		cnt = 0;

		// 국경선 열기
		open();

		// print_union();

		// 열린 국경선이 없다면
		if (cnt == n * n)
		{
			// 시뮬레이션 종료
			break;
		}

		// 인구 이동하기
		move();

		// print_population();

		// 국경선 닫기
		init_union();

		ans += 1;
	}

	return;
}

int main()
{
	scanf("%d %d %d", &n, &l, &r);

	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			scanf("%d", &population_list[row][col]);
		}
	}

	/*
	print_population();
	print_union();
	*/

	simulate();

	printf("%d", ans);

    // std::cout << "Hello World!\n"; 

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
