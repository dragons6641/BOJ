/*
1008 A/B
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_A 10
#define MAX_B 10

int main(void)
{
	double A;
	double B;

	scanf("%lf %lf", &A, &B);

	double ans = A / B;

	printf("%.10lf\n", ans);

	return 0;
}
