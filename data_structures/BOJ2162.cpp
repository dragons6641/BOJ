#define _CRT_SECURE_NO_WARNINGS
#define CCW 3
#define MAX_N 3000
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

// union-find
// 부모를 저장
vector <int> parent;

// 상태를 기록
vector <int> check;

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

void Print_Parent()
{
	printf("parent : ");

	for (int i = 0; i < parent.size(); i++)
	{
		printf("%d ", parent[i]);
	}

	printf("\n");

	return;
}

void Print_Check()
{
	printf("check : ");

	for (int i = 0; i < check.size(); i++)
	{
		printf("%d ", check[i]);
	}

	printf("\n");

	return;
}

void Init()
{
	for (int i = 0; i < parent.size(); i++)
	{
		parent[i] = i;
	}

	return;
}

int Find(int z)
{
	if (parent[z] == z)
	{
		return z;
	}
	else
	{
		parent[z] = Find(parent[z]);

		return parent[z];
	}

	return -1;
}

void Union(int x, int y)
{
	int xRoot = -1;
	int yRoot = -1;

	xRoot = Find(x);
	yRoot = Find(y);

	parent[xRoot] = yRoot;

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
	int cur = 0;
	int group = 0;
	int edge = 0;
	double z = 0;
	double w = 0;
	double x = 0;
	double y = 0;
	double ans = 0;
	double a = 0;
	double b = 0; 
	double c = 0;
	double d = 0;
	double ax = 0;
	double bx = 0;
	double cx = 0;
	double dx = 0;
	double ay = 0;
	double by = 0;
	double cy = 0;
	double dy = 0;

	scanf("%d", &n);

	// 벡터 크기
	pii.reserve(n);
	parent.resize(n, 0);
	check.resize(n, 0);

	// 부모 벡터 초기화
	Init();

	for (int i = 0; i < n; i++)
	{
		scanf("%lf %lf", &x, &y);

		pstart.push_back(make_pair(x, y));

		scanf("%lf %lf", &z, &w);

		pend.push_back(make_pair(z, w));

		pii.push_back(make_pair(z - x, w - y));

		// printf("size : %d\n", pii.size());
		// printf("x = %d, y = %d\n", pii[i].first, pii[i].second);
	}

	// Print_Parent();
	// print_pii();
	// print_pstart();
	// print_pend();

	for (int i = 0; i < parent.size(); i++)
	// 거꾸로 돌려보자
	// for (int i = parent.size() - 1; i >= 0; i--)
	{
		ax = pstart[i].first;
		ay = pstart[i].second;
		bx = pend[i].first;
		by = pend[i].second;

		// printf("ax = %lf, ay = %lf, bx = %lf, by = %lf\n", ax, ay, bx, by);

		for (int j = i + 1; j < parent.size(); j++)
		// 거꾸로 돌려보자
		// for (int j = parent.size() - 1; j > i; j--)
		{
			cx = pstart[j].first;
			cy = pstart[j].second;
			dx = pend[j].first;
			dy = pend[j].second;

			// printf("cx = %lf, cy = %lf, dx = %lf, dy = %lf\n", cx, cy, dx, dy);

			// 자신을 제외한 ccw 값 계산
			a = ccw(cx, cy, dx, dy, bx, by);
			b = ccw(cx, cy, dx, dy, ax, ay);
			c = ccw(ax, ay, bx, by, dx, dy);
			d = ccw(ax, ay, bx, by, cx, cy);

			// printf("a = %lf, b = %lf, c = %lf, d = %lf\n", a, b, c, d);

			// ccw 값이 서로 다르다면
			// 즉, 서로 반대편에 있다면
			if (((a * b) <= 0) && ((c * d) <= 0))
			{
				// 일반적인 경우
				if (a || b || c || d)
				{
					// 같은 그룹이므로 합친다
					// Find(i);
					// Find(j);
					Union(i, j);
				}
				// 단, 동일 직선상은 모든 ccw값이 0이므로
				// 좌표 기준으로 예외처리 반드시 해줘야함
				else
				{
					// 이러면 x좌표는 만나지 않는다
					if ((max(ax, bx) < min(cx, dx)) || (max(cx, dx) < min(ax, bx)))
					{
						// 즉 교차하지 않는다
						// 서로 다른 그룹이므로 합치지 않는다
						continue;
					}
					// 이러면 y좌표는 만나지 않는다
					else if ((max(ay, by) < min(cy, dy)) || (max(cy, dy) < min(ay, by)))
					{
						// 즉 교차하지 않는다
						// 서로 다른 그룹이므로 합치지 않는다
						continue;
					}
					// 겹치는 부분이 있다!
					else
					{
						// 같은 그룹이므로 합친다
						// Find(i);
						// Find(j);
						Union(i, j);
					}
				}
			}
		}
	}

	// 한번 정리하자!
	for (int i = 0; i < parent.size(); i++)
	{
		Find(i);
	}

	// 그룹 상태 확인
	for (int i = 0; i < parent.size(); i++)
	{
		cur = parent[i];

		// printf("cur = %d\n", cur);

		check[cur] += 1;
	}

	// 답안 생성
	for (int i = 0; i < check.size(); i++)
	{
		cur = check[i];

		// 그룹이 있긴 하면
		if (check[i])
		{
			// 그룹 갯수에 추가
			group += 1;
		}

		// 가장 큰 그룹이라면
		if (cur > edge)
		{
			// 바꿔준다
			edge = cur;
		}
	}

	// Print_Parent();
	// Print_Check();

	printf("%d\n", group);
	printf("%d\n", edge);

	return 0;
}

// 강사님 코드
/*
#include "stdio.h"
#include <algorithm>
using namespace std;
#define MAXN 3000
#define max(x, y) ((x)>(y)?(x):(y))
int N, M;
int r[MAXN + 1];
int cnt[MAXN + 1];
struct Line {
	int x1, y1, x2, y2;
} L[MAXN + 1];
int idx = 0;

int getParent(int a) {
	if (r[a] == a) return a;
	return r[a] = getParent(r[a]);
}
void join(int a, int b) {
	r[getParent(a)] = getParent(b);
}
int ccw(int x1, int y1, int x2, int y2, int x3, int y3) {
	int val = (x1*y2 + x2*y3 + x3*y1) - (y1*x2 + y2*x3 + y3*x1);
	return val > 0 ? 1 : (val < 0 ? -1 : 0);
}
bool isCross(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
	if (ccw(x1, y1, x2, y2, x3, y3) * ccw(x1, y1, x2, y2, x4, y4) <= 0 &&
		ccw(x3, y3, x4, y4, x1, y1) * ccw(x3, y3, x4, y4, x2, y2) <= 0) {
		if ((x1 > x3 && x1 > x4 && x2 > x3 && x2 > x4) ||
			(x1 < x3 && x1 < x4 && x2 < x3 && x2 < x4)) return false;
		if ((y1 > y3 && y1 > y4 && y2 > y3 && y2 > y4) ||
			(y1 < y3 && y1 < y4 && y2 < y3 && y2 < y4)) return false;
		return true;
	}
	return false;
}
int main()
{
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) r[i] = i;
	for (int i = 1; i <= N; i++) {
		scanf("%d%d%d%d", &L[i].x1, &L[i].y1, &L[i].x2, &L[i].y2);
		for (int j = 1; j < i; j++)
			if (isCross(L[i].x1, L[i].y1, L[i].x2, L[i].y2, L[j].x1, L[j].y1, L[j].x2, L[j].y2))
				join(i, j);
	}
	for (int i = 1; i <= N; i++) cnt[getParent(i)]++;
	int group_count = 0, max_member = 0;
	for (int i = 1; i <= N; i++) {
		if (cnt[i]) group_count++;
		max_member = max(max_member, cnt[i]);
	}
	printf("%d\n%d\n", group_count, max_member);
}
*/
