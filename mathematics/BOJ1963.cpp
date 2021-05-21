/*
1963 소수 경로
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MIN_N 1000
#define MAX_N 10000
#define MIN_DIVIDE 2
#define MAX_DIVIDE 100
#define MAX_QUEUE (MAX_N - MIN_N)
#define MAX_DIGIT 10
#define MAX_SIZE 4

struct Node
{
	int time;
	int pos;
};

bool visit[MAX_N] = { false, };
// 소수인지 아닌지부터 구하자
// true값을 가지면 소수, 초기화 필요
bool isPrime[MAX_N] = { false, };
Node start;
Node end;
Node queue[MAX_QUEUE] = { {0, 0} };

void initVisit(void)
{
	for (register int i = MIN_N; i < MAX_N; i++)
	{
		visit[i] = false;
	}

	return;
}

void initIsPrime(void)
{
	for (register int i = MIN_N; i < MAX_N; i++)
	{
		isPrime[i] = true;
	}

	return;
}

void checkPrime(void)
{
	// 나눌 수
	for (register int i = MIN_DIVIDE; i <= MAX_DIVIDE; i++)
	{
		// 나눠질 수
		for (register int j = MIN_N; j < MAX_N; j++)
		{
			// 이미 소수가 아닌거 확인했다면
			if (!isPrime[j])
			{
				// 그 수는 더 볼 필요도 없다
				continue;
			}

			// 나눠진다면
			if ((j % i) == 0)
			{
				// 그 수는 소수가 아니다
				isPrime[j] = false;
			}
		}
	}

	return;
}

int bfs(void)
{
	register int head = 0;
	register int tail = 0;

	int digitList[MAX_SIZE] = { 0, };
	int mulList[MAX_SIZE] = { 1000, 100, 10, 1 };

	visit[start.pos] = true;
	queue[tail++] = start;

	while (head != tail)
	{
		Node now = queue[head++];

		if (head == MAX_QUEUE)
		{
			head = 0;
		}

		if (now.pos == end.pos)
		{
			return now.time;
		}

		// 자릿수 분해
		int tmpPos = now.pos;

		for (register int i = MAX_SIZE - 1; i >= 0; i--)
		{
			digitList[i] = tmpPos % MAX_DIGIT;
			tmpPos /= MAX_DIGIT;
		}

		// 각 자릿수
		for (register int i = MAX_SIZE - 1; i >= 0; i--)
		{
			int tmpDigit = digitList[i];

			// 반영할 자리 숫자
			for (register int j = 0; j < MAX_DIGIT; j++)
			{
				tmpPos = 0;

				digitList[i] = j;

				for (register int k = MAX_SIZE - 1; k >= 0; k--)
				{
					tmpPos += (digitList[k] * mulList[k]);
				}

				// 소수가 아니라면
				if (!isPrime[tmpPos])
				{
					// 이동 불가
					continue;
				}

				// 이미 방문했다면
				if (visit[tmpPos])
				{
					// 이동 불가
					continue;
				}

				visit[tmpPos] = true;
				queue[tail++] = { now.time + 1, tmpPos };

				if (tail == MAX_QUEUE)
				{
					tail = 0;
				}
			}

			digitList[i] = tmpDigit;
		}
	}

	return -1;
}

void print(int ans)
{
	if (ans == -1)
	{
		printf("Impossible\n");
	}
	else
	{
		printf("%d\n", ans);
	}

	return;
}

void inputData(void)
{
	/*
	scanf("%d %d", &start.pos, &end.pos);

	start.time = 0;
	end.time = 0;
	*/

	int T;

	scanf("%d", &T);

	initIsPrime();

	for (register int testCase = 1; testCase <= T; testCase++)
	{
		scanf("%d %d", &start.pos, &end.pos);

		start.time = 0;
		end.time = 0;

		initVisit();

		checkPrime();

		int ans = bfs();

		print(ans);
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	inputData();

	/*
	init();

	checkPrime();

	int ans = bfs();

	printf("%d\n", ans);
	*/

	return 0;
}
