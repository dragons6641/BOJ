// KJO14499.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 20
#define MAX_M 20
#define MAX_K 1000
#define MAX_S 6

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>

int n = 0;
int m = 0;
int x = 0;
int y = 0;
int k = 0;

int matrix[MAX_M][MAX_N] = { 0 };
int command[MAX_K] = { 0 };
// 바닥은 dice[0], 윗면은 dice[1]
int dice[MAX_S] = { 0 };

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

void print_command()
{
	printf("command : \n");

	for (int i = 0; i < k; i++)
	{
		printf("%d ", command[i]);
	}

	printf("\n");

	return;
}

void next_dice(int dir)
{
	int tmp = 0;

	// 동
	if (dir == 1)
	{
		tmp = dice[0];
		dice[0] = dice[3];
		dice[3] = dice[1];
		dice[1] = dice[4];
		dice[4] = tmp;
	}
	// 서
	else if (dir == 2)
	{
		tmp = dice[0];
		dice[0] = dice[4];
		dice[4] = dice[1];
		dice[1] = dice[3];
		dice[3] = tmp;
	}
	// 북
	else if (dir == 3)
	{
		tmp = dice[0];
		dice[0] = dice[2];
		dice[2] = dice[1];
		dice[1] = dice[5];
		dice[5] = tmp;
	}
	// 남
	else if (dir == 4)
	{
		tmp = dice[0];
		dice[0] = dice[5];
		dice[5] = dice[1];
		dice[1] = dice[2];
		dice[2] = tmp;
	}

	return;
}

void simulate()
{
	int cur_r = x;
	int cur_c = y;
	int roll_dir = 0;

	for (int i = 0; i < k; i++)
	{
		roll_dir = command[i];

		// printf("cur = (%d, %d), matrix = %d, command = %d, bottom = %d, top = %d\n", cur_r, cur_c, matrix[cur_r][cur_c], roll_dir, dice[0], dice[1]);

		// 이동 방향에 따라 굴리기
		// 동
		if (roll_dir == 1)
		{
			// 이동 불가
			if (cur_c == m - 1)
			{
				continue;
			}
			// 이동 가능
			else
			{
				cur_c += 1;
			}
		}
		// 서
		else if (roll_dir == 2)
		{
			// 이동 불가
			if (cur_c == 0)
			{
				continue;
			}
			// 이동 가능
			else
			{
				cur_c -= 1;
			}
		}
		// 북
		else if (roll_dir == 3)
		{
			// 이동 불가
			if (cur_r == 0)
			{
				continue;
			}
			// 이동 가능
			else
			{
				cur_r -= 1;
			}
		}
		// 남
		else if (roll_dir == 4)
		{
			// 이동 불가
			if (cur_r == n - 1)
			{
				continue;
			}
			// 이동 가능
			else
			{
				cur_r += 1;
			}
		}

		// 주사위 상태 변경
		next_dice(roll_dir);

		// 이동한 바닥 칸이 0이면
		if (matrix[cur_r][cur_c] == 0)
		{
			// 주사위 칸을 바닥면에 복사
			matrix[cur_r][cur_c] = dice[0];
		}
		// 이동한 바닥 칸이 0이 아니면
		else
		{
			// 바닥면이 주사위 칸에 복사
			dice[0] = matrix[cur_r][cur_c];
			// 칸은 0으로
			matrix[cur_r][cur_c] = 0;
		}

		// 윗면 값을 출력
		printf("%d\n", dice[1]);
	}

	return;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	int ans = 0;

	scanf("%d %d %d %d %d", &n, &m, &x, &y, &k);

	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < m; col++)
		{
			scanf("%d", &matrix[row][col]);
		}
	}

	for (int i = 0; i < k; i++)
	{
		scanf("%d", &command[i]);
	}

	/*
	print_matrix();
	print_command();
	*/

	simulate();

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
