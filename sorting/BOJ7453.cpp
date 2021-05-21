#define _CRT_SECURE_NO_WARNINGS
#define ll long long

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main()
{
	// cin cout 속도 빠르게
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	ll n = 0;
	ll a = 0;
	ll b = 0;
	ll c = 0;
	ll d = 0;
	ll diff = 0;
	ll ans = 0;

	vector<ll> A;
	vector<ll> B;
	vector<ll> C;
	vector<ll> D;
	vector<ll> AB;
	vector<ll> CD;

	scanf("%lld", &n);

	A.reserve(n);
	B.reserve(n);
	C.reserve(n);
	D.reserve(n);
	AB.reserve(n * n);
	CD.reserve(n * n);

	for (int i = 0; i < n; i++)
	{
		scanf("%lld %lld %lld %lld", &a, &b, &c, &d);

		A.push_back(a);
		B.push_back(b);
		C.push_back(c);
		D.push_back(d);
	}

	// A와 B의 부분합
	for (int i = 0; i < n; i++)
	{
		a = A.at(i);

		for (int j = 0; j < n; j++)
		{
			b = B.at(j);

			AB.push_back(a + b);
		}
	}

	// C와 D의 부분합
	for (int i = 0; i < n; i++)
	{
		c = C.at(i);

		for (int j = 0; j < n; j++)
		{
			d = D.at(j);

			CD.push_back(c + d);
		}
	}

	// 퀵 정렬 시험 전에 외우고 가자
	sort(CD.begin(), CD.end());

	for (int i = 0; i < AB.size(); i++)
	{
		diff = -AB.at(i);

		vector<ll>::iterator up = upper_bound(CD.begin(), CD.end(), diff);
		vector<ll>::iterator lo = lower_bound(CD.begin(), CD.end(), diff);

		ans += (up - lo);
	}

	printf("%lld\n", ans);

	return 0;
}
