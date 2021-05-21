/*
16161 가장 긴 증가하는 팰린드롬 부분수열
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 100000
#define MAX_M 1000000000

int N;
// 최솟값으로 초기화
int ans = 0;
// 1부터 시작
int inputList[MAX_N + 1] = { 0, };

// 팰린드롬인지 체크하는 함수
int checkPalindrome(int lp, int rp)
{
	// 홀수 : 수열 길이의 절반 - 1
	// 짝수 : 수열 길이의 절반
	int result = 0;
	// 최댓값 + 1로 초기화
	int lastNum = MAX_M + 1;

	while ((lp >= 1) && (rp <= N))
	{
		// 팰린드롬이고, 증가한다면
		if ((inputList[lp] == inputList[rp]) && (inputList[lp] < lastNum))
		{
			// 자신 스스로와 비교한 경우는 세지 않는다
			if (lp < rp)
			{
				result++;
			}

			// 값 갱신, 포인터 이동
			lastNum = inputList[lp];
			lp--;
			rp++;
		}
		else
		{
			break;
		}
	}

	return result;
}

void input(void)
{
	scanf("%d", &N);

	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &inputList[i]);
	}

	return;
}

void solve(void)
{
	// 투 포인터
	int lp = 1;
	int rp = 2;
	// rp가 이동할 크기
	// 음수값을 가지는 것은 불가능
	int cnt = 0;

	while (rp <= N)
	{
		// (rp - 1)번째와 rp번째의 원소를 비교
		// 뒷 원소가 더 크다면
		if (inputList[rp - 1] < inputList[rp])
		{
			// rp포인터 증가
			rp++;
		}
		// 앞 원소가 더 크다면
		else if (inputList[rp - 1] > inputList[rp])
		{
			// (rp - 1)번째 값을 중심으로 팰린드롬인지 확인
			// 전체 원소는 홀수개
			// cnt 값은 수열 길이의 절반 - 1
			cnt = checkPalindrome(rp - 1, rp - 1);

			// 정답 갱신
			if (ans < (cnt * 2) + 1)
			{
				ans = (cnt * 2) + 1;
			}

			// 다음 탐색 지점으로 이동
			if (cnt == 0)
			{
				rp++;
			}
			else
			{
				rp += cnt;
			}

			lp = rp;
		}
		// 같다면
		else
		{
			// (rp - 1)번째 값과 rp번째 값을 중심으로 팰린드롬인지 확인
			// 전체 원소는 짝수개
			// cnt 값은 수열 길이의 절반
			cnt = checkPalindrome(rp - 1, rp);

			// 정답 갱신
			if (ans < (cnt * 2))
			{
				ans = (cnt * 2);
			}

			// 다음 탐색 지점으로 이동
			if (cnt == 0)
			{
				rp++;
			}
			else
			{
				rp += cnt;
			}

			lp = rp;
		}

		// int debug = 1;
	}

	if (ans == 0)
	{
		ans = 1;
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);	// 4
	// freopen("input2.txt", "r", stdin);	// 3
	// freopen("input3.txt", "r", stdin);	// 2
	// freopen("input4.txt", "r", stdin);	// 1
	// freopen("input5.txt", "r", stdin);	// 2
	// freopen("input6.txt", "r", stdin);	// 1
	// freopen("input7.txt", "r", stdin);	// 1
	// freopen("input8.txt", "r", stdin);	// 3
	// freopen("input9.txt", "r", stdin);	// 2
	// freopen("input10.txt", "r", stdin);	// 2
	// freopen("input11.txt", "r", stdin);	// 3
	// freopen("input12.txt", "r", stdin);	// 2
	// freopen("input13.txt", "r", stdin);	// 5
	// freopen("input14.txt", "r", stdin);	// 2
	// freopen("input15.txt", "r", stdin);	// 3

	setbuf(stdout, NULL);

	input();

	// 예외처리(N == 1)
	if (N == 1)
	{
		ans = 1;
	}
	// 예외처리(N == 2)
	else if (N == 2)
	{
		// 두 수가 서로 같을 경우
		if (inputList[1] == inputList[2])
		{
			ans = 2;
		}
		// 두 수가 서로 다를 경우
		else
		{
			ans = 1;
		}
	}
	// 일반적인 경우
	else
	{
		solve();
	}

	printf("%d\n", ans);

	return 0;
}
