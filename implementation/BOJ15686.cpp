// KJO15686.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 50
#define MAX_M 13
#define MAX_1 100
#define MAX_2 13
#define INF 1000000000

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>
#include <math.h>

typedef struct node {
	int isOpen = 1;
	int r = 0;
	int c = 0;
} NODE;

int n = 0;
int m = 0;
int cnt_1 = 0;
int cnt_2 = 0;
int ans = INF;

NODE list_1[MAX_1] = { 0 };
NODE list_2[MAX_2] = { 0 };
int matrix[MAX_N + 2][MAX_N + 2] = { 0 };

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

void print_list1()
{
	printf("list_1 : \n");
	
	for (int i = 0; i < cnt_1; i++)
	{
		printf("isOpen : %d, pos : (%d, %d)\n", list_1[i].isOpen, list_1[i].r, list_1[i].c);
	}

	printf("\n");

	return;
}

void print_list2()
{
	printf("list_2 : \n");

	for (int i = 0; i < cnt_2; i++)
	{
		printf("isOpen : %d, pos : (%d, %d)\n", list_2[i].isOpen, list_2[i].r, list_2[i].c);
	}

	printf("\n");

	return;
}

int calc_dist(int a1, int b1, int a2, int b2)
{
	return (abs(a2 - a1) + abs(b2 - b1));
}

void calc_ans()
{
	int r1 = 0;
	int c1 = 0;
	int r2 = 0;
	int c2 = 0;
	int city_dist = 0;
	int home_dist = INF;
	int result_dist = 0;

	for (int i = 0; i < cnt_1; i++)
	{
		home_dist = INF;

		r1 = list_1[i].r;
		c1 = list_1[i].c;

		for (int j = 0; j < cnt_2; j++)
		{
			// 열려 있는 경우에만 거리 계산
			if (list_2[j].isOpen)
			{
				r2 = list_2[j].r;
				c2 = list_2[j].c;

				result_dist = calc_dist(r1, c1, r2, c2);

				if (result_dist < home_dist)
				{
					home_dist = result_dist;
				}
			}
		}

		city_dist += home_dist;
	}

	if (city_dist < ans)
	{
		ans = city_dist;
	}

	return;
}

void backtrack(int start, int remain)
{
	// 남아있는 치킨집이 m개라면
	if (remain == m)
	{
		// 치킨 거리 구하자
		calc_ans();

		return;
	}

	for (int i = start; i < cnt_2; i++)
	{
		// 치킨집이 열려있다면
		if (list_2[i].isOpen)
		{
			// printf("i = %d, remain = %d\n", i, remain);

			// 닫아버리고
			list_2[i].isOpen = 0;

			// 완전탐색
			backtrack(i + 1, remain - 1);

			// 초기화
			list_2[i].isOpen = 1;
		}
	}

	return;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	int tmp = 0;

	scanf("%d %d", &n, &m);

	for (int row = 1; row <= n; row++)
	{
		for (int col = 1; col <= n; col++)
		{
			scanf("%d", &tmp);

			matrix[row][col] = tmp;

			// 집일 경우
			if (tmp == 1)
			{
				list_1[cnt_1].isOpen = 1;
				list_1[cnt_1].r = row;
				list_1[cnt_1].c = col;

				cnt_1 += 1;
			}
			// 치킨집일 경우
			else if (tmp == 2)
			{
				list_2[cnt_2].isOpen = 1;
				list_2[cnt_2].r = row;
				list_2[cnt_2].c = col;

				cnt_2 += 1;
			}
		}
	}

	/*
	print_matrix();
	print_list1();
	print_list2();
	*/

	backtrack(0, cnt_2);

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
