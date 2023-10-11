#include "util.h"

int find_pow(int a, int b) // this function is for calculating the power of numbers
{
    int result;

    result = 1;
    while(b > 0)
    {
        result *= a; // we multiply 'a' by itself 'b' times
        b--;
    }
    return result;
}

int find_factorial(int a) // this function is for calculating the factorial of numbers
{
    int result;

    result = 1;
    while (a > 0)
    {
        result *= a; //we multiply result by 'a' and decrease 'a' until it is 0
        a--;
    }
}

int digit(int num) // this function is for calculating the digit count of numbers
{
    int digit = 0;
    while(num) // we could write (num != 0) too but its the same thing
    {
        num /= 10; // we divide the number by 10 until it is 0 .... 123/10/10/10 = 0 so it is 3 digits
        digit++;
    }
    return digit;
}

void scientific_print(double result, int m, int n)
{
    int power_holder = 0; // this value stands for the value after e ... for example in 0.12e5.. , 5 is this value
    int startingZeros = 0;
    int temp = n; // i will need this temporary value

	while ((double)(int)result != result) // if integer value of a double is same with itself it means it has no digits after point
	{
        result *= 10; // we multiply the fractional numbers by 10 until it has no digits after point 3.68 ->> 368*10^-2
        power_holder--;
	}
    while ((int)result%10 == 0) // i need the 12 in 120000 number so i get rid of zeros and hold them as the 10th power value
    {
        result /= 10;
        power_holder++;
    }
    while (temp>0) // i divide the result n times so it could have exact n digits after point
    {
        result /= 10;
        temp--;
        power_holder++;     //10^-
    }
    startingZeros = m - digit((int)result) - n; // if we subtract the digit count before and after the n value from m it will give us how much 0 we need to complete m
    if((int)result == 0) // this part needed when result is lower than 1 because 0.625 own its own 0 and i dont need to print it
        startingZeros--;
    for (int i = 0; i < startingZeros; i++)
    {
        printf("0");
    }
    
    printf("%.*fe%d \n", n, result, power_holder); // we only print n digits after point because after that its all zeros like 12.35400000 when n is 3
}


double make_calc(char op, double a, double b)
{
    switch(op) // i use switch-case statement to check what operation user wants and return the result
   {
       case '+' :
            return a+b;

       case '-' :
            return a-b;
       case '/' :
            return a/b;
       case '*' :
            return a*b;
       case '%' :
            return fmod(a, b); // fmod is a math.h function that takes mod of fractional numbers
       case '!' :
            return find_factorial(a); // this is my factorial calculation function
       case '^' :
            return find_pow(a, b); // this is my power calculation function
       default:
            return -1.888999; // I use this value as my EXIT_NUM main function will understand something wrong if result is this 
   }
}