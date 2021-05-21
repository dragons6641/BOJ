// KJO16506.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_L 6
#define MAX_OP 12
#define ANS_L 16
#define OP_L 4
#define REG_L 3
#define C_L 4
#define MAX_A 4

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>
#include <string.h>

using namespace std;

char op_list[MAX_OP][MAX_L + 1] = { "ADD", "SUB", "MOV", "AND", "OR", "NOT", "MULT", "LSFTL", "LSFTR", "ASFTR", "RL", "RR" };
char opc_list[MAX_OP][MAX_L + 1] = { "ADDC", "SUBC", "MOVC", "ANDC", "ORC", "NOTC", "MULTC", "LSFTLC", "LSFTRC", "ASFTRC", "RLC", "RRC" };
char bit_list[MAX_OP][OP_L + 1] = { "0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011" };
char a_list[MAX_A][MAX_L + 1] = { "MOV", "MOVC", "NOT", "NOTC" };

char ans[ANS_L + 1] = { '\0' };

void init()
{
	for (int i = 0; i <= ANS_L; i++)
	{
		ans[i] = '\0';
	}

	return;
}

void make_reg(int x, int start)
{
	for (int i = 0; i < REG_L; i++)
	{
		// printf("%d, %d\n", start + REG_L - i - 1, x % 2);

		if (x % 2)
		{
			ans[start + REG_L - i - 1] = '1';
		}
		else
		{
			ans[start + REG_L - i - 1] = '0';
		}
		
		x /= 2;
	}

	return;
}

void make_c(int x, int start)
{
	for (int i = 0; i < C_L; i++)
	{
		if (x % 2)
		{
			ans[start + C_L - i - 1] = '1';
		}
		else
		{
			ans[start + C_L - i - 1] = '0';
		}

		x /= 2;
	}

	return;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	int testcase = 0;

	scanf("%d", &testcase);

	for (int t = 1; t <= testcase; t++)
	{
		char opcode[MAX_L + 1] = { '\0' };
		char bit = '\0';

		int d = 0;
		int a = 0;
		int b = 0;
		int c = 0;
		// int isA = 1;

		init();

		scanf("%s", &opcode);

		// printf("opcode : %s\n", opcode);

		for (int i = 0; i < MAX_OP; i++)
		{
			// rB 사용
			if (strcmp(opcode, op_list[i]) == 0)
			{
				bit = '0';

				// 해당 opcode 넣어준다
				strncpy(ans, bit_list[i], sizeof(bit_list - 1));

				break;
			}

			// #C 사용
			else if (strcmp(opcode, opc_list[i]) == 0)
			{
				bit = '1';

				// 해당 opcode 넣어준다
				strncpy(ans, bit_list[i], sizeof(bit_list - 1));

				break;
			}
		}

		// printf("bit : %c\n", bit);

		ans[OP_L] = bit;
		ans[OP_L + 1] = '0';

		// printf("ans : %s\n", ans);

		// rD
		scanf("%d", &d);

		// printf("d = %d\n", d);

		// 2진수 변환
		make_reg(d, OP_L + 2);

		// printf("ans : %s\n", ans);

		/*
		for (int i = 0; i < MAX_A; i++)
		{
			// rA가 000인 경우
			if (strcmp(opcode, a_list[i]) == 0)
			{
				isA = 0;

				for (int j = 0; j < REG_L; j++)
				{
					ans[OP_L + REG_L + 2 + j] = '0';
				}

				break;
			}
		}

		// rA 사용
		if (isA)
		{

		}
		*/

		scanf("%d", &a);

		// printf("a = %d\n", a);

		// rA 사용
		make_reg(a, OP_L + REG_L + 2);

		// printf("bit = %c\n", bit);

		// rB 사용
		if (bit == '0')
		{
			scanf("%d", &b);

			// printf("b = %d\n", b);

			make_reg(b, OP_L + (REG_L * 2) + 2);

			ans[OP_L + (REG_L * 3) + 2] = '0';
		}

		// #C 사용
		else
		{
			scanf("%d", &c);

			// printf("c = %d\n", c);

			make_c(c, OP_L + (REG_L) * 2 + 2);
		}

		printf("%s\n", ans);

		/*
		for (int i = 0; i < ANS_L; i++)
		{
			printf("%c", ans[i]);
		}

		printf("\n");
		*/
	}

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
