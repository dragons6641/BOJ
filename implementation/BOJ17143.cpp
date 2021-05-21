// KJO17143.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_R 100
#define MAX_C 100
#define MAX_M (MAX_R * MAX_C)

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>
#include <vector>

using namespace std;

typedef struct NODE
{
	// 속력
	int s = 0;
	// 이동 방향
	int d = 0;
	// 크기
	int z = 0;
}
node;

// 격자판
// 슬라이딩 윈도우
// 홀수번째
vector < vector < node > > v1;
// 짝수번째
vector < vector < node > > v2;

int rows = 0;
int cols = 0;
int m = 0;

void init_v()
{
	v1.clear();
	v2.clear();
	v1.resize(rows);
	v2.resize(rows);

	for (int r = 0; r < rows; r++)
	{
		v1[r].resize(cols);
		v2[r].resize(cols);
	}

	return;
}

void print_s1()
{
	printf("s1 : \n");

	for (int r = 0; r < v1.size(); r++)
	{
		for (int c = 0; c < v1[r].size(); c++)
		{
			printf("%d ", v1[r][c].s);
		}

		printf("\n");
	}

	return;
}

void print_s2()
{
	printf("s2 : \n");

	for (int r = 0; r < v2.size(); r++)
	{
		for (int c = 0; c < v2[r].size(); c++)
		{
			printf("%d ", v2[r][c].s);
		}

		printf("\n");
	}

	return;
}

void print_d1()
{
	printf("d1 : \n");

	for (int r = 0; r < v1.size(); r++)
	{
		for (int c = 0; c < v1[r].size(); c++)
		{
			printf("%d ", v1[r][c].d);
		}

		printf("\n");
	}

	return;
}

void print_d2()
{
	printf("d2 : \n");

	for (int r = 0; r < v2.size(); r++)
	{
		for (int c = 0; c < v2[r].size(); c++)
		{
			printf("%d ", v2[r][c].d);
		}

		printf("\n");
	}

	return;
}

void print_z1()
{
	printf("z1 : \n");

	for (int r = 0; r < v1.size(); r++)
	{
		for (int c = 0; c < v1[r].size(); c++)
		{
			printf("%d ", v1[r][c].z);
		}

		printf("\n");
	}

	return;
}

void print_z2()
{
	printf("z2 : \n");

	for (int r = 0; r < v2.size(); r++)
	{
		for (int c = 0; c < v2[r].size(); c++)
		{
			printf("%d ", v2[r][c].z);
		}

		printf("\n");
	}

	return;
}

int human(int c)
{
	int result = 0;

	// v1
	if (c % 2)
	{
		// 아래로 탐색하면서 물고기 찾기
		for (int r = 0; r < v1.size(); r++)
		{
			// 만약 상어가 있다면
			if (v1[r][c].z > 0)
			{
				// 상어 크기 기록
				result = v1[r][c].z;

				// 그 상어는 제거
				v1[r][c].s = 0;
				v1[r][c].d = 0;
				v1[r][c].z = 0;

				// 더 찾을 필요 없다
				break;
			}
		}
	}
	// v2
	else
	{
		// 아래로 탐색하면서 물고기 찾기
		for (int r = 0; r < v2.size(); r++)
		{
			// 만약 상어가 있다면
			if (v2[r][c].z > 0)
			{
				// 상어 크기 기록
				result = v2[r][c].z;

				// 그 상어는 제거
				v2[r][c].s = 0;
				v2[r][c].d = 0;
				v2[r][c].z = 0;

				// 더 찾을 필요 없다
				break;
			}
		}
	}

	// 잡은 경우에는 크기
	// 못 잡은 경우에는 0
	return result;
}

void move(int t, int r, int c, int s, int d, int z)
{
	int next_r = r;
	int next_c = c;
	int next_d = d;

	// 4방향
	// 1   2     3       4
	// 위 아래 오른쪽 왼쪽

	// 위나 아래일 경우
	if ((d == 1) || (d == 2))
	{
		// row만 변함
		// 속력만큼 이동
		for (int i = 0; i < s; i++)
		{
			// 위로 이동
			if (next_d == 1)
			{
				// 범위 체크
				if (next_r == 0)
				{
					// 방향 반대로
					next_d = 2;
					next_r += 1;
				}
				// 일반적인 경우
				else
				{
					// 방향 그대로
					next_r -= 1;
				}
			}
			// 아래로 이동
			else if (next_d == 2)
			{
				// 범위 체크
				if (next_r == rows - 1)
				{
					// 방향 반대로
					next_d = 1;
					next_r -= 1;
				}
				// 일반적인 경우
				else
				{
					// 방향 그대로
					next_r += 1;
				}
			}
		}
	}
	// 오른쪽이나 왼쪽일 경우
	else if ((d == 3) || (d == 4))
	{
		// col만 변함
		// 속력만큼 이동
		for (int i = 0; i < s; i++)
		{
			// 오른쪽으로 이동
			if (next_d == 3)
			{
				// 범위 체크
				if (next_c == cols - 1)
				{
					// 방향 반대로
					next_d = 4;
					next_c -= 1;
				}
				// 일반적인 경우
				else
				{
					// 방향 그대로
					next_c += 1;
				}
			}
			// 왼쪽으로 이동
			else if (next_d == 4)
			{
				// 범위 체크
				if (next_c == 0)
				{
					// 방향 반대로
					next_d = 3;
					next_c += 1;
				}
				// 일반적인 경우
				else
				{
					// 방향 그대로
					next_c -= 1;
				}
			}
		}
	}

	// 해당 위치로 상어 이동
	// v2 <- v1
	if (t % 2)
	{
		// 쓰기
		// 이미 있고 있는 놈이 나보다 크다면
		if (z < v2[next_r][next_c].z)
		{
			// 잡아먹힌다
			// 쓰면 안됨
		}
		// 아무도 없다면
		else
		{
			// 그냥 쓰면 됨
			v2[next_r][next_c].s = s;
			v2[next_r][next_c].d = next_d;
			v2[next_r][next_c].z = z;
		}

		// 지우기
		v1[r][c].s = 0;
		v1[r][c].d = 0;
		v1[r][c].z = 0;
	}
	// v1 <- v2
	else
	{
		// 쓰기
		// 이미 있고 있는 놈이 나보다 크다면
		if (z < v1[next_r][next_c].z)
		{
			// 잡아먹힌다
			// 쓰면 안됨
		}
		// 아무도 없다면
		else
		{
			// 그냥 쓰면 됨
			v1[next_r][next_c].s = s;
			v1[next_r][next_c].d = next_d;
			v1[next_r][next_c].z = z;
		}

		// 지우기
		v2[r][c].s = 0;
		v2[r][c].d = 0;
		v2[r][c].z = 0;
	}

	return;
}

void shark(int t)
{
	// v2 <- v1
	if (t % 2)
	{
		for (int r = 0; r < v1.size(); r++)
		{
			for (int c = 0; c < v1[r].size(); c++)
			{
				// 상어가 있을 경우
				if (v1[r][c].z > 0)
				{
					// 상어 이동
					move(t, r, c, v1[r][c].s, v1[r][c].d, v1[r][c].z);
				}
			}
		}
	}
	// v1 <- v2
	else
	{
		for (int r = 0; r < v2.size(); r++)
		{
			for (int c = 0; c < v2[r].size(); c++)
			{
				// 상어가 있을 경우
				if (v2[r][c].z > 0)
				{
					// 상어 이동
					move(t, r, c, v2[r][c].s, v2[r][c].d, v2[r][c].z);
				}
			}
		}
	}

	return;
}

int simluate()
{
	int result = 0;
	int c = -1;

	while (true)
	{
		// 낚시왕이 오른쪽으로 이동
		c += 1;

		// printf("c = %d\n", c);

		// 범위 초과했다면
		if (c == cols)
		{
			// 종료
			break;
		}

		// 해당 열의 상어 잡기
		result += human(c);

		// 전체 상어 이동 & 잡아먹기
		shark(c);

		/*
		if (c % 2)
		{
			print_z2();
		}
		else
		{
			print_z1();
		}
		*/
	}

	return result;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	scanf("%d %d %d", &rows, &cols, &m);

	// printf("%d %d %d\n", rows, cols, m);

	init_v();

	// printf("size : (%d * %d)\n", v.size(), v[0].size());

	// print_s();
	// print_d();
	// print_z();

	for (int i = 0; i < m; i++)
	{
		// 위치 먼저 받자
		int r = 0;
		int c = 0;

		scanf("%d %d", &r, &c);

		// printf("(%d, %d)\n", r, c);

		// 해당 위치 변환해서 정보 입력
		scanf("%d %d %d", &v2[r - 1][c - 1].s, &v2[r - 1][c - 1].d, &v2[r - 1][c - 1].z);
	}

	// print_s();
	// print_d();
	// print_z();

	int ans = simluate();

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
