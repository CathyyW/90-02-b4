/* 2354180 王韵涵 计科 */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include<conio.h>
#include<Windows.h>
#include "../include/cmd_gmw_tools.h"
#include "../include/cmd_console_tools.h"
#include "90-02-b2.h"
#include"../include/common_tools.h"

using namespace std;

void input_mines(char n[][30],int *row,int *col,int *num_mines)
{
	
	char level='0';

	int placed_mines = 0;
	
	srand((unsigned int)(time(0))); //生成种子
	while (level != '1' && level != '2' && level!= '3') {
		cout << "请输入扫雷游戏的等级（数字），初级/中级/高级（1/2/3）" << endl;
		level = _getche();
	}
		
	if (level == '1') {
		*row = 9, * col = 9;
		*num_mines = 10;
		while (placed_mines < *num_mines) {
			// 随机选择一个位置
			int r = rand() % *row;
			int c = rand() % *col;

			// 检查该位置是否已放置雷
			if (n[r][c] != '9') {
				n[r][c] = '9'; // 放置雷
				placed_mines++;
			}
		}
	}
	if (level == '2') {
		*row = 16, * col = 16;
		*num_mines = 40;
		while (placed_mines < *num_mines) {
			// 随机选择一个位置
			int r = rand() % *row;
			int c = rand() % *col;

			// 检查该位置是否已放置雷
			if (n[r][c] != '9') {
				n[r][c] = '9'; // 放置雷
				placed_mines++;
			}
		}
	}
	if (level == '3') {
		*row = 16, * col = 30;
		*num_mines = 99;
		while (placed_mines < *num_mines) {
			// 随机选择一个位置
			int r = rand() % *row;
			int c = rand() % *col;

			// 检查该位置是否已放置雷
			if (n[r][c] != '9') {
				n[r][c] = '9'; // 放置雷
				placed_mines++;
			}
		}
	}
	

	

}

void init_mines(char n[][30],int row,int col)
{
	int count = 0;
	int i, j;
	int directions[8][2] = 
	{
		{-1,-1}, {-1,0}, {-1,1},//左上，上，右上
		{0, -1}, {0, 1},//左 右
		{1, -1}, {1, 0}, {1, 1} //左下，下，右下
	};


	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (n[i][j] != '9') {

				count = 0;
				for (auto& dir : directions) {
					int nrow = i + dir[0];
					int ncol = j + dir[1];

					// 检查边界
					if (nrow>= 0 && nrow < row && ncol >= 0 && ncol < col) {
						if (n[nrow][ncol] == '9') {
							count++;
						}
					}
				}
				n[i][j] = count+'0';//保存当前周围雷的数量,最多八个
			}
		}
	}
}

void uncover(int mrow,int mcol,int row, int col, char n[][30], int cover[][30], const CONSOLE_GRAPHICS_INFO* const pCGI)
{
	int nrow, ncol;
	int directions[8][2] =
	{
		{-1,-1}, {-1,0}, {-1,1},//左上，上，右上
		{0, -1}, {0, 1},//左 右
		{1, -1}, {1, 0}, {1, 1} //左下，下，右下
	};
	
	for (auto& dir : directions) {
		 nrow = mrow + dir[0];
		 ncol = mcol + dir[1];

		// 检查边界 周围一定是带数字的或者空白
		if (nrow >= 0 && nrow < row && ncol >= 0 && ncol < col&&cover[nrow][ncol]==0) {//还没被翻开过 防止多次遍历
			if (n[nrow][ncol] == '0') {//空白 进入下一次递归
				cover[nrow][ncol] = 1;
				gmw_draw_block(pCGI, nrow, ncol, n[nrow][ncol] - '0', bdi_uncover);
				uncover(nrow, ncol, row, col, n, cover, pCGI);
			}
			else {//有数字 不进入下一次递归
				cover[nrow][ncol] = 1;
				gmw_draw_block(pCGI, nrow, ncol, n[nrow][ncol] - '0', bdi_uncover);
			}
		}
	}


}

void mouseread(int row, int col, char n[][30], int cover[][30],int *num_mines, const CONSOLE_GRAPHICS_INFO* const pCGI)
{
	bool b = false, c = false;
	int loop = 1;
	int maction, old_mrow, old_mcol, mrow = -1, mcol = -1;
	int keycode1, keycode2;
	int ret;
	char temp[256];

	LARGE_INTEGER frequency;  // 计时器频率
	LARGE_INTEGER start, end; // 开始和结束的时间点
	// 获取计时器的频率
	QueryPerformanceFrequency(&frequency);
	// 获取开始时间
	QueryPerformanceCounter(&start);

	cct_enable_mouse();

	/* 打印初始光标位置[0,0] */
	cct_setcursor(CURSOR_INVISIBLE);	//关闭光标

	while (loop) {
		old_mrow = mrow;
		old_mcol = mcol;
		ret = gmw_read_keyboard_and_mouse(pCGI, maction, mrow, mcol, keycode1, keycode2);

		if (ret == CCT_MOUSE_EVENT) {
			if (maction == MOUSE_ONLY_MOVED) {
			}
			else if (maction == MOUSE_LEFT_BUTTON_CLICK) {
				if (cover[mrow][mcol] == 0) {//还没有被打开
					cover[mrow][mcol] = 1;//打开
					if (n[mrow][mcol] == '9') {
						gmw_draw_block(pCGI, mrow, mcol, n[mrow][mcol] - '0', bdi_uncover);
						sprintf(temp, "剩余雷数：%d ", *num_mines);
						gmw_status_line(pCGI, TOP_STATUS_LINE, "ESC退出，空格显示时间", temp);
						
						QueryPerformanceCounter(&end);

						sprintf(temp, "总用时：%lf ", (end.QuadPart - start.QuadPart) * 1.0 / frequency.QuadPart);
						gmw_status_line(pCGI, LOWER_STATUS_LINE, "你输了！！！", temp);
						loop = 0;//退回main函数结束游戏
					}
					else if (n[mrow][mcol] == '0') {
						gmw_draw_block(pCGI, mrow, mcol, n[mrow][mcol] - '0', bdi_uncover);
						uncover(mrow,mcol,row, col, n, cover, pCGI);

					}
					else {
						gmw_draw_block(pCGI, mrow, mcol, n[mrow][mcol] - '0', bdi_uncover);
					}
				}//其他情况继续读鼠标
			}
			

		}
		if (ret == CCT_KEYBOARD_EVENT) {
			if (keycode1 == 27) {//ESC 退出当前游戏
				loop = 0;


			}
			if (keycode1 == 32) {//空格显示时间

				QueryPerformanceCounter(&end);
				sprintf(temp, "当前用时：%lf ", (end.QuadPart - start.QuadPart) * 1.0 / frequency.QuadPart);
				gmw_status_line(pCGI, TOP_STATUS_LINE, "ESC退出，空格显示时间", temp);
			}
		}
		int num=row*col;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (cover[i][j] == 1)
					num--;
			}
		}
		if (num == *num_mines) {
			loop = 0;
			gmw_status_line(pCGI, LOWER_STATUS_LINE, "你成功了！游戏结束！");
		}
			

	}//end of while


	cct_disable_mouse();	//禁用鼠标







}