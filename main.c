/* Programmer name: Genevieve Kochel
Date: October 26th 2023
Assignment Description: PA 6 - This assignment simulates a game of battleship via text. The program
interacts with the user as if it is the second player in battleship. The user is player 1
File Description: This file will contain the code for the main gameplay */

#include "header.h"


int main(void)
{
	/****** VARIABLE DECLARATIONS *******/

	srand((unsigned int) time(NULL)); // allows random number generation in who_starts_first() function

	int player_playing_turn = 0, user_input = 0, player1_turn_count = 1, player2_turn_count = 1, winner_determined = 0;

	char which_ship_hit = '\0'; // character reflects which ship was hit during a turn, if any
	char* ship_hit_ptr = &which_ship_hit;

	Stats player1 = { 0, 0, 0, 0, 0.0 },
		player2 = { 0, 0, 0, 0, 0.0 }; 

	Stats* player1_ptr = &player1;
	Stats* player2_ptr = &player2;
	

	char player1_board[MAX_ROWS][MAX_COLUMNS] = {{'\0'}},
		player2_board[MAX_ROWS][MAX_COLUMNS] = {{'\0'}}; // initially null characters, must be populated with '~' when game starts
	
	
	/****** INITIALIZE BOARDS AND SET UP GAME *******/

	FILE* outfile = fopen("battleship.log", "w"); // open output file battleship.log for writing

	welcome_screen();
	
	initialize_game_board(player1_board, 10, 10);
	initialize_game_board(player2_board, 10, 10); // initialize player 1 and player 2's boards to '~'

	system("pause");

	system("cls");

	do {

		printf("Please select from the following menu:\n\n"
		"1) Place ships manually\n"
		"2) Randomly generate gameboard\n\n"
		"Enter your selection here: ");

		scanf("%d", &user_input);

		if (user_input != 1 && user_input != 2)
		{
			system("cls");
			printf("Invalid input!! Please enter a valid selction (1 or 2)\n");
		}

	} while (user_input != 1 && user_input != 2);

	switch (user_input)
	{
	case 1:
		
		system("cls");
		display_board(player1_board, 10, 10, 1);
		manually_place_ships_on_board(player1_board);

		break;

	case 2:

		randomly_place_ships_on_board(player1_board);
		system("cls");

		break;
	}

	randomly_place_ships_on_board(player2_board);

	printf("\nPlayer 2's gameboard has been generated!\n");

	player_playing_turn = select_who_starts_first();

	printf("\nPlayer %d has been selected to play first!\n\n", player_playing_turn);

	

	/******* PLAY GAME *******/ 
	while (winner_determined != 1 && winner_determined != 2) // while no winner
	{
		putchar('\n');
		system("pause");
		system("cls");

		putchar('\n');
		printf("Player #1 gameboard:\n\n");
		display_board(player1_board, 10, 10, 1);
		printf("\n\nPlayer #2 gameboard:\n\n");
		display_board(player2_board, 10, 10, 2);

		if (player_playing_turn == 1)
		{

			//play_player1_turn(player1_board, player2_board, player1_ptr, player2_ptr, which_ship_hit, outfile, player1_turn_count);// play player 1 turn
			int result_shot = -2, row = 0, col = 0, shot_valid = 0, is_ship_sunk = 0;
			
			while (!shot_valid)
			{
				do {

					printf("\nTake a shot! Enter a row number (1-9) followed by a column number (1-9): ");
					scanf("%d%d", &row, &col);

					if (row < 0 || row > 9 || col < 0 || col > 9)
					{
						system("cls");
						printf("\nInvalid input. Please enter a new shot.\n");
					}


				} while (row < 0 || row > 9 || col < 0 || col > 9);

				result_shot = check_shot(1, player1_board, player2_board, row, col, player1_ptr, player2_ptr, ship_hit_ptr); //check shot 

				if (result_shot == -1)
				{
					system("cls");
					printf("\nYou already entered that shot. Please enter another.\n"); // you already took that shot
					shot_valid = 0;
				}
				else
				{
					shot_valid = 1;
				}
			}

			update_board(player2_board, result_shot, row, col);

			if (result_shot == 1) // if was a hit, check if ship was sunk and print message
			{
				printf("\nYour shot at (row %d, column %d) was a hit!\n", row, col);
				is_ship_sunk = check_if_sunk_ship(player2_board, which_ship_hit, 10, 10);

				if (is_ship_sunk)
				{
					printf("\nYou sunk a ship!\n");
				}

			}
			if (result_shot == 0)
			{
				system("cls");
				printf("\nSorry, your shot at (row %d, column %d) was a miss!\n\n", row, col);
			}

			output_current_move(outfile, 1, result_shot, is_ship_sunk, which_ship_hit, row, col, player1_turn_count);
			

			winner_determined = is_winner(1, player1_board, player2_board, player1_ptr, player2_ptr);

			printf("\nHit enter to continue playing!\n");
			putchar('\n');
			system("pause");
			system("cls");

			++player1_turn_count;
			player_playing_turn = 2; // then player 2 player thier turn after player 1
		}

		else if (player_playing_turn == 2)
		{
			
			// clear screen?????????
			//play_player1_turn(player1_board, player2_board, player1_ptr, player2_ptr, which_ship_hit, outfile, player1_turn_count);// play player 1 turn
			int result_shot = -2, row = 0, col = 0, shot_valid = 0, is_ship_sunk = 0;
			int* row_ptr = &row;
			int* col_ptr = &col;

			while (!shot_valid)
			{
				gen_random_shot(row_ptr, col_ptr);

				result_shot = check_shot(2, player1_board, player2_board, row, col, player1_ptr, player2_ptr, ship_hit_ptr); //check shot 

				if (result_shot == -1)
				{
					shot_valid = 0;
				}
				else
				{
					shot_valid = 1;
				}
			}

			update_board(player1_board, result_shot, row, col);

			if (result_shot == 1) // if was a hit, check if ship was sunk and print message
			{
				printf("\nPlayer 2 shot at (row %d, column %d) and it was a hit!\n\n", row, col);
				is_ship_sunk = check_if_sunk_ship(player1_board, which_ship_hit, 10, 10);

				if (is_ship_sunk)
				{
					printf("\nPlayer 2 sunk one of your ships!\n\n");
				}

			}
			if (result_shot == 0)
			{
				system("cls");
				printf("\nPlayer 2 shot at (row %d, column %d) and missed!\n", row, col);
			}

			output_current_move(outfile, 2, result_shot, is_ship_sunk, which_ship_hit, row, col, player2_turn_count);


			winner_determined = is_winner(2, player1_board, player2_board, player1_ptr, player2_ptr);// play player 2 turn

			++player2_turn_count;
			player_playing_turn = 1; // player 1 plays after
		}

	}

	if (winner_determined == 1)
	{
		printf("\nPlayer 1 is the winner!\n");
	}
	if (winner_determined == 2)
	{
		printf("\nPlayer 2 is the winner!\n");
	}

	printf("\nStatistics outputted to outfile successfully!\n");
	

	/********* OUTPUT STATS TO LOG FILE *********/
	
	output_stats(outfile, player1_ptr, player2_ptr);
	
	/************ CLOSE LOG FILE ***********/
	fclose(outfile); 
	return 0;
}