// KJO2290.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_S 10
#define MAX_L 10
#define MAX_INFO 7
#define MAX_NUM 10

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>
#include <vector>
#include <cstring>

using namespace std;

// 입력 숫자
char tmp[MAX_L + 1] = { '\0' };

// 길이
int s = 0;

// 출력 벡터
vector < vector < char > > v;

// 정보 배열
// 0, 1, 2, 3, 4, 5, 6
int info[MAX_NUM][MAX_INFO] = {
{1, 1, 1, 0, 1, 1, 1}, // 0
{1, 0, 1, 0, 0, 0, 0}, // 1
{1, 1, 0, 1, 1, 1, 0}, // 2
{1, 1, 1, 1, 0, 1, 0}, // 3
{1, 0, 1, 1, 0, 0, 1}, // 4
{0, 1, 1, 1, 0, 1, 1}, // 5
{0, 1, 1, 1, 1, 1, 1}, // 6
{1, 1, 1, 0, 0, 0, 0}, // 7
{1, 1, 1, 1, 1, 1, 1}, // 8
{1, 1, 1, 1, 0, 1, 1}, // 9
};

int calc_r(int i, int j)
{
	int result = 0;

	if (j == 1)
	{
		result = 0;
	}
	else if ((j == 0) || (j == 6))
	{
		result = 1;
	}
	else if (j == 3)
	{
		result = s + 1;
	}
	else if ((j == 2) || (j == 4))
	{
		result = s + 2;
	}
	else if (j == 5)
	{
		result = 2 * (s + 1);
	}

	return result;
}

int calc_c(int i, int j)
{
	int result = 0;

	if ((j == 4) || (j == 6))
	{
		result = i * (s + 3);
	}
	else if ((j == 1) || (j == 3) || (j == 5))
	{
		result = i * (s + 3) + 1;
	}
	else if ((j == 0) || (j == 2))
	{
		result = i * (s + 3) + (s + 1);
	}

	return result;
}

void lcd_test()
{
	// i : 한 개의 숫자
	for (int i = 0; i < strlen(tmp); i++)
	{
		// j : 한 개의 lcd판
		for (int j = 0; j < MAX_INFO; j++)
		{
			int cur_info = info[(int)(tmp[i] - '0')][j];

			// 해당 lcd 켜야 한다면
			if (cur_info)
			{
				int start_r = calc_r(i, j);
				int start_c = calc_c(i, j);

				// 홀수일 경우 가로
				if (j % 2)
				{
					// col이 바뀐다
					for (int c = start_c; c < start_c + s; c++)
					{
						v[start_r][c] = '-';
					}
				}
				// 짝수일 경우 세로
				else
				{
					// row가 바뀐다
					for (int r = start_r; r < start_r + s; r++)
					{
						v[r][start_c] = '|';
					}
				}
			}
		}
	}

	return;
}

void print_ans()
{
	for (int r = 0; r < v.size(); r++)
	{
		for (int c = 0; c < v[r].size(); c++)
		{
			printf("%c", v[r][c]);
		}

		printf("\n");
	}

	return;
}

void init(int l)
{
	// 세로는 2s + 3
	v.resize((2 * s) + 3);

	for (int r = 0; r < v.size(); r++)
	{
		// 가로는 (s + 3) * l
		// 공백으로 초기화
		// 숫자 사이에 공백 한 칸!
		v[r].resize((s + 3) * l, ' ');
	}

	return;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	scanf("%d %s", &s, &tmp);

	// printf("%d %s\n", s, tmp);

	init(strlen(tmp));

	lcd_test();

	print_ans();

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
