#define _CRT_SECURE_NO_WARNINGS
#define ll long long
#define MAX_N 100
#define MAX_M 100
#define MAX_K 1000000000

#include <stdio.h>
#include <vector>

using namespace std;

// 문자열을 저장할 벡터
vector <char> ans;

ll n = 0;
ll m = 0;
int k = 0;
int cnt = 0;

bool isFinished = false;
bool isError = false;

// 조합 DP 배열
vector <vector <ll> > dp;

ll factorial(ll x)
{
	if (x == 1)
	{
		return 1;
	}
	else
	{
		return x * factorial(x - 1);
	}

	return 0;
}

ll def_nCk(ll n, ll k)
{
	ll a = factorial(n);
	ll b = factorial(n - k);
	ll c = factorial(k);
	ll result = a / (b * c);

	return result;
}

void make_dp(ll x)
{
	for (int i = 0; i < dp.size(); i++)
	{
		for (int j = 0; j <= i; j++)
		{
			// printf("i = %d, j = %d\n", i, j);

			if ((j == 0) || (j == i))
			{
				dp[i][j] = 1;
			}
			else
			{
				// 원래는 이렇게 하면 된다
				dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];

				// k보다 큰 값은
				if (dp[i][j] > MAX_K)
				{
					// k보다 크게만 저장해 주면 된다!
					dp[i][j] = MAX_K + 1;
				}
			}

			// printf("%lld ", dp[i][j]);
		}

		// printf("\n");
	}

	return;
}

void print_ans()
{
	for (int i = 0; i < ans.size(); i++)
	{
		printf("%c", ans[i]);
	}

	printf("\n");

	return;
}

void backtrack(int a, int z)
{
	// printf("a = %d, z = %d\n", a, z);
	// print_ans();

	// 끝났으면 종료
	if (isFinished)
	{
		return;
	}

	// 문자열을 모두 다 썼으면
	if (ans.size() == (n + m))
	{
		// 하나 완성된 것
		cnt += 1;

		// 목표한 값 찾았으면
		if (cnt == k)
		{
			// 끝났다고 표시하고 출력 후 종료
			isFinished = true;

			print_ans();

			return;
		}
	}

	// 아직 쓸 a가 남았으면
	if (a < n)
	{
		ans.push_back('a');

		backtrack(a + 1, z);

		ans.pop_back();
	}

	// 아직 쓸 z가 남았으면
	if (z < m)
	{
		ans.push_back('z');

		backtrack(a, z + 1);

		ans.pop_back();
	}

	return;
}

void solve(ll a, ll z, ll pos)
{
	while ((a != 0) || (z != 0))
	{
		ll nCk = dp[a + z - 1][z];

		// printf("a = %lld, z = %lld, pos = %lld, nCk = %lld\n", a, z, pos, nCk);

		// 첫 문자가 a일 경우
		if (pos <= nCk)
		{
			// printf("DOWN\n");

			// a를 이미 다 썼다면
			if (a == 0)
			{
				// 불가능
				isError = true;

				break;
			}
			// a가 아직 남아있다면
			else
			{
				// printf("WRITE\n");

				// a는 하나 사용함
				a -= 1;

				// 기록한다
				ans.push_back('a');
			}
		}
		// 첫 문자가 z일 경우
		else
		{
			// printf("UP\n");

			// z를 이미 다 썼다면
			if (z == 0)
			{
				// 불가능
				isError = true;

				break;
			}
			// a가 아직 남아있다면
			else
			{
				// printf("WRITE\n");

				// 위치 갱신
				pos -= nCk;

				// z는 하나 사용함
				z -= 1;

				// 기록한다
				ans.push_back('z');
			}
		}

		// print_ans();
	}

	return;
}

int main()
{
	ll ans = 0;

	vector <ll> tmp;

	scanf("%lld %lld %d", &n, &m, &k);

	tmp.resize(n + m + 1);

	// 여기서 size 쓰면 안된다!
	// 초기화도 미리 해주면 안된다!
	for (int i = 0; i <= n + m; i++)
	{
		// printf("i = %d\n", i);

		dp.push_back(tmp);
	}

	// printf("%d %d\n", dp.size(), dp[0].size());

	// printf("HERE~\n");

	make_dp(n + m);

	solve(n, m, k);

	// 못 찾았으면
	if (isError)
	{
		printf("-1\n");
	}
	// 찾았으면
	else
	{
		print_ans();
	}

	/*
	backtrack(0, 0);

	// 끝났을 때
	if (isFinished)
	{
		// 이미 출력해줬다
	}
	// 부족
	else
	{
		printf("-1\n");
	}
	*/

	return 0;
}

// 강사님 코드
/*
#include<stdio.h>

int n, m, k, ncr[201][201], N;
int ans[201];

int main()
{
	int i, j;
	scanf("%d%d%d", &n, &m, &k);

	for (i = 0; i <= n + m; i++)
	{
		ncr[i][0] = 1;
		for (j = 1; j <= i; j++)
		{
			ncr[i][j] = ncr[i - 1][j - 1] + ncr[i - 1][j];
			if (ncr[i][j]>k)
				ncr[i][j] = k + 1;
		}
	}

	N = n + m;
	if (ncr[N][m] < k)
	{
		printf("-1");
		return 0;
	}

	for (i = 1; i <= N; i++)
	{
		// 앞자리에 0을 배치하면 n+m-1칸에 1을 m개 배치하게 된다.
		if (ncr[n + m - 1][m] < k) //0을 배치했는데 k번째에 도달하지 못한 경우
		{
			k -= ncr[n + m - 1][m];
			m--;//1을 하나 씀
			ans[i] = 1; // 'z'
		}
		else
		{
			ans[i] = 0;
			n--;//0을 하나 씀
		}
	}

	for (i = 1; i <= N; i++)
	{
		printf("%c", ans[i] == 0 ? 'a' : 'z');
	}

	return 0;
}
*/
