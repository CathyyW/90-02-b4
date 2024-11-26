/* 2354180 王韵涵 计科 */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include<conio.h>
#include "../include/cmd_gmw_tools.h"
#include "../include/cmd_console_tools.h"
#include "90-02-b2.h"
#include"../include/common_tools.h"
#include<Windows.h>

using namespace std;

int main()
{
	while (1) {
		cct_setfontsize("新宋体", 16);
		cct_setconsoleborder(100, 40);
		cct_setcursor(CURSOR_INVISIBLE);	//关闭光标
		cct_cls();
		int row, col, num_mines;


		char n[16][30];//雷的最大数组范围
		int cover[16][30] = { 0 };//是否打开

		input_mines(n, &row, &col, &num_mines);
		cct_cls();

		const char* gname = "Minessweeper";
		CONSOLE_GRAPHICS_INFO Minesweeper; //声明一个CGI变量

		/*用缺省值初始化（窗口背景黑/前景白，点阵16*8，上下左右无额外行列，上下状态栏均有，无行号/列标，框架线型为双线，色块宽度2/高度1/无小边框，颜色略）*/
		gmw_init(&Minesweeper);

		gmw_set_rowcol(&Minesweeper, row, col);
		gmw_set_color(&Minesweeper, COLOR_BLACK, COLOR_WHITE);
		gmw_set_font(&Minesweeper, "新宋体", 16, 8);
		gmw_set_frame_style(&Minesweeper, 4, 2, true);	//色块带边框，宽度为6，高度为3
		gmw_set_frame_color(&Minesweeper, COLOR_HWHITE, COLOR_BLACK);
		gmw_set_block_border_switch(&Minesweeper, false);
		gmw_set_rowno_switch(&Minesweeper, true);//显示行号
		gmw_set_colno_switch(&Minesweeper, true);//显示列标

		//显示框架
		gmw_draw_frame(&Minesweeper);
		/* 上状态栏显示内容 */
		gmw_status_line(&Minesweeper, TOP_STATUS_LINE, "ESC退出，空格显示时间");
		//初始化色块值
		init_mines(n, row, col);

		//打印色块
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				gmw_draw_block(&Minesweeper, i, j, n[i][j] - '0', bdi_cover);
			}
		}


		mouseread(row, col, n, cover, &num_mines, &Minesweeper);//开始游戏

		int ret = endpcgi(&Minesweeper, gname);

		if (ret == 1)
			continue;
		else
			break;
	}

}