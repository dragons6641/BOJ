// KJO17140.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_R 100
#define MAX_C 100
#define MAX_K 100
#define MAX_A 100
#define MAX_ANS 100
#define START_R 3
#define START_C 3

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>
#include <algorithm>

using namespace std;

typedef struct NODE
{
	// 해당 숫자 나온 횟수
	int m = 0;
	// 해당 숫자
	int n = 0;
}
node;

bool operator < (node a, node b)
{
	if (a.m == b.m)
	{
		return a.n < b.n;
	}
	else
	{
		return a.m < b.m;
	}
}

// 이차원 배열
// 0번째는 해당 행/열의 size 저장
int v[MAX_R + 1][MAX_C + 1];

// 입력값
int row = 0;
int col = 0;
int k = 0;

// 배열 크기는 따로 저장
// 크기까지 포함해서 돌아야 한다!
int row_size = START_R;
int col_size = START_C;

void init_v()
{
	for (int r = 0; r <= row_size; r++)
	{
		for (int c = 0; c <= col_size; c++)
		{
			if ((r == 0) && (c == 0))
			{
				v[r][c] = row_size * col_size;
			}
			else if (r == 0)
			{
				v[r][c] = row_size;
			}
			else if (c == 0)
			{
				v[r][c] = col_size;
			}
		}
	}

	return;
}

void print_v()
{
	printf("v : \n");

	for (int r = 0; r <= row_size; r++)
	{
		for (int c = 0; c <= col_size; c++)
		{
			printf("%d ", v[r][c]);
		}

		printf("\n");
	}

	return;
}

void r_op()
{
	// 행 우선 탐색
	for (int r = 1; r <= row_size; r++)
	{
		// 실제 배열에 적어줄 위치
		int j = 0;

		// 숫자 세고 저장할 배열
		node w[MAX_A + 1];

		for (int c = 1; c <= col_size; c++)
		{
			w[v[r][c]].m += 1;
			w[v[r][c]].n = v[r][c];
		}

		/*
		printf("not sorted : ");

		for (int i = 1; i <= MAX_A; i++)
		{
			printf("%d ", w[i].n);
		}

		printf("\n");
		*/

		// 1부터 100까지 나온 횟수별로 정렬
		sort(w + 1, w + MAX_A + 1);

		/*
		printf("sorted : ");

		for (int i = 1; i <= MAX_A; i++)
		{
			printf("%d ", w[i].n);
		}

		printf("\n");
		*/

		// 정렬된 배열 탐색하며 V 배열에 반영
		for (int i = 1; i <= MAX_A; i++)
		{
			// 해당 숫자가 하나 이상일 경우
			if (w[i].m > 0)
			{
				// 인덱스 하나 늘려주고
				j += 1;

				// 배열에 해당 숫자 적어준다
				v[r][j] = w[i].n;

				// 인덱스 하나 늘려주고
				j += 1;

				// 배열에 해당 숫자 나온 횟수 적어준다
				v[r][j] = w[i].m;

				// 열 크기 갱신
				if (j > col_size)
				{
					col_size = j;
				}

				// 인덱스 초과 방지
				if (j == MAX_C)
				{
					break;
				}
			}
		}

		// 크기 기록
		v[r][0] = j;

		// print_v();

		// 인덱스 초과 방지
		if (j == MAX_C)
		{
			break;
		}
	}

	// 크기 정리
	for (int r = 1; r <= row_size; r++)
	{
		for (int c = v[r][0] + 1; c <= col_size; c++)
		{
			v[r][c] = 0;
		}
	}

	v[0][0] = row_size * col_size;

	// print_v();

	return;
}

void c_op()
{
	// 열 우선 탐색
	for (int c = 1; c <= col_size; c++)
	{
		// 실제 배열에 적어줄 위치
		int j = 0;

		// 숫자 세고 저장할 배열
		node w[MAX_A + 1];

		for (int r = 1; r <= row_size; r++)
		{
			w[v[r][c]].m += 1;
			w[v[r][c]].n = v[r][c];
		}

		/*
		printf("not sorted : ");

		for (int i = 1; i <= MAX_A; i++)
		{
			printf("%d ", w[i].n);
		}

		printf("\n");
		*/

		// 1부터 100까지 나온 횟수별로 정렬
		sort(w + 1, w + MAX_A + 1);

		/*
		printf("sorted : ");

		for (int i = 1; i <= MAX_A; i++)
		{
			printf("%d ", w[i].n);
		}

		printf("\n");
		*/

		// 정렬된 배열 탐색하며 V 배열에 반영
		for (int i = 1; i <= MAX_A; i++)
		{
			// 해당 숫자가 하나 이상일 경우
			if (w[i].m > 0)
			{
				// 인덱스 하나 늘려주고
				j += 1;

				// 배열에 해당 숫자 적어준다
				v[j][c] = w[i].n;

				// 인덱스 하나 늘려주고
				j += 1;

				// 배열에 해당 숫자 나온 횟수 적어준다
				v[j][c] = w[i].m;

				// 열 크기 갱신
				if (j > row_size)
				{
					row_size = j;
				}

				// 인덱스 초과 방지
				if (j == MAX_C)
				{
					break;
				}
			}
		}

		// 크기 기록
		v[0][c] = j;

		// print_v();

		// 인덱스 초과 방지
		if (j == MAX_C)
		{
			break;
		}
	}

	// 크기 정리
	for (int c = 1; c <= col_size; c++)
	{
		for (int r = v[0][c] + 1; r <= row_size; r++)
		{
			v[r][c] = 0;
		}
	}

	v[0][0] = row_size * col_size;

	// print_v();

	return;
}

int simulate()
{
	int result = 0;

	while (true)
	{
		// 답일 경우
		if (v[row][col] == k)
		{
			// 그만
			break;
		}
		else if (result > MAX_ANS)
		{
			// 찾기 불가능
			result = -1;

			// 그만
			break;
		}

		// 행-열 크기 비교
		if (row_size >= col_size)
		{
			// R 연산
			r_op();
		}
		else
		{
			// C 연산
			c_op();
		}

		// print_v();

		// 답이 아닐 경우
		// 시간 1 증가 후 계속 수행
		result += 1;
	}

	return result;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	scanf("%d %d %d", &row, &col, &k);

	init_v();

	for (int r = 1; r <= row_size; r++)
	{
		for (int c = 1; c <= col_size; c++)
		{
			scanf("%d", &v[r][c]);
		}
	}

	// print_v();

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
