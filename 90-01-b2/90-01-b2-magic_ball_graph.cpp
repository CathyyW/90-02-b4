/* 2354180 王韵涵 计科 */
#include<iostream>
#include<iomanip>
#include<Windows.h>
#include "90-01-b2-magic_ball.h"
#include "../include/cmd_console_tools.h"
using namespace std;
#include"../include/common_menu.h"
void changeball(int row, int col, char n[][9], int hint[][9])
{
	int i, j;
	char ch;
	

	int x = 2, y = 2;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (hint[i][j] == 2) {
				if (hint[i - 1][j] == 2  && i - 1 >= 0) {
					hint[i - 1][j] = 0, hint[i][j] = 0;
					
					ch = n[i - 1][j];
					n[i - 1][j] = n[i][j];
					n[i][j] = ch;

					cct_showstr(x + j * 4, y + i * 2, "〇", n[i][j], 0);
					cct_showstr(x + j * 4, y + (i-1) * 2, "〇", n[i-1][j], 0);
					
				}
				if (hint[i + 1][j] == 2  && i + 1 < row) {
					hint[i + 1][j] = 0, hint[i][j] = 0;

					ch = n[i+1][j];
					n[i + 1][j] = n[i][j];
					n[i][j] = ch;


					cct_showstr(x + j * 4, y + i * 2, "〇", n[i][j], 0);
					cct_showstr(x + j * 4, y + (i +1) * 2, "〇", n[i + 1][j], 0);
				}
				if (hint[i][j + 1] == 2  && j + 1 < col) {
					hint[i][j+1] = 0, hint[i][j] = 0;

					ch = n[i][j+1];
					n[i][j+1] = n[i][j];
					n[i][j] = ch;


					cct_showstr(x + j * 4, y + i * 2, "〇", n[i][j], 0);
					cct_showstr(x + (j+1) * 4, y + i * 2, "〇", n[i][j+1], 0);
				}
				if (hint[i][j - 1] == 2&& j - 1 >= 0) {
					hint[i][j-1] = 0, hint[i][j] = 0;


					ch = n[i ][j-1];
					n[i ][j-1] = n[i][j];
					n[i][j] = ch;

					cct_showstr(x + j * 4, y + i * 2, "〇", n[i][j], 0);
					cct_showstr(x + (j - 1) * 4, y + i * 2, "〇", n[i][j -1], 0);
				}
			}
		}
	}

	cct_gotoxy(0, y + row * 2 + 1);

	cct_setcolor(0, 7);
}






void fillball(int row, int col, char n[][9], char choice)
{
	int i, j;
	int x, y;
	cct_getxy(x, y);
	x = 2, y = 2;
	cct_gotoxy(x, y);
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (n[i][j] == '0') {
				n[i][j] = (rand() % 9 + 1) + '0';
				Sleep(30);
				cct_showstr(x + j * 4, y + i * 2, "〇", n[i][j], 0);
				
			}
			
		}
	}
	cct_gotoxy(0, y + row * 2 + 1);

	cct_setcolor(0, 7);
}

void Deleteball(int row, int col, char n[][9])
{
	int i, j,t,k;
	int x, y;
	cct_getxy(x, y);
	x = 2, y = 2;
	cct_gotoxy(x, y);
	int b[9][9] = { 0 };
	//bool数组标记
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {

			if (n[i - 1][j] == n[i][j] && i - 1 >= 0 && i + 1 < row && n[i + 1][j] == n[i][j]) {

				b[i - 1][j] = 1, b[i][j] = 1, b[i + 1][j] = 1;
			}
			else if (n[i][j - 1] == n[i][j] && j - 1 >= 0 && j + 1 < row && n[i][j + 1] == n[i][j]) {

				b[i][j - 1] = 1, b[i][j] = 1, b[i][j + 1] = 1;
			}
		}
	}
	//频闪消除并赋值0
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (b[i][j] == 1) {
				
				for (k = 1; k <= 3; k++) {
					cct_showstr(x + j * 4, y + i * 2, "¤", n[i][j], 0);
					Sleep(100);
					cct_showstr(x + j * 4, y + i * 2, "  ", n[i][j], n[i][j]);
				}
				n[i][j] = '0';
				cct_showstr(x + j * 4, y + i * 2, "  ", 15, 15);
			}

		}
	}
	cct_setcolor(0,7);

	
	//改变数组值
	for (j = 0; j < col; j++) {
		for (i = 0; i < row - 1; i++) {
			for (t = 0; t < row - (i + 1); t++) {
				if (n[t + 1][j] == '0' && t + 1 < row&&n[t][j]!='0') {

					n[t + 1][j] = n[t][j];
					n[t][j] = '0';
					//移动
					cct_getxy(x, y);
					x = 2, y = 2;
					x = x + j * 4, y = y + t * 2;
					cct_gotoxy(x, y);
					
					cct_showstr(x , y , "  ", 15, 15);
					cct_showstr(x, y + 1, "〇", n[t + 1][j], COLOR_BLACK);
					Sleep(30);
					cct_showstr(x, y + 1, "═", 15, COLOR_BLACK);
					cct_showstr(x, y + 2, "〇", n[t + 1][j], COLOR_BLACK);
					cct_setcolor(0,7);

				}
			}

		}
	}
	

	cct_gotoxy(0, y + row * 2 );
	
	cct_setcolor(0,7);


}




bool hintball(int row, int col, char n[][9], char choice,int hint[][9])
{
	
	int x, y;
	cct_getxy(x, y);
	x = 2, y = 2;
	cct_gotoxy(x, y);
	int i, j;
	bool c = false;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (hint[i][j] == 1) {
				cct_showstr(x + j * 4, y + i * 2, "〇", n[i][j], 0);
				hint[i][j] = 0;
			}
		}
	}
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (n[i][j - 1] == n[i][j + 1] && n[i][j - 1] == n[i + 1][j] && j - 1 >= 0 && i + 1 < row && j + 1 < col ||  //i,j&i+1,j
				n[i - 1][j] == n[i - 2][j] && n[i - 1][j] == n[i + 1][j] && i - 2 >= 0 && i + 1 < row ||
				n[i][j - 2] == n[i][j - 1] && n[i][j - 2] == n[i + 1][j] && j - 2 >= 0 && i + 1 < row ||
				n[i][j + 2] == n[i][j + 1] && n[i][j + 2] == n[i + 1][j] && j + 2 < col && i + 1 < row) {
				cct_showstr(x + j * 4, y + i * 2, "◎", n[i][j], 0);
				cct_showstr(x + j * 4, y + (i+1) * 2, "◎", n[i+1][j], 0);
				hint[i+1][j] = 1;
				hint[i][j] = 1;
				c = true;
			}
			if (n[i][j + 1] == n[i + 1][j] && n[i][j + 1] == n[i - 1][j] && i - 1 >= 0 && j + 1 < col ||  //i,j&i,j+1
				n[i][j + 1] == n[i][j - 1] && n[i][j + 1] == n[i][j - 2] && j - 2 >= 0 && j + 1 < col ||
				n[i][j + 1] == n[i - 1][j] && n[i][j + 1] == n[i - 2][j] && i - 2 >= 0 && j + 1 < col ||
				n[i][j + 1] == n[i + 1][j] && n[i][j + 1] == n[i + 2][j] && j + 1 < col && i + 2 < row) {
				cct_showstr(x + j * 4, y + i * 2, "◎", n[i][j], 0);
				cct_showstr(x + (j+1) * 4, y + i * 2, "◎", n[i][j+1], 0);
				hint[i][j] = 1;
				hint[i][j+1] = 1;
				c = true;
			}
			if (n[i][j - 1] == n[i + 1][j] && n[i][j - 1] == n[i - 1][j] && i - 1 >= 0 && i + 1 < row && j - 1 >= 0 ||  //i,j&i,j-1
				n[i][j - 1] == n[i][j + 1] && n[i][j - 1] == n[i][j + 2] && j - 1 >= 0 && j + 2 < col ||
				n[i][j - 1] == n[i - 1][j] && n[i][j - 1] == n[i - 2][j] && i - 2 >= 0 && j - 1 >= 0 ||
				n[i][j - 1] == n[i + 1][j] && n[i][j - 1] == n[i + 2][j] && j - 1 >= 0 && i + 2 < row) {
				cct_showstr(x + j * 4, y + i * 2, "◎", n[i][j], 0);
				cct_showstr(x + (j-1) * 4, y + i* 2, "◎", n[i][j-1], 0);
				hint[i][j] = 1;
				hint[i][j-1] = 1;
				c = true;
			}
			if (n[i - 1][j] == n[i][j + 1] && n[i - 1][j] == n[i][j - 1] && i - 1 >= 0 && j + 1 < col && j - 1 >= 0 ||  //i,j&i-1,j
				n[i - 1][j] == n[i + 1][j] && n[i - 1][j] == n[i + 2][j] && i - 1 >= 0 && i + 2 < row ||
				n[i - 1][j] == n[i][j - 1] && n[i - 1][j] == n[i][j - 2] && j - 2 >= 0 && i - 1 >= 0 ||
				n[i - 1][j] == n[i][j + 1] && n[i - 1][j] == n[i][j + 2] && i - 1 >= 0 && j + 2 < col) {
				cct_showstr(x + j * 4, y + i * 2, "◎", n[i][j], 0);
				cct_showstr(x + j * 4, y + (i - 1) * 2, "◎", n[i - 1][j], 0);
				hint[i -1][j] = 1;
				hint[i][j] = 1;
				c = true;
			}
		}
	}

	cct_gotoxy(0, y + row *2);
	cct_setcolor(0,7);
	return c;
}

void note0(int row, int col, char n[][9], char choice)
{
	int x, y;
	int i, j;
	cct_getxy(x, y);
	x = 2, y = 2;
	cct_gotoxy(x, y);
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			
			if (n[i - 1][j] == n[i][j] && i - 1 >= 0 && n[i + 1][j] == n[i][j]&&i+1<row) {
				if (choice == '6') {
					cct_showstr(x + j * 2, y + i, "●", n[i][j], 0);
					cct_showstr(x + j * 2, y + (i - 1), "●", n[i - 1][j], 0);
					cct_showstr(x + j * 2, y + (i + 1), "●", n[i + 1][j], 0);
				}
				if (choice == '7'||choice=='8'||choice=='9') {
					cct_showstr(x + j * 4, y + i*2, "●", n[i][j], 0);
					cct_showstr(x + j * 4, y + (i - 1)*2, "●", n[i - 1][j], 0);
					cct_showstr(x + j * 4, y + (i + 1)*2, "●", n[i + 1][j], 0);
				}


			}
			else if (n[i][j - 1] == n[i][j] && j - 1 >= 0 && n[i][j + 1] == n[i][j]&&j+1<col) {
				if (choice == '6') {
					cct_showstr(x + j * 2, y + i, "●", n[i][j], 0);
					cct_showstr(x + (j - 1) * 2, y + i, "●", n[i][j - 1], 0);
					cct_showstr(x + (j + 1) * 2, y + i, "●", n[i][j + 1], 0);
				}
				if (choice == '7'||choice=='8'||choice=='9') {
					cct_showstr(x + j * 4, y + i*2, "●", n[i][j], 0);
					cct_showstr(x + (j - 1) * 4, y + i*2, "●", n[i][j - 1], 0);
					cct_showstr(x + (j + 1) * 4, y + i*2, "●", n[i][j + 1], 0);
				}

			}
		}
	}
	cct_setcolor(0,7);

	if (choice == '6') {
		cct_gotoxy(0, y + row + 1);
	}
	if (choice == '7') {
		cct_gotoxy(0, y + row *2);
	}
	


}


bool searchball0(int row, int col, char n[][9], char choice)
{
	int i, j;

	bool b = false;
	

	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {

			if (n[i - 1][j] == n[i][j] && i - 1 >= 0 && n[i + 1][j] == n[i][j]&&i+1<row) {
				
				b = true;
			}
			else if (n[i][j - 1] == n[i][j] && j - 1 >= 0 && n[i][j + 1] == n[i][j]&&j+1<col) {
				b = true;
			}
		}
	}
	
	return b;
}
void printball(int row, int col, char n[][9],char choice)
{
	
	int i, j;
	int x=2, y=2;
	
	cct_gotoxy(x, y);
	
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if(choice=='4'||choice=='6')
				cct_showstr(x + j * 2, y + i, "〇", n[i][j], 0);
			if(choice=='5'||choice=='7'||choice=='8'||choice=='9')
				cct_showstr(x + j * 4, y + i*2, "〇", n[i][j], 0);
		}
	}
	cct_setcolor(0,7);
	
	cct_getxy(x, y);
	cct_gotoxy(0, y + 2);
	
}



void printgraph(int row, int col, char n[][9],char choice)
{
	int i, j;
	int x, y;
	cct_setfontsize("新宋体", 40);
	if (choice == '4'||choice=='6') {
		cct_setconsoleborder(40, row + 8, 120, 150);
		cout << "屏幕：" << row + 8 << "行" << 40 << "列" << endl;
	}
	if (choice == '5'||choice=='7'||choice=='8'||choice=='9') {
		cct_setconsoleborder(40, row + 14, 120, 150);
		cout << "屏幕：" << row + 14 << "行" << 40 << "列" << endl;
	}
	cct_setcolor(15, 0);//背景亮白，前景黑
	//第一行
	cct_getxy(x,y);
	cct_showstr(x, y, "╔", COLOR_HWHITE, COLOR_BLACK);
	for (j = 0;j<col; j++) {
		Sleep(30);
		cct_getxy(x, y);
		cct_showstr(x, y, "═", COLOR_HWHITE, COLOR_BLACK);
		
		if ((choice == '5'||choice=='7'||choice=='8'||choice=='9') && j != col - 1) {
			cct_getxy(x, y);
			cct_showstr(x, y, "╦", COLOR_HWHITE, COLOR_BLACK);
			
		}
	}
	cct_getxy(x, y);
	cct_showstr(x, y, "╗", COLOR_HWHITE, COLOR_BLACK);
	cout << endl;

	//中间几行
	if (choice == '4'||choice=='6') {
		for (i = 0; i < row; i++) {
			cct_getxy(x, y);
			cct_showstr(x, y, "║", COLOR_HWHITE, COLOR_BLACK);
			
			cct_setcolor(0,7);
			for (j = 0; j < col * 2; j++) {

				cout << " ";
			}
			cct_setcolor(15, 0);//背景白，前景黑
			cct_getxy(x, y);
			cct_showstr(x, y, "║", COLOR_HWHITE, COLOR_BLACK);
			cout<<endl;
		}
	}
	if (choice == '5'||choice=='7'||choice=='8'||choice=='9') {
		for (i = 0; i < row-1; i++) {
			for (j = 0; j < col; j++) {
				cct_getxy(x, y);
				cct_showstr(x, y, "║  ", COLOR_HWHITE, COLOR_BLACK);
			}
			cct_getxy(x, y);
			cct_showstr(x, y, "║", COLOR_HWHITE, COLOR_BLACK);
			cout << endl;

			cct_getxy(x, y);
			cct_showstr(x, y, "╠", COLOR_HWHITE, COLOR_BLACK);
	
			for (j = 0; j < col-1; j++) {
				cct_getxy(x, y);
				cct_showstr(x, y, "═╬", COLOR_HWHITE, COLOR_BLACK);
	
			}
			cct_getxy(x, y);
			cct_showstr(x, y, "═╣", COLOR_HWHITE, COLOR_BLACK);
			cout << endl;
			
		}
		for (j = 0; j < col; j++) {
			cct_getxy(x, y);
			cct_showstr(x, y, "║  ", COLOR_HWHITE, COLOR_BLACK);
		}
		cct_getxy(x, y);
		cct_showstr(x, y, "║", COLOR_HWHITE, COLOR_BLACK);
		cout << endl;
	}
	//最后一行
	cct_getxy(x, y);
	cct_showstr(x, y, "╚", COLOR_HWHITE, COLOR_BLACK);
	
	for (j = 0; j < col; j++) {
		Sleep(30);
		cct_getxy(x, y);
		cct_showstr(x, y, "═", COLOR_HWHITE, COLOR_BLACK);
		if ((choice == '5' ||choice=='7'||choice=='8'||choice=='9') && j != col - 1) {
			cct_getxy(x, y);
			cct_showstr(x, y, "╩", COLOR_HWHITE, COLOR_BLACK);
		}
	}
	cct_getxy(x, y);
	cct_showstr(x, y, "╝", COLOR_HWHITE, COLOR_BLACK);
	cout << endl;
	
	
	cct_setcolor(0,7);
	

}