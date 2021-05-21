// KJO14501.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 15
#define MAX_D 15
#define MAX_T 5
#define MAX_P 100

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>
#include <algorithm>

using namespace std;

typedef struct consult {
	// 금액 / 기간
	float factor = 0;
	// 시작
	int start = 0;
	// 기간
	int t = 0;
	// 금액
	int p = 0;
}CONSULT;

int n = 0;
int ans = 0;

CONSULT schedule[MAX_N + 1];
// int isBooked[MAX_D + 1][MAX_N + 1];
int isBooked[MAX_N + 1] = { 0 };

bool cmp(const CONSULT &a, const CONSULT &b)
{
	if (a.factor > b.factor)
	{
		return true;
	}
	else if (a.factor == b.factor)
	{
		return a.p > b.p;
	}
	else
	{
		return false;
	}
}

void print_schedule()
{
	printf("schedule : \n");

	for (int i = 1; i <= n; i++)
	{
		printf("%f %d %d %d\n", schedule[i].factor, schedule[i].start, schedule[i].t, schedule[i].p);
	}

	printf("\n");

	return;
}

void calc_factor()
{
	for (int i = 1; i <= n; i++)
	{
		schedule[i].factor = (float)(schedule[i].p) / (float)(schedule[i].t);
	}

	return;
}

/*
void greedy()
{
	// sort(schedule + 1, schedule + n + 1);

	float cur_factor = 0;
	int cur_start = 0;
	int cur_t = 0;
	int cur_p = 0;
	int isAvailable = 1;
	
	sort(schedule + 1, schedule + n + 1, cmp);

	// print_schedule();

	for (int i = 1; i <= n; i++)
	{
		cur_factor = schedule[i].factor;
		cur_start = schedule[i].start;
		cur_t = schedule[i].t;
		cur_p = schedule[i].p;
		isAvailable = 1;

		// 퇴사 이후라면
		if (cur_start + cur_t - 1 > n)
		{
			// 상담 불가능
			isAvailable = 0;
		}

		for (int j = cur_start; j < cur_start + cur_t; j++)
		{
			// 이미 상담 예약되어 있다면
			if (isBooked[j])
			{
				// 상담 불가능
				isAvailable = 0;

				break;
			}
		}

		// 상담 가능하다면
		if (isAvailable)
		{
			for (int j = cur_start; j < cur_start + cur_t; j++)
			{
				// 상담 일정에 추가
				isBooked[j] = 1;
			}

			ans += cur_p;
		}
	}

	return;
}
*/

void backtrack(int cur_day, int cur_pay)
{
	float next_factor = 0;
	int next_start = 0;
	int next_t = 0;
	int next_p = 0;
	int isAvailable = 1;

	// printf("day = %d, pay = %d\n", cur_day, cur_pay);

	for (int i = cur_day + 1; i <= n; i++)
	{
		next_factor = schedule[i].factor;
		next_start = schedule[i].start;
		next_t = schedule[i].t;
		next_p = schedule[i].p;
		isAvailable = 1;
		
		// 퇴사 이후라면
		if (next_start + next_t - 1 > n)
		{
			// 상담 불가능
			isAvailable = 0;
		}

		for (int j = next_start; j < next_start + next_t; j++)
		{
			// 이미 상담 예약되어 있다면
			// if (isBooked[cur_day][j])
			if (isBooked[j])
			{
				// 상담 불가능
				isAvailable = 0;

				break;
			}
		}

		// 상담 가능하다면
		if (isAvailable)
		{
			for (int j = next_start; j < next_start + next_t; j++)
			{
				// 상담 일정에 추가
				// isBooked[i][j] = 1;
				isBooked[j] = 1;
			}

			if (cur_pay + next_p > ans)
			{
				ans = cur_pay + next_p;
			}

			// printf("day %d selected\n", i);

			// 상담 일정에 추가한 후 탐색
			backtrack(i, cur_pay + next_p);

			for (int j = next_start; j < next_start + next_t; j++)
			{
				// 상담 일정 복구
				// isBooked[i][j] = 0;
				isBooked[j] = 0;
			}
		}

		// printf("day %d not selected\n", i);

		// 상담 일정에 추가하지 않고 탐색
		backtrack(i, cur_pay);
	}

	return;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d %d", &schedule[i].t, &schedule[i].p);

		schedule[i].start = i;
	}

	calc_factor();

	// print_schedule();

	// greedy();

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
