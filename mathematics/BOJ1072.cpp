#define _CRT_SECURE_NO_WARNINGS
#define MAX_X 1000000000

#include <stdio.h>

using namespace std;

int main()
{
	long long x = 0;
	long long y = 0;
	long long z = 0;
	long long left = 0;
	long long right = MAX_X;
	long long mid = 0;
	long long w = 0;
	long long ans = MAX_X;
	long long tmp_y = 0;
	long long tmp_x = 0;

	while ((scanf("%lld %lld", &x, &y) != EOF))
	{
		z = (y * 100 / x);

		// BS
		while (left <= right)
		{
			mid = (left + right) / 2;

			// 승률 변하는지 판별
			tmp_y = (y + mid) * 100;
			tmp_x = (x + mid);
			w = (tmp_y / tmp_x);

			// printf("z = %d, w = %d, mid = %d\n", z, w, mid);

			// 승률 아직 안변하면
			if (z == w)
			{
				// 더 많이 이겨야한다
				left = mid + 1;
			}
			// 승률이 변했다면
			else
			{
				// 일단 답 표시 후
				if (mid < ans)
				{
					ans = mid;
				}

				// 더 적게 이겨도 되나 확인
				right = mid - 1;
			}
		}

		// 승률 변하지 않을 경우
		if ((mid == 0) || (z >= 99))
		{
			ans = -1;
		}
		
		printf("%lld\n", ans);
	}

	return 0;
}
