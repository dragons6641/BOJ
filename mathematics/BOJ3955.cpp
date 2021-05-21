#define _CRT_SECURE_NO_WARNINGS
#define ll long long
#define MAX_ANS 1000000000

#include <stdio.h>
#include <vector>

using namespace std;

typedef struct node
{
	ll s = 0;
	ll t = 0;
	ll r = 0;
	ll q = 0;
}
NODE;

ll ans = 0;

ll euclid(ll m, ll n)
{
	ll cnt = 0;
	ll result = 0;

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
		cur.r = v[cnt].r % v[cnt + 1].r;

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

			// printf("%lld %lld %lld %lld\n", cur.s, cur.t, cur.r, cur.q);

			result = cur.r;
			ans = cur.t;

			break;
		}

		// 아니면
		else
		{
			// 계속
			v.push_back(cur);

			// printf("%lld %lld %lld %lld\n", cur.s, cur.t, cur.r, cur.q);

			cnt += 1;
		}
	}

	return result;
}

int my_main()
{
	ll t = 0;
	ll k = 0; // 사람 수
	ll c = 0; // 한 봉지에 들어 있는 사탕 수
	ll gcd = 0;

	scanf("%lld", &t);

	for (int i = 0; i < t; i++)
	{
		ans = 0;

		scanf("%lld %lld", &k, &c);

		// 예외 처리
		// 사람이 1명이면
		if (k == 1)
		{
			///*
			// 사탕 수가 1개일 경우에만
			if (c == 1)
			{
				// 하나 더 사고
				ans = 2;
			}
			// 나머지는
			else
			{
				// 무조건 줄 수 있다
				ans = 1;
			}
			//*/

			// ans = 1;

			printf("%lld\n", ans);

			// 다음으로
			continue;
		}

		// 한 봉지에 들어 있는 사탕 수가 1개이면
		else if (c == 1)
		{
			// (사람 수 + 1) 만큼만 사면 됨
			ans = k + 1;

			// 값을 초과하면 안된다
			if (ans> MAX_ANS)
			{
				printf("IMPOSSIBLE\n");
			}
			// 나머지는 가능
			else
			{
				ans = k + 1;

				printf("%lld\n", ans);
			}

			// 다음으로
			continue;
		}

		// 일반적인 경우
		if (k > c)
		{
			gcd = euclid(k, c);
		}
		else
		{
			gcd = euclid(c, k);
		}

		// printf("gcd = %lld\n", gcd);

		// 가능한 경우
		if (gcd == 1)
		{
			// 값을 초과하면 안된다
			if (ans > MAX_ANS)
			{
				printf("IMPOSSIBLE\n");
			}
			// 양수여야 한다
			else if (ans > 0)
			{
				printf("%lld\n", ans);
			}
			// 음수라면
			else
			{
				// 양수로 만들어 준다
				while (ans < 0)
				{
					ans += k;
				}

				// 값을 초과하면 안된다
				if (ans > MAX_ANS)
				{
					printf("IMPOSSIBLE\n");
				}
				else
				{
					printf("%lld\n", ans);
				}
			}
		}
		// 불가능한 경우
		else
		{
			printf("IMPOSSIBLE\n");
		}
	}

	return 0;
}

// 강사님 코드
///*
#include <iostream>

using namespace std;

#define MAX 1000000000ll

long gcd(long a, long b)
{
	if (b == 0ll)
		return a;
	else
		return gcd(b, a%b);
}

int main()
{
	int t;
	cin >> t;
	long k, c;
	for (int i = 0; i < t; i++)
	{
		cin >> k >> c; // -kx + cY = 1 꼴의 방정식
		long g = 1ll;

		if (k > c)
			g = gcd(k, c);
		else
			g = gcd(c, k);

		if (g != 1ll)
		{
			cout << "IMPOSSIBLE" << '\n';
		}
		else if (k == 1ll)
		{
			if (c == 1ll) cout << 2 << "\n";
			else cout << 1 << '\n';
		}
		else if (c == 1)
		{
			if (k == MAX)
				cout << "IMPOSSIBLE\n";
			else
				cout << (k + 1) << "\n";
		}


		else
		{
			long y2, y1, y;
			long x2, x1, x;
			long r2, r1, r;
			long q;

			y2 = 1ll;
			x1 = -1ll; // -kx + cy = 1꼴이므로
			y1 = x2 = 0;
			r2 = c;
			r1 = k;
			x = y = r = q = 0;
			while (r2%r1 != 0)
			{
				// 연산
				q = r2 / r1;
				r = r2 - r1*q;
				x = x2 - x1*q;
				y = y2 - y1*q;
				// 다음 바퀴를 위한 세팅
				x2 = x1;
				y2 = y1;
				r2 = r1;
				x1 = x;
				y1 = y;
				r1 = r;
			}
			while (y<0ll)
			{
				y += k;
				x -= c;
			}

			if (y>MAX)
				cout << "IMPOSSIBLE" << '\n';
			else
				cout << y << '\n';
		}
	}

	return 0;
}
//*/
