/* Programmer name: Genevieve Kochel
Date: October 26th 2023
Assignment Description: PA 6 - This assignment simulates a game of battleship via text. The program
interacts with the user as if it is the second player in battleship. The user is player 1
File Description: This file will include all the function declarations for the program. */

#include "header.h"

/*Function: void welcome_screen ()
Description: This function displays an intial welcome message for battleship and displays the rules of the game.
Date created: October 27th 2023
Date last modified: October 27th 2023
Input parameters:None, void.
Returns: None, void.
Preconditions: <stdio.h> and _CRT_SECURE_NO_WARNINGS must be defined/included in the header file
Postconditions: A welcome message and the rules of battleship must be printed to the screen.
*/
void welcome_screen(void) {

	printf("********* WELCOME TO BATTLESHIP *********\n");
	printf("\nBattleship is a two player Navy game. The user is player 1 and the computer is player 2.\n"
		"The objective of the game is to sink all ships in your enemy's fleet. The player to sink his / her\n"
		"enemy's fleet first wins. Both players' fleets consist of 5 ships that are hidden from the enemy.\n" 
		"Each ship may be differentiated by its 'size' (besides the Cruiser and Submarine) or number of cells\n"
		"it expands on the game board.The Carrier has 5 cells, Battleship has 4 cells, Cruiser has 3 cells,\n" 
		"Submarine has 3 cells, and the Destroyer has 2 cells.\n");
	printf("\nPress enter to start the game!\n");

}

/*Function: int select_who_starts_first ()
Description: Function randomly generates a number 1-2 corresponding to the player who starts first in the first turn of battleship.
Date created: October 27th 2023
Date last modified: October 27th 2023
Input: None
Returns: An integer (1 or 2) corresponding to the player that will start first in the game.
Preconditions: srand() must be called once in main. 
Postconditions: An integer 1 or 2 must be outputted by the function, and function should be called in main and assigned to variable
who_starts_first that is used as a loop condition for which player will play thier turn first.
*/

int select_who_starts_first(void) {
	int who_starts_first = 0;

	who_starts_first = rand() % 2 + 1;

	return who_starts_first;
}

/*Function: void manually_place_ships_on_board(char player1_board[10][10]);
Description: This function allows the user to select where they want to place thier 5 ships on thier gameboard.
The function must also check that the user does not try to place the ships diagonally, enters values outside of 
bounds of array (ex: larger than 10 - 9 index is max so subtract 1), and if they try to place a ship somewhere they have 
already selected to place a ship. The user is prompted to place the carrier, battleship, cruiser, submarine, and destroyer
in that order. A 'c', 'b', 'r', 's' or 'd' will be placed in the slot of the gameboard where a piece of the corresponding ship exists.
Date created: October 27th 2023
Date last modified: October 27th 2023
Input: Gameboard array for player 1 of max size 10x10.
Returns: None, void.
Preconditions: Player1_board array must be defined and user must have selected to manually place ships on board before function
call.
Postconditions: Player1_board array must be altered to reflect the placement of all 5 ships by the user, and the user's 
gameboard must be printed to the screen after to display what they selected.
*/

void manually_place_ships_on_board(char player1_board[][MAX_COLUMNS])
{
	int count = 0;
	char carrier_direction = '\0', battleship_direction = '\0', cruiser_direction = '\0', submarine_direction = '\0', destroyer_direction = '\0';
	

	/**** Place Carrier ****/

	do {
		printf("\nPlease enter the direction (horisontal or vertical) you would like to place your Carrier (h/v): ");
		scanf(" %c", &carrier_direction);

		if (carrier_direction != 'h' && carrier_direction != 'v')
		{
			system("cls");
			display_board(player1_board, 10, 10, 1);
			printf("\n** INVALID INPUT: Please enter a direction (h/v) **\n");
		}

	} while (carrier_direction != 'h' && carrier_direction != 'v'); // input validation

	if (carrier_direction == 'h')
	{
		int row = 0, col = 0, direction_valid = 0, is_input_overlap = 0;

		while (count < CARRIER)
		{
			do {

				if (count == 0 || is_input_overlap == 1) // get new col and row if first selection or player tried to crash ship
				{
					if (is_input_overlap == 1)
					{
						system("cls");
						display_board(player1_board, 10, 10, 1);
						printf("\nThat input is invalid! Please enter new input for your Carrier.\n");
					}

					do {
						
						system("cls");
						display_board(player1_board, 10, 10, 1);
						printf("\nEnter the row you would like to place your Carrier across: ");
						scanf("%d", &row);

					} while (row < 0 || row > 9);
				}

				do {
					
					printf("\nEnter column #%d of your placement. Note that you can only place each piece\n"
						"across the selected row (%d) and you may not go off the gameboard, crash with other ships\n"
						"or re-enter the same column more than once: ", count + 1, row);
					scanf("%d", &col);



					if ((count == 0 && (col + CARRIER) <= MAX_COLUMNS) ||
						(count > 0 && player1_board[row][col] != 'c' && player1_board[row][col + 1] != 'c' && player1_board[row][col - 1] == 'c'))
					{
						direction_valid = 1;
					}
					else // else
					{
						direction_valid = 0;
						system("cls");
						display_board(player1_board, 10, 10, 1);
						printf("\nInvalid input. Please try again.\n");
					}

					if (count == 0) {

						is_input_overlap = is_overlap(player1_board, CARRIER, 0, col, row); // checks to see if ships will crash
						

					}


				} while ((col < 0 || col > 9) || !direction_valid);



			} while (is_input_overlap == 1);

			player1_board[row][col] = 'c';
			++count;
		}

	}

	else if (carrier_direction == 'v')
	{
		int row = 0, col = 0, direction_valid = 0, is_input_overlap = 0;

		while (count < CARRIER)
		{
			do {

				if (count == 0 || is_input_overlap == 1) // get new col and row if first selection or player tried to crash ship
				{
					if (is_input_overlap == 1)
					{
						system("cls");
						display_board(player1_board, 10, 10, 1);
						printf("\nThat input is invalid! Please enter new input for your Carrier.\n");
					}

					do {
						printf("\nEnter the column you would like to place your Carrier down: ");
						scanf("%d", &col);
					} while (col < 0 || col > 9);
				}

				do {
					printf("\nEnter row #%d of your placement. Note that you can only place each piece\n"
						"down the selected column (%d) and you may not go off the gameboard, crash with other ships\n"
						"or re-enter the same row more than once: ", count + 1, col);
					scanf("%d", &row);



					if ((count == 0 && (row + CARRIER) <= MAX_ROWS) ||
						(count > 0 && player1_board[row][col] != 'c' && player1_board[row + 1][col] != 'c' && player1_board[row - 1][col] == 'c'))
					{
						direction_valid = 1;
					}
					else // else
					{
						direction_valid = 0;
						system("cls");
						display_board(player1_board, 10, 10, 1);
						printf("\nInvalid input. Please try again.\n");
					}

					if (count == 0) {

						is_input_overlap = is_overlap(player1_board, CARRIER, 1, col, row); // checks to see if ships will crash, only check when entering first input

					}

				} while ((row < 0 || row > 9) || !direction_valid);


			} while (is_input_overlap == 1);

			player1_board[row][col] = 'c';
			++count;
		}


	}

		/**********Place Battleship***********/
		
		system("cls");
		display_board(player1_board, 10, 10, 1); // display updated board

		count = 0;
		do {
			printf("\nPlease enter the direction (horisontal or vertical) you would like to place your Battleship (h/v): ");
			scanf(" %c", &battleship_direction);

			if (battleship_direction != 'h' && battleship_direction != 'v')
			{
				system("cls");
				display_board(player1_board, 10, 10, 1);
				printf("\n** INVALID INPUT: Please enter a direction (h/v) **\n");
			}

		} while (battleship_direction != 'h' && battleship_direction != 'v'); // input validation

		if (battleship_direction == 'h')
		{
			int row = 0, col = 0, direction_valid = 0, is_input_overlap = 0;

			while (count < BATTLESHIP)
			{
				do {

					if (count == 0 || is_input_overlap == 1) // get new col and row if first selection or player tried to crash ship
					{
						if (is_input_overlap == 1)
						{
							system("cls");
							display_board(player1_board, 10, 10, 1);
							printf("\nThat input is invalid! Please enter new input for your Battleship.\n");
						}

						do {
							printf("\nEnter the row you would like to place your Battleship across: ");
							scanf("%d", &row);
						} while (row < 0 || row > 9);
					}

					do {
						printf("\nEnter column #%d of your placement. Note that you can only place each piece\n"
							"across the selected row (%d) and you may not go off the gameboard, crash with other ships\n"
							"or re-enter the same column more than once: ", count + 1, row);
						scanf("%d", &col);



						if ((count == 0 && (col + BATTLESHIP) <= MAX_COLUMNS) ||
							(count > 0 && player1_board[row][col] != 'b' && player1_board[row][col + 1] != 'b' && player1_board[row][col - 1] == 'b'))
						{
							direction_valid = 1;
						}
						else
						{
							direction_valid = 0;
							system("cls");
							display_board(player1_board, 10, 10, 1);
							printf("\nInvalid input. Please try again.\n");
						}

						if (count == 0) {

							is_input_overlap = is_overlap(player1_board, BATTLESHIP, 0, col, row); // checks to see if ships will crash

						}

					} while ((col < 0 || col > 9) || !direction_valid);


				} while (is_input_overlap == 1);

				player1_board[row][col] = 'b';
				++count;
			}

		}

		else if (battleship_direction == 'v')
		{
			int row = 0, col = 0, direction_valid = 0, is_input_overlap = 0;

			while (count < BATTLESHIP)
			{
				do {

					if (count == 0 || is_input_overlap == 1) // get new col and row if first selection or player tried to crash ship
					{
						if (is_input_overlap == 1)
						{
							system("cls");
							display_board(player1_board, 10, 10, 1);
							printf("\nThat input is invalid! Please enter new input for your Battleship.\n");
						}

						do {
							printf("\nEnter the column you would like to place your Battleship down: ");
							scanf("%d", &col);
						} while (col < 0 || col > 9);
					}

					do {
						printf("\nEnter row #%d of your placement. Note that you can only place each piece\n"
							"down the selected column (%d) and you may not go off the gameboard, crash with other ships\n"
							"or re-enter the same row more than once: ", count + 1, col);
						scanf("%d", &row);



						if ((count == 0 && (row + BATTLESHIP) <= MAX_ROWS) ||
							(count > 0 && player1_board[row][col] != 'b' && player1_board[row + 1][col] != 'b' && player1_board[row - 1][col] == 'b'))
						{
							direction_valid = 1;
						}
						else
						{
							direction_valid = 0;
							system("cls");
							display_board(player1_board, 10, 10, 1);
							printf("\nInvalid input. Please try again.\n");
						}

						if (count == 0) {

							is_input_overlap = is_overlap(player1_board, BATTLESHIP, 1, col, row); // checks to see if ships will crash, only check when entering first input

						}

					} while ((row < 0 || row > 9) || !direction_valid);


				} while (is_input_overlap == 1);

				player1_board[row][col] = 'b';
				++count;
			}


		}

		system("cls");
		display_board(player1_board, 10, 10, 1); // display updated board

		/* Place Cruiser */

		count = 0; 
		do {
			printf("\nPlease enter the direction (horisontal or vertical) you would like to place your Cruiser (h/v): ");
			scanf(" %c", &cruiser_direction);
			
			if (cruiser_direction != 'h' && cruiser_direction != 'v')
			{
				system("cls");
				display_board(player1_board, 10, 10, 1);
				printf("\n** INVALID INPUT: Please enter a direction (h/v) **\n");
			}

		} while (cruiser_direction != 'h' && cruiser_direction != 'v'); // input validation

		if (cruiser_direction == 'h')
		{
			int row = 0, col = 0, direction_valid = 0, is_input_overlap = 0;

			while (count < CRUISER)
			{
				do {

					if (count == 0 || is_input_overlap == 1) // get new col and row if first selection or player tried to crash ship
					{
						if (is_input_overlap == 1)
						{
							system("cls");
							display_board(player1_board, 10, 10, 1);
							printf("\nThat input is invalid! Please enter new input for your Cruiser.\n");
						}

						do {
							printf("\nEnter the row you would like to place your Cruiser across: ");
							scanf("%d", &row);
						} while (row < 0 || row > 9);
					}

					do {
						printf("\nEnter column #%d of your placement. Note that you can only place each piece\n"
							"dacross the selected row (%d) and you may not go off the gameboard, crash with other ships\n"
							"or re-enter the same column more than once: ", count + 1, row);
						scanf("%d", &col);



						if ((count == 0 && (col + CRUISER) <= MAX_ROWS) ||
							(count > 0 && player1_board[row][col] != 'r' && player1_board[row][col + 1] != 'r' && player1_board[row][col - 1] == 'r'))
						{
							direction_valid = 1;
						}
						else
						{
							direction_valid = 0;
							system("cls");
							display_board(player1_board, 10, 10, 1);
							printf("\nInvalid input. Please try again.\n");
						}

						if (count == 0) {

							is_input_overlap = is_overlap(player1_board, CRUISER, 0, col, row); // checks to see if ships will crash

						}

					} while ((col < 0 || col > 9) || !direction_valid);


				} while (is_input_overlap == 1);

				player1_board[row][col] = 'r';
				++count;
			}

		}

		else if (cruiser_direction == 'v')
		{
			int row = 0, col = 0, direction_valid = 0, is_input_overlap = 0;

			while (count < CRUISER)
			{
				do {
				
					if (count == 0 || is_input_overlap == 1) // get new col and row if first selection or player tried to crash ship
					{
						if (is_input_overlap == 1)
						{
							system("cls");
							display_board(player1_board, 10, 10, 1);
							printf("\nThat input is invalid! Please enter new input for your Cruiser.\n");
						}

						do {
						printf("\nEnter the column you would like to place your Cruiser down: ");
						scanf("%d", &col);
						} while (col < 0 || col > 9);
					}

					do {
					printf("\nEnter row #%d of your placement. Note that you can only place each piece\n"
						"down the selected column (%d) and you may not go off the gameboard, crash with other ships\n"
						"or re-enter the same row more than once: ", count + 1, col);
					scanf("%d", &row);

					

					if ( (count == 0 && (row + CRUISER) <= MAX_ROWS) ||
						(count > 0 && player1_board[row][col] != 'r' && player1_board[row + 1][col] != 'r' && player1_board[row - 1][col] == 'r') )
					{
						direction_valid = 1;
					}
					else
					{
						direction_valid = 0;
						system("cls");
						display_board(player1_board, 10, 10, 1);
						printf("\nInvalid input. Please try again.\n");
					}
					
					if (count == 0) {

						is_input_overlap = is_overlap(player1_board, CRUISER, 1, col, row); // checks to see if ships will crash

					}

					} while ((row < 0 || row > 9) || !direction_valid);


				} while (is_input_overlap == 1);
				
				player1_board[row][col] = 'r';
				++count;
			}
			

		}

		system("cls");
		display_board(player1_board, 10, 10, 1); // display updated board

		/***** Place Submarine ******/

		count = 0;
		do {
			printf("\nPlease enter the direction (horisontal or vertical) you would like to place your Submarine (h/v): ");
			scanf(" %c", &submarine_direction);

			if (submarine_direction != 'h' && submarine_direction != 'v')
			{
				printf("\n** INVALID INPUT: Please enter a direction (h/v) **\n");
			}

		} while (submarine_direction != 'h' && submarine_direction != 'v'); // input validation

		if (submarine_direction == 'h')
		{
			int row = 0, col = 0, direction_valid = 0, is_input_overlap = 0;

			while (count < SUBMARINE)
			{
				do {

					if (count == 0 || is_input_overlap == 1) // get new col and row if first selection or player tried to crash ship
					{
						if (is_input_overlap == 1)
						{
							system("cls");
							display_board(player1_board, 10, 10, 1);
							printf("\nThat input is invalid! Please enter new input for your Submarine.\n");
						}

						do {
							printf("\nEnter the row you would like to place your Submarine across: ");
							scanf("%d", &row);
						} while (row < 0 || row > 9);
					}

					do {
						printf("\nEnter column #%d of your placement. Note that you can only place each piece\n"
							"dacross the selected row (%d) and you may not go off the gameboard, crash with other ships\n"
							"or re-enter the same column more than once: ", count + 1, row);
						scanf("%d", &col);



						if ((count == 0 && (col + SUBMARINE) <= MAX_ROWS) ||
							(count > 0 && player1_board[row][col] != 's' && player1_board[row][col + 1] != 's' && player1_board[row][col - 1] == 's'))
						{
							direction_valid = 1;
						}
						else
						{
							direction_valid = 0;
							system("cls");
							display_board(player1_board, 10, 10, 1);
							printf("\nInvalid input. Please try again.\n");
						}

						if (count == 0) {

							is_input_overlap = is_overlap(player1_board, SUBMARINE, 0, col, row); // checks to see if ships will crash

						}

					} while ((col < 0 || col > 9) || !direction_valid);


				} while (is_input_overlap == 1);

				player1_board[row][col] = 's';
				++count;
			}

		}

		else if (submarine_direction == 'v')
		{
			int row = 0, col = 0, direction_valid = 0, is_input_overlap = 0;

			while (count < SUBMARINE)
			{
				do {

					if (count == 0 || is_input_overlap == 1) // get new col and row if first selection or player tried to crash ship
					{
						if (is_input_overlap == 1)
						{
							system("cls");
							display_board(player1_board, 10, 10, 1);
							printf("\nThat input is invalid! Please enter new input for your Submarine.\n");
						}

						do {
							printf("\nEnter the column you would like to place your Submarine down: ");
							scanf("%d", &col);
						} while (col < 0 || col > 9);
					}

					do {
						printf("\nEnter row #%d of your placement. Note that you can only place each piece\n"
							"down the selected column (%d) and you may not go off the gameboard, crash with other ships\n"
							"or re-enter the same row more than once: ", count + 1, col);
						scanf("%d", &row);



						if ((count == 0 && (row + SUBMARINE) <= MAX_ROWS) ||
							(count > 0 && player1_board[row][col] != 's' && player1_board[row + 1][col] != 's' && player1_board[row - 1][col] == 's'))
						{
							direction_valid = 1;
						}
						else
						{
							direction_valid = 0;
							system("cls");
							display_board(player1_board, 10, 10, 1);
							printf("\nInvalid input. Please try again.\n");
						}

						if (count == 0) {

							is_input_overlap = is_overlap(player1_board, SUBMARINE, 1, col, row); // checks to see if ships will crash

						}

					} while ((row < 0 || row > 9) || !direction_valid);


				} while (is_input_overlap == 1);

				player1_board[row][col] = 's';
				++count;
			}


		}

		system("cls");
		display_board(player1_board, 10, 10, 1);

		/******* Place Destroyer *****/

		count = 0;
		do {
			printf("\nPlease enter the direction (horisontal or vertical) you would like to place your Destroyer (h/v): ");
			scanf(" %c", &destroyer_direction);

			if (destroyer_direction != 'h' && destroyer_direction != 'v')
			{
				printf("\n** INVALID INPUT: Please enter a direction (h/v) **\n");
			}

		} while (destroyer_direction != 'h' && destroyer_direction != 'v'); // input validation

		if (destroyer_direction == 'h')
		{
			int row = 0, col = 0, direction_valid = 0, is_input_overlap = 0;

			while (count < DESTROYER)
			{
				do {

					if (count == 0 || is_input_overlap == 1) // get new col and row if first selection or player tried to crash ship
					{
						if (is_input_overlap == 1)
						{
							system("cls");
							display_board(player1_board, 10, 10, 1);
							printf("\nThat input is invalid! Please enter new input for your Destroyer.\n");
						}

						do {
							printf("\nEnter the row you would like to place your Destroyer across: ");
							scanf("%d", &row);
						} while (row < 0 || row > 9);
					}

					do {
						printf("\nEnter column #%d of your placement. Note that you can only place each piece\n"
							"dacross the selected row (%d) and you may not go off the gameboard, crash with other ships\n"
							"or re-enter the same column more than once: ", count + 1, row);
						scanf("%d", &col);



						if ((count == 0 && (col + DESTROYER) <= MAX_ROWS) ||
							(count > 0 && player1_board[row][col] != 'd' && player1_board[row][col + 1] != 'd' && player1_board[row][col - 1] == 'd'))
						{
							direction_valid = 1;
						}
						else
						{

							direction_valid = 0;
							system("cls");
							display_board(player1_board, 10, 10, 1);
							printf("\nInvalid input. Please try again.\n");
						}

						if (count == 0) {

							is_input_overlap = is_overlap(player1_board, DESTROYER, 0, col, row); // checks to see if ships will crash

						}

					} while ((col < 0 || col > 9) || !direction_valid);


				} while (is_input_overlap == 1);

				player1_board[row][col] = 'd';
				++count;
			}

		}

		else if (cruiser_direction == 'v')
		{
			int row = 0, col = 0, direction_valid = 0, is_input_overlap = 0;

			while (count < DESTROYER)
			{
				do {

					if (count == 0 || is_input_overlap == 1) // get new col and row if first selection or player tried to crash ship
					{
						if (is_input_overlap == 1)
						{
							system("cls");
							display_board(player1_board, 10, 10, 1);
							printf("\nThat input is invalid! Please enter new input for your Destroyer.\n");
						}

						do {
							printf("\nEnter the column you would like to place your Destroyer down: ");
							scanf("%d", &col);
						} while (col < 0 || col > 9);
					}

					do {
						printf("\nEnter row #%d of your placement. Note that you can only place each piece\n"
							"down the selected column (%d) and you may not go off the gameboard, crash with other ships\n"
							"or re-enter the same row more than once: ", count + 1, col);
						scanf("%d", &row);



						if ((count == 0 && (row + DESTROYER) <= MAX_ROWS) ||
							(count > 0 && player1_board[row][col] != 'd' && player1_board[row + 1][col] != 'd' && player1_board[row - 1][col] == 'd'))
						{
							direction_valid = 1;
						}
						else
						{
							direction_valid = 0;
							system("cls");
							display_board(player1_board, 10, 10, 1);
							printf("\nInvalid input. Please try again.\n");
						}

						if (count == 0) {

							is_input_overlap = is_overlap(player1_board, DESTROYER, 1, col, row); // checks to see if ships will crash

						}

					} while ((row < 0 || row > 9) || !direction_valid);


				} while (is_input_overlap == 1);

				player1_board[row][col] = 'd';
				++count;
			}


		}


}

/*Function: void randomly_place_ships_on_board();
Description: This function randomly places the carrier, crusier, battleship, submarine and destroyer on the gameboard.
Date created: October 27th 2023
Date last modified: October 27th 2023
Input: 
Returns: Void, none.
Preconditions: The scoreboard of the user must be defined and the user must have selected to randomly place the boats. 
Postconditions: If randomly generating for user, the user's gameboard must be updated and printed to the screen after this function
call. When function used for placing computer ships, the computer's gameboard should be altered to reflect the position of the boats
but it should not be printed to the screen. 
*/

void randomly_place_ships_on_board(char player_board[][MAX_COLUMNS])
{
	int direction = 0, will_cause_overlap = 0, col = 0, row = 0, index = 0;
	int* row_start_ptr = &row;
	int* col_start_ptr = &col;
	
	/* Place Carrier */
	do {
		
		direction = rand() % 2; // generate random direction for ship between 1 and 2
		gen_start_pt(direction, CARRIER, row_start_ptr, col_start_ptr); // generate starting point
		will_cause_overlap = is_overlap(player_board, CARRIER, direction, col, row); // check if starting point will cause overlap, 
		// keep generating until valid starting point found

	} while (will_cause_overlap == 1);

	
	for (index = 0; index < CARRIER; ++index) {

		if (direction == 0) {
			player_board[row][col + index] = 'c';
		}
		if (direction == 1) {
			player_board[row + index][col] = 'c';
		}
	}

	/* Place Battleship */

	do {

		direction = rand() % 2; // generate random direction for ship between 1 and 2
		gen_start_pt(direction, BATTLESHIP, row_start_ptr, col_start_ptr); // generate starting point
		will_cause_overlap = is_overlap(player_board, BATTLESHIP, direction, col, row); // check if starting point will cause overlap, 
		// keep generating until valid starting point found

	} while (will_cause_overlap);

	for (index = 0; index < BATTLESHIP; ++index) {

		if (direction == 0) {
			player_board[row][col + index] = 'b';
		}
		if (direction == 1) {
			player_board[row + index][col] = 'b';
		}

	}

	/* Place Cruiser */

	do {

		direction = rand() % 2; // generate random direction for ship between 1 and 2
		gen_start_pt(direction, CRUISER, row_start_ptr, col_start_ptr); // generate starting point
		will_cause_overlap = is_overlap(player_board, CRUISER, direction, col, row); // check if starting point will cause overlap, 
		// keep generating until valid starting point found

	} while (will_cause_overlap);

	for (index = 0; index < CRUISER; ++index) {

		if (direction == 0) {
			player_board[row][col + index] = 'r';
		}
		if (direction == 1) {
			player_board[row + index][col] = 'r';
		}

	}

	/* Place Submarine */

	do {

		direction = rand() % 2; // generate random direction for ship between 1 and 2
		gen_start_pt(direction, SUBMARINE, row_start_ptr, col_start_ptr); // generate starting point
		will_cause_overlap = is_overlap(player_board, SUBMARINE, direction, col, row); // check if starting point will cause overlap, 
		// keep generating until valid starting point found

	} while (will_cause_overlap);

	for (index = 0; index < SUBMARINE; ++index) {

		if (direction == 0) {
			player_board[row][col + index] = 's';
		}
		if (direction == 1) {
			player_board[row + index][col] = 's';
		}

	}

	/* Place Destroyer */

	do {

		direction = rand() % 2; // generate random direction for ship between 1 and 2
		gen_start_pt(direction, DESTROYER, row_start_ptr, col_start_ptr); // generate starting point
		will_cause_overlap = is_overlap(player_board, DESTROYER, direction, col, row); // check if starting point will cause overlap, 
		// keep generating until valid starting point found

	} while (will_cause_overlap);

	for (index = 0; index < DESTROYER; ++index) {

		if (direction == 0) {
			player_board[row][col + index] = 'd';
		}
		if (direction == 1) {
			player_board[row + index][col] = 'd';
		}

	}



}

/*Function:  void initialize_gameboard (char gameboard[10][10])
Description: This function initializes all elements in a single 2-dimensional gameboard array to "-" characters
Date created: October 27th 2023
Date last modified: October 27th 2023
Input parameters: A single 2-dimensional array with 10 rows and 10 columns max (9 indexes on each side)
Returns: None, void.
Preconditions: Array being passed into the function must be defined and the function must only be called once
at the beginning of every battleship game.
Postconditions: The 2d array passed in must be altered to reflect the content of every index as as all "-"
*/
void initialize_game_board(char gameboard[][MAX_COLUMNS], int num_rows, int num_columns)
{
	int row_index = 0, col_index = 0;

	for (; row_index < num_rows; ++row_index)
	{
		for (col_index = 0; col_index < num_columns; ++ col_index)
		{
			gameboard[row_index][col_index] = '~';
		}
	}
}

/*Function: void display_board(char board[][MAX_COLUMNS], int num_rows, int num_cols, int player_num)
Description: This function displays the gameboard array.
Date created: October 27th 2023
Date last modified: October 27th 2023
Input parameters: A single 2-dimensional array with 10 rows and 10 columns max (9 indexes on each side), the number of rows, 
number of columns, and the player number for which to display the board.
Returns: None, void.
Preconditions: <stdio.h> must be included in the header, the scoreboard array must be defined in main. 
Postconditions: The scoreboard array for the player passed in must be printed to the screen. Player 2's board is only printed with waves,
hits (*) and misses (m) to keep the location of its ships unknown to the user.
*/
void display_board(char board[][MAX_COLUMNS], int num_rows, int num_cols, int player_num) 
{
	int row_index = 0, col_index = 0;
	
	if (player_num == 1)
	{
		printf("%5d%4d%4d%4d%4d%4d%4d%4d%4d%4d\n", 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);

		for (; row_index < num_rows; ++row_index)
		{
			printf("%-2d", row_index);
			for (col_index = 0; col_index < num_cols; ++col_index)
			{

				printf("%-2c%-2c", '|', board[row_index][col_index]);
			}
			putchar('|');
			putchar('\n');
		}
	}

	else
	{
		printf("%5d%4d%4d%4d%4d%4d%4d%4d%4d%4d\n", 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);

		for (; row_index < num_rows; ++row_index)
		{
			printf("%-2d", row_index);
			for (col_index = 0; col_index < num_cols; ++col_index)
			{
				if (board[row_index][col_index] == '*' || board[row_index][col_index] == '~' || board[row_index][col_index] == 'm')
				{
					printf("%-2c%-2c", '|', board[row_index][col_index]);
				} // if contents of an index is empty (~), a hit or a miss, prints the actual contents of computer board

				else
				{
					printf("%-2c%-2c", '|', '~');
				} // if contents contain the info where computer's ships are, prints wave to keep hidden

			}
			putchar('|');
			putchar('\n');
		}

	}
}

/*Function: int check_shot ()
Description: This function checks the shot taken by a player and determines if it is a hit or miss. 
Date created: November 2nd 2023
Date last modified: November 2nd 2023
Input: Number of player currently playing/taking the shot, gameboard of player that is being shot at, the coordinates of the shot, and two pointers to the specific
structs correspoinding to player 1's stats and player 2's stats.  
Returns: 1 if a hit, 0 if a miss and -1 if the user has already shot at those coordinates. 
Will use these numbers to update the board of player being shot at and to write to log file.
Preconditions: The scoreboard being shot at must be defined and the boats must have been placed previously. Row and column number must have 
been validated previous to function call to ensure not off the board.
Postconditions: Return value of this function must be used in a condition for update_scoreboard() for 0 or 1. If returns -1, the program must loop and get a new shot
from the user because they have already shot at that cell. Value at struct containing hits or misses for player shooting must be incremented by 1.
*/
int check_shot(int player_taking_shot, char player1_board[][MAX_COLUMNS], char player2_board[][MAX_COLUMNS], int row, int column, Stats* player1_stats, 
	Stats* player2_stats, char *ship_hit_ptr)
{
	

	// pass in &player1 for Stats* player1_stats and &player2 for Stats* player2_stats
	// player1_stats->hits
	if (player_taking_shot == 1) // user is taking shot
	{
		if (player2_board[row][column] == '~')
		{
			*ship_hit_ptr = '\0';
			player1_stats->misses += 1; // update player1 misses count
			player1_stats->total_shots += 1;
			return 0;
		}
		else if (player2_board[row][column] == 'b' || player2_board[row][column] == 'c' || player2_board[row][column] == 'r' || player2_board[row][column] == 's' || player2_board[row][column] == 'd')
		{
			if (player2_board[row][column] == 'b')
			{
				*ship_hit_ptr = 'b';
			}
			if (player2_board[row][column] == 'c')
			{
				*ship_hit_ptr = 'c';
			}
			if (player2_board[row][column] == 'r')
			{
				*ship_hit_ptr = 'r';
			}
			if (player2_board[row][column] == 's')
			{
				*ship_hit_ptr = 's';
			}
			else if (player2_board[row][column] == 'd')// the destroyer was hit
			{
				*ship_hit_ptr = 'd';
			}

			player1_stats->hits += 1;
			player1_stats->total_shots += 1;
			return 1;
		}
		else
		{
			return -1;
		}

	}
	if (player_taking_shot == 2) // computer is taking shot
	{
		if (player1_board[row][column] == '~')
		{
			*ship_hit_ptr = '\0';
			player2_stats->misses += 1;
			player2_stats->total_shots += 1;
			return 0;
		}
		else if (player1_board[row][column] == 'b' || player1_board[row][column] == 'c' || player1_board[row][column] == 'r' || player1_board[row][column] == 's' || player1_board[row][column] == 'd')
		{

			if (player1_board[row][column] == 'b')
			{
				*ship_hit_ptr = 'b';
			}
			else if (player1_board[row][column] == 'c')
			{
				*ship_hit_ptr = 'c';
			}
			else if (player1_board[row][column] == 'r')
			{
				*ship_hit_ptr = 'r';
			}
			else if (player1_board[row][column] == 's')
			{
				*ship_hit_ptr = 's';
			}
			else if (player1_board[row][column] == 'd') // the destroyer was hit
			{
				*ship_hit_ptr = 'd';
			}
			player2_stats->hits += 1;
			player2_stats->total_shots += 1;
			return 1;
		}
		else
		{
			return -1; // if no letters or no waves, means cell contains either 'm' or '*' so user has already entered that shot, loops until gets valid shot
		}

	}


}

/*Function: int is_winner()
Description: This function determines if there is a winner of battleship. 
Date created: November 2nd 2023
Date last modified: November 2nd 2023
Input: Player who is currently taking thier turn, the scoreboard arrays of both players and two pointers to stats struct for player 1 and player 2.
Returns: 1 if player 1 is the winner, 2 if player 2/computer is the winner, and 0 if there does not exist a winner yet.
Will use these numbers to get out of loop of player's turns and print to log file.
Preconditions: The scoreboard being shot at must be defined and the boats must have been placed previously. The player playing thier turn must have shot, the shot
must have been evaluated and the scoreboard of the player being shot at must have been updated to reflect the shot. 
Postconditions: Return value of this function must be used in a condition for main loop between player's turns.
The program continues to loop as long as there isn't a winner (this function's return value is 0), and prints to log file. Log file print function must be called
immediately after this function. Struct player 1 and 2 stats must have been updated to reflect if they won or lost.
*/
int is_winner(int player_taking_turn, char player1_scoreboard[][MAX_COLUMNS], char player2_scoreboard[][MAX_COLUMNS], Stats* player1_stats, Stats* player2_stats)
{
	 // pass stats struct into function...to determine who has reached 17 hits and won **struct pointer here
	if (player1_stats->hits == 17 && player_taking_turn == 1)
	{
		return 1; // player 1 won
		player1_stats->win_or_loss = 1; // updates stats struct to indicate player 1 won
		player2_stats->win_or_loss = 0; // updates stats struct to indicate player 2 lost
	}
	else if (player2_stats->hits == 17 && player_taking_turn == 2)
	{
		return 2; // computer won
		player2_stats->win_or_loss = 1; // updates stats struct to indicate player 2 won
		player1_stats->win_or_loss = 0; // updates stats struct to indicate player 1 lost
	}
	else 
	{
		return 0; // no winner yet
	}
}

/*Function: void update_board(char gameboard[][MAX COLS], int check shot, int row, int column)
Description: This function updates the gameboard with either a hit or miss, denoting the cell shot at with a '*' or 'm', respectively.
Date created: November 2nd 2023
Date last modified: November 2nd 2023
Input: Gameboard that was shot at, the value of check shot (0 or 1) and the row and column number of the shot taken.
Returns: None, void.
Preconditions: The scoreboard being shot at must be defined and the boats must have been placed previously. The player playing thier turn must have shot, and the shot
must have been evaluated prior to function call. 
Postconditions: The gameboard array of the player being shot at must be updated at the index of the row and column number passed in, either with a '*' or 'm'*/

void update_board(char gameboard[][MAX_COLUMNS], int check_shot, int row, int column)
{
	if (check_shot == 1) // hit
	{
		gameboard[row][column] = '*';
	}
	else // miss
	{
		gameboard[row][column] = 'm';
	}

}

/*Function: int check_if_sunk_ship(char scoreboard_arr[][MAX_COLUMNS], int ship_name)
Description: This function checks if a ship has been sunk based on value of which ship hit variable. 
Date created: November 3rd 2023
Date last modified: November 3rd 2023
Input: Scoreboard array of the player who's being shot at, a character variable representing which ship was hit, the number of rows and the number of columns 
of the scoreboard array. 
Returns: 1 if ship has sunk and 0 if that ship has not sunk. 
Preconditions: The scoreboard being shot at must be defined and the boats must have been placed previously. The player playing thier turn must have shot, the shot
must have been evaluated as a hit before this function is called; if not a hit, don't call this function. 
Postcondition: The value outputted by this function must be used to determine if need to print a message stating if/which ship was sunk by a player.
*/

int check_if_sunk_ship(char scoreboard_arr[][MAX_COLUMNS], char which_ship_hit, int rows, int cols)
{
	int is_ship_sunk = 0, index = 0, ship_count = 0, j = 0;

	for (; index < rows; ++index) // checks entire scoreboard for character of ship that was hit, if does not exist on board, returns 1
	{
		for (j = 0; j < cols; ++j)
		{
			if (scoreboard_arr[index][j] == which_ship_hit)
			{
				++ship_count;
			}
		}
	}
	
	if (ship_count > 0)
	{
		is_ship_sunk = 0; // ship not sunk
	}

	else if (ship_count == 0)
	{
		is_ship_sunk = 1;
	}
	
	return is_ship_sunk; // did not find a character matching which_ship_hit
}

/*Function: void output_current_move(FILE* outfile, int is_hit_or_miss, int is_ship_sunk, int is_winner)
Description: This function outputs the current shot of the player, whether the shot was a hit or miss and whether a ship was sunk.
Date created: November 3rd 2023
Date last modified: November 3rd 2023
Input: File to output to, integer representing player who is playing (1 or 2), if shot was a hit or miss (0 or 1), if the ship sunk, which ship was sunk (which_ship
_hit), the row number and column number of the shot, and the turn count for that player.
Returns: None, void.
Preconditions: The player must have successfully completed a turn and the logfile must have been opened successfully.
Postcondition: battleship.txt must have been written to with the player number and the turn number they are on, the shot they took and whether it was a
hit or miss, whether a ship was sunk (if a ship was sunk, which one).
*/

void output_current_move(FILE* outfile, int player_num, int is_hit_or_miss, int is_ship_sunk, char which_ship_hit, int row, int col, int turn_count)
{
	char ship_name[100] = "";
	if (which_ship_hit == 'c')
	{
		strcpy(ship_name, "Carrier");
	}
	else if (which_ship_hit == 'b')
	{
		strcpy(ship_name, "Battleship");
	}
	else if (which_ship_hit == 'r')
	{
		strcpy(ship_name, "Cruiser");
	}
	else if (which_ship_hit == 's')
	{
		strcpy(ship_name, "Submarine");
	}
	else if (which_ship_hit == 'd')
	{
		strcpy(ship_name, "Destroyer");
	}
	

	fprintf(outfile, "Turn #%d: Player %d:\n", turn_count, player_num);
	if (is_hit_or_miss == 1 && is_ship_sunk == 1) // shot was a hit and a ship was sunk
	{
	
		fprintf(outfile, "Your shot at (row %d, column %d) was a hit and the %s was sunk.\n\n", row, col, ship_name);

	}
	else if (is_hit_or_miss == 1 && is_ship_sunk == 0) // shot was a hit but ship was not sunk
	{
		fprintf(outfile, "Your shot at (row %d, column %d) was a hit on a %s but it was not sunk.\n\n", row, col, ship_name);

	}
	else if (is_hit_or_miss == 0 && which_ship_hit == '\0') // shot was a miss and ship was not sunk (obviously)
	{
		fprintf(outfile, "Your shot at (row %d, column %d) was miss. No ships were sunk.\n\n", row, col);

	}

}

/*Function: void output_stats(FILE* outfile, Stats player1, Stats player2)
Description: This function outputs the total number of hits, total number of misses, total number of shots taken, a hits to misses ratio as a percentage,
and who won or lost the game for EACH PLAYER.
Date created: November 3rd 2023
Date last modified: November 3rd 2023
Input: File to output to, the stats struct of player 1, and the stats struct of player 2.
Returns: None, void.
Preconditions: The game must have ended and there must have been a winner determined/broken out of gameplay loop. The battleship logfile must have been opened successfully.
Postcondition: battleship.txt must have been written to with the following information for each player: total hits, total misses, number of shots taken, a hits
to misses ratio. The winner and looser should also be printed. 
*/
void output_stats(FILE* outfile, Stats* player1, Stats* player2)
{
	player1->hits_misses_ratio = ((double)player1->hits / player1->total_shots) * 100; // calculate player 1 hits and misses ratio
	player2->hits_misses_ratio = ((double)player2->hits / player2->total_shots) * 100; // calculate computer hits and misses ratio


	fprintf(outfile, "******** FINAL STATS *******\n");
	fprintf(outfile, "Player #1:\n"
		"Total hits: %d\n"
		"Total misses: %d\n"
		"Total shots taken: %d\n"
		"Hits to misses ratio: %.2lf percent accuracy\n\n", player1->hits, player1->misses, player1->total_shots, player1->hits_misses_ratio);

	fprintf(outfile, "Player #2:\n"
		"Total hits: %d\n"
		"Total misses: %d\n"
		"Total shots taken: %d\n"
		"Hits to misses ratio: %.2lf percent accuracy\n\n", player2->hits, player2->misses, player2->total_shots, player2->hits_misses_ratio);

	if (player2->win_or_loss == 1)
	{
		fprintf(outfile, "WINNER: Player 2\n");
	}
	else if (player1->win_or_loss == 1)
	{
		fprintf(outfile, "WINNER: Player 1\n");
	}

}


/*Function: int is_overlap(char player_board[][MAX_COLUMNS], int length_ship, int direction, int col, int row)
Description: This function checks for possible overlap of ships when a player is placing thier ships on thier board.
Date created: October 29th 2023
Date last modified: October 29th 2023
Input parameters: A single 2-dimensional array with 10 rows and 10 columns max (9 indexes on each side), the length of the ship being placed (can use name),
an integer representing the direction the ship is being placed (1 for vertical, 0 for horisontal), the initial column number (if direction vertical, will be constant)
and initial row (if direction horisontal, will be constant).
Returns: 0 if no potential overlap found, 1 if found potential overlap.
Preconditions: Array being passed into the function must be defined, the direction placement of the ship must have been gotten from user input,
the (initial) column and (initial) row must have been checked for invalid input.
Postconditions: The 2d array passed in must be altered to reflect the content of every index as as all "-"
*/
int is_overlap(char player_board[][MAX_COLUMNS], int length_ship, int direction, int col, int row)
{

	int is_overlap = 0, count = 0; // returns false(no overlap) if none of the if statements evaluate to true

	// battleship


	if (direction == 1) // vertical, iterates down column starting at row number passed in 
	{
		for (count = 0; count < length_ship; ++count)
		{
			if (player_board[row + count][col] != '~')
			{
				++is_overlap;
			}
		}



	}

	else if (direction == 0) // horisontal, iterates down row starting at column number passed in (length of ship) number of times
	{
		for (count = 0; count < length_ship; ++count)
		{
			if (player_board[row][col + count] != '~')
			{
				++is_overlap;
			}
		}

		}

	// returns 1 if found overlap, 0 if didn't find overlap
	if (is_overlap != 0)
	{
		return 1; // found overlap
	}

	else
	{
		return 0; // did not find overlap
	}

}


/*Function: void gen_start_pt(int dir, int ship_length, int* row_start_ptr, int* col_start_ptr)
Description: This function generates a random starting point to place a ship and checks to ensure the ship does not go off the board.
Date created: October 29th 2023
Date last modified: October 29th 2023
Input parameters: The direction of the ship, the length of the ship (represented as a #define constant), a pointer to the starting row index and a pointer to the 
starting column index. 
Returns: None, void.
Preconditions: Player 1 must have chosen to randomly generate a board, or the computer must be playing.
Postconditions: The values of row and column must be indirectly modified to reflect a starting point that will not take the ship off the gameboard. 
This function is called in the function randomly_place_ships_on_board.
*/
void gen_start_pt(int dir, int ship_length, int* row_start_ptr, int* col_start_ptr)
{
	if (dir == 0) // horizontal
	{
		*row_start_ptr = rand() % MAX_ROWS;
		*col_start_ptr = rand() % (MAX_COLUMNS - ship_length + 1);
	}
	else // vertical
	{
		*row_start_ptr = rand() % (MAX_ROWS - ship_length + 1);
		*col_start_ptr = rand() % MAX_COLUMNS;
	}
}

/*Function: void gen_random_shot(int* row, int* col)
Description: This function generates a random row and column for a shot taken by the computer. 
Date created: November 3rd 2023
Date last modified: November 3rd 2023
Input parameters: A pointer to the row and column that will be generated for that shot.
Returns: None, void.
Preconditions: Computer must be playing a turn. 
Postconditions: The values of row and column must be indirectly modified to reflect a random row and column number (0-9). These values must be checked in check_shot() and 
must be regenerated if check_shot() returns -1 --> loop in main. 
*/
void gen_random_shot(int* row, int* col)
{
	*row = rand() % 10;
	*col = rand() % 10;

}





