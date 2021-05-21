#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <vector>

using namespace std;

typedef struct node
{
	int s = 0;
	int t = 0;
	int r = 0;
	int q = 0;
}
NODE;

int euclid(int m, int n)
{
	int cnt = 0;
	int result = 0;

	NODE cur;

	// 벡터 선언
	vector <NODE> v;

	// 0번째
	cur.s = 1;
	cur.t = 0;
	cur.r = m;
	cur.q = -1;

	// 초기값 넣어주기
	v.push_back(cur);

	// 1번째
	cur.s = 0;
	cur.t = 1;
	cur.r = n;
	cur.q = -1;

	// 초기값 넣어주기
	v.push_back(cur);

	// 2번째부터는 무한루프
	while (1)
	{
		// 몫 구하기
		cur.q = v[cnt].r / v[cnt + 1].r;

		// 나머지 구하기
		cur.r =  v[cnt].r % v[cnt + 1].r;

		// s 구하기
		cur.s = v[cnt].s - v[cnt + 1].s * cur.q;

		// t 구하기
		cur.t = v[cnt].t - v[cnt + 1].t * cur.q;

		// 나머지가 0이면
		if (cur.r == 0)
		{
			// 아직 넣은거 아니니까 마지막거 빼라
			cur = v.back();

			// a = cur.s, b = cur.t
			// x = m, y = n
			result = cur.r;

			break;
		}

		// 아니면
		else
		{
			// 계속
			v.push_back(cur);

			// printf("%d %d %d %d\n", cur.s, cur.t, cur.r, cur.q);

			cnt += 1;
		}
	}

	return result;
}

int main()
{
	int a = 0;
	int b = 0;
	int m = 0;
	int n = 0;
	int mo = 0;
	int ja = 0;
	int gcd = 0;

	scanf("%d %d", &a, &m);

	scanf("%d %d", &b, &n);

	// printf("%d %d %d %d\n", a, b, m, n);

	// 일단 계산
	mo = m * n;
	ja = (a * n + b * m);

	// printf("%d %d\n", ja, mo);

	// 확장 유클리드 호제법
	if (mo > ja)
	{
		gcd = euclid(mo, ja);
	}
	else
	{
		gcd = euclid(ja, mo);
	}

	printf("%d %d\n", ja / gcd, mo / gcd);

	return 0;
}

// 강사님 코드
/*
#include <cstdio>

int gcd(int a, int b)
{
	if (b) return gcd(b, a%b);
	else return a;
}

int main()
{
	int A1, B1, A2, B2;
	scanf("%d %d", &A1, &B1);
	scanf("%d %d", &A2, &B2);
	int U, D, g;
	D = B1*B2; // 분모 통분 
	U = A1*B2 + A2*B1; // 분자 계산 
	g = gcd(D, U);
	printf("%d %d", U / g, D / g);
}
*/
