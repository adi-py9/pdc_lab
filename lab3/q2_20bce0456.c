#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<math.h>

#define PI 3.1415926538837211

int main()
{
	int num_intv, i;
	float sum, x, total_sum, y, partial_sum, sum_thread;
	printf("Enter the number of intervals\n");
	scanf("%d", &num_intv);
	if (num_intv <= 0)//constraint/condition
    {
		printf("No. of intervals should be positive integer!!!");
		exit(1);//exit
	}
	sum = 0.0;
	y = 1.0 / num_intv;

#pragma omp parallel for private(x) shared(sum_thread)
	for (i = 1; i < num_intv + 1; i = i + 1)
    {
		x = y * (i - 0.5);

//OpenMP Critical Section Directive
#pragma omp critical
		sum_thread = sum_thread + 4.0 / (1 + x * x);
	}
	partial_sum = sum_thread * y;

//OpenMP Critical Section Directive 
#pragma omp critical
	sum = sum + partial_sum;
	printf("The value of PI: %f \nError: %1.16f\n", sum, fabs(sum - PI));
}