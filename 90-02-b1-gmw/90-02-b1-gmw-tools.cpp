/* 2354180 王韵涵 计科 */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include<conio.h>
#include<Windows.h>
#include "../include/cmd_gmw_tools.h"
#include "../include/cmd_console_tools.h"
#include "90-02-b1-gmw.h"
#include"../include/common_tools.h"

using namespace std;
void scoresum(int row, int col, int* score, int* sum, char n[][10], char hint[][10])
{
	int i, j;
	*score = 0;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (hint[i][j] == '*') {
				*score += 5;
			}

		}
	}
	*sum += *score;
}

bool searcharound(int row, int col, int mrow, int mcol, char n[][10], int step, char hint[][10])
{

	//判断周围是否有相同色块
	if (step == 1) {
		//left,right,up,down
		if ((n[mrow][mcol-1] == n[mrow][mcol] && mcol - 1 >= 0) || (
			n[mrow][mcol + 1] == n[mrow][mcol] &&mcol + 1 < col) ||
			(n[mrow-1][mcol] == n[mrow][mcol] && mrow - 1 >= 0) ||
			(n[mrow+1][mcol] == n[mrow][mcol] && mrow+ 1 < row)) {

			return true;
		}
		return false;
	}
	//递归方式将所有选择的相同色块标记
	if (n[mrow][mcol - 1] == n[mrow][mcol] && mcol - 1 >= 0) {
		if (hint[mrow][mcol - 1] != '*' || hint[mrow][mcol] != '*') {
			hint[mrow][mcol - 1] = '*';
			hint[mrow][mcol] = '*';
			searcharound(row, col, mrow, mcol - 1, n, 2, hint);//left
		}
	}
	if (n[mrow][mcol + 1] == n[mrow][mcol] && mcol + 1 < col) {
		if (hint[mrow][mcol + 1] != '*' || hint[mrow][mcol] != '*') {
			hint[mrow][mcol + 1] = '*';
			hint[mrow][mcol] = '*';
			searcharound(row, col, mrow, mcol +1, n, 2, hint);//left
		}
	}
	if (n[mrow - 1][mcol] == n[mrow][mcol] && mrow - 1 >= 0) {
		if (hint[mrow - 1][mcol] != '*' || hint[mrow][mcol] != '*') {
			hint[mrow - 1][mcol] = '*';
			hint[mrow][mcol] = '*';
			searcharound(row, col, mrow - 1, mcol, n, 2, hint);//up
		}
	}
	if (n[mrow + 1][mcol] == n[mrow][mcol] && mrow + 1 < row) {
		if (hint[mrow + 1][mcol] != '*' || hint[mrow][mcol] != '*') {
			hint[mrow + 1][mcol] = '*';
			hint[mrow][mcol] = '*';
			searcharound(row, col, mrow + 1, mcol, n, 2, hint);//up
		}
	}

	return true;
}

bool printaround(int mrow, int mcol, int row, int col, char n[][10], int step, char hint[][10], const CONSOLE_GRAPHICS_INFO* const pCGI)
{

	int i, j;
	
	bool judge = false;//判断是否有连续值

	if (step == 0) {//涂黑
		for (i = 0; i < row; i++) {
			for (j = 0; j < col; j++) {
				if (hint[i][j] == '*') {
					gmw_draw_block(pCGI, i, j, n[i][j] - '0', bdi_normal);
					hint[i][j] = '0';
				}

			}
		}
	}

	if ( (hint[mrow][mcol] != '*' && step == 1)) {

		judge = searcharound(row, col, mrow,mcol, n, 1, hint);//检查当前色块周围有相同值
		if (judge) {
			searcharound(row, col, mrow, mcol, n, 2, hint);//把选中和周围全部高亮
			for (i = 0; i < row; i++) {
				for (j = 0; j < col; j++) {
					if (hint[i][j] == '*')//将此次选中的涂白
						gmw_draw_block(pCGI,i,j, n[i][j] - '0', bdi_related);
				}
			}
		}
		else {
			
			gmw_status_line(pCGI, LOWER_STATUS_LINE, "周围无相同星星,请重新选择");
			Sleep(500);
			return false;
		}
	}
	return true;
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

bool searchall(int row, int col, char n[][10])
{
	int i, j;



	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {

			if (n[i - 1][j] == n[i][j] && i - 1 >= 0 && n[i][j] != '0') {
				return true;
			}
			if (n[i][j - 1] == n[i][j] && j - 1 >= 0 && n[i][j] != '0') {
				return true;
			}
			if (n[i][j + 1] == n[i][j] && j + 1 < col && n[i][j] != '0') {
				return true;
			}
			if (n[i + 1][j] == n[i][j] && i + 1 < row && n[i][j] != '0') {
				return true;
			}

		}
	}
	return false;
}

void clear(int mrow, int mcol, int row, int col,  char n[][10], char hint[][10], const CONSOLE_GRAPHICS_INFO* const pCGI)
{

	int i, j;
	
	searcharound(row, col, mrow, mcol, n, 2, hint);

	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (hint[i][j] == '*') {
				
				gmw_draw_block(pCGI, i, j, BDI_VALUE_BLANK, bdi_normal);
				n[i][j] = '0';

			}
		}
	}

}

void star_down(int row, int col, char n[][10], const CONSOLE_GRAPHICS_INFO* const pCGI)
{
	int i, j, t;
	
	for (j = 0; j < col; j++) {
		for (i = 0; i < row - 1; i++) {
			for (t = 0; t < row - (i + 1); t++) {
				if (n[ t + 1][ j] == '0' && t + 1 < row && n[t][j]!= '0') {

					gmw_move_block(pCGI, t, j, n[t][j] - '0', BDI_VALUE_BLANK, bdi_normal, UP_TO_DOWN, 1);


					n[t + 1][j] = n[t][j];
					n[t][j] = '0';
					

				}
			}

		}
	}

}

void mouse_keyboard(int row, int col, char n[][10], char hint[][10], const CONSOLE_GRAPHICS_INFO* const pCGI)
{
	
	int loop = 1;
	int maction, old_mrow, old_mcol, mrow =0 , mcol = 0;//初始值左上角0,0
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
				
				if (n[mrow][mcol] != '0') {//不是已经消除的状态
					//新的显白处理
					gmw_draw_block(pCGI, mrow, mcol, n[mrow][mcol] - '0', bdi_selected);
					//旧的显黑
					if(old_mrow>=0&&old_mcol>=0)
						gmw_draw_block(pCGI, old_mrow, old_mcol, n[old_mrow][old_mcol] - '0', bdi_normal);
					
				}
				else {
					gmw_status_line(pCGI, LOWER_STATUS_LINE, "[当前光标] 位置非法");//遮住函数里的坐标
					if (old_mrow >= 0 && old_mcol >= 0)
						gmw_draw_block(pCGI, old_mrow, old_mcol, n[old_mrow][old_mcol] - '0', bdi_normal);
				}

			}
			if (maction == MOUSE_LEFT_BUTTON_CLICK) {
				if (n[mrow][mcol] != '0') {//不是已经消除的状态
					
						sprintf(temp, "[当前选择] %c行%d列", char('A' + mrow), mcol); //未考虑mrow超过26，mcol超过99的情况，如有需要，请自行处理
						gmw_status_line(pCGI, LOWER_STATUS_LINE, temp);
						//标记选择及其周围
						bool d;
						d = printaround(mrow, mcol, row, col, n, 1, hint, pCGI);//涂白
						
					
						while (d) {
							gmw_status_line(pCGI, LOWER_STATUS_LINE, "箭头键/鼠标移动取消当前选择，回车键/单击左键合成");
							int secondx, secondy;
							ret = cct_read_keyboard_and_mouse(secondx, secondy, maction, keycode1, keycode2);
							if ((mrow== (secondy + 1) / 4 - 1) && (mcol == (secondx + 4) / 8)-1 && (maction == MOUSE_LEFT_BUTTON_CLICK || keycode1 == 13)) {
								clear(mrow, mcol, row, col, n, hint,pCGI);//合并消除
								loop = 0;
								break;
							}
							if (mrow!= (secondy + 1) / 4 - 1 || (mcol!= (secondx + 4) / 8-1)) {
								printaround(mrow, mcol, row, col, n, 0, hint,pCGI);//抹黑
								break;
							}
						}
						gmw_status_line(pCGI, LOWER_STATUS_LINE, "                                                   ");//清屏
					

				}
				else {
					gmw_status_line(pCGI, LOWER_STATUS_LINE, "[当前光标] 位置非法");//遮住函数里的坐标

				}
			}

			
		}//鼠标结束
		if (ret == CCT_KEYBOARD_EVENT) {

			if (keycode1 == 0xe0) {
				if (keycode2 == KB_ARROW_UP) {
					if (old_mrow == 0) {
						mrow = row - 1;
					}
					else {
						mrow = old_mrow - 1;
					}


				}
				if (keycode2 == KB_ARROW_DOWN) {
					if (old_mrow == row - 1) {
						mrow = 0;
					}
					else {
						mrow = old_mrow + 1;
					}
				}
				if (keycode2 == KB_ARROW_LEFT) {
					if (old_mcol == 0) {
						mcol = col - 1;
					}
					else {
						mcol = old_mcol - 1;

					}
				}
				if (keycode2 == KB_ARROW_RIGHT) {
					if (old_mcol == col - 1) {
						mcol = 0;
					}
					else {
						mcol = old_mcol + 1;
					}
				}
				if (n[mrow][mcol] != '0') {
					//新的显白处理
					gmw_draw_block(pCGI, mrow, mcol, n[mrow][mcol] - '0', bdi_selected);
					//旧的显黑
					if (old_mrow >= 0 && old_mcol >= 0)
						gmw_draw_block(pCGI, old_mrow, old_mcol, n[old_mrow][old_mcol] - '0', bdi_normal);
					sprintf(temp, "[当前键盘] %d行%d列", mrow, mcol);
					gmw_status_line(pCGI, LOWER_STATUS_LINE, temp);


				}
				else {
					gmw_status_line(pCGI, LOWER_STATUS_LINE, "[当前键盘] 位置非法");
					if (old_mrow >= 0 && old_mcol >= 0)
						gmw_draw_block(pCGI, old_mrow, old_mcol, n[old_mrow][old_mcol] - '0', bdi_normal);
				}
			}
			else if (keycode1 == 13) {
				if (n[mrow][mcol] != '0') {//不是已经消除的状态

					sprintf(temp, "[当前选择] %c行%d列", char('A' + mrow), mcol); //未考虑mrow超过26，mcol超过99的情况，如有需要，请自行处理
					gmw_status_line(pCGI, LOWER_STATUS_LINE, temp);
					//标记选择及其周围
					bool d;
					d = printaround(mrow, mcol, row, col, n, 1, hint, pCGI);//涂白

					while (d) {
						gmw_status_line(pCGI, LOWER_STATUS_LINE, "箭头键/鼠标移动取消当前选择，回车键/单击左键合成");
						int secondx, secondy;
						ret = cct_read_keyboard_and_mouse(secondx, secondy, maction, keycode1, keycode2);
						if (((mrow == (secondy + 1) / 4 - 1 && mcol == (secondx + 4) / 8) - 1 && maction == MOUSE_LEFT_BUTTON_CLICK) ||( keycode1 == 13)) {
							clear(mrow, mcol, row, col, n, hint, pCGI);//合并消除
							loop = 0;
							break;
						}
						if (mrow != (secondy + 1) / 4 - 1 || (mcol != (secondx + 4) / 8 - 1)) {
							printaround(mrow, mcol, row, col, n, 0, hint, pCGI);//抹黑
							break;
						}
					}
					gmw_status_line(pCGI, LOWER_STATUS_LINE, "                                                   ");//清屏


				}
				else {
					gmw_status_line(pCGI, LOWER_STATUS_LINE, "[当前键盘] 位置非法");//遮住函数里的坐标

				}


			}

		}

	}

	cct_disable_mouse();	//禁用鼠标
	



}

bool refreshright(int row, int col, char n[][10], int step, const CONSOLE_GRAPHICS_INFO* const pCGI)
{
	int i, j, t;
	int number = 0;
	bool d = false;
	int hint[10] = { 0 };
	for (j = 0; j < col; j++) {
		for (i = 0; i < row; i++) {
			if (n[i][j] != '0')
				break;
			if (i == row - 1) {
				hint[j] = 1;//标记要移动的列
				number++;//空列的数量
				d = true;
			}
		}

	}
	if (step == 2 || step == 3) {
		for (i = col-1; i >=0; i--) {
			if (hint[i] == 1) {
				for (j = i; j + 1 < col; j++) {
					for (t = 0; t < row; t++) {

						if (step == 3 && n[t][j+1] != '0') {
							gmw_move_block(pCGI, t, j + 1, n[t][j + 1] - '0', BDI_VALUE_BLANK, bdi_normal, RIGHT_TO_LEFT, 1);

						}
						n[t][j] = n[t][j + 1];
						n[t][j + 1] = '0';
					}
					hint[j] = hint[j + 1];

					if (j + 1 < col)
						hint[j + 1] = 1;
				}
			}

		}

	}

	return d;



}