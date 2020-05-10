#include "board.h"
#include "pieces.h"
#include "controller.h"
#include "computer_controller.h"

//Colours
HANDLE computer_console = GetStdHandle(STD_OUTPUT_HANDLE);
#define GREEN_F		(SetConsoleTextAttribute(computer_console, FOREGROUND_GREEN))  //sets the console colour to green
#define RED_F		(SetConsoleTextAttribute(computer_console, FOREGROUND_RED))  //sets the console colour to red
#define BLUE_F		(SetConsoleTextAttribute(computer_console, FOREGROUND_BLUE)) //sets the console colour to blue
#define WHITE_F		(SetConsoleTextAttribute(computer_console, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN)) //defines the colour white

using namespace chess;


int computer_controller::evaluation(board* the_board, int* player_to_move)
{
	int point_evaluation{}; // counter 
	auto pieces = the_board->get_pieces();

	for (auto iterator = pieces.begin(); iterator != pieces.end(); iterator++) {
		point_evaluation = point_evaluation + (*iterator)->points();
	}
	if (the_board->is_king_in_check(*player_to_move)) {
		point_evaluation = 10000 * *player_to_move *-1;
	}

	return point_evaluation;
}


auto computer_controller::valid_moves_list(board* the_board, int player_to_move)
{
	std::vector<int> initial_positions;
	std::vector<int> final_positions;
	auto pieces = the_board->get_pieces();
	for (auto iterator = pieces.begin(); iterator != pieces.end(); iterator++) {
		auto the_piece = (*iterator);
		if ((*iterator)->get_colour<int>() == player_to_move) {
			int initial_position = the_piece->get_position<int>();
			std::vector<int> this_piece_valid_moves = the_piece->valid_moves(the_board);

			for (auto second_iterator = this_piece_valid_moves.begin(); second_iterator != this_piece_valid_moves.end(); second_iterator++) {
				initial_positions.push_back(initial_position);
			}

			final_positions.insert(final_positions.end(), this_piece_valid_moves.begin(), this_piece_valid_moves.end());
		}
	}

	//Use of structured binding to return two vectors. 

	struct two_vectors {
		std::vector<int> vector_1, vector_2;
	};

	return two_vectors{ initial_positions,final_positions };
}

std::tuple<int, std::string> computer_controller::minimax_search(board* the_board, size_t depth,int alpha, int beta, bool maximizing_player)
{

	std::string best_move{};
	std::string future_moves{};
	bool end_game{ false };
	int player_to_move;

	if (maximizing_player == true) {
		player_to_move = -1;
	}
	else {
		player_to_move = 1;
	}


	if (depth == 0 || end_game == true) {
		return {evaluation(the_board,&player_to_move),best_move};
	}

	auto [initial_positions, final_positions] = valid_moves_list(the_board, player_to_move);

	if (maximizing_player == true) {
		int max_evaluation{ INT_MAX * -1 };
		size_t move{};
		for (auto iterator = initial_positions.begin(); iterator != initial_positions.end(); iterator++){
			chess::computer_controller temporary_controller;
			board temporary_board(the_board, &temporary_controller, (*iterator), final_positions.at(move));
			auto[evaluation, future_moves] = minimax_search(&temporary_board, depth - 1, alpha, beta, false);
			
			if (evaluation*-1 > max_evaluation) {
				max_evaluation = evaluation*-1;
				best_move = square_notation_to_human((*iterator)) + square_notation_to_human(final_positions.at(move));
			}
			alpha = max(alpha, evaluation * -1);
			if (beta <= alpha) {
				break;
			}
			//std::cout << "eval: " << evaluation*-1 << "  b_eval:" << max_evaluation << " move:" << square_notation_to_human((*iterator)) + square_notation_to_human(final_positions.at(move)) << " best move: " << best_move << " " << depth << std::endl;
			move++;
			}
		return { max_evaluation,best_move};
	}
	else {
		int min_evaluation{ INT_MAX };
		size_t move{};
		for (auto iterator = initial_positions.begin(); iterator != initial_positions.end(); iterator++) {
			chess::computer_controller temporary_controller;
			board temporary_board(the_board, &temporary_controller, (*iterator), final_positions.at(move));
			auto [evaluation, future_moves] = minimax_search(&temporary_board, depth - 1, alpha, beta, true);
			if (evaluation < min_evaluation) {
				min_evaluation = evaluation*-1;
				best_move = square_notation_to_human((*iterator)) + square_notation_to_human(final_positions.at(move));
			}
			beta = min(beta, evaluation * -1);
			if (beta <= alpha) {
				break;
			}
			//std::cout << "eval: " << evaluation*-1 << "  b_eval:" << min_evaluation << " move:" << square_notation_to_human((*iterator)) + square_notation_to_human(final_positions.at(move)) << " best move: " << best_move << " " << depth << std::endl;
			move++;
		}
		return { min_evaluation,best_move};
	}
}

bool computer_controller::each_turn(board* the_board)
{
	std::cout << *the_board << std::endl;
	this->print_move_history();
	std::cout << std::endl;
	bool valid_move{ false };
	std::string player_to_move = the_board->whose_turn_to_move();
	bool end_game{ false };
	while (valid_move == false && end_game == false) {
		if (the_board->is_king_in_check(get_turn_to_move()) == true && the_board->is_there_any_valid_moves(player_to_move) == false) {
			GREEN_F; std::cout << player_to_move << " has been checkmated. Game over." << std::endl; WHITE_F;
			end_game = true;
		}
		else if (the_board->is_king_in_check(get_turn_to_move()) == true) {
			GREEN_F; std::cout << player_to_move << "'s king is in check" << std::endl; WHITE_F;
		}
		else if (the_board->is_there_any_valid_moves(player_to_move) == false) {
			GREEN_F; std::cout << "Game has been drawn by stalemate " << std::endl; WHITE_F;
			end_game = true;
		}
		if (end_game == true) {
			std::string key;
			std::cout << std::endl << "enter any key to go back to the main menu" << std::endl;
			std::cin >> key;
		}
		else {
			if (player_to_move == "white") {
				std::cout << player_to_move << "'s turn to move. Enter your move: ";
				std::vector<int> moves = enter_move(the_board);
				if (moves.at(1) == -101) {
					the_board->print_valid_moves(moves.at(0), true);
				}
				else if (moves.at(1) == -102) {
					std::cout << "No valid move was entered. Enter square e.g e2 for information about available placements." << std::endl;
				}
				else if (moves.at(1) == -110) {
					std::cout << "Error: You can only move " << the_board->whose_turn_to_move() << " pieces" << std::endl;
				}
				else if (moves.at(1) == -600) {
					end_game = true;
				}
				else {
					this->make_move(moves.at(0), moves.at(1), the_board);
					valid_move = true;
				}
			}
			//Computer is black so this code looks at the minimax search and gets the move.
			else if (player_to_move == "black") {
				auto [evaluation, computer_move] = minimax_search(the_board, 3, INT_MAX*-1, INT_MAX, true);
				std::vector<int> moves = enter_computer_move(the_board, computer_move);
				this->make_move(moves.at(0), moves.at(1), the_board);
				valid_move = true;
				std::cout << evaluation << " " << computer_move;
			}
			

		}
	}
	std::system("cls");
	return end_game;
}

std::vector<int> computer_controller::enter_computer_move(board* the_board, std::string move)
{
	std::vector<int> initial_and_final_moves;
	std::vector<std::string> move_vector = split_string(move, 2);
	initial_and_final_moves.push_back(square_notation_to_computer(move_vector.at(0)));
	initial_and_final_moves.push_back(square_notation_to_computer(move_vector.at(1)));

	return initial_and_final_moves;
}