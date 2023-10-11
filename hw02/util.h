#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>
#include <math.h>

int find_pow(int a, int b);
int find_factorial(int a);
int digit(int num);
void scientific_print(double result, int m, int n);
double make_calc(char op, double a, double b);

#endif /* _UTIL_H_ */