#define _CRT_SECURE_NO_WARNINGS
#define MAX_DIGIT 100
#define MAX_K 1000000

#include <cstdio>
#include <vector>

using namespace std;

// 상태를 표시할 벡터
vector <int> check;

// 소수를 모아둘 벡터
vector <int> prime;

char p[MAX_DIGIT + 1] = "\0";

void print_p()
{
	int i = 0;

	printf("p = ");

	while (p[i] != '\0')
	{
		printf("%c", p[i]);

		i++;
	}

	printf("\n");

	return;
}

void print_prime()
{
	printf("prime : ");

	for (int i = 0; i < prime.size(); i++)
	{
		printf("%d ", prime[i]);
	}

	printf("\n");

	return;
}

void sieve(int k)
{
	// i는 시작 위치
	for (int i = 2; i <= k; i++)
	{
		// 시작점은 따로 처리
		if (check[i] == 0)
		{
			// 소수임
			prime.push_back(i);
		}

		// j는 현재 위치
		for (int j = 2 * i; j <= k; j += i)
		{
			// 아직 표시 안 되어있다면
			if (check[j] == 0)
			{
				check[j] = 1;
			}
		}
	}

	return;
}

int solve(int k)
{
	int result = 0;
	int j = 0;

	// k 미만의 모든 소수들에 대해
	for (int i = 0; i < prime.size(); i++)
	{
		// 이중 반복문은 초기화 주의!
		result = 0;
		j = 0;

		while (p[j] != '\0')
		{
			// 가장 큰 자릿수부터 나머지 연산
			// char니까 추가 처리 해줘야 함!
			result = ((result * 10) + (p[j] - '0')) % prime[i];

			// printf("result = %d, p[j] = %d, prime[i] = %d\n", result, p[j] - '0', prime[i]);

			j++;
		}

		// 최종 나머지 연산의 값이 0이면
		if (result == 0)
		{
			// BAD, 해당 소수를 리턴
			return prime[i];
		}
	}

	// GOOD
	return 0;
}

int main()
{
	int k = 0;
	int ans = 0;

	scanf("%s %d", p, &k);

	/*
	print_p();
	printf("k = %d\n", k);
	*/

	// 벡터 사이즈 결정
	check.resize(k);
	prime.reserve(k);

	// 예외 처리
	if (k == 2)
	{
		printf("GOOD\n");
	}
	// 일반적인 경우
	else
	{
		// 1. k 미만의 소수 구하기
		sieve(k - 1);

		// print_prime();

		// 2. p가 해당 소수들 중 하나라도 나누어 떨어지면 BAD
		ans = solve(k - 1);

		// GOOD
		if (ans == 0)
		{
			printf("GOOD\n");
		}
		else
		{
			printf("BAD %d\n", ans);
		}
	}

	return 0;
}

// 강사님 코드
/*
#include <stdio.h>
#include <string.h>
int K, p;
char P[101];
bool isPrime[1000001];
int prime[1000001], pcnt;

void makePrime(int n) // n보다 작은 소수 구하기 
{
	isPrime[0] = isPrime[1] = false;
	for (int i = 2; i < n; i++) isPrime[i] = true;

	pcnt = 0;
	for (int i = 2; i < n; i++)
	{
		if (isPrime[i])
		{
			prime[pcnt++] = i;
			for (int j = i + i; j <= n; j += i) isPrime[j] = false;
		}
	}
}

int div(int num)
{
	int d = 0, len = strlen(P);
	for (int i = 0; i < len; i++)
	{
		d = d * 10 + P[i] - '0'; // 큰 수에서 한자리씩 가져오기 
		if (d >= num)
		{
			d %= num;
		}
	}
	return d == 0;
}

int main()
{
	int q = 0;
	scanf("%s %d", P, &K);
	makePrime(K); // K보다 작은 암호 구하기, K가 소수일 경우 K가 소수리스트에 포함되면 안됨 
	for (int i = 0; i < pcnt; i++)
	{
		if (div(prime[i]))
		{
			q = prime[i];
			break;
		}
	}
	if (q>0) printf("BAD %d", q);
	else printf("GOOD");
}
*/
