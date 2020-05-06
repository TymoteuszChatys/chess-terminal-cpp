#include "board.h"
#include "pieces.h"
#include "controller.h"

class board;
class controller;

int menu();
std::string dash();
void player_vs_player();
void program_help();


int main()
{
	int option;
	option = menu();
	if (option == 1) {
		std::system("cls");
		player_vs_player();
	}else if (option == 31) {
		program_help();
	}
	return 0;
}

std::string dash()
{
	std::string break_line;
	break_line = "---------------------------------";
	return break_line;
}

int menu() 
{
	std::cout << dash() << dash() << std::endl << "Chess Program" << std::endl << dash() << dash() << std::endl;
	std::cout << "Which option would you like to choose?" << std::endl;
	std::cout << "1 - Player vs Player" << std::endl;
	std::cout << "2 - Secret (Not yet implemented)" << std::endl;
	std::cout << "3 - Help (Recommended for first time use)" << std::endl << dash() << dash() << std::endl;
	//Asks user to choose an option
	std::string option;
	getline(std::cin, option);
	if (option == "1") {
		return 1;
	}else if (option == "3") {
		std::system("cls");
		std::cout << dash() << dash() << std::endl << "Help" << std::endl << dash() << dash() << std::endl;
		std::cout << "Which option would you like to choose?" << std::endl;
		std::cout << "1 - How to use the program" << std::endl;
		std::cout << "2 - How to play chess" << std::endl;
		std::string help_option;
		getline(std::cin, help_option);
		if (help_option == "1") {
			return 31;
		}else if (help_option == "2") {
			return 32;
		}
	}
	return 0;
}

void player_vs_player() 
{
	chess::controller global_controller;
	chess::board global_board(&global_controller);

	for (auto i = 0; i < 999; i++) {
		std::cout << "Mode: Player vs Player "<< std::endl;
		std::cout << "FEN: " << global_board.get_fen() << std::endl;
		global_controller.each_turn(&global_board);
	}
}

void program_help() 
{
	std::system("cls");
	std::cout << dash() << dash() << std::endl << "Program Help" << std::endl << dash() << dash() << std::endl;
	
	std::cout << "1.To make a move you must first indicate the starting co-ordinate of the piece followed by the co-ordinate you want to move the piece to. (e.g. e2e4 to move white pawn to e4)" << std::endl << std::endl;
	std::cout << "2.You can see all the available moves for the piece by typing in just the starting co-ordinate (e.g e2 to see valid moves for the e2 pawn)" <<std::endl << std::endl;
}