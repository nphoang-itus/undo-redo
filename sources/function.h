#pragma once
#ifndef FUNCTION_H
#define FUNCTION_H

#include "header.h"

extern int headsize;

template <class T>
T* origin_addr(T*& aData) {
	if (aData != nullptr) {
		return (T*)((char*)aData - headsize);
	}
	return nullptr;
}

template <class T>
T* data_addr(T*& aOrigin) {
	if (aOrigin != nullptr) {
		return (T*)((char*)aOrigin + headsize);
	}
	return nullptr;
}

template <class T>
void read_data(T*& aData) {
	if (!aData) return;

	int index = 0;

	std::fstream fin("input.txt", std::ios::in);

	if (!fin.is_open()) {
		std::cout << "Fail to open file!\n";
		return;
	}
	while (!fin.eof()) {
		fin >> aData[index++];
	}

	fin.close();
}

template <class T>
void allocate_data(T*& aData, const int& n) {
	if (aData) return;

	//aData = new (std::nothrow) T[n + 1];
	aData = (T*)malloc(n * sizeof(T) + sizeof(int));

	if (!aData) {
		std::cout << "Fail allocate!\n";
		return;
	}

	aData = data_addr<T>(aData);
	*((int*)origin_addr<T>(aData)) = n;
}

template <class T>
T* free_arr(T*& aData) {
	if (!aData) {
		return nullptr;
	}

	aData = origin_addr(aData);

	//delete[] aData;

	free(aData);

	aData = nullptr;

	return aData;
}

template <class T>
T* resize_arr(T*& aData, const int& newSize) {
	int sizeArr = *((int*)origin_addr<T>(aData));

	if (sizeArr == newSize || aData == nullptr) return aData;

	T* aNew = nullptr;

	allocate_data(aNew, newSize);

	sizeArr = (newSize < sizeArr) ? newSize : sizeArr;

	for (int i = 0; i < sizeArr; i++) {
		aNew[i] = aData[i];
	}

	aData = free_arr<T>(aData);

	return aNew;
}

template <class T>
void delete_pos(T*& aData, int& pos) {
	int sizeArr = *((int*)origin_addr<T>(aData));

	if (pos > sizeArr || pos < 0) {
		system("cls");
		std::cout << "\n\t Invalid pos!\n";
		return;
	}

	for (int i = pos; i < sizeArr - 1; i++) {
		aData[i] = aData[i + 1];
	}

	aData = resize_arr<T>(aData, sizeArr - 1);

	*((int*)origin_addr<T>(aData)) = sizeArr - 1;

	system("cls");
}

template <class T>
void insert_pos_val(T*& aData, int& pos, int& val) {
	int sizeArr = *((int*)origin_addr<T>(aData));

	if (pos > sizeArr || pos < 0) {
		system("cls");
		std::cout << "\n\t Invalid pos!\n";
		return;
	}

	aData = resize_arr<T>(aData, sizeArr + 1);

	for (int i = sizeArr; i > pos; i--) {
		aData[i] = aData[i - 1];
	}
	aData[pos] = val;

	system("cls");
}

template <class T>
void save_file_data(T*& aData) {
	if (!aData) return;

	int n = *((int*)origin_addr<T>(aData));

	std::fstream fout("output.txt", std::ios::trunc | std::ios::out);

	if (!fout.is_open()) {
		std::cout << "Fail to open file!\n";
		return;
	}
	for (int i = 0; i < n; i++) {
		fout << aData[i];

		if (i != (n - 1)) {
			fout << " ";
		}
	}
	system("cls");
}

template <class T>
void current_arr(T*& aData) {
	if (!aData) return;

	int n = *((int*)origin_addr<T>(aData));

	std::cout << "\n\t Current array: ";

	for (int i = 0; i < n; i++) {
		std::cout << aData[i];

		if (i != (n - 1)) {
			std::cout << " ";
		}
	}

	std::cout << "\n";
}

// Những sự kiện được thực hiện sẽ lưu vào đây
template <class T>
void undo_stack(T*& aData, Stack<T>*& undo, Stack<T>*& redo) {
	int sizeStack = *((int*)origin_addr(undo));

	if (sizeStack == 0 || aData == nullptr) {
		system("cls");
		return;
	}

	if (undo[sizeStack - 1].history == delete_action) {
		insert_pos_val(aData, undo[sizeStack - 1].pos, undo[sizeStack - 1].val);
		redo_push(undo[sizeStack - 1], redo);
		undo = resize_arr(undo, sizeStack - 1);
	}
	else {
		delete_pos(aData, undo[sizeStack - 1].pos);
		redo_push(undo[sizeStack - 1], redo);
		undo = resize_arr(undo, sizeStack - 1);
	}
	system("cls");
}

// Lưu những stack được lấy ra khỏi undo
template <class T>
void redo_stack(T*& aData, Stack<T>*& undo, Stack<T>*& redo) {
	int sizeStack = *((int*)origin_addr(redo));

	if (sizeStack == 0 || aData == nullptr) {
		system("cls");
		return;
	}

	if (redo[sizeStack - 1].history == delete_action) {
		delete_pos(aData, redo[sizeStack - 1].pos);
		undo_push(redo[sizeStack - 1], undo);
		redo = resize_arr(redo, sizeStack - 1);
	}
	else {
		insert_pos_val(aData, redo[sizeStack - 1].pos, redo[sizeStack - 1].val);
		undo_push(redo[sizeStack - 1], undo);
		redo = resize_arr(redo, sizeStack - 1);
	}
	system("cls");
}

// Chèn phần undo vừa đc thực hiện vào cuối stack của redo
template <class T>
void redo_push(const Stack<T>& undo, Stack<T>*& redo) {
	int sizeStack = *((int*)origin_addr(redo));

	redo = resize_arr(redo, sizeStack + 1);

	redo[sizeStack] = undo;

}

// Chèn phần hành động vừa đc thực hiện ở menu vào cuối stack của undo
template <class T>
void undo_push(const Stack<T>& redo , Stack<T>*& undo) {
	int sizeStack = *((int*)origin_addr(undo));

	undo = resize_arr(undo, sizeStack + 1);

	undo[sizeStack] = redo;
}

#endif