// KJO17136.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#define ROWS 10
#define COLS 10
#define INF 1000000000
#define PAPERS 5
#define SIZES 5

/*
#include "pch.h"
#include <iostream>
*/

#include <stdio.h>
#include <vector>

using namespace std;

int ans = INF;

int matrix[ROWS][COLS] = { -1 };
int isChecked[ROWS][COLS] = { 0 };
int cnt_list[SIZES + 1] = { PAPERS };
vector <pair<int, int>> v;

void init()
{
	ans = INF;

	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			matrix[row][col] = -1;
			// isChecked[row][col] = 0;
		}
	}

	for (int i = 1; i <= SIZES; i++)
	{
		cnt_list[i] = PAPERS;
	}

	return;
}

void print_matrix()
{
	printf("matrix : \n");

	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			printf("%d ", matrix[row][col]);
		}

		printf("\n");
	}

	printf("\n");

	return;
}

///*
void print_check()
{
	printf("isChecked : \n");

	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			printf("%d ", isChecked[row][col]);
		}

		printf("\n");
	}

	printf("\n");

	return;
}
//*/

void print_cnt()
{
	printf("cnt_list : \n");

	for (int i = 1; i <= SIZES; i++)
	{
		printf("%d ", cnt_list[i]);
	}

	printf("\n");

	return;
}

int fill(int start_r, int start_c, int s)
{
	// 경계 밖으로 나가는 경우
	if ((start_r + s >= ROWS + 1) || (start_c + s >= COLS + 1))
	{
		// 채울 수 없음
		return 0;
	}

	// 채워보자
	for (int row = start_r; row < start_r + s; row++)
	{
		for (int col = start_c; col < start_c + s; col++)
		{
			// 채우면 안되는 칸일 경우
			if (matrix[row][col] != 1)
			{
				// 채울 수 없음
				return 0;
			}
		}
	}

	// 빠져나왔다면 채울 수 있다는 것!
	for (int row = start_r; row < start_r + s; row++)
	{
		for (int col = start_c; col < start_c + s; col++)
		{
			// 채워준다
			matrix[row][col] = s + 4;

			// 체크도 해준다
			// isChecked[row][col] = 1;
		}
	}

	// 채우기 성공
	return 1;
}

void reverse_fill(int start_r, int start_c, int s)
{
	/*
	// 경계 밖으로 나가는 경우
	if ((start_r + s >= ROWS + 1) || (start_c + s >= COLS + 1))
	{
		// 채울 수 없음
		return 0;
	}
	*/

	/*
	for (int row = start_r; row < start_r + s; row++)
	{
		for (int col = start_c; col < start_c + s; col++)
		{
			// 채우면 안되는 칸일 경우
			if (matrix[row][col] != 1)
			{
				// 채울 수 없음
				return 0;
			}
		}
	}
	*/

	// 빠져나왔다면 채울 수 있다는 것!
	for (int row = start_r; row < start_r + s; row++)
	{
		for (int col = start_c; col < start_c + s; col++)
		{
			// 복구해준다
			matrix[row][col] = 1;

			// 체크도 돌려준다
			// isChecked[row][col] = 1;
		}
	}

	// 복구 성공
	return;
}

int check_matrix(int start_r, int start_c, int d)
{
	int remain = 0;

	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			// 채워지지 않은 칸 있으면
			if (matrix[row][col] == 1)
			{
				// 남은 칸 갯수 추가
				remain += 1;
			}
		}
	}

	return remain;
}

int check_result()
{
	int result = 0;

	for (int i = 1; i <= SIZES; i++)
	{
		result += (PAPERS - cnt_list[i]);
	}

	return result;
}

int check_paper()
{
	int remain = 0;

	for (int i = 1; i < SIZES; i++)
	{
		remain += (cnt_list[i] * (i * i));
	}

	return remain;
}

int check_1()
{
	int result = 0;
	int is1 = 0;

	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			is1 = 0;

			if (matrix[row][col] == 1)
			{
				if (is1)
				{
					break;
				}
				else
				{
					// 위 아래 막힌 경우
					// 일반
					if ((row > 0) && (row < ROWS - 1))
					{
						if ((matrix[row - 1][col] == 0) && (matrix[row + 1][col] == 0))
						{
							is1 = 1;

							result += 1;
						}
					}
					else if (row == 0)
					{
						if (matrix[row + 1][col] == 0)
						{
							is1 = 1;

							result += 1;
						}
					}
					else if (row == ROWS - 1)
					{
						if (matrix[row - 1][col] == 0)
						{
							is1 = 1;

							result += 1;
						}
					}
				}

				if (is1)
				{
					break;
				}
				else
				{
					// 양 옆 막힌 경우
					// 일반
					if ((col > 0) && (col < COLS - 1))
					{
						if ((matrix[row][col - 1] == 0) && (matrix[row][col + 1] == 0))
						{
							is1 = 1;

							result += 1;
						}
					}
					else if (col == 0)
					{
						if (matrix[row][col + 1] == 0)
						{
							is1 = 1;

							result += 1;
						}
					}
					else if (col == COLS - 1)
					{
						if (matrix[row][col - 1] == 0)
						{
							is1 = 1;

							result += 1;
						}
					}
				}

				/*
				if (is1)
				{
					break;
				}
				*/
			}
		}
	}

	return result;
}

// void backtrack(int start_r, int start_c, int depth, int remain)
void backtrack(int start, int depth, int remain)
{
	int isFilled = -1;
	int isAvailable = -1;
	int remain_matrix = -1;
	int remain_paper = -1;
	int result = -1;
	int need_1 = -1;

	/*
	printf("start = %d, depth = %d, remain = %d\n", start, depth, remain);
	print_matrix();
	*/

	// 끝까지 갔다면
	if (start >= v.size())
	{
		// 남아있다면
		if (remain > 0)
		{
			return;
		}
		// 모두 채웠다면
		else
		{
			if (depth < ans)
			{
				ans = depth;
			}
		}
	}

	// 답이 될 수 있는지 체크
	// result = check_result();

	// 답이 될 수 없다면
	if (depth >= ans)
	{
		return;
	}

	/*
	// 다 채웠는지 체크
	remain_matrix = check_matrix(start_r, start_c, depth);
	*/

	/*
	printf("(%d, %d), depth : %d, result = %d, ans = %d, remain_matrix = %d\n", start_r, start_c, depth, result, ans, remain_matrix);
	print_matrix();
	// print_check();
	print_cnt();
	*/

	// printf("(%d, %d), depth : %d, result = %d, ans = %d, remain_matrix = %d\n", v[start].first, v[start].second, depth, result, ans, remain_matrix);

	// 왜 답이 안맞지?
	// 정답일 경우
	// if (remain_matrix == 0)
	// 이 경우는 남은 칸이 0인 경우!
	///*
	if (remain == 0)
	{
		// print_cnt();

		// 정답 갱신
		if (depth < ans)
		{
			ans = depth;
		}
	}
	//*/
	/*
	else
	{
		remain_paper = check_paper();

		// 남은 칸을 종이로 모두 채울 수 없을 경우
		if (remain_matrix > remain_paper)
		{
			return;
		}
	}
	*/

	/*
	// 1개짜리 없을 경우 쳐내자!
	need_1 = check_1();

	// 1개짜리가 부족하면
	if (need_1 > cnt_list[1])
	{
		return;
	}
	*/

	/*
	for (int row = start_r; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			// printf("탐색 중 : (%d, %d)\n", row, col);

			// 시작 줄일 경우
			if (row == start_r)
			{
				// 이미 확인했다면
				if (col < start_c)
				{
					// 넘어가자
					continue;
				}
			}

			// 채워야 하는 칸인 경우
			if (matrix[row][col] == 1)
			{
				isAvailable = 0;

				// 5부터 1까지
				for (int k = SIZES; k > 0; k--)
				{
					// printf("(%d, %d), size: %d\n", row, col, k);

					// 해당 사이즈 색종이 남아있으면
					if (cnt_list[k] > 0)
					{
						// 채우기 시도
						isFilled = fill(row, col, k);
					}
					// 색종이 없으면
					else
					{
						// 못 채움
						isFilled = 0;
					}

					// 채워졌다면
					if (isFilled == 1)
					{
						// 계속 탐색 가능
						isAvailable = 1;

						// 해당되는 사이즈의 색종이 갯수 갱신
						cnt_list[k] -= 1;

						// 마지막 col이라면
						if (col == COLS - 1)
						{
							// 다음 줄부터 완전탐색
							backtrack(row + 1, 0, depth + 1, remain - (k * k));
						}
						// 마지막 col이 아니라면
						else
						{
							// 다음 col부터 완전탐색
							backtrack(row, col + 1, depth + 1, remain - (k * k));
						}

						// 해당되는 사이즈의 색종이 갯수 초기화
						cnt_list[k] += 1;

						// 채운거 다시 되돌려주자
						reverse_fill(row, col, k);
					}
				}

				// 5개 모두 못채웠다면, 즉 1이 남아있다면
				if (isAvailable == 0)
				{
					return;
				}
			}
		}
	}
	*/

	int row = v[start].first;
	int col = v[start].second;

	// printf("value : %d\n", matrix[row][col]);

	// 채워야 하는 칸인 경우
	if (matrix[row][col] == 1)
	{
		isAvailable = 0;

		// 5부터 1까지
		for (int k = SIZES; k > 0; k--)
		{
			// printf("(%d, %d), size: %d\n", row, col, k);

			// 해당 사이즈 색종이 남아있으면
			if (cnt_list[k] > 0)
			{
				// 채우기 시도
				isFilled = fill(row, col, k);
			}
			// 색종이 없으면
			else
			{
				// 못 채움
				isFilled = 0;
			}

			// 채워졌다면
			if (isFilled == 1)
			{
				// 계속 탐색 가능
				isAvailable = 1;

				// 해당되는 사이즈의 색종이 갯수 갱신
				cnt_list[k] -= 1;

				/*
				// 마지막 col이라면
				if (col == COLS - 1)
				{
					// 다음 줄부터 완전탐색
					backtrack(row + 1, 0, depth + 1, remain - (k * k));
				}
				// 마지막 col이 아니라면
				else
				{
					// 다음 col부터 완전탐색
					backtrack(row, col + 1, depth + 1, remain - (k * k));
				}
				*/

				// printf("(%d, %d), depth : %d, result = %d, ans = %d, remain = %d, k = %d\n", row, col, depth, result, ans, remain, k);

				backtrack(start + 1, depth + 1, remain - (k * k));

				// printf("returned\n");

				// 해당되는 사이즈의 색종이 갯수 초기화
				cnt_list[k] += 1;

				// 채운거 다시 되돌려주자
				reverse_fill(row, col, k);
			}
		}

		// 5개 모두 못채웠다면, 즉 1이 남아있다면
		if (isAvailable == 0)
		{
			return;
		}
	}
	// 이미 채워져있다면
	else if (matrix[row][col] > 1)
	{
		backtrack(start + 1, depth, remain);
	}

	return;
}

int main()
{
    // std::cout << "Hello World!\n";

	int remain = 0;

	init();

	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			scanf("%d", &matrix[row][col]);

			if (matrix[row][col] == 1)
			{
				remain += 1;

				v.push_back(make_pair(row, col));
			}
		}
	}

	// print_matrix();
	// print_cnt();

	// backtrack(0, 0, 0, remain);
	backtrack(0, 0, remain);

	// 불가능할 경우
	if (ans == INF)
	{
		// -1 출력
		ans = -1;
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
