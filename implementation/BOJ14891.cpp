// KJO14891.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_K 100
#define TOOTHS 8
#define WHEELS 4
#define LEFT 6
#define RIGHT 2
#define POINT 0

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>

typedef struct node {
	int num = -1;
	int dir = 0;
}NODE;

int k = 0;
int ans = 0;

int matrix[WHEELS + 1][TOOTHS] = { -1 };
int isRotate[WHEELS + 1] = { 0 };
NODE info_list[MAX_K];

void print_matrix()
{
	printf("matrix : \n");

	for (int i = 1; i <= WHEELS; i++)
	{
		for (int j = 0; j < TOOTHS; j++)
		{
			printf("%d ", matrix[i][j]);
		}

		printf("\n");
	}

	printf("\n");

	return;
}

void print_info()
{
	printf("info_list : \n");

	for (int i = 0; i < k; i++)
	{
		printf("%d %d\n", info_list[i].num, info_list[i].dir);
	}

	printf("\n");

	return;
}

void print_rotate()
{
	printf("isRotate : ");

	for (int i = 1; i <= WHEELS; i++)
	{
		printf("%d ", isRotate[i]);
	}

	printf("\n");

	return;
}

void init()
{
	for (int i = 1; i <= WHEELS; i++)
	{
		isRotate[i] = 0;
	}

	return;
}

void rotate_right(int n)
{
	int tmp = matrix[n][TOOTHS - 1];
	
	for (int i = TOOTHS - 2; i >= 0; i--)
	{
		matrix[n][i + 1] = matrix[n][i];
	}

	matrix[n][0] = tmp;

	return;
}

void rotate_left(int n)
{
	int tmp = matrix[n][0];

	for (int i = 0; i < TOOTHS - 1; i++)
	{
		matrix[n][i] = matrix[n][i + 1];
	}

	matrix[n][TOOTHS - 1] = tmp;

	return;
}

int check_right(int n)
{
	int cur = matrix[n][RIGHT];
	int next = matrix[n + 1][LEFT];

	// 극이 다르면
	if (cur != next)
	{
		// 다음 회전 실행
		return 1;
	}
	// 극이 같으면
	else
	{
		// 회전 종료
		return 0;
	}

	return -1;
}

int check_left(int n)
{
	int cur = matrix[n][LEFT];
	int next = matrix[n - 1][RIGHT];

	// 극이 다르면
	if (cur != next)
	{
		// 다음 회전 실행
		return 1;
	}
	// 극이 같으면
	else
	{
		// 회전 종료
		return 0;
	}

	return -1;
}

void check_all(int n, int d)
{
	int cur_dir = d;
	int chk = -1;

	isRotate[n] = d;

	// 오른쪽 체크
	for (int i = n; i < WHEELS; i++)
	{
		// 같이 도는지 확인
		chk = check_right(i);

		// 같이 돈다면
		if (chk)
		{
			if (cur_dir == 1)
			{
				cur_dir = -1;
			}
			else if (cur_dir == -1)
			{
				cur_dir = 1;
			}

			isRotate[i + 1] = cur_dir;
		}
		// 돌지 않는다면
		else
		{
			cur_dir = 0;

			break;
		}
	}

	cur_dir = d;
	chk = -1;

	// 왼쪽 체크
	for (int i = n; i > 1; i--)
	{
		// 같이 도는지 확인
		chk = check_left(i);

		// 같이 돈다면
		if (chk)
		{
			if (cur_dir == 1)
			{
				cur_dir = -1;
			}
			else if (cur_dir == -1)
			{
				cur_dir = 1;
			}

			isRotate[i - 1] = cur_dir;
		}
		// 돌지 않는다면
		else
		{
			cur_dir = 0;

			break;
		}
	}

	return;
}

// void rotate(int cur_num, int prev_num, int cur_dir)
void rotate(int n, int d)
{
	check_all(n, d);

	// print_rotate();

	for (int i = 1; i <= WHEELS; i++)
	{
		// 시계 방향
		if (isRotate[i] == 1)
		{
			rotate_right(i);
		}
		// 반시계 방향
		else if (isRotate[i] == -1)
		{
			rotate_left(i);
		}
	}

	/*
	int next_dir = 0;
	int chk = -1;
	*/

	/*
	// 시계 방향
	if (cur_dir == 1)
	{
		next_dir = 1;
	}
	// 반시계 방향
	else if (cur_dir == -1)
	{
		next_dir = -1;
	}
	*/

	/*
	// 현재 시계 방향 회전이면
	if (cur_dir == 1)
	{
		// 방향대로 회전
		rotate_right(cur_num);

		// 다음 톱니는 반대로
		next_dir = -1;
	}
	// 현재 반시계 방향 회전이면
	else if (cur_dir == -1)
	{
		// 방향대로 회전
		rotate_left(cur_num);

		// 다음 톱니는 반대로
		next_dir = 1;
	}

	// 마지막 톱니가 아니면
	if ((cur_num < WHEELS) && (cur_num >= prev_num))
	{
		// 오른쪽 톱니 체크
		chk = check_right(cur_num);
	}
	else
	{
		chk = 0;
	}

	// 추가 회전 필요하면
	if (chk)
	{
		// 다음 회전 실행
		rotate(cur_num + 1, cur_num, next_dir);
	}

	// 처음 톱니가 아니면
	if ((cur_num > 1) && (cur_num <= prev_num))
	{
		// 왼쪽 톱니 체크
		chk = check_left(cur_num);
	}
	else
	{
		chk = 0;
	}

	// 추가 회전 필요하면
	if (chk)
	{
		// 다음 회전 실행
		rotate(cur_num - 1, cur_num, next_dir);
	}
	*/

	return;
}

void count_point()
{
	int factor = 1;

	for (int i = 1; i <= WHEELS; i++)
	{
		ans += (matrix[i][POINT] * factor);

		factor *= 2;
	}

	return;
}

void simulate()
{
	for (int i = 0; i < k; i++)
	{
		rotate(info_list[i].num, info_list[i].dir);

		init();

		// print_matrix();
	}

	count_point();

	return;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	for (int i = 1; i <= WHEELS; i++)
	{
		for (int j = 0; j < TOOTHS; j++)
		{
			scanf("%1d", &matrix[i][j]);
		}
	}

	scanf("%d", &k);

	for (int i = 0; i < k; i++)
	{
		scanf("%d %d", &info_list[i].num, &info_list[i].dir);
	}

	/*
	print_matrix();
	print_info();
	*/

	simulate();

	/*
	rotate_left(1);
	rotate_right(2);

	print_matrix();
	*/

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
