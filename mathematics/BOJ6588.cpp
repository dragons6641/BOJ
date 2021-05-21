#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 1000000

#include <stdio.h>
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
	int lp = 0;
	int rp = prime.size() - 1;
	int ans = prime[lp] + prime[rp];
	
	int left = 0;
	int right = prime.size() - 1;
	int mid = (left + right) / 2;

	// 1. binary search

	while (left <= right)
	{
		mid = (left + right) / 2;

		// printf("mid : %d\n", prime[mid]);

		// 단 하나의 값을 찾았다면
		if (left == right)
		{
			// 큰 거면
			if (prime[mid] >= k)
			{
				// 찾아준 범위로 갱신
				rp = right;
			}
			// 작은 거면
			else 
			{
				// 찾아준 범위로 갱신
				rp = right + 1;
			}
		}

		// 아직 값이 크다면
		if (prime[mid] > k)
		{
			// 작은 쪽으로
			right = mid - 1;
		}
		// 오히려 값이 작다면
		else if (prime[mid] < k)
		{
			// 큰 쪽으로
			left = mid + 1;
		}
		// 같다면
		else
		{
			// 찾아준 범위로 갱신
			rp = right;

			break;
		}
	}

	// printf("lp = %d, rp : %d\n", prime[lp], prime[rp]);

	// 2. two pointer
	while (1)
	{
		ans = prime[lp] + prime[rp];

		// 아직 차이가 더 크다면
		if (ans > k)
		{
			// 합이 줄어야 함
			rp -= 1;
		}
		// 아직 차이가 더 작다면
		else if (ans < k)
		{
			// 합이 늘어야 함
			lp += 1;
		}
		// 찾았다면
		else
		{
			// 출력
			printf("%d = %d + %d\n", k, prime[lp], prime[rp]);

			break;
		}

		// 불가능한 경우
		if (lp > rp)
		{
			printf("Goldbach's conjecture is wrong.\n");

			break;
		}
	}

	return;
}

int main()
{
	int n = 0;

	// 벡터 사이즈
	prime.reserve(MAX_N);

	// 입력 받기 전 미리 구하자!
	sieve(MAX_N);

	// print_prime();

	while (1)
	{
		scanf("%d", &n);

		if (n == 0)
		{
			break;
		}
		else
		{
			solve(n);
		}
	}

	return 0;
}

// 강사님 코드
/*
#include <cstdio>

int N;
bool isPrime[1000001];
int prime[1000001], prime_cnt;

int main()
{
	isPrime[0] = isPrime[1] = false;
	for (int i = 2; i <= 1000000; i++) isPrime[i] = true;

	prime_cnt = 0;
	for (int i = 2; i <= 1000000; i++)
	{
		if (!isPrime[i]) continue;
		// 소수발견 
		prime[prime_cnt++] = i; // 소수리스트 추가 
		for (int j = i + i; j <= 1000000; j += i) isPrime[j] = false;
	}

	while (true)
	{
		scanf("%d", &N);
		if (N == 0) break;

		int s = -1, e = -1;
		for (int i = 0; i < prime_cnt; i++)
		{
			// prime1 + prime2 = N => N - prime1 이 소수이면 만족 
			if (isPrime[N - prime[i]])
			{
				s = prime[i];
				e = N - prime[i];
				break;
			}
		}
		if (s > -1) printf("%d = %d + %d\n", N, s, e);
		else printf("Goldbach's conjecture is wrong.\n");
	}
}
*/
