// KJO14890.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 100
#define MAX_L 100
#define MAX_H 10

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>

int n = 0;
int l = 0;
int ans = 0;

int matrix[MAX_N][MAX_N] = { 0 };
int isConstructed[MAX_N][MAX_N] = { 0 };

void print_matrix()
{
	printf("matrix : \n");
	
	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			printf("%d ", matrix[row][col]);
		}

		printf("\n");
	}

	printf("\n");

	return;
}

void init()
{
	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			isConstructed[row][col] = 0;
		}
	}

	return;
}

void row_search()
{
	int cur = 0;
	int prev = 0;
	int cnt = 0;
	int isAvailable = 0;
	int isRoad = 1;

	for (int col = 0; col < n; col++)
	{
		cnt = 0;
		isRoad = 1;

		// 위에서 아래로
		for (int row = 0; row < n; row++)
		{
			// printf("(%d, %d), cnt = %d\n", row, col, cnt);

			isAvailable = 0;

			// 예외 처리
			if (row == 0)
			{
				cnt += 1;
			}
			// 일반 케이스
			else
			{
				cur = matrix[row][col];
				prev = matrix[row - 1][col];

				// 높이가 같으면
				if (cur == prev)
				{
					cnt += 1;
				}
				// 높이가 높아지면
				else if (cur > prev)
				{
					// 높이 차이가 1보다 크다면
					// 경사로를 놓을 공간이 없다면
					if ((cur - prev > 1) || (cnt < l))
					{
						// 불가능, 초기화
						cnt = 1;
						isRoad = 0;
					}
					else
					{
						// 경사로 놓을 곳 탐색
						for (int k = row - 1; k > row - l - 1; k--)
						{
							// 이미 경사로가 있다면
							if (isConstructed[k][col])
							{
								// 불가능, 초기화
								cnt = 1;
								isRoad = 0;

								break;
							}

							isAvailable = 1;
						}

						// 공사 가능하다면
						if (isAvailable)
						{
							// 경사로 놓기
							for (int k = row - 1; k > row - l - 1; k--)
							{
								isConstructed[k][col] = 1;
							}

							// 초기화
							cnt = 1;
						}
					}

				}
				// 높이가 낮아지면
				else
				{

				}
			}
		}

		cnt = 0;

		// 이미 길 아닌거 확인했으면
		if (!isRoad)
		{
			// 한 번 더 확인할 필요는 없음
			continue;
		}

		// 위에서 아래로
		for (int row = n - 1; row >= 0; row--)
		{
			// printf("(%d, %d), cnt = %d\n", row, col, cnt);

			isAvailable = 0;

			// 예외 처리
			if (row == n - 1)
			{
				cnt += 1;
			}
			// 일반 케이스
			else
			{
				cur = matrix[row][col];
				prev = matrix[row + 1][col];

				// 높이가 같으면
				if (cur == prev)
				{
					cnt += 1;
				}
				// 높이가 높아지면
				else if (cur > prev)
				{
					// 높이 차이가 1보다 크다면
					// 경사로를 놓을 공간이 없다면
					if ((cur - prev > 1) || (cnt < l))
					{
						// 불가능, 초기화
						cnt = 1;
						isRoad = 0;
					}
					else
					{
						// 경사로 놓을 곳 탐색
						for (int k = row + 1; k < row + l + 1; k++)
						{
							// 이미 경사로가 있다면
							if (isConstructed[k][col])
							{
								// 불가능, 초기화
								cnt = 1;
								isRoad = 0;

								break;
							}

							isAvailable = 1;
						}

						// 공사 가능하다면
						if (isAvailable)
						{
							// 경사로 놓기
							for (int k = row + 1; k < row + l + 1; k++)
							{
								isConstructed[k][col] = 1;
							}

							// 초기화
							cnt = 1;
						}
					}

				}
				// 높이가 낮아지면
				else
				{

				}
			}
		}

		// 길이라면
		if (isRoad)
		{
			// printf("col = %d\n", col);

			ans += 1;
		}
	}

	return;
}

void col_search()
{
	int cur = 0;
	int prev = 0;
	int cnt = 0;
	int isAvailable = 0;
	int isRoad = 1;

	for (int row = 0; row < n; row++)
	{
		cnt = 0;
		isRoad = 1;

		// 왼쪽에서 오른쪽으로
		for (int col = 0; col < n; col++)
		{
			// printf("(%d, %d), cnt = %d\n", row, col, cnt);

			isAvailable = 0;

			// 예외 처리
			if (col == 0)
			{
				cnt += 1;
			}
			// 일반 케이스
			else
			{
				cur = matrix[row][col];
				prev = matrix[row][col - 1];

				// 높이가 같으면
				if (cur == prev)
				{
					cnt += 1;
				}
				// 높이가 높아지면
				else if (cur > prev)
				{
					// 높이 차이가 1보다 크다면
					// 경사로를 놓을 공간이 없다면
					if ((cur - prev > 1) || (cnt < l))
					{
						// 불가능, 초기화
						cnt = 1;
						isRoad = 0;
					}
					else
					{
						// 경사로 놓을 곳 탐색
						for (int k = col - 1; k > col - l - 1; k--)
						{
							// 이미 경사로가 있다면
							if (isConstructed[row][k])
							{
								// 불가능, 초기화
								cnt = 1;
								isRoad = 0;

								break;
							}

							isAvailable = 1;
						}

						// 공사 가능하다면
						if (isAvailable)
						{
							// 경사로 놓기
							for (int k = col - 1; k > col - l - 1; k--)
							{
								isConstructed[row][k] = 1;
							}

							// 초기화
							cnt = 1;
						}
					}

				}
				// 높이가 낮아지면
				else
				{

				}
			}
		}

		cnt = 0;

		// 이미 길 아닌거 확인했으면
		if (!isRoad)
		{
			// 한 번 더 확인할 필요는 없음
			continue;
		}

		// 오른쪽에서 왼쪽으로
		for (int col = n - 1; col >= 0; col--)
		{
			// printf("(%d, %d), cnt = %d\n", row, col, cnt);

			isAvailable = 0;

			// 예외 처리
			if (col == n - 1)
			{
				cnt += 1;
			}
			// 일반 케이스
			else
			{
				cur = matrix[row][col];
				prev = matrix[row][col + 1];

				// 높이가 같으면
				if (cur == prev)
				{
					cnt += 1;
				}
				// 높이가 높아지면
				else if (cur > prev)
				{
					// 높이 차이가 1보다 크다면
					// 경사로를 놓을 공간이 없다면
					if ((cur - prev > 1) || (cnt < l))
					{
						// 불가능, 초기화
						cnt = 1;
						isRoad = 0;
					}
					else
					{
						// 경사로 놓을 곳 탐색
						for (int k = col + 1; k < col + l + 1; k++)
						{
							// 이미 경사로가 있다면
							if (isConstructed[row][k])
							{
								// 불가능, 초기화
								cnt = 1;
								isRoad = 0;

								break;
							}

							isAvailable = 1;
						}

						// 공사 가능하다면
						if (isAvailable)
						{
							// 경사로 놓기
							for (int k = col + 1; k < col + l + 1; k++)
							{
								isConstructed[row][k] = 1;
							}

							// 초기화
							cnt = 1;
						}
					}

				}
				// 높이가 낮아지면
				else
				{

				}
			}
		}

		// 길이라면
		if (isRoad)
		{
			// printf("row = %d\n", row);

			ans += 1;
		}
	}

	return;
}

void solve()
{
	// row
	row_search();

	// 초기화
	init();

	// col
	col_search();

	return;
}

int main()
{
    // std::cout << "Hello World!\n"; 

	scanf("%d %d", &n, &l);

	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
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
