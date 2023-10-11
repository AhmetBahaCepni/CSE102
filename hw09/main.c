#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "utils.h"

// We already set the head to nect position in move funciton, in here i will update the body according to the direction of the head
// I need to update bait and obstacles in here if there is any change
void update(t_snake *snake, t_block ***board)
{
    t_point head;
    int rand_row, rand_col;
    int is_bait, is_safe;
    srand(time(NULL));

    head.row = snake->body[0].row;
    head.col = snake->body[0].col;

    is_bait = 0;
    if (board[head.row][head.col]->type == 'o')
        snake->obs_count--;
    if (board[head.row][head.col]->type == 'b')
    {
        snake->length++;
        snake->score++;

        // we should allocate a new memory for the snake body array
        snake->body = (t_point *)realloc(snake->body, sizeof(t_point) * snake->length);
        is_bait = 1;
    }
    if (is_bait == 0) // if snake didnt eat a bait there will not be any adding to the body so we empty that block
    {
        board[snake->body[snake->length - 1].row][snake->body[snake->length - 1].col]->type = 'e';
        board[snake->body[snake->length - 1].row][snake->body[snake->length - 1].col]->value = 0;
    }
    else
    {
        is_safe = 0;
        rand_row = rand() % 10;
        rand_col = rand() % 10;
        while(is_safe == 0 || board[rand_row][rand_col]->type != 'e')
        {
            for(int k = 0; k < snake->length; k++) // I check if the random position on the snake body or not
            {
                if(snake->body[k].row == rand_row && snake->body[k].col == rand_col)
                {
                    rand_row = rand() % 10;
                    rand_col = rand() % 10;
                    break;
                }
                else if(k == snake->length - 1)
                    is_safe = 1;
            }
            if(is_safe == 0 || board[rand_row][rand_col]->type != 'e') // random position block should be empty
            {
                rand_row = rand() % 10;
                rand_col = rand() % 10;
                is_safe = 0;
            }
        }
        board[rand_row][rand_col]->type = 'b';
        board[rand_row][rand_col]->value = 0;
    }
    if (snake->move_count != 0 && snake->move_count % 5 == 0) // i need to update obstacles every 5 moves
    {
        if (snake->obs_count != 3) // there could be maximum 3 obstacles
        {
            is_safe = 0;
            rand_row = rand() % 10;
            rand_col = rand() % 10;

            while(is_safe == 0 || board[rand_row][rand_col]->type != 'e') // same check as bait valid for this one too
            {
                for(int k = 0; k < snake->length; k++)
                {
                    if(snake->body[k].row == rand_row && snake->body[k].col == rand_col)
                    {
                        rand_row = rand() % 10;
                        rand_col = rand() % 10;
                        break;
                    }
                    else if(k == snake->length - 1)
                        is_safe = 1;
                }
                if(is_safe == 0 || board[rand_row][rand_col]->type != 'e')
                {
                    rand_row = rand() % 10;
                    rand_col = rand() % 10;
                    is_safe = 0;
                }
            }
            board[rand_row][rand_col]->type = 'o';
            board[rand_row][rand_col]->value = rand() % 9 + 1;
            snake->obs_count++;
        }
        else // in here we will increase the height of one of the obstacles and if all of them are at max height we will destroy one of them
        {
            rand_row = rand() % 10;
            rand_col = rand() % 10;
            while(board[rand_row][rand_col]->type != 'o')
            {
                rand_row = rand() % 10;
                rand_col = rand() % 10;
            }
            if(board[rand_row][rand_col]->value < 9) // we could update the height of the obstacle if it is not at max height
            {
                int new_height = rand() % 9 + 1;
                while(new_height <= board[rand_row][rand_col]->value) // we can add new nested blocks to the obstacle or we can destroy it
                    new_height = rand() % 9 + 1;
                board[rand_row][rand_col]->value = new_height;
            }
            else // if random choosen obstacle is at max height we will destroy it
            {
                board[rand_row][rand_col]->type = 'e';
                board[rand_row][rand_col]->value = 0;
                snake->obs_count--;
            }
        }
    }
    
    // we shift the all parts of the snake except the head and the second block
    for(int i = snake->length - 1; i > 1; i--)
    {
        snake->body[i].row = snake->body[i - 1].row;
        snake->body[i].col = snake->body[i - 1].col;
    }

    // in move function we updated the head so we need to update the "second block" in the body
    //      according to the reverse direction fo updated position of the head
    switch(snake->direction)
    {
        case 0:
            snake->body[1].row = head.row + 1;
            snake->body[1].col = head.col;
            break;
        case 1:
            snake->body[1].row = head.row;
            snake->body[1].col = head.col + 1;
            break;
        case 2:
            snake->body[1].row = head.row - 1;
            snake->body[1].col = head.col;
            break;
        case 3:
            snake->body[1].row = head.row;
            snake->body[1].col = head.col - 1;
            break;
    }
}

int check_status(t_snake snake, t_block ***board)
{
    int is_over = 0;

    t_point head;

    head.row = snake.body[0].row;
    head.col = snake.body[0].col;

    if(head.row < 0 || head.row > 9 || head.col < 0 || head.col > 9) // check for out of borders
        is_over = 1;
    else if(board[head.row][head.col]->type == 'o' && (board[head.row][head.col]->value > snake.length)) // check for obstacle and its height
        is_over = 1;
    else // in here we will check if the snake hit itself
    {
        for(int i = 1; i < snake.length; i++)
        {
            if(snake.body[i].row == head.row && snake.body[i].col == head.col)
            {
                is_over = 1;
                break;
            }
        }
    }
    return is_over;
}

int move(t_snake *snake)
{
    t_point next;
    t_point head;
    char move;

    printf("Enter your move(w,a,s,d) --> ");
    scanf(" %c", &move);

    // in here we check if the move goes through its own body. after that we assign the direction
    switch(move)
    {
        case 'w':
            if(snake->direction == 2 && snake->length > 1)
                return 1;
            snake->direction = 0;
            break;
        case 'a':
            if(snake->direction == 3 && snake->length > 1)
                return 1;
            snake->direction = 1;
            break;
        case 's':
            if(snake->direction == 0 && snake->length > 1)
                return 1;
            snake->direction = 2;
            break;
        case 'd':
            if(snake->direction == 1 && snake->length > 1)
                return 1;
            snake->direction = 3;
            break;
    }

    // in pdf we are wanted to set the head to the next position in the move function it here: 
    head.row = snake->body[0].row;
    head.col = snake->body[0].col;
    switch(snake->direction)
    {
        // 0,1,2,3 represents up, left, down, right
        case 0: 
            next.row = head.row - 1;
            next.col = head.col;
            break;
        case 1:
            next.row = head.row;
            next.col = head.col - 1;
            break;
        case 2:
            next.row = head.row + 1;
            next.col = head.col;
            break;
        case 3:
            next.row = head.row;
            next.col = head.col + 1;
            break;
    }

    // we set the head to the next position
    snake->body[0].row = next.row; 
    snake->body[0].col = next.col;
    return 0;
}

void play(t_block ***board)
{
    t_snake snake;

    snake.body = (t_point *)malloc(sizeof(t_point)); // we allocate 1 point sized memory for the body
    snake.body[0].row = 0;      // we set the head to (0,0)
    snake.body[0].col = 0;      // we set the head to (0,0)
    snake.length = 1;           // we set the length to 1 
    snake.direction = 1;        // we set the direction to 
    snake.obs_count = 1;        // we set the obstacle count to 1
    snake.score = 0;            // we set the score to 0
    snake.move_count = 0;       // we set the move count to 0
    snake.is_over = 0;          // we set the is_over flag to 0


    while(snake.is_over == 0)
    {
        draw_board(snake, board);
        while(move(&snake)) // if move is illegal we want a new move
        {
            draw_board(snake, board);
            printf("Invalid move, Please make a legal one!\n");
        }
        snake.is_over = check_status(snake, board); // we check if the game is over
        if (snake.is_over == 1)
            break;
        update(&snake, board); // we update the board and snake positions
        snake.move_count++;
    }

    printf("   Game Over!   \n");
    printf("--> You've made %d moves and Your score is: %d <--\n", snake.move_count , snake.score);
    free(snake.body); // we free the body array
}

// this function is draws the board to the terminal
void draw_board(t_snake snake,t_block ***board)
{
    int is_snake;

    printf("  ");
    for(int i = 0; i < 10; i++)
        printf("--");
    printf("\n ");
    for(int i = 0; i < 10; i++)
    {
        printf("|");
        for(int j = 0; j < 10; j++)
        {
            is_snake = 0; // this is a flag to check if snake is in the block
            for(int k = 0; k < snake.length; k++) // we check all parts of the snake
            {
                if(snake.body[k].row == i && snake.body[k].col == j)
                {
                    if(k == 0)
                        printf("O "); // if it is the head we print O
                    else
                        printf("X "); // if it is not the head we print X
                    is_snake = 1;
                    break;
                }
            }
            if(is_snake == 0) // if there are snake on that block we dont print anything more
            {
                switch(board[i][j]->type)
                {
                    case 'e':
                        printf("  "); // i used 2 char for every block so board looks like a square
                        break;
                    case 'b':
                        printf(". ");
                        break;
                    case 'o':
                        printf("%d ", board[i][j]->value); // if there are a obstacle we print its height
                        break;
                }
            } 
        }
        printf("|\n ");
    }
    printf(" ");
    for(int i = 0; i < 10; i++)
        printf("--");
    printf("\n");
}

//this is the function that initializes the board with random obstacles and baits
t_block ***init_board()
{
    int m, rand_row, rand_col, obs_coord;
    srand(time(NULL));
    
    m = 10;
    // we should allocate memory for the board using malloc at the end we will free it
    t_block ***board = (t_block ***)malloc(sizeof(t_block **) * m);
    for(int i = 0; i < 10; i++)
    {
        board[i] = (t_block **)malloc(sizeof(t_block *) * 10);
        for(int j = 0; j < 10; j++)
        {
            board[i][j] = (t_block *)malloc(sizeof(t_block) * 10);
            board[i][j]->type = 'e';
            board[i][j]->value = 0;
        }
    }

    rand_row = rand() % 10;
    rand_col = rand() % 10;
    while(rand_row == 0 && rand_col == 0) // in the start of the game snake is in (0,0) so we dont want to be in here
    {
        rand_row = rand() % 10;
        rand_col = rand() % 10;
    }
    board[rand_row][rand_col]->type = 'o';
    board[rand_row][rand_col]->value = rand() % 9 + 1;
    obs_coord = rand_row * 10 + rand_col; // this holds the coordinate of the obstacle as a single integer
    rand_col = rand() % 10;
    rand_row = rand() % 10;
    while(rand_row == 0 && rand_col == 0 && ((rand_row * 10 + rand_col) == obs_coord)) // this check is for obs and bait not to be on the same block
    {
        rand_row = rand() % 10;
        rand_col = rand() % 10;
    }
    board[rand_row][rand_col]->type = 'b';
    board[rand_row][rand_col]->value = 0;
    return board;
}

int main(void)
{
    t_block ***board = init_board(); // i initialized the board here
    play(board);

    // we should free up the board
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
            free(board[i][j]); // this frees the array at board[i][j]
        free(board[i]); // this frees the array at board[i] which we freed every array inside of it
    }
    free(board); // this frees the board that we free every array inside of it
    return 0;
}