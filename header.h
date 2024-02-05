/* Programmer name: Genevieve Kochel
Date: October 26th 2023
Assignment Description: PA 6 - This assignment simulates a game of battleship via text. The program
interacts with the user as if it is the second player in battleship. The user is player 1
File Description: This file will contain all of the #defines and #includes for the program */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#define MAX_ROWS 10
#define MAX_COLUMNS 10
#define CARRIER 5
#define BATTLESHIP 4
#define CRUISER 3
#define SUBMARINE 3
#define DESTROYER 2

typedef struct stats {

	int hits;
	int misses;
	int total_shots;
	int win_or_loss;
	double hits_misses_ratio;


}Stats;


void welcome_screen(void);
void initialize_game_board(char gameboard[][MAX_COLUMNS], int num_rows, int num_columns);
void manually_place_ships_on_board(char player1_board[][MAX_COLUMNS]);
void randomly_place_ships_on_board(char player_board[][MAX_COLUMNS]);
int select_who_starts_first(void);
int check_shot(int player_taking_shot, char player1_board[][MAX_COLUMNS], char player2_board[][MAX_COLUMNS], int row, int column, Stats* player1_stats,
	Stats* player2_stats, char *ship_hit_ptr);
int is_winner(int player_taking_turn, char player1_scoreboard[][MAX_COLUMNS], char player2_scoreboard[][MAX_COLUMNS], Stats* player1_stats, Stats* player2_stats);
void update_board(char gameboard[][MAX_COLUMNS], int check_shot, int row, int column);
void display_board(char board[][MAX_COLUMNS], int num_rows, int num_cols, int player_num);
int check_if_sunk_ship(char scoreboard_arr[][MAX_COLUMNS], char which_ship_hit, int rows, int cols);
void output_current_move(FILE* outfile, int player_num, int is_hit_or_miss, int is_ship_sunk, char which_ship_hit, int row, int col, int turn_count);
void output_stats(FILE* outfile, Stats* player1, Stats* player2);
int is_overlap(char player_board[][MAX_COLUMNS], int length_ship, int direction, int col, int row);
void gen_start_pt(int dir, int ship_length, int* row_start_ptr, int* col_start_ptr);
void gen_random_shot(int* row, int* col);
