#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_T 100
#define MAX_L 5000
#define MOD 1000000007

typedef long long LL;

// 테스트케이스의 갯수
int T;
// 괄호 문자열의 길이
int L;
// dp[K] : 길이가 K인 괄호 문자열의 갯수 % MOD
// 1부터 사용
LL dp[MAX_L + 1] = { 0, };

void solve(void)
{
	// 미리 dp를 구해둔다
	// 초기값 설정
	// 곱셈으로 만드니까 초기값은 1
	dp[0] = 1;
	dp[2] = 1;

	// 전체 문자열의 길이
	for (register int i = 4; i <= MAX_L; i += 2)
	{
		// 부분 문자열의 길이
		for (register int j = 2; j <= i; j++)
		{
			dp[i] += (dp[j - 2] * dp[i - j]);
			dp[i] %= MOD;
		}
	}

	scanf("%d", &T);

	for (register int i = 1; i <= T; i++)
	{
		scanf("%d", &L);

		printf("%lld\n", dp[L]);
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	solve();

	return 0;
}
