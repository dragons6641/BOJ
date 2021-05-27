#define _CRT_SECURE_NO_WARNINGS

#define MAX_T 20
#define MAX_SM 100000
#define MAX_SC 4096
#define MAX_SI 4096
#define MAX_STACK ((MAX_SC / 2) + 1)
#define MAX_LOOP 50000000
#define MOD 256

#include <stdio.h>

// unsigned char : 0 ~ 255
typedef unsigned char UC;

// 테스트 케이스의 개수
int T;
// 메모리(배열)의 크기
int SM;
// 프로그램 코드의 크기
int SC;
// 입력의 크기
int SI;
// 명령 포인터
int cmdPtr;
// 입력 포인터
int inputPtr;
// 메모리 포인터
int memPtr;
// 무한 루프 시작점
int loopStart;
// 무한 루프 종료점
int loopEnd;
// 스택 포인터
int top;
// 명령어 실행 횟수
int cmdCnt;
// 자신의 짝 위치 기록
int pairPos[MAX_SC];
// 괄호 짝 찾기 용도
int stack[MAX_STACK + 1];
// 무한 루프 여부
bool isLoop;
// Brainfuck 프로그램
char cmdList[MAX_SC + 1];
// 프로그램의 입력
char inputList[MAX_SI + 1];
// 메모리(배열)
UC memList[MAX_SM + 1];

void inputData(void)
{
	// 각 테스트 케이스는 세 줄로 이루어져 있다. 
	// 첫째 줄에는 sm, sc, si가 주어진다. 
	// sm은 메모리(배열)의 크기이고, sc는 프로그램 코드의 크기, si는 입력의 크기이다. (0 < sm ≤ 100,000, 0 < sc, si < 4096)
	scanf("%d %d %d", &SM, &SC, &SI);
	// 둘째 줄에는 Brainf**k 프로그램이 주어진다.
	// 프로그램은 sc개의 문자로 이루어져 있다.
	scanf("%s", cmdList);
	// 셋째 줄에는 프로그램의 입력이 주어진다. (공백이 아니면서 출력할 수 있는 문자만 주어진다)
	scanf("%s", inputList);

	return;
}

void init(void)
{
	// 프로그램을 수행하기 전에, 데이터 배열의 값은 0으로 초기화되어 있고, 포인터가 가리키는 칸은 0번 칸이다.
	cmdPtr = 0;
	inputPtr = 0;
	memPtr = 0;
	loopStart = MAX_SC;
	loopEnd = -1;
	top = 0;
	cmdCnt = 0;
	isLoop = false;

	for (register int i = 0; i < SC; i++)
	{
		pairPos[i] = -1;
	}

	for (register int i = 0; i <= SM; i++)
	{
		memList[i] = 0;
	}

	// 코드를 쭉 보면서 괄호 짝의 위치를 미리 알아둔다. 
	for (register int i = 0; i < SC; i++)
	{
		if (cmdList[i] == '[')
		{
			stack[++top] = i;
		}
		else if (cmdList[i] == ']')
		{
			pairPos[i] = stack[top];
			pairPos[stack[top]] = i;

			top--;
		}
	}

	return;
}

void execute(void)
{
	// 프로그램이 명령어를 50,000,000번 이상 수행한 경우, 프로그램은 항상 종료되었거나 무한 루프에 빠져있다. 
	// 무한 루프일 경우, 해당 루프는 적어도 한 번 실행이 완료된 상태이며, 한 번의 무한 루프에서 실행되는 명령어의 개수는 50,000,000개 이하이다.
	while (cmdList[cmdPtr])
	{
		switch (cmdList[cmdPtr])
		{
			// - : 포인터가 가리키는 수를 1 감소시킨다. (modulo 2^8)
			case '-':
			{
				memList[memPtr] = (memList[memPtr] + MOD - 1) % MOD;

				break;
			}
			// + : 포인터가 가리키는 수를 1 증가시킨다. (modulo 2^8)
			case '+':
			{
				memList[memPtr] = (memList[memPtr] + 1) % MOD;

				break;
			}
			// < : 포인터를 왼쪽으로 한 칸 움직인다.
			case '<':
			{
				memPtr = (memPtr + SM - 1) % SM;

				break;
			}
			// > : 포인터를 오른쪽으로 한 칸 움직인다.
			case '>':
			{
				memPtr = (memPtr + 1) % SM;

				break;
			}
			// [ : 만약 포인터가 가리키는 수가 0이라면, [ 와 짝을 이루는 ] 의 다음 명령으로 점프한다.
			case '[':
			{
				// Terminate
				if (memList[memPtr] == 0)
				{
					cmdPtr = pairPos[cmdPtr];
				}

				break;
			}
			// ] : 만약 포인터가 가리키는 수가 0이 아니라면, ] 와 짝을 이루는 [ 의 다음 명령으로 점프한다.
			case ']':
			{
				// Loop
				if (memList[memPtr] != 0)
				{
					cmdPtr = pairPos[cmdPtr];
				}

				break;
			}
			// . : 포인터가 가리키는 수를 출력한다.
			case '.':
			{
				break;
			}
			// , : 문자 하나를 읽고 포인터가 가리키는 곳에 저장한다. 
			case ',':
			{
				if (inputList[inputPtr])
				{
					memList[memPtr] = (UC)inputList[inputPtr++];
				}
				else
				{
					// 입력의 마지막(EOF)인 경우에는 255를 저장한다.
					memList[memPtr] = MOD - 1;
				}

				break;
			}
			default:
			{
				return;
			}
		}

		cmdCnt++;

		if ((cmdCnt > MAX_LOOP) && (loopStart > cmdPtr))
		{
			loopStart = cmdPtr;
			loopEnd = pairPos[cmdPtr];
		}

		if (cmdCnt > MAX_LOOP * 2)
		{
			isLoop = true;

			break;
		}

		cmdPtr++;
	}

	return;
}

void outputData(void)
{
	// 각 테스트 케이스에 대해서, 프로그램이 종료된다면 "Terminates"를, 무한 루프에 빠지게 된다면 "Loops"를 출력한다.
	if (isLoop)
	{
		// 무한 루프에 빠졌을 때는, 프로그램의 어느 부분이 무한 루프인지를 출력한다. ([와 ]의 위치)
		printf("Loops %d %d\n", loopStart, loopEnd);
	}
	else
	{
		printf("Terminates\n");
	}

	return;
}

void solve(void)
{
	// 첫째 줄에 테스트 케이스의 개수 t (0 < t ≤ 20)가 주어진다.
	scanf("%d", &T);

	for (register int testCase = 1; testCase <= T; testCase++)
	{
		inputData();

		init();

		execute();

		outputData();
	}

	return;
}

int main(void)
{
	// freopen("input1.txt", "r", stdin);

	solve();

	return 0;
}
