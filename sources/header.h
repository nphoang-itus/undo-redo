#pragma once
#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>

extern int headsize;

enum Action {
	delete_action, insert_action
};

template <class T>
struct Stack {
	Action history;
	int pos;
	T val;
};

void menu();

template <class T>
void undo_push(const Stack<T>& redo, Stack<T>*& undo);

template <class T>
void redo_push(const Stack<T>& undo, Stack<T>*& redo);

template <class T>
void redo_stack(T*& aData, Stack<T>*& undo, Stack<T>*& redo);

template <class T>
void undo_stack(T*& aData, Stack<T>*& undo, Stack<T>*& redo);

template <class T>
void current_arr(T*& aData);

template <class T>
T* origin_addr(T*& aData);

template <class T>
T* data_addr(T*& aOrigin);

int size_file_data();

template <class T>
void read_data(T*& aData);

template <class T>
void allocate_data(T*& aData, const int& n);

template <class T>
T* free_arr(T*& aData);

template <class T>
T* resize_arr(T*& aData, const int& newSize);

template <class T>
void delete_pos(T*& aData, int& pos);

template <class T>
void insert_pos_val(T*& aData, int& pos, int& val);

template <class T>
void save_file_data(T*& aData);

void input_pos(const int& n, int& pos);

void input_pos_and_val(const int& n, int& pos, int& val);

void input_checking(int& num);

#endif
