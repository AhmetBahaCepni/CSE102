#include "util.h"

void part1()
{
    int year;

    printf("Please enter a year: ");
    scanf("%d", &year);

    if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) // a year is a leap year if its divisible by 4 but not 100 or if it divisible by 400
    {
        printf("%d is a leap year\n", year);
    }
    else
    {
        printf("%d is not a leap year\n", year);
    }
}

void part2()
{
    char format, op; // format for printing format and op for operation sign (+-/*)
	double num1, num2, result; // we declared these variables as double because we could find float results
    int m, n;

    printf("Enter the format of output (S or I): ");
    scanf(" %c", &format); // we scan char values by %c

    if(format == 'S')
    {
        printf("Enter m and n values(m cant be smaller than n): ");
        scanf("%d %d", &m, &n); // we scan integer values by %d
    }

    printf("Enter the operation (+, -, /, *, %%, !, ^): ");
    scanf(" %c", &op);
    
    if(op == '!') // ! operation only have 1 argument
    {
        printf("Enter the operand: ");
        scanf("%lf", &num1); // we scan double values by %lf
    }
    else
    {
        printf("Enter the first operand: ");
        scanf("%lf", &num1);  // we scan double values by %lf
        printf("Enter the second operand: ");
        scanf("%lf", &num2);
    }
    
    result = make_calc(op, num1, num2); // make_calc function makes the calculations using switch-case statements and returns result
    if (result == -1.888999) // i use this value as EXIT_NUM if make_calc returns this this means something wrong
	{
        printf("You entered an invalid operation, valid inputs are (+, -, /, *, %%, !, ^)\n");
        return;
	}
    
    if (format == 'S')
	{
        if(op == '!')
        {
            printf("%d! = ", (int)num1);  // this part is for the "5! =" string to be printed
        }
        else
        {
            printf("%d%c%d = ", (int)num1, op, (int)num2); // this part is for the "12+34 =" string to be printed
        }
	    scientific_print(result, m, n); // ths function converts result as user wanted according to m and n values and prints result
	    return; // after scientific_print called we return to main because we dont want to part2 function to keep going
	}
    if (op == '!')
    {
        printf("%d %c = %d", (int)num1, op, (int)result);
        return; // after ! operation completed we return to main because we dont want to part2 function to keep going
    }
    printf("%d %c %d = %d",(int)num1, op, (int)num2, (int)result); // this is for FORMAT==I situation and it prints the result as integer 
}

void part3()
{
    double exam1, exam2, exam3, hw1, hw2;
    double final_grade;

    printf("Enter 3 exam grades of student: ");
    scanf("%lf %lf %lf", &exam1, &exam2, &exam3); // we scan these values as double because result could be 56.5 or something and result is calculated by these values
    printf("Enter 2 assignment grades of student: ");
    scanf("%lf %lf", &hw1, &hw2);

    final_grade = ((exam1+exam2+exam3)/3*0.6)+((hw1+hw2)/2*0.4); // th's part is simple calculaton of grade
    if (final_grade >= 60)
    {
        printf("Final Grade: %.1lf Passed!\n", final_grade);
    }
    else
    {
        printf("Final Grade: %.1lf Failed!\n", final_grade);
    }
}

int main(void)
{
    // in main we call parts one by one then terminate the program
    printf("\n------PART 1------\n");
    part1();
    printf("\n------PART 2------\n");
    part2();
    printf("\n------PART 3------\n");
    part3();
}