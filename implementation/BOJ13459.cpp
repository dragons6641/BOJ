// KJO13459.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_M 10
#define MAX_N 10

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>
#include <queue>

using namespace std;

typedef struct node {
	int cnt = 0;
	int dir = 0;
	int r_row = -1;
	int r_col = -1;
	int b_row = -1;
	int b_col = -1;
} NODE;

int n = 0;
int m = 0;
int hole_row = -1;
int hole_col = -1;
int red_row = -1;
int red_col = -1;
int blue_row = -1;
int blue_col = -1;

char matrix[MAX_N][MAX_M + 1] = { '\0' };

int bfs()
{
	int cur_cnt = 0;
	int cur_dir = 0;
	int cur_r_row = -1;
	int cur_r_col = -1;
	int cur_b_row = -1;
	int cur_b_col = -1;

	int next_cnt = 0;
	int next_dir = 0;
	int next_r_row = -1;
	int next_r_col = -1;
	int next_b_row = -1;
	int next_b_col = -1;

	NODE cur;
	NODE next;

	queue<NODE> q;

	cur.cnt = 0;
	cur.dir = 0;
	cur.r_row = red_row;
	cur.r_col = red_col;
	cur.b_row = blue_row;
	cur.b_col = blue_col;

	q.push(cur);

	while (!(q.empty()))
	{
		cur = q.front();
		q.pop();

		cur_cnt = cur.cnt;
		cur_dir = cur.dir;
		cur_r_row = cur.r_row;
		cur_r_col = cur.r_col;
		cur_b_row = cur.b_row;
		cur_b_col = cur.b_col;

		// printf("cnt = %d, dir = %d, red = (%d, %d), blue = (%d, %d), hole = (%d, %d)\n", cur_cnt, cur_dir, cur_r_row, cur_r_col, cur_b_row, cur_b_col, hole_row, hole_col);

		// 10번을 넘어가면
		if (cur_cnt > 10)
		{
			/*
			// -1 출력
			return -1;
			*/

			return 0;
		}

		/*
		if (cur_cnt == 3)
		{
			return -1;
		}
		*/

		// 파란 구슬이 먼저 들어갔을 경우
		if ((cur_b_row == hole_row) && (cur_b_col == hole_col))
		{
			// 실패, 다음 것 탐색
			continue;
		}

		// 빨간 구슬이 먼저 들어갔을 경우
		if ((cur_r_row == hole_row) && (cur_r_col == hole_col))
		{
			/*
			// 횟수 출력
			return cur_cnt;
			*/

			return 1;
		}

		// 구슬 위치 생성
		matrix[cur_r_row][cur_r_col] = 'R';
		matrix[cur_b_row][cur_b_col] = 'B';

		// 4방향
		// 상
		// if (cur_dir != 12)
		if (cur_dir != 12 && cur_dir != 6)
		{
			// 같은 열이 아닐 경우
			if (cur_r_col != cur_b_col)
			{
				// 빨간 공이 움직일 위치를 찾는다
				for (int row = cur_r_row - 1; row >= 0; row--)
				{
					// 구멍일 경우
					if (matrix[row][cur_r_col] == 'O')
					{
						// 위치 설정
						next.r_row = row;
						next.r_col = cur_r_col;

						matrix[cur_r_row][cur_r_col] = '.';

						break;
					}
					// 빈 공간이 아닐 경우
					if (matrix[row][cur_r_col] != '.')
					{
						// 위치 설정
						next.r_row = row + 1;
						next.r_col = cur_r_col;

						matrix[cur_r_row][cur_r_col] = '.';
						matrix[next.r_row][next.r_col] = 'R';

						break;
					}
				}

				// 파란 공이 움직일 위치를 찾는다
				for (int row = cur_b_row - 1; row >= 0; row--)
				{
					// 구멍일 경우
					if (matrix[row][cur_b_col] == 'O')
					{
						// 위치 설정
						next.b_row = row;
						next.b_col = cur_b_col;

						matrix[cur_b_row][cur_b_col] = '.';

						break;
					}

					// 빈 공간이 아닐 경우
					if (matrix[row][cur_b_col] != '.')
					{
						// 위치 설정
						next.b_row = row + 1;
						next.b_col = cur_b_col;

						matrix[cur_b_row][cur_b_col] = '.';
						matrix[next.b_row][next.b_col] = 'B';

						break;
					}
				}
			}

			// 같은 열일 경우
			else
			{
				// 빨간 공이 더 위에 있을 경우
				if (cur_r_row < cur_b_row)
				{
					// 빨간 공이 움직일 위치를 찾는다
					for (int row = cur_r_row - 1; row >= 0; row--)
					{
						// 구멍일 경우
						if (matrix[row][cur_r_col] == 'O')
						{
							// 위치 설정
							next.r_row = row;
							next.r_col = cur_r_col;

							matrix[cur_r_row][cur_r_col] = '.';

							break;
						}
						// 빈 공간이 아닐 경우
						if (matrix[row][cur_r_col] != '.')
						{
							// 위치 설정
							next.r_row = row + 1;
							next.r_col = cur_r_col;

							matrix[cur_r_row][cur_r_col] = '.';
							matrix[next.r_row][next.r_col] = 'R';

							break;
						}
					}

					// 파란 공이 움직일 위치를 찾는다
					for (int row = cur_b_row - 1; row >= 0; row--)
					{
						// 구멍일 경우
						if (matrix[row][cur_b_col] == 'O')
						{
							// 위치 설정
							next.b_row = row;
							next.b_col = cur_b_col;

							matrix[cur_b_row][cur_b_col] = '.';

							break;
						}
						// 빈 공간이 아닐 경우
						if (matrix[row][cur_b_col] != '.')
						{
							// 위치 설정
							next.b_row = row + 1;
							next.b_col = cur_b_col;

							matrix[cur_b_row][cur_b_col] = '.';
							matrix[next.b_row][next.b_col] = 'B';

							break;
						}
					}
				}
				// 파란 공이 더 위에 있을 경우
				else
				{
					// 파란 공이 움직일 위치를 찾는다
					for (int row = cur_b_row - 1; row >= 0; row--)
					{
						// 구멍일 경우
						if (matrix[row][cur_b_col] == 'O')
						{
							// 위치 설정
							next.b_row = row;
							next.b_col = cur_b_col;

							matrix[cur_b_row][cur_b_col] = '.';

							break;
						}

						// 빈 공간이 아닐 경우
						if (matrix[row][cur_b_col] != '.')
						{
							// 위치 설정
							next.b_row = row + 1;
							next.b_col = cur_b_col;

							matrix[cur_b_row][cur_b_col] = '.';
							matrix[next.b_row][next.b_col] = 'B';

							break;
						}
					}

					// 빨간 공이 움직일 위치를 찾는다
					for (int row = cur_r_row - 1; row >= 0; row--)
					{
						// 구멍일 경우
						if (matrix[row][cur_r_col] == 'O')
						{
							// 위치 설정
							next.r_row = row;
							next.r_col = cur_r_col;

							matrix[cur_r_row][cur_r_col] = '.';

							break;
						}
						// 빈 공간이 아닐 경우
						if (matrix[row][cur_r_col] != '.')
						{
							// 위치 설정
							next.r_row = row + 1;
							next.r_col = cur_r_col;

							matrix[cur_r_row][cur_r_col] = '.';
							matrix[next.r_row][next.r_col] = 'R';

							break;
						}
					}
				}
			}

			next.cnt = (cur_cnt + 1);
			next.dir = 12;

			matrix[next.r_row][next.r_col] = '.';
			matrix[next.b_row][next.b_col] = '.';

			matrix[hole_row][hole_col] = 'O';

			q.push(next);
		}

		// 하
		// if (cur_dir != 6)
		if (cur_dir != 12 && cur_dir != 6)
		{
			// 같은 열이 아닐 경우
			if (cur_r_col != cur_b_col)
			{
				// 빨간 공이 움직일 위치를 찾는다
				for (int row = cur_r_row + 1; row < n; row++)
				{
					// 구멍일 경우
					if (matrix[row][cur_r_col] == 'O')
					{
						// 위치 설정
						next.r_row = row;
						next.r_col = cur_r_col;

						matrix[cur_r_row][cur_r_col] = '.';

						break;
					}

					// 빈 공간이 아닐 경우
					if (matrix[row][cur_r_col] != '.')
					{
						// 위치 설정
						next.r_row = row - 1;
						next.r_col = cur_r_col;

						matrix[cur_r_row][cur_r_col] = '.';
						matrix[next.r_row][next.r_col] = 'R';

						break;
					}
				}

				// 파란 공이 움직일 위치를 찾는다
				for (int row = cur_b_row + 1; row < n; row++)
				{
					// 구멍일 경우
					if (matrix[row][cur_b_col] == 'O')
					{
						// 위치 설정
						next.b_row = row;
						next.b_col = cur_b_col;

						matrix[cur_b_row][cur_b_col] = '.';

						break;
					}

					// 빈 공간이 아닐 경우
					if (matrix[row][cur_b_col] != '.')
					{
						// 위치 설정
						next.b_row = row - 1;
						next.b_col = cur_b_col;

						matrix[cur_b_row][cur_b_col] = '.';
						matrix[next.b_row][next.b_col] = 'B';

						break;
					}
				}
			}
			// 같은 열일 경우
			else
			{
				// 빨간 공이 더 위에 있을 경우
				if (cur_r_row < cur_b_row)
				{
					// 파란 공이 움직일 위치를 찾는다
					for (int row = cur_b_row + 1; row < n; row++)
					{
						// 구멍일 경우
						if (matrix[row][cur_b_col] == 'O')
						{
							// 위치 설정
							next.b_row = row;
							next.b_col = cur_b_col;

							matrix[cur_b_row][cur_b_col] = '.';

							break;
						}

						// 빈 공간이 아닐 경우
						if (matrix[row][cur_b_col] != '.')
						{
							// 위치 설정
							next.b_row = row - 1;
							next.b_col = cur_b_col;

							matrix[cur_b_row][cur_b_col] = '.';
							matrix[next.b_row][next.b_col] = 'B';

							break;
						}
					}

					// 빨간 공이 움직일 위치를 찾는다
					for (int row = cur_r_row + 1; row < n; row++)
					{
						// 구멍일 경우
						if (matrix[row][cur_r_col] == 'O')
						{
							// 위치 설정
							next.r_row = row;
							next.r_col = cur_r_col;

							matrix[cur_r_row][cur_r_col] = '.';

							break;
						}

						// 빈 공간이 아닐 경우
						if (matrix[row][cur_r_col] != '.')
						{
							// 위치 설정
							next.r_row = row - 1;
							next.r_col = cur_r_col;

							matrix[cur_r_row][cur_r_col] = '.';
							matrix[next.r_row][next.r_col] = 'R';

							break;
						}
					}
				}
				// 파란 공이 더 위에 있을 경우
				else
				{
					// 빨간 공이 움직일 위치를 찾는다
					for (int row = cur_r_row + 1; row < n; row++)
					{
						// 구멍일 경우
						if (matrix[row][cur_r_col] == 'O')
						{
							// 위치 설정
							next.r_row = row;
							next.r_col = cur_r_col;

							matrix[cur_r_row][cur_r_col] = '.';

							break;
						}

						// 빈 공간이 아닐 경우
						if (matrix[row][cur_r_col] != '.')
						{
							// 위치 설정
							next.r_row = row - 1;
							next.r_col = cur_r_col;

							matrix[cur_r_row][cur_r_col] = '.';
							matrix[next.r_row][next.r_col] = 'R';

							break;
						}
					}

					// 파란 공이 움직일 위치를 찾는다
					for (int row = cur_b_row + 1; row < n; row++)
					{
						// 구멍일 경우
						if (matrix[row][cur_b_col] == 'O')
						{
							// 위치 설정
							next.b_row = row;
							next.b_col = cur_b_col;

							matrix[cur_b_row][cur_b_col] = '.';

							break;
						}

						// 빈 공간이 아닐 경우
						if (matrix[row][cur_b_col] != '.')
						{
							// 위치 설정
							next.b_row = row - 1;
							next.b_col = cur_b_col;

							matrix[cur_b_row][cur_b_col] = '.';
							matrix[next.b_row][next.b_col] = 'B';

							break;
						}
					}
				}
			}

			next.cnt = (cur_cnt + 1);
			next.dir = 6;

			matrix[next.r_row][next.r_col] = '.';
			matrix[next.b_row][next.b_col] = '.';

			matrix[hole_row][hole_col] = 'O';

			q.push(next);
		}

		// 좌
		// if (cur_dir != 9)
		if (cur_dir != 9 && cur_dir != 3)
		{
			// 같은 행이 아닐 경우
			if (cur_r_row != cur_b_row)
			{
				// 빨간 공이 움직일 위치를 찾는다
				for (int col = cur_r_col - 1; col >= 0; col--)
				{
					// 구멍일 경우
					if (matrix[cur_r_row][col] == 'O')
					{
						// 위치 설정
						next.r_row = cur_r_row;
						next.r_col = col;

						matrix[cur_r_row][cur_r_col] = '.';

						break;
					}

					// 빈 공간이 아닐 경우
					if (matrix[cur_r_row][col] != '.')
					{
						// 위치 설정
						next.r_row = cur_r_row;
						next.r_col = col + 1;

						matrix[cur_r_row][cur_r_col] = '.';
						matrix[next.r_row][next.r_col] = 'R';

						break;
					}
				}

				// 파란 공이 움직일 위치를 찾는다
				for (int col = cur_b_col - 1; col >= 0; col--)
				{
					// 구멍일 경우
					if (matrix[cur_b_row][col] == 'O')
					{
						// 위치 설정
						next.b_row = cur_b_row;
						next.b_col = col;

						matrix[cur_b_row][cur_b_col] = '.';

						break;
					}

					// 빈 공간이 아닐 경우
					if (matrix[cur_b_row][col] != '.')
					{
						// 위치 설정
						next.b_row = cur_b_row;
						next.b_col = col + 1;

						matrix[cur_b_row][cur_b_col] = '.';
						matrix[next.b_row][next.b_col] = 'B';

						break;
					}
				}
			}
			// 같은 열일 경우
			else
			{
				// 빨간 공이 더 왼쪽에 있을 경우
				if (cur_r_col < cur_b_col)
				{
					// 빨간 공이 움직일 위치를 찾는다
					for (int col = cur_r_col - 1; col >= 0; col--)
					{
						// 구멍일 경우
						if (matrix[cur_r_row][col] == 'O')
						{
							// 위치 설정
							next.r_row = cur_r_row;
							next.r_col = col;

							matrix[cur_r_row][cur_r_col] = '.';

							break;
						}

						// 빈 공간이 아닐 경우
						if (matrix[cur_r_row][col] != '.')
						{
							// 위치 설정
							next.r_row = cur_r_row;
							next.r_col = col + 1;

							matrix[cur_r_row][cur_r_col] = '.';
							matrix[next.r_row][next.r_col] = 'R';

							break;
						}
					}

					// 파란 공이 움직일 위치를 찾는다
					for (int col = cur_b_col - 1; col >= 0; col--)
					{
						// 구멍일 경우
						if (matrix[cur_b_row][col] == 'O')
						{
							// 위치 설정
							next.b_row = cur_b_row;
							next.b_col = col;

							matrix[cur_b_row][cur_b_col] = '.';

							break;
						}

						// 빈 공간이 아닐 경우
						if (matrix[cur_b_row][col] != '.')
						{
							// 위치 설정
							next.b_row = cur_b_row;
							next.b_col = col + 1;

							matrix[cur_b_row][cur_b_col] = '.';
							matrix[next.b_row][next.b_col] = 'B';

							break;
						}
					}
				}
				// 파란 공이 더 왼쪽에 있을 경우
				else
				{
					// 파란 공이 움직일 위치를 찾는다
					for (int col = cur_b_col - 1; col >= 0; col--)
					{
						// 구멍일 경우
						if (matrix[cur_b_row][col] == 'O')
						{
							// 위치 설정
							next.b_row = cur_b_row;
							next.b_col = col;

							matrix[cur_b_row][cur_b_col] = '.';

							break;
						}

						// 빈 공간이 아닐 경우
						if (matrix[cur_b_row][col] != '.')
						{
							// 위치 설정
							next.b_row = cur_b_row;
							next.b_col = col + 1;

							matrix[cur_b_row][cur_b_col] = '.';
							matrix[next.b_row][next.b_col] = 'B';

							break;
						}
					}

					// 빨간 공이 움직일 위치를 찾는다
					for (int col = cur_r_col - 1; col >= 0; col--)
					{
						// 구멍일 경우
						if (matrix[cur_r_row][col] == 'O')
						{
							// 위치 설정
							next.r_row = cur_r_row;
							next.r_col = col;

							matrix[cur_r_row][cur_r_col] = '.';

							break;
						}


						// 빈 공간이 아닐 경우
						if (matrix[cur_r_row][col] != '.')
						{
							// 위치 설정
							next.r_row = cur_r_row;
							next.r_col = col + 1;

							matrix[next.b_row][next.b_col] = 'B';

							break;
						}
					}
				}
			}

			next.cnt = (cur_cnt + 1);
			next.dir = 9;

			matrix[next.r_row][next.r_col] = '.';
			matrix[next.b_row][next.b_col] = '.';

			matrix[hole_row][hole_col] = 'O';

			q.push(next);
		}

		// 우
		// if (cur_dir != 3)
		if (cur_dir != 9 && cur_dir != 3)
		{
			// 같은 행이 아닐 경우
			if (cur_r_row != cur_b_row)
			{
				// 빨간 공이 움직일 위치를 찾는다
				for (int col = cur_r_col + 1; col < m; col++)
				{
					// 구멍일 경우
					if (matrix[cur_r_row][col] == 'O')
					{
						// 위치 설정
						next.r_row = cur_r_row;
						next.r_col = col;

						matrix[cur_r_row][cur_r_col] = '.';

						break;
					}

					// 빈 공간이 아닐 경우
					if (matrix[cur_r_row][col] != '.')
					{
						// 위치 설정
						next.r_row = cur_r_row;
						next.r_col = col - 1;

						matrix[cur_r_row][cur_r_col] = '.';
						matrix[next.r_row][next.r_col] = 'R';

						break;
					}
				}

				// 파란 공이 움직일 위치를 찾는다
				for (int col = cur_b_col + 1; col < m; col++)
				{
					// 구멍일 경우
					if (matrix[cur_b_row][col] == 'O')
					{
						// 위치 설정
						next.b_row = cur_b_row;
						next.b_col = col;

						matrix[cur_b_row][cur_b_col] = '.';

						break;
					}

					// 빈 공간이 아닐 경우
					if (matrix[cur_b_row][col] != '.')
					{
						// 위치 설정
						next.b_row = cur_b_row;
						next.b_col = col - 1;

						matrix[cur_b_row][cur_b_col] = '.';
						matrix[next.b_row][next.b_col] = 'B';

						break;
					}
				}
			}
			// 같은 열일 경우
			else
			{
				// 빨간 공이 더 왼쪽에 있을 경우
				if (cur_r_col < cur_b_col)
				{
					// 파란 공이 움직일 위치를 찾는다
					for (int col = cur_b_col + 1; col < m; col++)
					{
						// 구멍일 경우
						if (matrix[cur_b_row][col] == 'O')
						{
							// 위치 설정
							next.b_row = cur_b_row;
							next.b_col = col;

							matrix[cur_b_row][cur_b_col] = '.';

							break;
						}

						// 빈 공간이 아닐 경우
						if (matrix[cur_b_row][col] != '.')
						{
							// 위치 설정
							next.b_row = cur_b_row;
							next.b_col = col - 1;

							matrix[cur_b_row][cur_b_col] = '.';
							matrix[next.b_row][next.b_col] = 'B';

							break;
						}
					}

					// 빨간 공이 움직일 위치를 찾는다
					for (int col = cur_r_col + 1; col < m; col++)
					{
						// 구멍일 경우
						if (matrix[cur_r_row][col] == 'O')
						{
							// 위치 설정
							next.r_row = cur_r_row;
							next.r_col = col;

							matrix[cur_r_row][cur_r_col] = '.';

							break;
						}

						// 빈 공간이 아닐 경우
						if (matrix[cur_r_row][col] != '.')
						{
							// 위치 설정
							next.r_row = cur_r_row;
							next.r_col = col - 1;

							matrix[cur_r_row][cur_r_col] = '.';
							matrix[next.r_row][next.r_col] = 'R';

							break;
						}
					}
				}
				// 파란 공이 더 왼쪽에 있을 경우
				else
				{
					// 빨간 공이 움직일 위치를 찾는다
					for (int col = cur_r_col + 1; col < m; col++)
					{
						// 구멍일 경우
						if (matrix[cur_r_row][col] == 'O')
						{
							// 위치 설정
							next.r_row = cur_r_row;
							next.r_col = col;

							matrix[cur_r_row][cur_r_col] = '.';

							break;
						}

						// 빈 공간이 아닐 경우
						if (matrix[cur_r_row][col] != '.')
						{
							// 위치 설정
							next.r_row = cur_r_row;
							next.r_col = col - 1;

							matrix[cur_r_row][cur_r_col] = '.';
							matrix[next.r_row][next.r_col] = 'R';

							break;
						}
					}

					// 파란 공이 움직일 위치를 찾는다
					for (int col = cur_b_col + 1; col < m; col++)
					{
						// 구멍일 경우
						if (matrix[cur_b_row][col] == 'O')
						{
							// 위치 설정
							next.b_row = cur_b_row;
							next.b_col = col;

							matrix[cur_b_row][cur_b_col] = '.';

							break;
						}

						// 빈 공간이 아닐 경우
						if (matrix[cur_b_row][col] != '.')
						{
							// 위치 설정
							next.b_row = cur_b_row;
							next.b_col = col - 1;

							matrix[cur_b_row][cur_b_col] = '.';
							matrix[next.b_row][next.b_col] = 'B';

							break;
						}
					}
				}
			}

			next.cnt = (cur_cnt + 1);
			next.dir = 3;

			matrix[next.r_row][next.r_col] = '.';
			matrix[next.b_row][next.b_col] = '.';

			matrix[hole_row][hole_col] = 'O';

			q.push(next);
		}

		// 구슬 위치 제거
		/*
		if (matrix[cur_r_row][cur_r_col] != 'O')
		{
			matrix[cur_r_row][cur_r_col] = '.';
		}

		if (matrix[cur_b_row][cur_b_col] != 'O')
		{
			matrix[cur_b_row][cur_b_col] = '.';
		}
		*/

		matrix[hole_row][hole_col] = 'O';
	}

	// return -1;

	return 0;
}

int main()
{
	// std::cout << "Hello World!\n"; 

	int ans = 0;

	scanf("%d %d", &n, &m);

	/*
	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < m; col++)
		{
			scanf("%c", &matrix[row][col]);
		}
	}
	*/

	for (int row = 0; row < n; row++)
	{
		scanf("%s", &matrix[row]);

		for (int col = 0; col < m; col++)
		{
			// 구멍일 경우
			if (matrix[row][col] == 'O')
			{
				hole_row = row;
				hole_col = col;
			}
			// 빨간 공일 경우
			else if (matrix[row][col] == 'R')
			{
				red_row = row;
				red_col = col;

				matrix[row][col] = '.';
			}
			// 파란 공일 경우
			else if (matrix[row][col] == 'B')
			{
				blue_row = row;
				blue_col = col;

				matrix[row][col] = '.';
			}
		}
	}

	/*
	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < m; col++)
		{
			printf("%c", matrix[row][col]);
		}

		printf("\n");
	}

	printf("hole = (%d, %d)\n", hole_row, hole_col);
	printf("red = (%d, %d)\n", red_row, red_col);
	printf("blue = (%d, %d)\n", blue_row, blue_col);

	*/

	ans = bfs();

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
