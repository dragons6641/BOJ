// KJO3568.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

/*
#define _CRT_SECURE_NO_WARNINGS
#define MAX_L 120
#define MAX_CNT 3

#include "pch.h"
#include <iostream>

#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

// 입력 벡터
vector < vector < char > > vi;

// 출력 벡터
vector < vector < char > > vo;

// 공통 자료형 갯수 세기
vector < int > cnt;

// 개별 자료형 갯수 세기
vector < vector < int > > var;

// 입력 기본 변수형
char bi[MAX_L + 1] = { '\0' };

// 출력 기본 변수형
char bo[MAX_L + 1] = { '\0' };

void init_cnt()
{
	cnt.clear();
	cnt.resize(MAX_CNT, 0);

	// 숫자 세어준다
	// 공통 추가 변수형
	for (int i = strlen(bo); i < strlen(bi); i++)
	{
		// 참조
		if (bi[i] == '&')
		{
			cnt[0] += 1;
		}
		// 배열
		// 여는 괄호는 세고
		else if (bi[i] == '[')
		{
			cnt[1] += 1;
		}
		// 닫는 괄호는 세지 않는다
		else if (bi[i] == ']')
		{
			continue;
		}
		// 포인터
		else if (bi[i] == '*')
		{
			cnt[2] += 1;
		}
		// 공백 입력이면 세지 않는다
		else if (bi[i] == ' ')
		{
			continue;
		}
	}

	return;
}

void print_vi()
{
	printf("vi : \n");

	for (int r = 0; r < vi.size(); r++)
	{
		for (int c = 0; c < vi[r].size(); c++)
		{
			printf("%c", vi[r][c]);
		}

		printf("\n");
	}

	return;
}

void print_vo()
{
	printf("vo : \n");

	for (int r = 0; r < vo.size(); r++)
	{
		for (int c = 0; c < vo[r].size(); c++)
		{
			printf("%c", vo[r][c]);
		}

		printf("\n");
	}

	return;
}

void print_ans()
{
	// 변수 갯수만큼 출력
	for (int r = 0; r < var.size(); r++)
	{
		// 기본 변수형 출력
		for (int c = 0; c < strlen(bo); c++)
		{
			printf("%c", bo[c]);
		}

		// & 출력
		for (int c = 0; c < var[r][0]; c++)
		{
			printf("&");
		}
		// [] 출력
		for (int c = 0; c < var[r][0]; c++)
		{
			printf("&");
		}
		// & 출력
		for (int c = 0; c < var[r][0]; c++)
		{
			printf("&");
		}

		// 공백 출력
		printf(" ");
	}

	return;
}

// r번째 변수 출력 만들기
void count_var(int r)
{
	// 임시 벡터
	vector < int > tmp(MAX_CNT);

	tmp[0] = cnt[0];
	tmp[1] = cnt[1];
	tmp[2] = cnt[2];

	// 숫자 세어준다
	// 개별 추가 변수형
	for (int i = 0; i < vi[r].size(); i++)
	{
		// 참조
		if (vi[r][i] == '&')
		{
			tmp[0] += 1;
		}
		// 배열
		// 여는 괄호는 세고
		else if (vi[r][i] == '[')
		{
			tmp[1] += 1;
		}
		// 닫는 괄호는 세지 않는다
		else if (vi[r][i] == ']')
		{
			continue;
		}
		// 포인터
		else if (vi[r][i] == '*')
		{
			tmp[2] += 1;
		}
		// 공백 입력이면 세지 않는다
		else if (vi[r][i] == ' ')
		{
			continue;
		}
		else
		{
			vo[r].push_back(vi[r][i]);
		}
	}

	// printf("c : %d %d %d\n", cnt[0], cnt[1], cnt[2]);
	// printf("%d : %d %d %d\n", r, tmp[0], tmp[1], tmp[2]);

	var.push_back(tmp);

	return;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	// 기본 변수형 + 추가 변수형
	scanf("%s", &bi);

	// printf("%s\n", bi);

	int pos = strlen(bi);

	// 기본 변수형만 가져오자
	for (int i = 0; i < strlen(bi); i++)
	{
		// printf("%c\n", bi[i]);

		// 소문자
		if ((bi[i] >= 'a') && (bi[i] <= 'z'))
		{
			// printf("%c\n", bi[i]);

			continue;
		}
		// 대문자
		else if ((bi[i] >= 'A') && (bi[i] <= 'Z'))
		{
			// printf("%c\n", bi[i]);

			continue;
		}
		// 다른 문자가 있다면
		// 즉 추가 변수형이 있다면
		else
		{
			// 마지막 대소문자 위치 지정
			pos = i;

			break;
		}
	}

	strncpy(bo, bi, pos);

	// printf("%s, %d, %d\n", bo, pos, strlen(bo));

	// 공백 하나 무시
	getchar();

	// 변수들
	while (1)
	{
		// 버퍼
		// char tmp[MAX_L + 1] = { '\0' };

		int i = 0;
		int isFinished = 0;

		char c = '\0';

		vector < char > tmp(MAX_L + 1, '\0');

		// 한 변수
		while (1)
		{
			scanf("%c", &c);

			// 세미콜론 입력이면
			if (c == ';')
			{
				// 입력 끝
				isFinished = 1;

				break;
			}
			// 컴마 입력이면
			else if (c == ',')
			{
				// 공백 입력까지 무시
				getchar();

				break;
			}
			// 일반 입력이면
			else
			{
				// 인정
				tmp[i] = c;
			}

			i += 1;
		}

		// 변수 선언 하나를 입력 벡터에 추가
		vi.push_back(tmp);

		// 입력 종료
		if (isFinished)
		{
			break;
		}
	}

	// 변수 길이만큼 출력 문자열 생성
	vo.resize(vi.size());

	// print_vi();

	// 공통 자료형 변수 세기
	init_cnt();

	// 변수 하나하나마다
	for (int r = 0; r < vi.size(); r++)
	{
		count_var(r);
	}

	// print_vo();
	print_ans();

	return 0;
}
*/

// 출처는 아래에
// 일단 제출하고 나중에 공부하자!
#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(void) {
	string str;
	string strt = "";
	string tmp = "";
	string value = "";
	int flag = 1;

	getline(cin, str);
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ' ' && flag) {
			strt = tmp;
			tmp = "";
			flag = 0;
		}
		else if (str[i] == ',' || str[i] == ';') {
			cout << strt;
			for (int j = tmp.size() - 1; j >= 0; j--) {
				if (tmp[j] == '[') printf("]");
				else if (tmp[j] == ']') printf("[");
				else printf("%c", tmp[j]);
			}
			cout << " " << value << ';' << endl;
			value = "";
			tmp = "";
		}
		else if (!flag && ((str[i] <= 'z' && str[i] >= 'a') || ('A' <= str[i] && str[i] <= 'Z'))) {
			value += str[i];
		}
		else if (str[i] != ' ') {
			tmp += str[i];
		}
	}
	return 0;
}
// [출처] BOJ 3568. iSharp - 구현 | 작성자 1ilsang
// http://blog.naver.com/PostView.nhn?blogId=1ilsang&logNo=221436875424&categoryNo=0&parentCategoryNo=0&viewDate=&currentPage=1&postListTopCurrentPage=1&from=postView\

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
