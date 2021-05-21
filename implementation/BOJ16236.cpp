// KJO16236.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 20
#define START_SIZE 2
#define MIN_SIZE 1
#define MAX_SIZE 6
#define MAX_M MAX_N * MAX_N
#define INF 1000000000

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>
#include <queue>
// #include <cmath>

using namespace std;

typedef struct fish {
	int s = -1;
	int r = -1;
	int c = -1;
	int isAlive = 1;
} FISH;

int n = 0;
int ans = 0;
int shark_row = 0;
int shark_col = 0;
int shark_size = START_SIZE;
int shark_point = 0;
int fish_cnt = 0;

int matrix[MAX_N][MAX_N] = { 0 };
int isVisited[MAX_N][MAX_N] = { 0 };
FISH fish_list[MAX_M];

void init_visit()
{
	for (int row = 0; row < MAX_N; row++)
	{
		for (int col = 0; col < MAX_N; col++)
		{
			isVisited[row][col] = 0;
		}
	}

	return;
}

void print_matrix()
{
	printf("print_matrix : \n");

	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			printf("%d ", matrix[row][col]);
		}

		printf("\n");
	}

	printf("\n");

	return;
}

void print_shark()
{
	printf("print_shark : \n");

	printf("pos : (%d, %d), size : %d, point : %d\n", shark_row, shark_col, shark_size, shark_point);

	printf("\n");

	return;
}

void print_fish()
{
	printf("print_fish : \n");

	for (int i = 0; i < fish_cnt; i++)
	{
		printf("pos : (%d, %d), size : %d, isAlive : %d\n", fish_list[i].r, fish_list[i].c, fish_list[i].s, fish_list[i].isAlive);
	}

	printf("\n");

	return;
}

FISH bfs()
{
	int cur_size = -1;
	int cur_row = -1;
	int cur_col = -1;
	int cur_isAlive = -1;
	int next_size = -1;
	int next_row = -1;
	int next_col = -1;
	int ans_size = -1;
	int ans_row = -1;
	int ans_col = -1;
	int ans_isAlive = -1;

	FISH cur;
	FISH next;

	queue<FISH> q;
	
	cur.r = shark_row;
	cur.c = shark_col;
	cur.s = matrix[shark_row][shark_col];
	// 지나갈 수 있다의 표시로 대체 사용
	cur.isAlive = 0;

	q.push(cur);

	while ((!q.empty()))
	{
		next_size = -1;
		next_row = -1;
		next_col = -1;

		cur = q.front();
		q.pop();

		cur_size = cur.s;
		cur_row = cur.r;
		cur_col = cur.c;
		cur_isAlive = cur.isAlive;

		/*
		printf("pos : (%d, %d), size : %d\n", cur_row, cur_col, cur_size);
		printf("ans : (%d, %d), size : %d, isAlive = %d\n", ans_row, ans_col, ans_size, ans_isAlive);
		*/

		// 빈 칸이 아닌 경우
		if ((cur_size >= MIN_SIZE) && (cur_size <= MAX_SIZE))
		{
			// 먹을 수 있다면
			if (cur_size < shark_size)
			{
				// cur.isAlive = 1;

				// 답이 아직 없을 경우
				if (ans_isAlive == -1)
				{
					// 갱신
					ans_size = cur_size;
					ans_row = cur_row;
					ans_col = cur_col;
					ans_isAlive = cur_isAlive;
				}
				// 답이 있다면
				else
				{
					// printf("cur = %d, ans = %d\n", cur_isAlive, ans_isAlive);

					// 지금부터 비교 들어갑니다~
					// 같을 경우
					if (cur_isAlive == ans_isAlive)
					{
						// 더 위쪽이라면
						if (cur_row < ans_row)
						{
							// 갱신
							ans_size = cur_size;
							ans_row = cur_row;
							ans_col = cur_col;
							ans_isAlive = cur_isAlive;
						}
						// 같을 경우
						else if (cur_row == ans_row)
						{
							// 더 왼쪽이라면
							if (cur_col < ans_col)
							{
								// 갱신
								ans_size = cur_size;
								ans_row = cur_row;
								ans_col = cur_col;
								ans_isAlive = cur_isAlive;
							}
						}
					}
					// 더 가까울 경우
					else if (cur_isAlive < ans_isAlive)
					{
						// 갱신
						ans_size = cur_size;
						ans_row = cur_row;
						ans_col = cur_col;
						ans_isAlive = cur_isAlive;
					}
					// 더 멀 경우
					else
					{
						// 더 이상 좋은 답이 나올 수가 없다, 종료
						cur.s = ans_size;
						cur.r = ans_row;
						cur.c = ans_col;
						cur.isAlive = ans_isAlive;

						// printf("final : (%d, %d), size : %d, isAlive = %d\n", cur.r, cur.c, cur.s, cur.isAlive);

						return cur;
					}
				}
			}
		}

		// 4방향 탐색
		// 상
		if (cur_row > 0)
		{
			next_row = cur_row - 1;
			next_col = cur_col;
			next_size = matrix[next_row][next_col];

			// printf("next_size : %d\n", next_size);

			// 방문하지 않았다면
			if (isVisited[next_row][next_col] == 0)
			{
				// 방문 표시
				isVisited[next_row][next_col] = 1;

				// 빈 칸일 경우
				if (next_size == 0)
				{
					// 지나갈 수 있다
					next.s = next_size;
					next.r = next_row;
					next.c = next_col;
					next.isAlive = cur.isAlive + 1;

					q.push(next);
				}
				// 물고기일 경우
				else if ((next_size >= MIN_SIZE) && (next_size <= MAX_SIZE))
				{
					// 아기 상어보다 작거나 같다면
					if (next_size <= shark_size)
					{
						// 지나갈 수 있다
						next.s = next_size;
						next.r = next_row;
						next.c = next_col;
						next.isAlive = cur.isAlive + 1;

						q.push(next);
					}
				}
			}
		}
		// 좌
		if (cur_col > 0)
		{
			next_row = cur_row;
			next_col = cur_col - 1;
			next_size = matrix[next_row][next_col];

			// printf("next_size : %d\n", next_size);

			// 방문하지 않았다면
			if (isVisited[next_row][next_col] == 0)
			{
				// 방문 표시
				isVisited[next_row][next_col] = 1;

				// 빈 칸일 경우
				if (next_size == 0)
				{
					// 지나갈 수 있다
					next.s = next_size;
					next.r = next_row;
					next.c = next_col;
					next.isAlive = cur.isAlive + 1;

					q.push(next);
				}
				// 물고기일 경우
				else if ((next_size >= MIN_SIZE) && (next_size <= MAX_SIZE))
				{
					// 아기 상어보다 작거나 같다면
					if (next_size <= shark_size)
					{
						// 지나갈 수 있다
						next.s = next_size;
						next.r = next_row;
						next.c = next_col;
						next.isAlive = cur.isAlive + 1;

						q.push(next);
					}
				}
			}
		}
		// 우
		if (cur_col < n - 1)
		{
			next_row = cur_row;
			next_col = cur_col + 1;
			next_size = matrix[next_row][next_col];

			// printf("next_size : %d\n", next_size);

			// 방문하지 않았다면
			if (isVisited[next_row][next_col] == 0)
			{
				// 방문 표시
				isVisited[next_row][next_col] = 1;

				// 빈 칸일 경우
				if (next_size == 0)
				{
					// 지나갈 수 있다
					next.s = next_size;
					next.r = next_row;
					next.c = next_col;
					next.isAlive = cur.isAlive + 1;

					q.push(next);
				}
				// 물고기일 경우
				else if ((next_size >= MIN_SIZE) && (next_size <= MAX_SIZE))
				{
					// 아기 상어보다 작거나 같다면
					if (next_size <= shark_size)
					{
						// 지나갈 수 있다
						next.s = next_size;
						next.r = next_row;
						next.c = next_col;
						next.isAlive = cur.isAlive + 1;

						q.push(next);
					}
				}
			}
		}
		// 하
		if (cur_row < n - 1)
		{
			next_row = cur_row + 1;
			next_col = cur_col;
			next_size = matrix[next_row][next_col];

			// printf("next_size : %d\n", next_size);

			// 방문하지 않았다면
			if (isVisited[next_row][next_col] == 0)
			{
				// 방문 표시
				isVisited[next_row][next_col] = 1;

				// 빈 칸일 경우
				if (next_size == 0)
				{
					// 지나갈 수 있다
					next.s = next_size;
					next.r = next_row;
					next.c = next_col;
					next.isAlive = cur.isAlive + 1;

					q.push(next);
				}
				// 물고기일 경우
				else if ((next_size >= MIN_SIZE) && (next_size <= MAX_SIZE))
				{
					// 아기 상어보다 작거나 같다면
					if (next_size <= shark_size)
					{
						// 지나갈 수 있다
						next.s = next_size;
						next.r = next_row;
						next.c = next_col;
						next.isAlive = cur.isAlive + 1;

						q.push(next);
					}
				}
			}
		}
	}

	// 먹을 물고기가 없다면
	if (ans_isAlive == -1)
	{
		cur.isAlive = 0;

		return cur;
	}
	else
	{
		// 더 이상 좋은 답이 나올 수가 없다, 종료
		cur.s = ans_size;
		cur.r = ans_row;
		cur.c = ans_col;
		cur.isAlive = ans_isAlive;

		// printf("final : (%d, %d), size : %d, isAlive = %d\n", cur.r, cur.c, cur.s, cur.isAlive);

		return cur;
	}
}

/*
int calc_dist(int a1, int b1, int a2, int b2)
{
	return (abs(a1 - a2) + abs(b1 - b2));
}
*/

void eat(FISH pos)
{
	/*
	int dist = 0;

	dist = calc_dist(shark_row, shark_col, pos.r, pos.c);

	ans += dist;
	*/

	// 이동 거리만큼 시간 추가
	ans += pos.isAlive;

	// 이전은 빈 공간...
	matrix[shark_row][shark_col] = 0;

	// 상어 이동
	shark_row = pos.r;
	shark_col = pos.c;
	shark_point += 1;

	// 먹으면 상어만 있다....
	matrix[shark_row][shark_col] = 9;

	// 크기만큼의 물고기를 먹으면
	if (shark_point == shark_size)
	{
		// 크기 커진다!
		shark_size += 1;
		shark_point = 0;
	}

	return;
}

void simulate()
{
	FISH result;

	while (1)
	{
		init_visit();

		/*
		printf("shark : (%d, %d), size : %d, point : %d\n", shark_row, shark_col, shark_size, shark_point);
		print_matrix();
		*/

		result = bfs();

		// 먹을 물고기가 있다면
		if (result.isAlive)
		{
			eat(result);
		}
		// 먹을 물고기가 없다면
		else
		{
			break;
		}

		/*
		printf("pos : (%d, %d), fish_size : %d, shark_size : %d, shark_point = %d, isAlive : %d, ans = %d\n\n\n\n\n",
			result.r, result.c, result.s, shark_size, shark_point, result.isAlive, ans);
		*/
	}

	return;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	int tmp = 0;

	scanf("%d", &n);

	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			scanf("%d", &tmp);

			matrix[row][col] = tmp;

			// 아기 상어
			if (tmp == 9)
			{
				shark_row = row;
				shark_col = col;
			}
			// 물고기
			else if ((tmp >= MIN_SIZE) && (tmp <= MAX_SIZE))
			{
				fish_list[fish_cnt].s = tmp;
				fish_list[fish_cnt].r = row;
				fish_list[fish_cnt].c = col;
				fish_list[fish_cnt].isAlive = 1;

				fish_cnt += 1;
			}
		}
	}

	/*
	print_matrix();
	print_shark();
	print_fish();
	*/

	simulate();

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
