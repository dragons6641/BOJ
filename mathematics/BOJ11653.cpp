#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 10000000

#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

// 상태를 표시할 벡터
vector <int> check(MAX_N + 1);

// 소수를 모아둘 벡터
vector <int> prime;

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

void solve(int k)
{
	int tmp = (int)(sqrt(k)) + 1;
	int idx = 0;
	int cur = prime[idx];

	// 루트까지만 찾아보면 된다
	while (1)
	{
		cur = prime[idx];

		// 더 볼 필요 없으면
		if ((cur > tmp) || (k == 1))
		{
			// 1은 출력할 필요 없다
			if (k != 1)
			{
				printf("%d\n", k);
			}

			// 끝
			break;
		}

		// 나누어 떨어질 경우
		if ((k % cur) == 0)
		{
			// 출력 후
			printf("%d\n", cur);

			// 나눠준 몫으로 계속 수행
			k /= cur;
		}
		// 나누어 떨어지지 않을 경우
		else
		{
			// 다음 소수로
			idx += 1;
		}
	}

	return;
}

void new_solve(int k)
{
	int tmp = (int)(sqrt(k)) + 1;
	int cur = 2;

	// 루트까지만 찾아보면 된다
	while (1)
	{
		// 더 볼 필요 없으면
		if ((cur > tmp) || (k == 1))
		{
			// 1은 출력할 필요 없다
			if (k != 1)
			{
				printf("%d\n", k);
			}

			// 끝
			break;
		}

		// 나누어 떨어질 경우
		if ((k % cur) == 0)
		{
			// 출력 후
			printf("%d\n", cur);

			// 나눠준 몫으로 계속 수행
			k /= cur;
		}
		// 나누어 떨어지지 않을 경우
		else
		{
			// 다음 수로
			cur += 1;
		}
	}

	return;
}

int main()
{
	int n = 0;
	int ans = 0;

	// 벡터 사이즈
	// prime.reserve(MAX_N);

	// 입력 받기 전 미리 구하자!
	// sieve(MAX_N);

	// print_prime();

	scanf("%d", &n);

	// 예외 처리
	if (n == 1)
	{
		ans = 1;

		// printf("%d\n", ans);
	}
	else
	{
		// 벡터 사이즈
		// prime.reserve(n);

		// 입력 받고 나서 구하자!
		// sieve(n);

		// print_prime();

		// solve(n);

		new_solve(n);
	}

	return 0;
}

// 강사님 코드
/*
#include <cstdio>
#define NMAX 10000000
int N;
bool isPrime[NMAX + 1];
int pcnt, prime[NMAX];

void makePrime(int n)
{
	isPrime[0] = isPrime[1] = false;
	for (int i = 2; i <= n; i++) isPrime[i] = true;
	pcnt = 0;
	for (int i = 2; i <= n; i++)
	{
		if (isPrime[i])
		{
			prime[pcnt++] = i;
			for (int j = i + i; j <= n; j += i) isPrime[j] = false;
		}
	}

}
int main()
{
	scanf("%d", &N);
	makePrime(N);
	for (int i = 0; i < pcnt && prime[i] <= N; i++)
	{
		while (N%prime[i] == 0)
		{
			printf("%d\n", prime[i]);
			N /= prime[i];
		}
	}
}
*/
