/*
Pro입문 2주차 Problem I 섞기 수열
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 20000
#define MAX_ANS 2000000000

typedef long long ll;

int N;
int vectCnt = 0;
int cycleCnt = 0;
int vect[MAX_N] = { 0, };
int cycle[MAX_N] = { 0, };

void change(int* v1, int* v2)
{
	cycleCnt++;

	for (int i = 0; i < N; i++)
	{
		// 실제로 섞는 과정
		v2[i] = v1[vect[i] - 1];

		// 한 사이클 돌았으면
		if ((v2[i] == i + 1) && (cycle[i] == 0))
		{
			// 사이클 횟수 기록
			cycle[i] = cycleCnt;

			vectCnt++;
		}
	}

	return;
}

/*
int isFinish(int* v)
{
	for (int i = 0; i < N; i++)
	{
		if (v[i] != i + 1)
		{
			return 0;
		}
	}

	return 1;
}
*/

void init(int* v)
{
	for (int i = 0; i < N; i++)
	{
		v[i] = i + 1;
	}

	return;
}

// a >= b
ll findGcd(ll a, ll b)
{
	return (b > 0) ? findGcd(b, a % b) : a;
}

// a, b는 두 수, c는 gcd
ll findLca(ll a, ll b, ll c)
{
	return (a * b / c);
}

int main(void)
{
	/*
	int po[7] = { 5, 4, 3, 5, 4, 5 }; // 지금까지 얻은 표 수
	char name[7] = "ABEQFN";

	// 투표
	char list[21] = "NNAAABBAEEQQQQAAQQFN"; // 20명

	// 누가 당선이 되었는지 출력
	int max = -21e8;
	// char maxCh;
	int bucket[100] = { 0, };

	for (int i = 0; i < 6; i++)
	{
		bucket[name[i]] = po[i];
	}

	for (int i = 0; i < 20; i++)
	{
		bucket[list[i]]++;

		if (bucket[list[i]] > max)
		{
			max = bucket[list[i]];
		}
	}

	for (int i = 0; i < 100; i++)
	{
		if (bucket[i] == max)
		{
			printf("%c ", i);
		}
	}

	printf("\n");
	*/

	///*
	// freopen("input1.txt", "r", stdin);

	int cnt = 0;
	ll gcd;
	ll lca;
	int a[MAX_N] = { 0, };
	int b[MAX_N] = { 0, };

	setbuf(stdout, NULL);

	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &vect[i]);
	}

	init(a);

	while (true)
	{
		cnt++;

		change(a, b);

		/*
		if (isFinish(b) == 1)
		{
			break;
		}
		*/

		// 모든 사이클을 찾았으면
		if (vectCnt == N)
		{
			break;
		}

		cnt++;

		change(b, a);

		/*
		if (isFinish(a) == 1)
		{
			break;
		}
		*/

		// 모든 사이클을 찾았으면
		if (vectCnt == N)
		{
			break;
		}
	}

	// 최대공약수 초기값 찾기
	if (cycle[0] < cycle[1])
	{
		gcd = findGcd(cycle[1], cycle[0]);
	}
	else if (cycle[0] > cycle[1])
	{
		gcd = findGcd(cycle[0], cycle[1]);
	}
	else
	{
		gcd = cycle[1];
	}

	// 최소공배수 초기값 찾기
	lca = findLca(cycle[0], cycle[1], gcd);
	
	for (int i = 2; i < N; i++)
	{
		// 최대공약수 찾기
		// 최소공배수 찾기
		if (lca < cycle[i])
		{
			gcd = findGcd(cycle[i], lca);
			lca = findLca(lca, cycle[i], gcd);
		}
		else if (lca > cycle[i])
		{
			gcd = findGcd(lca, cycle[i]);
			lca = findLca(lca, cycle[i], gcd);
		}
		else
		{
			gcd = cycle[i];
			lca = cycle[i];
		}
	}

	// printf("%d\n", cnt);
	printf("%lld\n", lca);
	//*/

	return 0;
}
