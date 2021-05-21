// KJO15684.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 10
#define MAX_H 30
#define MAX_M ((MAX_N - 1) * (MAX_H))

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>
#include <cstring>
#include <algorithm>

using namespace std;

int n = 0;
int m = 0;
int h = 0;
int ans = -1;

typedef struct hor {
	int a = 0;
	int b = 0;
} HOR;

HOR hor_info[MAX_M + 3];
HOR copy_info[MAX_M + 3];

int hor_cnt[MAX_N + 1] = { 0 };

bool cmp(const HOR x, const HOR y)
{
	if (x.a < y.a)
	{
		return true;
	}
	else if (x.a == y.a)
	{
		return x.b < y.b;
	}
	else
	{
		return false;
	}
}

void print_info()
{
	printf("hor_list : \n");

	for (int i = 0; i < m + 3; i++)
	{
		printf("%d %d\n", hor_info[i].a, hor_info[i].b);
	}

	printf("\n");

	return;
}

void print_copy()
{
	printf("copy_list : \n");

	for (int i = 0; i < m + 3; i++)
	{
		printf("%d %d\n", copy_info[i].a, copy_info[i].b);
	}

	printf("\n");

	return;
}

void print_cnt()
{
	printf("hor_cnt : \n");

	for (int i = 1; i <= n; i++)
	{
		printf("%d %d\n", i, hor_cnt[i]);
	}

	printf("\n");

	return;
}

int chk_dst(int depth)
{
	int index = 0;
	// int cur_row = 0;
	int cur_col = 0;
	int cur_a = 0;
	int cur_b = 0;

	memcpy(copy_info, hor_info, sizeof(hor_info));

	sort(copy_info, copy_info + m + depth, cmp);

	// print_copy();

	// 세로선마다 체크
	for (int col = 1; col <= n; col++)
	{
		index = 0;
		cur_col = col;

		while (1)
		{
			if (index == m + depth)
			{
				break;
			}

			cur_a = copy_info[index].a;
			cur_b = copy_info[index].b;

			for (int row = 1; row <= h; row++)
			{
				// printf("a = %d, b = %d, row = %d, col = %d, index = %d\n", cur_a, cur_b, row, col, index);

				// cur_row = row;

				// row : 현재 위치, cur_a : 읽고 있는 가로줄의 위치
				// 아직 가로줄 위치까지 가지 못했을 때
				if (row < cur_a)
				{
					// 현재 위치에서 아래로 내려감
					continue;
				}
				// 읽고 있는 가로줄을 이미 지나왔을 때
				else if (row > cur_a)
				{
					// 다음 가로줄을 읽어야 함
					break;
				}
				// 현재 위치에 가로줄이 있을 때
				else
				{
					// 오른쪽으로 진행 가능할 때
					if (cur_b == cur_col)
					{
						cur_col += 1;
					}
					// 왼쪽으로 진행 가능할 때
					else if (cur_b + 1 == cur_col)
					{
						cur_col -= 1;
					}
					// 현재 세로줄에 그어진 가로줄이 없을 때
					else
					{
						continue;
					}
				}
			}

			// 다음 가로줄 읽기
			index += 1;
		}

		// printf("col = %d, cur_col = %d\n", col, cur_col);

		// 사다리 결과가 다르다면
		if (cur_col != col)
		{
			// 추가 가로줄 필요
			return 1;
		}
	}

	// 반복문을 정상적으로 빠져나오면 이미 완성
	return 0;
}

void greedy()
{
	int result = 0;

	for (int i = 1; i <= n; i++)
	{
		// 짝수개가 아니면
		if (hor_cnt[i] % 2)
		{
			result += 1;
		}
	}

	// 3보다 큰 경우
	if (result > 3)
	{
		ans = -1;
	}
	// 불가능한 경우
	else if (result == 0)
	{
		ans = -1;
	}
	// 정상적인 경우
	else
	{
		ans = result;
	}

	return;
}

void backtrack(int depth, int r, int c)
{
	int err = 0;
	int cur_a = 0;
	int cur_b = 0;
	int isAvailable = 1;

	// 3보다 크다면
	if (depth > 3)
	{
		// 돌아가자
		return;
	}
	// 더 이상 놓을 수 없다면
	else if (depth == 3)
	{
		// 정답이 없는 경우에만 체크
		if (ans == -1)
		{
			err = chk_dst(depth);

			/*
			printf("depth = %d, err = %d, (%d, %d)\n", depth, err, r, c);
			print_info();
			*/

			// 원하는 결과가 나왔을 경우
			if (!err)
			{
				/*
				printf("depth = %d, err = %d, (%d, %d)\n", depth, err, r, c);
				print_info();
				*/

				// 아직 정답이 없다면
				if (ans == -1)
				{
					// 정답으로 넣는다
					ans = depth;
				}
				// 이미 있던 정답보다 작으면
				else if (depth < ans)
				{
					// 정답으로 넣는다
					ans = depth;
				}
			}

			return;
		}
	}
	// 3보다 작지만 이미 답이 될 수 없다면
	else if ((ans != -1) && (depth >= ans))
	{
		// 돌아가자
		return;
	}
	// 새로 놓은 줄이 있다면
	else if (depth > 0)
	{
		err = chk_dst(depth);

		/*
		printf("depth = %d, err = %d, (%d, %d)\n", depth, err, r, c);
		print_info();
		*/

		// 원하는 결과가 나왔을 경우
		if (!err)
		{
			/*
			printf("depth = %d, err = %d, (%d, %d)\n", depth, err, r, c);
			print_info();
			*/

			// 아직 정답이 없다면
			if (ans == -1)
			{
				// 정답으로 넣는다
				ans = depth;
			}
			// 이미 있던 정답보다 작으면
			else if (depth < ans)
			{
				// 정답으로 넣는다
				ans = depth;
			}
		}
	}

	/*
	printf("depth = %d\n", depth);
	print_info();
	*/

	for (int row = 1; row <= h; row++)
	{
		for (int col = 1; col < n; col++)
		{
			// 이미 지나온 것 탐색 방지
			if (row < r)
			{
				break;
			}
			// 이미 지나온 것 탐색 방지
			else if ((row == r) && (col < c))
			{
				continue;
			}

			isAvailable = 1;

			for (int k = 0; k < m + depth; k++)
			{
				cur_a = hor_info[k].a;
				cur_b = hor_info[k].b;

				// printf("a = %d, b = %d, row = %d, col = %d, k = %d\n", cur_a, cur_b, row, col, k);

				// 이미 가로줄이 있으면
				if ((cur_a == row) && (cur_b == col))
				{
					// 불가능, 다른 곳 확인
					isAvailable = 0;

					break;
				}

				// 연속해서 놓는 자리라면
				else if ((cur_a == row) && ((cur_b - 1 == col) || (cur_b + 1 == col)))
				{
					// 불가능, 다른 곳 확인
					isAvailable = 0;

					break;
				}
			}

			// 가로줄을 놓을 수 있다면
			if (isAvailable)
			{
				// 줄 놓은 것 표시 해주고
				hor_info[m + depth].a = row;
				hor_info[m + depth].b = col;

				// 완전 탐색
				backtrack(depth + 1, row, col);

				// 줄 놓은 것 초기화
				hor_info[m + depth].a = 0;
				hor_info[m + depth].b = 0;
			}
		}
	}

	return;
}

int main()
{
	int err = 0;

    // std::cout << "Hello World!\n";

	scanf("%d %d %d", &n, &m, &h);

	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &hor_info[i].a, &hor_info[i].b);

		hor_cnt[hor_info[i].b] += 1;
	}

	/*
	print_info();
	print_cnt();
	*/

	err = chk_dst(0);

	// i번 세로선의 결과가 i번이 아닐 경우
	if (err)
	{
		// 필요한 가로선의 갯수 구하기
		// greedy();

		ans = -1;

		backtrack(0, 0, 0);
	}
	// 이미 원하는 결과가 나왔을 경우
	else
	{
		// 굳이 진행할 필요 없음
		ans = 0;
	}

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
