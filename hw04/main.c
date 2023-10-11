#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int	find_digits(int num) // This Funciton is used to calculate digits of integers
{
	int digit = 0;
	while (num != 0)
	{
		num /= 10;
		digit++;
	}
	return digit;
}


// We print spaces to the receipt file more than 3 times so i write this
void print_spaces(FILE *out, int size, int len)
{
	for (int i = 0; i < size-len; i++)
	{
		fprintf(out, " ");
	}
}

void print_menu() // This Function prints the menu that user sees as first
{
	FILE *inp; 
    char mychar;
	int isOver; 
	int fscanf_return;

    inp = fopen("menu.txt", "r"); // we open with "r" because i will only read
	
	printf("Yemek Listesi:\n");	
	while (mychar != '\n') // we skip the first column that contains "Product        Price (TL)" by reading until newline because we dont want to print this
	{
		fscanf(inp, "%c", &mychar);
	}
	int i = 1; //this variable is for the order point so its 1.Kebab 2.lahmacun so we use it in here 
	isOver = 0; // this is our while exit statement so i make this 1 when i read EOF so we can get out of loop
	while(!isOver)
	{
		if(fscanf(inp, "%c", &mychar) == EOF) // we first check for EOF
			break;
		printf("%d. ", i);
		while (mychar != ' ')  // we print until we see a space
		{
			printf("%c", mychar);
			fscanf(inp, "%c", &mychar);
		}
		printf("\n");
		fscanf_return = fscanf(inp, "%c", &mychar); // we use fscanf_return variable to check if fscanf returns EOF or not
		while (mychar != '\n' && fscanf_return != EOF) // we read until new line so we could get to the next line
		{
			fscanf_return = fscanf(inp, "%c", &mychar);
		}
		if (mychar != '\n') // for exit the loop above (mychar != '\n' && fscanf_return != EOF) should be true so if my_char still not '\n' it means we are at END OF FILE
		{
			isOver = 1;
		}
		i++;
	}
	fclose(inp); // we close the file we opened
}

void print_receipt() // this function called last to print receipt to the terminal
{
	FILE *inp;
	int fscanf_return;
	char mychar;
	inp = fopen("receipt.txt", "r"); // we open the receipt file with 'r' beacuse we will read from it and print to terminal

	fscanf_return = 0;
	fscanf_return = fscanf(inp, "%c", &mychar);
	printf("\n");
	while (fscanf_return != EOF) // print the file until fscanf_return != EOF means that prit the all file until end
	{
		printf("%c", mychar);
		fscanf_return = fscanf(inp, "%c", &mychar);
	}
}


// This function below called from fill receipt function to print name and prices of selected foods form menu

// we take 4 variables as argument;  1-(out) we use this argument to print to the file that we opened in fill_receipt function
// 2-(index) is the index of the selected food in menu so that we can print the right food.  3-(count) is the amount of selected food
// 4-(len) is the count of printed characters to the line so that we can calculate how many spaces we will print to make alignment right
double printFromIndex(FILE *out, int index, int count, int len)
{
	FILE *inp;
	inp = fopen("menu.txt", "r");

	char mychar;
	double price;
	for (int i = 0; i <= index; i++)
	{
		if (i != index) // while i not index it means we are not at the selected line so we pass these lines
		{
			fscanf(inp, "%c", &mychar);
			while (mychar != '\n' && mychar)
			{
				fscanf(inp, "%c", &mychar);
			}
		}
		else // if i==index that means we are at the selected line now
		{
			fscanf(inp, "%c", &mychar);
			while (mychar != ' ') // we fprint until space and count the printed characters in variable len
			{
				len += fprintf(out, "%c", mychar);
				fscanf(inp, "%c", &mychar);
			}
			fscanf(inp, "%lf", &price); // now we are on space and there is only a double number ahead of line so we can scan as double to the price variable
			len += (find_digits((int)price * count) + 3);  // we add the digits of number using find_digits and there is always 2 digits after point so we add 3
			print_spaces(out, 36, len); // print spaces function prints spaces to the file 36-len times
			fprintf(out, "%.2f\n", count*price);
			return price*count; // we return price*count so total price could be calculated
		}
	}
	fclose(inp); // we close the file
}

void fill_receipt() // we take input from user according the menu printed and write selected foods and prices to receipt.txt
{
	FILE *out;
	int index, count, len;
	double total_price, discount;
	char isStudent;

    out = fopen("receipt.txt", "w"); // we create the receipt.txt file to print orders to it

	time_t my_time;
	struct tm * timeinfo;
	char my_str[50];
	time(&my_time);
	timeinfo = localtime(&my_time);
	strftime(my_str, 50, "%d.%m.%Y/%H:%S", timeinfo);

	fprintf(out, "20180000001         %s\n", my_str);
	fprintf(out, "------------------------------------\n");
	fprintf(out, "Product                   Price (TL)\n");
	fprintf(out, "------------------------------------\n");

	isStudent = 'Q'; // we assign a random char to this variable we will scan later
	discount = 0;
	total_price = 0;

	printf("Please choose a product (1-8): ");
	scanf("%d", &index);
	while(index != 0) // order is not completed until 0 input
	{
		printf("How many servings do you want? ");
		scanf("%d", &count);
		if (count == 0) 
		{
			break;
		}

		len = 0; // we reset the len
		if (count != 1)
		{
			fprintf(out, "%d* ", count); // we print "count*" part of the "5* doner"
			len += (find_digits(count)+2); // in here we add digit count of the count and +2 for the "* " part
		}
		total_price += printFromIndex(out, index, count, len); // we call the function to print the names and prices of the food to the receipt.txt
		printf("Please choose a product (1-8): ");
		scanf("%d", &index);
	}
	fprintf(out, "\nTotal:");
	print_spaces(out, 33, (6+find_digits((int)total_price))); // we call this function to print space 33-len times
	fprintf(out, "%.2lf\n", total_price);
	while(isStudent != 'Y' && isStudent != 'N') // we call for if user is student or not and we ask until a valid answer
	{
		printf("Are you student? (Y,N): ");
		scanf(" %c", &isStudent);

		if (isStudent != 'Y' && isStudent != 'N')
		{
			printf("Please enter a valid answer!\n");
		}
	}
	if(isStudent == 'Y') // we fprint to receipt the student discount part
	{
		fprintf(out, "Student discount:");
		print_spaces(out, 33, (17+1+find_digits((int)(total_price*12.5/100))));
		fprintf(out, "-%.2lf\n", total_price*12.5/100);
		discount += total_price*12.5/100;
	}
	if (total_price > 150) // we fprint to receipt the additional discount part
	{
		fprintf(out, "Additional discount:");
		print_spaces(out, 33, (20+1+find_digits((int)(total_price/10))));
		fprintf(out, "-%.2lf\n", total_price/10);
		discount += total_price/10;
	}
	fprintf(out, "------------------------------------\n");

	fprintf(out, "Price:"); // we fprint the discounted price
	print_spaces(out, 33, (6+find_digits((int)(total_price-discount))));
	fprintf(out, "%.2lf\n", total_price-discount);

	fprintf(out, "Price + VAT:"); // we fprint the price after TAX's
	print_spaces(out, 33, (12+find_digits((int)((total_price-discount)*118/100))));
	fprintf(out, "%.2lf\n", (total_price-discount)*118/100);

	fclose(out); // we close the receipt.txt file
}

void part1()// PART 1 program
{
	print_menu();
	fill_receipt();
	print_receipt();
}

void part2() // PART 2 program
{
	int user_choice, pc_choice;
	char isGame;

	srand(time(0));
	isGame = 'Y';
	while (isGame == 'Y')
	{
		printf("\nPlease make a choice!\n");
		printf("1: Stone, 2: Paper, 3: Scissors\n");
		scanf("%d", &user_choice);

		pc_choice = (rand() % 3) + 1; // we create random number 0,1,2 then we add 1 to make it 1,2,3

		switch (user_choice) // I used switch case statements in another switch case statement to check every situation user and pc could pick
		{
		case 1:
			printf("You choose Stone.");
			switch (pc_choice)
			{
			case 1:
				printf(" I chose Stone.");
				printf(" Draw!\n");
				break;
			case 2:
				printf(" I chose Paper.");
				printf(" I won!\n");
				break;
			case 3:
				printf(" I chose Scissors.");
				printf(" You won!\n");
				break;
			}
			break;
		case 2:
			printf("You choose Paper.");
			switch (pc_choice)
			{
			case 1:
				printf(" I chose Stone.");
				printf(" You won!\n");
				break;
			case 2:
				printf(" I chose Paper.");
				printf(" Draw!\n");
				break;
			case 3:
				printf(" I chose Scissors.");
				printf(" I won!\n");
				break;
			}
			break;
		case 3:
			printf("You choose Scissors.");
			switch (pc_choice)
			{
			case 1:
				printf(" I chose Stone.");
				printf(" I won!\n");
				break;
			case 2:
				printf(" I chose Paper.");
				printf(" You won!\n");
				break;
			case 3:
				printf(" I chose Scissors.");
				printf(" Draw!\n");
				break;
			}
			break;
		}
		
		printf("\nDo you want to play again? (Y/N): "); // we ask for another game
		scanf(" %c", &isGame);
	}

	return;
}

int main(void)
{
	printf("\n### PART 1 ###\n");
	part1();
	printf("\n### PART 2 ###\n");
	part2();

	return 0;
}