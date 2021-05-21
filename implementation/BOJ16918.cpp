// KJO16918.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_R 200
#define MAX_C 200
#define MAX_N 200
#define MAX_S 3
#define MAX_DIR 4

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>
#include <vector>

using namespace std;

// 입력 벡터
// '.' : 빈 공간, 'O' : 폭탄
vector < vector < char > > v;

// 시뮬레이션 벡터
// 0 : 빈 공간, 숫자 : 폭탄과 시간
vector < vector < int > > w;

// 4방향
// 상, 하, 좌, 우
int dr[MAX_DIR] = { -1, 1, 0, 0 };
int dc[MAX_DIR] = { 0, 0, -1, 1 };

void init(int rows, int cols)
{
	v.resize(rows);
	w.resize(rows);

	for (int r = 0; r < v.size(); r++)
	{
		v[r].resize(cols);
		w[r].resize(cols, -1);
	}

	return;
}

void print_v()
{
	printf("v : \n");

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

void print_w()
{
	printf("w : \n");

	for (int r = 0; r < w.size(); r++)
	{
		for (int c = 0; c < w[r].size(); c++)
		{
			printf("%d ", w[r][c]);
		}

		printf("\n");
	}

	return;
}

void print_ans()
{
	// 시뮬레이션 결과 반영 후 출력
	for (int r = 0; r < w.size(); r++)
	{
		for (int c = 0; c < w[r].size(); c++)
		{
			// 빈 공간이라면
			if (w[r][c] == -1)
			{
				// 빈 공간 출력
				printf(".");
			}
			// 폭탄이라면
			else
			{
				printf("O");
			}
		}

		printf("\n");
	}

	return;
}

int check(int i, int n, int r, int c)
{
	int next_r = r + dr[i];
	int next_c = c + dc[i];

	// 상, 하 체크
	if ((next_r < 0) || (next_r >= v.size()))
	{
		// 불가능
		return 0;
	}
	// 좌, 우 체크
	else if ((next_c < 0) || (next_c >= v[r].size()))
	{
		// 불가능
		return 0;
	}
	// 그 자리에 함께 터질 폭탄 있다면
	else if (n - w[next_r][next_c] == MAX_S)
	{
		// 일단 살려는 드릴게
		return 0;
	}

	// 나머지는 가능
	return 1;
}

void explode(int n)
{
	// printf("explode = %d\n", n);

	// 3초 지난 폭탄 폭발
	// 인접한 4방향 폭탄도 함께 폭발

	for (int r = 0; r < w.size(); r++)
	{
		for (int c = 0; c < w[r].size(); c++)
		{
			// 3초 된 폭탄 있다면
			if (n - w[r][c] == MAX_S)
			{
				// 4방향 확인
				for (int i = 0; i < MAX_DIR; i++)
				{
					int isPossible = check(i, n, r, c);

					// 폭발 가능하다면
					if (isPossible)
					{
						// 해당 인접 자리 폭발 후 빈 공간
						w[r + dr[i]][c + dc[i]] = -1;
					}
				}

				// 해당 자리도 폭발 후 빈 공간
				w[r][c] = -1;
			}
		}
	}

	return;
}

void install(int n)
{
	// printf("install = %d\n", n);

	// 폭탄 없는 모든 칸에 폭탄 설치
	// 즉 모든 칸이 폭탄!

	for (int r = 0; r < w.size(); r++)
	{
		for (int c = 0; c < w[r].size(); c++)
		{
			// 빈 공간이라면
			if (w[r][c] == -1)
			{
				// 폭탄 설치하고 시간 표시
				w[r][c] = n;
			}
		}
	}

	return;
}

void simulate(int n)
{
	// 2초부터 변화 발생
	for (int i = 2; i <= n; i++)
	{
		// 홀수 초에 폭발
		if (i % 2)
		{
			explode(i);
		}

		// 짝수 초에 설치
		else
		{
			install(i);
		}

		// print_w();
	}

	return;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	int rows = 0;
	int cols = 0;
	int n = 0;

	scanf("%d %d %d", &rows, &cols, &n);

	init(rows, cols);

	for (int r = 0; r < rows; r++)
	{
		getchar();

		for (int c = 0; c < cols; c++)
		{
			scanf("%c", &v[r][c]);

			// 폭탄이면
			if (v[r][c] == 'O')
			{
				// 설치 시간 표시
				w[r][c] = 0;
			}
		}

		// getchar();
	}

	// print_v();
	// print_w();

	// N초 후의 격자판까지 시뮬레이션
	simulate(n);

	// 정답 출력
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
