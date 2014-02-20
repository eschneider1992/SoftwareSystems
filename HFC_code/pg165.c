#include <stdio.h>
#include "pg165_subprogram.h"

float total = 0.0;
short count = 0;

int main()
{
	float val;
	printf("Price of item: ");
	while (scanf("%f", &val) == 1) {
		// total = add_with_tax(val);
		printf("Total so far: %.2f\n", total);
		printf("Price of item: ");
		count += 1;
	}
	printf("\nFinal total: %.2f\n", total);
	printf("Number of items: %hi\n", count);
	return 0;
}
