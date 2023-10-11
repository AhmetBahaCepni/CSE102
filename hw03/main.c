#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'

void the_game_menu();

int print_menu() // this is the fucntion that i wrote for printing the menu and get the input taken from
{
	int menu_selection; // we will hold the selected operation with this integer

	printf("Welcome to the 2D puzzle game!\n");
	printf("1. New Game\n");
	printf("2. Help\n");
	printf("3. Exit\n");
	scanf("%d", &menu_selection);

	if (menu_selection == 2)
	{
		printf("###########-HELP-###########\n\n");
		printf("This is a 2D puzzle game that character try to reach the door, character represented as C and the door is D\n\n");
		printf("The character is able to move one space in any of the four cardinal directions: up, down, left, and right. Diagonal moves are not allowed. The user will input their desired move using the following keys: 'a' for left, 'd' for right, 'w' for up, and 's' for down.\n\n");

		menu_selection = print_menu(); // after HELP called, menu should be printed again. so i used recursive
	}
	if (menu_selection > 3 || menu_selection < 1)
	{
		printf("Please input 1, 2 or 3 according to given menu:\n");
		menu_selection = print_menu(); // if input is not in the menu, menu should be called again so i used recursive
	}

	return menu_selection;
}

void draw_room(int room_size, int ch_x, int ch_y, int door_x, int door_y) // Part 1 that wanted in pdf
{
	for (int i = 0; i < (room_size * 2) + 1; i++) // (room_size * 2) + 1 is exact amout of '-' to complete map
	{
		printf("-");
	}
	printf("\n");

	for (int i = 0; i < room_size; i++) // we use loop in loop to create a 2d map.  i represents y axis
	{
		for (int j = 0; j < room_size; j++) // j represents x axis
		{
			printf("|");// for each j we print '|' but after that we check for coordinates to print ' ' or 'C' or 'D' 
			if (i == ch_y && j == ch_x)
				printf("C");
			else if (i == door_y && j == door_x)
				printf("D");
			else
				printf(" ");
		}
		printf("|\n");
	}

	for (int i = 0; i < (room_size * 2) + 1; i++) // (room_size * 2) + 1 is exact amout of '-' to complete map
	{
		printf("-");
	}
	printf("\n");
}

int isGameOver(int ch_x, int ch_y, int door_x, int door_y) // Part 3 that wanted in pdf
{
	if (ch_x == door_x && ch_y == door_y) // if both x and y coordinates same, character and door are in the same place
	{
		return 1;
	}
	return 0;
}

void gameplay(int room_size, int ch_x, int ch_y, int door_x, int door_y) // Part 2 that wanted in pdf
{
	int step;	// to keep the move count
	char input; // to hold the character inputs in scanf

	step = 0;
	while (!isGameOver(ch_x, ch_y, door_x, door_y)) // if isGameOver is returns 1 it means game is over so this while keeps us in game
	{
		draw_room(room_size, ch_x, ch_y, door_x, door_y); // we print the map

		printf("Enter your move: ");
		scanf(" %c", &input);
		// the lines 85 to 89 is used for cleaning the input stream, so this way when user inputs "wadws" it will only read 'w' and pass others
		char c = getchar();
		while (c != '\n' && c != EOF)
		{
			c = getchar();
		}
		printf("\n");

		switch (input) // i used swtich case statement to what key user inputted according to defined values
		{
		case UP: // UP is defined 'w'
			if (ch_y != 0) // if ch_y == 0 character cant go UP because it would be out of border
			{
				ch_y--; // we decrease ch_y to make character go up
				step++; // in each key we increase the step to count moves
			}
			else
			{
				printf("You cant move through a wall\n"); // warning message if user try to move through wall
			}
			break;
		case RIGHT: // RIGHT defined 'd'
			if (ch_x != room_size - 1) // if ch_x == room_size-1 character cant go ROGHT because it would be out of border
			{
				ch_x++; // we increase ch_x to make character go right
				step++;
			}
			else
			{
				printf("You cant move through a wall\n"); // warning message if user try to move through wall
			}
			break; 
		case DOWN: // DOWN defined 's'
			if (ch_y != room_size - 1)// if ch_y == room_size-1 character cant go DOWN because it would be out of border
			{
				ch_y++; // we increase ch_y to make character go down
				step++;
			}
			else
			{
				printf("You cant move through a wall\n"); // warning message if user try to move through wall
			}
			break;
		case LEFT: // LEFT defined 'a'
			if (ch_x != 0) // if ch_x == 0 character cant go LEFT because it would be out of border
			{
				ch_x--; // we decrease ch_x to make character go left
				step++;
			}
			else
			{
				printf("You cant move through a wall\n"); // warning message if user try to move through wall
			}
			break;
		default:
			break;
		}
	}
	printf("Congratulations! you have completed the puzzle with %d moves\n\n", step); // we print move count with a greeting message
	the_game_menu();
}

void the_game_menu() // Part 4 that is wanted in pdf
{
	int room_size;
	int menu_selection;
	int ch_x, ch_y, door_x, door_y;

	srand(time(NULL));			   // srand is for completely randomizing the rand() function. If we dont do this, each game same coordinates would be played
	menu_selection = print_menu(); // we print the menu and take the return value
	if (menu_selection == 3)	   // if menu_selection is 3 taht means user picked EXIT
	{
		printf("\nThanks for playing, I hope you had fun!\n"); // goodbye message after 3 selected in menu
		return; // to return to main and terminate the program
	}
	printf("Please enter the room size in range [5-10]: ");
	scanf("%d", &room_size);
	if (room_size < 5 || room_size > 10)
	{
		printf("You cant specify a size smaller than 5 or greater than 10\n");
		return; // to return to main and terminate the program
	}
	// in below we find random values for our coordinates. % is used for find a number in range [0,room_size), integer%5 is always in range [0,5)
	ch_x = rand() % room_size;
	ch_y = rand() % room_size;
	door_x = rand() % room_size;
	door_y = rand() % room_size;
	while (ch_x == door_x && ch_y == door_y) // if coordinates is same there wouldnt be a puzzle so i rerandomize until they are not same
	{
		door_x = rand() % room_size;
		door_y = rand() % room_size;
	}

	gameplay(room_size, ch_x, ch_y, door_x, door_y); // we call part 2 where game is played
}

int main(void)
{
	the_game_menu(); // we call the game, this function could be on main too but pdf wants us to seperate these parts as functions
	return 0;
}