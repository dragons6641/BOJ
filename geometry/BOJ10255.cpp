/*
#define _CRT_SECURE_NO_WARNINGS
#define CCW 3
#define MAX_N 3000
#define ANGLE 4
#define EDGE 2
#define MAX_X 10000
#define MAX_Y 10000
#define ll long long

#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

// 기하는 2차원이니까 pair벡터 써보자!
// 정렬은 첫번째 인자 기준, 같으면 두번째 인자
// 즉 x좌표 기준 정렬, 같으면 y좌표 기준 정렬
// vector < pair <int, int> > pii(CCW, pair<int, int> (0, 0));
vector < pair <double, double> > pii;
vector < pair <double, double> > pstart;
vector < pair <double, double> > pend;
vector < pair <double, double> > pmid;

// 교차 판별 여부 표시
vector <bool> check0;
vector <bool> check1;
vector <bool> check2;

void swap(double *x, double *y)
{
	double tmp = *x;
	*x = *y;
	*y = tmp;

	return;
}

void print_pii()
{
	printf("pii : \n");

	for (int i = 0; i < pii.size(); i++)
	{
		printf("x = %lf, y = %lf\n", pii[i].first, pii[i].second);
	}

	return;
}

void print_pstart()
{
	printf("start : \n");

	for (int i = 0; i < pstart.size(); i++)
	{
		printf("x = %lf, y = %lf\n", pstart[i].first, pstart[i].second);
	}

	return;
}

void print_pend()
{
	printf("end: \n");

	for (int i = 0; i < pend.size(); i++)
	{
		printf("x = %lf, y = %lf\n", pend[i].first, pend[i].second);
	}

	return;
}

void print_pmid()
{
	printf("pmid : \n");

	for (int i = 0; i < pmid.size(); i++)
	{
		printf("x = %lf, y = %lf\n", pmid[i].first, pmid[i].second);
	}

	return;
}

void print_check0()
{
	printf("check0 : ");

	for (int i = 0; i < check0.size(); i++)
	{
		if (check0[i])
		{
			printf("1 ");
		}
		else
		{
			printf("0 ");
		}
	}

	printf("\n");

	return;
}

void print_check1()
{
	printf("check1 : ");

	for (int i = 0; i < check1.size(); i++)
	{
		if (check1[i])
		{
			printf("1 ");
		}
		else
		{
			printf("0 ");
		}
	}

	printf("\n");

	return;
}

void print_check2()
{
	printf("check2 : ");

	for (int i = 0; i < check2.size(); i++)
	{
		if (check2[i])
		{
			printf("1 ");
		}
		else
		{
			printf("0 ");
		}
	}

	printf("\n");

	return;
}

double ccw(double x0, double y0, double x1, double y1, double x2, double y2)
{
	double result = 0;
	double a = 0;
	double b = 0;

	a = (x0 * y1) + (x1 * y2) + (x2 * y0);
	b = (x1 * y0) + (x2 * y1) + (x0 * y2);

	result = a - b;

	return result;
}

// 선분 정보를 입력으로 받는다 + 사각형의 무게중심
int solve(double ax, double ay, double bx, double by, double mx, double my)
{
	// 0, 1, 2, 4
	int result = 3;
	int cnt0 = 0;
	int cnt1 = 0;
	int cnt2 = 0;
	bool b0 = false;
	bool b1 = false;
	bool b2 = false;
	double a = 0;
	double b = 0;
	double c = 0;
	double d = 0;
	double cx = 0;
	double dx = 0;
	double cy = 0;
	double dy = 0;

	// 사각형의 각 변에 대해서
	for (int i = 0; i < pii.size(); i++)
	{
		// 선분 교차 판별 들어간다
		b0 = false;
		b1 = false;
		b2 = false;

		cx = pstart[i].first;
		cy = pstart[i].second;
		dx = pend[i].first;
		dy = pend[i].second;

		// printf("ax = %lf, ay = %lf, bx = %lf, by = %lf\n", ax, ay, bx, by);
		// printf("cx = %lf, cy = %lf, dx = %lf, dy = %lf\n", cx, cy, dx, dy);

		// 자신을 제외한 ccw 값 계산
		a = ccw(cx, cy, dx, dy, bx, by);
		b = ccw(cx, cy, dx, dy, ax, ay);
		c = ccw(ax, ay, bx, by, dx, dy);
		d = ccw(ax, ay, bx, by, cx, cy);

		// printf("a = %lf, b = %lf, c = %lf, d = %lf\n", a, b, c, d);

		// 평행하게 겹칠 경우
		if ((a || b) && (c || d))
		{
			b0 = false;
		}
		// 그렇지 않을 경우
		else
		{
			b0 = true;
			cnt0 += 1;
		}

		// ccw 값이 서로 다르다면
		// 즉, 서로 반대편에 있다면
		if (((a * b) <= 0) && ((c * d) <= 0))
		{
			// 일반적인 경우
			if (a || b || c || d)
			{
				// 교차한다
				b1 = true;
				cnt1 += 1;
			}
			// 단, 동일 직선상은 모든 ccw값이 0이므로
			// 좌표 기준으로 예외처리 반드시 해줘야함
			else
			{
				// 이러면 x좌표는 만나지 않는다
				if ((max(ax, bx) < min(cx, dx)) || (max(cx, dx) < min(ax, bx)))
				{
					// 교차하지 않는다
					b1 = false;
				}
				// 이러면 y좌표는 만나지 않는다
				else if ((max(ay, by) < min(cy, dy)) || (max(cy, dy) < min(ay, by)))
				{
					// 교차하지 않는다
					b1 = false;
				}
				// 겹치는 부분이 있다!
				else
				{
					// 교차한다
					b1 = true;
					cnt1 += 1;
				}
			}
		}
		// 서로 같은 편에 있다면
		else
		{
			// 교차하지 않는다
			b1 = false;
		}

		// 이건 등호 포함 안된 것
		// 서로 반대편에 있다면
		if (((a * b) < 0) && ((c * d) < 0))
		{
			// 교차한다
			b2 = true;
			cnt2 += 1;
		}
		// 서로 같은 편에 있다면
		else
		{
			// 교차하지 않는다
			b2 = false;
		}

		// 교차 여부 벡터에 표시
		check0.push_back(b0);
		check1.push_back(b1);
		check2.push_back(b2);
	}

	// print_check0();
	// print_check1();
	// print_check2();

	printf("cnt0 = %d, cnt1 = %d, cnt2 = %d\n", cnt0, cnt1, cnt2);

	// 여기서부터 답안체크
	// 특수 케이스
	// 포함되는 경우
	if (cnt0)
	{
		// 4. 교점이 무한개일 경우
		result = 4;
	}
	// 포함되지 않는 경우
	else
	{
		// 특수 케이스
		// 교차 선분이 없음
		if (cnt1 == 0)
		{
			// 1. 교점이 0개일 경우
			result = 0;
		}
		// 교차 선분 1개 이상인 경우
		else
		{
			// 여기서부터는 1개 혹은 2개
			// 즉 포함되는 경우는 없음
		}
	}

	// 1. 교점이 0개일 경우
	// 2. 교점이 1개일 경우
	// 3. 교점이 2개일 경우
	// 4. 교점이 무한개일 경우

	// 교점의 갯수 출력
	return result;
}

int main()
{
	int t = 0;
	int ans = 0;
	double z = 0;
	double w = 0;
	double x = 0;
	double y = 0;
	double u = 0;
	double v = 0;

	scanf("%d", &t);

	for (int i = 0; i < t; i++)
	{
		// printf("#%d\n", i + 1);

		// 벡터 크기
		pstart.reserve(ANGLE);
		pend.reserve(ANGLE);
		pmid.reserve(EDGE);
		pii.reserve(ANGLE);
		check0.reserve(ANGLE);
		check1.reserve(ANGLE);
		check2.reserve(ANGLE);

		// 사각형 입력
		scanf("%lf %lf", &x, &y);

		// pstart.push_back(make_pair(x, y));

		scanf("%lf %lf", &z, &w);

		// 중점 구하기
		u = (x + z) / 2;
		v = (y + w) / 2;

		// pend.push_back(make_pair(z, w));

		// pii.push_back(make_pair(z - x, w - y));

		// 1. 12시
		pstart.push_back(make_pair(x, w));
		pend.push_back(make_pair(z, w));
		pii.push_back(make_pair(z - x, 0));

		// 2. 3시
		pstart.push_back(make_pair(z, w));
		pend.push_back(make_pair(z, y));
		pii.push_back(make_pair(0, y - w));

		// 3. 6시
		pstart.push_back(make_pair(z, y));
		pend.push_back(make_pair(x, y));
		pii.push_back(make_pair(x - z, 0));

		// 4. 9시
		pstart.push_back(make_pair(x, y));
		pend.push_back(make_pair(x, w));
		pii.push_back(make_pair(0, w - y));

		// 선분 입력
		scanf("%lf %lf", &x, &y);
		scanf("%lf %lf", &z, &w);

		// 선분의 양 꼭지점과 중점을 각각 연결한 선분
		pmid.push_back(make_pair(x - u, y - v));
		pmid.push_back(make_pair(z - u, w - v));

		// printf("x = %lf, y = %lf, z = %lf, w = %lf\n", x, y, z, w);

		// printf("size : %d\n", pii.size());
		// printf("x = %d, y = %d\n", pii[i].first, pii[i].second);

		// print_pii();
		// print_pstart();
		// print_pend();
		// print_pmid();

		// 여기에 문제풀이
		ans = solve(x, y, z, w, u, v);

		printf("%d\n", ans);

		// 벡터 초기화
		pstart.clear();
		pend.clear();
		pmid.clear();
		pii.clear();
		check0.clear();
		check1.clear();
		check2.clear();
	}
	
	return 0;
}
*/

// 강사님 코드
#include<stdio.h>
#include<algorithm>

using namespace std;

typedef long long int lld;

struct Point {
	lld x, y;
	bool operator <(const Point a)const {
		return x == a.x ? y<a.y : x<a.x;
	}
	Point operator -(const Point a)const {
		return{ x - a.x,y - a.y };
	}
	bool operator ==(const Point a)const {
		return x == a.x&&y == a.y;
	}
}rect[5];

int ccw(Point A, Point B)
{
	lld t = A.x*B.y - A.y*B.x;
	return t<0 ? -1 : t>0;
}
int ccw(Point A, Point B, Point C) {
	return ccw(B - A, C - A);
}

bool iscross(Point A, Point B, Point C, Point D)
{
	int ab = ccw(A, B, C)*ccw(A, B, D);
	int cd = ccw(C, D, A)*ccw(C, D, B);

	if (ab == 0 && cd == 0) {
		if (B<A)swap(A, B);
		if (D<C)swap(C, D);
		if (B<C&&A<C || D<A&&C<A)return false;
	}
	return ab <= 0 && cd <= 0;
}
bool iscross_opt(Point A, Point B, Point C, Point D) {
	int ab = ccw(A, B, C)*ccw(A, B, D);
	int cd = ccw(C, D, A)*ccw(C, D, B);
	return ab<0 && cd <= 0;
}
bool iscross_opt2(Point A, Point B, Point C, Point D) {
	int ab = ccw(A, B, C)*ccw(A, B, D);
	int cd = ccw(C, D, A)*ccw(C, D, B);
	return ab == 0 && cd <= 0;
}

bool isoverlap(Point A, Point B, Point C, Point D) {
	if (!iscross(A, B, C, D))return false;
	if (ccw(A, B, C) != 0 || ccw(A, B, D) != 0)return false;

	if (B<A)swap(A, B);
	if (D<C)swap(C, D);
	return A<C&&C<B || C<A&&A<D || A<D&&D<B || C<B&&B<D || A == C&&B == D;
}

int main()
{
	int t, i, j;
	scanf("%d", &t);

	for (int tt = 1; tt <= t; tt++)
	{
		scanf("%lld%lld%lld%lld", &rect[0].x, &rect[0].y, &rect[2].x, &rect[2].y);
		rect[1] = { rect[0].x,rect[2].y };
		rect[3] = { rect[2].x,rect[0].y };
		rect[4] = { rect[0].x,rect[0].y };
		Point a, b;
		scanf("%lld%lld%lld%lld", &a.x, &a.y, &b.x, &b.y);
		if (b<a)swap(a, b);
		//1. 교점 없음
		for (i = 0; i<4; i++)
		{
			if (iscross(a, b, rect[i], rect[i + 1]))
				break;
		}
		if (i == 4)
		{
			puts("0");
			continue;
		}
		//2. 교점 무한
		for (i = 0; i<4; i++)
		{
			if (isoverlap(a, b, rect[i], rect[i + 1]))
				break;
		}
		if (i != 4)
		{
			puts("4");
			continue;
		}
		//3. 교점 개수 세기
		// - 사각형의 선분과 교차
		// - 사각형의 꼭지점과 교차
		int cnt = 0, cnt2 = 0;
		for (i = 0; i<4; i++)
		{
			if (iscross_opt(a, b, rect[i], rect[i + 1]))cnt++;
			if (iscross_opt2(a, b, rect[i], rect[i + 1]))cnt2++;
		}
		printf("%d\n", cnt + cnt2 / 2);
	}
	return 0;
}
