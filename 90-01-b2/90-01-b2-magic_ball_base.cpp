/* 2354180 王韵涵 计科 */
#include<iostream>
#include<iomanip>
#include "90-01-b2-magic_ball.h"
#include "../include/cmd_console_tools.h"
using namespace std;
#include"../include/common_menu.h"
#include"../include/common_tools.h"

void hint(int row, int col, char n[][9])//先画再标记
{
	int x, y;
	cout << "可选择的消除提示（不同色标识）：" << endl;
	printbase(row, col, n[0],1);
	cct_getxy(x, y);
	y = y - row;
	x = x + 5;
	int i, j;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (n[i][j - 1] == n[i][j + 1] && n[i][j - 1] == n[i + 1][j] && j - 1 >= 0 && i + 1 < row && j + 1 < col ||  //i,j&i+1,j
				n[i - 1][j] == n[i - 2][j] && n[i - 1][j] == n[i + 1][j] && i - 2 >= 0 && i + 1 < row ||
				n[i][j - 2] == n[i][j - 1] && n[i][j - 2] == n[i + 1][j] && j - 2 >= 0 && i + 1 < row ||
				n[i][j + 2] == n[i][j + 1] && n[i][j + 2] == n[i + 1][j] && j + 2 < col && i + 1 < row) {
				cct_showch(x + j * 3, y + i, n[i][j], 14, 1);
				cct_showch(x + j * 3, y + i+1, n[i+1][j], 14, 1);
			}
			if (n[i][j + 1] == n[i+1][j] && n[i][j + 1] == n[i -1][j] && i - 1 >= 0 &&j + 1 < col ||  //i,j&i,j+1
				n[i][j+1] == n[i ][j-1] && n[i][j+1] == n[i ][j-2] && j - 2 >= 0 && j+ 1 < col ||
				n[i][j+1] == n[i-1][j] && n[i][j+1] == n[i -2][j] && i - 2 >= 0 && j + 1 < col ||
				n[i][j +1] == n[i+1][j] && n[i][j + 1] == n[i+2][j] && j + 1 < col && i + 2 < row) {
				cct_showch(x + j * 3, y + i, n[i][j], 14, 1);
				cct_showch(x + (j+1) * 3, y + i , n[i][j+1], 14, 1);
			}
			if (n[i][j - 1] == n[i + 1][j] && n[i][j - 1] == n[i - 1][j] && i - 1 >= 0 && i + 1 < row&&j-1>=0 ||  //i,j&i,j-1
				n[i][j - 1] == n[i][j + 1] && n[i][j - 1] == n[i][j +2] && j - 1 >= 0 && j + 2< col ||
				n[i][j -1] == n[i - 1][j] && n[i][j - 1] == n[i - 2][j] && i - 2 >= 0 && j -1>=0 ||
				n[i][j - 1] == n[i + 1][j] && n[i][j - 1] == n[i + 2][j] && j -1>=0 && i + 2 < row) {
				cct_showch(x + j * 3, y + i, n[i][j], 14, 1);
				cct_showch(x + (j - 1) * 3, y + i, n[i][j - 1], 14, 1);
			}
			if (n[i-1][j] == n[i][j+1] && n[i-1][j] == n[i][j-1] && i - 1 >= 0 && j+1<col&& j - 1 >= 0 ||  //i,j&i-1,j
				n[i-1][j] == n[i+1][j ] && n[i-1][j] == n[i+2][j ] && i - 1 >= 0 && i + 2 <row ||
				n[i-1][j] == n[i][j-1] && n[i-1][j] == n[i][j-2] && j - 2 >= 0 && i - 1 >= 0 ||
				n[i-1][j] == n[i ][j+1] && n[i-1][j] == n[i ][j+2] && i- 1 >= 0 && j + 2 <col) {
				cct_showch(x + j * 3, y + i, n[i][j], 14, 1);
				cct_showch(x + j * 3, y + i-1, n[i-1][j], 14, 1);
			}
		}
	}
	
	cct_gotoxy(0, y + row + 1);
	cct_setcolor();
}


void printfill(int row, int col, char n[][9]) // 边画边标记
{
	int i, j;
	int x, y;
	cout << "  |";
	for (i = 1; i <= col; i++) {
		cout << "  " << i;
	}
	cout << endl << "--+";
	cout << setfill('-') << setw(col * 3 + 1) << "" << endl;
	for (i = 0; i < row; i++) {
		cout << char('A' + i) << " |";
		for (j = 0; j < col; j++) {
			if (n[i][j] == '0') {
				cout << "  ";
				cct_getxy(x, y);
				n[i][j] = (rand() % 9 + 1) + '0';
				cct_showch(x, y, n[i][j], 14, 1);
				cct_setcolor();
			}
			else
				cout << "  " << n[i][j];

		}
		cout << endl;
	}
}



bool search0(int row, int col, char n[][9])//先画再标记
{
	int i, j;
	int x, y;
	bool b = false;

	cout << "按回车键进行寻找初始可消除项的操作...";
	while (getchar() != '\n') {
	}
	cout << endl;
	
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {

			if (n[i - 1][j] == n[i][j] && i - 1 >= 0 && n[i + 1][j] == n[i][j]) {
				b = true;
			}
			else if (n[i][j - 1] == n[i][j] && j - 1 >= 0 && n[i][j + 1] == n[i][j]) {
				b = true;
			}


		}
	}
	if (b) {
		cout << "初始可消除项（不同色标识）：" << endl;
		printbase(row, col, n[0],1);
		cct_getxy(x, y);
		y = y - row;
		x = x + 5;
		for (i = 0; i < row; i++) {
			for (j = 0; j < col; j++) {

				if (n[i - 1][j] == n[i][j] && i - 1 >= 0 &&i+1<row&& n[i + 1][j] == n[i][j]) {

					cct_showch(x + j * 3, y + i - 1, n[i - 1][j], 14, 1);
					cct_showch(x + j * 3, y + i, n[i][j], 14, 1);
					cct_showch(x + j * 3, y + i + 1, n[i + 1][j], 14, 1);
					
				}
				else if (n[i][j - 1] == n[i][j] && j - 1 >= 0 &&j+1<row&& n[i][j + 1] == n[i][j]) {

					cct_showch(x + (j - 1) * 3, y + i, n[i][j - 1], 14, 1);
					cct_showch(x + j * 3, y + i, n[i][j], 14, 1);
					cct_showch(x + (j + 1) * 3, y + i, n[i][j + 1], 14, 1);
				
				}

			}
		}
		cct_gotoxy(0, y+row+1);
	}
	
	else
		cout << "初始已无可消除项" << endl;
	cct_setcolor();
	return b;
}
void Delete(int row, int col, char n[][9])
{
	int i, j,k=0;

	int b[9][9] = {0};
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {

			if (n[i - 1][j] == n[i][j] && i - 1 >= 0 && i + 1 < row && n[i + 1][j] == n[i][j]) {
				
				b[i - 1][j] = 1, b[i][j] = 1, b[i + 1][j] = 1;
			}
			else if (n[i][j - 1] == n[i][j] && j - 1 >= 0 && j + 1 < row && n[i][j + 1] == n[i][j]) {

				b[i][j-1] = 1, b[i][j] = 1, b[i][j+1] = 1;
			}

		}
	}
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			if (b[i][j] == 1)
				n[i][j] = '0';
		}
	}

	
}