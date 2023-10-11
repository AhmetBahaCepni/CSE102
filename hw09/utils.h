#ifndef UTILS_H
#define UTILS_H

typedef struct s_point{ // a point represents a body part of a snake
    int row;
    int col;
} t_point;

typedef struct s_block{ // a block represents a cell of the board
    char type;
    int value;
} t_block;

// snake is the bigger struct that has a point array for body parts
//  and other variables for game logic
typedef struct s_snake{
    t_point *body;
    int length;
    int direction;
    int score;
    int obs_count;
    int move_count;
    int is_over;
} t_snake;

// these are the functions i used in the game
t_block ***init_board();
void draw_board(t_snake snake, t_block ***board);
void play(t_block ***board);
int move(t_snake *snake);
int check_status(t_snake snake, t_block ***board);
void update(t_snake *snake, t_block ***board);

#endif