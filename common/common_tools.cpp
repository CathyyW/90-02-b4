/* 2354180 王韵涵 计科 */
#include<iostream>
#include<iomanip>
#include<conio.h>
#include "../include/cmd_gmw_tools.h"
#include "../include/cmd_console_tools.h"
#include"../include/common_tools.h"

using namespace std;        

void input(int* row, int* col, char *str,int program)
{

	int i, j;
	srand((unsigned int)(time(0))); //生成种子
	while (1) {
		if(program==1)
			cout << "请输入行数（5-9）：" << endl;
		if(program==2)
			cout << "请输入行数（8-10）：" << endl;

		cin >> *row;
	

		if (*row >= 5 && *row <= 9&&program==1)
			break;
		if (*row >= 8 && *row <= 10 && program == 2)
			break;

	}

	while (1) {
		if (program == 1)
			cout << "请输入列数（5-9）：" << endl;
		if (program == 2)
			cout << "请输入列数（8-10）：" << endl;
		cin >> *col;
	

		if (*col >= 5 && *col <= 9 && program == 1)
			break;
		if (*col >= 8 && *col <= 10 && program == 2)
			break;
	}
	for (i = 0; i < *row; i++) {
		for (j = 0; j < *col; j++) {
			if(program==1)
				str[i * 9 + j] = (rand() % 9 + 1) + '0';
			if(program==2)
				str[i * 10 + j] = (rand() % 5 + 1) + '0';

		}
	}
	cout << endl;

}
void printbase(int row, int col, char *str,int program) //边画边标记
{
	int i, j;
	int x, y;
	cout << "  |";
	if (program == 1) {
		for (i = 1; i <= col; i++) {
			cout << "  " << i;
		}
	}
	if (program == 2) {
		for (i = 0; i <= col-1; i++) {
			cout << "  " << i;
		}
	}
	cout << endl << "--+";
	cout << setfill('-') << setw(col * 3 + 1) << "" << endl;
	for (i = 0; i < row; i++) {
		cout << char('A' + i) << " |";
		for (j = 0; j < col; j++) {
			if (program == 1) {

				if (str[i * 9 + j] == '0') {
					cout << "  ";
					cct_getxy(x, y);
					cct_showch(x, y, str[i * 9 + j], 14, 1);
					cct_setcolor();
				}
				else 
					cout << "  " << str[i * 9 + j];
				
			}
			if (program == 2) {
				if (str[i *10 + j] == '0') {
					cout << "  ";
					cct_getxy(x, y);
					cct_showch(x, y, str[i * 10 + j], 14, 1);
					cct_setcolor();
				}
				else
					cout << "  " << str[i *10 + j];
			}
		}
		cout << endl;
	}
}
void end()
{
	int x, y;
	char b[] = "end";

	cct_getxy(x, y);
	cout << "                                                       ";
	cct_gotoxy(x, y);
	cout << "本小题结束，请输入End继续...";

	while (1) {
		char a[20] = { 0 };
		cin >> a;
		if (tj_strcasencmp(a, b, 3) == 0) {
			cct_cls();
			break;


		}
		else {
			cct_gotoxy(28, y);
			cout << "   ";
			cct_gotoxy(28, y);
		}

	}


}
int tj_strcasencmp(const char* s1, const char* s2, const int len)
{
	/* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
	const char* p1 = s1, * p2 = s2;
	int ret = 0;

	if (s1 != NULL && s2 == NULL) {
		return 1;
	}
	else if (s2 != NULL && s1 == NULL) {
		return -1;
	}
	else if (s1 == NULL && s2 == NULL) {
		return 0;
	}
	else {
		for (; *s1 && *s2 && s1 - p1 < len && s2 - p2 < len; s1++, s2++) {

			if ((*s1 >= 'A' && *s1 <= 'Z')) {
				if (*s1 + 32 == *s2)
					continue;
				else
					return (*s1 + 32) - *s2;
			}
			else if ((*s2 >= 'A' && *s2 <= 'Z')) {
				if (*s2 + 32 == *s1)
					continue;
				else
					return *s1 - (32 + *s2);
			}

			else {
				if (*s1 != *s2) {
					return *s1 - *s2;
				}
			}


		}
	}
	return (s1 - p1 >= len) ? 0 : (*s1 - *s2);

}

void refreshdown(int row, int col, char* str, int program)
{
	int i, j, t;
	for (j = 0; j < col; j++) {
		for (i = 0; i < row - 1; i++) {
			for (t = 0; t < row - (i + 1); t++) {
				if (program == 2) {
					if (str[(t + 1) * 10 + j] == '0' && t + 1 < row) {

						str[(t + 1) * 10 + j] = str[t * 10 + j];
						str[t * 10 + j] = '0';
					}
				}
				if (program == 1||program==3) {
					if (str[(t + 1) * 9 + j] == '0' && t + 1 < row) {

						str[(t + 1) * 9 + j] = str[t * 9 + j];
						str[t * 9 + j] = '0';
					}
				}
			}

		}
	}
	if (program == 1) {
		printbase(row, col, str, 1);
	}
	
}
int endpcgi(const CONSOLE_GRAPHICS_INFO* const pCGI,const char*gname) 
{
	cct_setcolor(pCGI->area_bgcolor,pCGI->area_fgcolor); //恢复初始颜色

	char ch = '0';
	while (ch != 'c' && ch != 'q') {
		cct_gotoxy(0, pCGI->SLI.lower_start_y + 2);//光标设到指定位置
		cout << setw(pCGI->cols - 1) << ' '; //先用空格清空整行

		cct_gotoxy(0, pCGI->SLI.lower_start_y + 2);//光标设到指定位置

		cout << gname << '-' << "输入c继续，输入q退出";

		ch = _getche();
	}
	if (ch == 'c')
		return 1;
	else
		return 0;

}