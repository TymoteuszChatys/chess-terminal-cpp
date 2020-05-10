#include "board.h"
#include "pieces.h"
#include "controller.h"
#include "tutorial_controller.h"
#include "checkmate_controller.h"
#include "computer_controller.h"

//Colours
HANDLE main_console = GetStdHandle(STD_OUTPUT_HANDLE);
#define GREEN_F		(SetConsoleTextAttribute(main_console, FOREGROUND_GREEN))  //sets the console colour to green
#define RED_F		(SetConsoleTextAttribute(main_console, FOREGROUND_RED))  //sets the console colour to red
#define BLUE_F		(SetConsoleTextAttribute(main_console, FOREGROUND_BLUE)) //sets the console colour to blue
#define WHITE_F		(SetConsoleTextAttribute(main_console, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN)) //defines the colour white


class board;
class controller;
class computer_controller;

int main_menu();
std::string dash();
void player_vs_player();
void beginners_tutorial();
void advanced_tutorial();
void checkmate_trainer();
void chess_engine();

int main()
{
	bool end_program{ false };
	while (end_program == false) {
		int option;
		option = main_menu();
		if (option == 1) {
			std::system("cls");
			player_vs_player();
		}
		else if (option == 2) {
			chess_engine();
		}
		else if (option == 3) {
			checkmate_trainer();
		}
		else if (option == 41) {
			beginners_tutorial();
		}
		else if (option == 42) {
			advanced_tutorial();
		}
		else if (option == 5) {
			end_program = true;
		}
	}
	
	return 0;
}

std::string dash()
{
	std::string break_line;
	break_line = "---------------------------------";
	return break_line;
}

int main_menu() 
{
	std::system("cls");
	std::cout << dash() << dash() << std::endl << "Chess Program" << std::endl << dash() << dash() << std::endl;
	std::cout << "Which option would you like to choose?" << std::endl;
	std::cout << "1 - Player vs Player" << std::endl;
	std::cout << "2 - Player vs Computer" << std::endl;
	std::cout << "3 - Checkmate Trainer" << std::endl;
	std::cout << "4 - Tutorial (Recommended for first time use)" << std::endl;
	std::cout << "5 - exit" << std::endl << dash() << dash() << std::endl;
	//Asks user to choose an option
	std::string option;
	getline(std::cin, option);
	if (option == "1") {
		return 1;
	}else if (option == "2") {
		return 2;
	}else if (option == "3") {
		return 3;
	}else if (option == "4") {
		std::system("cls");
		std::cout << dash() << dash() << std::endl << "Tutorial" << std::endl << dash() << dash() << std::endl;
		std::cout << "Which option would you like to choose?" << std::endl;
		std::cout << "1 - Beginners Tutorial" << std::endl;
		std::cout << "2 - Advanced Tutorial" << std::endl;
		std::string help_option;
		getline(std::cin, help_option);
		if (help_option == "1") {
			return 41;
		}else if (help_option == "2") {
			return 42;
		}
	}else if (option == "5") {
		return 4;
	}
	return 0;
}

void player_vs_player() 
{
	chess::controller global_controller;
	chess::board global_board(&global_controller);
	bool end_game = {false};
	
	while (end_game == false) {
		std::cout << "Mode: Player vs Player " << std::endl;
		std::cout << "FEN: " << global_board.get_fen() << std::endl;
		std::cout << "type 'stop' to abort game" << std::endl;
		end_game = global_controller.each_turn(&global_board);
	}
}

void chess_engine()
{
	chess::computer_controller global_computer_controller;
	chess::board global_computer_board(&global_computer_controller);
	bool end_game = { false };


	while (end_game == false) {
		std::cout << "Mode: Player vs Player " << std::endl;
		std::cout << "FEN: " << global_computer_board.get_fen() << std::endl;
		std::cout << "type 'stop' to abort game" << std::endl;
		end_game = global_computer_controller.each_turn(&global_computer_board);
	}

	std::string key;
	std::cout << "Input any key to go back to the main menu ";
	getline(std::cin, key);
}

void beginners_tutorial() 
{
	std::system("cls");
	std::vector<std::string> title;
	std::vector<std::string> fen_strings;
	std::vector<std::string> tutorial_information;
	
	//pawn tutorial moving
	title.push_back("The Pawn");
	fen_strings.push_back("8/8/8/8/8/8/4P3/8 w - - 0 1");
	tutorial_information.push_back("A pawn may only move one square forward at a time, apart from its first move in which it can move two squares forward at a time");

	//pawn promotion tutorial
	title.push_back("Pawn Promotion");
	fen_strings.push_back("8/4P3/8/8/8/8/8/8 w - - 0 1");
	tutorial_information.push_back("When a pawn reaches the other end of the board it can be changed for any other piece of its own colour, except the King. This is called promotion. To do this you can do e7e8Q to promote to a queen.");

	//pawn tutorial capture
	title.push_back("Pawn Capture");
	fen_strings.push_back("8/5p2/4pp2/3pp3/3P4/8/8/8 w - - 0 1");
	tutorial_information.push_back("Although a pawn moves straight forward it captures by taking one square diagonally forward");
	
	//knight tutorial
	title.push_back("The Knight");
	fen_strings.push_back("8/8/8/8/3N4/8/8/8 w - - 0 1");
	tutorial_information.push_back("The Knight moves in an L shape in any direction. We can say that it either moves two squares sideways and then one square up or down, or two squares up or down, and then one square sideways. The Knight may jump over pieces");

	//bishop tutorial
	title.push_back("The Bishop");
	fen_strings.push_back("8/8/8/8/3B4/8/8/8 w - - 0 1");
	tutorial_information.push_back("The Bishop moves diagonally any number of squares, forwards or backwards");

	//rook tutorial
	title.push_back("The Rook");
	fen_strings.push_back("8/8/8/3R4/8/8/8/8 w - - 0 1");
	tutorial_information.push_back("The Rook moves horizontally and vertically any number of squares, forwards or backwards.");

	//queen tutorial
	title.push_back("The Queen");
	fen_strings.push_back("8/8/8/4Q3/8/8/8/8 w - - 0 1");
	tutorial_information.push_back("The Queen moves straight forward or backwards and diagonally any number of squares, a combination of a Rook and Bishop.");
	
	//king tutorial
	title.push_back("The King");
	fen_strings.push_back("8/8/8/8/4K3/8/8/8 w - - 0 1");
	tutorial_information.push_back("The King is the most important piece on the chessboard. It can never be captured and if it is in danger then it must be made safe immediately. If it is not possible to make the King safe then the game is lost. The King may move one square in any direction.");	

	for (size_t i{}; i < fen_strings.size(); i++) {
		chess::tutorial_controller global_tutorial_controller;
		chess::board tutorial_board(fen_strings.at(i), &global_tutorial_controller);
		bool end_game = { false };

		while (end_game == false) {
			std::system("cls");
			std::cout << "Mode: Beginners tutorial part " << i+1 << "/" << fen_strings.size() << std::endl;
			std::cout << "          " << title.at(i) << std::endl;
			RED_F;
			std::cout << "Type a square to see availabe moves e.g. e2" << std::endl;
			std::cout << "To make a move type the intial and final position e.g. e2e4" << std::endl;
			WHITE_F;
			std::cout << "Type 'next' to move to next part" << std::endl;
			end_game = global_tutorial_controller.each_turn(&tutorial_board, tutorial_information.at(i));
		}
	}
	
	std::string key;
	std::cout << "Input any key to go back to the main menu ";
	getline(std::cin, key);
}


void advanced_tutorial()
{
	std::system("cls");
	std::vector<std::string> title;
	std::vector<std::string> fen_strings;
	std::vector<std::string> tutorial_information;

	//castling tutorial
	title.push_back("Castling");
	fen_strings.push_back("8/8/8/8/8/8/8/4K2R w K - 0 1");
	tutorial_information.push_back("When the King castles, he moves two squares to the left or right and the Rook is moved to stand on the opposite side of the King. When castling, the King must always be moved first. In this case e1g1.");

	//en passant tutorial
	title.push_back("En Passant");
	fen_strings.push_back("8/8/8/4Pp2/8/8/8/8 w - f6 0 1");
	tutorial_information.push_back("This special way of capturing is called capturing en passant and is abbreviated e.p. En passant is a French expression which means 'in passing'. The en passant capture must be done immediately after the black pawn advances two squares. If White plays another move she cannot then decide to capture en passant!  (e5f6)");

	GREEN_F; 
	std::cout << "  This advanced tutorial will introduce two advanced chess moves" << std::endl << std::endl;
	WHITE_F;
	std::string key_1;
	std::cout << "  Input any key to continue: ";
	getline(std::cin, key_1);

	for (size_t i{}; i < fen_strings.size(); i++) {
		chess::tutorial_controller global_tutorial_controller;
		chess::board tutorial_board(fen_strings.at(i), &global_tutorial_controller);
		bool end_game = { false };

		while (end_game == false) {
			std::system("cls");
			std::cout << "Mode: Advanced tutorial part " << i + 1 << "/" << fen_strings.size() << std::endl;
			std::cout << "          " << title.at(i) << std::endl;
			RED_F;
			std::cout << "Type a square to see availabe moves e.g. e2" << std::endl;
			std::cout << "To make a move type the intial and final position e.g. e2e4" << std::endl;
			WHITE_F;
			std::cout << "Type 'next' to move to next part" << std::endl;
			end_game = global_tutorial_controller.each_turn(&tutorial_board, tutorial_information.at(i));
		}
	}

	std::string key_2;
	std::cout << "Input any key to go back to the main menu ";
	getline(std::cin, key_2);


}

void checkmate_trainer() 
{
	std::system("cls");
	std::string title;
	std::vector<std::string> fen_strings;
	std::vector<std::string> correct_moves;
	title = "Checkmate in 1 move";
	
	fen_strings.push_back("6k1/4Rppp/8/8/8/8/5PPP/6K1 w - - 0 1");
	correct_moves.push_back("e7e8");

	fen_strings.push_back("8/1p6/kp6/1p6/8/8/5PPP/5RK1 w - - 0 1");
	correct_moves.push_back("f1a1");

	fen_strings.push_back("R7/4kp2/5N2/4P3/8/8/8/6K1 w - - 0 1");
	correct_moves.push_back("a8e8");

	fen_strings.push_back("5r2/1b2Nppk/8/2R5/8/8/5PPP/6K1 w - - 0 1");
	correct_moves.push_back("c5h5");



	for (size_t i{}; i < fen_strings.size(); i++) {
		chess::checkmate_controller global_checkmate_controller;
		chess::board checkmate_board(fen_strings.at(i), &global_checkmate_controller);
		bool end_game = { false };

		while (end_game == false) {
			std::system("cls");
			std::cout << "Mode: Checkmate trainer.  " << i + 1 << "/" << fen_strings.size() << std::endl;
			std::cout << "          " << title << std::endl;
			RED_F;
			std::cout << "Type a square to see availabe moves e.g. e2" << std::endl;
			std::cout << "To make a move type the intial and final position e.g. e2e4" << std::endl;
			WHITE_F;
			std::cout << "Type 'next' to move to next checkmate" << std::endl;
			end_game = global_checkmate_controller.each_turn(&checkmate_board, title,correct_moves.at(i));
		}
	}

	std::string key;
	std::cout << "Input any key to go back to the main menu ";
	getline(std::cin, key);
}

