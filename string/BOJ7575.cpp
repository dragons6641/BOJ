#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 100
#define MAX_K 1000
#define MAX_M 1000
#define MAX_CODE 10000
#define MAX_HASH 1009
#define MOD (ULL)0
#define BASE (ULL)33
/*
#define MAX_HASH 10000
#define MOD (ULL)0
#define BASE (ULL)100
*/

typedef unsigned long long ULL;

struct HashNode
{
	// 해당 데이터의 인덱스 범위
	int start;
	int end;
	// 동일한 데이터의 갯수
	int cnt;
	// Chaining 방식
	HashNode* next;

	void hashAlloc(int _start, int _end, HashNode* _prev)
	{
		start = _start;
		end = _end;
		cnt = 1;
		
		if (_prev)
		{
			next = _prev->next;
			_prev->next = this;
		}

		return;
	}
};

// 감염된 프로그램의 개수
int N;
// 바이러스 코드 추정을 위한 최소 길이
int K;
// 사용한 버퍼 개수
int bCnt = 0;
// 바이러스 코드가 있는 프로그램의 개수
int ans = 1;
// 각 프로그램 길이
int M[MAX_N] = { 0, };
// 프로그램 정보
int program[MAX_N][MAX_M] = { 0, };
// Rolling Hash 가중치
ULL weight = 1;
// 실제 Hash Table
HashNode hashTable[MAX_HASH];
// Hash Table 버퍼
HashNode hashBuf[MAX_M * 2];

/*
unsigned long hash(const char *str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
	{
		hash = (((hash << 5) + hash) + c) % MAX_TABLE;
	}

	return hash % MAX_TABLE;
}
*/

ULL getFirstKey(const int* code, int start, int end)
{
	ULL key = MOD;

	// 정방향일 경우
	if (start < end)
	{
		for (register int i = start; i <= end; i++)
		{
			key = ((key * BASE) + (ULL)code[i]);
		}
	}
	// 역방향일 경우
	else
	{
		for (register int i = start; i >= end; i--)
		{
			key = ((key * BASE) + (ULL)code[i]);
		}
	}

	return key;
}

ULL getRollingKey(const int* code, int start, int end, ULL key)
{
	// 정방향일 경우
	if (start < end)
	{
		// 기존 키에 한 단계 곱함
		// end번째 key 추가
		// (start - 1)번째 key 제거
		key = ((key * BASE) + (ULL)code[end] - ((ULL)code[start - 1] * weight));
	}
	// 역방향일 경우
	else
	{
		// 기존 키에 한 단계 곱함
		// end번째 key 추가
		// (start + 1)번째 key 제거
		key = ((key * BASE) + (ULL)code[end] - ((ULL)code[start + 1] * weight));
	}

	return key;
}

void insertHash(int start, int end, ULL key)
{
	// 중복 원소 체크
	for (HashNode* p = hashTable[key].next; p; p = p->next)
	{
		// 시작 코드와 끝 코드가 같으면 같은 데이터로 임의 판단
		if ((program[0][p->start] == program[0][start]) && (program[0][p->end] == program[0][end]))
		{
			// 중복 원소가 있다면 추가할 필요 없다
			return;
		}
	}

	// Hash Table에 추가
	hashBuf[bCnt++].hashAlloc(start, end, &hashTable[key]);

	// 해당 key에 추가했다고 표시
	hashTable[key].cnt++;

	return;
}

void compHash(int start, int end, ULL key, int nowProgram)
{
	// 같은 코드 있는지 체크
	for (HashNode* p = hashTable[key].next; p; p = p->next)
	{
		// 바이러스 코드 후보만 확인
		if (p->cnt != nowProgram)
		{
			continue;
		}

		// 시작 코드와 끝 코드가 같으면 같은 데이터로 임의 판단
		if ((program[0][p->start] == program[nowProgram][start]) && (program[0][p->end] == program[nowProgram][end]))
		{
			// 검출한 횟수 증가
			p->cnt++;

			// 정답 갱신
			if (ans < p->cnt)
			{
				ans = p->cnt;
			}

			// 이미 체크했다면 더 볼 필요 없다
			break;
		}
	}

	return;
}

void init(void)
{
	for (register int i = 0; i < K; i++)
	{
		weight *= BASE;
	}

	for (register int i = 0; i < MAX_HASH; i++)
	{
		hashTable[i].cnt = 0;
		hashTable[i].next = (HashNode*)NULL;
	}

	return;
}

void solve(void)
{
	int start;
	int end;
	ULL key;

	scanf("%d %d", &N, &K);

	init();

	// 첫 번째 프로그램은 Hash Table에 저장
	scanf("%d", &M[0]);

	// 정방향만 수행
	for (register int c = 0; c < M[0]; c++)
	{
		start = c - K + 1;
		end = c;

		scanf("%d", &program[0][c]);

		// 범위 벗어나면 실행하지 않음
		if (start < 0)
		{
			continue;
		}
		// 이미 존재하는 키를 수정하는 경우
		else if (start > 0)
		{
			key = getRollingKey(program[0], start, end, key);
		}
		// 새로운 키를 구하는 경우
		else
		{
			key = getFirstKey(program[0], start, end);
		}

		// Hash Table에 추가
		insertHash(start, end, (key % MAX_HASH));
	}

	// 나머지 프로그램은 첫 번째 프로그램과 비교
	for (register int r = 1; r < N; r++)
	{
		scanf("%d", &M[r]);

		// 정방향
		for (register int c = 0; c < M[r]; c++)
		{
			start = c - K + 1;
			end = c;

			scanf("%d", &program[r][c]);

			// 범위 벗어나면 실행하지 않음
			if (start < 0)
			{
				continue;
			}
			// 이미 존재하는 키를 수정하는 경우
			else if (start > 0)
			{
				key = getRollingKey(program[r], start, end, key);
			}
			// 새로운 키를 구하는 경우
			else
			{
				key = getFirstKey(program[r], start, end);
			}

			// 기존 Hash Table과 비교
			compHash(start, end, (key % MAX_HASH), r);
		}

		// 역방향
		for (register int c = M[r] - 1; c >= 0; c--)
		{
			start = c + K - 1;
			end = c;

			// 범위 벗어나면 실행하지 않음
			if (start > M[r] - 1)
			{
				continue;
			}
			// 이미 존재하는 키를 수정하는 경우
			else if (start < M[r] - 1)
			{
				key = getRollingKey(program[r], start, end, key);
			}
			// 새로운 키를 구하는 경우
			else
			{
				key = getFirstKey(program[r], start, end);
			}

			// 기존 Hash Table과 비교
			compHash(start, end, (key % MAX_HASH), r);
		}
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);
	// freopen("input2.txt", "r", stdin);
	// freopen("input3.txt", "r", stdin);

	solve();

	printf("%s\n", ((ans == N) ? "YES" : "NO"));

	return 0;
}
