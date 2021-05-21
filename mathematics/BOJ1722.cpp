#define _CRT_SECURE_NO_WARNINGS
#define ll long long
#define MAX_N 20

#include <stdio.h>
#include <vector>

using namespace std;

// 입력받은 순열을 저장할 벡터
vector <ll> input;

// 출력할 순열을 저장할 벡터
vector <ll> output;

// 팩토리얼을 저장할 벡터
vector <ll> fact;

// 사용 여부를 표시할 벡터
vector <bool> isUsed;

void print_fact()
{
	printf("fact : \n");

	for (int i = 1; i < fact.size(); i++)
	{
		printf("%lld\n", fact[i]);
	}

	return;
}

void print_input()
{
	for (int i = 1; i < input.size(); i++)
	{
		printf("%lld ", input[i]);
	}

	printf("\n");

	return;
}

void print_output()
{
	for (int i = 1; i < output.size(); i++)
	{
		printf("%lld ", output[i]);
	}

	printf("\n");

	return;
}

void dp(int k)
{
	// 초기값
	fact[0] = 1;
	fact[1] = 1;

	// 점화식
	for (int i = 2; i < fact.size(); i++)
	{
		fact[i] = i * fact[i - 1];
	}

	return;
}

// k번째 순열 구하기
void solve_1(ll n, ll k)
{
	int cnt = 0;
	ll pos = 0;

	// 다 만들때까지 반복
	while (output.size() <= n)
	{
		cnt = 0;

		// 들어갈 수 있는 건 1부터 n
		for (int i = 1; i <= n; i++)
		{
			// 아직 사용하지 않았다면
			if (!isUsed[i])
			{
				// 만들긴 한다는 말이다
				cnt += 1;

				// 위치값 수정
				pos = cnt * fact[n - output.size()];

				// printf("cnt = %d, n = %d, k = %lld, pos = %lld\n", cnt, n, k, pos);
				// print_output();

				// 첫 문자가 i번째 문자일 경우
				if (k <= pos)
				{
					// k만 바꿔주면 된다
					pos = (cnt - 1) * fact[n - output.size()];
					k -= pos;

					// 사용했다고 표시
					isUsed[i] = true;

					// 순열 목록에 추가
					output.push_back(i);

					break;
				}
			}
		}
	}

	return;
}

// 몇 번째 순열인지 구하기
ll solve_2(ll n)
{
	ll result = 1;
	ll pos = 0;
	int cur = 0;
	int cnt = 0;

	// 차례대로 하나씩 읽는다
	for (int i = 1; i <= n; i++)
	{
		cnt = 0;

		// 값을 불러오고
		cur = input[i];

		// 썼다고 표시
		isUsed[cur] = true;

		// 내 앞에서
		for (int j = 1; j < cur; j++)
		{
			// 안 쓴 것들만
			if (!isUsed[j])
			{
				// 세 준다
				cnt += 1;
			}
		}

		// printf("i = %d, n = %lld, cur = %d, cnt = %d\n", i, n, cur, cnt);

		pos = cnt * fact[n - i];

		result += pos;

		// printf("pos = %lld, result = %lld\n", pos, result);
	}

	return result;
}

int main()
{
	ll n = 0;
	int q = 0;
	ll k = 0;
	ll ans = 0;

	scanf("%lld", &n);

	// 벡터 크기 지정
	input.reserve(n + 1);
	output.reserve(n + 1);
	fact.resize(n + 1, 0);
	isUsed.resize(n + 1, false);

	// 쓰레기값 넣어두기
	input.push_back(0);
	output.push_back(0);

	// 팩토리얼은 미리 구하자!
	dp(n);

	// print_fact();

	// 문제 번호
	scanf("%d", &q);

	// k번째 순열 구하기
	if (q == 1)
	{
		scanf("%lld", &k);

		// k번째를 구하자
		solve_1(n, k);

		print_output();
	}
	// 몇 번째 순열인지 구하기
	else if (q == 2)
	{
		for (int i = 0; i < n; i++)
		{
			scanf("%lld", &k);

			// 일단 벡터에 저장
			input.push_back(k);
		}

		// print_input();

		// 몇 번째인지 구하자
		ans = solve_2(n);

		printf("%lld\n", ans);
	}
	// error
	else
	{

	}

	return 0;
}

// 강사님 코드
/*
#include <stdio.h>
int N, OP;
int A[21];
long long K, fac[21];
int ans[21], visit[21];

int main()
{
	scanf("%d%d", &N, &OP);
	fac[0] = 1;
	for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i;
	if (OP == 1)
	{
		scanf("%lld", &K);
		for (int i = 1; i <= N; i++) visit[i] = 0;
		for (int i = 1; i <= N; i++)
		{
			//printf("i[%d] ",i);
			for (int j = 1, cnt = 1; j <= N; j++)
			{
				if (visit[j])continue;
				if (K <= cnt*fac[N - i])
				{
					//printf("j[%d] K[%lld] cnt[%d]*fac[%d]=%lld\n",j,K,cnt,N-i,cnt*fac[N-i]);
					K -= ((cnt - 1)*fac[N - i]);
					ans[i] = j;
					visit[j] = 1;
					break;
				}
				cnt++;
			}
		}
		for (int i = 1; i <= N; i++) printf("%d ", ans[i]);
	}
	else if (OP == 2)
	{
		for (int i = 1; i <= N; i++) visit[i] = 0;
		K = 1;
		for (int i = 1; i <= N; i++)
		{
			scanf("%d", A + i);
			int cnt = 0;
			for (int j = 1; j<A[i]; j++) if (visit[j] == 0) cnt++;
			K += cnt*fac[N - i];
			visit[A[i]] = 1;
		}
		printf("%lld", K);
	}
}
*/
