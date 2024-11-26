/* 2354180 计科 王韵涵 */
#include <iostream>
#include<iomanip>
#include<conio.h>
#include "../include/cmd_console_tools.h"
#include"../include/common_menu.h"
#include"../include/common_tools.h"
#include"90-02-b1.h"
using namespace std;

int main()
{
	cct_setcolor();
	cct_cls();
	cct_setconsoleborder(120, 31, 120, 9001);
	cout << "--------------------------------------------" << endl;
	cout << "A.命令行找出可消除项并标识" << endl;
	cout << "B.命令行完成一次消除（分步骤显示）" << endl;
	cout << "C.命令行完成一关（分步骤显示）" << endl;
	cout << "D.伪图形界面下用鼠标选择一个色块（无分隔线）" << endl;
	cout << "E.伪图形界面下用鼠标选择一个色块（有分隔线）" << endl;
	cout << "F.伪图形界面完成一次消除（分步骤）" << endl;
	cout << "G.伪图形界面完整版" << endl;
	cout << "Q.退出" << endl;
	cout << "--------------------------------------------" << endl;
	cout << "[请选择]:";
	char choice;
	choice = menu_starball(2);

	if (choice == 'Q')
		return 0;
	//a实现逻辑
	if (choice == 'A' || choice == 'A' + 32|| choice == 'B' || choice == 'B' + 32|| choice == 'C' || choice == 'C' + 32) {
		cct_cls();
		int row, col;
		bool b=false;
		bool c = false;
		bool d = false;
		char n[10][10];
		char hint[10][10] = { 0 };
		int sum = 0, score = 0;
		//初始化数组（公共函数）
		input(&row, &col, n[0], 2);
		
		//大循环 是否选择该坐标
		while (1) {
			cout << "当前数组：" << endl;
			printbase(row, col, n[0], 2);
			//定位矩阵坐标
			char cord_r, cord_c;
			char answer;
			
			while (1) {
				while (1) {
					cout << "请以字母 + 数字形式[例：c2]输入矩阵坐标：";
					cord_r = _getche();
					cord_c = _getche();
					//正确范围以及该位置不是0
					if (((cord_r >= 'A' && cord_r <= row - 1 + 'A') || (cord_r >= 'A' + 32 && cord_r <= row - 1 + 'A' + 32)) && (cord_c >= '0' && cord_c <= '0' + col - 1)&&(n[cord_r-'A'][cord_c-'0']!='0'&& n[cord_r - 'a'][cord_c - '0'] != '0')) {
						
						break;
					}
					cout << endl;
				}
				if (cord_r >= 'A' + 32 && cord_r <= row - 1 + 'A' + 32)
					cord_r = cord_r - 32;
				//查找是否有连续值
				cout << "输入为" << cord_r << "行" << cord_c << "列" << endl;
				b = search(row, col, cord_r, cord_c, n[0], 1, hint);
				if (b) {
					break;
				}
				else {
					cout << "输入的矩阵坐标位置处无连续相同值，请重新输入" << endl;
				}
			}
			//结果数组与标识数组
			//重来后hint重新初始化
			for (int i = 0; i < 10; ++i) {
				for (int j = 0; j < 10; ++j) {
					hint[i][j] = '\0';
				}
			}

			b = search(row, col, cord_r, cord_c, n[0], 2, hint);
			
			printconse(row, col, n, hint, 1);//打印0*数组
			printconse(row, col, n, hint, 2);//打印不变值的数组
			
			if (choice == 'A' || choice == 'A' + 32) {
				break;
			}
			if (choice == 'B' || choice == 'B' + 32 || choice == 'C' || choice == 'C' + 32) {
				cout << "请确认是否把" << cord_r << cord_c << "及周围的相同值消除(Y / N / Q)：";
				while (1) {
					answer = _getche();
					
					if (answer == 'Y' || answer == 'y') {
						//将消除项全部赋值为0
						for (int i = 0; i < 10; ++i) {
							for (int j = 0; j < 10; ++j) {
								if (hint[i][j] == '*')
									n[i][j] = '0';
							}
						}
						cout << endl;
						printconse(row, col, n, hint, 3);//打印消除后的数组
						scoresum(row, col, &score, &sum, n, hint);//计算得分
						cout << "本次得分：" <<score << " 总得分：" << sum<< endl;
				
						break;
					}
					if (answer == 'N' || answer == 'n' ) 

						break;
					
					if (answer == 'Q' || answer == 'q') 
						break;
					
				}
				
				if (answer == 'N' || answer == 'n') {
					cout << endl;
					continue;
				}
				
				if (answer == 'Q' || answer == 'q')
					break;

			}
			if (choice == 'A' || choice == 'A' + 32 || choice == 'B' || choice == 'B' + 32) {
				break;
			}
			if (choice == 'C' || choice == 'C' + 32) {
				//数组下落
				cout << "按回车键进行数组下落操作...";
				while (getchar() != '\n') {
				}
				cout << endl;
				cout << "下落后的数组：" << endl;
				refreshdown(row, col, n[0], 2);
				
				printbase(row, col, n[0], 2);
				
				//检查是否需要右移
				d = refreshright(row, col, n, 1,choice);
				if (d) {
					cout << "右移后的数组:" << endl;
					refreshright(row, col, n, 2,choice);
					printbase(row, col, n[0], 2);
				}

				//检验是否有下一轮
				cout << "本次消除结束，按回车键继续新一次的消除...";
				while (getchar() != '\n') {
				}
				cout << endl;
				c=searchsame(row, col, n);
				if (c)
					continue;
				else {
					
					int left;
					left = row * col - sum / 5;
					
					cct_setcolor(13, 1);
					cout << "剩余" << left << "个不可消除项，本关结束！！！" << endl;
					cct_setcolor();
					break;
				}

			}


		}
		
		//第一次大循环结束后
		end();
		main();
		
		
	}
	if (choice == 'D'||choice=='d'||choice == 'E' || choice == 'e'||choice=='F'||choice=='f'||choice=='G'||choice=='g') {
		cct_cls();
		int row, col;
		int i, j;
		bool c = false;
		bool d = false;
		char n[10][10];
		char hint[10][10] = { 0 };
		int sum = 0, score = 0;
		//初始化数组（公共函数）
		input(&row, &col, n[0], 2);
		cct_cls();

		printtext(row, col, choice);
		printgraph(row, col, choice);
		for (i = 0; i < row; i++) {
			for (j = 0; j < col; j++) {
				printstar(i, j, n[0], choice, 0);
			}
		}
		cout << endl << endl << endl;
		//鼠标键盘操作
		
		if (choice == 'G' || choice == 'g') {
			c = searchsame(row, col, n); //有无连续相同值（排除0）
			while (c) {
				
				mouse_keyboard(row, col, choice, n[0],hint);
				

				cct_gotoxy(0, row * 4 + 3);
				cout << "                                                         ";
				cct_gotoxy(0, row * 4 + 3);
				scoresum(row, col, &score, &sum, n, hint);//计算得分
				cct_gotoxy(0, 0);
				cout << "本次得分：" << score << " 总得分：" << sum << endl;
				for (i = 0; i < 10; ++i) {
					for (j = 0; j < 10; ++j) {
						if (hint[i][j] == '*')
							hint[i][j] = '0';
					}
				}

				star_down(row, col, n[0], choice);
				d = refreshright(row, col, n, 1, choice);
				if(d)
					refreshright(row, col, n, 3, choice);
				c = searchsame(row, col, n);

				cct_gotoxy(0, row * 4 + 3);
				cout << "                                                         ";
				cct_gotoxy(0, row * 4 + 3);

				cout << "按下回车键进行下一回合，按c可退出游戏";//
				
					char button = _getche();
					if (button == 'c')
						break;
					if (button == '\n' || button == '\r')
						continue;
				
				
			}
			if (c == false) {
				cct_gotoxy(0, row * 4 + 4);
				cout << "                                                    ";
				cct_gotoxy(0, row * 4 + 4);
				cct_setcolor(13, 1);
				cout << "剩余" << row * col - sum / 5 << "个不可消除项，本关结束！！！           " << endl;
				cct_setcolor();
			}
			cct_gotoxy(0, row * 4 + 3);

			end();
			main();
		}

		if (choice == 'D' || choice == 'd' || choice == 'E' || choice == 'e') {
			mouse_keyboard(row, col, choice, n[0],hint);
			end();
			main();
		}
		if (choice == 'F' || choice == 'f') {
			mouse_keyboard(row, col, choice, n[0],hint);
			cct_gotoxy(0, row * 3 + 4);
			cout << "                                                         ";
			cct_gotoxy(0, row * 3 + 4);
			cout << "按下回车键即可进行下落和平移操作";
			while (getchar() != '\n') {
			}

			star_down(row, col, n[0], choice);
			refreshright(row, col, n, 3,choice);

			
			cct_gotoxy(0, row * 3 + 4);
			cout << "                                                         ";
			cct_gotoxy(0, row * 3 + 4);
			cout << "按下回车键即可进行下一回合的操作";
			while (getchar() != '\n') {
			}
			cct_gotoxy(0, row * 3 + 4);
			end();
			main();
		}
		
	}
}
