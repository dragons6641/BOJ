// KJO5373.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_T 100
#define MAX_N 1000
#define COMS 3
#define SIDES 6
#define ROWS 3
#define COLS 3

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>

int t = 0;
int n = 0;

char cube[SIDES][ROWS][COLS];
char info[MAX_N][COMS];

void init()
{
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			// 윗면 흰색
			cube[0][row][col] = 'w';
			// 아랫면 노란색
			cube[1][row][col] = 'y';
			// 앞면 빨간색
			cube[2][row][col] = 'r';
			// 뒷면 오렌지색
			cube[3][row][col] = 'o';
			// 왼쪽면 초록색
			cube[4][row][col] = 'g';
			// 오른쪽면 파란색
			cube[5][row][col] = 'b';
		}
	}

	for (int i = 0; i < MAX_N; i++)
	{
		for (int j = 0; j < COMS; j++)
		{
			info[i][j] = '\0';
		}
	}

	return;
}

void print_cube()
{
	printf("cube : \n");

	for (int k = 0; k < SIDES; k++)
	{
		printf("side = %d\n", k);

		for (int row = 0; row < ROWS; row++)
		{
			for (int col = 0; col < COLS; col++)
			{
				printf("%c", cube[k][row][col]);
			}

			printf("\n");
		}

		printf("\n");
	}

	printf("\n");

	return;
}

void print_info()
{
	printf("info : \n");

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < COMS; j++)
		{
			printf("%c", info[i][j]);
		}
		
		printf("\n");
	}

	printf("\n");

	return;
}

void print_ans()
{
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			printf("%c", cube[0][row][col]);
		}

		printf("\n");
	}

	// printf("\n");

	return;
}

void change()
{


	return;
}

void change(char side, char dir)
{
	char tmp;

	// 시계 방향
	if (dir == '+')
	{
		tmp = cube[side][1][0];
		cube[side][1][0] = cube[side][2][1];
		cube[side][2][1] = cube[side][1][2];
		cube[side][1][2] = cube[side][0][1];
		cube[side][0][1] = tmp;

		tmp = cube[side][0][0];
		cube[side][0][0] = cube[side][2][0];
		cube[side][2][0] = cube[side][2][2];
		cube[side][2][2] = cube[side][0][2];
		cube[side][0][2] = tmp;
	}
	// 반시계 방향
	else if (dir == '-')
	{
		tmp = cube[side][0][1];
		cube[side][0][1] = cube[side][1][2];
		cube[side][1][2] = cube[side][2][1];
		cube[side][2][1] = cube[side][1][0];
		cube[side][1][0] = tmp;

		tmp = cube[side][0][0];
		cube[side][0][0] = cube[side][0][2];
		cube[side][0][2] = cube[side][2][2];
		cube[side][2][2] = cube[side][2][0];
		cube[side][2][0] = tmp;
	}

	return;
}

void swap(char dir, 
	char* c1, char* c2, char* c3, 
	char* c4, char* c5, char* c6, 
	char* c7, char* c8, char* c9, 
	char* c10, char* c11, char* c12)
{
	int tmp1;
	int tmp2;
	int tmp3;

	// printf("dir = %c, before swap : %c%c%c %c%c%c %c%c%c %c%c%c\n", dir, *c1, *c2, *c3, *c4, *c5, *c6, *c7, *c8, *c9, *c10, *c11, *c12);
	
	// 시계 방향
	if (dir == '+')
	{
		tmp1 = *c10;
		tmp2 = *c11;
		tmp3 = *c12;

		*c10 = *c7;
		*c11 = *c8;
		*c12 = *c9;

		*c7 = *c4;
		*c8 = *c5;
		*c9 = *c6;

		*c4 = *c1;
		*c5 = *c2;
		*c6 = *c3;

		*c1 = tmp1;
		*c2 = tmp2;
		*c3 = tmp3;
	}
	else if (dir == '-')
	{
		tmp1 = *c1;
		tmp2 = *c2;
		tmp3 = *c3;

		*c1 = *c4;
		*c2 = *c5;
		*c3 = *c6;

		*c4 = *c7;
		*c5 = *c8;
		*c6 = *c9;

		*c7 = *c10;
		*c8 = *c11;
		*c9 = *c12;

		*c10 = tmp1;
		*c11 = tmp2;
		*c12 = tmp3;
	}

	// printf("dir = %c, after swap : %c%c%c %c%c%c %c%c%c %c%c%c\n", dir, *c1, *c2, *c3, *c4, *c5, *c6, *c7, *c8, *c9, *c10, *c11, *c12);

	return;
}

void rotate(char side, char dir)
{
	// printf("side = %c, dir = %c\n", side, dir);

	// 윗면을
	// F, B, L, R
	if (side == 'U')
	{
		// 시계 방향으로
		if (dir == '+')
		{
			// 해당 면 변경
			change(0, '+');

			// 3, 5, 2, 4
			swap('+',
				&cube[3][0][2], &cube[3][0][1], &cube[3][0][0],
				&cube[5][0][2], &cube[5][0][1], &cube[5][0][0],
				&cube[2][0][2], &cube[2][0][1], &cube[2][0][0],
				&cube[4][0][2], &cube[4][0][1], &cube[4][0][0]);
		}
		// 반시계 방향으로
		else if (dir == '-')
		{
			// 해당 면 변경
			change(0, '-');

			// 3, 5, 2, 4
			swap('-',
				&cube[3][0][2], &cube[3][0][1], &cube[3][0][0],
				&cube[5][0][2], &cube[5][0][1], &cube[5][0][0],
				&cube[2][0][2], &cube[2][0][1], &cube[2][0][0],
				&cube[4][0][2], &cube[4][0][1], &cube[4][0][0]);
		}
	}
	// 아랫면을
	// F, B, L, R
	else if (side == 'D')
	{
		// 시계 방향으로
		if (dir == '+')
		{
			// 해당 면 변경
			change(1, '+');

			// 2, 5, 3, 4
			swap('+',
				&cube[2][2][0], &cube[2][2][1], &cube[2][2][2],
				&cube[5][2][0], &cube[5][2][1], &cube[5][2][2],
				&cube[3][2][0], &cube[3][2][1], &cube[3][2][2],
				&cube[4][2][0], &cube[4][2][1], &cube[4][2][2]);
		}
		// 반시계 방향으로
		else if (dir == '-')
		{
			// 해당 면 변경
			change(1, '-');

			// 2, 5, 3, 4
			swap('-',
				&cube[2][2][0], &cube[2][2][1], &cube[2][2][2],
				&cube[5][2][0], &cube[5][2][1], &cube[5][2][2],
				&cube[3][2][0], &cube[3][2][1], &cube[3][2][2],
				&cube[4][2][0], &cube[4][2][1], &cube[4][2][2]);
		}
	}
	// 앞면을
	// U, D, L, R
	else if (side == 'F')
	{
		// 시계 방향으로
		if (dir == '+')
		{
			// 해당 면 변경
			change(2, '+');

			// 0, 5, 1, 4
			swap('+',
				&cube[0][2][0], &cube[0][2][1], &cube[0][2][2],
				&cube[5][0][0], &cube[5][1][0], &cube[5][2][0],
				&cube[1][2][0], &cube[1][2][1], &cube[1][2][2],
				&cube[4][2][2], &cube[4][1][2], &cube[4][0][2]);
		}
		// 반시계 방향으로
		else if (dir == '-')
		{
			// 해당 면 변경
			change(2, '-');

			// 0, 5, 1, 4
			swap('-',
				&cube[0][2][0], &cube[0][2][1], &cube[0][2][2],
				&cube[5][0][0], &cube[5][1][0], &cube[5][2][0],
				&cube[1][2][0], &cube[1][2][1], &cube[1][2][2],
				&cube[4][2][2], &cube[4][1][2], &cube[4][0][2]);
		}
	}
	// 뒷면을
	// U, D, L, R
	else if (side == 'B')
	{
		// 시계 방향으로
		if (dir == '+')
		{
			// 해당 면 변경
			change(3, '+');

			// 0, 4, 1, 5
			swap('+',
				&cube[0][0][2], &cube[0][0][1], &cube[0][0][0],
				&cube[4][0][0], &cube[4][1][0], &cube[4][2][0],
				&cube[1][0][2], &cube[1][0][1], &cube[1][0][0],
				&cube[5][2][2], &cube[5][1][2], &cube[5][0][2]);
		}
		// 반시계 방향으로
		else if (dir == '-')
		{
			// 해당 면 변경
			change(3, '-');

			// 0, 4, 1, 5
			swap('-',
				&cube[0][0][2], &cube[0][0][1], &cube[0][0][0],
				&cube[4][0][0], &cube[4][1][0], &cube[4][2][0],
				&cube[1][0][2], &cube[1][0][1], &cube[1][0][0],
				&cube[5][2][2], &cube[5][1][2], &cube[5][0][2]);
		}
	}
	// 왼쪽면을
	// U, D, F, B
	else if (side == 'L')
	{
		// 시계 방향으로
		if (dir == '+')
		{
			// 해당 면 변경
			change(4, '+');

			// 0, 2, 1, 3
			swap('+',
				&cube[0][0][0], &cube[0][1][0], &cube[0][2][0],
				&cube[2][0][0], &cube[2][1][0], &cube[2][2][0],
				&cube[1][2][2], &cube[1][1][2], &cube[1][0][2],
				&cube[3][2][2], &cube[3][1][2], &cube[3][0][2]);
		}
		// 반시계 방향으로
		else if (dir == '-')
		{
			// 해당 면 변경
			change(4, '-');

			// 0, 2, 1, 3
			swap('-',
				&cube[0][0][0], &cube[0][1][0], &cube[0][2][0],
				&cube[2][0][0], &cube[2][1][0], &cube[2][2][0],
				&cube[1][2][2], &cube[1][1][2], &cube[1][0][2],
				&cube[3][2][2], &cube[3][1][2], &cube[3][0][2]);
		}
	}
	// 오른쪽면을
	// U, D, F, B
	else if (side == 'R')
	{
		// 시계 방향으로
		if (dir == '+')
		{
			// 해당 면 변경
			change(5, '+');

			// 0, 3, 1, 2
			swap('+',
				&cube[0][2][2], &cube[0][1][2], &cube[0][0][2],
				&cube[3][0][0], &cube[3][1][0], &cube[3][2][0],
				&cube[1][0][0], &cube[1][1][0], &cube[1][2][0],
				&cube[2][2][2], &cube[2][1][2], &cube[2][0][2]);
		}
		// 반시계 방향으로
		else if (dir == '-')
		{
			// 해당 면 변경
			change(5, '-');

			// 0, 3, 1, 2
			swap('-',
				&cube[0][2][2], &cube[0][1][2], &cube[0][0][2],
				&cube[3][0][0], &cube[3][1][0], &cube[3][2][0],
				&cube[1][0][0], &cube[1][1][0], &cube[1][2][0],
				&cube[2][2][2], &cube[2][1][2], &cube[2][0][2]);
		}
	}

	return;
}

void simulate()
{
	// 명령 수행
	for (int i = 0; i < n; i++)
	{
		rotate(info[i][0], info[i][1]);
	}

	return;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	scanf("%d", &t);

	for (int tc = 1; tc <= t; tc++)
	{
		init();

		scanf("%d", &n);

		for (int i = 0; i < n; i++)
		{
			scanf("%s", info[i]);
		}

		/*
		print_cube();
		print_info();
		*/

		simulate();

		print_ans();
	}

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
