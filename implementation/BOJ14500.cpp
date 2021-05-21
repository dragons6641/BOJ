// KJO14500.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 500
#define MAX_M 500

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>

// row
int n = 0;
// col
int m = 0;

int ans = 0;

int matrix[MAX_N][MAX_M] = { 0 };

void print_matrix()
{
	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < m; col++)
		{
			printf("%d ", matrix[row][col]);
		}

		printf("\n");
	}

	return;
}

// 세로 최대 4개
void row_4()
{
	int result = 0;

	for (int r = 0; r < n - 3; r++)
	{
		for (int c = 0; c < m; c++)
		{
			result = (matrix[r][c] + matrix[r + 1][c] + matrix[r + 2][c] + matrix[r + 3][c]);

			if (result > ans)
			{
				ans = result;
			}
		}
	}

	return;
}

// 가로 최대 4개
void col_4()
{
	int result = 0;

	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < m - 3; c++)
		{
			result = (matrix[r][c] + matrix[r][c + 1] + matrix[r][c + 2] + matrix[r][c + 3]);

			if (result > ans)
			{
				ans = result;
			}
		}
	}

	return;
}

// 세로 최대 3개
void row_3()
{
	int result = 0;

	for (int r = 0; r < n - 2; r++)
	{
		for (int c = 0; c < m; c++)
		{
			if (c > 0)
			{
				result = (matrix[r][c] + matrix[r + 1][c] + matrix[r + 2][c] + matrix[r][c - 1]);

				if (result > ans)
				{
					ans = result;
				}

				result = (matrix[r][c] + matrix[r + 1][c] + matrix[r + 2][c] + matrix[r + 1][c - 1]);

				if (result > ans)
				{
					ans = result;
				}

				result = (matrix[r][c] + matrix[r + 1][c] + matrix[r + 2][c] + matrix[r + 2][c - 1]);

				if (result > ans)
				{
					ans = result;
				}
			}
			
			if (c < m - 1)
			{
				result = (matrix[r][c] + matrix[r + 1][c] + matrix[r + 2][c] + matrix[r][c + 1]);

				if (result > ans)
				{
					ans = result;
				}

				result = (matrix[r][c] + matrix[r + 1][c] + matrix[r + 2][c] + matrix[r + 1][c + 1]);

				if (result > ans)
				{
					ans = result;
				}

				result = (matrix[r][c] + matrix[r + 1][c] + matrix[r + 2][c] + matrix[r + 2][c + 1]);

				if (result > ans)
				{
					ans = result;
				}
			}
		}
	}

	return;
}

// 가로 최대 3개
void col_3()
{
	int result = 0;

	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < m - 2; c++)
		{
			if (r > 0)
			{
				result = (matrix[r][c] + matrix[r][c + 1] + matrix[r][c + 2] + matrix[r - 1][c]);

				if (result > ans)
				{
					ans = result;
				}

				result = (matrix[r][c] + matrix[r][c + 1] + matrix[r][c + 2] + matrix[r - 1][c + 1]);

				if (result > ans)
				{
					ans = result;
				}

				result = (matrix[r][c] + matrix[r][c + 1] + matrix[r][c + 2] + matrix[r - 1][c + 2]);

				if (result > ans)
				{
					ans = result;
				}
			}

			if (r < n - 1)
			{
				result = (matrix[r][c] + matrix[r][c + 1] + matrix[r][c + 2] + matrix[r + 1][c]);

				if (result > ans)
				{
					ans = result;
				}

				result = (matrix[r][c] + matrix[r][c + 1] + matrix[r][c + 2] + matrix[r + 1][c + 1]);

				if (result > ans)
				{
					ans = result;
				}

				result = (matrix[r][c] + matrix[r][c + 1] + matrix[r][c + 2] + matrix[r + 1][c + 2]);

				if (result > ans)
				{
					ans = result;
				}
			}
		}
	}

	return;
}

// 세로 최대 2개
void row_2()
{
	int result = 0;

	for (int r = 0; r < n - 1; r++)
	{
		for (int c = 0; c < m; c++)
		{
			if (c > 0)
			{
				if (r > 0)
				{
					result = (matrix[r][c] + matrix[r + 1][c] + matrix[r - 1][c - 1] + matrix[r][c - 1]);

					if (result > ans)
					{
						ans = result;
					}
				}
				
				if (r < n - 2)
				{
					result = (matrix[r][c] + matrix[r + 1][c] + matrix[r + 1][c - 1] + matrix[r + 2][c - 1]);

					if (result > ans)
					{
						ans = result;
					}
				}
			}

			if (c < m - 1)
			{
				if (r > 0)
				{
					result = (matrix[r][c] + matrix[r + 1][c] + matrix[r - 1][c + 1] + matrix[r][c + 1]);

					if (result > ans)
					{
						ans = result;
					}
				}

				if (r < n - 2)
				{
					result = (matrix[r][c] + matrix[r + 1][c] + matrix[r + 1][c + 1] + matrix[r + 2][c + 1]);

					if (result > ans)
					{
						ans = result;
					}
				}
			}
		}
	}

	return;
}

// 가로 최대 2개
void col_2()
{
	int result = 0;

	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < m - 1; c++)
		{
			if (r > 0)
			{
				if (c > 0)
				{
					result = (matrix[r][c] + matrix[r][c + 1] + matrix[r - 1][c - 1] + matrix[r - 1][c]);

					if (result > ans)
					{
						ans = result;
					}
				}

				if (c < m - 2)
				{
					result = (matrix[r][c] + matrix[r][c + 1] + matrix[r - 1][c + 1] + matrix[r - 1][c + 2]);

					if (result > ans)
					{
						ans = result;
					}
				}
			}

			if (r < n - 1)
			{
				if (c > 0)
				{
					result = (matrix[r][c] + matrix[r][c + 1] + matrix[r + 1][c - 1] + matrix[r + 1][c]);

					if (result > ans)
					{
						ans = result;
					}
				}

				if (c < m - 2)
				{
					result = (matrix[r][c] + matrix[r][c + 1] + matrix[r + 1][c + 1] + matrix[r + 1][c + 2]);

					if (result > ans)
					{
						ans = result;
					}
				}
			}
		}
	}

	return;
}

// 2*2
void square()
{
	int result = 0;

	for (int r = 0; r < n - 1; r++)
	{
		for (int c = 0; c < m - 1; c++)
		{
			result = (matrix[r][c] + matrix[r][c + 1] + matrix[r + 1][c] + matrix[r + 1][c + 1]);

			if (result > ans)
			{
				ans = result;
			}
		}
	}

	return;
}

void solve()
{
	// 세로 최대 4개
	row_4();

	// 가로 최대 4개
	col_4();

	// 세로 최대 3개
	row_3();

	// 가로 최대 3개
	col_3();

	// 세로 최대 2개
	row_2();

	// 가로 최대 2개
	col_2();

	// 2*2
	square();

	return;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	scanf("%d %d", &n, &m);

	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < m; col++)
		{
			scanf("%d", &matrix[row][col]);
		}
	}

	// print_matrix();

	solve();

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
