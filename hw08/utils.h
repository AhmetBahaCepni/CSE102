#ifndef UTILS_H
#define UTILS_H

// this is the struct I used for puzzle
// It holds the map, score, move count and isOver flag
typedef struct s_puzzle{
    int map[3][3];
    int score;
    int move_c;
    int isOver;
} t_puzzle;

// These are the functions I used for puzzle
int		check_if_puzzle_solvable(t_puzzle my_puzzle);
void	save_current_board(t_puzzle my_puzzle);
void	save_score(t_puzzle my_puzzle);
char	to_upper(char c);
void	isGameOver(t_puzzle *my_puzzle);
void	print_map(t_puzzle my_puzzle);
void	randomize_map(t_puzzle *my_puzzle);
int		isMovable(t_puzzle my_puzzle, int *pos, int move_int, char move_char);
int		*find_position(t_puzzle my_puzzle, int move_int);
void	move(t_puzzle *my_puzzle, int move_int, char move_char);
void	gameplay();
int		isPcMovable(t_puzzle my_puzzle, int *pos, int move_rnd, int old_move);
void	auto_finish(t_puzzle *my_puzzle, int temp_rnd, int reccur_times);
void	solve_with_pc();
void	print_best_score();

#endif