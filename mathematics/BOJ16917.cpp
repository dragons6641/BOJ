#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// 양념 치킨 한 마리의 가격
int A;
// 후라이드 치킨 한 마리의 가격
int B;
// 반반 치킨 한 마리의 가격
int C;
// 양념 치킨 최소 마리 수
int X;
// 후라이드 치킨 최소 마리 수
int Y;

int calcMax(int v, int w)
{
	return ((v > w) ? v : w);
}

int calcMin(int v, int w)
{
	return ((v < w) ? v : w);
}

int calcAbs(int k)
{
	return ((k > 0) ? k : 0);
}

int solve(void)
{
	int cnt;
	int tmp;

	// 1. 반반 치킨 없이 따로 사는 경우
	// 양념, 후라이드 각각 갯수에 맞춰서 구매
	int result = (A * X) + (B * Y);

	// 2. 반반 치킨을 필요한 만큼만 사는 경우
	// 양념, 후라이드 중 적은 마리 수 * 2만큼 구매
	cnt = calcMin(X, Y);
	tmp = C * cnt * 2;
	
	// 양념을 추가로 구매해야 할 경우
	if (X > Y)
	{
		tmp += (A * (X - Y));
	}
	// 후라이드를 추가로 구매해야 할 경우
	else
	{
		tmp += (B * (Y - X));
	}

	result = calcMin(result, tmp);

	// 3. 반반 치킨을 최대로 사는 경우
	// 양념, 후라이드 중 많은 마리 수 * 2만큼 구매
	cnt = calcMax(X, Y);
	tmp = C * cnt * 2;
	result = calcMin(result, tmp);

	return result;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);	// 7900
	// freopen("input2.txt", "r", stdin);	// 8500
	// freopen("input3.txt", "r", stdin);	// 100000000

	scanf("%d %d %d %d %d", &A, &B, &C, &X, &Y);

	int ans = solve();

	printf("%d\n", ans);

	return 0;
}
