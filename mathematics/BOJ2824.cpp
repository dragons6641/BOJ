#define _CRT_SECURE_NO_WARNINGS
#define MAX_K 1000000000
#define MAX_DIGIT 10
#define ll long long

#include <cstdio>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// 상태를 표시할 벡터
// vector <int> check(MAX_K + 1);

// 소수를 모아둘 벡터
vector <int> prime;

// 소인수분해 결과 모은 벡터
vector <int> a;
vector <int> b;

// 우선순위 큐에 집어넣자
// priority_queue <int, vector <int>, greater<int> > pq;
// priority_queue <int, vector <int>, greater<int> > a;
// priority_queue <int, vector <int>, greater<int> > b;

// 넘었는지 체크
bool isExceeded = false;

void print_a()
{
	printf("a = ");

	for (int i = 0; i < a.size(); i++)
	{
		printf("%d ", a[i]);
	}

	printf("\n");

	return;
}

void print_b()
{
	printf("b = ");

	for (int i = 0; i < b.size(); i++)
	{
		printf("%d ", b[i]);
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

/*
void print_a()
{
printf("a : \n");

for (int i = 2; i < a.size(); i++)
{
if (a[i] > 0)
{
printf("%d ^ %d\n", i, a[i]);
}
}

printf("\n");

return;
}

void print_b()
{
printf("b : \n");

for (int i = 2; i < b.size(); i++)
{
if (b[i] > 0)
{
printf("%d ^ %d\n", i, b[i]);
}
}

printf("\n");

return;
}
*/

/*
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
*/
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

void new_solve(int k, char c)
{
	int tmp = (int)(sqrt(k)) + 1;
	int cur = 2;
	int top = 0;

	// 하나씩 받아서 넣어준다
	if (c == 'a')
	{
		// 루트까지만 찾아보면 된다
		while (1)
		{
			// 더 볼 필요 없으면
			if ((cur > tmp) || (k == 1))
			{
				// 1은 출력할 필요 없다
				if (k != 1)
				{
					// printf("%d\n", k);

					// pq.push(k);
					a.push_back(k);
				}

				// 끝
				break;
			}

			// 나누어 떨어질 경우
			if ((k % cur) == 0)
			{
				// 출력 후
				// printf("%d\n", cur);

				// pq.push(cur);
				a.push_back(cur);

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
	}
	// 하나씩 받으면서 나눠준다
	else if (c == 'b')
	{
		// 루트까지만 찾아보면 된다
		while (1)
		{
			// 더 볼 필요 없으면
			if ((cur > tmp) || (k == 1))
			{
				// 1은 출력할 필요 없다
				if (k != 1)
				{
					// printf("%d\n", k);

					// pq.push(k);
					b.push_back(k);
				}

				// 끝
				break;
			}

			// 나누어 떨어질 경우
			if ((k % cur) == 0)
			{
				// 출력 후
				// printf("%d\n", cur);

				// pq.push(cur);
				b.push_back(cur);

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
	}
	// error
	else
	{

	}

	return;
}

ll gcd()
{
	int cur_a = 0;
	int cur_b = 0;
	ll result = 1;

	/*
	// 처음 한 번
	// a큐에서 하나 뽑고
	if (a.size() != 0)
	{
		cur_a = a.top();
	}
	else
	{
		// break;
	}

	// b큐에서 하나 뽑고
	if (b.size() != 0)
	{
		cur_b = b.top();
	}
	else
	{
		// break;
	}

	// 같을때만 실행
	if (cur_a == cur_b)
	{
		// 값을 초과하면
		if (result * (ll)(cur_a) > MAX_K)
		{
			// 초과했다고 표시
			isExceeded = true;

			// 일단 곱해주고
			result *= (ll)(cur_a);

			// 나머지 연산
			result %= MAX_K;
		}
		// 아니면 그냥 곱해준다
		else
		{
			result *= (ll)(cur_a);
		}

		// printf("result = %lld\n", result);
	}

	// 나머지
	while (1)
	{
		if (a.empty() || b.empty())
		{
			break;
		}
		else
		{
			if (a.size() != 0)
			{
				a.pop();
			}

			if (b.size() != 0)
			{
				b.pop();
			}
		}

		// a큐에서 하나 뽑고
		if (a.size() != 0)
		{
			cur_a = a.top();
		}
		else
		{
			// break;
		}

		// b큐에서 하나 뽑고
		if (b.size() != 0)
		{
			cur_b = b.top();
		}
		else
		{
			// break;
		}

		// printf("before !!! a = %d, b = %d\n", cur_a, cur_b);
		// printf("a.size() = %d, b.size() = %d\n", a.size(), b.size());

		// a가 더 크면
		if (cur_a > cur_b)
		{
			// 같아질 때 까지 b에서 pop
			while (1)
			{
				// b큐에서 하나 뽑고
				if (b.size() != 0)
				{
					b.pop();
					cur_b = b.top();

					// 만약 뒤집히면 끝
					if (cur_a <= cur_b)
					{
						break;
					}
				}
				else
				{
					break;
				}
			}
		}
		// b가 더 크면
		else if (cur_a < cur_b)
		{
			// 같아질 때 까지 a에서 pop
			while (1)
			{
				// b큐에서 하나 뽑고
				if (a.size() != 0)
				{
					a.pop();
					cur_a = a.top();

					// 만약 뒤집히면 끝
					if (cur_a >= cur_b)
					{
						break;
					}
				}
				else
				{
					break;
				}
			}
		}

		// printf("after !!! a = %d, b = %d\n", cur_a, cur_b);
		// printf("a.size() = %d, b.size() = %d\n", a.size(), b.size());

		// 같을때만 실행
		if (cur_a == cur_b)
		{
			// 값을 초과하면
			if (result * (ll)(cur_a) > MAX_K)
			{
				// 초과했다고 표시
				isExceeded = true;

				// 일단 곱해주고
				result *= (ll)(cur_a);

				// 나머지 연산
				result %= MAX_K;
			}
			// 아니면 그냥 곱해준다
			else
			{
				result *= (ll)(cur_a);
			}

			// printf("result = %lld\n", result);
		}
	}
	*/

	return result;
}

int check_digit(ll k)
{
	int result = 0;

	// k가 0이면 종료
	while (k > 0)
	{
		// 10으로 한번 나눠주고
		k /= 10;
		// 자릿수에 한번 더해준다
		result += 1;
	}

	return result;
}

ll new_gcd()
{
	ll result = 1; // 곱셈이니까 1로 초기화!
	int ap = 0;
	int bp = 0;

	while (1)
	{
		if (ap >= a.size())
		{
			break;
		}

		if (bp >= b.size())
		{
			break;
		}

		// printf("a = %d, b = %d\n", a[ap], b[bp]);

		// a가 더 큰 소수이면
		if (a[ap] > b[bp])
		{
			// b를 맞춰준다
			bp += 1;
		}
		// b가 더 큰 소수이면
		else if (a[ap] < b[bp])
		{
			// a를 맞춰준다
			ap += 1;
		}
		// 같으면
		else
		{
			// 값을 초과하면
			if (result * (ll)(a[ap]) >= MAX_K)
			{
				// 초과했다고 표시
				isExceeded = true;

				// 일단 곱해주고
				result *= (ll)(a[ap]);

				// 나머지 연산
				result %= MAX_K;
			}
			// 아니면 그냥 곱해준다
			else
			{
				result *= (ll)(a[ap]);
			}

			// 하나씩 증가
			ap += 1;
			bp += 1;
		}
	}

	return result;
}

int main()
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);
	// freopen("input4.txt", "r", stdin);
	// freopen("input5.txt", "r", stdin);
	// freopen("input6.txt", "r", stdin);
	// freopen("input7.txt", "r", stdin);

	int n = 0;
	int m = 0;
	ll ans = 0;
	int tmp = 0;
	int digit = 0;

	// 벡터 사이즈
	// prime.reserve(MAX_N);

	// 입력 받기 전 미리 구하자!
	// sieve(MAX_N);

	// print_prime();

	scanf("%d", &n);

	// 벡터 사이즈
	a.reserve(n + 1);
	b.reserve(n + 1);

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &tmp);

		// 1은 안해도 된다
		if (tmp > 1)
		{
			new_solve(tmp, 'a');

			// a.push_back(tmp);
		}
	}

	scanf("%d", &m);

	for (int i = 0; i < m; i++)
	{
		scanf("%d", &tmp);

		// 1은 안해도 된다
		if (tmp > 1)
		{
			new_solve(tmp, 'b');

			// b.push_back(tmp);
		}
	}

	// ans = gcd();

	// 오름차순 정렬
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());

	// print_a();
	// print_b();

	ans = new_gcd();

	// ans = 1234567;
	// isExceeded = true;

	// 초과했다면
	if (isExceeded)
	{
		// 자릿수 확인
		digit = check_digit(ans);

		// 빈 갯수만큼
		for (int i = 0; i < MAX_DIGIT - digit - 1; i++)
		{
			// 0 출력
			printf("%d", 0);
		}

		// 뒤에 답 출력
		if (ans != 0)
		{
			printf("%lld\n", ans);
		}
	}
	// 초과하지 않았다면
	else
	{
		// 그냥 출력
		if (ans != 0)
		{
			printf("%lld\n", ans);
		}
	}

	// print_a();
	// print_b();

	return 0;
}
