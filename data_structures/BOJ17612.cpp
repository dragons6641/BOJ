/*
Problem H 쇼핑몰
User Priority Queue
Check In : minpq
Check Out : maxpq
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

typedef long long LL;

struct Data
{
	int id;
	int tm;
	int cNum;

	bool operator < (const Data &r) const
	{
		if (tm != r.tm)
		{
			return tm < r.tm;
		}

		return cNum < r.cNum;
	}

	bool operator > (const Data &r) const
	{
		if (tm != r.tm)
		{
			return tm < r.tm;
		}

		return cNum > r.cNum;
	}
};

const int LM = 100010;
int N;
int K;
LL ans;

bool Max(const Data& a, const Data& b)
{
	/*
	if (a.tm != b.tm)
	{
		return (a.tm < b.tm);
	}

	return (a.cNum > b.cNum);
	*/

	return a > b;
}

bool Min(const Data& a, const Data& b)
{
	/*
	if (a.tm != b.tm)
	{
		return (a.tm < b.tm);
	}

	return (a.cNum < b.cNum);
	*/

	return a < b;
}

inline void swap(Data& a, Data& b)
{
	Data t = a;
	a = b;
	b = t;

	return;
}

struct PriorityQueue
{
	int hn;
	Data heap[LM];
	bool (*comp)(const Data&, const Data&);

	void init(bool flag)
	{
		hn = 0;
		comp = (flag ? Max : Min);
	}

	Data top(void)
	{
		return heap[1];
	}

	int size(void)
	{
		return hn;
	}

	bool empty(void)
	{
		return (hn == 0);
	}

	void push(Data val)
	{
		heap[++hn] = val;

		register int c = hn;

		while ((c > 1) && (comp(heap[c], heap[c / 2])))
		{
			swap(heap[c], heap[c / 2]);

			c /= 2;
		}

		return;
	}

	Data pop(void)
	{
		register int p = 1;
		register int c = 2;
		Data ret = heap[1];
		swap(heap[1], heap[hn--]);

		while (c <= hn)
		{
			if ((c < hn) && (comp(heap[c + 1], heap[c])))
			{
				c++;
			}

			if (!comp(heap[c], heap[p]))
			{
				break;
			}

			swap(heap[c], heap[p]);

			p = c;
			c *= 2;
		}

		return ret;
	}
};

PriorityQueue maxpq;
PriorityQueue minpq;

void inputData(void)
{
	int id;
	int w;
	register int i;

	scanf("%d %d", &N, &K);

	// 줄서있는 고객에 대하여 계산대 번호가 작은 것부터 배정
	for (i = 1; (i <= N) && (i <= K); i++)
	{
		scanf("%d %d", &id, &w);

		minpq.push({ id, w, i });
	}

	// 고객이 남아있다면
	for (; i <= N; i++)
	{
		scanf("%d %d", &id, &w);

		Data ret = minpq.pop();

		maxpq.push(ret);
		minpq.push({ id, ret.tm + w, ret.cNum });
	}

	// 계산대에 계산중인 고객의 계산 완료 시키기
	while (!minpq.empty())
	{
		Data ret = minpq.pop();

		maxpq.push(ret);
	}

	// 모든 고객을 집으로...
	for (i = 1; i <= N; i++)
	{
		Data ret = maxpq.pop();

		ans += ((LL)i * ret.id);
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	maxpq.init(true);
	minpq.init(false);

	inputData();

	printf("%lld\n", ans);

	return 0;
}
