#include "../function.h"

int main() {
	bool reset = false;

	do {
		reset = false;
		int* data = nullptr;
		int choice = 0, pos, val, nTemp = -1;
		bool is_running = true;
		Stack<int>* redo = nullptr;
		Stack<int>* undo = nullptr;

		allocate_data(data, size_file_data());
		allocate_data(redo, 0);
		allocate_data(undo, 0);
		read_data(data);

		while (is_running) {
			current_arr(data);
			menu();
			input_checking(choice);

			switch (choice) {
			case 1:

				input_pos(*((int*)origin_addr(data)), pos);

				// Lưu sự kiện xóa phần tử vào undo
				nTemp = *((int*)origin_addr(undo));
				undo = resize_arr(undo, nTemp + 1);
				undo[nTemp].history = delete_action;
				undo[nTemp].pos = pos;
				undo[nTemp].val = data[pos];

				delete_pos(data, pos);

				break;
			case 2:

				input_pos_and_val(*((int*)origin_addr(data)), pos, val);

				insert_pos_val(data, pos, val);


				// Lưu sự kiện thêm phần tử vào undo
				nTemp = *((int*)origin_addr(undo));
				undo = resize_arr(undo, nTemp + 1);
				undo[nTemp].history = insert_action;
				undo[nTemp].pos = pos;
				undo[nTemp].val = val;

				break;
			case 3:
				undo_stack(data, undo, redo);
				break;
			case 4:
				redo_stack(data, undo, redo);
				break;
			case 5:
				save_file_data(data);
				std::cout << "\t Saved!\n";
				break;
			case 6:
				reset = true;
				is_running = false;
				system("cls");
				std::cout << "\t  Reset is done!\n";
				break;
			case 7:
				is_running = false;
				break;
			default:
				break;
			}
		}

		data = free_arr(data);
		redo = free_arr(redo);
		undo = free_arr(undo);

	} while (reset);

	return 0;
}
