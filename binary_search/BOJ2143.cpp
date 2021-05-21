#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int my_main()
{
	int t = 0;
	int n = 0;
	int m = 0;
	int tmp = 0;
	int lp_n = 0;
	int rp_n = 0;
	int lp_m = 0;
	int rp_m = 0;

	long long sum_n = 0;
	long long sum_m = 0;
	long long ans = 0;

	vector<int> v_n;
	vector<int> v_m;

	scanf("%d", &t);

	scanf("%d", &n);
	
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &tmp);

		v_n.push_back(tmp);
	}

	scanf("%d", &m);

	
	for (int i = 0; i < m; i++)
	{
		scanf("%d", &tmp);

		v_m.push_back(tmp);
	}

	/*
	for (int i = 0; i < n; i++)
	{
		printf("%d ", v_n[i]);
	}

	printf("\n");

	for (int i = 0; i < m; i++)
	{
		printf("%d ", v_m[i]);
	}

	printf("\n");
	*/

	///*
	// n 배열
	while (1)
	{
		printf("NNNN\nsum = %lld, lp = %d, rp = %d\n", sum_n, lp_n, rp_n);

		// 합이 초과한 경우
		if (sum_n > t)
		{
			// lp 증가
			sum_n -= v_n[lp_n];
			lp_n += 1;
		}
		// rp가 범위 밖인 경우
		else if (rp_n == n)
		{
			// 종료
			break;
		}
		// 합이 초과하지 않은 경우
		else
		{
			// rp 증가
			sum_n += v_n[rp_n];
			rp_n += 1;
		}

		lp_m = 0;
		rp_m = 0;
		sum_m = 0;

		// m 배열
		while (1)
		{
			printf("MMMM\nsum = %lld, lp = %d, rp = %d\n", sum_m, lp_m, rp_m);

			// 합이 초과한 경우
			if (sum_n + sum_m > t)
			{
				// lp 증가
				sum_m -= v_m[lp_m];
				lp_m += 1;
			 }
			// rp가 범위 밖인 경우
			else if (rp_m == m)
			{
				// 종료
				break;
			}
			// 합이 초과하지 않을 경우
			else
			{
				// 같으면
				if (sum_n + sum_m == t)
				{
					if ((rp_n - lp_n > 0) && (rp_m - lp_m > 0))
					{
						// 정답
						ans += 1;
					}
				}

				// rp 증가
				sum_m += v_m[rp_m];
				rp_m += 1;
			}
		}
	}
	//*/

	printf("%lld\n", ans);

	return 0;
}

int main()
{
	vector<int> A, B;

	int T, n;

	scanf("%d %d", &T, &n);

	int tmp;

	A.reserve(n);

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &tmp);

		A.push_back(tmp);
	}

	int m;

	scanf("%d", &m);

	B.reserve(m);

	for (int i = 0; i < m; i++)
	{
		scanf("%d", &tmp);

		B.push_back(tmp);
	}

	vector<int> avt;

	avt.reserve(n*n);

	// a와 a' 조합
	for (int i = 0; i < n; i++)
	{
		tmp = A.at(i);
		avt.push_back(tmp);

		for (int j = i + 1; j < n; j++)
		{
			tmp += A.at(j);
			avt.push_back(tmp);
		}
	}

	vector<int> bvt;

	bvt.reserve(m*m);

	// b와 b' 조합
	for (int i = 0; i < m; i++)
	{
		tmp = B.at(i);
		bvt.push_back(tmp);

		for (int j = i + 1; j < m; j++)
		{
			tmp += B.at(j);
			bvt.push_back(tmp);
		}
	}

	// 정렬은 나중에 직접 짜자!
	sort(bvt.begin(), bvt.end());

	int diff;
	long long ans = 0;

	for (int i = 0; i < avt.size(); i++)
	{
		diff = T - avt.at(i);
		vector<int>::iterator up = upper_bound(bvt.begin(), bvt.end(), diff);
		vector<int>::iterator lo = lower_bound(bvt.begin(), bvt.end(), diff);

		ans += (up - lo);
	}

	printf("%lld\n", ans);

	return 0;
}
