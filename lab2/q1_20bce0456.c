#include <omp.h>
#include <stdio.h>
#define N 1000

int main() {
int i, sum = 0;
#pragma omp parallel for reduction(+:sum)
for (i = 0; i < N; i++) {
sum += i;
}
printf("Sum of first %d numbers = %d\n", N, sum);
return 0;
}