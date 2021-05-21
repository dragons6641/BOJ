#define _CRT_SECURE_NO_WARNINGS
#define MAX_H 1000
#define MAX_W 1000
#define MAX_N 1000000

#include <stdio.h>
#include <vector>

using namespace std;

// 상태 저장 벡터
vector < vector <int> > matrix;

// DP 저장 벡터
// 몇 번이나 그 교차로를 지났는지!
vector < vector <int> > dp;

int ans_row = 0;
int ans_col = 0;

void print_matrix()
{
	printf("matrix : \n");

	for (int r = 1; r < matrix.size() - 1; r++)
	{
		for (int c = 1; c < matrix[r].size() - 1; c++)
		{
			printf("%d ", matrix[r][c]);
		}

		printf("\n");
	}

	return;
}

void print_dp()
{
	printf("dp : \n");

	for (int r = 1; r < dp.size() - 1; r++)
	{
		for (int c = 1; c < dp[r].size() - 1; c++)
		{
			printf("%d ", dp[r][c]);
		}

		printf("\n");
	}

	return;
}

// k - 1번째의 상태 만든 후
// 한 번 더 실행해 준다
void solve(int k)
{
	int cur = 0;

	// 마지막 길 찾기에 사용
	int row = 1;
	int col = 1;

	// 초기값 설정
	// 첫 칸은 k - 1번 밟고 한 번 더 밟는다
	dp[1][1] = k - 1;

	// 점화식 설정
	for (int r = 1; r < dp.size() - 1; r++)
	{
		for (int c = 1; c < dp[r].size() - 1; c++)
		{
			// 걍 변수 잡아서 옮겨쓰는 짓거리 하지마!
			// cur = dp[r][c];

			// printf("r = %d, c = %d, cur = %d\n", r, c, dp[r][c]);

			// print_matrix();
			// print_dp();

			// 현재 칸이 0이면
			if (dp[r][c] == 0)
			{
				// 칸은 반영하고
				matrix[r][c] = (matrix[r][c] + dp[r][c]) % 2;

				// 이건 건너뛴다
				continue;
			}
			// 아니면
			else
			{
				// 반반씩 간다
				dp[r + 1][c] += dp[r][c] / 2;
				dp[r][c + 1] += dp[r][c] / 2;

				// 단 홀수일때는 주의
				if ((dp[r][c] % 2) == 1)
				{
					// 첫 상태가 오른쪽이면
					if (matrix[r][c] == 1)
					{
						// 오른쪽에 +1
						dp[r][c + 1] += 1;
					}
					// 첫 상태가 아랫쪽이면
					else
					{
						// 아랫쪽에 +1
						dp[r + 1][c] += 1;
					}
				}

				// 이 칸은 더 이상 안 봐도 된다
				// 정보 반영
				matrix[r][c] = (matrix[r][c] + dp[r][c]) % 2;

				// printf("matrix = %d\n", matrix[r][c]);

				// printf("matrix : %d\n", matrix[r][c]);
			}
		}
	}

	// print_matrix();

	while (1)
	{
		cur = matrix[row][col];

		// printf("row = %d, col = %d, cur = %d\n", row, col, cur);

		// 오른쪽으로 가야하면
		if (cur)
		{
			// 끝에 왔으면
			if (col == matrix[0].size() - 2)
			{
				// 정답 표시
				ans_row = row;
				ans_col = col + 1;

				// 종료
				break;
			}
			// 아직 끝 아니라면
			else
			{
				// 오른쪽으로
				col += 1;
			}
		}
		// 아랫쪽으로 가야하면
		else
		{
			// 끝에 왔으면
			if (row == matrix.size() - 2)
			{
				// 정답 표시
				ans_row = row + 1;
				ans_col = col;

				// 종료
				break;
			}
			// 아직 끝 아니라면
			else
			{
				// 아랫쪽으로
				row += 1;
			}
		}
	}

	return;
}

int main()
{
	int h = 0;
	int w = 0;
	int n = 0;

	vector <int> tmp;

	scanf("%d %d %d", &h, &w, &n);

	// 벡터 초기화
	tmp.resize(w + 2);

	for (int r = 0; r <= h + 1; r++)
	{
		matrix.push_back(tmp);
		dp.push_back(tmp);
	}

	// printf("%d %d\n", matrix.size(), matrix[0].size());
	// printf("%d %d\n", dp.size(), dp[0].size());

	for (int r = 1; r <= h; r++)
	{
		for (int c = 1; c <= w; c++)
		{
			scanf("%d", &matrix[r][c]);
		}
	}

	// 딱 봐도 브루트 포스는 아니잖아...
	// 이건 반대로 늘려나가는 방식!

	// print_matrix();
	// print_dp();

	solve(n);

	// print_matrix();

	printf("%d %d\n", ans_row, ans_col);

	return 0;
}

// 강사님 코드
/*
#include <stdio.h>
int H, W, N;
int C[1002][1002], D[1002][1002];

int main()
{
	scanf("%d%d%d", &H, &W, &N);
	for (int r = 1; r <= H; r++)
		for (int c = 1; c <= W; c++)
		{
			scanf("%d", &D[r][c]);
			C[r][c] = 0;
		}

	C[1][1] += N - 1;
	for (int r = 1; r <= H; r++)
		for (int c = 1; c <= W; c++)
		{
			if (C[r][c] == 0)continue;

			C[r + 1][c] += C[r][c] / 2;
			C[r][c + 1] += C[r][c] / 2;
			if (C[r][c] % 2)
			{
				if (D[r][c]) C[r][c + 1]++;
				else C[r + 1][c]++;
			}
			D[r][c] = (D[r][c] + C[r][c]) % 2;
		}
	int r = 1, c = 1;
	while (r <= H&&c <= W)
	{
		if (D[r][c]) c++;
		else r++;
	}
	printf("%d %d", r, c);
}
*/
