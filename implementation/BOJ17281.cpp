// KJO17281.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 50
#define MAX_M 9
#define MAX_OUTS 3
#define MAX_BASES 3

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>
#include <vector>

using namespace std;

// 입력 벡터
vector < vector < int > > v;

// 타순 벡터
// 1번부터 9번 선수까지의 타순
vector < int > w(MAX_M + 1, 0);

// 사용한 타순 번호
vector < int > isVisited(MAX_M + 1, 0);

// 1루부터 3루까지
// 맨 첫칸은 점수
vector < int > base(MAX_BASES + 1, 0);

// 최대 점수
int ans = 0;

// 현재 점수
int score = 0;

int n = 0;

void init_v()
{
	v.clear();
	// 1회부터 n회
	v.resize(n + 1);

	for (int r = 0; r < v.size(); r++)
	{
		// 1번부터 9번
		v[r].resize(MAX_M + 1, 0);
	}

	return;
}

void init_base()
{
	base.clear();
	base.resize(MAX_BASES + 1, 0);

	return;
}

void print_v()
{
	printf("v : \n");

	for (int r = 1; r < v.size(); r++)
	{
		for (int c = 1; c < v[r].size(); c++)
		{
			printf("%d ", v[r][c]);
		}

		printf("\n");
	}

	return;
}

void print_w()
{
	printf("w : ");

	for (int i = 1; i < w.size(); i++)
	{
		printf("%d ", w[i]);
	}

	printf("\n");

	return;
}

void print_isVisited()
{
	printf("isVisited : ");

	for (int i = 1; i < isVisited.size(); i++)
	{
		printf("%d ", isVisited[i]);
	}

	printf("\n");

	return;
}

// i번째 이닝에서 j번째 타자의 타격 결과
int simulate(int i, int j)
{
	int cur = v[i][isVisited[j]];

	// printf("cur = %d\n", cur);

	// 안타
	if (cur == 1)
	{
		// 3루주자 홈으로
		base[0] += base[3];
		// 2루주자 3루로
		base[3] = base[2];
		// 1루주자 2루로
		base[2] = base[1];
		// 타자 1루로
		base[1] = 1;

		return 0;
	}
	// 2루타
	else if (cur == 2)
	{
		// 3루주자 홈으로
		base[0] += base[3];
		// 2루주자 홈으로
		base[0] += base[2];
		// 1루주자 3루로
		base[3] = base[1];
		base[1] = 0;
		// 타자 2루로
		base[2] = 1;

		return 0;
	}
	// 3루타
	else if (cur == 3)
	{
		// 3루주자 홈으로
		base[0] += base[3];
		// 2루주자 홈으로
		base[0] += base[2];
		base[2] = 0;
		// 1루주자 홈으로
		base[0] += base[1];
		base[1] = 0;
		// 타자 3루로
		base[3] = 1;

		return 0;
	}
	// 홈런
	else if (cur == 4)
	{
		// 3루주자 홈으로
		base[0] += base[3];
		base[3] = 0;
		// 2루주자 홈으로
		base[0] += base[2];
		base[2] = 0;
		// 1루주자 홈으로
		base[0] += base[1];
		base[1] = 0;
		// 타자 홈으로
		base[0] += 1;

		return 0;
	}
	// 아웃
	else if (cur == 0)
	{
		// 주자 이동 없음
		// 아웃카운트 증가
		return 1;
	}
	
	// error
	return -1;
}

void make_ans()
{
	int result = 0;
	// 타순
	int j = 0;

	// n회동안 시뮬레이션
	for (int i = 1; i <= n; i++)
	{
		// 아웃카운트
		int outs = 0;

		// 주자 초기화
		init_base();

		// 1번 타순부터 9번 타순까지 하려면 isVisited!
		while (true)
		{
			// 다음 타순으로
			j += 1;

			// 9번 타자 다음은 1번 타자
			if (j == 10)
			{
				j = 1;
			}

			// 해당 타자 결과 시뮬레이션
			outs += simulate(i, j);

			// printf("outs = %d\n", outs);

			// 3번 아웃이면
			if (outs == MAX_OUTS)
			{
				// printf("i = %d, isVisited[j] = %d\n", i, isVisited[j]);

				// 이닝 점수 저장
				score += base[0];

				// 다음 이닝으로
				break;
			}
		}
	}

	return;
}

void backtrack(int cur)
{
	// printf("cur = %d\n", cur);

	// 종료 조건
	// 9번 선수까지 타순 모두 정했으면
	if (cur > MAX_M)
	{
		// 현재 점수 초기화
		score = 0;

		// 시뮬레이션
		make_ans();

		// print_w();
		// print_isVisited();

		// printf("score = %d, ans = %d\n", base[0], ans);

		// 정답 갱신
		if (score > ans)
		{
			// print_w();
			// print_isVisited();

			ans = score;
		}

		// 더 할 필요 없다
		return;
	}

	// 해당 선수에게 타순 배정
	for (int i = 1; i <= MAX_M; i++)
	{
		// 단, 4번은 제외
		if (i == 4)
		{
			continue;
		}
		// 해당 타순이 남아있다면
		else if (!isVisited[i])
		{
			// 타순 배정 후
			isVisited[i] = cur;
			w[cur] = i;

			// 다음 선수 타순 배정
			backtrack(cur + 1);

			// 원래대로
			isVisited[i] = 0;
			w[cur] = 0;
		}
	}

	return;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	scanf("%d", &n);

	init_v();

	for (int r = 1; r < v.size(); r++)
	{
		for (int c = 1; c < v[r].size(); c++)
		{
			scanf("%d", &v[r][c]);
		}
	}

	// print_v();
	// print_w();
	// print_isVisited();

	// 1번 선수는 4번 타자로 고정
	isVisited[4] = 1;
	w[1] = 4;

	// 다음 선수부터 완전탐색으로 타순 결정
	backtrack(2);

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
