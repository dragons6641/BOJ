/*
Pro입문 2주차 Problem H 숫자의 개수
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_M 10

int main(void)
{
	// DAT (Direct Addressing Table)

	/*
	int cnt = 0;
	int bucket[100] = { 0, };
	char vect[10] = "ADASDASDA";

	for (int i = 0; vect[i] != '\0'; i++)
	{
		bucket[vect[i]] = 1;
	}

	for (int i = 0; i < 100; i++)
	{
		if (bucket[i] == 1)
		{
			cnt++;
		}
	}

	printf("%d\n", cnt);
	*/

	/*
	// 한 문자열 입력받고
	// 각각의 알파벳이 총 몇 개가 쓰였는지 출력
	int bucket[100] = { 0, };
	char vect[12] = "ABCCBCCCBD";

	for (int i = 0; vect[i] != '\0'; i++)
	{
		bucket[vect[i]]++;
	}

	for (int i = 0; i < 100; i++)
	{
		if (bucket[i] > 0)
		{
			printf("%c : %d\n", i, bucket[i]);
		}
	}
	*/

	/*
	// 가장 빈도수가 높은 숫자를 출력
	// 답 : 1000
	int max = 0;
	int maxIndex;
	int vect[11] = {3, 2, 3, 1000, 1000, 1000, 1000, 1, 5, 2, 2};
	int bucket[1001] = { 0 };

	for (int i = 0; i < 11; i++)
	{
		bucket[vect[i]]++;

		if (bucket[vect[i]] > max)
		{
			max = bucket[vect[i]];
			maxIndex = vect[i];
		}
	}
	
	printf("%d\n", maxIndex);
	*/

	/*
	// 가장 많이 등장하는 숫자 : 4
	// 가장 적게 등장하는 숫자 : 6
	int min = 21e8;
	int minValue;
	int max = -21e8;
	int maxValue;
	int bucket[10] = { 0, };
	int vect[3][4] =
	{
		4, 1, 3, 3,
		4, 4, 3, 4,
		4, 4, 4, 6
	};

	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			bucket[vect[r][c]]++;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (bucket[i] == 0)
		{
			continue;
		}

		if (bucket[i] < min)
		{
			min = bucket[i];
			minValue = i;
		}

		if (bucket[i] > max)
		{
			max = bucket[i];
			maxValue = i;
		}
	}
	*/

	///*
	// freopen("input1.txt", "r", stdin);

	int a;
	int b;
	int c;
	int han;
	int bucket[MAX_M] = { 0, };

	setbuf(stdout, NULL);

	scanf("%d %d %d", &a, &b, &c);

	int target = a * b * c;

	while (true)
	{
		if (target == 0)
		{
			break;
		}

		han = target % MAX_M;
		bucket[han]++;
		target /= MAX_M;
	}

	for (int i = 0; i < MAX_M; i++)
	{
		printf("%d\n", bucket[i]);
	}
	//*/

	return 0;
}
