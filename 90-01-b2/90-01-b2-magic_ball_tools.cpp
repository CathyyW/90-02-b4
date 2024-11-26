/* 2354180 王韵涵 计科 */
#include<iostream>
#include<iomanip>
#include "90-01-b2-magic_ball.h"
#include "../include/cmd_console_tools.h"
#include"../include/common_tools.h"
#include<Windows.h>
using namespace std;
#include"../include/common_menu.h"

void menu1(char choice)
{
	int row, col;
	bool b = false;
	char n[9][9];
	cct_cls();
	input(&row, &col, n[0], 1);
	if (choice == '1') {
		cout << "初始数组：" << endl;
		printbase(row, col, n[0],1);

		b = search0(row, col, n);
	}
	if (choice == '2' || choice == '3') {
		cout << "初始数组：" << endl;
		printbase(row, col, n[0],1);

		b = search0(row, col, n);
		if (b == false && choice == '2') {
			cout << "初始无可消除项，本小题无法测试，请再次运行" << endl;
		}
		else if (b == false && choice == '3') {
			hint(row, col, n);
		}
		else {
			while (b) {

				cout << "按回车键进行数组下落除0操作...";
				while (getchar() != '\n') {
				}
				cout << endl;
				cout << "下落除0后的数组(不同色标识)：" << endl;
				Delete(row, col, n);
				refreshdown(row, col, n[0], 1);
				cout << "按回车键进行新值填充...";
				while (getchar() != '\n') {
				}
				cout << endl;
				printfill(row, col, n);
				b = search0(row, col, n);
			}
			if (choice == '3')
				hint(row, col, n);
		}

	}

	end();
	main();

}
void menu2(char choice)
{
	int row, col;
	bool b;
	char n[9][9];
	int hint[9][9] = { 0 };
	cct_cls();
	input(&row, &col, n[0], 1);
	cout << "初始数组：" << endl;
	printbase(row, col, n[0],1);
	cout << "按回车键显示图形..." << endl;
	while (getchar() != '\n') {
	}
	cout << endl;
	cct_cls();
	printgraph(row, col, n, choice);
	printball(row, col, n, choice);

	if (choice == '6') {
		b = searchball0(row, col, n, choice);
		if (b == false)
			cout << "未找到初始可消除项" << endl;

		else {
			note0(row, col, n, choice);

		}

	}
	if (choice == '7') {

		b = searchball0(row, col, n, choice);

		if (b == false) {
			cct_gotoxy(14, 0);
			cout << "(未找到初始项)";
			cct_gotoxy(0, row * 2 + 2);
			cout << "按回车键显示消除提示...";
			while (getchar() != '\n') {
			}

			hintball(row, col, n, choice, hint);
		}

		else {
			while (b) {
				note0(row, col, n, choice);
				cct_gotoxy(0, row * 2 + 2);
				cout << "                                    ";
				cct_gotoxy(0, row * 2 + 2);
				cout << "按回车键进行消除及下落除0操作...";
				while (getchar() != '\n') {
				}

				Deleteball(row, col, n);
				cct_gotoxy(0, row * 2 + 2);
				cout << "                                    ";
				cct_gotoxy(0, row * 2 + 2);
				cout << "按回车键进行新值填充...";
				while (getchar() != '\n') {
				}

				fillball(row, col, n, choice);
				b = searchball0(row, col, n, choice);
			}
			cct_gotoxy(14, 0);
			cout << "(未找到初始项)";
			cct_gotoxy(0, row * 2 + 2);
			cout << "按回车键显示消除提示...";
			while (getchar() != '\n') {
			}

			hintball(row, col, n, choice, hint);
		}

	}
	if (choice == '8') {
		cct_gotoxy(14, 0);
		cout << "(当前分数：0 右键退出)";
		cct_gotoxy(0, row * 2 + 2);
		b = searchball0(row, col, n, choice);

		if (b == false) {

			hintball(row, col, n, choice, hint);
		}

		else {
			while (b) {
				note0(row, col, n, choice);

				Deleteball(row, col, n);

				fillball(row, col, n, choice);
				b = searchball0(row, col, n, choice);
			}

			hintball(row, col, n, choice, hint);
		}
		mouseread(row, col, n, hint, choice);


	}

	end();
	main();
}
void menu3(char choice)
{
	int row, col;
	bool b = true, c = true;
	int score = 0;
	char n[9][9];
	int hint[9][9] = { 0 };
	cct_cls();
	input(&row, &col, n[0],1);
	cout << "初始数组：" << endl;
	printbase(row, col, n[0],1);
	cout << "按回车键显示图形..." << endl;
	while (getchar() != '\n') {
	}
	cout << endl;
	cct_cls();
	printgraph(row, col, n, choice);
	printball(row, col, n, choice);
	//第一次
	cct_gotoxy(14, 0);
	cout << "(当前分数：0 右键退出)";
	cct_gotoxy(0, row * 2 + 2);

	b = searchball0(row, col, n, choice);

	if (b == false) {

		hintball(row, col, n, choice, hint);
	}

	else {
		while (b) {
			note0(row, col, n, choice);

			Deleteball(row, col, n);

			fillball(row, col, n, choice);
			b = searchball0(row, col, n, choice);
		}

		hintball(row, col, n, choice, hint);
	}
	mouseread(row, col, n, hint, choice);

	changeball(row, col, n, hint);
	//之后
	while (1) {




		b = searchball0(row, col, n, choice);


		while (b) {
			note0(row, col, n, choice);

			Deleteball(row, col, n);
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					if (n[i][j] == '0')
						score++;
				}
			}
			cct_gotoxy(14, 0);
			cout << "(当前分数：" << score << " 右键退出)";
			cct_gotoxy(0, row * 2 + 2);

			fillball(row, col, n, choice);
			b = searchball0(row, col, n, choice);
		}

		c = hintball(row, col, n, choice, hint);
		if (c == false) {
			break;
		}

		mouseread(row, col, n, hint, choice);

		changeball(row, col, n, hint);



	}


	end();
	main();




}


bool check(int row, int col, char n[][9], int hint[][9], int i, int j)
{
	
	bool c=false;
	
	int t;
	if (hint[i - 1][j] == 2 && hint[i][j] == 2 && i - 1 >= 0) {
		t = n[i - 1][j];
		n[i - 1][j] = n[i][j];
		n[i][j] = t;
		c = searchball0(row, col, n, 9);
		t = n[i - 1][j];
		n[i - 1][j] = n[i][j];
		n[i][j] = t;
		
	}
	if (hint[i + 1][j] == 2 && hint[i][j] == 2 && i + 1 < row) {
		t = n[i +1][j];
		n[i + 1][j] = n[i][j];
		n[i][j] = t;
		c = searchball0(row, col, n, 9);
		t = n[i + 1][j];
		n[i + 1][j] = n[i][j];
		n[i][j] = t;
	}
	if (hint[i][j + 1] == 2 && hint[i][j] == 2 && j + 1 < col) {
		t = n[i][j+1];
		n[i ][j+1] = n[i][j];
		n[i][j] = t;
		c= searchball0(row, col, n, 9);
		t = n[i][j + 1];
		n[i][j + 1] = n[i][j];
		n[i][j] = t;
	}
	if (hint[i][j - 1] == 2 && hint[i][j] == 2 && j - 1 >= 0) {
		t = n[i][j - 1];
		n[i][j - 1] = n[i][j];
		n[i][j] = t;
		c = searchball0(row, col, n, 9);
		t = n[i][j - 1];
		n[i][j - 1] = n[i][j];
		n[i][j] = t;
	}
	return c;
}


bool click(int row, int col, char n[][9], int hint[][9],int i,int j)
{

	bool b=false;
	
	if (hint[i - 1][j] == 2 &&hint[i][j]==2&& i - 1 >= 0) {
		
		b = true;
	}
	if (hint[i +1][j] == 2 && hint[i][j] == 2 && i +1<row) {
		b = true;
	}
	if (hint[i][j+1] == 2 && hint[i][j] == 2 && j + 1 <col) {
		b = true;
	}
	if (hint[i][j - 1] == 2 && hint[i][j] == 2 && j-1>=0) {
		b = true;
	}

	return b;

	
}

void mouseread(int row, int col, char n[][9], int hint[][9],char choice)
{
	int X = 0, Y = 0;
	bool b,c;
	
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;
	
	cct_enable_mouse();

	/* 打印初始光标位置[0,0] */
	cct_setcursor(CURSOR_INVISIBLE);	//关闭光标
	while (loop) {
		/* 读鼠标/键盘，返回值为下述操作中的某一种, 当前鼠标位置在<X,Y>处 */
		ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

if (ret == CCT_MOUSE_EVENT) {

	cct_gotoxy(0, row * 2 + 2);
	cout << "[当前光标] ";
	if (Y % 2 == 0 && Y >= 2 && Y <= row * 2 && (X == 2 || X == 3 || X == 6 || X == 7 || X == 10 || X == 11 || X == 14 || X == 15 || X == 18 || X == 19 || X == 22 || X == 23 || X == 26 || X == 27 || X == 30 || X == 31 || X == 34 || X == 35) && X <= 4 * col - 1) { //1,0;3,1;5,2 // 2,0;4,1;6,2 //2,3,6,7,10,11
		cout << char('A' + Y / 2 - 1) << "行" << X / 4 + 1 << "列            ";

		switch (maction) {
			case MOUSE_RIGHT_BUTTON_DOUBLE_CLICK:	//双击右键
				loop = 0;
				break;
			case MOUSE_LEFT_BUTTON_CLICK:			//按下左键
				cct_gotoxy(0, row * 2 + 2);

				if (hint[Y / 2 - 1][X / 4] == 1 || hint[Y / 2 - 1][X / 4] == 2) {
					cout << "当前选择" << char('A' + Y / 2 - 1) << "行" << X / 4 + 1 << "列         ";

					if (choice == '8') {
						Sleep(50);
						loop = 0;
					}
					if (choice == '9') {
						if (hint[Y / 2 - 1][X / 4] == 1) {
							hint[Y / 2 - 1][X / 4] = 2; //变值
							if (X % 2 == 0)
								cct_showstr(X, Y, "◎", n[Y / 2 - 1][X / 4], 15); //变色
							else
								cct_showstr(X - 1, Y, "◎", n[Y / 2 - 1][X / 4], 15);
							cct_setcolor();
						}
						else if (hint[Y / 2 - 1][X / 4] == 2) {
							hint[Y / 2 - 1][X / 4] = 1; //变值
							if (X % 2 == 0)
								cct_showstr(X, Y, "◎", n[Y / 2 - 1][X / 4], 0); //变色
							else
								cct_showstr(X - 1, Y, "◎", n[Y / 2 - 1][X / 4], 0);
							cct_setcolor();
						}

						b = click(row, col, n, hint, Y / 2 - 1, X / 4); //检查是否相邻
						c = check(row, col, n, hint, Y / 2 - 1, X / 4);//检查是否可交换
						if (b == true && c == true)
							loop = 0;
						else if (b == true && c == false) {
							cct_gotoxy(0, row * 2 + 2);
							cout << "无法交换";
							Sleep(100);
							int i, j;
							for (i = 0; i < row; i++) {
								for (j = 0; j < col; j++) {
									if (hint[i][j] == 2) {
										hint[i][j] = 1; //变值

										cct_showstr(2 + j * 4, 2 + i * 2, "◎", n[i][j], 0);
										cct_setcolor();
									}
								}
							}
						}
						else {
							int i, j;
							for (i = 0; i < row; i++) {
								for (j = 0; j < col; j++) {
									if (hint[i][j] == 2 && (i != Y / 2 - 1 || j != X / 4)) {
										hint[i][j] = 1; //变值

										cct_showstr(2 + j * 4, 2 + i * 2, "◎", n[i][j], 0);
										cct_setcolor();
									}
								}
							}
						}
					}

				}
				else { //1,0;3,1;5,2 // 2,0;4,1;6,2
					cout << "不能选择" << char('A' + Y / 2 - 1) << "行" << X / 4 + 1 << "列           ";
					Sleep(50);
				}
				break;
		}

	}
	else {
		cout << "位置非法";
		switch (maction) {
			case MOUSE_RIGHT_BUTTON_DOUBLE_CLICK:	//双击右键
				loop = 0;
				break;
		}
	}

}
	}
	cct_disable_mouse();	//禁用鼠标
	cct_setcursor(CURSOR_VISIBLE_NORMAL);	//打开光标
	cct_gotoxy(0, row * 2 + 3);

}













