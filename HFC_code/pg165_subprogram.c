#include "pg165_subprogram.h"

// float total = 0.0;
short tax_percent = 6;

float add_with_tax(float f)
{
	float tax_rate = 1 + tax_percent / 100.0;
	total = total + (f * tax_rate);
	return total;
}