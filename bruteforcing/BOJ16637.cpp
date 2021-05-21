// KJO16637.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 19

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>
#include <vector>
#include <limits.h>

using namespace std;

// 숫자 벡터
vector < int > d;

// 연산자 벡터
vector < char > c;

// 방문 벡터
vector < int > isVisited;

// 임시 숫자 벡터
vector < int > dd;

// 임시 연산자 벡터
vector < char > cc;

// 정답
int ans = INT_MIN;

void init_v(int n)
{
	d.clear();
	c.clear();
	isVisited.clear();

	// d는 올림
	d.resize((n + 1) / 2);
	// c는 내림
	c.resize((n - 1) / 2);
	// isVisited는 내림
	isVisited.resize((n - 1) / 2);

	return;
}

void init_vv()
{
	dd.clear();
	cc.clear();

	// 벡터 복사
	dd.assign(d.begin(), d.end());
	cc.assign(c.begin(), c.end());

	return;
}

void print_d()
{
	printf("d : ");

	for (int i = 0; i < d.size(); i++)
	{
		printf("%d ", d[i]);
	}

	printf("\n");

	return;
}

void print_c()
{
	printf("c : ");

	for (int i = 0; i < c.size(); i++)
	{
		printf("%c ", c[i]);
	}

	printf("\n");

	return;
}

void print_dd()
{
	printf("dd : ");

	for (int i = 0; i < dd.size(); i++)
	{
		printf("%d ", dd[i]);
	}

	printf("\n");

	return;
}

void print_cc()
{
	printf("cc : ");

	for (int i = 0; i < cc.size(); i++)
	{
		printf("%c ", cc[i]);
	}

	printf("\n");

	return;
}

void print_isVisited()
{
	printf("isVisited : ");

	for (int i = 0; i < isVisited.size(); i++)
	{
		printf("%d ", isVisited[i]);
	}

	printf("\n");

	return;
}

void calculate(int i)
{
	// printf("i = %d, (%d %c %d)\n", i, dd[i], cc[i], dd[i + 1]);

	// 덧셈
	if (cc[i] == '+')
	{
		dd[i] += dd[i + 1];
	}
	// 뺄셈
	else if (cc[i] == '-')
	{
		dd[i] -= dd[i + 1];
	}
	// 곱셈
	else if (cc[i] == '*')
	{
		dd[i] *= dd[i + 1];
	}

	// 삭제
	dd.erase(dd.begin() + (i + 1));
	cc.erase(cc.begin() + i);

	return;
}

void make_ans()
{
	// 초기화
	init_vv();

	int i = 0;
	int j = 0;

	// printf("i = %d\n", i);

	// 괄호 있는 것 연산
	while (true)
	{
		// 괄호 있다면
		if (isVisited[j])
		{
			// 연산
			calculate(i);

			// printf("i = %d\n", i);
			// print_dd();
			// print_cc();
		}
		// 괄호 없다면
		else
		{
			// 다음 연산으로
			i += 1;
		}

		// 벡터 인덱스 초과하면
		if (i == cc.size())
		{
			break;
		}

		j += 1;
	}

	i = 0;

	// 괄호 없는 것 연산
	while (true)
	{
		// 연산
		calculate(0);

		// printf("i = %d\n", i);
		// print_dd();
		// print_cc();

		// 벡터 인덱스 초과하면
		if (cc.empty())
		{
			break;
		}
	}

	// printf("cur = %d, ans = %d\n", dd[0], ans);

	// 최댓값 찾으면 갱신
	if (dd[0] > ans)
	{
		ans = dd[0];
	}

	return;
}

void backtrack(int cur)
{
	// printf("cur = %d\n", cur);
	// print_isVisited();

	// 마지막까지 배정했다면
	if (cur == isVisited.size())
	{
		// print_isVisited();

		// 연산
		make_ans();
	
		// 더 이상 하면 안된다
		return;
	}

	// 첫 번째는 예외처리
	if (cur == 0)
	{
		// 괄호 X
		isVisited[cur] = 0;
		backtrack(cur + 1);

		// 괄호 O
		isVisited[cur] = 1;
		backtrack(cur + 1);
	}
	// 일반적인 경우
	else
	{
		// 다음 괄호 배정은 이전 연산자에 괄호 있냐 없냐에 따라 결정
		// 이전 연산자에 괄호 있다면
		if (isVisited[cur - 1])
		{
			// 괄호 넣을 수 없다
			// 괄호 X
			isVisited[cur] = 0;
			backtrack(cur + 1);
		}
		// 이전 연산자에 괄호 없다면
		else
		{
			// 두 경우 모두 가능
			// 괄호 X
			isVisited[cur] = 0;
			backtrack(cur + 1);

			// 괄호 O
			isVisited[cur] = 1;
			backtrack(cur + 1);
		}
	}

	return;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	int n = 0;
	int d_tmp = 0;
	char c_tmp = '\0';

	scanf("%d", &n);

	init_v(n);

	for (int i = 1; i <= n; i++)
	{
		// 숫자 입력
		if (i % 2)
		{
			scanf("%d", &d_tmp);

			d[(i - 1) / 2] = d_tmp;
		}
		// 연산자 입력
		else
		{
			scanf("%c", &c_tmp);

			c[(i / 2) - 1] = c_tmp;
		}
	}

	// print_d();
	// print_c();
	// print_isVisited();

	// 연산자 없을 경우 예외처리
	if (n == 1)
	{
		ans = d[0];
	}
	// 연산자 하나일 경우도 예외처리
	else if (n == 3)
	{
		init_vv();

		calculate(0);

		ans = dd[0];
	}
	// 일반적인 경우
	else
	{
		backtrack(0);
	}

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
