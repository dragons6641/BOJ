#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 4000000

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

int solve(int k)
{
	// 초기 포인터 위치 설정
	// 이동은 오른쪽으로만!
	int lp = 0;
	int rp = 0;
	int cur_sum = prime[0];
	int result = 0;

	while (1)
	{
		// printf("lp : %d, rp : %d, cur_sum = %d\n", lp, rp, cur_sum);

		// 아직 부족하거나 같으면
		if (cur_sum <= k)
		{
			// 같으면
			if (cur_sum == k)
			{
				// 경우의 수에 추가
				result += 1;
			}

			// 마지막이면
			if (rp == prime.size() - 1)
			{
				// 더 이상 답이 없음, 끝
				break;
			}
			// 마지막이 아니면
			else
			{
				// 이동하고 더해준다
				rp += 1;
				cur_sum += prime[rp];
			}
		}
		// 넘치면
		else
		{
			// 마지막이면
			if (lp == prime.size() - 1)
			{
				// 더 이상 답이 없음, 끝
				break;
			}

			// 빼주고 이동한다
			cur_sum -= prime[lp];
			lp += 1;
		}
	}

	return result;
}

int main()
{
	int n = 0;
	int ans = 0;

	/*
	// 벡터 사이즈
	prime.reserve(MAX_N);

	// 입력 받기 전 미리 구하자!
	sieve(MAX_N);

	print_prime();
	*/

	scanf("%d", &n);

	// 예외 처리
	if (n == 1)
	{
		ans = 0;

		printf("%d\n", ans);
	}
	else
	{
		///*
		// 벡터 사이즈
		prime.reserve(n);

		// 입력 받고 나서 구하자!
		sieve(n);

		// print_prime();
		//*/
		ans = solve(n);

		printf("%d\n", ans);
	}

	return 0;
}

// 강사님 코드
/*
#include <stdio.h>
#define NMAX 4000000
int N;
bool isPrime[NMAX + 1];
int pcnt, prime[NMAX];

void makePrime(int n) // n보다 작거나 같은 소수 구하기 
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

	int s, e, ans, sum;
	sum = s = e = ans = 0;

	// pcnt 개의 소수 중 연속하여 더하였을 때 합이 N이 되는 경우 구하기
	// 2 point로 구현 
	while (s <= e&&e<pcnt)
	{
		// sum 이 N 미만이면 누적하여 더하기 
		while (e<pcnt && sum < N) sum += prime[e++];

		// 모든 소수를 다썼으나 sum이 N보다 작으면 종료 
		if (sum < N) break;

		// sum 이 N 초과면 누적하여 빼기 
		while (s<e && sum > N) sum -= prime[s++];

		// sum 이 N 이면 답 갱신, sum 에서 누적하여 빼기 
		if (sum == N)
		{
			ans++;
			sum -= prime[s++];
		}
	}
	printf("%d", ans);
}
*/
