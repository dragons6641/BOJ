/*
D3 콘서트
*/

#define _CRT_SECURE_NO_WARNINGS
#define ll long long

#include <stdio.h>

#define MAX_N ((int)5e5)
#define MAX_H (ll)(((ll)1 << (ll)31) - (ll)1)
#define STACK_SIZE		MAX_N
#define STACK_EMPTY		STACK_SIZE
#define STACK_FULL		0

struct Node
{
	// 나와 같은 키를 연속으로 count
	int same;
	int height;
};

// 사람의 수
int N;
int Sptr = STACK_EMPTY;
// 각 사람의 키
// 1부터 사용
int H[MAX_N + 1] = { 0, };
Node Stack[STACK_SIZE];

int Push_Stack(Node data)
{
	if (Sptr == STACK_FULL) return -1;
	Stack[--Sptr] = data;
	return 1;
}

int Pop_Stack(Node *p)
{
	if (Sptr == STACK_EMPTY) return -1;
	*p = Stack[Sptr++];
	return 1;
}

void inputData(void)
{
	scanf("%d", &N);

	for (register int i = 1; i <= N; i++)
	{
		scanf("%d", &H[i]);
	}

	return;
}

ll solve(void)
{
	ll cnt = 0;
	Node now;

	// 각 사람에 대해
	for (register int i = 1; i <= N; i++)
	{
		int same = 1;

		// 스택이 빌 때까지 확인
		while (Sptr != STACK_EMPTY)
		{
			// 내가 스택 탑보다 크거나 같다면
			if (H[i] >= Stack[Sptr].height)
			{
				// 정답 갱신
				cnt += (ll)Stack[Sptr].same;

				// 만약 키가 같다면
				if (H[i] == Stack[Sptr].height)
				{
					// 같은 사람 세기
					same += Stack[Sptr].same;
				}

				// 후보에서 제거
				Pop_Stack(&now);
			}
			// 내가 스택 탑보다 작다면
			else
			{
				// 더 이상 제거할 수 없음
				break;
			}
		}

		// 스택이 비어있지 않다면
		if (Sptr != STACK_EMPTY)
		{
			// 볼 수 있으므로 정답에 추가
			cnt += 1;
		}

		// 후보로 스택에 넣는다
		Push_Stack({ same, H[i] });
	}

	return cnt;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);

	inputData();

	ll ans = solve();

	printf("%lld\n", ans);

	return 0;
}
