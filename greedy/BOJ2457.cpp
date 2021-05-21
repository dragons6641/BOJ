/*
D1 공주님의 정원
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 100000
#define START_MONTH 3
#define START_DAY 1
#define END_MONTH 12
#define END_DAY 1
#define MIN_MONTH 1
#define MIN_DAY 1
#define MAX_MONTH 12
#define MAX_DAY 31

/*
struct Node
{
	// 시작월
	int sm;
	// 시작일
	int sd;
	// 종료월
	int em;
	// 종료일
	int ed;
};

int N;
// 1부터 사용
Node inputList[MAX_N + 1] = { {0, 0, 0, 0}, };
Node tmpList[MAX_N + 1] = { {0, 0, 0, 0}, };

int compNode(Node *x, Node *y)
{
	if (x->sm == y->sm)
	{
		if (x->sd == y->sd)
		{
			if (x->em == y->em)
			{
				return (x->ed - y->ed);
			}

			return (x->em - y->em);
		}

		return (x->sd - y->sd);
	}

	return (x->sm - y->sm);
}

int compStart(Node *x, Node *y)
{
	if (x->sm == y->sm)
	{
		return (x->sd - y->sd);
	}

	return (x->sm - y->sm);
}

int compStartEnd(Node *x, Node *y)
{
	if (x->sm == y->em)
	{
		return (x->sd - y->ed);
	}

	return (x->sm - y->em);
}

int compEnd(Node *x, Node *y)
{
	if (x->em == y->em)
	{
		return (x->ed - y->ed);
	}

	return (x->em - y->em);
}

int Sort_Merge(Node *d, Node *tmp, int order, int s, int e, int(*comp)(Node *x, Node *y))
{
	int m, idx1, idx2, idxtmp;
	if (s >= e) return -1;

	m = (s + e) / 2;

	Sort_Merge(d, tmp, order, s, m, comp);
	Sort_Merge(d, tmp, order, m + 1, e, comp);

	idx1 = s; idx2 = m + 1; idxtmp = s;
	while (idx1 <= m && idx2 <= e)
	{
		if ((order * comp(&d[idx1], &d[idx2])) < 0) tmp[idxtmp++] = d[idx1++];
		else tmp[idxtmp++] = d[idx2++];
	}

	if (idx1 <= m) while (idx1 <= m) tmp[idxtmp++] = d[idx1++];
	else while (idx2 <= e) tmp[idxtmp++] = d[idx2++];

	for (idxtmp = s; idxtmp <= e; idxtmp++) d[idxtmp] = tmp[idxtmp];
	return e - s + 1;
}

void inputData(void)
{
	scanf("%d", &N);

	for (register int i = 1; i <= N; i++)
	{
		scanf("%d %d %d %d", &inputList[i].sm, &inputList[i].sd, &inputList[i].em, &inputList[i].ed);

		if (inputList[i].sm < START_MONTH)
		{
			inputList[i].sm = START_MONTH;
			inputList[i].sd = START_DAY;
		}

		if (inputList[i].em >= END_MONTH)
		{
			inputList[i].em = END_MONTH;
			inputList[i].ed = END_DAY;
		}
	}

	return;
}

int solve(void)
{
	int cnt = 0;

	// 피는 날짜가 빠른 것이 앞으로 오도록
	// 피는 날짜가 같은 경우 지는 날짜가 빠른 것이 앞으로 오도록
	Sort_Merge(inputList, tmpList, 1, 1, N, compNode);

	// 첫 꽃이 4월 이후에 폈다면
	if (inputList[1].sm > START_MONTH)
	{
		// 끝!
		return 0;
	}
	// 첫 꽃이 3월에 피기는 폈는데 2일 이후에 폈다면
	else if ((inputList[1].sm == START_MONTH) && (inputList[1].sd > START_DAY))
	{
		// 끝!
		return 0;
	}

	int ret;
	// 현재 피어있는 꽃
	Node now = { START_MONTH, START_DAY, START_MONTH, START_DAY};
	// 다음에 필 꽃 후보
	Node next = inputList[1];

	// Greedy
	for (register int i = 2; i <= N; i++)
	{
		// 꽃이 핀 날짜 비교
		ret = compStartEnd(&inputList[i], &now);

		// 현재 날짜보다 뒤에 핀 꽃이라면
		if (ret >= 0)
		{
			// 그 이전까지의 꽃들 중 가장 늦게까지 피어있는 꽃을 골라야 함
			now = next;
			cnt++;

			// 새로운 꽃이 핀 날짜 비교
			ret = compStart(&inputList[i], &now);

			// 만약 내가 더 빨리 핀다면
			if (ret <= 0)
			{
				// 내가 후보자가 된다
				next = inputList[i];
			}
			// 내가 더 늦게 핀다면
			else
			{
				// 피어있지 않은 날짜가 생긴다
				// 끝!
				return 0;
			}
		}
		// 현재 날짜보다 이전에 핀 꽃이라면
		else
		{
			// 꽃이 진 날짜 비교
			ret = compEnd(&inputList[i], &next);

			// 다음 후보의 지는 날보다 내가 더 늦게 진다면
			if (ret > 0)
			{
				// 내가 후보자가 된다
				next = inputList[i];
			}
		}
	}

	// 마지막 필 꽃은 예외처리
	// 모든 범위 커버했다면
	if ((now.em == END_MONTH) && (now.ed == END_DAY))
	{
		// 성공적으로 끝!
		return cnt;
	}

	// 아직 커버 못했다면
	// 핀 날짜 비교
	ret = compStartEnd(&next, &now);

	// 현재 날짜보다 먼저 핀 꽃이라면
	if (ret <= 0)
	{
		// 그 이전까지의 꽃들 중 가장 늦게까지 피어있는 꽃을 골라야 함
		now = next;
		cnt++;
	}
	// 현재 날짜보다 나중에 핀 꽃이라면
	else
	{
		// 피어있지 않은 날짜가 생긴다
		// 끝!
		return 0;
	}

	return cnt;
}
*/

struct Node
{
	int start;
	int end;
};

// 꽃의 종류
int N;
// 1부터 시작
Node inputList[MAX_N + 1] = { 0, 0 };
// 1부터 시작
Node tmpList[MAX_N + 1] = { 0, 0 };

int comp(Node *x, Node *y)
{
	if (x->start == y->start)
	{
		return (x->end - y->end);
	}

	return (x->start - y->start);
}

int Sort_Merge(Node *d, Node *tmp, int order, int s, int e, int(*comp)(Node *x, Node *y))
{
	int m, idx1, idx2, idxtmp;
	if (s >= e) return -1;

	m = (s + e) / 2;

	Sort_Merge(d, tmp, order, s, m, comp);
	Sort_Merge(d, tmp, order, m + 1, e, comp);

	idx1 = s; idx2 = m + 1; idxtmp = s;
	while (idx1 <= m && idx2 <= e)
	{
		if ((order * comp(&d[idx1], &d[idx2])) < 0) tmp[idxtmp++] = d[idx1++];
		else tmp[idxtmp++] = d[idx2++];
	}

	if (idx1 <= m) while (idx1 <= m) tmp[idxtmp++] = d[idx1++];
	else while (idx2 <= e) tmp[idxtmp++] = d[idx2++];

	for (idxtmp = s; idxtmp <= e; idxtmp++) d[idxtmp] = tmp[idxtmp];
	return e - s + 1;
}

void inputData(void)
{
	int sm;
	int sd;
	int em;
	int ed;

	scanf("%d", &N);

	for (register int i = 1; i <= N; i++)
	{
		scanf("%d %d %d %d", &sm, &sd, &em, &ed);

		inputList[i].start = (sm * 100) + sd;
		inputList[i].end = (em * 100) + ed;
	}

	return;
}

int solve(void)
{
	// 꽃의 갯수 세기
	int cnt = 0;
	// 현재 날짜
	// 
	int now = START_MONTH * 100 + START_DAY;
	// 다음 필 후보 인덱스
	int idx = 1;

	// 피는 날짜가 빠른 것이 앞으로 오도록
	// 피는 날짜가 같은 경우 지는 날짜가 빠른 것이 앞으로 오도록
	Sort_Merge(inputList, tmpList, 1, 1, N, comp);

	// 가장 빨리 피는 꽃이 3월 1일보다 늦게 핀다면
	// 꽃이 피어있지 않은 기간이 존재하므로
	if (inputList[idx].start > now)
	{
		// 끝!
		return 0;
	}

	// Greedy
	for (register int i = 2; i <= N; i++)
	{
		// 이 꽃이 현재 날짜보다 늦게 핀다면
		if (inputList[i].start > now)
		{
			// 기존 후보를 피운다
			now = inputList[idx].end;
			cnt++;

			// 마지막까지 다 피웠다면
			// 더 할 필요 없다!
			if (now >= ((END_MONTH * 100) + END_DAY))
			{
				return cnt;
			}

			// 이 꽃이 갱신된 현재 날짜보다 늦게 핀다면
			// 꽃이 피어있지 않은 기간이 존재하므로
			if (inputList[i].start > now)
			{
				// 끝!
				return 0;
			}

			// 후보 갱신
			idx = i;
		}
		// 이 꽃이 현재 날짜 이전에 핀다면
		else
		{
			// 후보일 수 있는지 확인
			// 후보는 가장 늦게 져야 하므로
			// 이 꽃이 후보 꽃보다 늦게 진다면
			if (inputList[i].end > inputList[idx].end)
			{
				// 후보 갱신
				idx = i;
			}
		}
	}

	// 마지막 후보는 확인 필요
	// 이 꽃이 갱신된 현재 날짜보다 늦게 핀다면
	// 꽃이 피어있지 않은 기간이 존재하므로
	if (inputList[idx].start > now)
	{
		// 끝!
		return 0;
	}
	// 이 꽃이 갱신된 현재 날짜 이전에 핀다면
	else
	{
		// 기존 후보를 피운다
		now = inputList[idx].end;
		cnt++;
	}

	// 마지막 날까지 꽃이 피지 않았다면
	// 꽃이 피어있지 않은 기간이 존재하므로
	if (now < ((END_MONTH * 100) + END_DAY))
	{
		// 끝!
		return 0;
	}

	return cnt;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);
	// freopen("input4.txt", "r", stdin);
	// freopen("input5.txt", "r", stdin);
	// freopen("input6.txt", "r", stdin);
	// freopen("input7.txt", "r", stdin);
	// freopen("input8.txt", "r", stdin);
	// freopen("input9.txt", "r", stdin);
	// freopen("input10.txt", "r", stdin);
	// freopen("input11.txt", "r", stdin);
	// freopen("input12.txt", "r", stdin);
	// freopen("input13.txt", "r", stdin);
	// freopen("input14.txt", "r", stdin);
	// freopen("input15.txt", "r", stdin);
	// freopen("input16.txt", "r", stdin);
	// freopen("input17.txt", "r", stdin);
	// freopen("input18.txt", "r", stdin);
	// freopen("input19.txt", "r", stdin);

	inputData();

	int ans = solve();

	printf("%d\n", ans);

	return 0;
}
