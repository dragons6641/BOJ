/*
Pro입문 3주차 Problem B 떡 먹는 호랑이
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_D 30
#define MAX_K 100000

int day;
int target;

void getHang(int& a, int& b)
{
	int arr[MAX_D + 10] = { 0, 1, 0, };
	int brr[MAX_D + 10] = { 0, 0, 1, };

	for (int i = 3; i <= day; i++)
	{
		arr[i] = arr[i - 1] + arr[i - 2];
		brr[i] = brr[i - 1] + brr[i - 2];
	}

	a = arr[day];
	b = brr[day];

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);

	setbuf(stdout, NULL);

	scanf("%d %d", &day, &target);

	int a;
	int b;
	int ha;
	int hb;

	getHang(ha, hb);

	int limit = (target / hb) + 1;

	for (b = 0; b <= limit; b++)
	{
		/*
		if (b == 21)
		{
			int debug = 1;
		}
		*/

		int temp = target - (hb * b);

		if (temp < 0)
		{
			break;
		}

		if ((temp % ha) != 0)
		{
			continue;
		}

		a = temp / ha;

		if (a > b)
		{
			continue;
		}

		break;
	}

	printf("%d\n%d\n", a, b);

	return 0;
}
