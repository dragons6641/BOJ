// KJO14503.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 50
#define MAX_M 50
#define MAX_D 4

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>

int n = 0;
int m = 0;
int r = 0;
int c = 0;
int d = 0;
int ans = 0;

int matrix[MAX_N][MAX_M] = { 1 };

void print_matrix()
{
	printf("matrix : \n");

	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < m; col++)
		{
			printf("%d ", matrix[row][col]);
		}

		printf("\n");
	}

	return;
}

int rotate_left(int dir)
{
	// 북쪽
	if (dir == 0)
	{
		// 서쪽으로
		return 3;
	}
	// 동쪽
	else if (dir == 1)
	{
		// 북쪽으로
		return 0;
	}
	// 남쪽
	else if (dir == 2)
	{
		// 동쪽으로
		return 1;
	}
	// 서쪽
	else if (dir == 3)
	{
		// 남쪽으로
		return 2;
	}

	return -1;
}

void simulate()
{
	int cur_row = r;
	int cur_col = c;
	int cur_dir = d;
	int rotate_cnt = 0;
	int goto_1 = 0;

	// 1번으로 가는 것은 break
	// 2번으로 가는 것은 continue
	while (1)
	{
		/*
		print_matrix();

		printf("cur = (%d, %d), dir = %d\n", cur_row, cur_col, cur_dir);
		*/

		// 초기화
		rotate_cnt = 0;
		goto_1 = 0;

		// 1. 청소하지 않은 칸이라면
		if (matrix[cur_row][cur_col] == 0)
		{
			// 청소한다
			matrix[cur_row][cur_col] = 2;

			ans += 1;
		}

		// 2. 왼쪽부터
		for (int i = 0; i < MAX_D; i++)
		{
			// 북쪽일 경우
			if (cur_dir == 0)
			{
				// 서쪽 청소 안했으면
				if (matrix[cur_row][cur_col - 1] == 0)
				{
					// 왼쪽으로 회전
					cur_dir = rotate_left(cur_dir);

					// 회전 횟수 증가
					rotate_cnt += 1;

					// 전진
					cur_col -= 1;

					// 1번으로
					goto_1 = 1;

					break;
				}
				// 청소를 했거나 벽이면
				else
				{
					// 왼쪽으로 회전
					cur_dir = rotate_left(cur_dir);

					// 회전 횟수 증가
					rotate_cnt += 1;

					// 2번으로
					continue;
				}
			}
			// 동쪽일 경우
			else if (cur_dir == 1)
			{
				// 북쪽 청소 안했으면
				if (matrix[cur_row - 1][cur_col] == 0)
				{
					// 왼쪽으로 회전
					cur_dir = rotate_left(cur_dir);

					// 회전 횟수 증가
					rotate_cnt += 1;

					// 전진
					cur_row -= 1;

					// 1번으로
					goto_1 = 1;

					break;
				}
				// 청소를 했거나 벽이면
				else
				{
					// 왼쪽으로 회전
					cur_dir = rotate_left(cur_dir);

					// 회전 횟수 증가
					rotate_cnt += 1;

					// 2번으로
					continue;
				}
			}
			// 남쪽일 경우
			else if (cur_dir == 2)
			{
				// 동쪽 청소 안했으면
				if (matrix[cur_row][cur_col + 1] == 0)
				{
					// 왼쪽으로 회전
					cur_dir = rotate_left(cur_dir);

					// 회전 횟수 증가
					rotate_cnt += 1;

					// 전진
					cur_col += 1;

					// 1번으로
					goto_1 = 1;

					break;
				}
				// 청소를 했거나 벽이면
				else
				{
					// 왼쪽으로 회전
					cur_dir = rotate_left(cur_dir);

					// 회전 횟수 증가
					rotate_cnt += 1;

					// 2번으로
					continue;
				}
			}
			// 서쪽일 경우
			else if (cur_dir == 3)
			{
				// 남쪽 청소 안했으면
				if (matrix[cur_row + 1][cur_col] == 0)
				{
					// 왼쪽으로 회전
					cur_dir = rotate_left(cur_dir);

					// 회전 횟수 증가
					rotate_cnt += 1;

					// 전진
					cur_row += 1;

					// 1번으로
					goto_1 = 1;

					break;
				}
				// 청소를 했거나 벽이면
				else
				{
					// 왼쪽으로 회전
					cur_dir = rotate_left(cur_dir);

					// 회전 횟수 증가
					rotate_cnt += 1;

					// 2번으로
					continue;
				}
			}
		}

		// 1번으로 보내주자
		if (goto_1)
		{
			continue;
		}

		// 4방향 모두 청소 혹은 벽인 경우만 이 코드 실행
		// 북쪽일 경우
		if (cur_dir == 0)
		{
			// 남쪽으로 후진 가능하다면
			if (matrix[cur_row + 1][cur_col] != 1)
			{
				// 후진
				cur_row += 1;

				// 2번으로
				continue;
			}
			// 후진 불가능하다면
			else
			{
				// 멈춤
				return;
			}
		}
		// 동쪽일 경우
		else if (cur_dir == 1)
		{
			// 서쪽으로 후진 가능하다면
			if (matrix[cur_row][cur_col - 1] != 1)
			{
				// 후진
				cur_col -= 1;

				// 2번으로
				continue;
			}
			// 후진 불가능하다면
			else
			{
				// 멈춤
				return;
			}
		}
		// 남쪽일 경우
		else if (cur_dir == 2)
		{
			// 북쪽으로 후진 가능하다면
			if (matrix[cur_row - 1][cur_col] != 1)
			{
				// 후진
				cur_row -= 1;

				// 2번으로
				continue;
			}
			// 후진 불가능하다면
			else
			{
				// 멈춤
				return;
			}
		}
		// 서쪽일 경우
		else if (cur_dir == 3)
		{
			// 동쪽으로 후진 가능하다면
			if (matrix[cur_row][cur_col + 1] != 1)
			{
				// 후진
				cur_col += 1;

				// 2번으로
				continue;
			}
			// 후진 불가능하다면
			else
			{
				// 멈춤
				return;
			}
		}
	}

	return;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	scanf("%d %d", &n, &m);

	scanf("%d %d %d", &r, &c, &d);

	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < m; col++)
		{
			scanf("%d", &matrix[row][col]);
		}
	}

	// print_matrix();

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
