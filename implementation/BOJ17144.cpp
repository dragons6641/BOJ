// KJO17144.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_R 50
#define MAX_C 50
#define MAX_T 1000
#define MAX_DIR 4

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>
#include <vector>

using namespace std;

// 집 격자판
vector < vector < int > > v;

// 임시 저장 배열
vector < vector < int > > w;

// 4방향
// 상, 하, 좌, 우
int dr[MAX_DIR] = { -1, 1, 0, 0 };
int dc[MAX_DIR] = { 0, 0, -1, 1 };

// 입력값
int rows = 0;
int cols = 0;
int time = 0;

// 공기청정기 위치
int r1 = -1;
int r2 = -1;

void init_v()
{
	v.clear();
	v.resize(rows);

	for (int r = 0; r < v.size(); r++)
	{
		v[r].resize(cols, 0);
	}

	return;
}

void init_w()
{
	w.clear();
	w.resize(rows);

	for (int r = 0; r < w.size(); r++)
	{
		w[r].resize(cols, 0);
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
			printf("%d ", v[r][c]);
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

int check(int i, int r, int c)
{
	int next_r = r + dr[i];
	int next_c = c + dc[i];

	// 상, 하 확인
	if ((next_r < 0) || (next_r >= v.size()))
	{
		// 불가능
		return 0;
	}
	// 좌, 우 확인
	else if ((next_c < 0) || (next_c >= v[r].size()))
	{
		// 불가능
		return 0;
	}
	// 확산할 칸이 공기청정기일 경우
	else if (v[next_r][next_c] == -1)
	{
		// 불가능
		return 0;
	}

	// 나머지는 모두 가능
	return 1;
}

void diffuse()
{
	// 모든 칸 확인
	for (int r = 0; r < v.size(); r++)
	{
		for (int c = 0; c < v[r].size(); c++)
		{
			// 해당 칸에 미세먼지가 있다면 확산 가능
			if (v[r][c] > 0)
			{
				// 각 방향마다 같은 양 확산
				int diff = (int)(v[r][c] / 5);

				// 각 방향마다 체크
				for (int i = 0; i < MAX_DIR; i++)
				{
					int isPossible = check(i, r, c);

					// 확산 가능하다면
					if (isPossible)
					{
						// 더하는 것은 임시 벡터
						w[r + dr[i]][c + dc[i]] += diff;

						// 빼주는 것은 원래 벡터
						v[r][c] -= diff;
					}
				}
			}
		}
	}

	// 실제 확산 시작
	for (int r = 0; r < v.size(); r++)
	{
		for (int c = 0; c < v[r].size(); c++)
		{
			// 임시 벡터 값 더해줌
			v[r][c] += w[r][c];

			// 임시 벡터 초기화
			w[r][c] = 0;
		}
	}

	return;
}
// 상, row, 정방향
void operate_0(int sr, int er, int c)
{
	for (int r = sr; r < er; r++)
	{
		v[r][c] = v[r + 1][c];
	}

	v[er][c] = 0;

	return;
}

// 하, row, 역방향
void operate_1(int sr, int er, int c)
{
	for (int r = sr; r > er; r--)
	{
		v[r][c] = v[r - 1][c];
	}

	v[er][c] = 0;

	return;
}

// 좌, col, 정방향
void operate_2(int sc, int ec, int r)
{
	for (int c = sc; c < ec; c++)
	{
		v[r][c] = v[r][c + 1];
	}

	v[r][ec] = 0;

	return;
}

// 우, col, 역방향
void operate_3(int sc, int ec, int r)
{
	for (int c = sc; c > ec; c--)
	{
		v[r][c] = v[r][c - 1];
	}

	v[r][ec] = 0;

	return;
}

void operate()
{
	// 들어오는 것부터 땡겨줘야 한다!
	// 0, 1, 2, 3
	// 상, 하, 좌, 우

	// 윗칸 r1은 반시계 방향
	// 하, row
	operate_1(r1 - 1, 0, 0);
	// 좌, col
	operate_2(0, cols - 1, 0);
	// 상, row
	operate_0(0, r1, cols - 1);
	// 우, col
	operate_3(cols - 1, 1, r1);

	// 아랫칸 r2는 시계 방향
	// 상, row
	operate_0(r2 + 1, rows - 1, 0);
	// 좌, col
	operate_2(0, cols - 1, rows - 1);
	// 하, row
	operate_1(rows - 1, r2, cols - 1);
	// 우, col
	operate_3(cols - 1, 1, r2);

	return;
}

int make_ans()
{
	int result = 0;

	for (int r = 0; r < v.size(); r++)
	{
		for (int c = 0; c < v[r].size(); c++)
		{
			// 공기청정기와 빈 공간은 제외
			if (v[r][c] > 0)
			{
				result += v[r][c];
			}
		}
	}

	return result;
}

int simulate()
{
	// t초 동안
	for (int t = 1; t <= time; t++)
	{
		// printf("t = %d\n", t);

		// 1. 미세먼지 확산
		diffuse();

		// printf("diffuse!\n");
		// print_v();

		// 2. 공기청정기 작동
		operate();

		// printf("operate!\n");
		// print_v();
	}

	// 정답 계산
	int result = make_ans();

	return result;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	scanf("%d %d %d\n", &rows, &cols, &time);

	// printf("%d %d %d\n", rows, cols, t);

	init_v();
	init_w();

	for (int r = 0; r < v.size(); r++)
	{
		for (int c = 0; c < v[r].size(); c++)
		{
			scanf("%d", &v[r][c]);

			// 공기청정기 위치 표시
			if (v[r][c] == -1)
			{
				// 첫 번째 위치일 경우
				if (r1 == -1)
				{
					r1 = r;
				}
				// 두 번째 위치일 경우
				else
				{
					r2 = r;
				}
			}
		}
	}

	// printf("1 : (%d, 0), 2 : (%d, 0)\n", r1, r2);

	// print_v();
	// print_w();

	int ans = simulate();

	printf("%d\n", ans);

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
