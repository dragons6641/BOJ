// KJO16939.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_R 2
#define MAX_C 2
#define MAX_S 6
#define MAX_N (MAX_R * MAX_C * MAX_S)

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>
#include <vector>

using namespace std;

// 큐브 벡터
vector < int > v(MAX_N, 0);

// 복사 벡터
vector < int > w(MAX_N, 0);

void print_v()
{
	printf("v : ");

	for (int i = 0; i < v.size(); i++)
	{
		printf("%d ", v[i]);
	}

	printf("\n");

	return;
}

int check()
{
	for (int i = 0; i < MAX_S; i++)
	{
		for (int j = 1; j < (MAX_R * MAX_C); j++)
		{
			int idx = i * (MAX_R * MAX_C) + j;

			// 한 면에서 하나라도 색깔이 다르면
			if (w[idx] != w[idx - 1])
			{
				// 풀지 못한다
				return 0;
			}
		}
	}

	// 반복문을 빠져나왔다면 풀었다!
	return 1;
}

// 1번
int turn_r0d0()
{
	int result = 0;

	// 벡터 복사
	w.clear();
	w.assign(v.begin(), v.end());

	int tmp0 = w[20];
	int tmp1 = w[21];

	w[20] = w[16];
	w[21] = w[17];

	w[16] = w[4];
	w[17] = w[5];

	w[4] = w[12];
	w[5] = w[13];

	w[12] = tmp0;
	w[13] = tmp1;

	result = check();

	return result;
}

// 2번
int turn_r0d1()
{
	int result = 0;

	// 벡터 복사
	w.clear();
	w.assign(v.begin(), v.end());

	int tmp0 = w[12];
	int tmp1 = w[13];

	w[12] = w[4];
	w[13] = w[5];

	w[4] = w[16];
	w[5] = w[17];

	w[16] = w[20];
	w[17] = w[21];

	w[20] = tmp0;
	w[21] = tmp1;

	result = check();

	return result;
}

// 3번
int turn_r1d0()
{
	int result = 0;

	// 벡터 복사
	w.clear();
	w.assign(v.begin(), v.end());

	int tmp0 = w[22];
	int tmp1 = w[23];

	w[22] = w[18];
	w[23] = w[19];

	w[18] = w[6];
	w[19] = w[7];

	w[6] = w[14];
	w[7] = w[15];

	w[14] = tmp0;
	w[15] = tmp1;

	result = check();

	return result;
}

// 4번
int turn_r1d1()
{
	int result = 0;

	// 벡터 복사
	w.clear();
	w.assign(v.begin(), v.end());

	int tmp0 = w[14];
	int tmp1 = w[15];

	w[14] = w[6];
	w[15] = w[7];

	w[6] = w[18];
	w[7] = w[19];

	w[18] = w[22];
	w[19] = w[23];

	w[22] = tmp0;
	w[23] = tmp1;

	result = check();

	return result;
}

// 5번
int turn_c0d0()
{
	int result = 0;

	// 벡터 복사
	w.clear();
	w.assign(v.begin(), v.end());

	int tmp0 = w[21];
	int tmp1 = w[23];

	w[21] = w[8];
	w[23] = w[10];

	w[8] = w[4];
	w[10] = w[6];

	w[4] = w[0];
	w[6] = w[2];

	w[0] = tmp0;
	w[2] = tmp1;

	result = check();

	return result;
}

// 6번
int turn_c0d1()
{
	int result = 0;

	// 벡터 복사
	w.clear();
	w.assign(v.begin(), v.end());

	int tmp0 = w[0];
	int tmp1 = w[2];

	w[0] = w[4];
	w[2] = w[6];

	w[4] = w[8];
	w[6] = w[10];

	w[8] = w[21];
	w[10] = w[23];

	w[21] = tmp0;
	w[23] = tmp1;

	result = check();

	return result;
}

// 7번
int turn_c1d0()
{
	int result = 0;

	// 벡터 복사
	w.clear();
	w.assign(v.begin(), v.end());

	int tmp0 = w[20];
	int tmp1 = w[22];

	w[20] = w[9];
	w[22] = w[11];

	w[9] = w[5];
	w[11] = w[7];

	w[5] = w[1];
	w[7] = w[3];

	w[1] = tmp0;
	w[3] = tmp1;

	result = check();

	return result;
}

// 8번
int turn_c1d1()
{
	int result = 0;

	// 벡터 복사
	w.clear();
	w.assign(v.begin(), v.end());

	int tmp0 = w[1];
	int tmp1 = w[3];

	w[1] = w[5];
	w[3] = w[7];

	w[5] = w[9];
	w[7] = w[11];

	w[9] = w[20];
	w[11] = w[22];

	w[20] = tmp0;
	w[22] = tmp1;

	result = check();

	return result;
}

// 9번
int turn_h0d0()
{
	int result = 0;

	// 벡터 복사
	w.clear();
	w.assign(v.begin(), v.end());

	int tmp0 = w[2];
	int tmp1 = w[3];

	w[2] = w[15];
	w[3] = w[13];

	w[15] = w[9];
	w[13] = w[8];

	w[9] = w[16];
	w[8] = w[18];

	w[16] = tmp0;
	w[18] = tmp1;

	result = check();

	return result;
}

// 10번
int turn_h0d1()
{
	int result = 0;

	// 벡터 복사
	w.clear();
	w.assign(v.begin(), v.end());

	int tmp0 = w[2];
	int tmp1 = w[3];

	w[2] = w[16];
	w[3] = w[18];

	w[16] = w[9];
	w[18] = w[8];

	w[9] = w[15];
	w[8] = w[13];

	w[15] = tmp0;
	w[13] = tmp1;

	result = check();

	return result;
}

// 11번
int turn_h1d0()
{
	int result = 0;

	// 벡터 복사
	w.clear();
	w.assign(v.begin(), v.end());

	int tmp0 = w[0];
	int tmp1 = w[1];

	w[0] = w[14];
	w[1] = w[12];

	w[14] = w[11];
	w[12] = w[10];

	w[11] = w[17];
	w[10] = w[19];

	w[17] = tmp0;
	w[19] = tmp1;

	result = check();

	return result;
}

// 12번
int turn_h1d1()
{
	int result = 0;

	// 벡터 복사
	w.clear();
	w.assign(v.begin(), v.end());

	int tmp0 = w[0];
	int tmp1 = w[1];

	w[0] = w[17];
	w[1] = w[19];

	w[17] = w[11];
	w[19] = w[10];

	w[11] = w[14];
	w[10] = w[12];

	w[14] = tmp0;
	w[12] = tmp1;

	result = check();

	return result;
}

void simulate()
{
	// d0 : 시계
	// d1 : 반시계

	int result = 0;

	// 1번
	result = turn_r0d0();

	// 가능하다면
	if (result)
	{
		// 1 출력
		printf("1\n");

		// 더 이상 볼 필요 없다
		return;
	}

	// 2번
	result = turn_r0d1();

	// 가능하다면
	if (result)
	{
		// 1 출력
		printf("1\n");

		// 더 이상 볼 필요 없다
		return;
	}

	// 3번
	result = turn_r1d0();

	// 가능하다면
	if (result)
	{
		// 1 출력
		printf("1\n");

		// 더 이상 볼 필요 없다
		return;
	}

	// 4번
	result = turn_r1d1();

	// 가능하다면
	if (result)
	{
		// 1 출력
		printf("1\n");

		// 더 이상 볼 필요 없다
		return;
	}

	// 5번
	result = turn_c0d0();

	// 가능하다면
	if (result)
	{
		// 1 출력
		printf("1\n");

		// 더 이상 볼 필요 없다
		return;
	}

	// 6번
	result = turn_c0d1();

	// 가능하다면
	if (result)
	{
		// 1 출력
		printf("1\n");

		// 더 이상 볼 필요 없다
		return;
	}

	// 7번
	result = turn_c1d0();

	// 가능하다면
	if (result)
	{
		// 1 출력
		printf("1\n");

		// 더 이상 볼 필요 없다
		return;
	}

	// 8번
	result = turn_c1d1();

	// 가능하다면
	if (result)
	{
		// 1 출력
		printf("1\n");

		// 더 이상 볼 필요 없다
		return;
	}

	// 9번
	result = turn_h0d0();

	// 가능하다면
	if (result)
	{
		// 1 출력
		printf("1\n");

		// 더 이상 볼 필요 없다
		return;
	}

	// 10번
	result = turn_h0d1();

	// 가능하다면
	if (result)
	{
		// 1 출력
		printf("1\n");

		// 더 이상 볼 필요 없다
		return;
	}

	// 11번
	result = turn_h1d0();

	// 가능하다면
	if (result)
	{
		// 1 출력
		printf("1\n");

		// 더 이상 볼 필요 없다
		return;
	}

	// 12번
	result = turn_h1d1();

	// 가능하다면
	if (result)
	{
		// 1 출력
		printf("1\n");

		// 더 이상 볼 필요 없다
		return;
	}

	// 12번 모두 실패했다면 불가능
	// 0 출력
	printf("0\n");

	return;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	for (int i = 0; i < v.size(); i++)
	{
		scanf("%d", &v[i]);
	}

	// print_v();

	simulate();

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
