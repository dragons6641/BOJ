#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 9
#define MAX_R 3
#define MAX_C 3
#define MAX_ANS 1000000000
#define MAX_K 362880
#define MAX_QUEUE 362880
#define MAX_DIR 4
#define DIGIT 10
#define TARGET 123456789

struct Node
{
	// 9자리 int값
	int num;
	// 몇 번 이동했는지
	int time;
	// 0이 몇 번째 자리에 위치해 있는지
	int zeroPos;
};

int N;
int startPos = 0;
// 상하좌우
int weightList[MAX_N] = { 0, };
int directList[MAX_DIR] = { MAX_C, -MAX_C, 1, -1 };
bool visit[MAX_K] = { 0, };
Node queue[MAX_QUEUE] = { 0, 0, 0 };

// a의 b승
int pow(int a, int b)
{
	int result = 1;

	for (register int i = 0; i < b; i++)
	{
		result *= a;
	}

	return result;
}

void inputData(void)
{
	int M;

	for (register int i = 1; i <= MAX_N; i++)
	{
		scanf("%d", &M);

		if (M == 0)
		{
			startPos = MAX_N - i;
			// 0을 9로 변환
			M = MAX_N;
		}

		N = (N * DIGIT) + M;
	}

	return;
}

void init(void)
{
	int tmp = 1;

	for (register int i = 1; i < MAX_N; i++)
	{
		tmp *= i;
		weightList[MAX_N - i - 1] = tmp;
	}

	return;
}

void printAns(void)
{
	for (register int r = MAX_R - 1; r >= 0; r--)
	{
		for (register int c = MAX_C - 1; c >= 0; c--)
		{
			int ret = pow(DIGIT, (r * MAX_R) + c);

			printf("%d ", (N / ret));

			N %= ret;
		}

		printf("\n");
	}

	return;
}

// 빈 자리 없이 362880가지의 경우의 수를 모두 사용하려면
// 인덱스를 변환해주면 된다!
int calcWeight(int num)
{
	int result = 0;
	int pow = MAX_ANS / DIGIT;
	bool isUsed[MAX_N + 1];

	for (register int i = 0; i <= MAX_N; i++)
	{
		isUsed[i] = false;
	}

	for (register int i = 0; i < MAX_N; i++)
	{
		int digit = (int)(num / pow);
		int cnt = 0;

		isUsed[digit] = true;

		for (register int j = 1; j < digit; j++)
		{
			if (!isUsed[j])
			{
				cnt++;
			}
		}

		result += (cnt * weightList[i]);
		num -= (pow * digit);
		pow /= DIGIT;
	}

	return result;
}

// num의 a번째 자릿수와 b번째 자릿수 바꾸기
int swapDigit(int num, int a, int b)
{
	int powA = pow(DIGIT, a);
	int powB = pow(DIGIT, b);
	int digitA = (((int)(num / powA) % DIGIT));
	int digitB = (((int)(num / powB) % DIGIT));
	int result = num - (powA * digitA) - (powB * digitB) + (powA * digitB) + (powB * digitA);

	return result;
}

int bfs(void)
{
	register int head = 0;
	register int tail = 0;

	int idx = calcWeight(N);

	visit[idx] = true;
	queue[tail++] = { N, 0, startPos };

	while (head != tail)
	{
		Node now = queue[head++];

		if (head == MAX_QUEUE)
		{
			head = 0;
		}

		if (now.num == TARGET)
		{
			return now.time;
		}

		// 4방향 이동 가능
		for (register int d = 0; d < MAX_DIR; d++)
		{
			int nextPos = now.zeroPos + directList[d];

			if ((nextPos < 0) || (nextPos >= MAX_N))
			{
				continue;
			}

			// 왼쪽, 오른쪽 이동은 같은 row에 있어야 한다!
			/*
			if (((d == 2) || (d == 3)) && (((int)(now.zeroPos / MAX_R)) != (int)((nextPos / MAX_R))))
			{
				continue;
			}
			*/

			// 왼쪽으로 이동하는 경우 이미 가장 왼쪽이면 이동 불가
			if ((d == 2) && (nextPos % MAX_C == 0))
			{
				continue;
			}
			// 오른쪽으로 이동하는 경우 이미 가장 오른쪽이면 이동 불가
			else if ((d == 3) && (nextPos % MAX_C == (MAX_C - 1)))
			{
				continue;
			}

			int ret = swapDigit(now.num, now.zeroPos, nextPos);

			idx = calcWeight(ret);

			if (visit[idx])
			{
				continue;
			}

			visit[idx] = true;
			queue[tail++] = { ret, now.time + 1, nextPos };

			if (tail == MAX_QUEUE)
			{
				tail = 0;
			}
		}
	}

	return -1;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);	// 3
	// freopen("input2.txt", "r", stdin);	// -1
	// freopen("input3.txt", "r", stdin);	// 0
	// freopen("input4.txt", "r", stdin);	// 1
	// freopen("input5.txt", "r", stdin);	// 1
	// freopen("input6.txt", "r", stdin);	// -1
	// freopen("input7.txt", "r", stdin);	// -1
	// freopen("input8.txt", "r", stdin);	// -1
	// freopen("input9.txt", "r", stdin);	// 31
	// freopen("input10.txt", "r", stdin);	// 18

	inputData();

	init();

	// printf("%d\n", calcWeight(123456789));
	// printf("%d\n", calcWeight(987654321));

	int ans = bfs();

	// printAns();

	printf("%d\n", ans);

	return 0;
}
