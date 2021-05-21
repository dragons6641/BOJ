#define _CRT_SECURE_NO_WARNINGS
 
#include <stdio.h>
 
#define MAX_N 1500
#define MAX_M 1500
#define MAX_HASH 1511
// #define MAX_HASH 1125763
// #define MAX_HASH 2250001
// #define MAX_HASH 4500007
// #define MAX_HASH 9000011
#define MAX_BUF ((MAX_N + 1) * (MAX_M + 1)) / 2
#define MAX_ALPHABET 26
 
typedef unsigned long long ULL;
 
struct HashNode
{
    // 구간의 인덱스
    int start;
    int end;
    // 구간 성분의 길이
    int len;
    // Chaining
    HashNode* next;
 
    void hashAlloc(int _start, int _end, int _len, HashNode* _prev)
    {
        start = _start;
        end = _end;
        len = _len;
 
        if (_prev)
        {
            next = _prev->next;
            _prev->next = this;
        }
 
        return;
    }
};
 
// 사용한 버퍼 개수
int bCnt;
// 문자열의 길이
int aLen;
int bLen;
// 두 문자열 중 최소 길이
int minLen;
// 입력 문자열
char A[MAX_N + 1];
char B[MAX_M + 1];
// 계산한 Key값을 저장함
ULL aKeyList[MAX_N];
ULL bKeyList[MAX_M];
// Rolling Hash 가중치 목록
ULL weightList[MAX_ALPHABET];
// 실제 Hash Table
HashNode hashTable[MAX_HASH];
// Hash Table 버퍼
HashNode hashBuf[MAX_BUF];
 
int mstrlen(const char* str)
{
    register int i;
 
    for (i = 0; str[i]; i++);
 
    return i;
}
 
inline int Min(const int& a, const int& b)
{
    return ((a < b) ? a : b);
}
 
inline ULL getBase(ULL key)
{
    return ((key << 5) + key);
}
 
void initWeight(void)
{
    weightList[0] = 1;
 
    for (register int i = 1; i < MAX_ALPHABET; i++)
    {
        weightList[i] = getBase(weightList[i - 1]);
    }
 
    return;
}
 
void initHash(void)
{
    bCnt = 0;
 
    for (register int i = 0; i < MAX_HASH; i++)
    {
        hashTable[i].len = 0;
        hashTable[i].next = (HashNode*)NULL;
    }
}
 
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
 
ULL getFirstKey(const char* str, int start, int end)
{
    ULL key = 0;
 
    for (register int i = start; i <= end; i++)
    {
        key += weightList[str[i] - 'a'];
    }
 
    return key;
}
 
ULL getRollingKey(const char* str, int start, int end, ULL key)
{
    // end번째 정보 추가
    // (start - 1)번째 정보 제거
    return (key + weightList[str[end] - 'a'] - weightList[str[start - 1] - 'a']);
}
 
bool compStr(int as, int ae, int bs, int be)
{
    // 중복일 경우 직접 세면서 계산
    int cntList[MAX_ALPHABET] = { 0, };
 
    // 문자열 A를 확인해 주면서 증가
    for (register int i = as; i <= ae; i++)
    {
        cntList[A[i] - 'a']++;
    }
 
    // 문자열 B를 확인해 주면서 감소
    for (register int i = bs; i <= be; i++)
    {
        cntList[B[i] - 'a']--;
 
        // B 문자열에 이미 더 많은 알파벳이 최소 한 종류 있다면
        if (cntList[B[i] - 'a'] < 0)
        {
            // 서로 다른 문자열
            return false;
        }
    }
 
    // 모두 통과한 경우 서로 같은 문자열
    return true;
}
 
void insertHash(int start, int end, int len, ULL key)
{
    // 중복 검사
    for (HashNode* p = hashTable[key].next; p; p = p->next)
    {
        // 길이가 같으면 직접 세어줘야 함
        if (p->len == len)
        {
            // 문자열 직접 비교
            bool ret = compStr(p->start, p->end, start, end);
 
            // 이미 같은 데이터가 있으면 추가할 필요 없음
            if (ret)
            {
                return;
            }
        }
    }
 
    // 해당 key에 추가
    hashBuf[bCnt++].hashAlloc(start, end, len, &hashTable[key]);
 
    return;
}
 
bool compHash(int start, int end, int len, ULL key)
{
    // 해당 내용 찾기
    for (HashNode* p = hashTable[key].next; p; p = p->next)
    {
        // 길이가 같으면 직접 세어줘야 함
        if (p->len == len)
        {
            // 문자열 직접 비교
            bool ret = compStr(p->start, p->end, start, end);
 
            // 찾은 경우 True 리턴
            if (ret)
            {
                return true;
            }
        }
    }
 
    // 찾지 못한 경우 False 리턴
    return false;
}
 
int solve(void)
{
    register int start;
    register int end;
    bool ret;
    ULL key;
    ULL tmp;
 
    // 최소 길이 찾기
    aLen = mstrlen(A);
    bLen = mstrlen(B);
    minLen = Min(aLen, bLen);
 
    // 1. 최소 길이의 경우만 Hash Table 구한다
    // 매 길이마다 Hash Table 초기화
    initHash();
 
    // AAAA
    // 초기값 설정
    start = 0;
    end = minLen - 1;
    // 첫 번째 키는 모두 읽으면서 생성
    key = getFirstKey(A, start, end);
 
    // key값을 기록
    aKeyList[start] = key;
 
    // Hash Table에 추가
    insertHash(start, end, minLen, (key % MAX_HASH));
 
    // 다음 문자열 Hash
    start++;
    end++;
 
    while (A[end])
    {
        // 나머지 키는 Rolling Hash로 생성
        key = getRollingKey(A, start, end, key);
 
        // key값을 기록
        aKeyList[start] = key;
 
        // Hash Table에 추가
        insertHash(start, end, minLen, (key % MAX_HASH));
 
        // 다음 문자열 Hash
        start++;
        end++;
    }
 
    // BBBB
    // 초기값 설정
    start = 0;
    end = minLen - 1;
 
    // 첫 번째 키는 모두 읽으면서 생성
    key = getFirstKey(B, start, end);
 
    // key값을 기록
    bKeyList[start] = key;
 
    // Hash Table에서 검색
    ret = compHash(start, end, minLen, (key % MAX_HASH));
 
    // 찾은 경우 해당 길이 리턴
    if (ret)
    {
        return minLen;
    }
 
    // 다음 문자열 Hash
    start++;
    end++;
 
    while (B[end])
    {
        // 나머지 키는 Rolling Hash로 생성
        key = getRollingKey(B, start, end, key);
 
        // key값을 기록
        bKeyList[start] = key;
 
        // Hash Table에서 검색
        ret = compHash(start, end, minLen, (key % MAX_HASH));
 
        // 찾은 경우 해당 길이 리턴
        if (ret)
        {
            return minLen;
        }
 
        // 다음 문자열 Hash
        start++;
        end++;
    }
 
    // 2. 최소 길이부터 역순으로 진행
    for (register int len = minLen - 1; len > 0; len--)
    {
        // 매 길이마다 Hash Table 초기화
        initHash();
 
        // AAAA
        // 백업
        tmp = aKeyList[0];
 
        // 초기값 설정
        start = aLen - len;
        end = aLen - 1;
 
        while (start > 0)
        {
            // 나머지 키는 이전 키에서 첫 원소 제외
            key = aKeyList[start - 1] - weightList[A[start - 1] - 'a'];
 
            // key값을 기록
            aKeyList[start] = key;
 
            // Hash Table에 추가
            insertHash(start, end, len, (key % MAX_HASH));
 
            // 다음 문자열 Hash
            start--;
            end--;
        }
 
        // 첫 번째 키는 이전 키에서 마지막 원소 제외
        key = tmp - weightList[A[len] - 'a'];
 
        // key값을 기록
        aKeyList[start] = key;
 
        // Hash Table에 추가
        insertHash(start, end, len, (key % MAX_HASH));
 
        // BBBB
        // 백업
        tmp = bKeyList[0];
 
        // 초기값 설정
        start = bLen - len;
        end = bLen - 1;
 
        while (start > 0)
        {
            // 나머지 키는 이전 키에서 첫 원소 제외
            key = bKeyList[start - 1] - weightList[B[start - 1] - 'a'];
 
            // key값을 기록
            bKeyList[start] = key;
 
            // Hash Table에서 검색
            ret = compHash(start, end, len, (key % MAX_HASH));
 
            // 찾은 경우 해당 길이 리턴
            if (ret)
            {
                return len;
            }
 
            // 다음 문자열 Hash
            start--;
            end--;
        }
 
        // 첫 번째 키는 이전 키에서 마지막 원소 제외
        key = tmp - weightList[B[len] - 'a'];
 
        // key값을 기록
        bKeyList[start] = key;
 
        // Hash Table에서 검색
        ret = compHash(start, end, len, (key % MAX_HASH));
 
        // 찾은 경우 해당 길이 리턴
        if (ret)
        {
            return len;
        }
    }
 
    return 0;
}
 
int main(void)
{
    // freopen("input1.txt", "r", stdin);   // 0
    // freopen("input2.txt", "r", stdin);   // 7
    // freopen("input3.txt", "r", stdin);   // 11
    // freopen("input4.txt", "r", stdin);   // 3
    // freopen("input5.txt", "r", stdin);   // 4
 
    initWeight();
 
    scanf("%s %s", &A, &B);
 
    int ans = solve();
 
    printf("%d\n", ans);
 
    return 0;
}
