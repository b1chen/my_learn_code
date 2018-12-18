#pragma once
#include "stdafx.h"
#include <iostream>
#include<stdlib.h>
#include <time.h>

#define HORIZONTAL 14
#define VERTICAL 20
//
class Cell {
public:
	int get_col() { return col; }
	int get_row() { return row; }
	bool get_is_used() { return is_used; }
	void set_is_used(bool use_flag) { is_used = use_flag; }
	void set_col(int col) { this->col = col; }
	void set_row(int row) { this->row = row; }
	void up() {
		row--;
	}
	void drop() { 
		row++; 
		//row = row % 20;
	}
	void moveleft() { col--; }
	void moveright() { col++; }
	void cell_coordinate() {
		std::cout << "(col, row) = (" << col << ", " << row << ")" << std::endl;
	}
	Cell(int row, int col) { this->col = col; this->row = row; is_used = false; }
	Cell() { col = -1; row = -1; is_used = false; }
private:
	int col;
	int row;
	bool is_used;
};

class State {
public:
	int row0;
	int col0;
	int row1;
	int col1;
	int row2;
	int col2;
	int row3;
	int col3;
	State(int row0, int col0, int row1, int col1, int row2, int col2, int row3, int col3) {
		this->row0 = row0;
		this->col0 = col0;
		this->row1 = row1;
		this->col1 = col1;
		this->row2 = row2;
		this->col2 = col2;
		this->row3 = row3;
		this->col3 = col3;
	}
	State() {}
};

//公共block基类
class General_block {
public:
	unsigned int block_idx;
	Cell cells[4];
	State states[4];
private:
	int cell_num_in_block() {
		return sizeof(cells) / sizeof(cells[0]);
	}
public:
	bool coincide();
	bool is_out_of_bound();
	bool can_drop();
	General_block() { block_idx = 0; }
	void move_up() {
		for (int ix = 0; ix < cell_num_in_block(); ix++) {
			cells[ix].up();
		}
	}
	void move_down() {
		for (int ix = 0; ix < cell_num_in_block(); ix++) {
			cells[ix].drop();
		}
	}
	void move_left() {
		for (int ix = 0; ix < cell_num_in_block(); ix++) {
			cells[ix].moveleft();
		}
	}
	void move_right() {
		for (int ix = 0; ix < cell_num_in_block(); ix++) {
			cells[ix].moveright();
		}
	}
	void rotate_left() {
		block_idx = (--block_idx) % 4;
		int row = cells[0].get_row();
		int col = cells[0].get_col();
		cells[1].set_row(states[block_idx].row1 + row);
		cells[1].set_col(states[block_idx].col1 + col);
		cells[2].set_row(states[block_idx].row2 + row);
		cells[2].set_col(states[block_idx].col2 + col);
		cells[3].set_row(states[block_idx].row3 + row);
		cells[3].set_col(states[block_idx].col3 + col);
	}
	void rotate_right() {
		block_idx = (++block_idx) % 4;
		int row = cells[0].get_row();
		int col = cells[0].get_col();
		cells[1].set_row(states[block_idx].row1 + row);
		cells[1].set_col(states[block_idx].col1 + col);
		cells[2].set_row(states[block_idx].row2 + row);
		cells[2].set_col(states[block_idx].col2 + col);
		cells[3].set_row(states[block_idx].row3 + row);
		cells[3].set_col(states[block_idx].col3 + col);
	}

};

class T_block : public General_block {
public:
	T_block(){
		cells[0] = Cell(0, 4);//原点
		cells[1] = Cell(0, 3);
		cells[2] = Cell(0, 5);
		cells[3] = Cell(1, 4);
		states[0] = State(0, 0, 0, -1, 0, 1, 1, 0);
		states[1] = State(0, 0, -1, 0, 1, 0, 0, -1);
		states[2] = State(0, 0, 0, 1, 0, -1, -1, 0);
		states[3] = State(0, 0, 1, 0, -1, 0, 0, 1);
	}
};

class L_block : public General_block {
public:
	L_block() {
		cells[0] = Cell(0, 4);
		cells[1] = Cell(0, 3);
		cells[2] = Cell(0, 5);
		cells[3] = Cell(1, 3);
		states[0] = State(0, 0, 0, -1, 0, 1, 1, -1);
		states[1] = State(0, 0, -1, 0, 1, 0, -1, -1);
		states[2] = State(0, 0, 0, 1, 0, -1, -1, 1);
		states[3] = State(0, 0, 1, 0, -1, 0, 1, 1);
	}
};

class I_block : public General_block {
public:
	I_block() {
		cells[0] = Cell(0, 4);
		cells[1] = Cell(0, 3);
		cells[2] = Cell(0, 5);
		cells[3] = Cell(0, 6);
		states[0] = State(0, 0, 0, 1, 0, -1, 0, -2);
		states[1] = State(0, 0, -1, 0, 1, 0, 2, 0);
		states[2] = State(0, 0, 0, 1, 0, -1, 0, -2);
		states[3] = State(0, 0, -1, 0, 1, 0, 2, 0);
	}
};


class S_block : public General_block {
public:
	S_block() {
		cells[0] = Cell(0, 4);
		cells[1] = Cell(0, 5);
		cells[2] = Cell(1, 3);
		cells[3] = Cell(1, 4);
		states[0] = State(0, 0, 0, 1, 1, -1, 1, 0);
		states[1] = State(0, 0, -1, 0, 1, 1, 0, 1);
		states[2] = State(0, 0, 0, 1, 1, -1, 1, 0);
		states[3] = State(0, 0, -1, 0, 1, 1, 0, 1);
	}
};

class Z_block : public General_block {
public:
	Z_block() {
		cells[0] = Cell(1, 4);
		cells[1] = Cell(0, 3);
		cells[2] = Cell(0, 4);
		cells[3] = Cell(1, 5);
		states[0] = State(0, 0, -1, -1, -1, 0, 0, 1);
		states[1] = State(0, 0, -1, 1, 0, 1, 1, 0);
		states[2] = State(0, 0, -1, -1, -1, 0, 0, 1);
		states[3] = State(0, 0, -1, 1, 0, 1, 1, 0);
	}
};

class J_block : public General_block {
public:
	J_block() {
		cells[0] = Cell(0, 4);
		cells[1] = Cell(0, 3);
		cells[2] = Cell(0, 5);
		cells[3] = Cell(1, 5);
		states[0] = State(0, 0, 0, -1, 0, 1, 1, 1);
		states[1] = State(0, 0, -1, 0, 1, 0, 1, -1);
		states[2] = State(0, 0, 0, 1, 0, -1, -1, -1);
		states[3] = State(0, 0, 1, 0, -1, 0, -1, 1);
	}
};

class O_block : public General_block {
public:
	O_block() {
		cells[0] = Cell(0, 4);
		cells[1] = Cell(0, 5);
		cells[2] = Cell(1, 4);
		cells[3] = Cell(1, 5);
		states[0] = State(0, 0, 0, 1, 1, 0, 1, 1);
		states[1] = State(0, 0, 0, 1, 1, 0, 1, 1);
		states[2] = State(0, 0, 0, 1, 1, 0, 1, 1);
		states[3] = State(0, 0, 0, 1, 1, 0, 1, 1);
	}
};


//

class Map {
public:
	static int score;
	static int level;
	static int timer_flag;
	static int gameover;
	static General_block *current_block;
	static General_block *next_block;
	static Cell map_cells[VERTICAL][HORIZONTAL];
	static bool cur_block_exist;
	static std::vector<int> detect_full_lines();
	static void update_map(std::vector<int> full_lines_num);
	static int get_replace_row(int last_rep_row);
	static void replace_line(int row, int rep_row);
	static void paint_map(HDC hdc, HPEN hpen) {

		HBRUSH hbrush = CreateSolidBrush(RGB(255, 255, 255)); //定义画刷并赋初值，画刷颜色采用背景色
		HBRUSH hbrush_wall = CreateSolidBrush(FgColor);
		SelectObject(hdc, hpen); //重新选择画笔
								 //SelectObject(hdc, hbrush); //选择画刷
		for (int ix = 0; ix < VERTICAL; ix++) {
			for (int iy = 0; iy < HORIZONTAL; iy++) {
				if (map_cells[ix][iy].get_is_used() == true) {
					SelectObject(hdc, hbrush_wall);
					Rectangle(hdc, (iy)*BSIZE + 5, (ix)*BSIZE + 5, (iy + 1)*BSIZE + 5, (ix + 1)*BSIZE + 5);
				}
				else {
					SelectObject(hdc, hbrush);
					Rectangle(hdc, (iy)*BSIZE + 5, (ix)*BSIZE + 5, (iy + 1)*BSIZE + 5, (ix + 1)*BSIZE + 5);
				}
			}
		}

		//draw next block
		SelectObject(hdc, hbrush);
		for (int ix = 0; ix < 6; ix++) {
			for (int iy = 1; iy < 7; iy++) {
				Rectangle(hdc, (14+iy)*BSIZE + 10, (ix)*BSIZE + 5, (14 + iy +1)*BSIZE + 10, (ix + 1)*BSIZE + 5);
			}
		}
		DeleteObject(hpen);
		DeleteObject(hbrush); //删除画刷
		DeleteObject(hbrush_wall); //删除画刷
	}

	static void paint_block(HDC hdc, HPEN hpen, General_block block) {
		HBRUSH hbrush_block = CreateSolidBrush(RGB(255, 255, 0));
		SelectObject(hdc, hpen); //重新选择画笔
		SelectObject(hdc, hbrush_block);
		for (int ix = 0; ix < 4; ix++) {
			Rectangle(hdc, (block.cells[ix].get_col())*BSIZE + 5, (block.cells[ix].get_row())*BSIZE + 5, (block.cells[ix].get_col() + 1)*BSIZE + 5, (block.cells[ix].get_row() + 1)*BSIZE + 5);
		}
		DeleteObject(hpen);
		DeleteObject(hbrush_block); //删除画刷
	}
	static void paint_next_block(HDC hdc, HPEN hpen, General_block block) {
		HBRUSH hbrush_block = CreateSolidBrush(RGB(255, 255, 0));
		SelectObject(hdc, hpen); //重新选择画笔
		SelectObject(hdc, hbrush_block);
		for (int ix = 0; ix < 4; ix++) {
			Rectangle(hdc, (block.cells[ix].get_col() + 14)*BSIZE + 5, (block.cells[ix].get_row())*BSIZE + 5, (block.cells[ix].get_col() + 1 + 14)*BSIZE + 5, (block.cells[ix].get_row() + 1)*BSIZE + 5);
		}
		DeleteObject(hpen);
		DeleteObject(hbrush_block); //删除画刷
	}

	static void set_block_to_map(General_block block) {
		for (int ix = 0; ix < 4; ix++) {
			int row = block.cells[ix].get_row();
			int col = block.cells[ix].get_col();
			map_cells[row][col].set_col(col);
			map_cells[row][col].set_row(row);
			map_cells[row][col].set_is_used(true);
		}
	}

	static General_block * RandomOne() {
		int item_idx = rand() % 7;
		switch (item_idx) {
		case 0:
			return new T_block();
		case 1:
			return new L_block();
		case 2:
			return new S_block();
		case 3:
			return new I_block();
		case 4:
			return new O_block();
		case 5:
			return new J_block();
		case 6:
			return new Z_block();
		default:
			return new T_block();
		}
	}
};
Cell Map::map_cells[VERTICAL][HORIZONTAL];
int Map::timer_flag = 0;
int Map::gameover = 0;
General_block *Map::current_block =nullptr;
General_block *Map::next_block = nullptr;
bool Map::cur_block_exist = false;
int Map::score = 0;
int Map::level = 1;
bool General_block::is_out_of_bound() {
	for (int ix = 0; ix < cell_num_in_block(); ix++) {
		if (cells[ix].get_col() < 0 || cells[ix].get_col() > (HORIZONTAL - 1)) {
			return true;
		}
	}
	return false;
}

bool General_block::coincide() {
	for (int ix = 0; ix < cell_num_in_block(); ix++) {
		int col = cells[ix].get_col();
		int row = cells[ix].get_row();
		if (col >= 0 && col < HORIZONTAL && row >= 0 && row < VERTICAL && (Map::map_cells[row][col].get_is_used() == true)) {
			return true;
		}
	}
	return false;
}

bool General_block::can_drop() {
	for (int ix = 0; ix < cell_num_in_block(); ix++) {
		int row = cells[ix].get_row();
		if (row == VERTICAL - 1) {
			return false;
		}
	}

	for (int ix = 0; ix < cell_num_in_block(); ix++) {
		int col = cells[ix].get_col();
		int row = cells[ix].get_row();
		if (Map::map_cells[row+1][col].get_is_used() == true) {
			return false;
		}
	}
	return true;
}


std::vector<int> Map::detect_full_lines() {
	std::vector<int> ivec;
	for (int row = 19; row >= 0; row--) {
		bool full_line = true;
		for (int col = 0; col < 14; col++) {
			if (map_cells[row][col].get_is_used() == false) {
				full_line = false;
				break;
			}
		}
		if (full_line == true) {
			ivec.push_back(row);
		}
	}
	return ivec;
}

int Map::get_replace_row(int last_rep_row) {
	//int smallest_full_line_num = full_lines_num[full_lines_num.size() - 1];
	if (last_rep_row == 0) return 0xff;
	for (int row = last_rep_row - 1; row >= 0; row--) {
		for (int col = 0; col < 14; col++) {
			if (map_cells[row][col].get_is_used() == false) {
				return row;
			}
		}
	}
}

void Map::replace_line(int row, int rep_row) {
	if (rep_row != 0xff) {
		for (int col = 0; col < 14; col++) {
			map_cells[row][col].set_col(col);
			map_cells[row][col].set_row(row);
			map_cells[row][col].set_is_used(map_cells[rep_row][col].get_is_used());
		}
	}
	else {
		for (int col = 0; col < 14; col++) {
			map_cells[row][col].set_col(-1);
			map_cells[row][col].set_row(-1);
			map_cells[row][col].set_is_used(false);
		}
	}
}

void Map::update_map(std::vector<int> full_lines_num) {
	if (full_lines_num.empty()) return;
	int biggest_full_line_num = full_lines_num[0];
	int smallest_full_line_num = full_lines_num[full_lines_num.size() - 1];
	int last_rep_row = biggest_full_line_num;
	for (int row = biggest_full_line_num; row >= 0; row--) {
		int rep_row = get_replace_row(last_rep_row);
		if (!(rep_row == 0xff))
			last_rep_row = rep_row;
		else {
			last_rep_row = 0;
		}
		replace_line(row, rep_row);
	}
	Map::score += full_lines_num.size() * 10;
	switch (full_lines_num.size()) {
	case 4 :
		Map::score += 40; break;
	case 3:
		Map::score += 30; break;
	case 2:
		Map::score += 20; break;
	default:
		break;
	}
}