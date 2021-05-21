// KJO14889.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 20
#define INF 1000000000

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>

int n = 0;
int ans = INF;
int cnt_start = 0;
int cnt_link = 0;

int matrix[MAX_N][MAX_N] = { 0 };
int team[MAX_N] = { 0 };

void print_matrix()
{
	printf("matrix : \n");

	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			printf("%d ", matrix[row][col]);
		}

		printf("\n");
	}

	return;
}

void print_team()
{
	printf("team : \n");

	for (int i = 0; i < n; i++)
	{
		printf("%d ", team[i]);
	}

	printf("\n");

	return;
}

void calc_diff()
{
	int ovr_start = 0;
	int ovr_link = 0;
	int result = 0;

	// print_team();

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			// 같은 팀일 경우
			if (team[i] == team[j])
			{
				// 링크팀
				if (team[i])
				{
					ovr_link += matrix[i][j];
				}
				// 스타트팀
				else
				{
					ovr_start += matrix[i][j];
				}
			}
		}
	}

	if (ovr_start > ovr_link)
	{
		result = ovr_start - ovr_link;
	}
	else
	{
		result = ovr_link - ovr_start;
	}

	if (result < ans)
	{
		ans = result;
	}

	return;
}

void backtrack(int start_pos)
{
	// 스타트팀 : 0, 링크팀 : 1
	/*
	print_team();
	printf("start : link = %d : %d, depth = %d\n", cnt_start, cnt_link, depth);
	*/

	// 팀 다 짰으면
	// if (depth == n / 2)
	if (cnt_start == cnt_link)
	{
		calc_diff();

		return;
	}

	for (int i = start_pos; i < n; i++)
	{
		// 링크 팀 자리 있으면
		if ((team[i] == 0) && (cnt_link < n / 2))
		{
			// 링크팀으로
			team[i] = 1;
			cnt_start -= 1;
			cnt_link += 1;

			// 완전탐색
			backtrack(i);

			///*
			// 초기화
			team[i] = 0;
			cnt_start += 1;
			cnt_link -= 1;
			//*/
		}
	}

	return;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	scanf("%d", &n);

	cnt_start = n;

	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			scanf("%d", &matrix[row][col]);
		}
	}

	// print_matrix();

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
