// KJO14888.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 11
#define MAX_A 100
#define OPERATORS 4
#define MAX_ANS 1000000000
#define MIN_ANS -1000000000
#define START_POS 1

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>

int n = 0;
int adds = 0;
int subs = 0;
int muls = 0;
int divs = 0;
int max = MIN_ANS;
int min = MAX_ANS;

int number_list[MAX_N + 1] = { 0 };

void print_number()
{
	printf("number_list : ");

	for (int i = 1; i <= n; i++)
	{
		printf("%d ", number_list[i]);
	}

	printf("\n");

	return;
}

void print_operator()
{
	printf("operators : %d %d %d %d\n", adds, subs, muls, divs);

	return;
}

void backtrack(int depth, int value)
{
	/*
	printf("depth = %d, value = %d\n", depth, value);
	print_operator();
	*/

	// 모든 연산자 사용
	if (depth == n)
	{
		if (value > max)
		{
			max = value;
		}

		if (value < min)
		{
			min = value;
		}

		return;
	}

	// 덧셈
	if (adds > 0)
	{
		adds -= 1;

		backtrack(depth + 1, value + number_list[depth + 1]);

		adds += 1;
	}
	// 뺄셈
	if (subs > 0)
	{
		subs -= 1;

		backtrack(depth + 1, value - number_list[depth + 1]);

		subs += 1;
	}
	// 곱셈
	if (muls > 0)
	{
		muls -= 1;

		backtrack(depth + 1, value * number_list[depth + 1]);

		muls += 1;
	}
	// 나눗셈
	if (divs > 0)
	{
		divs -= 1;

		backtrack(depth + 1, value / number_list[depth + 1]);

		divs += 1;
	}

	return;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &number_list[i]);
	}

	scanf("%d %d %d %d", &adds, &subs, &muls, &divs);

	/*
	print_number();
	print_operator();
	*/

	backtrack(START_POS, number_list[START_POS]);

	printf("%d\n%d\n", max, min);

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
