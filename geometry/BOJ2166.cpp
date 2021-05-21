#define _CRT_SECURE_NO_WARNINGS
#define CCW 3
#define MAX_N 10000
#define ll long long

#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

// 기하는 2차원이니까 pair벡터 써보자!
// 정렬은 첫번째 인자 기준, 같으면 두번째 인자
// 즉 x좌표 기준 정렬, 같으면 y좌표 기준 정렬
// vector < pair <int, int> > pii(CCW, pair<int, int> (0, 0));
vector < pair <double, double> > pii;

void print_pii()
{
	printf("pii : \n");

	for (int i = 0; i < pii.size(); i++)
	{
		printf("x = %lf, y = %lf\n", pii[i].first, pii[i].second);
	}

	return;
}

double ccw(double x0, double y0, double x1, double y1, double x2, double y2)
{
	double result = 0;
	double a = 0;
	double b = 0;
	/*
	ll x0 = pii[0].first;
	ll y0 = pii[0].second;
	ll x1 = pii[1].first;
	ll y1 = pii[1].second;
	ll x2 = pii[2].first;
	ll y2 = pii[2].second;
	*/

	a = (x0 * y1) + (x1 * y2) + (x2 * y0);
	b = (x1 * y0) + (x2 * y1) + (x0 * y2);

	result = a - b;

	return result;
}

int main()
{
	int n = 0;
	double x = 0;
	double y = 0;
	double cur = 0;
	double ans = 0;

	scanf("%d", &n);

	pii.reserve(n);

	for (int i = 0; i < n; i++)
	{
		scanf("%lf %lf", &x, &y);

		pii.push_back(make_pair(x, y));

		// printf("size : %d\n", pii.size());
		// printf("x = %d, y = %d\n", pii[i].first, pii[i].second);
	}

	// print_pii();
	// printf("size : %d\n", pii.size());

	// 원점에서부터 두 점 씩 잡아서 ccw
	x = 0;
	y = 0;

	// 첫 점과 마지막 점 포함해서 먼저 ccw
	cur = ccw(x, y, pii.back().first, pii.back().second, pii.front().first, pii.front().second) / 2;
	ans += cur;

	// printf("cur = %lf\n", cur);

	for (int i = 1; i < pii.size(); i++)
	{
		cur = ccw(x, y, pii[i - 1].first, pii[i - 1].second, pii[i].first, pii[i].second) / 2;
		ans += cur;

		// printf("cur = %lf\n", cur);
	}

	printf("%.1lf\n", abs(ans));

	return 0;
}

// 강사님 코드
/*
#include<stdio.h>
#include <math.h>

typedef long long ll;
typedef struct point {
	ll x, y;
	point operator-(point a) { return{ x - a.x,y - a.y }; }
} Point;

ll ccw(Point A, Point B)
{
	return A.x*B.y - A.y*B.x;
}
ll ccw(Point C, Point A, Point B)
{
	return ccw(A - C, B - C);
}

Point P[10001];
int i, n;

int main()
{
	scanf("%d", &n);
	for (i = 0; i<n; i++) scanf("%lld%lld", &P[i].x, &P[i].y);

	ll result = 0;
	for (int i = 1; i<n - 1; i++) result += ccw(P[0], P[i], P[i + 1]);

	printf("%.1lf", fabs(result) / 2);
}
*/
