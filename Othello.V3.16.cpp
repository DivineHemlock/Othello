#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <cstring>
#include <conio.h>

struct PlayerInfo
{
	char player_name[10];
	int player_score;
};


struct GameInfo
{
int board_size;
int selected_row;
int selected_col;
char board[13][13];
char player_one_name[10];
char player_two_name[10]; 
int player_one_score;
int player_two_score;
int turn;
};

int calculate_player_two_score (char board[13][13] , int board_size);
int calculate_player_one_score (char board[13][13] , int board_size);
void player_one_flip(char board[13][13] , int board_size , int selected_row , int selected_col);
void player_two_flip(char board[13][13] , int board_size , int selected_row , int selected_col);
bool is_player_one_move_legal (char board[13][13] , int board_size , int selected_row , int selected_col);
bool is_player_two_move_legal (char board[13][13] , int board_size , int selected_row , int selected_col);
bool can_player_one_move (char board[13][13] , int board_size);
bool can_player_two_move (char board[13][13] , int board_size);
void line_BB();
void line_BM();
void line_BE();
void line_MB();
void line_MM();
void line_ME();
void line_EB();
void line_EM();
void line_EE();
void line_BB_pre_selected();
void line_MB_pre_selected();
void line_EB_pre_selected();
void line_M_pre_selected();
void make_space(int size);
void special_line(int row_of_the_selected_room, int current_row);
void draw_table_first_line(int columns);
void draw_table_middle_line(int columns);
void draw_table_end_line(int columns);
void print_content(char arr[13][13], int i, int j);
void draw_table_columns(int columns, int row, char arr[13][13]);
void draw_table_special_line_B(int columns,int column_of_selected_room, int row_of_the_selected_room, int current_row);
void draw_table_special_line_M(int columns,int column_of_selected_room, int row_of_the_selected_room, int current_row);
void draw_table_special_line_E(int columns,int column_of_selected_room, int row_of_the_selected_room, int current_row);
void draw_table_columns_special(int columns, int column_of_selected_room, int row, char arr[13][13]);
void score_board(char player_1_name[10], char player_2_name[10], char board[13][13] , int board_size , int turn);
void draw_the_table(int board_size, int selected_col, int selected_row, char board[13][13]);
void draw_touturial();
int return_save_option_in_load(GameInfo * games, int length);
int return_accepted_save_value(int current_room, int length);
void put_info_of_saves(GameInfo * games, int length_of_saves);
void write_new_saves(GameInfo * games, int length_of_saves);
void change_save_info(GameInfo * games, char board[13][13], int player_one_score , int player_two_score, int selected_save, int turn);
int get_players_num_in_leader_board();
void put_players_in_array(PlayerInfo * players, int length);
void sort_leader_board(PlayerInfo * players, int length);
void write_new_leader_board(PlayerInfo * players, int length);
void change_scores_in_leader_board(PlayerInfo * players, int length, char winner[10]);



using namespace std;

int main()
{
	while(1)	
	{	
		int selected_save;
		system("cls");
		cout << "select one of the following options : \n"

			 << "1 . new game \n"

			 << "2 . load game \n"

			 << "3 . ranking \n"

			 << "4 . exit \n";

		int choice; // gets the player choosen number , used for determining what part to load

		cin >> choice;

		bool new_game = false , load_game = false , ranking = false , exit = false;

		// boolians are used to direct the program to launch the selected part

		switch (choice)
		{
			case 1 : new_game = true; break;

			case 2 : load_game = true; break;

			case 3 : ranking = true; break;

			case 4 : exit = true; break;
		}

		// variables used in new game will be declared here for storage purposes :

		// important note : to prevent maulfunctions , do not declare any output 

		// or input statements between the switch and the ifs which determine what

		// part of the program is launched 

		string player_one_name;

		string player_two_name;

		char player_one_in_char[10];
			
		char player_two_in_char[10];


		int board_size , selected_row , selected_col;

		int player_one_score , player_two_score;

		char board[13][13];

		bool e_flag_for_player_one = false;

		bool e_flag_for_player_two = false;

		bool restart_flag = false;

		bool is_game_over = false;

		int turn = 2; // player one starts the game , 1 for player one and 2 for player 2

		if (new_game == true) // if this if-statement is true , we run the new game part
		{
			while(1) // inputting player one name
			{	
				cout << "\nplease enter player one's name , name should be at most ten characters long : \n";

				getline (cin , player_one_name);

				getline (cin , player_one_name);

				if (player_one_name.length() > 10)
				{
					cout << "\nthe name is too long , try again\n";

					continue;
				}
				else
				{
					break;
				}	
			}	
			while(1) // inputting player two name
			{	
			    cout << " \nplease enter player two's name , name should be at most ten characters long: \n";

				getline (cin , player_two_name);

				if (player_two_name.length() > 10)
				{
					cout << "\nthe name is too long , try again\n";

					continue;
				}
				else
				{
					break;
				}	
			}

			int size_player1 = sizeof(player_one_name);
			
			int size_player2 = sizeof(player_two_name);
			
			for(int i = 0; i < 10; i++)
			{
				player_one_in_char[i] = player_one_name[i];
			}
			for(int i = 0; i < 10; i++)
			{
				player_two_in_char[i] = player_two_name[i];
			}


			cout << " \nplease enter the board size , board size must be an even number between 4 and 12 \n";

			bool flag1 = false;

			while(1) // in this while we input the board size
			{	
				// flag1 is used to determine if this is the first time that we are getting an input , if flag is false 

				// this is the first time that we are getting input , if the flag is true , we have already taken a wrong input and should

				// display an option for returning to main menu

				if (flag1 == true)
				{
					cout << "\nif you want to return to main menue , enter 1 , if you want to try another number for board size enter any other number \n";

					int choice;

					cin >> choice;

					if (choice == 1)
					{
						restart_flag = true;
					}
					else
					{	
						cout << "\nenter the board size : \n";
					}	
				}

				if (restart_flag == true) // if restart flag is true we need to restart the program , first break the input while # 
				{
					break;
				}

				cin >> board_size;

				if (board_size % 2 == 0 && board_size >= 4 && board_size <= 12)
				{
					break;
				}
				else
				{	
					flag1 = true;

					cout << "\nunacceptable value for board size , board size must be an even number between 4 and 12 \n ";
				}	
			}
			
			if (restart_flag == true) // after breaking the input while , we now state continue , which will guide the program to re launch #
			{
				continue;
			}

			// at this point in the program we have a correct board size and the player names 

			// determining and filling the center squares :

			for (int i = 0; i < 13; i++) // first fill all squares with null
			{
				for (int j = 0; j < 13; j++)
				{
					board[i][j] = '-';
				}
			}

			// now fill the center squares

			board[board_size/2 - 1][board_size/2 -1] ='X'; board[board_size/2 - 1][board_size/2] ='O';

			board[board_size/2][board_size/2 - 1] ='O'; board[board_size/2][board_size/2] ='X';

			// main game starts here :

			// by default , the first selected square is always board[board_size/2][board_size/2]

			selected_row = board_size/2;

			selected_col = board_size/2;

			ifstream InGameFile("save.txt" , ios:: in);
			
			int length_of_saves;
			
			InGameFile >> length_of_saves;
			
			length_of_saves ++ ;                                 // make length of saves + 1
			
			GameInfo * games = new GameInfo [length_of_saves];
			
			games[length_of_saves - 1].board_size = board_size;
			
			games[length_of_saves - 1].selected_row = selected_row;
			
			games[length_of_saves - 1].selected_col = selected_col;
			
			games[length_of_saves - 1].player_one_score = 2;
			
			games[length_of_saves - 1].player_two_score = 2;     // this section saves the game at the end of new game
			
			games[length_of_saves - 1].turn = turn;
			
			for(int i = 0; i < 10; i++)
			{
				games[length_of_saves - 1].player_one_name[i] = player_one_name[i];
			
				games[length_of_saves - 1].player_two_name[i] = player_two_name[i];
			}
			for(int i = 0; i < 13; i++)
			{
       			for(int j = 0; j < 13; j++)
       			{
           			games[length_of_saves - 1].board[i][j] = board[i][j];
        		}
        	}
			
			InGameFile.close();
			
			put_info_of_saves(games, length_of_saves - 1);    // length - 1 because we already put info on length
			
			write_new_saves(games, length_of_saves);
			
			selected_save = length_of_saves;

			while(1) // this while runs the main game and should be broken when the game ends
			{
				cout << endl;

				if (can_player_one_move(board , board_size) == false && can_player_two_move(board , board_size) == false) // this means the game is over , break the while
				{
					is_game_over = true;

					new_game = false;

				}

				if (can_player_one_move(board , board_size) == false && can_player_two_move(board , board_size) == true)
				{
					turn = 2;
				}

				if (can_player_two_move(board , board_size) == false && can_player_one_move(board , board_size) == true)
				{
					turn = 1;
				}

				if (turn == 1 && can_player_one_move(board , board_size) == true)
				{
					char choice;

					bool enter_flag_1 = false;

					while(enter_flag_1 == false)		
					{	

						while(enter_flag_1 == false)
						{	 

							system("cls");

							score_board(player_one_in_char, player_two_in_char, board , board_size , turn);

							draw_the_table(board_size, selected_col, selected_row, board);

							draw_touturial();

							cout << endl;

							choice = getch();

							switch(choice)
							{
								case 'w' : if(selected_row > 0) selected_row--; break;

								case 's' : if(selected_row < board_size-1)selected_row++; break;

								case 'a' : if(selected_col > 0)selected_col--; break;

								case 'd' : if(selected_col < board_size-1)selected_col++; break;

								case 13 : enter_flag_1 = true;  break;

								case 'e' : e_flag_for_player_one = true; break;

								case 'v' :
									player_one_score = calculate_player_one_score(board, board_size);
									
									player_two_score = calculate_player_two_score(board, board_size); 
									
									change_save_info(games, board, player_one_score, player_two_score, selected_save, turn);
									
									write_new_saves(games, length_of_saves);
									
									break;
							}
							if (e_flag_for_player_one == true)
							{
								break;
							}

						}

						if (e_flag_for_player_one == true)
						{
							break;
						}		
					
						if (board[selected_row][selected_col] == '-' && is_player_one_move_legal(board , board_size , selected_row , selected_col) == true) // an empty square has been chosen , put down the thing and check for flips
						{
							player_one_flip(board ,board_size ,selected_row ,selected_col);

							turn = 2;
								
						}
						else // if the selected square is not empty or if the move is illegal , act as if enter was not pressed and continue to get input
						{
							enter_flag_1 = false;

							continue;
						}	
					}

					if (e_flag_for_player_one == true)
					{
						break;
					}	
				}
				else if(can_player_two_move(board , board_size) == true) // if we enter this else block , this means its now player two's turn
				{
					char choice;

					bool enter_flag_2 = false;

					while(enter_flag_2 == false)		
					{		
						while(enter_flag_2 == false)
						{	
							system("cls");

							score_board(player_one_in_char, player_two_in_char, board , board_size , turn);

							draw_the_table(board_size, selected_col, selected_row, board);

							draw_touturial();

							choice = getch();

							switch(choice)
							{
								case 'w' : if(selected_row > 0) selected_row--; break;

								case 's' : if(selected_row < board_size-1) selected_row++; break;

								case 'a' : if(selected_col > 0) selected_col--; break;

								case 'd' : if(selected_col < board_size-1) selected_col++; break;

								case 13 : enter_flag_2 = true; break;

								case 'e' : e_flag_for_player_two = true; break;

								case 'v' : 
									player_one_score = calculate_player_one_score(board, board_size);
									
									player_two_score = calculate_player_two_score(board, board_size);
									
									change_save_info(games, board, player_one_score, player_two_score, selected_save, turn);
									
									write_new_saves(games, length_of_saves);
									
									cout << games[selected_save - 1].player_one_score << "********************";
									
									break;
							}
							if (e_flag_for_player_two == true)
							{
								break;
							}

						}

						if (e_flag_for_player_two == true)
						{
							break;
						}	

						if (board[selected_row][selected_col] == '-' && is_player_two_move_legal(board , board_size , selected_row , selected_col) == true) // an empty square has been chosen , put down the thing and check for flips
						{					
							player_two_flip (board , board_size , selected_row , selected_col);

							turn = 1;	
									
						}
						else // if the selected square is not empty or if move isnt legal , act as if enter was not pressed and continue to get input
						{
							enter_flag_2 = false;

							continue;
						}
					}
					if (e_flag_for_player_two == true)
					{
						break;
					}	
				}

				if (is_game_over == true)
				{
					system("cls");

					score_board(player_one_in_char, player_two_in_char, board , board_size , turn);

					draw_the_table(board_size, selected_col, selected_row, board);

					player_one_score = calculate_player_one_score(board , board_size);

					player_two_score = calculate_player_two_score(board , board_size);

					cout << "\n" << player_one_name << " score = " << player_one_score << endl;

					cout << "\n" << player_two_name << " score = " << player_two_score << endl;

					cout << endl;

					int length_of_leader_board_in_end_game;
					
					length_of_leader_board_in_end_game = get_players_num_in_leader_board();
					
					PlayerInfo * players_for_end_game_option = new PlayerInfo [length_of_leader_board_in_end_game + 1];
					
					put_players_in_array(players_for_end_game_option, length_of_leader_board_in_end_game);

					if (player_one_score > player_two_score)
					{
						cout << player_one_name << " wins!";
						
						change_scores_in_leader_board(players_for_end_game_option, length_of_leader_board_in_end_game, player_one_in_char);
					}
					else if (player_one_score == player_two_score)
					{
						cout << "draw!";
					}
					else if (player_one_score < player_two_score)
					{
						cout << player_two_name << " wins!" ;
						change_scores_in_leader_board(players_for_end_game_option, length_of_leader_board_in_end_game, player_two_in_char);
						
					}

					cout << endl << " press any key to exit to main menu";
					char b;                                                       // this code equals to press any key to exit to main menu
					
					b = getch();
					
					break;
				}

			}

			if (e_flag_for_player_two == true)
			{
				e_flag_for_player_two = false;

				system ("cls");

				continue;
			}

			if (e_flag_for_player_one == true)
			{
				e_flag_for_player_one = false;

				system ("cls");

				continue;
			}	
		}

		
		
	
		if (load_game == true) // if this if-statement is true , we run the load game part
		{
			ifstream InGameFile("save.txt" , ios:: in);
			
			int length_of_saves;
			
			GameInfo * games = new GameInfo [length_of_saves];
			
			InGameFile >> length_of_saves;
			
			InGameFile.close();
			
			put_info_of_saves(games, length_of_saves);
			
			selected_save = return_save_option_in_load(games, length_of_saves);         // remember it retruns current room + 1
			
			if(selected_save != 0)
			{                                                     // if a save was chosen game will start
				string player_one_name;
			
				string player_two_name;
			
				char player_one_in_char[10];
			
				char player_two_in_char[10];
			
				for(int i = 0; i < 10; i ++)
				{
					 player_one_in_char[i] = games[selected_save - 1].player_one_name[i];
			
					 player_two_in_char[i] = games[selected_save - 1].player_two_name[i];
				}
				player_one_name = player_one_in_char;
				
				player_two_name = player_two_in_char;
				
				int size_player1 = sizeof(player_one_name);
				
				int size_player2 = sizeof(player_two_name);
				
				int board_size =  games[selected_save - 1].board_size;
				
				int selected_row  = games[selected_save - 1].selected_row;
				
				int selected_col = games[selected_save - 1].selected_col;
				
				int player_one_score = games[selected_save - 1].player_one_score;
				
				int player_two_score = games[selected_save - 1].player_two_score;
				
				char board[13][13];
				
				for(int i = 0; i < 13; i ++)
				{
					for(int j = 0; j < 13; j ++)
					{
						board[i][j] = games[selected_save - 1].board[i][j];
					}
				}

				bool e_flag_for_player_one = false;

				bool e_flag_for_player_two = false;

				bool restart_flag = false;

				bool is_game_over = false;

				int turn = games[selected_save - 1].turn; // player one starts the game , 1 for player one and 2 for player 2
				
			

			while(1) // this while runs the main game and should be broken when the game ends
			{
				cout << endl;

				if (can_player_one_move(board , board_size) == false && can_player_two_move(board , board_size) == false) // this means the game is over , break the while
				{
					is_game_over = true;

					load_game = false;
				}

				if (can_player_one_move(board , board_size) == false && can_player_two_move(board , board_size) == true)
				{
					turn = 2;
				}

				if (can_player_two_move(board , board_size) == false && can_player_one_move(board , board_size) == true)
				{
					turn = 1;
				}

				if (turn == 1 && can_player_one_move(board , board_size) == true)
				{
					char choice;

					bool enter_flag_1 = false;

					while(enter_flag_1 == false)		
					{	

						while(enter_flag_1 == false)
						{	 

							system("cls");

							score_board(player_one_in_char, player_two_in_char, board , board_size , turn);

							draw_the_table(board_size, selected_col, selected_row, board);

							draw_touturial();

							cout << endl;

							choice = getch();

							switch(choice)
							{
								case 'w' : if(selected_row > 0) selected_row--; break;

								case 's' : if(selected_row < board_size-1)selected_row++; break;

								case 'a' : if(selected_col > 0)selected_col--; break;

								case 'd' : if(selected_col < board_size-1)selected_col++; break;

								case 13 : enter_flag_1 = true;  break;

								case 'e' : e_flag_for_player_one = true; break;

								case 'v' : 
									player_one_score = calculate_player_one_score(board, board_size);
									
									player_two_score = calculate_player_two_score(board, board_size);
									
									change_save_info(games, board, player_one_score, player_two_score, selected_save, turn);
									
									write_new_saves(games, length_of_saves);
									
									break;
							}
							if (e_flag_for_player_one == true)
							{
								break;
							}

						}

						if (e_flag_for_player_one == true)
						{
							break;
						}		
					
						if (board[selected_row][selected_col] == '-' && is_player_one_move_legal(board , board_size , selected_row , selected_col) == true) // an empty square has been chosen , put down the thing and check for flips
						{
							player_one_flip(board ,board_size ,selected_row ,selected_col);
							
							player_one_score = calculate_player_one_score(board , board_size);

							turn = 2;
								
						}
						else // if the selected square is not empty or if the move is illegal , act as if enter was not pressed and continue to get input
						{
							enter_flag_1 = false;

							continue;
						}	
					}

					if (e_flag_for_player_one == true)
					{
						break;
					}	
				}
				else if(can_player_two_move(board , board_size) == true) // if we enter this else block , this means its now player two's turn
				{
					char choice;

					bool enter_flag_2 = false;

					while(enter_flag_2 == false)		
					{		
						while(enter_flag_2 == false)
						{	
							system("cls");

							score_board(player_one_in_char, player_two_in_char, board , board_size , turn);

							draw_the_table(board_size, selected_col, selected_row, board);

							draw_touturial();

							choice = getch();

							switch(choice)
							{
								case 'w' : if(selected_row > 0) selected_row--; break;

								case 's' : if(selected_row < board_size-1) selected_row++; break;

								case 'a' : if(selected_col > 0) selected_col--; break;

								case 'd' : if(selected_col < board_size-1) selected_col++; break;

								case 13 : enter_flag_2 = true; break;

								case 'e' : e_flag_for_player_two = true; break;

								case 'v' :
									player_one_score = calculate_player_one_score(board, board_size);
									
									player_two_score = calculate_player_two_score(board, board_size); 
									
									change_save_info(games, board, player_one_score, player_two_score, selected_save, turn);
									
									write_new_saves(games, length_of_saves);
									
									cout << games[selected_save - 1].player_one_score << "********************";
									
									break;
							}
							if (e_flag_for_player_two == true)
							{
								break;
							}

						}

						if (e_flag_for_player_two == true)
						{
							break;
						}	

						if (board[selected_row][selected_col] == '-' && is_player_two_move_legal(board , board_size , selected_row , selected_col) == true) // an empty square has been chosen , put down the thing and check for flips
						{					
							player_two_flip (board , board_size , selected_row , selected_col);

							player_two_score = calculate_player_two_score(board , board_size);

							turn = 1;	
									
						}
						else // if the selected square is not empty or if move isnt legal , act as if enter was not pressed and continue to get input
						{
							enter_flag_2 = false;

							continue;
						}
					}
					if (e_flag_for_player_two == true)
					{
						break;
					}	
				}	

				if (is_game_over == true)
				{
					system("cls");

					score_board(player_one_in_char, player_two_in_char, board , board_size , turn);

					draw_the_table(board_size, selected_col, selected_row, board);

					player_one_score = calculate_player_one_score(board , board_size);

					player_two_score = calculate_player_two_score(board , board_size);

					cout << "\n" << player_one_name << " score = " << player_one_score << endl;

					cout << "\n" << player_two_name << " score = " << player_two_score << endl;

					cout << endl;

					int length_of_leader_board_in_end_game;
					
					length_of_leader_board_in_end_game = get_players_num_in_leader_board();
					
					PlayerInfo * players_for_end_game_option = new PlayerInfo [length_of_leader_board_in_end_game + 1];
					
					put_players_in_array(players_for_end_game_option, length_of_leader_board_in_end_game);

					if (player_one_score > player_two_score)
					{
						cout << player_one_name << " wins!";
						
						change_scores_in_leader_board(players_for_end_game_option, length_of_leader_board_in_end_game, player_one_in_char);
						
					}
					else if (player_one_score == player_two_score)
					{
						cout << "draw!";
					}
					else if (player_one_score < player_two_score)
					{
						cout << player_two_name << " wins!" ;
						
						change_scores_in_leader_board(players_for_end_game_option, length_of_leader_board_in_end_game, player_two_in_char);
						
					}

					cout << endl << "press any key to exit to main menu";
					
					char a;
					
					a = getch();                                                        // this code equals to press any key to exit to main menu
					
					break;
				}
			}

			if (e_flag_for_player_two == true)
			{
				e_flag_for_player_two = false;

				system ("cls");

				continue;
			}

			if (e_flag_for_player_one == true)
			{
				e_flag_for_player_one = false;

				system ("cls");

				continue;
			}
		}

		}

		if (ranking == true) // if this if-statement is true , we run the ranking part
		{
			system("cls");
			
			ifstream InLeaderFile("leader_board.txt", ios:: in);
			
			int length;
			
			InLeaderFile >> length;
			
			PlayerInfo * players_for_rank_option = new PlayerInfo [length];
			
			InLeaderFile.close();
			
			put_players_in_array(players_for_rank_option, length);
			
			for(int i = 0 ; i < length; i ++)
			{
				cout << players_for_rank_option[i].player_name <<" "<< players_for_rank_option[i].player_score << endl;
			}
			cout << endl <<"press E for exit";
			while(1)
			{
				char choice;
			
				choice = getch();
			
				if(choice == 'e')
				{
					break;
				}
			}
		}

		if (exit == true) // // if this if-statement is true , we close the program
		{
			return 0;
		}

	}	

	return 0;
}

int calculate_player_two_score (char board[13][13] , int board_size)
{
	int ans = 0;

	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			if (board[i][j] == 'O')
			{
				ans++;
			}
		}	
	}

	return ans;
}

int calculate_player_one_score (char board[13][13] , int board_size)
{
	int ans = 0;

	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			if (board[i][j] == 'X')
			{
				ans++;
			}
		}
	}

	return ans;
}

void player_two_flip(char board[13][13] , int board_size , int selected_row , int selected_col)
{
	board[selected_row][selected_col] = 'O';

	int temp_selected_row = selected_row;

	int temp_selected_col = selected_col;

	if (board[temp_selected_row+1][temp_selected_col] == 'X') //**************checking upper direction for flips**************
	{
		while(board[temp_selected_row+1][temp_selected_col] == 'X')
		{
			temp_selected_row++;
		}
		if (board[temp_selected_row+1][temp_selected_col] == 'O') // if we enter this if-block , we should flip upward
		{

			for (int i = selected_row; i <= temp_selected_row; i++)
			{
				board[i][temp_selected_col] = 'O';
			}
		}	
	}

	temp_selected_row = selected_row;

	temp_selected_col = selected_col;

	if (board[temp_selected_row-1][temp_selected_col] == 'X') //**************checking lower direction for flips**************
	{
		while(board[temp_selected_row-1][temp_selected_col] == 'X')
		{
			temp_selected_row--;
		}
		if (board[temp_selected_row-1][temp_selected_col] == 'O') // if we enter this if-block , we should flip downward
		{

			for (int i = selected_row; i >= temp_selected_row; i--)
			{
				board[i][temp_selected_col] = 'O';
			}
		}	
	}

	temp_selected_row = selected_row;

	temp_selected_col = selected_col;

	if (board[temp_selected_row][temp_selected_col+1] == 'X') //**************checking right direction for flips**************
	{
		while(board[temp_selected_row][temp_selected_col+1] == 'X')
		{
			temp_selected_col++;
		}
		if (board[temp_selected_row][temp_selected_col+1] == 'O') // if we enter this if-block , we should flip rightward
		{

			for (int j = selected_col; j <= temp_selected_col; j++)
			{
				board[temp_selected_row][j] = 'O';
			}
		}	
	}

	temp_selected_row = selected_row;

	temp_selected_col = selected_col;

	if (board[temp_selected_row][temp_selected_col-1] == 'X') //**************checking left direction for flips**************
	{
		while(board[temp_selected_row][temp_selected_col-1] == 'X')
		{
			temp_selected_col--;
		}
		if (board[temp_selected_row][temp_selected_col-1] == 'O') // if we enter this if-block , we should flip rightward
		{

			for (int j = selected_col; j >= temp_selected_col; j--)
			{
				board[temp_selected_row][j] = 'O';
			}
		}	
	}

	temp_selected_row = selected_row;

	int temp_selected_row_2 = selected_row;

	temp_selected_col = selected_col;

	int temp_selected_col_2 = selected_col;

	if (board[temp_selected_row-1][temp_selected_col+1] == 'X') //**************checking diagonal right-up for flips**************
	{
		while(board[temp_selected_row-1][temp_selected_col+1] == 'X')
		{
			temp_selected_row--;

			temp_selected_col++;
		}
		if (board[temp_selected_row-1][temp_selected_col+1] == 'O') // if we enter this if-block , we should flip diagonal right-up
		{

			for (int i = selected_row; i >= temp_selected_row; i--)
			{
				board[i][temp_selected_col_2] = 'O';

				temp_selected_col_2++;
			}
		}	
	}

	temp_selected_row = selected_row;

	temp_selected_row_2 = selected_row;

	temp_selected_col = selected_col;

	temp_selected_col_2 = selected_col;

	if (board[temp_selected_row+1][temp_selected_col+1] == 'X') //**************checking diagonal right-down for flips**************
	{
		while(board[temp_selected_row+1][temp_selected_col+1] == 'X')
		{
			temp_selected_row++;

			temp_selected_col++;
		}
		if (board[temp_selected_row+1][temp_selected_col+1] == 'O') // if we enter this if-block , we should flip diagonal right-down
		{
			for (int i = selected_row; i <= temp_selected_row; i++)
			{
				board[i][temp_selected_col_2] = 'O';

				temp_selected_col_2++;
			}
		}	
	}

	temp_selected_row = selected_row;

	temp_selected_row_2 = selected_row;

	temp_selected_col = selected_col;

	temp_selected_col_2 = selected_col;

	if (board[temp_selected_row-1][temp_selected_col-1] == 'X') //**************checking diagonal left-up for flips**************
	{
		while(board[temp_selected_row-1][temp_selected_col-1] == 'X')
		{
			temp_selected_row--;

			temp_selected_col--;
		}
		if (board[temp_selected_row-1][temp_selected_col-1] == 'O') // if we enter this if-block , we should flip diagonal left-up
		{								

			for (int i = selected_row; i >= temp_selected_row; i--)
			{
				board[i][temp_selected_col_2] = 'O';

				temp_selected_col_2--;
			}
		}	
	}

	temp_selected_row = selected_row;

	temp_selected_row_2 = selected_row;

	temp_selected_col = selected_col;

	temp_selected_col_2 = selected_col;

	if (board[temp_selected_row+1][temp_selected_col-1] == 'X') //**************checking diagonal left-down for flips**************
	{
		while(board[temp_selected_row+1][temp_selected_col-1] == 'X')
		{
			temp_selected_row++;

			temp_selected_col--;
		}
		if (board[temp_selected_row+1][temp_selected_col-1] == 'O') // if we enter this if-block , we should flip diagonal left-down
		{

			for (int i = selected_row; i <= temp_selected_row; i++)
			{
				board[i][temp_selected_col_2] = 'O';

				temp_selected_col_2--;
			}
		}
	}

}

void player_one_flip(char board[13][13] , int board_size , int selected_row , int selected_col)
{
	board[selected_row][selected_col] = 'X';

	int temp_selected_row = selected_row;

	int temp_selected_col = selected_col;

	if (board[temp_selected_row+1][temp_selected_col] == 'O') //**************checking upper direction for flips**************
	{
		while(board[temp_selected_row+1][temp_selected_col] == 'O')
		{
			temp_selected_row++;
		}
		if (board[temp_selected_row+1][temp_selected_col] == 'X') // if we enter this if-block , we should flip upward
		{

			for (int i = selected_row; i <= temp_selected_row; i++)
			{
				board[i][temp_selected_col] = 'X';
			}
		}	
	}

	temp_selected_row = selected_row;

	temp_selected_col = selected_col;

	if (board[temp_selected_row-1][temp_selected_col] == 'O') //**************checking lower direction for flips**************
	{
		while(board[temp_selected_row-1][temp_selected_col] == 'O')
		{
			temp_selected_row--;
		}
		if (board[temp_selected_row-1][temp_selected_col] == 'X') // if we enter this if-block , we should flip downward
		{

			for (int i = selected_row; i >= temp_selected_row; i--)
			{
				board[i][temp_selected_col] = 'X';
			}
		}	
	}

	temp_selected_row = selected_row;

	temp_selected_col = selected_col;

	if (board[temp_selected_row][temp_selected_col+1] == 'O') //**************checking right direction for flips**************
	{
		while(board[temp_selected_row][temp_selected_col+1] == 'O')
		{
			temp_selected_col++;
		}
		if (board[temp_selected_row][temp_selected_col+1] == 'X') // if we enter this if-block , we should flip rightward
		{

			for (int j = selected_col; j <= temp_selected_col; j++)
			{
				board[temp_selected_row][j] = 'X';
			}
		}	
	}

	temp_selected_row = selected_row;

	temp_selected_col = selected_col;

	if (board[temp_selected_row][temp_selected_col-1] == 'O') //**************checking left direction for flips**************
	{
		while(board[temp_selected_row][temp_selected_col-1] == 'O')
		{
			temp_selected_col--;
		}
		if (board[temp_selected_row][temp_selected_col-1] == 'X') // if we enter this if-block , we should flip rightward
		{

			for (int j = selected_col; j >= temp_selected_col; j--)
			{
				board[temp_selected_row][j] = 'X';
			}
		}	
	}

	temp_selected_row = selected_row;

	int temp_selected_row_2 = selected_row;

	temp_selected_col = selected_col;

	int temp_selected_col_2 = selected_col;

	if (board[temp_selected_row-1][temp_selected_col+1] == 'O') //**************checking diagonal right-up for flips**************
	{
		while(board[temp_selected_row-1][temp_selected_col+1] == 'O')
		{
			temp_selected_row--;

			temp_selected_col++;
		}
		if (board[temp_selected_row-1][temp_selected_col+1] == 'X') // if we enter this if-block , we should flip diagonal right-up
		{

			for (int i = selected_row; i >= temp_selected_row; i--)
			{
				board[i][temp_selected_col_2] = 'X';

				temp_selected_col_2++;
			}
		}	
	}

	temp_selected_row = selected_row;

	temp_selected_row_2 = selected_row;

	temp_selected_col = selected_col;

	temp_selected_col_2 = selected_col;

	if (board[temp_selected_row+1][temp_selected_col+1] == 'O') //**************checking diagonal right-down for flips**************
	{
		while(board[temp_selected_row+1][temp_selected_col+1] == 'O')
		{
			temp_selected_row++;

			temp_selected_col++;
		}
		if (board[temp_selected_row+1][temp_selected_col+1] == 'X') // if we enter this if-block , we should flip diagonal right-down
		{

			for (int i = selected_row; i <= temp_selected_row; i++)
			{
				board[i][temp_selected_col_2] = 'X';

				temp_selected_col_2++;
			}
		}	
	}

	temp_selected_row = selected_row;

	temp_selected_row_2 = selected_row;

	temp_selected_col = selected_col;

	temp_selected_col_2 = selected_col;

	if (board[temp_selected_row-1][temp_selected_col-1] == 'O') //**************checking diagonal left-up for flips**************
	{
		while(board[temp_selected_row-1][temp_selected_col-1] == 'O')
		{
			temp_selected_row--;

			temp_selected_col--;
		}
		if (board[temp_selected_row-1][temp_selected_col-1] == 'X') // if we enter this if-block , we should flip diagonal left-up
		{

			for (int i = selected_row; i >= temp_selected_row; i--)
			{
				board[i][temp_selected_col_2] = 'X';

				temp_selected_col_2--;
			}
		}	
	}

	temp_selected_row = selected_row;

	temp_selected_row_2 = selected_row;

	temp_selected_col = selected_col;

	temp_selected_col_2 = selected_col;

	if (board[temp_selected_row+1][temp_selected_col-1] == 'O') //**************checking diagonal left-down for flips**************
	{
		while(board[temp_selected_row+1][temp_selected_col-1] == 'O')
		{
			temp_selected_row++;

			temp_selected_col--;
		}
		if (board[temp_selected_row+1][temp_selected_col-1] == 'X') // if we enter this if-block , we should flip diagonal left-down
		{

			for (int i = selected_row; i <= temp_selected_row; i++)
			{
				board[i][temp_selected_col_2] = 'X';

				temp_selected_col_2--;
			}
		}	
	}

}


bool can_player_one_move (char board[13][13] , int board_size)
{
	char temp_board[13][13];

	for (int i = 0; i < board_size; i++) // copying the board in a temp board / cleaning the temp board
	{
		for (int j = 0; j < board_size; j++)
		{
			temp_board[i][j] = board[i][j];
		}
	}

	bool is_this_move_legal = false;

	int temp_selected_row , temp_selected_col;

	int temp_selected_row_2 , temp_selected_col_2;

	for (int selected_row = 0; selected_row < board_size; selected_row++)
	{
		for (int i = 0; i < board_size; i++) // copying the board in a temp board / cleaning the temp board
		{
			for (int j = 0; j < board_size; j++)
			{
				temp_board[i][j] = board[i][j];
			}
		}

		for (int selected_col = 0; selected_col < board_size; selected_col++)
		{
			for (int i = 0; i < board_size; i++) // copying the board in a temp board / cleaning the temp board
			{
				for (int j = 0; j < board_size; j++)
				{
					temp_board[i][j] = board[i][j];
				}
			}


			if (temp_board[selected_row][selected_col] == '-') // if the square is empty , we might have a legal move here
			{
				is_this_move_legal = false;						

				temp_board[selected_row][selected_col] == 'X';

				temp_selected_row = selected_row;

				temp_selected_col = selected_col;

				if (temp_board[temp_selected_row+1][temp_selected_col] == 'O') //**************checking upper direction for flips**************
				{
					while(temp_board[temp_selected_row+1][temp_selected_col] == 'O')
					{
						temp_selected_row++;
					}
					if (temp_board[temp_selected_row+1][temp_selected_col] == 'X') 
					{
						is_this_move_legal = true;

						return is_this_move_legal;
					}	
				}

				temp_selected_row = selected_row;

				temp_selected_col = selected_col;

				if (temp_board[temp_selected_row-1][temp_selected_col] == 'O') //**************checking lower direction for flips**************
				{
					while(temp_board[temp_selected_row-1][temp_selected_col] == 'O')
					{
						temp_selected_row--;
					}
					if (temp_board[temp_selected_row-1][temp_selected_col] == 'X') 
					{
						is_this_move_legal = true;

						return is_this_move_legal;
					}	
				}

				temp_selected_row = selected_row;

				temp_selected_col = selected_col;

				if (temp_board[temp_selected_row][temp_selected_col+1] == 'O') //**************checking right direction for flips**************
				{
					while(temp_board[temp_selected_row][temp_selected_col+1] == 'O')
					{
						temp_selected_col++;
					}
					if (temp_board[temp_selected_row][temp_selected_col+1] == 'X') 
					{
						is_this_move_legal = true;

						return is_this_move_legal;
					}	
				}

				temp_selected_row = selected_row;

				temp_selected_col = selected_col;

				if (temp_board[temp_selected_row][temp_selected_col-1] == 'O') //**************checking left direction for flips**************
				{
					while(temp_board[temp_selected_row][temp_selected_col-1] == 'O')
					{
						temp_selected_col--;
					}
					if (temp_board[temp_selected_row][temp_selected_col-1] == 'X') 
					{
						is_this_move_legal = true;

						return is_this_move_legal;
					}	
				}

				temp_selected_row = selected_row;

				temp_selected_row_2 = selected_row;

				temp_selected_col = selected_col;

				temp_selected_col_2 = selected_col;

				if (temp_board[temp_selected_row-1][temp_selected_col+1] == 'O') //**************checking diagonal right-up for flips**************
				{
					while(temp_board[temp_selected_row-1][temp_selected_col+1] == 'O')
					{
						temp_selected_row--;

						temp_selected_col++;
					}
					if (temp_board[temp_selected_row-1][temp_selected_col+1] == 'X') 
					{
						is_this_move_legal = true;

						return is_this_move_legal;
					}	
				}

				temp_selected_row = selected_row;

				temp_selected_row_2 = selected_row;

				temp_selected_col = selected_col;

				temp_selected_col_2 = selected_col;

				if (temp_board[temp_selected_row+1][temp_selected_col+1] == 'O') //**************checking diagonal right-down for flips**************
				{
					while(temp_board[temp_selected_row+1][temp_selected_col+1] == 'O')
					{
						temp_selected_row++;

						temp_selected_col++;
					}
					if (temp_board[temp_selected_row+1][temp_selected_col+1] == 'X') 
					{
						is_this_move_legal = true;

						return is_this_move_legal;
					}	
				}

				temp_selected_row = selected_row;

				temp_selected_row_2 = selected_row;

				temp_selected_col = selected_col;

				temp_selected_col_2 = selected_col;

				if (temp_board[temp_selected_row-1][temp_selected_col-1] == 'O') //**************checking diagonal left-up for flips**************
				{
					while(temp_board[temp_selected_row-1][temp_selected_col-1] == 'O')
					{
						temp_selected_row--;

						temp_selected_col--;
					}
					if (temp_board[temp_selected_row-1][temp_selected_col-1] == 'X') 
					{
						is_this_move_legal = true;	

						return is_this_move_legal;								
					}	
				}

				temp_selected_row = selected_row;

				temp_selected_row_2 = selected_row;

				temp_selected_col = selected_col;

				temp_selected_col_2 = selected_col;

				if (temp_board[temp_selected_row+1][temp_selected_col-1] == 'O') //**************checking diagonal left-down for flips**************
				{
					while(temp_board[temp_selected_row+1][temp_selected_col-1] == 'O')
					{
						temp_selected_row++;

						temp_selected_col--;
					}
					if (temp_board[temp_selected_row+1][temp_selected_col-1] == 'X') 
					{
						is_this_move_legal = true;

						return is_this_move_legal;

					}
				}

			}
		}
	}

	return is_this_move_legal;

}



bool can_player_two_move (char board[13][13] , int board_size)
{
	char temp_board[13][13];

	for (int i = 0; i < board_size; i++) // copying the board in a temp board
	{
		for (int j = 0; j < board_size; j++)
		{
			temp_board[i][j] = board[i][j];
		}
	}

	bool is_this_move_legal = false;

	int temp_selected_row , temp_selected_col;

	int temp_selected_row_2 , temp_selected_col_2;

	for (int selected_row = 0; selected_row < board_size; selected_row++)
	{
		for (int i = 0; i < board_size; i++) // copying the board in a temp board / cleaning the temp board
		{
			for (int j = 0; j < board_size; j++)
			{
				temp_board[i][j] = board[i][j];
			}	
		}

		for (int selected_col = 0; selected_col < board_size; selected_col++)
		{
			for (int i = 0; i < board_size; i++) // copying the board in a temp board / cleaning the temp board
			{
				for (int j = 0; j < board_size; j++)
				{
					temp_board[i][j] = board[i][j];
				}
			}

			if (temp_board[selected_row][selected_col] == '-') // if the square is empty , we might have a legal move here
			{
				is_this_move_legal = false;						

				temp_board[selected_row][selected_col] == 'O';

				temp_selected_row = selected_row;

				temp_selected_col = selected_col;

				if (temp_board[temp_selected_row+1][temp_selected_col] == 'X') //**************checking upper direction for flips**************
				{
					while(temp_board[temp_selected_row+1][temp_selected_col] == 'X')
					{
						temp_selected_row++;
					}
					if (temp_board[temp_selected_row+1][temp_selected_col] == 'O') 
					{
						is_this_move_legal = true;

						return is_this_move_legal;
					}	
				}

				temp_selected_row = selected_row;

				temp_selected_col = selected_col;

				if (temp_board[temp_selected_row-1][temp_selected_col] == 'X') //**************checking lower direction for flips**************
				{
					while(temp_board[temp_selected_row-1][temp_selected_col] == 'X')
					{
						temp_selected_row--;
					}
					if (temp_board[temp_selected_row-1][temp_selected_col] == 'O') 
					{
						is_this_move_legal = true;

						return is_this_move_legal;
					}	
				}

				temp_selected_row = selected_row;

				temp_selected_col = selected_col;

				if (temp_board[temp_selected_row][temp_selected_col+1] == 'X') //**************checking right direction for flips**************
				{
					while(temp_board[temp_selected_row][temp_selected_col+1] == 'X')
					{
						temp_selected_col++;
					}
					if (temp_board[temp_selected_row][temp_selected_col+1] == 'O') 
					{
						is_this_move_legal = true;

						return is_this_move_legal;
					}	
				}

				temp_selected_row = selected_row;

				temp_selected_col = selected_col;

				if (temp_board[temp_selected_row][temp_selected_col-1] == 'X') //**************checking left direction for flips**************
				{
					while(temp_board[temp_selected_row][temp_selected_col-1] == 'X')
					{
						temp_selected_col--;
					}
					if (temp_board[temp_selected_row][temp_selected_col-1] == 'O') 
					{
						is_this_move_legal = true;

						return is_this_move_legal;
					}	
				}

				temp_selected_row = selected_row;

				temp_selected_row_2 = selected_row;

				temp_selected_col = selected_col;

				temp_selected_col_2 = selected_col;

				if (temp_board[temp_selected_row-1][temp_selected_col+1] == 'X') //**************checking diagonal right-up for flips**************
				{
					while(temp_board[temp_selected_row-1][temp_selected_col+1] == 'X')
					{
						temp_selected_row--;

						temp_selected_col++;
					}
					if (temp_board[temp_selected_row-1][temp_selected_col+1] == 'O') 
					{
						is_this_move_legal = true;

						return is_this_move_legal;
					}	
				}

				temp_selected_row = selected_row;

				temp_selected_row_2 = selected_row;

				temp_selected_col = selected_col;

				temp_selected_col_2 = selected_col;

				if (temp_board[temp_selected_row+1][temp_selected_col+1] == 'X') //**************checking diagonal right-down for flips**************
				{
					while(temp_board[temp_selected_row+1][temp_selected_col+1] == 'X')
					{
						temp_selected_row++;

						temp_selected_col++;
					}
					if (temp_board[temp_selected_row+1][temp_selected_col+1] == 'O') 
					{
						is_this_move_legal = true;

						return is_this_move_legal;
					}	
				}

				temp_selected_row = selected_row;

				temp_selected_row_2 = selected_row;

				temp_selected_col = selected_col;

				temp_selected_col_2 = selected_col;

				if (temp_board[temp_selected_row-1][temp_selected_col-1] == 'X') //**************checking diagonal left-up for flips**************
				{
					while(temp_board[temp_selected_row-1][temp_selected_col-1] == 'X')
					{
						temp_selected_row--;

						temp_selected_col--;
					}
					if (temp_board[temp_selected_row-1][temp_selected_col-1] == 'O') 
					{
						is_this_move_legal = true;	

						return is_this_move_legal;								
					}	
				}

				temp_selected_row = selected_row;

				temp_selected_row_2 = selected_row;

				temp_selected_col = selected_col;

				temp_selected_col_2 = selected_col;

				if (temp_board[temp_selected_row+1][temp_selected_col-1] == 'X') //**************checking diagonal left-down for flips**************
				{
					while(temp_board[temp_selected_row+1][temp_selected_col-1] == 'X')
					{
						temp_selected_row++;

						temp_selected_col--;
					}
					if (temp_board[temp_selected_row+1][temp_selected_col-1] == 'O') 
					{
						is_this_move_legal = true;

						return is_this_move_legal;

					}
				}

			}
		}
	}

	return is_this_move_legal;
}

bool is_player_one_move_legal (char board[13][13] , int board_size , int selected_row , int selected_col)
{
	char temp_board[13][13];

	for (int i = 0; i < board_size; i++) // copying the board in a temp board
	{
		for (int j = 0; j < board_size; j++)
		{
			temp_board[i][j] = board[i][j];
		}
	}

	bool is_this_move_legal = false;

	int temp_selected_row , temp_selected_col;

	int temp_selected_row_2 , temp_selected_col_2;

	if (temp_board[selected_row][selected_col] == '-') // if the square is empty , we might have a legal move here
	{
		is_this_move_legal = false;						

		temp_board[selected_row][selected_col] == 'X';

		temp_selected_row = selected_row;

		temp_selected_col = selected_col;

		if (temp_board[temp_selected_row+1][temp_selected_col] == 'O') //**************checking upper direction for flips**************
		{
			while(temp_board[temp_selected_row+1][temp_selected_col] == 'O')
			{
				temp_selected_row++;
			}
			if (temp_board[temp_selected_row+1][temp_selected_col] == 'X') 
			{
				is_this_move_legal = true;

				return is_this_move_legal;
			}	
		}

		temp_selected_row = selected_row;

		temp_selected_col = selected_col;

		if (temp_board[temp_selected_row-1][temp_selected_col] == 'O') //**************checking lower direction for flips**************
		{
			while(temp_board[temp_selected_row-1][temp_selected_col] == 'O')
			{
				temp_selected_row--;
			}
			if (temp_board[temp_selected_row-1][temp_selected_col] == 'X') 
			{
				is_this_move_legal = true;

				return is_this_move_legal;
			}	
		}

		temp_selected_row = selected_row;

		temp_selected_col = selected_col;

		if (temp_board[temp_selected_row][temp_selected_col+1] == 'O') //**************checking right direction for flips**************
		{
			while(temp_board[temp_selected_row][temp_selected_col+1] == 'O')
			{
				temp_selected_col++;
			}
			if (temp_board[temp_selected_row][temp_selected_col+1] == 'X') 
			{
				is_this_move_legal = true;

				return is_this_move_legal;
			}	
		}

		temp_selected_row = selected_row;

		temp_selected_col = selected_col;

		if (temp_board[temp_selected_row][temp_selected_col-1] == 'O') //**************checking left direction for flips**************
		{
			while(temp_board[temp_selected_row][temp_selected_col-1] == 'O')
			{
				temp_selected_col--;
			}
			if (temp_board[temp_selected_row][temp_selected_col-1] == 'X') 
			{
				is_this_move_legal = true;

				return is_this_move_legal;
			}	
		}

		temp_selected_row = selected_row;

		temp_selected_row_2 = selected_row;

		temp_selected_col = selected_col;

		temp_selected_col_2 = selected_col;

		if (temp_board[temp_selected_row-1][temp_selected_col+1] == 'O') //**************checking diagonal right-up for flips**************
		{
			while(temp_board[temp_selected_row-1][temp_selected_col+1] == 'O')
			{
				temp_selected_row--;

				temp_selected_col++;
			}
			if (temp_board[temp_selected_row-1][temp_selected_col+1] == 'X') 
			{
				is_this_move_legal = true;

				return is_this_move_legal;
			}	
		}

		temp_selected_row = selected_row;

		temp_selected_row_2 = selected_row;

		temp_selected_col = selected_col;

		temp_selected_col_2 = selected_col;

		if (temp_board[temp_selected_row+1][temp_selected_col+1] == 'O') //**************checking diagonal right-down for flips**************
		{
			while(temp_board[temp_selected_row+1][temp_selected_col+1] == 'O')
			{
				temp_selected_row++;

				temp_selected_col++;
			}
			if (temp_board[temp_selected_row+1][temp_selected_col+1] == 'X') 
			{
				is_this_move_legal = true;

				return is_this_move_legal;
			}	
		}

		temp_selected_row = selected_row;

		temp_selected_row_2 = selected_row;

		temp_selected_col = selected_col;

		temp_selected_col_2 = selected_col;

		if (temp_board[temp_selected_row-1][temp_selected_col-1] == 'O') //**************checking diagonal left-up for flips**************
		{
			while(temp_board[temp_selected_row-1][temp_selected_col-1] == 'O')
			{
				temp_selected_row--;

				temp_selected_col--;
			}
			if (temp_board[temp_selected_row-1][temp_selected_col-1] == 'X') 
			{
				is_this_move_legal = true;	

				return is_this_move_legal;								
			}	
		}

		temp_selected_row = selected_row;

		temp_selected_row_2 = selected_row;

		temp_selected_col = selected_col;

		temp_selected_col_2 = selected_col;

		if (temp_board[temp_selected_row+1][temp_selected_col-1] == 'O') //**************checking diagonal left-down for flips**************
		{
			while(temp_board[temp_selected_row+1][temp_selected_col-1] == 'O')
			{
				temp_selected_row++;

				temp_selected_col--;
			}
			if (temp_board[temp_selected_row+1][temp_selected_col-1] == 'X') 
			{
				is_this_move_legal = true;

				return is_this_move_legal;

			}
		}

	}
	
	

	return is_this_move_legal;

}

bool is_player_two_move_legal (char board[13][13] , int board_size , int selected_row , int selected_col)
{
	char temp_board[13][13];

	for (int i = 0; i < board_size; i++) // copying the board in a temp board
	{
		for (int j = 0; j < board_size; j++)
		{
			temp_board[i][j] = board[i][j];
		}
	}

	bool is_this_move_legal = false;

	int temp_selected_row , temp_selected_col;

	int temp_selected_row_2 , temp_selected_col_2;


	if (temp_board[selected_row][selected_col] == '-') // if the square is empty , we might have a legal move here
	{
		is_this_move_legal = false;						

		temp_board[selected_row][selected_col] == 'O';

		temp_selected_row = selected_row;

		temp_selected_col = selected_col;

		if (temp_board[temp_selected_row+1][temp_selected_col] == 'X') //**************checking upper direction for flips**************
		{
			while(temp_board[temp_selected_row+1][temp_selected_col] == 'X')
			{
				temp_selected_row++;
			}
			if (temp_board[temp_selected_row+1][temp_selected_col] == 'O') 
			{
				is_this_move_legal = true;

				return is_this_move_legal;
			}	
		}

		temp_selected_row = selected_row;

		temp_selected_col = selected_col;

		if (temp_board[temp_selected_row-1][temp_selected_col] == 'X') //**************checking lower direction for flips**************
		{
			while(temp_board[temp_selected_row-1][temp_selected_col] == 'X')
			{
				temp_selected_row--;
			}
			if (temp_board[temp_selected_row-1][temp_selected_col] == 'O') 
			{
				is_this_move_legal = true;

				return is_this_move_legal;
			}	
		}

		temp_selected_row = selected_row;

		temp_selected_col = selected_col;

		if (temp_board[temp_selected_row][temp_selected_col+1] == 'X') //**************checking right direction for flips**************
		{
			while(temp_board[temp_selected_row][temp_selected_col+1] == 'X')
			{
				temp_selected_col++;
			}
			if (temp_board[temp_selected_row][temp_selected_col+1] == 'O') 
			{
				is_this_move_legal = true;

				return is_this_move_legal;
			}	
		}

		temp_selected_row = selected_row;

		temp_selected_col = selected_col;

		if (temp_board[temp_selected_row][temp_selected_col-1] == 'X') //**************checking left direction for flips**************
		{
			while(temp_board[temp_selected_row][temp_selected_col-1] == 'X')
			{
				temp_selected_col--;
			}
			if (temp_board[temp_selected_row][temp_selected_col-1] == 'O') 
			{
				is_this_move_legal = true;

				return is_this_move_legal;
			}	
		}

		temp_selected_row = selected_row;

		temp_selected_row_2 = selected_row;

		temp_selected_col = selected_col;

		temp_selected_col_2 = selected_col;

		if (temp_board[temp_selected_row-1][temp_selected_col+1] == 'X') //**************checking diagonal right-up for flips**************
		{
			while(temp_board[temp_selected_row-1][temp_selected_col+1] == 'X')
			{
				temp_selected_row--;

				temp_selected_col++;
			}
			if (temp_board[temp_selected_row-1][temp_selected_col+1] == 'O') 
			{
				is_this_move_legal = true;

				return is_this_move_legal;
			}	
		}

		temp_selected_row = selected_row;

		temp_selected_row_2 = selected_row;

		temp_selected_col = selected_col;

		temp_selected_col_2 = selected_col;

		if (temp_board[temp_selected_row+1][temp_selected_col+1] == 'X') //**************checking diagonal right-down for flips**************
		{
			while(temp_board[temp_selected_row+1][temp_selected_col+1] == 'X')
			{
				temp_selected_row++;

				temp_selected_col++;
			}
			if (temp_board[temp_selected_row+1][temp_selected_col+1] == 'O') 
			{
				is_this_move_legal = true;

				return is_this_move_legal;
			}	
		}

		temp_selected_row = selected_row;

		temp_selected_row_2 = selected_row;

		temp_selected_col = selected_col;

		temp_selected_col_2 = selected_col;

		if (temp_board[temp_selected_row-1][temp_selected_col-1] == 'X') //**************checking diagonal left-up for flips**************
		{
			while(temp_board[temp_selected_row-1][temp_selected_col-1] == 'X')
			{
				temp_selected_row--;

				temp_selected_col--;
			}
			if (temp_board[temp_selected_row-1][temp_selected_col-1] == 'O') 
			{
				is_this_move_legal = true;	

				return is_this_move_legal;								
			}	
		}

		temp_selected_row = selected_row;

		temp_selected_row_2 = selected_row;

		temp_selected_col = selected_col;

		temp_selected_col_2 = selected_col;

		if (temp_board[temp_selected_row+1][temp_selected_col-1] == 'X') //**************checking diagonal left-down for flips**************
		{
			while(temp_board[temp_selected_row+1][temp_selected_col-1] == 'X')
			{
				temp_selected_row++;

				temp_selected_col--;
			}
			if (temp_board[temp_selected_row+1][temp_selected_col-1] == 'O') 
			{
				is_this_move_legal = true;

				return is_this_move_legal;

			}
		}

	}
		
	return is_this_move_legal;
}


void draw_touturial(){

    cout << endl;
    for (int i = 1; i <= 172; i++){
        cout <<"_";
    }
    for (int i = 1; i <= 15; i++){
        cout <<" ";
    }
    cout << "Save: V";
    for (int i = 1; i <= 15; i++){
        cout <<" ";
    }
    cout << "Exit: E";
    for (int i = 1; i <= 15; i++){
        cout <<" ";
    }
    cout << "UP: W";
    for (int i = 1; i <= 15; i++){
        cout <<" ";
    }
    cout << "Down: S";
    for (int i = 1; i <= 15; i++){
        cout <<" ";
    }
    cout << "Left: A";
    for (int i = 1; i <= 15; i++){
        cout <<" ";
    }
    cout << "Right: D";
    for (int i = 1; i <= 15; i++){
        cout <<" ";
    }
    cout << "Put: Enter";
    for (int i = 1; i <= 15; i++){
        cout <<" ";
    }
    cout << endl;

    for (int i = 1; i <= 172; i++){
        cout <<"_";
    }

    
}



void score_board(char player_1_name[10], char player_2_name[10], char board[13][13] , int board_size , int turn)
{
    make_space(1);

    cout << player_1_name << " : " << calculate_player_one_score(board , board_size) << "  symbol : X" << endl;

    make_space(1);

    cout << player_2_name << " : " << calculate_player_two_score(board , board_size) << "  symbol : O" << endl;

    make_space(1);

    if (turn == 1)
    {
    	cout << "its " << player_1_name << "'s turn";
    }
    else
    {
    	cout << "its " << player_2_name << "'s turn";
    }	
    cout << endl << endl;

    
}



/*
9 functions below draw a part of row based on where it is the first char represnts 
where is this row and the second char represent which part of the row we want to 
print
B = Begin
M = Middle
E = End
*/
void line_BB(){
    cout << "\u250C\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u252C";
}


void line_BM(){
    cout << "\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u252C";
}


void line_BE(){
    cout << "\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2510";    
}


void line_MB(){
    cout << "\u251C\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u253C";
}


void line_MM(){
    cout << "\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u253C";    
}


void line_ME(){
    cout << "\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2524";
}


void line_EB(){
     cout << "\u2514\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2534";    
}


void line_EM(){
    cout << "\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2534";  
}


void line_EE(){
    cout << "\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2518";
}


//the four functions below draw the line of a room if it is before the selected room
void line_BB_pre_selected(){
    cout << "\u250C\u2500\u2500\u2500\u2500\u2500\u2500\u2500";
}


void line_MB_pre_selected(){
    cout << "\u251C\u2500\u2500\u2500\u2500\u2500\u2500\u2500";
}


void line_EB_pre_selected(){
     cout << "\u2514\u2500\u2500\u2500\u2500\u2500\u2500\u2500";    
}


void line_M_pre_selected(){
     cout << "\u2500\u2500\u2500\u2500\u2500\u2500\u2500";
}



// this function moves the table forward to move it in the middle of screnn
void make_space(int size){
	if (size == 4)
	{
		for (int i = 1; i <= 70; i ++){
        cout << " ";
        }
	}
    else if(size == 6){
        for (int i = 1; i <= 60; i ++){
        cout << " ";
        }
    }
    else if (size == 8){
        for (int i = 1; i <= 50; i ++){
        cout << " ";
        }
    }
    else if(size == 10){
        for (int i = 1; i <= 40; i ++){
        cout << " ";
        }
    }
    else if(size == 12){
        for (int i = 1; i <= 30; i ++){
        cout << " ";
        }
    }
    else{
        for (int i = 1; i <= 80; i ++){
        cout << " ";
        }
    }
    
}






// three functions below draw a row of function if there is no selected room in that row
//1
void draw_table_first_line(int columns)
{
    for(int i = 1; i <= columns; i++)
    {
        if(i == 1)
        {
            make_space(columns);
            line_BB();
        }
        else if(i == columns){
            line_BE();
        }
        else{
            line_BM();
        }
    }
    cout << endl;
}


//2
void draw_table_middle_line(int columns){
    for(int i = 1; i <= columns; i++)
    {
        if(i == 1)
        {
            make_space(columns);
            line_MB();
        }
        else if(i == columns){
            line_ME();
        }
        else
        {
            line_MM();
        }
    }
    cout << endl;
}


//3
void draw_table_end_line(int columns){
    for(int i = 1; i <= columns; i++)
    {
        if(i == 1)
        {
            make_space(columns);
            line_EB();
        }
        else if(i == columns){
            line_EE();
        }
        else
        {
            line_EM();
        }
    }
}


void special_line(int row_of_the_selected_room, int current_row){
    if(row_of_the_selected_room == current_row){
        cout << "\u2554\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2557";
    }
    else{
          cout << "\u255A\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u255D";
    }
}


// three functions below draw a row of function if there is a selected room in that row
void draw_table_special_line_B(int columns,int column_of_selected_room, int row_of_the_selected_room, int current_row){
    make_space(columns);
    for(int i = 1; i <= columns; i++){
        if(i == 1){
            if(i == column_of_selected_room - 1){
                line_BB_pre_selected();
            }
            else if(i == column_of_selected_room){      // if i is in the beginig of the line
                special_line(row_of_the_selected_room, current_row);
            }
            else{
                line_BB();
            }
        }
        else if(i == columns){
            if(i == column_of_selected_room){
                special_line(row_of_the_selected_room, current_row);
            }
            else{                                        // if i is in the middle of the line
                line_BE();
            }
        }
        else{
            if(i == column_of_selected_room - 1){
                line_M_pre_selected();
            }
            else if(i == column_of_selected_room){       // if i is in the ending of the line
                special_line(row_of_the_selected_room, current_row);
            }
            else{
                line_BM();
            }

        }
    }
    cout << endl;
}


void draw_table_special_line_E(int columns,int column_of_selected_room, int row_of_the_selected_room, int current_row){
    make_space(columns);
    for(int i = 1; i <= columns; i++){
        if(i == 1){
            if(i == column_of_selected_room - 1){
                line_EB_pre_selected();
            }
            else if(i == column_of_selected_room){      // if i is in the beginig of the line
                special_line(row_of_the_selected_room, current_row);
            }
            else{
                line_EB();
            }
        }
        else if(i == columns){
            if(i == column_of_selected_room){
                special_line(row_of_the_selected_room, current_row);
            }
            else{                                        // if i is in the middle of the line
                line_EE();
            }
        }
        else{
            if(i == column_of_selected_room - 1){
                line_M_pre_selected();
            }
            else if(i == column_of_selected_room){       // if i is in the ending of the line
                special_line(row_of_the_selected_room, current_row);
            }
            else{
                line_EM();
            }

        }
    }
    cout << endl;
}


void draw_table_special_line_M(int columns,int column_of_selected_room, int row_of_the_selected_room, int current_row){
    make_space(columns);
    for(int i = 1; i <= columns; i++){
        if(i == 1){
            if(i == column_of_selected_room - 1){
                line_MB_pre_selected();
            }
            else if(i == column_of_selected_room){      // if i is in the beginig of the line
                special_line(row_of_the_selected_room, current_row);
            }
            else{
                line_MB();
            }
        }
        else if(i == columns){
            if(i == column_of_selected_room){
                special_line(row_of_the_selected_room, current_row);
            }
            else{                                        // if i is in the middle of the line
                line_ME();
            }
        }
        else{
            if(i == column_of_selected_room - 1){
                line_M_pre_selected();
            }
            else if(i == column_of_selected_room){       // if i is in the ending of the line
                special_line(row_of_the_selected_room, current_row);
            }
            else{
                line_MM();
            }

        }
    }
    cout << endl;
}


//this function print the contents of the array
void print_content(char arr[13][13], int i, int j){
  if(arr[i - 1][j - 1] == '-'){
    cout <<" ";
  }
  else{
    cout << arr[i - 1][j - 1];
  }
}




// this function draw the table columns if in that row there is no selected room
void draw_table_columns(int columns, int row, char arr[13][13]){
    make_space(columns);
    for(int i = 1; i <= columns + 1; i++){
        if(i == columns + 1){
        cout << "\u2502";
        }
        else{
            cout << "\u2502       ";
        }
    }
    cout << endl;
    make_space(columns);
    for(int i = 1; i <= columns + 1; i++){
        if(i == columns + 1){
        cout << "\u2502";
        }
        else{ 
            cout << "\u2502   ";
            print_content(arr, row, i);
            cout <<"   ";
        }
    }
    cout << endl;
    make_space(columns);
    for(int i = 1; i <= columns + 1; i++){
        if(i == columns + 1){
        cout << "\u2502";
        }
        else{
           cout << "\u2502       ";
        }
    }
    cout << endl;
}



// this function draw table columns if there is a selected room in that row
void draw_table_columns_special(int columns, int column_of_selected_room, int row, char arr[13][13]){
        make_space(columns);
        for(int i = 1; i <= columns + 1; i++){
            if(i == column_of_selected_room || i == column_of_selected_room + 1){
                if(i == columns + 1){
                    cout << "\u2551";
                }
                else{
                    cout << "\u2551       ";
                }
                continue;
            }
            if(i == columns + 1){
            cout << "\u2502";

            }
            else{
                cout << "\u2502       ";
            }
        }
        cout << endl;
        make_space(columns);
        for(int i = 1; i <= columns + 1; i++){
            if(i == column_of_selected_room || i == column_of_selected_room + 1){
                if(i == columns + 1){
                    cout << "\u2551";
                }
                else{
                    cout << "\u2551   ";
                    print_content(arr, row, i);
                    cout <<"   ";
                }
                continue;
            }
            if(i == columns + 1){
            cout << "\u2502";

            }
            else{
                cout << "\u2502   ";
                    print_content(arr, row, i);
                    cout <<"   ";
            }
        }
        cout << endl;
        make_space(columns);
        for(int i = 1; i <= columns + 1; i++){
            if(i == column_of_selected_room || i == column_of_selected_room + 1){
                if(i == columns + 1){
                    cout << "\u2551";
                }
                else{
                    cout << "\u2551       ";
                }
                continue;
            }
            if(i == columns + 1){
            cout << "\u2502";

            }
            else{ 
                cout << "\u2502       ";
            }
        }
        cout << endl;
        
}  


// this function draw the table currently incomplete 
void draw_the_table(int board_size, int selected_col, int selected_row, char board[13][13]){
    selected_col++;
    selected_row++;
    for(int i = 1; i <= board_size + 1; i++){
         if(i == selected_row){
            if(i == 1){
                draw_table_special_line_B(board_size, selected_col, selected_row, i);
                draw_table_columns_special(board_size, selected_col, i , board);
                draw_table_special_line_M(board_size, selected_col, selected_row, i + 1);
                continue;
            }
            else if(i == board_size){
                draw_table_special_line_M(board_size, selected_col, selected_row, i);
                draw_table_columns_special(board_size, selected_col, i, board); 
                draw_table_special_line_E(board_size, selected_col, selected_row, i + 1);
                break;
            }
            else{
                draw_table_special_line_M(board_size, selected_col, selected_row, i);
                draw_table_columns_special(board_size, selected_col, i, board);
                draw_table_special_line_M(board_size, selected_col, selected_row, i + 1);
                continue;
            }
        }
        else if (i == selected_row + 1){
            draw_table_columns(board_size, i, board);
            continue;                                              
        }                                                         
        if(i==1){
            draw_table_first_line(board_size);
            draw_table_columns(board_size, i, board);
        }
        else if(i == board_size + 1){
            draw_table_end_line(board_size);  
        }
        else{
            draw_table_middle_line(board_size);
            draw_table_columns(board_size, i, board);
        }
    }
}


int return_accepted_save_value(int current_room, int length){     // this function return the save value in a suitable form if it is
	if(current_room == length){									  // more than length or its -1
		current_room --;
	}
	else if(current_room == -1){
		current_room ++;
	}
	return current_room;
}


int return_save_option_in_load(GameInfo * games, int length){        // this function chosses a save to load
	char choice;
	int current_room = 0;
	bool is_save_chosen = false;
	
	while(true){
		 system("cls");
		 for (int i = 1; i <= 25; i++){
         cout <<" ";
   		 }
   		 cout << "W : Up";
   		 for (int i = 1; i <= 25; i++){
         cout <<" ";
   		 }
   		 cout << "S : Down";
   		 for (int i = 1; i <= 25; i++){                            //draw_touturial for save option
         cout <<" ";
   		 }
    	 cout << "Enter : Put";
  		 for (int i = 1; i <= 25; i++){
         cout <<" ";
    	 }
   		 cout << "E : exit" << endl;
   		 for (int i = 1; i <= 172; i++){
         cout <<"_";
    	 }
    	 cout << endl << endl;
		for (int i = 0; i < length; i++){
			if(i == current_room){
				cout << i + 1 << " ***" << endl;
				cout << games[i].player_one_name <<" : " << games[i].player_one_score << endl;
				cout << games[i].player_two_name <<" : " << games[i].player_two_score << endl << endl;
			}
			else{
				cout << i + 1 << endl;
				cout << games[i].player_one_name <<" : " << games[i].player_one_score << endl;
				cout << games[i].player_two_name <<" : " << games[i].player_two_score << endl << endl;
			}
		}
		choice = getch();
		if(choice =='w'){
			current_room --;
			current_room = return_accepted_save_value(current_room, length);
		}
		else if(choice == 's'){
			current_room ++;
			current_room = return_accepted_save_value(current_room, length);
		}
		else if(choice == 13){
			is_save_chosen =true;
		}
		else if(choice == 'e'){
			is_save_chosen =true;
			current_room = -1;
		}
		if(is_save_chosen){
			break;   // current room = -1 means return to menu
		}
	}
	return current_room + 1;
}


void put_info_of_saves(GameInfo * games, int length_of_saves){   // this function put all of save infos in an structure array
	ifstream InGameFile("save.txt" , ios:: in);
	
	int fake_length;
	
	InGameFile >> fake_length;
	
	for(int i = 1; i <= length_of_saves; i++)
	{
		InGameFile >> games[i - 1].board_size >> games[i - 1].selected_row >> games[i - 1].selected_col
	
		>> games[i - 1].player_one_name >> games[i - 1].player_two_name;
	
		InGameFile >> games[i - 1].player_one_score >> games[i - 1].player_two_score >> games[i - 1].turn;
	
		for(int j = 0; j < 13; j++)
		{
       		for(int k = 0; k < 13; k++)
       		{
            InGameFile >> games[i - 1].board[j][k];
        	}
    	}	
    }
    InGameFile.close();
}


void change_save_info(GameInfo * games, char board[13][13], int player_one_score , int player_two_score, int selected_save, int turn){
	games[selected_save - 1].player_one_score = player_one_score;
	
	games[selected_save - 1].player_two_score = player_two_score;
	
	games[selected_save - 1].turn = turn;
	
	for(int i = 0; i < 13; i ++)
	{
		for(int j = 0 ; j < 13; j++)
		{
			games[selected_save - 1].board[i][j] = board[i][j];
		}
	}
}


void write_new_saves(GameInfo * games, int length_of_saves) // this function write the changed save in save.txt
{             
	ofstream OutGameFile("save.txt" , ios:: trunc);
	
	OutGameFile << length_of_saves << "\n";
	
	for(int i = 1; i <= length_of_saves; i++)
	{
		OutGameFile << " " << games[i - 1].board_size << " " << games[i - 1].selected_row << " " << games[i - 1].selected_col
	
		<< " " << games[i - 1].player_one_name << " " << games[i - 1].player_two_name; 
	
		OutGameFile << " " << games[i - 1].player_one_score << " " << games[i - 1].player_two_score
	
		<< " " << games[i - 1].turn << "\n";
	
		for(int j = 0; j < 13; j++)
		{
       		for(int k = 0; k < 13; k++)
       		{
            OutGameFile << games[i - 1].board[j][k];
        	}
        	OutGameFile << "\n";
    	}	
    }
    OutGameFile.close();
}


int get_players_num_in_leader_board(){
	ifstream InLeaderFile("leader_board.txt", ios:: in);
	int length;
	InLeaderFile >> length;
	InLeaderFile.close();
	return length;
}


void put_players_in_array(PlayerInfo * players, int length){
	ifstream InLeaderFile("leader_board.txt", ios:: in);
	int fake_length;
	InLeaderFile >> fake_length;
	for(int i = 1; i <= length; i++){
		InLeaderFile >> players[i - 1].player_name >> players[i - 1].player_score;
	}
	InLeaderFile.close();
}


void sort_leader_board(PlayerInfo * players, int length){
	for(int i = 0; i < length; i ++){
		for(int j = 0; j < length - i - 1; j ++){
			if(players[j].player_score < players[j + 1].player_score){
				char temp_player[10];
				int temp_score;
				temp_score = players[j].player_score;
				for(int k = 0 ; k < 10; k++){
					temp_player[k] = players[j].player_name[k];
				}
				strcpy(players[j].player_name, players[j + 1].player_name);
				players[j].player_score = players[j + 1].player_score;
				strcpy(players[j + 1].player_name, temp_player);
				players[j + 1].player_score = temp_score;
			}
		}
	}
}	


void write_new_leader_board(PlayerInfo * players, int length){             // this function write the changed save in save.txt
	ofstream OutLederFile("leader_board.txt" , ios:: trunc);
	OutLederFile << length << "\n";
	for(int i = 1; i <= length; i++){
		OutLederFile << players[i - 1].player_name << " " << players[i - 1].player_score << "\n";
    }
    OutLederFile.close();
}


void change_scores_in_leader_board(PlayerInfo * players, int length, char winner[10]){           // beware that this players array must have  length + 1 room
	bool found = false;
	for(int i = 0; i < length; i++){
		bool all_letters_equal = true;
		for(int j = 0; j < 10 ; j ++){
			if(winner[j] != players[i].player_name[j]){
				all_letters_equal = false;
				break;
			}
			if(winner[j] < 97 || players[i].player_name[j] < 97  || winner[j] > 122 || players[i].player_name[j] > 122){
				break;
			}
		}
		if(all_letters_equal){
				found = true;
				players[i].player_score ++;
		}
		if(found){
			break;
		}
	}
	if(!found){
		for(int i = 0; i < 10; i++){
			players[length].player_name[i] = winner[i];
		}
		players[length].player_score = 1;
		sort_leader_board(players, length + 1);                      // + 1 because a new score has been aded
		write_new_leader_board(players, length + 1);
	}
	else{
		sort_leader_board(players, length);                      
		write_new_leader_board(players, length);
	}
}

