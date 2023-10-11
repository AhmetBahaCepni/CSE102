#include <stdio.h>
#include <stdlib.h>
#include <time.h>   // i used this for srand() and sleep() functions
#include <unistd.h>

#include "utils.h"

#define BOARD_LOG "board_log.txt"
#define SCORE_LOG "best_score.txt"


// this function checks if the map created randomly is solvable or not
int check_if_puzzle_solvable(t_puzzle my_puzzle)
{
    int inversion_count = 0;
    int *arr;
    int temp;

    arr = (int *) malloc(sizeof(int) * 9);
    for (int i = 0; i < 9; i++)
    {
        arr[i] = my_puzzle.map[i/3][i%3];
    }
    for (int i = 0; i < 9; i++)
    {
        if (arr[i] == -1)
            continue;
        for (int j = i+1; j < 9; j++)
        {
            if (arr[j] == -1)
                continue;
            if (arr[i] > arr[j])
                inversion_count++;
        }
    }
    free(arr);
    if (inversion_count % 2 == 0)
        return 1;
    return 0;
}

// this function saves the current board to the board_log.txt
void    save_current_board(t_puzzle my_puzzle)
{
    FILE *board_log;

    if (my_puzzle.move_c == 0)
        board_log = fopen(BOARD_LOG, "w");
    else
        board_log = fopen(BOARD_LOG, "a");

    for (int m = 0; m < 3; m++)
    {
        for (int n = 0; n < 3; n++)
        {
            if (my_puzzle.map[m][n] == -1)
                fprintf(board_log, "_ ");
            else
                fprintf(board_log, "%d ", my_puzzle.map[m][n]);
        }
        fprintf(board_log, "\n");
    }
    fprintf(board_log, "\n");

    fclose(board_log);
}

// this function saves the score to the best_score.txt
void    save_score(t_puzzle my_puzzle)
{
    int best_score;
    FILE *score_log;

    score_log = fopen(SCORE_LOG, "r");
    fscanf(score_log, "%d", &best_score);
    if (my_puzzle.score > best_score)
    {
        fclose(score_log);
        score_log = fopen(SCORE_LOG, "w");
        fprintf(score_log, "%d",my_puzzle.score);
        printf("You have the best score\n");
        printf("Your score saved to the scoreboard\n");
        fclose(score_log);
        return ;
    }
}

// this function converts alphabetic characters to their upper version
char    to_upper(char c)
{
    if(c <= 'z' && c >= 'a')
        return c-32;
    return c;
}

// this function checks if the game is over or not and changes the isOver flag in struct
void    isGameOver(t_puzzle *my_puzzle)
{

    for (int i = 0; i < 8; i++)
    {
        if ((my_puzzle->map[i/3][i%3] != i+1))
            return ;
    }
    my_puzzle->isOver = 1;
}

// this function prints the map to the terminal
void print_map(t_puzzle my_puzzle)
{
    printf("\n");
    for (int m = 0; m < 3; m++)
    {
        for (int n = 0; n < 3; n++)
        {
            if (my_puzzle.map[m][n] == -1)
                printf("_ ");
            else
                printf("%d ", my_puzzle.map[m][n]);
        }
        printf("\n");
    }
    printf("\n");
}

// this function creates a random map and saves it to the struct
void    randomize_map(t_puzzle *my_puzzle)
{
    srand(time(NULL)); // this is for randomize the rand() function

    int start_p, coord;

    int saved[9] = {0,0,0,0,0,0,0,0,0};
    start_p = (rand()%9);
    saved[start_p] = -1; // -1 is the empty space
    for (int i = 1; i < 9; i++)
    {
       coord = rand()%9;
       while (saved[coord] != 0)
       {
           coord = rand()%9;
       }
       saved[coord] = i;
    }

    for (int j = 0; j < 9; j++) // this is for saving the map to the struct
    {
        my_puzzle->map[j/3][j%3] = saved[j];
    }
    save_current_board(*my_puzzle);
}

// this function checks if the move is legal or not
int    isMovable(t_puzzle my_puzzle, int *pos, int move_int, char move_char)
{
    int ret_flag = 1;

    // these checks are for the move is not a number on the map
    if(move_int < 1 || move_int > 8)
        ret_flag = 0;

    // these checks are for the move is not a direction we want
    if (move_char != 'U' && move_char != 'D' && move_char != 'R' && move_char != 'L')
        ret_flag = 0;

    // these checks are for the out of borders
    if ((pos[0] == 0 && move_char == 'U')
        || (pos[0] == 2 && move_char == 'D')
        || (pos[1] == 2 && move_char == 'R')
        || (pos[1] == 0 && move_char == 'L'))
        ret_flag = 0;

    // these checks are for the empty space is in the direction of move
    if ((move_char == 'U' && my_puzzle.map[pos[0]-1][pos[1]] != -1) ||
        (move_char == 'D' && my_puzzle.map[pos[0]+1][pos[1]] != -1) ||
        (move_char == 'R' && my_puzzle.map[pos[0]][pos[1]+1] != -1) ||
        (move_char == 'L' && my_puzzle.map[pos[0]][pos[1]-1] != -1))
        ret_flag = 0;

    if (ret_flag == 0)
    {
        printf("%d-%c is an illegal move!! make a legal one\n", move_int, move_char);
        return 0;
    }
    return 1;
}

// this function finds the position of the number we want to move as user
int *find_position(t_puzzle my_puzzle, int move_int)
{
    int *pos;
    pos = (int *) malloc(sizeof(int) * 2);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j< 3; j++)
        {
            if (my_puzzle.map[i][j] == move_int)
            {
                pos[0] = i;
                pos[1] = j;
                return pos;
            }
        }
    }
}

// this function makes the move we want to make according to the number and direction
void    move(t_puzzle *my_puzzle, int move_int, char move_char)
{
    int *pos;

    pos = find_position(*my_puzzle, move_int);
    while (!isMovable(*my_puzzle, pos, move_int, move_char)) // this is for the illegal moves
    {
        free(pos); // we free the allocated space on memory
        printf("Enter your %d. move(number-direction, ex: 2-U): ", my_puzzle->move_c+1);
        scanf("%d-%c", &move_int, &move_char);

        move_char = to_upper(move_char);
        pos = find_position(*my_puzzle, move_int);
    }
    switch (move_char) // I used switch case to make the different moves
    {
        case 'U':
            my_puzzle->map[pos[0]][pos[1]] = -1;
            my_puzzle->map[pos[0]-1][pos[1]] = move_int;
            break;
        case 'D':
            my_puzzle->map[pos[0]][pos[1]] = -1;
            my_puzzle->map[pos[0]+1][pos[1]] = move_int;
            break;
        case 'R':
            my_puzzle->map[pos[0]][pos[1]] = -1;
            my_puzzle->map[pos[0]][pos[1]+1] = move_int;
            break;
        case 'L':
            my_puzzle->map[pos[0]][pos[1]] = -1;
            my_puzzle->map[pos[0]][pos[1]-1] = move_int;
            break;
    }
    my_puzzle->move_c++;
    if (my_puzzle->score != 0) // if score is 0, we don't want to decrease it
        my_puzzle->score -= 10;
    save_current_board(*my_puzzle); // this is for saving the current board to the board_log.txt
    free(pos); // we free the allocated space on memory
}

// this function is the function that is number 1 in the menu so user can play the game
void    gameplay()
{
    t_puzzle my_puzzle; // I initialized the struct
    int move_int;
    char move_char;

    // I initialized the struct variables
    my_puzzle.score = 1000;
    my_puzzle.move_c = 0;
    my_puzzle.isOver = 0;

    randomize_map(&my_puzzle);
    while (!check_if_puzzle_solvable(my_puzzle)) // we randomize the map until it is solvable
    {
        randomize_map(&my_puzzle);
        sleep(1);
    }

    print_map(my_puzzle);
    while (!my_puzzle.isOver) // we will quit the loop when the game is over
    {
        printf("Enter your %d. move(number-direction, ex: 2-U): ", my_puzzle.move_c+1);
        scanf("%d-%c", &move_int, &move_char);

        move(&my_puzzle, move_int, to_upper(move_char)); // we always send the upper version
        print_map(my_puzzle); 
        isGameOver(&my_puzzle);// we check if the game is over or not
    }
    printf("Congratulations !! You finished the game.\n");
    printf("--> Total number of moves: %d\n", my_puzzle.move_c);
    printf("--> Total score is : %d\n", my_puzzle.score);
    save_score(my_puzzle);
    save_current_board(my_puzzle);
}

int     isPcMovable(t_puzzle my_puzzle, int *pos, int move_rnd, int old_move)
{
    int ret_flag = 1;

    
    if ((pos[0] == 0 && move_rnd == 1)
        || (pos[0] == 2 && move_rnd == 0)
        || (pos[1] == 2 && move_rnd == 3)
        || (pos[1] == 0 && move_rnd == 2))
        ret_flag = 0;

    if(old_move == 0 && move_rnd == 1 || old_move == 2 && move_rnd == 3
        || old_move == 1 && move_rnd == 0 || old_move == 3 && move_rnd == 2)
        ret_flag = 0;

    if (ret_flag == 0)
        return 0;
    return 1;
}

void    auto_finish(t_puzzle *my_puzzle, int temp_rnd, int reccur_times)
{
    if (my_puzzle->isOver == 1 || reccur_times == 10000)
        return ;
    
    int move_rnd;
    int *pos;

    move_rnd = rand()%4;
    pos = find_position(*my_puzzle, -1);
    while (!isPcMovable(*my_puzzle, pos, move_rnd, temp_rnd))
        move_rnd = rand()%4;
    switch(move_rnd)
    {
        case 0:
            printf("computer move: %d-U\n", my_puzzle->map[pos[0]+1][pos[1]]);
            my_puzzle->map[pos[0]][pos[1]] = my_puzzle->map[pos[0]+1][pos[1]];
            my_puzzle->map[pos[0]+1][pos[1]] = -1;
            break;
        case 1:
            printf("computer move: %d-D\n", my_puzzle->map[pos[0]-1][pos[1]]);
            my_puzzle->map[pos[0]][pos[1]] = my_puzzle->map[pos[0]-1][pos[1]];
            my_puzzle->map[pos[0]-1][pos[1]] = -1;
            break;
        case 2:
            printf("computer move: %d-R\n", my_puzzle->map[pos[0]][pos[1]-1]);
            my_puzzle->map[pos[0]][pos[1]] = my_puzzle->map[pos[0]][pos[1]-1];
            my_puzzle->map[pos[0]][pos[1]-1] = -1;
            break;
        case 3:
            printf("computer move: %d-L\n", my_puzzle->map[pos[0]][pos[1]+1]);
            my_puzzle->map[pos[0]][pos[1]] = my_puzzle->map[pos[0]][pos[1]+1];
            my_puzzle->map[pos[0]][pos[1]+1] = -1;
            break;
    }
    my_puzzle->move_c++;
    if (my_puzzle->score != 0)
        my_puzzle->score -= 10;

    print_map(*my_puzzle);
    
    save_current_board(*my_puzzle);
    free(pos);
    isGameOver(my_puzzle);
    auto_finish(my_puzzle, move_rnd, reccur_times+1);
}

// this function is the function that is number 2 in the menu so user can finish the game with pc
void    solve_with_pc()
{
    t_puzzle my_puzzle; // I initialized the struct
    int move_int;
    char move_char;

    // I initialized the struct variables
    my_puzzle.score = 1000;
    my_puzzle.move_c = 0;
    my_puzzle.isOver = 0;

    randomize_map(&my_puzzle);
    while (!check_if_puzzle_solvable(my_puzzle))
    {
        randomize_map(&my_puzzle);
        sleep(1);
    }

    save_current_board(my_puzzle);
    print_map(my_puzzle);

    while (!my_puzzle.isOver)// i will quit recursive for each 10000 moves and here i will enter again if puzzle is not finished
    {
        auto_finish(&my_puzzle, -1, 0);
    }

    printf("Computer finished the game.\n");
    printf("--> Total number of computer moves: %d\n", my_puzzle.move_c);
}

// this function is the function that is number 3 in the menu so user can see the best score
void print_best_score()
{
    FILE *score_log;
    int best_score;

    score_log = fopen(SCORE_LOG, "r");
    fscanf(score_log, "%d", &best_score);
    printf("Best score is %d\n", best_score);
    fclose(score_log);
}

int main(void)
{
    int chc = 0;
    while (chc < 4) // this is the menu loop
    {
        printf("\nWelcome to the 8-Puzzle Game!\n");
        printf("Please select an option:\n");
        printf("1. Play the game as USER\n");
        printf("2. Finish the game with PC\n");
        printf("3. Show the best score\n");
        printf("4. Exit\n");
        printf("---> ");
        scanf("%d", &chc);
        switch (chc) // I used switch case to make the different choices
        {
            case 1:
                gameplay();
                break;
            case 2:
                solve_with_pc();
                break;
            case 3:
                print_best_score();
                break;
        }
    }
    printf("Program Terminated...\n");
    return 0;
}