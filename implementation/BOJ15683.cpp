// KJO15683.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 8
#define MAX_M 8
#define MAX_D 8

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>
#include <cstring>

typedef struct cctv {
	int type = 0;
	int dir = 0;
	int row = 0;
	int col = 0;
} CCTV;

int n = 0;
int m = 0;
int ans = (MAX_N * MAX_M);
int cnt = 0;

int matrix[MAX_N + 2][MAX_M + 2] = { 6 };
int copy[MAX_N + 2][MAX_M + 2] = { 6 };
CCTV cctv_list[MAX_D + 1];

void print_matrix()
{
	printf("matrix : \n");

	for (int row = 1; row <= n; row++)
	{
		for (int col = 1; col <= m; col++)
		{
			printf("%d ", matrix[row][col]);
		}

		printf("\n");
	}

	printf("\n");

	return;
}

void print_copy()
{
	printf("copy : \n");

	for (int row = 1; row <= n; row++)
	{
		for (int col = 1; col <= m; col++)
		{
			printf("%d ", copy[row][col]);
		}

		printf("\n");
	}

	printf("\n");

	return;
}

void print_cctv()
{
	printf("cctv_list : \n");

	for (int i = 1; i <= cnt; i++)
	{
		printf("type : %d, dir = %d, pos : (%d, %d)\n", cctv_list[i].type, cctv_list[i].dir, cctv_list[i].row, cctv_list[i].col);
	}

	printf("\n");

	return;
}

void observe_12(int r, int c)
{
	// printf("observe_12()\n");

	int cur = 0;

	// 위쪽으로 감시
	for (int row = r - 1; row > 0; row--)
	{
		cur = copy[row][c];

		// 빈 공간일 경우
		if (cur == 0)
		{
			// 감시 중인 공간으로 표시
			copy[row][c] = 7;
		}
		// 벽일 경우
		else if (cur == 6)
		{
			// 더 이상 감시 불가능
			break;
		}
	}

	return;
}

void observe_3(int r, int c)
{
	// printf("observe_3()\n");

	int cur = 0;

	// 오른쪽으로 감시
	for (int col = c + 1; col < m + 1; col++)
	{
		cur = copy[r][col];

		// 빈 공간일 경우
		if (cur == 0)
		{
			// 감시 중인 공간으로 표시
			copy[r][col] = 7;
		}
		// 벽일 경우
		else if (cur == 6)
		{
			// 더 이상 감시 불가능
			break;
		}
	}

	return;
}

void observe_6(int r, int c)
{
	// printf("observe_6()\n");

	int cur = 0;

	// 아래쪽으로 감시
	for (int row = r + 1; row < n + 1; row++)
	{
		cur = copy[row][c];

		// 빈 공간일 경우
		if (cur == 0)
		{
			// 감시 중인 공간으로 표시
			copy[row][c] = 7;
		}
		// 벽일 경우
		else if (cur == 6)
		{
			// 더 이상 감시 불가능
			break;
		}
	}

	return;
}

void observe_9(int r, int c)
{
	// printf("observe_9()\n");

	int cur = 0;

	// 왼쪽으로 감시
	for (int col = c - 1; col > 0; col--)
	{
		cur = copy[r][col];

		// 빈 공간일 경우
		if (cur == 0)
		{
			// 감시 중인 공간으로 표시
			copy[r][col] = 7;
		}
		// 벽일 경우
		else if (cur == 6)
		{
			// 더 이상 감시 불가능
			break;
		}
	}

	return;
}

void calc_blindspot()
{
	int cur_type = 0;
	int cur_dir = 0;
	int cur_row = 0;
	int cur_col = 0;
	int result = 0;

	// print_cctv();

	// 안전한 계산을 위해 복사
	memcpy(copy, matrix, sizeof(matrix));

	for (int i = 1; i <= cnt; i++)
	{
		// 정보 불러오기
		cur_type = cctv_list[i].type;
		cur_dir = cctv_list[i].dir;
		cur_row = cctv_list[i].row;
		cur_col = cctv_list[i].col;

		// 1번 cctv
		if (cur_type == 1)
		{
			// 0도
			if (cur_dir == 12)
			{
				// 오른쪽 감시 가능
				observe_3(cur_row, cur_col);
			}
			// 90도
			else if (cur_dir == 3)
			{
				// 아래쪽 감시 가능
				observe_6(cur_row, cur_col);
			}
			// 180도
			else if (cur_dir == 6)
			{
				// 왼쪽 감시 가능
				observe_9(cur_row, cur_col);
			}
			// 270도
			else if (cur_dir == 9)
			{
				// 위쪽 감시 가능
				observe_12(cur_row, cur_col);
			}
		}
		// 2번 cctv
		else if (cur_type == 2)
		{
			// 0도
			if (cur_dir == 12)
			{
				// 오른쪽 감시 가능
				observe_3(cur_row, cur_col);
				// 왼쪽 감시 가능
				observe_9(cur_row, cur_col);
			}
			// 90도
			else if (cur_dir == 3)
			{
				// 아래쪽 감시 가능
				observe_6(cur_row, cur_col);
				// 위쪽 감시 가능
				observe_12(cur_row, cur_col);
			}
			// 180도
			else if (cur_dir == 6)
			{
				// 왼쪽 감시 가능
				observe_9(cur_row, cur_col);
				// 오른쪽 감시 가능
				observe_3(cur_row, cur_col);
			}
			// 270도
			else if (cur_dir == 9)
			{
				// 위쪽 감시 가능
				observe_12(cur_row, cur_col);
				// 아래쪽 감시 가능
				observe_6(cur_row, cur_col);
			}
		}
		// 3번 cctv
		else if (cur_type == 3)
		{
			// 0도
			if (cur_dir == 12)
			{
				// 오른쪽 감시 가능
				observe_3(cur_row, cur_col);
				// 위쪽 감시 가능
				observe_12(cur_row, cur_col);
			}
			// 90도
			else if (cur_dir == 3)
			{
				// 아래쪽 감시 가능
				observe_6(cur_row, cur_col);
				// 오른쪽 감시 가능
				observe_3(cur_row, cur_col);
			}
			// 180도
			else if (cur_dir == 6)
			{
				// 왼쪽 감시 가능
				observe_9(cur_row, cur_col);
				// 아래쪽 감시 가능
				observe_6(cur_row, cur_col);
			}
			// 270도
			else if (cur_dir == 9)
			{
				// 위쪽 감시 가능
				observe_12(cur_row, cur_col);
				// 왼쪽 감시 가능
				observe_9(cur_row, cur_col);
			}
		}
		// 4번 cctv
		else if (cur_type == 4)
		{
			// 0도
			if (cur_dir == 12)
			{
				// 오른쪽 감시 가능
				observe_3(cur_row, cur_col);
				// 위쪽 감시 가능
				observe_12(cur_row, cur_col);
				// 왼쪽 감시 가능
				observe_9(cur_row, cur_col);
			}
			// 90도
			else if (cur_dir == 3)
			{
				// 아래쪽 감시 가능
				observe_6(cur_row, cur_col);
				// 오른쪽 감시 가능
				observe_3(cur_row, cur_col);
				// 위쪽 감시 가능
				observe_12(cur_row, cur_col);
			}
			// 180도
			else if (cur_dir == 6)
			{
				// 왼쪽 감시 가능
				observe_9(cur_row, cur_col);
				// 아래쪽 감시 가능
				observe_6(cur_row, cur_col);
				// 오른쪽 감시 가능
				observe_3(cur_row, cur_col);
			}
			// 270도
			else if (cur_dir == 9)
			{
				// 위쪽 감시 가능
				observe_12(cur_row, cur_col);
				// 왼쪽 감시 가능
				observe_9(cur_row, cur_col);
				// 아래쪽 감시 가능
				observe_6(cur_row, cur_col);
			}
		}
		// 5번 cctv
		else if (cur_type == 5)
		{
			// 모두 감시 가능
			observe_12(cur_row, cur_col);
			observe_3(cur_row, cur_col);
			observe_6(cur_row, cur_col);
			observe_9(cur_row, cur_col);
		}
	}

	// print_copy();

	// 사각지대 갯수 세기
	for (int row = 1; row <= n; row++)
	{
		for (int col = 1; col <= m; col++)
		{
			if (copy[row][col] == 0)
			{
				result += 1;
			}
		}
	}

	// 정답 갱신
	if (result < ans)
	{
		ans = result;
	}

	return;
}

void backtrack(int depth)
{
	// printf("depth = %d\n", depth);

	// 모든 cctv 설치했다면
	if (depth == cnt)
	{
		// 사각지대 계산
		calc_blindspot();

		return;
	}

	// 0도
	cctv_list[depth + 1].dir = 12;

	backtrack(depth + 1);

	// 90도
	cctv_list[depth + 1].dir = 3;

	backtrack(depth + 1);

	// 180도
	cctv_list[depth + 1].dir = 6;

	backtrack(depth + 1);

	// 270도
	cctv_list[depth + 1].dir = 9;

	backtrack(depth + 1);

	// 초기화
	cctv_list[depth + 1].dir = 0;

	return;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	int tmp = 0;

	scanf("%d %d", &n, &m);

	for (int row = 0; row < n + 2; row++)
	{
		for (int col = 0; col < m + 2; col++)
		{
			// 테두리는
			if ((row == 0) || (row == n + 1) || (col == 0) || (col == m + 1))
			{
				// 벽으로
				matrix[row][col] = 6;
			}
			// 안쪽은
			else
			{
				scanf("%d", &tmp);

				matrix[row][col] = tmp;

				// CCTV라면
				if ((tmp > 0) && (tmp < 6))
				{
					// 갯수 추가
					cnt += 1;

					// 정보 기록
					cctv_list[cnt].type = tmp;
					// cctv_list[cnt].dir = 0;
					cctv_list[cnt].row = row;
					cctv_list[cnt].col = col;
				}
			}
		}
	}

	/*
	print_matrix();
	print_cctv();
	*/

	backtrack(0);

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
