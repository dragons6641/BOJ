#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 100000

#include <stdio.h>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

// 입력 저장 벡터
vector <pair <double, double> > pii;

// 볼록 껍질 목록 만드는 데 사용할 스택
// 인덱스가 들어간다
stack <int> us;
stack <int> ds;

void print_pii()
{
	printf("pii : \n");

	for (int i = 0; i < pii.size(); i++)
	{
		printf("x = %lf, y = %lf\n", pii[i].first, pii[i].second);
	}

	return;
}

void print_us()
{
	printf("us : ");

	while (!us.empty())
	{
		printf("%d ", us.top());
		us.pop();
	}

	printf("\n");

	return;
}

void print_ds()
{
	printf("ds : ");

	while (!ds.empty())
	{
		printf("%d ", ds.top());
		ds.pop();
	}

	printf("\n");

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

int solve()
{
	int result = 0;
	int f = 0;
	int s = 1;
	double cur = 0;

	// 먼저 반시계방향 확인
	// 시작점과 그 다음 점도 넣어둔다
	us.push(f);
	us.push(s);

	// 세 번째 점부터 볼록 껍질인지 확인
	for (int i = 2; i < pii.size(); i++)
	{
		while (us.size() > 1)
		{
			s = us.top();
			us.pop();

			f = us.top();

			// printf("f = %d, s = %d, i = %d\n", f, s, i);
			// printf("(%lf, %lf), (%lf, %lf), (%lf, %lf)\n", pii[f].first, pii[f].second, pii[s].first, pii[s].second, pii[i].first, pii[i].second);

			// first, second, i
			cur = ccw(pii[f].first, pii[f].second, pii[s].first, pii[s].second, pii[i].first, pii[i].second);

			// printf("ccw = %lf\n", cur);

			// 반시계 방향이라면
			if (cur > 0)
			{
				// 이 조합은 맞다
				us.push(s);

				break;
			}
		}

		us.push(i);
	}

	f = 0;
	s = 1;

	// 다음 시계방향 확인
	// 시작점과 그 다음 점도 넣어둔다
	ds.push(f);
	ds.push(s);

	// 세 번째 점부터 볼록 껍질인지 확인
	for (int i = 2; i < pii.size(); i++)
	{
		while (ds.size() > 1)
		{
			s = ds.top();
			ds.pop();

			f = ds.top();

			// printf("f = %d, s = %d, i = %d\n", f, s, i);
			// printf("(%lf, %lf), (%lf, %lf), (%lf, %lf)\n", pii[f].first, pii[f].second, pii[s].first, pii[s].second, pii[i].first, pii[i].second);

			// first, second, i
			cur = ccw(pii[f].first, pii[f].second, pii[s].first, pii[s].second, pii[i].first, pii[i].second);

			// printf("ccw = %lf\n", cur);

			// 시계 방향이라면
			if (cur < 0)
			{
				// 이 조합은 맞다
				ds.push(s);

				break;
			}
		}

		ds.push(i);
	}

	// 첫 점과 끝 점은 두 번 들어가 있다!
	result = us.size() + ds.size() - 2;

	// printf("size : %d\n", us.size());
	// print_us();

	// printf("size : %d\n", ds.size());
	// print_ds();

	return result;
}

int main()
{
	int n = 0;
	int ans = 0;
	double x = 0;
	double y = 0;

	scanf("%d", &n);

	// 벡터 초기화
	pii.reserve(n);

	for (int i = 0; i < n; i++)
	{
		scanf("%lf %lf", &x, &y);

		pii.push_back(make_pair(x, y));
	}

	// x좌표가 작은 순서대로 정렬
	// 만약 x좌표가 같으면 y좌표가 같은 순서대로
	sort(pii.begin(), pii.end());

	// print_pii();

	ans = solve();

	printf("%d\n", ans);

	return 0;
}
