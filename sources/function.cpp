#include "header.h"

int headsize = sizeof(int);

void menu() {
    std::cout << "\n\t _______________________MENU_______________________\n"
        << "\t|\t1. Delete element at position              |\n"
        << "\t|\t2. Insert element at position with value   |\n"
        << "\t|\t3. Undo last operation                     |\n"
        << "\t|\t4. Redo last undone operation              |\n"
        << "\t|\t5. Save array to file                      |\n"
        << "\t|\t6. Reset workspace                         |\n"
        << "\t|\t7. Quit                                    |\n"
        << "\t|__________________________________________________|\n";
    std::cout << "\t Please input: ";
}

int size_file_data() {

	int n = 0;
	std::fstream fin;
	fin.open("resources/input.txt", std::ios::in);

	if (!fin.is_open()) {
		std::cout << "Fail to open file!\n";
		return n;
	}

	while (!fin.eof()) {
		int temp;
		fin >> temp;
		n++;
	}
	return n;
}

void input_pos(const int& n,int& pos) {

	bool check = false;

	do 	{
		if (check) {
			std::cout << "\t Invalid position! Input again\n";
		}
		std::cout << "\t Please input position you want to delete: ";
		input_checking(pos);
		check = true;
	} while (pos < 1 || pos > n);

	pos--;
}

void input_pos_and_val(const int& n, int& pos, int& val) {

	bool check = false;

	do {
		if (check) {
			std::cout << "\t Invalid position! Input again\n";
		}
		std::cout << "\t Please input position you want to insert: ";
		input_checking(pos);
		std::cout << "\t Please input value you want to insert: ";
		input_checking(val);
		check = true;
	} while (pos < 1 || pos > n);

	pos--;
}

void input_checking(int& num) {
	bool check;

	do {
		check = false;
		std::cin >> num;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cout << "\t Invalid input! Input again: ";
			check = true;
		}
		std::cin.ignore();

	} while (check);
}