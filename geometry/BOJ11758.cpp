#define _CRT_SECURE_NO_WARNINGS
#define CCW 3
#define ll long long

#include <cstdio>
#include <vector>

using namespace std;

// 기하는 2차원이니까 pair벡터 써보자!
// 정렬은 첫번째 인자 기준, 같으면 두번째 인자
// 즉 x좌표 기준 정렬, 같으면 y좌표 기준 정렬
// vector < pair <int, int> > pii(CCW, pair<int, int> (0, 0));
vector < pair <int, int> > pii;

void print_pii()
{
	printf("pii : \n");

	for (int i = 0; i < pii.size(); i++)
	{
		printf("x = %d, y = %d\n", pii[i].first, pii[i].second);
	}

	return;
}

ll ccw()
{
	ll result = 0;
	ll a = 0;
	ll b = 0;
	ll x0 = pii[0].first;
	ll y0 = pii[0].second;
	ll x1 = pii[1].first;
	ll y1 = pii[1].second;
	ll x2 = pii[2].first;
	ll y2 = pii[2].second;

	a = (x0 * y1) + (x1 * y2) + (x2 * y0);
	b = (x1 * y0) + (x2 * y1) + (x0 * y2);

	result = a - b;

	return result;
}

int main()
{
	int x = 0;
	int y = 0;
	ll ans = 0;

	pii.reserve(CCW);

	for (int i = 0; i < CCW; i++)
	{
		scanf("%d %d", &x, &y);

		pii.push_back(make_pair(x, y));

		// printf("size : %d\n", pii.size());
		// printf("x = %d, y = %d\n", pii[i].first, pii[i].second);
	}

	// print_pii();
	// printf("size : %d\n", pii.size());

	ans = ccw();

	if (ans > 0)
	{
		printf("1\n");
	}
	else if (ans < 0)
	{
		printf("-1\n");
	}
	else
	{
		printf("0\n");
	}

	return 0;
}

// 강사님 코드
/*
#include<stdio.h>

typedef long long ll;
typedef struct point {
	ll x, y;
	point operator-(point a) { return{ x - a.x,y - a.y }; }
} Point;

ll ccw(Point A, Point B)
{
	ll t = A.x*B.y - A.y*B.x;
	if (t == 0)return 0;
	if (t<0) return -1;
	else return 1;
}
ll ccw(Point C, Point A, Point B)
{
	return ccw(A - C, B - C);
}

int main()
{
	Point P1, P2, P3;
	scanf("%lld%lld%lld%lld%lld%lld", &P1.x, &P1.y, &P2.x, &P2.y, &P3.x, &P3.y);

	printf("%lld", ccw(P1, P2, P3));
}
*/
