# define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <stdlib.h>

# define max_t 20
# define max_n 100000

typedef struct _data {
	int score1;
	int score2;
} data;

int t = 0;
int temp_int = 0;
int ans_list[max_t] = { 0 };
int cnt = 0;
int n = 0;
int ans = 0;
int high_score = 0;

// 오름차순 비교 함수 구현
int compare(const void *A, const void *B)
{
	// void 포인터를 int 포인터로 변환한 뒤 역참조하여 값을 가져옴
	int num1 = *(int *)A;
	int num2 = *(int *)B;

	// a가 b보다 작을 때는 -1을 반환
	if (num1 < num2)
	{
		return -1;
	}

	// a가 b보다 클 때는 1을 반환
	else if (num1 > num2)
	{
		return 1;
	}

	// a와 b가 같으면 0을 반환
	else
	{
		return 0;
	}
}

int search(data scores[], int n)
{
	cnt = 1;
	high_score = scores[0].score2;
	// printf("%d\n", high_score);

	for (int i = 1; i < n; i++)
	{
		// printf("i = %d, cnt = %d\n", i, cnt);
		// printf("%d %d\n\n", scores[i].score2, high_score);

		// printf("%d\n", high_score);

		if (scores[i].score2 == 1)
		{
			cnt += 1;

			return cnt;
		}

		/*
		for (int j = 0; j < i; j++)
		{
			// printf("i = %d, j = %d\ncnt = %d\n", i, j, cnt);
			// printf("%d %d\n\n", scores[i].score2, scores[j].score2);

			if (scores[i].score2 > scores[j].score2)
			{
				// cnt += 1;

				// printf("BREAKED\n");

				cnt -= 1;

				break;
			}
		}
		*/

		if (scores[i].score2 > high_score)
		{
			// cnt += 1;

			// printf("BREAKED\n");

			cnt -= 1;
		}

		else if (scores[i].score2 < high_score)
		{
			high_score = scores[i].score2;
		}

		cnt += 1;
	}

	return cnt;
}

int main()
{
	scanf("%d", &t);

	// printf("%d\n", t);

	for (int i = 0; i < t; i++)
	{
		n = 0;
		ans = 0;
		high_score = 0;
		data scores[max_n] = { 0, 0 };

		getchar();

		scanf("%d", &n);

		// printf("%d\n", n);

		for (int j = 0; j < n; j++)
		{
			getchar();

			scanf("%d %d", &scores[j].score1, &scores[j].score2);
		}

		// 서류 등수 오름차순 정렬
		/*
		for (int i = 0; i < n; i++)
		{
			for (int j = (i + 1); j < n; j++)
			{
				if (scores[i].score1 > scores[j].score1)
				{
					temp_int = scores[j].score1;
					scores[j].score1 = scores[i].score1;
					scores[i].score1 = temp_int;

					temp_int = scores[j].score2;
					scores[j].score2 = scores[i].score2;
					scores[i].score2 = temp_int;
				}
			}
		}
		*/

		qsort(scores, n, sizeof(data), compare);

		/*
		for (int j = 0; j < n; j++)
		{
			printf("%d %d\n", scores[j].score1, scores[j].score2);
		}
		*/

		// 탐색
		/*
		ans = search(scores, n);

		printf("%d\n", ans);
		*/

		ans_list[i] = search(scores, n);
	}

	for (int i = 0; i < t; i++)
	{
		printf("%d\n", ans_list[i]);
	}

	return 0;
}
