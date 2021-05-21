#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 200000
#define MAX_H 500000
#define INF 1000000000

#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

// 석순 벡터(홀수)
vector <int> s;

// 종유석 벡터(짝수)
vector <int> j;

void print_s()
{
	printf("s : ");

	for (int i = 0; i < s.size(); i++)
	{
		printf("%d ", s[i]);
	}

	printf("\n");

	return;
}

void print_j()
{
	printf("j : ");

	for (int i = 0; i < j.size(); i++)
	{
		printf("%d ", j[i]);
	}

	printf("\n");

	return;
}

int main()
{
	int n = 0;
	int h = 0;
	int tmp = 0;
	int ans = INF; // 장애물의 갯수
	int cnt = 1; // 구간의 갯수 (일단 자신은 포함이니까 1로 초기화!)
	int a = 0; // 석순
	int b = 0; // 종유석

	scanf("%d %d", &n, &h);

	// printf("n = %d, h = %d\n", n, h);

	// 벡터 선언하면 반드시 크기 지정!
	// push back이면 reserve
	// 배열처럼 쓰면 resize
	s.reserve((n / 2) + 1);
	j.reserve((n / 2) + 1);

	for (int i = 0; i < (n / 2); i++)
	{
		scanf("%d", &tmp);

		s.push_back(tmp);

		scanf("%d", &tmp);

		j.push_back(tmp);
	}

	// 정렬
	sort(s.begin(), s.end());
	sort(j.begin(), j.end());

	// print_s();
	// print_j();

	// 각 높이에 대하여
	for (int i = 0; i < h; i++)
	{
		// 해당 높이로 날았을 때 부딪히는 석순(아래에서부터)
		a = s.size() - (lower_bound(s.begin(), s.end(), i) - s.begin());
		// 해당 높이로 날았을 때 부딪히는 종유석(위에서부터)
		b = j.size() - (upper_bound(j.begin(), j.end(), h - i) - j.begin());

		// 더 적은 갯수의 장애물을 파괴했으면
		if ((a + b) < ans)
		{
			// 최솟값 갱신
			ans = (a + b);

			// 구간 갯수 초기화
			cnt = 1;
		}
		// 더 많은 갯수의 장애물을 파괴했으면
		else if ((a + b) > ans)
		{
			// 할 일 없다
		}
		// 같은 갯수의 장애물을 파괴했으면
		else
		{
			// 구간 갯수 증가
			cnt += 1;
		}
	}

	printf("%d %d\n", ans, cnt);

	return 0;
}
