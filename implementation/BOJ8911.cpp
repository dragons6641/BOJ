// KJO8911.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_L 500

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>

using namespace std;

// 12시 3시 6시 9시
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

// 명령 입력
char cmd[MAX_L + 1] = { '\0' };

int simulate()
{
	// 12시 3시 6시 9시
	// 0    1    2    3
	int dir = 0;
	int i = 0;
	int max_r = 0;
	int max_c = 0;
	int min_r = 0;
	int min_c = 0;
	int cur_r = 0;
	int cur_c = 0;
	int result = 0;

	while (1)
	{
		// 문자 하나 읽기
		char cur = cmd[i];

		// printf("dir : %d, (%d, %d)\n", dir, cur_r, cur_c);

		// 문자열 끝나면
		if (cur == '\0')
		{
			// 넓이 구하자
			result = (max_r - min_r) * (max_c - min_c);
			
			break;
		}

		// F : 한 눈금 앞으로
		else if (cur == 'F')
		{
			cur_r += dr[dir];
			cur_c += dc[dir];

			// 최댓값 최솟값 갱신
			if (cur_r > max_r)
			{
				max_r = cur_r;
			}
			else if (cur_r < min_r)
			{
				min_r = cur_r;
			}

			// 최댓값 최솟값 갱신
			if (cur_c > max_c)
			{
				max_c = cur_c;
			}
			else if (cur_c < min_c)
			{
				min_c = cur_c;
			}
		}

		// B : 한 눈금 뒤로
		else if (cur == 'B')
		{
			cur_r -= dr[dir];
			cur_c -= dc[dir];

			// 최댓값 최솟값 갱신
			if (cur_r > max_r)
			{
				max_r = cur_r;
			}
			else if (cur_r < min_r)
			{
				min_r = cur_r;
			}

			// 최댓값 최솟값 갱신
			if (cur_c > max_c)
			{
				max_c = cur_c;
			}
			else if (cur_c < min_c)
			{
				min_c = cur_c;
			}
		}

		// L : 왼쪽으로 90도 회전
		else if (cur == 'L')
		{
			dir -= 1;
			
			if (dir < 0)
			{
				dir += 4;
			}
		}

		// R : 오른쪽으로 90도 회전
		else if (cur == 'R')
		{
			dir += 1;

			if (dir > 3)
			{
				dir -= 4;
			}
		}

		i += 1;
	}

	return result;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	int testcase = 0;

	scanf("%d", &testcase);

	for (int t = 1; t <= testcase; t++)
	{
		int ans = 0;

		scanf("%s", &cmd);

		// printf("%s\n", cmd);

		ans = simulate();

		printf("%d\n", ans);
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
