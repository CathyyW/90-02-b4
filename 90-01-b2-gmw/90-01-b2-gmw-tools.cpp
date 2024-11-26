/* 2354180 王韵涵 计科 */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include<conio.h>
#include<Windows.h>
#include "../include/cmd_gmw_tools.h"
#include "../include/cmd_console_tools.h"
#include "90-01-b2-gmw.h"
#include"../include/common_tools.h"

using namespace std;

bool searchball0(int row, int col, char n[][9])
{
	int i, j;

	bool b = false;


	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {

			if (n[i - 1][j] == n[i][j] && i - 1 >= 0 && n[i + 1][j] == n[i][j] && i + 1 < row) {

				b = true;
			}
			else if (n[i][j - 1] == n[i][j] && j - 1 >= 0 && n[i][j + 1] == n[i][j] && j + 1 < col) {
				b = true;
			}
		}
	}

	return b;
}

void deleteball(int row, int col, char n[][9],const CONSOLE_GRAPHICS_INFO* const pCGI)
{
	int i, j, t, k;
	
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
				
				gmw_draw_block(pCGI, i, j, n[i][j]-'0', bdi_selected);
				Sleep(200);
				for (k = 0; k < 5; k++) {
					
					gmw_draw_block(pCGI, i, j, n[i][j]-'0', bdi_exploded);
					Sleep(50);
					gmw_draw_block(pCGI, i, j, 0, bdi_normal);
					Sleep(50);
				}
				n[i][j] = '0';
				
			}

		}
	}


	//改变数组值
	for (j = 0; j < col; j++) {
		for (i = 0; i < row - 1; i++) {
			for (t = 0; t < row - (i + 1); t++) {
				if (n[t + 1][j] == '0' && t + 1 < row && n[t][j] != '0') {

					gmw_move_block(pCGI, t, j, n[t][j] - '0', 0, bdi_normal, UP_TO_DOWN, 1);
					n[t + 1][j] = n[t][j];
					n[t][j] = '0';
					//移动
				}
			}

		}
	}


}

bool hintball(int row, int col, char n[][9], int hint[][9], const CONSOLE_GRAPHICS_INFO* const pCGI)
{

	
	int i, j;
	bool c = false;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (hint[i][j] == 1) {
				gmw_draw_block(pCGI, i, j, n[i][j]-'0', bdi_normal);
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
				
				gmw_draw_block(pCGI, i, j, n[i][j]-'0', bdi_prompt);
				gmw_draw_block(pCGI, i+1, j, n[i+1][j]-'0', bdi_prompt);
				
				hint[i + 1][j] = 1;
				hint[i][j] = 1;
				c = true;
			}
			if (n[i][j + 1] == n[i + 1][j] && n[i][j + 1] == n[i - 1][j] && i - 1 >= 0 && j + 1 < col ||  //i,j&i,j+1
				n[i][j + 1] == n[i][j - 1] && n[i][j + 1] == n[i][j - 2] && j - 2 >= 0 && j + 1 < col ||
				n[i][j + 1] == n[i - 1][j] && n[i][j + 1] == n[i - 2][j] && i - 2 >= 0 && j + 1 < col ||
				n[i][j + 1] == n[i + 1][j] && n[i][j + 1] == n[i + 2][j] && j + 1 < col && i + 2 < row) {
				

				gmw_draw_block(pCGI, i, j, n[i][j]-'0', bdi_prompt);
				gmw_draw_block(pCGI, i, j+1, n[i][j+1]-'0', bdi_prompt);

				hint[i][j] = 1;
				hint[i][j + 1] = 1;
				c = true;
			}
			if (n[i][j - 1] == n[i + 1][j] && n[i][j - 1] == n[i - 1][j] && i - 1 >= 0 && i + 1 < row && j - 1 >= 0 ||  //i,j&i,j-1
				n[i][j - 1] == n[i][j + 1] && n[i][j - 1] == n[i][j + 2] && j - 1 >= 0 && j + 2 < col ||
				n[i][j - 1] == n[i - 1][j] && n[i][j - 1] == n[i - 2][j] && i - 2 >= 0 && j - 1 >= 0 ||
				n[i][j - 1] == n[i + 1][j] && n[i][j - 1] == n[i + 2][j] && j - 1 >= 0 && i + 2 < row) {
				
				gmw_draw_block(pCGI, i, j, n[i][j]-'0', bdi_prompt);
				gmw_draw_block(pCGI, i, j - 1, n[i][j - 1]-'0', bdi_prompt);


				hint[i][j] = 1;
				hint[i][j - 1] = 1;
				c = true;
			}
			if (n[i - 1][j] == n[i][j + 1] && n[i - 1][j] == n[i][j - 1] && i - 1 >= 0 && j + 1 < col && j - 1 >= 0 ||  //i,j&i-1,j
				n[i - 1][j] == n[i + 1][j] && n[i - 1][j] == n[i + 2][j] && i - 1 >= 0 && i + 2 < row ||
				n[i - 1][j] == n[i][j - 1] && n[i - 1][j] == n[i][j - 2] && j - 2 >= 0 && i - 1 >= 0 ||
				n[i - 1][j] == n[i][j + 1] && n[i - 1][j] == n[i][j + 2] && i - 1 >= 0 && j + 2 < col) {
				
				
				gmw_draw_block(pCGI, i, j, n[i][j]-'0', bdi_prompt);
				gmw_draw_block(pCGI, i - 1, j, n[i - 1][j]-'0', bdi_prompt);

				hint[i - 1][j] = 1;
				hint[i][j] = 1;
				c = true;
			}
		}
	}

	
	return c;
}

void to_be_continued(const char* game_name, const char* prompt, const CONSOLE_GRAPHICS_INFO* const bgi)
{

	if (bgi->inited == CGI_INITED) { //初始化过
		cct_setcolor(bgi->area_bgcolor, bgi->area_fgcolor); //恢复初始颜色

		cct_gotoxy(0, bgi->SLI.lower_start_y + 2);//光标设到指定位置
		cout << setw(bgi->cols - 1) << ' '; //先用空格清空整行

		cct_gotoxy(0, bgi->SLI.lower_start_y + 2);//光标设到指定位置
		cout << game_name << '-' << (bgi->CFI.separator ? "有" : "无") << "分隔线-" << prompt << "，按回车键继续...";
	}
	else {
		cct_setcolor(); //恢复缺省颜色
		cct_gotoxy(0, 0);//光标设到指定位置
		cout << game_name << '-' << prompt << "，按回车键继续...   ";
	}

	while (_getch() != '\r')
		;

	return;
}

void fillball(int row, int col, char n[][9], const CONSOLE_GRAPHICS_INFO* const pCGI)
{
	int i, j;
	
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (n[i][j] == '0') {
				n[i][j] = (rand() % 9 + 1) + '0';
				
				gmw_draw_block(pCGI, i, j, n[i][j] - '0', bdi_normal);
			}

		}
	}
	
}

bool click(int row, int col, char n[][9], int hint[][9], int i, int j)
{

	bool b = false;

	if (hint[i - 1][j] == 2 && hint[i][j] == 2 && i - 1 >= 0) {

		b = true;
	}
	if (hint[i + 1][j] == 2 && hint[i][j] == 2 && i + 1 < row) {
		b = true;
	}
	if (hint[i][j + 1] == 2 && hint[i][j] == 2 && j + 1 < col) {
		b = true;
	}
	if (hint[i][j - 1] == 2 && hint[i][j] == 2 && j - 1 >= 0) {
		b = true;
	}

	return b;


}

bool check(int row, int col, char n[][9], int hint[][9], int i, int j)
{

	bool c = false;

	int t;
	if (hint[i - 1][j] == 2 && hint[i][j] == 2 && i - 1 >= 0) {
		t = n[i - 1][j];
		n[i - 1][j] = n[i][j];
		n[i][j] = t;
		c = searchball0(row, col, n);
		t = n[i - 1][j];
		n[i - 1][j] = n[i][j];
		n[i][j] = t;

	}
	if (hint[i + 1][j] == 2 && hint[i][j] == 2 && i + 1 < row) {
		t = n[i + 1][j];
		n[i + 1][j] = n[i][j];
		n[i][j] = t;
		c = searchball0(row, col, n);
		t = n[i + 1][j];
		n[i + 1][j] = n[i][j];
		n[i][j] = t;
	}
	if (hint[i][j + 1] == 2 && hint[i][j] == 2 && j + 1 < col) {
		t = n[i][j + 1];
		n[i][j + 1] = n[i][j];
		n[i][j] = t;
		c = searchball0(row, col, n);
		t = n[i][j + 1];
		n[i][j + 1] = n[i][j];
		n[i][j] = t;
	}
	if (hint[i][j - 1] == 2 && hint[i][j] == 2 && j - 1 >= 0) {
		t = n[i][j - 1];
		n[i][j - 1] = n[i][j];
		n[i][j] = t;
		c = searchball0(row, col, n);
		t = n[i][j - 1];
		n[i][j - 1] = n[i][j];
		n[i][j] = t;
	}
	return c;
}

void mouseread(int row, int col, char n[][9], int hint[][9], const CONSOLE_GRAPHICS_INFO* const pCGI)
{
	bool b = false, c = false;
	int loop = 1;
	int maction, old_mrow, old_mcol, mrow = -1, mcol = -1;
	int keycode1, keycode2;
	int ret;
	char temp[256];

	cct_enable_mouse();

	/* 打印初始光标位置[0,0] */
	cct_setcursor(CURSOR_INVISIBLE);	//关闭光标

	while (loop) {
		old_mrow = mrow;
		old_mcol = mcol;
		ret = gmw_read_keyboard_and_mouse(pCGI, maction, mrow, mcol, keycode1, keycode2);

		if (ret == CCT_MOUSE_EVENT) {
			if (maction == MOUSE_ONLY_MOVED) {
				/* 这时，mrow、mcol肯定跟刚才不同 */

				/* 做一个色块变化（color_linez不是所有位置都有色块，此处直接用3代替），不同游戏此处不同，仅仅是个演示 */

			}
			else if (maction == MOUSE_RIGHT_BUTTON_CLICK) {
				/* 下状态栏显示内容 */
				gmw_status_line(pCGI, LOWER_STATUS_LINE, "[读到右键] 退出", NULL);
				loop = 0;
			}
			else {
				if (hint[mrow][mcol] == 1 || hint[mrow][mcol] == 2) {

					sprintf(temp, "[当前选择] %c行%d列", char('A' + mrow), mcol); //未考虑mrow超过26，mcol超过99的情况，如有需要，请自行处理
					gmw_status_line(pCGI, LOWER_STATUS_LINE, temp);


					if (hint[mrow][mcol] == 1) {
						hint[mrow][mcol] = 2; //变值 已被选中
						gmw_draw_block(pCGI, mrow, mcol, n[mrow][mcol] - '0', bdi_click);
					}
					else if (hint[mrow][mcol] == 2) {
						hint[mrow][mcol] = 1; //取消选中状态
						gmw_draw_block(pCGI, mrow, mcol, n[mrow][mcol] - '0', bdi_prompt);
					}
					b = click(row, col, n, hint, mrow,mcol); //检查是否相邻
					c = check(row, col, n, hint, mrow, mcol);//检查是否可交换
					
					if (b == true && c == true)
						loop = 0;

					else if (b == true && c == false) {
						 //未考虑mrow超过26，mcol超过99的情况，如有需要，请自行处理
						gmw_status_line(pCGI, LOWER_STATUS_LINE, "无法交换");
						
						Sleep(100);
						int i, j;
						for (i = 0; i < row; i++) {
							for (j = 0; j < col; j++) {
								if (hint[i][j] == 2) {
									hint[i][j] = 1; //变值

									gmw_draw_block(pCGI, i, j, n[i][j] - '0', bdi_prompt);
								
								}
							}
						}
					}
					else {//不相邻
						int i, j;
						for (i = 0; i < row; i++) {
							for (j = 0; j < col; j++) {
								if (hint[i][j] == 2 && i!=mrow&&j!=mcol) {
									hint[i][j] = 1; //变值

									gmw_draw_block(pCGI, i, j, n[i][j] - '0', bdi_prompt);
								}
							}
						}
					}

				}
				else { 
					sprintf(temp, "[不能选择] %c行%d列", char('A' + mrow), mcol); //未考虑mrow超过26，mcol超过99的情况，如有需要，请自行处理
					gmw_status_line(pCGI, LOWER_STATUS_LINE, temp);
				}
			}

		}
		
	}//end of while

	
	cct_disable_mouse();	//禁用鼠标
	





	
}

void changeball(int row, int col, char n[][9], int hint[][9], const CONSOLE_GRAPHICS_INFO* const pCGI)
{
	int i, j;
	char ch;

	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (hint[i][j] == 2) {
				if (hint[i - 1][j] == 2 && i - 1 >= 0) {
					hint[i - 1][j] = 0, hint[i][j] = 0;

					ch = n[i - 1][j];
					n[i - 1][j] = n[i][j];
					n[i][j] = ch;

					gmw_draw_block(pCGI, i, j, n[i][j] - '0', bdi_normal);
					gmw_draw_block(pCGI, i-1, j, n[i-1][j] - '0', bdi_normal);


				}
				if (hint[i + 1][j] == 2 && i + 1 < row) {
					hint[i + 1][j] = 0, hint[i][j] = 0;

					ch = n[i + 1][j];
					n[i + 1][j] = n[i][j];
					n[i][j] = ch;

					gmw_draw_block(pCGI, i, j, n[i][j] - '0', bdi_normal);
					gmw_draw_block(pCGI, i + 1, j, n[i + 1][j] - '0', bdi_normal);
				}
				if (hint[i][j + 1] == 2 && j + 1 < col) {
					hint[i][j + 1] = 0, hint[i][j] = 0;

					ch = n[i][j + 1];
					n[i][j + 1] = n[i][j];
					n[i][j] = ch;

					gmw_draw_block(pCGI, i, j, n[i][j] - '0', bdi_normal);
					gmw_draw_block(pCGI, i , j+1, n[i ][j+1] - '0', bdi_normal);
				}
				if (hint[i][j - 1] == 2 && j - 1 >= 0) {
					hint[i][j - 1] = 0, hint[i][j] = 0;

					ch = n[i][j - 1];
					n[i][j - 1] = n[i][j];
					n[i][j] = ch;

					gmw_draw_block(pCGI, i, j, n[i][j] - '0', bdi_normal);
					gmw_draw_block(pCGI, i, j -1, n[i][j - 1] - '0', bdi_normal);
				}
			}
		}
	}

}
