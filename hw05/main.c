#include <stdio.h>
#include <math.h>

typedef enum {RED, GREEN, BLUE, YELLOW, ORANGE} color_t;

void part1()
{
	FILE *inp;
	char file_name[50];
	char alphabet[26] = {0};
	int fscanf_return;
	char my_char;

	printf("Enter the file name: "); 
	scanf("%s", file_name);			// we take the file name from user

	inp = fopen(file_name, "r"); // try to open file readonly because we will not edit
	if (inp == NULL)  		// if fopen returns NULL that means file doessnt exist so we exit
	{
		printf("File doesnt exist\n");
		return;
	}
	
	fscanf_return = fscanf(inp, "%c", &my_char); // we hold the value returned by fscanf because i will check if its EOF or not
	while (fscanf_return != EOF)
	{
		if (my_char >= 'a' && my_char <= 'z')  // it doesnt matter if character is lowercase or uppercase
		{
			alphabet[my_char - 'a']++;  // my_char - 'a' is just exactly the index number of my_char in alphabet.Example :  'd' - 'a' = 3
		}
		else if (my_char >= 'A' && my_char <= 'Z')  
		{
			alphabet[my_char - 'A']++;  
		}
	
		fscanf_return = fscanf(inp, "%c", &my_char); // we keep scanning in loop until EOF
	}

	printf("\nLetter Frequency:\n");
	for (int i = 0; i < 26; i++)
	{
		printf("%c: %d\n", 'A'+i, alphabet[i]); // we can initilaze char vaaribales by integers so 'A' + 2 = 'C'
	}

	fclose(inp); // we close the file;
}

color_t closestColor(color_t color1, color_t color2) // this is the function that is passed to colorMixer to find mixed color
{
    double color1RGB[3], color2RGB[3], mixedColorRGB[3]; // these 3 array will hold RGB values of 3 color
	double colorsRGB[5][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {0.5, 0.5, 0}, {0.5, 0.4, 0.2}}; // this array holds that 5 colors RGB values
	double min_distance, distance; // we will use these in euclidean calculation
	color_t closest_color;

    switch(color1) { // we find and assign the RGB values of color1 to its array
        case RED:
            color1RGB[0] = colorsRGB[RED][0];
            color1RGB[1] = colorsRGB[RED][1];
            color1RGB[2] = colorsRGB[RED][2];
            break;
        case GREEN:
            color1RGB[0] = colorsRGB[GREEN][0];
            color1RGB[1] = colorsRGB[GREEN][1];
            color1RGB[2] = colorsRGB[GREEN][2];
            break;
        case BLUE:
            color1RGB[0] = colorsRGB[BLUE][0];
            color1RGB[1] = colorsRGB[BLUE][1];
            color1RGB[2] = colorsRGB[BLUE][2];
            break;
        case YELLOW:
            color1RGB[0] = colorsRGB[YELLOW][0];
            color1RGB[1] = colorsRGB[YELLOW][1];
            color1RGB[2] = colorsRGB[YELLOW][2];
            break;
        case ORANGE:
            color1RGB[0] = colorsRGB[ORANGE][0];
            color1RGB[1] = colorsRGB[ORANGE][1];
            color1RGB[2] = colorsRGB[ORANGE][2];
            break;
    }
    switch(color2) { // we find and assign the RGB values of color2 to its array  
        case RED:
            color2RGB[0] = colorsRGB[RED][0];
            color2RGB[1] = colorsRGB[RED][1];
            color2RGB[2] = colorsRGB[RED][2];
            break;
        case GREEN:
            color2RGB[0] = colorsRGB[GREEN][0];
            color2RGB[1] = colorsRGB[GREEN][1];
            color2RGB[2] = colorsRGB[GREEN][2];
            break;
        case BLUE:
            color2RGB[0] = colorsRGB[BLUE][0];
            color2RGB[1] = colorsRGB[BLUE][1];
            color2RGB[2] = colorsRGB[BLUE][2];
            break;
        case YELLOW:
            color2RGB[0] = colorsRGB[YELLOW][0];
            color2RGB[1] = colorsRGB[YELLOW][1];
            color2RGB[2] = colorsRGB[YELLOW][2];
            break;
        case ORANGE:
            color2RGB[0] = colorsRGB[ORANGE][0];
            color2RGB[1] = colorsRGB[ORANGE][1];
            color2RGB[2] = colorsRGB[ORANGE][2];
            break;
    }

	// we find mixed RGB values of mixedColor by taking average
	mixedColorRGB[0] = (color1RGB[0] + color2RGB[0]) / 2;
	mixedColorRGB[1] = (color1RGB[1] + color2RGB[1]) / 2;
	mixedColorRGB[2] = (color1RGB[2] + color2RGB[2]) / 2;

	min_distance = 99999; // we assign this to a big integer
	for (int i = 0; i < 5; i++)
	{
		distance = sqrt(pow((mixedColorRGB[0] - colorsRGB[i][0]), 2) + pow((mixedColorRGB[1] - colorsRGB[i][1]), 2) + pow((mixedColorRGB[2] - colorsRGB[i][2]), 2));
		if (distance < min_distance) // we find the minimum by this statement
		{
			closest_color = i;
			min_distance = distance;
		}	
	}

	return closest_color;
}

void colorMixer(color_t color1, color_t color2, color_t (*f)(color_t, color_t)) // this is the function that is written in pdf with arguments
{
	color_t closest_color;

	closest_color = f(color1, color2); // calls the f function to calculate mixed color

	switch (closest_color) // prints color to terminal
	{
	case RED:
		printf("Mixed Color: RED [1.0, 0.0 , 0.0]");
		break;
	case GREEN:
		printf("Mixed Color: GREEN [0.0, 1.0 , 0.0]");
		break;
	case BLUE:
		printf("Mixed Color: BLUE [0.0, 0.0 , 1.0]");
		break;
	case YELLOW:
		printf("Mixed Color: YELLOW[0.5, 0.5 , 0.0]");
		break;
	case ORANGE:
		printf("Mixed Color: ORANGE [0.5, 0.4 , 0.2]");
		break;
	}
	printf("\n");
}

void part2()
{
	char cl1, cl2; // we will read by character values
	char color_names[5] = {'r', 'g', 'b', 'y', 'o'}; // this array holds colors that we will use
	color_t color1, color2; // this is the enumarated variables color_t

	printf("Enter Color 1 (r,g,b,y,o): ");
	scanf(" %c", &cl1);
	printf("Enter Color 2 (r,g,b,y,o): ");
	scanf(" %c", &cl2);
	
	for (int  i = 0; i < 5; i++) // we assign their colors to color_t enumarator variables
	{
		if(cl1 == color_names[i])
		{
			color1 = RED + i; // we can manipualte enumarators just like integers RED+1= GREEN 
		}
		if(cl2 == color_names[i])
		{
			color2 = RED + i;
		}
	}
	
	colorMixer(color1, color2, closestColor); // we call the color mixer to find closest color using assigned function and print the color

}

int checkGame(char map[3][3], char *winner)  // this is the function that i wrote to check if tic-tac-toe game is over or not
{
	for (int i = 0; i < 3; i++)  // check for vertical finishes
	{
		if(map[i][0] != '_' && (map[i][0] == map[i][1]) && (map[i][0] == map[i][2]))
		{
			*winner = map[i][0];
			return 1;
		}
	}

	for (int i = 0; i < 3; i++) // checks for hortizonal finishes
	{
		if(map[0][i] != '_' && (map[0][i] == map[1][i]) && (map[0][i] == map[2][i]))
		{
			*winner = map[0][i];
			return 1;
		}
	}
	
	if (map[0][0] != '_' && (map[0][0] == map[1][1] && map[0][0] == map[2][2])) // checks for left top to right bottom diagonal
	{
		*winner = map[0][0];
		return 1;
	}
	
	if (map[0][2] != '_' && (map[0][2] == map[1][1] && map[0][2] == map[2][0])) // checks for right top to left botton diagonal
	{
		*winner = map[0][2];
		return 1;
	}

	return 0;
}

void part3()
{
	char map[3][3] = {{'_','_','_'},{'_','_','_'},{'_','_','_'}}; // this is our map array
	int row, clm, isOver;
	char winner; // we will send this adress to check game and it will hold the winner

	isOver = 0;
	while (!isOver)
	{
		printf("Player 1(X), enter your move(row, column): ");
		scanf("%d %d", &row, &clm);

		map[row][clm] = 'X';
		printf("%c %c %c\n%c %c %c\n%c %c %c\n\n", map[0][0], map[0][1], map[0][2], map[1][0], map[1][1], map[1][2], map[2][0], map[2][1], map[2][2]);

		isOver = checkGame(map, &winner); // we check for game after each move
		if(isOver)
			break;

		printf("Player 2(O), enter your move(row, column): ");
		scanf("%d %d", &row, &clm); 

		map[row][clm] = 'O';
		printf("%c %c %c\n%c %c %c\n%c %c %c\n\n", map[0][0], map[0][1], map[0][2], map[1][0], map[1][1], map[1][2], map[2][0], map[2][1], map[2][2]);
	
		isOver = checkGame(map, &winner);  // we check for game after each move
	}
	
	if (winner == 'X')
	{
		printf("Player 1(X) wins!\n");
	}
	else if (winner == 'O')
	{
		printf("Player 2(O) wins!\n");
	}
}

int main(void)
{
	printf("\n### PART 1 ###\n");
	part1();
	printf("\n### PART 2 ###\n");
	part2();
	printf("\n### PART 3 ###\n");
	part3();

	return 0;
}