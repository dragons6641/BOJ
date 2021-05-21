// KJO12100.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 20
#define MAX_D 5

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>
#include <cstring>

int n = 0;
int ans = 0;

/*
int prev_board[MAX_N][MAX_N] = { 0 };
int cur_board[MAX_N][MAX_N] = { 0 };
int next_board[MAX_N][MAX_N] = { 0 };
*/

int board[MAX_D + 1][MAX_N][MAX_N] = { 0 };

///*
int tmp_12[MAX_N] = { 0 };
int tmp_6[MAX_N] = { 0 };
int tmp_9[MAX_N] = { 0 };
int tmp_3[MAX_N] = { 0 };
//*/
/*
int tmp_row[MAX_N] = { 0 };
int tmp_col[MAX_N] = { 0 };
*/

void init()
{
	for (int r = 0; r < MAX_N; r++)
	{
		tmp_12[r] = 0;
		tmp_6[r] = 0;
		// tmp_row[r] = 0;
	}

	for (int c = 0; c < MAX_N; c++)
	{
		tmp_9[c] = 0;
		tmp_3[c] = 0;
		// tmp_col[c] = 0;
	}

	return;
}

void init_12()
{
	for (int r = 0; r < MAX_N; r++)
	{
		tmp_12[r] = 0;
	}

	return;
}

void init_6()
{
	for (int r = 0; r < MAX_N; r++)
	{
		tmp_6[r] = 0;
	}

	return;
}

void init_9()
{
	for (int c = 0; c < MAX_N; c++)
	{
		tmp_9[c] = 0;
	}

	return;
}

void init_3()
{
	for (int c = 0; c < MAX_N; c++)
	{
		tmp_3[c] = 0;
	}

	return;
}

int calc_max(int d)
{
	int result = 0;

	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < n; c++)
		{
			if (board[d][r][c] > result)
			{
				result = board[d][r][c];
			}
		}
	}

	return result;
}

void print_prev_board(int d)
{
	printf("prev_board\n");

	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < n; c++)
		{
			printf("%d ", board[d - 1][r][c]);
		}

		printf("\n");
	}

	return;
}

void print_cur_board(int d)
{
	printf("cur_board\n");

	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < n; c++)
		{
			printf("%d ", board[d][r][c]);
		}

		printf("\n");
	}

	return;
}

void print_next_board(int d)
{
	printf("next_board\n");

	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < n; c++)
		{
			printf("%d ", board[d + 1][r][c]);
		}

		printf("\n");
	}

	return;
}

void print_tmp_12(int cnt)
{
	for (int r = 0; r < cnt; r++)
	{
		printf("%d ", tmp_12[r]);
	}

	printf("\n");

	return;
}

void print_tmp_6(int cnt)
{
	for (int r = 0; r < cnt; r++)
	{
		printf("%d ", tmp_6[r]);
	}

	printf("\n");

	return;
}

void print_tmp_9(int cnt)
{
	for (int c = 0; c < cnt; c++)
	{
		printf("%d ", tmp_9[c]);
	}

	printf("\n");

	return;
}

void print_tmp_3(int cnt)
{
	for (int c = 0; c < cnt; c++)
	{
		printf("%d ", tmp_3[c]);
	}

	printf("\n");

	return;
}

void backtrack(int depth, int dir)
{
	int result = 0;
	int index = 0;
	int row_cnt = 0;
	int col_cnt = 0;
	int cur_block = 0;
	int next_block = 0;

	// init();

	/*
	printf("depth = %d, dir = %d\n", depth, dir);
	print_prev_board();
	print_cur_board();
	print_next_board();
	printf("\n");
	*/

	/*
	// 현재 상태를 복사
	memcpy(next_board, cur_board, sizeof(cur_board));
	*/

	// 5번 모두 움직였을 경우
	if (depth == MAX_D)
	// if (depth == 3)
	{
		result = calc_max(depth);

		if (result > ans)
		{
			ans = result;
		}

		return;
	}

	// 4방향
	// 상
	for (int c = 0; c < n; c++)
	{
		index = 0;
		row_cnt = 0;

		init_12();

		for (int r = 0; r < n; r++)
		{
			// 블록만 복사
			if (board[depth][r][c] > 0)
			{
				///*
				tmp_12[index] = board[depth][r][c];
				//*/

				index += 1;
			}
		}

		/*
		printf("index = %d\n", index);
		print_tmp_12(index);
		//printf("\n");
		*/

		for (int r = 0; r < index; r++)
		{
			// 다음 칸이 남아있다면
			if (r < index - 1)
			{
				cur_block = tmp_12[r];
				next_block = tmp_12[r + 1];

				// printf("cur = %d, next = %d\n", cur_block, next_block);

				// 블록을 합칠 수 있다면
				if ((cur_block == next_block) && (cur_block > 0))
				{
					board[depth + 1][row_cnt][c] = cur_block + next_block;

					r += 1;
				}
				// 블록을 합칠 수 없다면
				else
				{
					// 그대로 둔다
					board[depth + 1][row_cnt][c] = cur_block;
				}

				row_cnt += 1;
			}
			// 다음 칸이 남아있지 않다면
			else
			{
				cur_block = tmp_12[r];

				board[depth + 1][row_cnt][c] = cur_block;

				row_cnt += 1;
			}
		}

		// printf("row_cnt = %d\n", row_cnt);

		// 뒤를 0으로 처리
		for (int r = row_cnt; r < n; r++)
		{
			board[depth + 1][r][c] = 0;
		}
	}

	// print_next_board();

	// 상태 변경 후 backtrack
	/*
	memcpy(prev_board, cur_board, sizeof(cur_board));
	memcpy(cur_board, next_board, sizeof(cur_board));
	*/
	backtrack(depth + 1, 12);

	/*
	// 초기화
	memcpy(next_board, cur_board, sizeof(cur_board));
	memcpy(cur_board, prev_board, sizeof(cur_board));
	*/

	// 하
	for (int c = 0; c < n; c++)
	{
		index = 0;
		row_cnt = n - 1;

		init_6();

		for (int r = 0; r < n; r++)
		{
			// 블록만 복사
			if (board[depth][r][c] > 0)
			{
				///*
				tmp_6[index] = board[depth][r][c];
				//*/

				index += 1;
			}
		}

		/*
		printf("index = %d\n", index);
		print_tmp_6(index);
		//printf("\n");
		*/

		for (int r = index - 1; r >= 0; r--)
		{
			// 다음 칸이 남아있다면
			if (r > 0)
			{
				cur_block = tmp_6[r];
				next_block = tmp_6[r - 1];

				// printf("cur = %d, next = %d\n", cur_block, next_block);

				// 블록을 합칠 수 있다면
				if ((cur_block == next_block) && (cur_block > 0))
				{
					board[depth + 1][row_cnt][c] = cur_block + next_block;

					r -= 1;
				}
				// 블록을 합칠 수 없다면
				else
				{
					// 그대로 둔다
					board[depth + 1][row_cnt][c] = cur_block;
				}

				row_cnt -= 1;
			}
			// 다음 칸이 남아있지 않다면
			else
			{
				cur_block = tmp_6[r];

				board[depth + 1][row_cnt][c] = cur_block;

				row_cnt -= 1;
			}
		}

		// printf("row_cnt = %d\n", row_cnt);

		// 뒤를 0으로 처리
		for (int r = row_cnt; r >= 0; r--)
		{
			board[depth + 1][r][c] = 0;
		}
	}

	// print_next_board();

	// 상태 변경 후 backtrack
	/*
	memcpy(prev_board, cur_board, sizeof(cur_board));
	memcpy(cur_board, next_board, sizeof(cur_board));
	*/
	backtrack(depth + 1, 6);

	/*
	// 초기화
	memcpy(next_board, cur_board, sizeof(cur_board));
	memcpy(cur_board, prev_board, sizeof(cur_board));
	*/

	// 좌
	for (int r = 0; r < n; r++)
	{
		index = 0;
		col_cnt = 0;

		init_9();

		for (int c = 0; c < n; c++)
		{
			// 블록만 복사
			if (board[depth][r][c] > 0)
			{
				///*
				tmp_9[index] = board[depth][r][c];
				//*/

				index += 1;
			}
		}

		/*
		printf("index = %d\n", index);
		print_tmp_9(index);
		//printf("\n");
		*/

		for (int c = 0; c < index; c++)
		{
			// 다음 칸이 남아있다면
			if (c < index - 1)
			{
				cur_block = tmp_9[c];
				next_block = tmp_9[c + 1];

				// printf("cur = %d, next = %d\n", cur_block, next_block);

				// 블록을 합칠 수 있다면
				if ((cur_block == next_block) && (cur_block > 0))
				{
					board[depth + 1][r][col_cnt] = cur_block + next_block;

					c += 1;
				}
				// 블록을 합칠 수 없다면
				else
				{
					// 그대로 둔다
					board[depth + 1][r][col_cnt] = cur_block;
				}

				col_cnt += 1;
			}
			// 다음 칸이 남아있지 않다면
			else
			{
				cur_block = tmp_9[c];

				board[depth + 1][r][col_cnt] = cur_block;

				col_cnt += 1;
			}
		}

		// printf("col_cnt = %d\n", col_cnt);

		// 뒤를 0으로 처리
		for (int c = col_cnt; c < n; c++)
		{
			board[depth + 1][r][c] = 0;
		}
	}

	// print_next_board();

	// 상태 변경 후 backtrack
	/*
	memcpy(prev_board, cur_board, sizeof(cur_board));
	memcpy(cur_board, next_board, sizeof(cur_board));
	*/
	backtrack(depth + 1, 9);

	// 초기화
	/*
	memcpy(next_board, cur_board, sizeof(cur_board));
	memcpy(cur_board, prev_board, sizeof(cur_board));
	*/

	// 우
	for (int r = 0; r < n; r++)
	{
		index = 0;
		col_cnt = n - 1;

		init_3();

		for (int c = 0; c < n; c++)
		{
			// 블록만 복사
			if (board[depth][r][c] > 0)
			{
				///*
				tmp_3[index] = board[depth][r][c];
				//*/

				index += 1;
			}
		}

		/*
		printf("index = %d\n", index);
		print_tmp_3(index);
		//printf("\n");
		*/

		for (int c = index - 1; c >= 0; c--)
		{
			// 다음 칸이 남아있다면
			if (c > 0)
			{
				cur_block = tmp_3[c];
				next_block = tmp_3[c - 1];

				// printf("cur = %d, next = %d\n", cur_block, next_block);

				// 블록을 합칠 수 있다면
				if ((cur_block == next_block) && (cur_block > 0))
				{
					board[depth + 1][r][col_cnt] = cur_block + next_block;

					c -= 1;
				}
				// 블록을 합칠 수 없다면
				else
				{
					// 그대로 둔다
					board[depth + 1][r][col_cnt] = cur_block;
				}

				col_cnt -= 1;
			}
			// 다음 칸이 남아있지 않다면
			else
			{
				cur_block = tmp_3[c];

				board[depth + 1][r][col_cnt] = cur_block;

				col_cnt -= 1;
			}
		}

		// printf("col_cnt = %d\n", col_cnt);

		// 뒤를 0으로 처리
		for (int c = col_cnt; c >= 0; c--)
		{
			board[depth + 1][r][c] = 0;
		}
	}

	// print_next_board();

	// 상태 변경 후 backtrack
	/*
	memcpy(prev_board, cur_board, sizeof(cur_board));
	memcpy(cur_board, next_board, sizeof(cur_board));
	*/
	backtrack(depth + 1, 3);

	/*
	// 초기화
	memcpy(next_board, cur_board, sizeof(cur_board));
	memcpy(cur_board, prev_board, sizeof(cur_board));
	*/

	/*
	// 리턴 전 초기화
	memcpy(next_board, cur_board, sizeof(cur_board));
	memcpy(cur_board, prev_board, sizeof(cur_board));
	*/

	return;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	scanf("%d", &n);

	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			scanf("%d", &board[0][row][col]);
		}
	}

	// print_cur_board();

	backtrack(0, 0);

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
