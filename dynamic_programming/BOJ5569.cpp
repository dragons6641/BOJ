#define _CRT_SECURE_NO_WARNINGS
#define MAX_W 100
#define MAX_H 100
#define MOD 100000

#include <stdio.h>
#include <vector>

using namespace std;

typedef struct node
{
	// dp값, 방법의 수
	int value = 0;
	// 진행방향 오른쪽인데 회전 직전에 함
	int ne = 0;
	// 진행방향 오른쪽인데 회전 직전에 안함
	int ee = 0;
	// 진행방향 위쪽인데 회전 직전에 함
	int en = 0;
	// 진행방향 위쪽인데 회전 직전에 안함
	int nn = 0;
}
NODE;

// dp 벡터
vector <vector <NODE> > dp;

void print_dp()
{
	printf("dp : \n");

	for (int r = 1; r < dp.size(); r++)
	{
		for (int c = 1; c < dp[r].size(); c++)
		{
			printf("%d ", dp[r][c].value);
		}

		printf("\n");
	}

	return;
}

// dp 배열을 만드는 과정
int solve(int r, int c)
{
	int result = 0;

	// 초기값 설정
	for (int i = 1; i < dp.size(); i++)
	{
		for (int j = 1; j < dp[i].size(); j++)
		{
			// 완전 처음이면
			if ((i == 1) && (j == 1))
			{
				dp[i][j].ne = 0;
				dp[i][j].ee = 0;
				dp[i][j].en = 0;
				dp[i][j].nn = 0;

				// value는 안전하게 구해준다!
				dp[i][j].value = dp[i][j].ne + dp[i][j].ee + dp[i][j].en + dp[i][j].nn;
			}
			// row쪽이 1, col이 넓적하다!
			else if (i == 1)
			{
				dp[i][j].ne = 0;
				dp[i][j].ee = 1;
				dp[i][j].en = 0;
				dp[i][j].nn = 0;

				// value는 안전하게 구해준다!
				dp[i][j].value = dp[i][j].ne + dp[i][j].ee + dp[i][j].en + dp[i][j].nn;
			}
			// col쪽이 1, row가 길쭉하다!
			else if (j == 1)
			{
				dp[i][j].ne = 0;
				dp[i][j].ee = 0;
				dp[i][j].en = 0;
				dp[i][j].nn = 1;

				// value는 안전하게 구해준다!
				dp[i][j].value = dp[i][j].ne + dp[i][j].ee + dp[i][j].en + dp[i][j].nn;
			}
			///*
			// 2일 경우도 해줘야함
			else if ((i == 2)  && (j == 2))
			{
				dp[i][j].ne = 1;
				dp[i][j].ee = 0;
				dp[i][j].en = 1;
				dp[i][j].nn = 0;

				// value는 안전하게 구해준다!
				dp[i][j].value = dp[i][j].ne + dp[i][j].ee + dp[i][j].en + dp[i][j].nn;
			}
			// row쪽이 2, col이 넓적하다!
			else if (i == 2)
			{
				dp[i][j].ne = 0;
				dp[i][j].ee = 1;
				dp[i][j].en = 1;
				dp[i][j].nn = 0;

				// value는 안전하게 구해준다!
				dp[i][j].value = dp[i][j].ne + dp[i][j].ee + dp[i][j].en + dp[i][j].nn;
			}
			// col쪽이 2, row가 길쭉하다!
			else if (j == 2)
			{
				dp[i][j].ne = 1;
				dp[i][j].ee = 0;
				dp[i][j].en = 0;
				dp[i][j].nn = 1;

				// value는 안전하게 구해준다!
				dp[i][j].value = dp[i][j].ne + dp[i][j].ee + dp[i][j].en + dp[i][j].nn;
			}
			//*/
		}
	}

	// print_dp();

	// 점화식
	for (int i = 3; i < dp.size(); i++)
	{
		for (int j = 3; j < dp[i].size(); j++)
		{
			// 나눠주는 것 잊지 말자
			// dp[i][j] = (dp[i - 2][j] + dp[i - 1][j - 1] + dp[i][j - 2]) % MOD;

			dp[i][j].ne = dp[i][j - 1].nn % MOD;
			dp[i][j].ee = (dp[i][j - 1].ne + dp[i][j - 1].ee) % MOD;
			dp[i][j].en = dp[i - 1][j].ee % MOD;
			dp[i][j].nn = (dp[i - 1][j].en + dp[i - 1][j].nn) % MOD;

			// value는 안전하게 구해준다!
			dp[i][j].value = (dp[i][j].ne + dp[i][j].ee + dp[i][j].en + dp[i][j].nn) % MOD;
		}
	}

	// print_dp();

	result = dp[r][c].value;

	return result;
}

int main()
{
	int w = 0;
	int h = 0;
	int ans = 0;

	vector <NODE> tmp;

	scanf("%d %d", &w, &h);

	// 벡터 사이즈
	tmp.resize(w + 1);

	for (int i = 0; i <= h; i++)
	{
		dp.push_back(tmp);
	}

	// print_dp();

	ans = solve(h, w);

	printf("%d\n", ans);

	return 0;
}

// 강사님 코드
/*
#include <stdio.h>
int W, H;
int D[2][2][101][101];

int main()
{
	scanf("%d%d", &W, &H);
	for (int r = 1; r <= H; r++) D[0][0][r][1] = 1;
	for (int c = 1; c <= W; c++) D[1][0][1][c] = 1;
	for (int r = 2; r <= H; r++)
	{
		for (int c = 2; c <= W; c++)
		{
			D[0][0][r][c] += D[0][0][r - 1][c];
			if (r - 2>0) D[0][0][r][c] += (D[1][0][r - 2][c]);
			D[0][1][r][c] += D[1][0][r - 1][c];

			D[1][0][r][c] += D[1][0][r][c - 1];
			if (c - 2>0) D[1][0][r][c] += (D[0][0][r][c - 2]);
			D[1][1][r][c] += D[0][0][r][c - 1];

			D[0][0][r][c] %= 100000;
			D[1][0][r][c] %= 100000;
			D[0][1][r][c] %= 100000;
			D[1][1][r][c] %= 100000;
		}
	}
	int ans = (D[0][0][H][W] + D[1][0][H][W] + D[0][1][H][W] + D[1][1][H][W]) % 100000;
	printf("%d", ans);

}
*/
