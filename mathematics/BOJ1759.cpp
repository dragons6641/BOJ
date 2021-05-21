# define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <string.h>

# define l_max 15
# define c_max 15
# define start 0

int l = 0;
int c = 0;
int ja = 0;
int mo = 0;

// backTrack 함수 돌 때마다 초기화 필요
///*
int used[c_max + 1] = {0};
int len = 0;
int ja_now = 0;
int mo_now = 0;
char ans[l_max + 1] = { '\0' };
//*/

char temp_char = '\0';
char char_list[c_max + 1] = { '\0' };

void backTrack(int now)
{
	// 변수 반영
	ans[len] = char_list[now];

	used[now] += 1;
	len += 1;

	if (char_list[now] == 'a' || char_list[now] == 'e' || char_list[now] == 'i' || char_list[now] == 'o' || char_list[now] == 'u')
	{
		mo_now += 1;
	}
	else
	{
		ja_now += 1;
	}

	// printf("%d %d\n", now, len);
	// printf("%s\n", ans);
	// printf("%d %d %d %d\n\n", now, len, ja_now, mo_now);

	for (int j = (now + 1); j <= c; j++)
	{
		/*
		for (int i = 0; i < c; i++)
		{
			printf("%d", used[i]);
		}

		printf("\n");
		*/

		// printf("%d %d %d\n", j, c, len);

		// 조건에 맞는 암호를 찾았으면 이전 단계로 return

		// 답이 아니면 가지치기

		//// 겹치지 않아야 한다. 사용했는가?
		for (int i = 0; i < c; i++)
		{
			if (used[i] > 1)
			{
				// 나에게로 돌아오면 초기화
				used[now] -= 1;
				len -= 1;

				if (char_list[now] == 'a' || char_list[now] == 'e' || char_list[now] == 'i' || char_list[now] == 'o' || char_list[now] == 'u')
				{
					mo_now -= 1;
				}
				else
				{
					ja_now -= 1;
				}

				ans[len] = '\0';

				return;
			}
		}

		/*
		//// 길이를 맞추지 못하면 탐색 제한
		if ((len + c - now) < l)
		{
			// 나에게로 돌아오면 초기화
			used[now] -= 1;
			len -= 1;

			if (char_list[now] == 'a' || char_list[now] == 'e' || char_list[now] == 'i' || char_list[now] == 'o' || char_list[now] == 'u')
			{
				mo_now -= 1;
			}
			else
			{
				ja_now -= 1;
			}

			ans[len] = '\0';

			return;
		}
		*/

		//// 길이가 l이면 출력하고 종료
		//// 최소 모음 1개, 자음 2개
		if (len == l && ja_now >= 2 && mo_now >= 1)
		{
			printf("%s\n", ans);

			// 나에게로 돌아오면 초기화
			used[now] -= 1;
			len -= 1;

			if (char_list[now] == 'a' || char_list[now] == 'e' || char_list[now] == 'i' || char_list[now] == 'o' || char_list[now] == 'u')
			{
				mo_now -= 1;
			}
			else
			{
				ja_now -= 1;
			}

			ans[len] = '\0';

			return;
		}

		backTrack(j);
	}

	// printf("returned!\n");

	// 나에게로 돌아오면 초기화
	used[now] -= 1;
	len -= 1;

	if (char_list[now] == 'a' || char_list[now] == 'e' || char_list[now] == 'i' || char_list[now] == 'o' || char_list[now] == 'u')
	{
		mo_now -= 1;
	}
	else
	{
		ja_now -= 1;
	}

	ans[len] = '\0';

	return;
}

int main()
{
	scanf("%d %d", &l, &c);

	// printf("%d %d\n", l, c);

	for (int i = 0; i < c; i++)
	{
		getchar();

		/*
		if (i != (c - 1))
		{
			scanf("%c ", &char_list[i]);
			//printf("scanned with space\n");
		}
		else
		{
			scanf("%c", &char_list[i]); 
			//printf("scanned without space\n");
		}
		*/

		scanf("%c", &char_list[i]);


		// 자음 모음 판별
		if (char_list[i] == 'a' || char_list[i] == 'e' || char_list[i] == 'i' || char_list[i] == 'o' || char_list[i] == 'u')
		{
			mo += 1;
		}
		else
		{
			ja += 1;
		}
		
		// printf("%d\n", i);
	}

	// printf("%d %d\n", ja, mo);

	// 배열 정렬

	for (int i = 0; i < (c - 1); i++)
	{
		for (int j = (i + 1); j < c; j++)
		{
			if (char_list[i] > char_list[j])
			{
				temp_char = char_list[j];
				char_list[j] = char_list[i];
				char_list[i] = temp_char;
			}

			// printf("%d %d\n", i, j);
		}
	}

	/*
	for (int i = 0; i < c; i++)
		{
			printf("%c\n", char_list[i]);
			// printf("%d\n", i);
		}
	*/

	for (int i = 0; i < c; i++)
	{
		// printf("%c\n", char_list[i]);
		backTrack(i);
	}

	return 0;
}
