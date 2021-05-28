#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>

#define MAX_N 49
#define MAX_M 100
#define MAX_DIR 4
#define MAX_SHIFT ((MAX_N - 1) / 2)
#define MIN_EXPLOSION_LEN 4

struct MagicNode
{
	// 시전 방향
	int dir;
	// 사정 거리
	int shift;
};

// 격자의 크기
int N;
// 블리자드 시전 횟수
int M;
// 1×(폭발한 1번 구슬의 개수) + 2×(폭발한 2번 구슬의 개수) + 3×(폭발한 3번 구슬의 개수)
int answer;
// 전체 칸의 갯수
int squareCnt;
// 블리자드 시전 방향
int dr[MAX_DIR + 1] = { 0, -1, 1, 0, 0 };
int dc[MAX_DIR + 1] = { 0, 0, 0, -1, 1 };
// 칸 번호 진행 방향 순서
int dirOrderArr[MAX_DIR] = { 3, 2, 4, 1 };
// 블리자드 격자판
int blizzardArr[MAX_N + 2][MAX_N + 2];
// 블리자드 목표 미리 구하기
int targetArr[MAX_DIR + 1][MAX_SHIFT + 1];
// 구슬의 번호 기록
std::vector<int> marbleVector;
// 블리자드의 방향과 사정거리 정보
std::vector<MagicNode> magicVector;

void inputData(void)
{
	int dir;
	int shift;

	std::cin >> N >> M;

	// 상수 초기화
	squareCnt = N * N - 1;

	// 벡터 초기화
	marbleVector.reserve(squareCnt);
	magicVector.reserve(M);

	for (register int r = 1; r <= N; r++)
	{
		for (register int c = 1; c <= N; c++)
		{
			std::cin >> blizzardArr[r][c];
		}
	}

	for (register int i = 0; i < M; i++)
	{
		std::cin >> dir >> shift;

		magicVector.push_back({ dir, shift });
	}

	return;
}

void initMarble(void)
{
	// 센터에서 시작
	int curR = (N + 1) / 2;
	int curC = (N + 1) / 2;
	// 반시계 방향 기록
	int dirIdx = 0;
	int curDir = dirOrderArr[dirIdx];
	// 같은 방향으로 이동한 거리 기록
	int curShift = 0;
	int maxShift = 1;

	// 1번 칸부터 순차적으로 순회
	for (register int i = 0; i < squareCnt; i++)
	{
		// 다음 칸으로 이동
		curR += dr[curDir];
		curC += dc[curDir];

		// 구슬이 있을 경우 벡터에 추가
		if (blizzardArr[curR][curC] > 0)
		{
			marbleVector.push_back(blizzardArr[curR][curC]);
		}

		// 같은 방향으로 최대로 이동했을 경우
		if (++curShift == maxShift)
		{
			// 다음 방향으로 바꾸기
			dirIdx = (dirIdx + 1) % MAX_DIR;
			curDir = dirOrderArr[dirIdx];

			// 같은 방향으로 이동한 거리 초기화
			curShift = 0;

			// 현재 방향이 오른쪽이나 왼쪽 방향이면 최대 이동거리 증가
			if (curDir > 2)
			{
				maxShift++;
			}
		}
	}

	return;
}

void initTarget(void)
{
	int curTarget = 0;
	int shiftDiff = 2;

	// 블리자드를 시전할 칸을 계차수열로 구하기
	for (register int targetIdx = 1; targetIdx <= (N - 1) / 2; targetIdx++)
	{
		for (register int dirIdx = 0; dirIdx < MAX_DIR; dirIdx++)
		{
			targetArr[dirOrderArr[dirIdx]][targetIdx] = curTarget;
			curTarget += shiftDiff;
		}

		curTarget += 1;
		shiftDiff += 2;
	}

	return;
}

void destroyMarble(int magicIdx)
{
	int dir = magicVector[magicIdx].dir;
	int shift = magicVector[magicIdx].shift;

	for (register int targetIdx = 1; targetIdx <= shift; targetIdx++)
	{
		// 블리자드 시전할 구슬 찾기
		int destroyIdx = targetArr[dir][targetIdx];

		// 구슬이 있을 경우에 일단 지운다고 표시만 해두자
		if (destroyIdx < marbleVector.size())
		{
			marbleVector[destroyIdx] = 0;
		}
	}

	return;
}

void moveMarble(void)
{
	// 원본 벡터를 순회할 반복자
	register std::vector<int>::iterator iter = marbleVector.begin();

	while (iter != marbleVector.end())
	{
		// 빈 공간일 경우 삭제
		if (*iter == 0)
		{
			// erase 함수는 해당 요소를 제거하고 그 다음 요소의 iter를 반환
			iter = marbleVector.erase(iter);
		}
		else
		{
			// 제거하지 않을 때는 그냥 증가
			iter++;
		}
	}

	return;
}

bool explodeMarble(void)
{
	// 폭발했는지 여부 표시
	bool isExploded = false;

	// 그룹 범위
	int startIdx = 0;
	int endIdx = 0;
	int groupLen = 0;

	// 이전 구슬의 종류
	int prevMarbleVal = 0;

	for (register int curIdx = 0; curIdx < marbleVector.size(); curIdx++)
	{
		// 이전 구슬과 현재 구슬이 같은 종류일 경우
		if (prevMarbleVal == marbleVector[curIdx])
		{
			// 현재 구간 연장
			endIdx = curIdx;
		}
		// 이전 구슬과 현재 구슬이 다른 종류일 경우
		else
		{
			groupLen = endIdx - startIdx + 1;

			// 이전 폭발 범위가 4 이상일 경우 [폭★8]
			if (groupLen >= MIN_EXPLOSION_LEN)
			{
				for (register int explodeIdx = startIdx; explodeIdx <= endIdx; explodeIdx++)
				{
					marbleVector[explodeIdx] = 0;
				}

				isExploded = true;
				answer += groupLen * prevMarbleVal;
			}

			// 새로운 구간으로 갱신
			startIdx = curIdx;
			endIdx = curIdx;
			prevMarbleVal = marbleVector[curIdx];
		}
	}

	groupLen = endIdx - startIdx + 1;

	// 마지막 구간 한 번 더 [폭★8]
	if (groupLen >= MIN_EXPLOSION_LEN)
	{
		for (register int explodeIdx = startIdx; explodeIdx <= endIdx; explodeIdx++)
		{
			marbleVector[explodeIdx] = 0;
		}

		isExploded = true;
		answer += groupLen * prevMarbleVal;
	}

	return isExploded;
}

void changeMarble(void)
{
	// 그룹 범위
	int startIdx = 0;
	int endIdx = 0;
	int groupLen = 0;

	// 이전 구슬의 종류
	int prevMarbleVal = 0;

	// 변화 결과를 저장할 임시 벡터
	std::vector<int> tmpVector;

	tmpVector.reserve(squareCnt);

	for (register int curIdx = 0; curIdx < marbleVector.size(); curIdx++)
	{
		// 이전 구슬과 현재 구슬이 같은 종류일 경우
		if (prevMarbleVal == marbleVector[curIdx])
		{
			// 현재 구간 연장
			endIdx = curIdx;
		}
		// 이전 구슬과 현재 구슬이 다른 종류일 경우
		else
		{
			// 처음일 경우는 제외
			if (prevMarbleVal == 0)
			{
				// 새로운 구간으로 갱신
				startIdx = curIdx;
				endIdx = curIdx;
				prevMarbleVal = marbleVector[curIdx];

				continue;
			}

			// 임시 벡터에 구간 갯수 저장
			groupLen = endIdx - startIdx + 1;
			tmpVector.push_back(groupLen);

			// 임시 벡터에 구슬 종류 저장
			tmpVector.push_back(prevMarbleVal);

			// 새로운 구간으로 갱신
			startIdx = curIdx;
			endIdx = curIdx;
			prevMarbleVal = marbleVector[curIdx];

			// 구간 벗어났는지 확인
			if (tmpVector.size() >= squareCnt)
			{
				break;
			}
		}
	}

	// 구간 벗어났는지 확인
	if (tmpVector.size() < squareCnt)
	{
		// 임시 벡터에 구간 갯수 저장
		groupLen = endIdx - startIdx + 1;
		tmpVector.push_back(groupLen);

		// 임시 벡터에 구슬 종류 저장
		tmpVector.push_back(prevMarbleVal);
	}

	// 원본 벡터 초기화
	marbleVector.clear();
	marbleVector.resize(tmpVector.size());

	// 임시 배열 결과를 원본 배열에 복사
	std::copy(tmpVector.begin(), tmpVector.end(), marbleVector.begin());

	return;
}

void solve(void)
{
	bool isNotFinished;

	// 마법사 상어는 블리자드를 총 M번 시전했다. 
	for (register int i = 0; i < M; i++)
	{
		// 1. 상어는 di 방향으로 거리가 si 이하인 모든 칸에 얼음 파편을 던져 그 칸에 있는 구슬을 모두 파괴한다. 
		destroyMarble(i);

		// 구슬이 이동한 후에는 다시 구슬이 폭발하는 단계이고, 이 과정은 더 이상 폭발하는 구슬이 없을때까지 반복된다. 
		do
		{
			// 2. 만약 어떤 칸 A의 번호보다 번호가 하나 작은 칸이 빈 칸이면, A에 있는 구슬은 그 빈 칸으로 이동한다. 
			moveMarble();
		}
		// 3. 폭발하는 구슬은 4개 이상 연속하는 구슬이 있을 때 발생한다. 
		while (explodeMarble());

		if (marbleVector.size() == 0)
		{
			break;
		}

		// 4. 이제 더 이상 폭발한 구슬이 없기 때문에, 구슬이 변화하는 단계가 된다. 
		changeMarble();
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);	// 28
	// freopen("input2.txt", "r", stdin);	// 0
	// freopen("input3.txt", "r", stdin);	// 39
	// freopen("input4.txt", "r", stdin);	// 62
	// freopen("input5.txt", "r", stdin);	// 97
	// freopen("input6.txt", "r", stdin);	// 86
	// freopen("input7.txt", "r", stdin);	// 442
	// freopen("input8.txt", "r", stdin);	// 164
	// freopen("input9.txt", "r", stdin);	// 8
	// freopen("input10.txt", "r", stdin);	// 0

	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	inputData();

	initMarble();

	initTarget();

	solve();

	std::cout << answer;

	return 0;
}
