// KJO13458.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 1000000
#define MAX_A 1000000
#define MAX_B 1000000
#define MAX_C 1000000
#define ARRS 10

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>
#include <queue>

using namespace std;

int n = 0;
int b = 0;
int c = 0;
int tmp = 0;
// int arr_idx = 0;

queue<int> q;

long long solve()
{
	long long result = 0;
	int cur_a = 0;

	while (!(q.empty()))
	{
		cur_a = q.front();
		q.pop();

		cur_a -= b;

		// printf("cur_a = %d\n", cur_a);

		result += 1;

		// 총감독관으로 충분할 경우
		if (cur_a <= 0)
		{
			
		}
		// 부감독관이 필요할 경우
		else
		{
			// 나누어 떨어질 경우
			if ((cur_a % c) == 0)
			{
				result += (cur_a / c);
			}
			// 나누어 떨어지지 않을 경우
			else
			{
				result += ((int)(cur_a / c) + 1);
			}
		}
	}

	return result;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	long long ans = 0;

	// int a[MAX_N] = { 0 };

	/*
	int a0[MAX_N / 10] = { 0 };
	int a1[MAX_N / 10] = { 0 };
	int a2[MAX_N / 10] = { 0 };
	int a3[MAX_N / 10] = { 0 };
	int a4[MAX_N / 10] = { 0 };
	int a5[MAX_N / 10] = { 0 };
	int a6[MAX_N / 10] = { 0 };
	int a7[MAX_N / 10] = { 0 };
	int a8[MAX_N / 10] = { 0 };
	int a9[MAX_N / 10] = { 0 };
	*/

	/*
	int a[ARRS][MAX_N / ARRS] = { 0 };
	*/

	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &tmp);

		q.push(tmp);
	}

	/*
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &tmp);

		if ((i % ARRS) == 0)
		{
			a0[(int)(i / ARRS)] = tmp;
		}
		else if ((i % ARRS) == 1)
		{
			a1[(int)(i / ARRS)] = tmp;
		}
		else if ((i % ARRS) == 2)
		{
			a2[(int)(i / ARRS)] = tmp;
		}
		else if ((i % ARRS) == 3)
		{
			a3[(int)(i / ARRS)] = tmp;
		}
		else if ((i % ARRS) == 4)
		{
			a4[(int)(i / ARRS)] = tmp;
		}
		else if ((i % ARRS) == 5)
		{
			a5[(int)(i / ARRS)] = tmp;
		}
		else if ((i % ARRS) == 6)
		{
			a6[(int)(i / ARRS)] = tmp;
		}
		else if ((i % ARRS) == 7)
		{
			a7[(int)(i / ARRS)] = tmp;
		}
		else if ((i % ARRS) == 8)
		{
			a8[(int)(i / ARRS)] = tmp;
		}
		else if ((i % ARRS) == 9)
		{
			a9[(int)(i / ARRS)] = tmp;
		}

		// scanf("%d", &a[i % ARRS][(int)(i / ARRS)]);
	}
	*/

	scanf("%d %d", &b, &c);

	/*
	for (int i = 0; i < n; i++)
	{
		tmp = q.front();
		q.pop();

		printf("%d ", tmp);
	}

	printf("\n");
	*/

	/*
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < ARRS; j++)
		{
			if ((i % ARRS) == 0)
			{
				tmp = a0[(int)(i / ARRS)];
			}
			else if ((i % ARRS) == 1)
			{
				tmp = a1[(int)(i / ARRS)];
			}
			else if ((i % ARRS) == 2)
			{
				tmp = a2[(int)(i / ARRS)];
			}
			else if ((i % ARRS) == 3)
			{
				tmp = a3[(int)(i / ARRS)];
			}
			else if ((i % ARRS) == 4)
			{
				tmp = a4[(int)(i / ARRS)];
			}
			else if ((i % ARRS) == 5)
			{
				tmp = a5[(int)(i / ARRS)];
			}
			else if ((i % ARRS) == 6)
			{
				tmp = a6[(int)(i / ARRS)];
			}
			else if ((i % ARRS) == 7)
			{
				tmp = a7[(int)(i / ARRS)];
			}
			else if ((i % ARRS) == 8)
			{
				tmp = a8[(int)(i / ARRS)];
			}
			else if ((i % ARRS) == 9)
			{
				tmp = a9[(int)(i / ARRS)];
			}
		}

		printf("%d ", tmp);

		// printf("%d ", a[i % ARRS][(int)(i / ARRS)]);
	}

	printf("\n");
	*/

	// printf("n = %d, b = %d, c = %d\n", n, b, c);

	ans = solve();

	printf("%lld", ans);

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
