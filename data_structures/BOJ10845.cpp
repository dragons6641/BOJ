#define _CRT_SECURE_NO_WARNINGS
#define MAX_N 10000

#include <stdio.h>

int queue[MAX_N];
int fp = 0;
int bp = 0;

using namespace std;

void print_queue()
{
	printf("queue : ");

	for (int i = fp; i < bp; i++)
	{
		printf("%d ", queue[i]);
	}

	printf("\n");

	return;
}

void push(int num)
{
	queue[bp] = num;
	bp += 1;

	return;
}

int pop()
{
	int result = 0;

	// 비어있을 경우
	if (fp == bp)
	{
		result = -1;
	}
	// 일반적인 경우
	else
	{
		result = queue[fp];
		fp += 1;
	}

	return result;
}

int size()
{
	return (bp - fp);
}

int empty()
{
	int result = 0;

	// 비어있을 경우
	if (fp == bp)
	{
		result = 1;
	}
	// 일반적인 경우
	else
	{
		result = 0;
	}

	return result;
}

int front()
{
	int result = 0;

	// 비어있을 경우
	if (fp == bp)
	{
		result = -1;
	}
	// 일반적인 경우
	else
	{
		result = queue[fp];
	}

	return result;
}

int back()
{
	int result = 0;

	// 비어있을 경우
	if (fp == bp)
	{
		result = -1;
	}
	// 일반적인 경우
	else
	{
		result = queue[bp - 1];
	}

	return result;
}

int main()
{
	int n = 0;
	int x = 0;
	int tmp = 0;
	char cmd[20];

	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		scanf("%s", &cmd);

		// push
		if ((cmd[0] == 'p') && (cmd[1] == 'u') && (cmd[2] == 's') && (cmd[3] == 'h'))
		{
			scanf("%d", &x);

			push(x);
		}

		// pop
		else if ((cmd[0] == 'p') && (cmd[1] == 'o') && (cmd[2] == 'p'))
		{
			tmp = pop();

			printf("%d\n", tmp);
		}

		// size
		else if ((cmd[0] == 's') && (cmd[1] == 'i') && (cmd[2] == 'z') && (cmd[3] == 'e'))
		{
			tmp = size();

			printf("%d\n", tmp);
		}

		// empty
		else if ((cmd[0] == 'e') && (cmd[1] == 'm') && (cmd[2] == 'p') && (cmd[3] == 't') && (cmd[4] == 'y'))
		{
			tmp = empty();

			printf("%d\n", tmp);
		}

		// front
		else if ((cmd[0] == 'f') && (cmd[1] == 'r') && (cmd[2] == 'o') && (cmd[3] == 'n') && (cmd[4] == 't'))
		{
			tmp = front();

			printf("%d\n", tmp);
		}

		// rear
		else if ((cmd[0] == 'b') && (cmd[1] == 'a') && (cmd[2] == 'c') && (cmd[3] == 'k'))
		{
			tmp = back();

			printf("%d\n", tmp);
		}

		// error
		else
		{

		}

		// print_queue();
	}

	return 0;
}
