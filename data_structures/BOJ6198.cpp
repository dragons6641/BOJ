/*
A5 불쾌한 날
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

/*
#define MAX_N 80000
#define ll long long

int N;
ll ans = 0;
// 찬 곳을 가리긴다
int top = 0;
// 1부터 사용
int inputList[MAX_N + 1] = { 0, };
// 1부터 사용
int stack[MAX_N + 1] = { 0, };

int pushStack(int data)
{
	if (top == MAX_N)
	{
		return -1;
	}

	stack[++top] = data;

	return 1;
}

int popStack(int *ptr)
{
	if (top == 0)
	{
		return -1;
	}

	*ptr = stack[top--];

	return 1;
}

void inputData(void)
{
	scanf("%d", &N);

	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &inputList[i]);
	}

	return;
}

void solveN2(void)
{
	for (int i = 1; i < N; i++)
	{
		for (int j = i + 1; j <= N; j++)
		{
			if (inputList[i] > inputList[j])
			{
				ans++;
			}
			else
			{
				break;
			}
		}
	}

	return;
}

void solveN(void)
{
	int data;
	int ret;

	for (int i = 1; i <= N; i++)
	{
		// 비어있거나, top의 원소보다 내가 작다면
		if ((top == 0) || (inputList[i] < stack[top]))
		{
			// 머리 모양 볼 수 있으므로 push
			ret = pushStack(inputList[i]);
		}
		// top의 원소보다 내가 크거나 같다면
		else
		{
			// 머리 모양 볼 수 없으므로
			while ((top > 0) && (inputList[i] >= stack[top]))
			{
				// 조건을 만족할 때까지 pop
				ret = popStack(&data);

				// 현재 남은 원소 갯수만큼 정답에 더함
				ans += top;
			}

			// pop이 모두 끝난 후 push
			ret = pushStack(inputList[i]);
		}

		// int debug = 1;
	}

	// 스택을 비우면서 정답 추가 계산
	// 머리 모양 볼 수 없으므로
	while (top > 0)
	{
		// 조건을 만족할 때까지 pop
		ret = popStack(&data);

		// 현재 남은 원소 갯수만큼 정답에 더함
		ans += top;
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	inputData();

	// solveN2();
	solveN();

	printf("%lld\n", ans);

	return 0;
}
*/

#define MAX_N ((int)8e4)

typedef signed long long S64;

// 소 마리 수
int N;
// stack 관련
int sp;
// 소들의 키
int H[MAX_N + 10] = { 0, };
int stack[MAX_N + 10] = { 0, };

void push(int h)
{
	stack[++sp] = h; // 저장

	return;
}

void pop(void)
{
	sp--; // 제거

	return;
}

int top(void)
{
	return stack[sp]; // 읽기(제거는 안함)
}

int size(void)
{
	return sp;
}

bool empty(void)
{
	return (sp == 0); // 비었는지 여부
}

void inputData(void)
{
	scanf("%d", &N);

	for (register int i = 1; i <= N; i++)
	{
		scanf("%d", &H[i]);
	}
}

S64 solveN2(void)
{
	S64 cnt = 0;

	for (register int i = 1; i < N; i++) // 보는 소
	{
		for (register int j = i + 1; j <= N; j++) // 대상 소
		{
			if (H[i] <= H[j])
			{
				break; // j번 소에 막혀서 나머지 소는 무조건 못 봄
			}

			cnt++;
		}
	}

	return cnt;
}

S64 solveN1(void)
{
	S64 cnt = 0;

	for (register int i = 1; i <= N; i++)
	{
		while ((!empty()) && (top() <= H[i]))
		{
			pop(); // i번 소를 못 보는 소는 스택에서 제거
		}

		cnt += size(); // 스택에 남은 소가 i번 소를 볼 수 있는 소들의 수

		push(H[i]); // 현재 i번 소가 맨 앞 소이므로 스택에 저장
	}

	return cnt;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	inputData();

	// S64 ans = solveN2();
	S64 ans = solveN1();

	printf("%lld\n", ans);

	return 0;
}
