/* 2354180 王韵涵 计科 */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include<conio.h>
#include "../include/cmd_gmw_tools.h"
#include "../include/cmd_console_tools.h"
#include "90-02-b1-gmw.h"
#include"../include/common_tools.h"

using namespace std;

int main()
{
	while (1) {
		cct_setfontsize("新宋体", 16);
		cct_setconsoleborder(100, 40);
		cct_setcursor(CURSOR_INVISIBLE);	//关闭光标
		cct_cls();
		int row, col;
		int i, j;
		bool c = false;
		bool d = false;
		char n[10][10];
		char hint[10][10] = { 0 };
		int sum = 0, score = 0;
		input(&row, &col, n[0], 2);
		cct_cls();

		const char* gname = "PopStar";
		CONSOLE_GRAPHICS_INFO Popstar; //声明一个CGI变量

		/*用缺省值初始化（窗口背景黑/前景白，点阵16*8，上下左右无额外行列，上下状态栏均有，无行号/列标，框架线型为双线，色块宽度2/高度1/无小边框，颜色略）*/
		gmw_init(&Popstar);

		gmw_set_rowcol(&Popstar, row, col);
		gmw_set_color(&Popstar, COLOR_BLACK, COLOR_WHITE);
		gmw_set_font(&Popstar, "新宋体", 16, 8);
		gmw_set_frame_style(&Popstar, 6, 3, true);	//色块带边框，宽度为6，高度为3
		gmw_set_frame_color(&Popstar, COLOR_WHITE, COLOR_BLACK);
		gmw_set_block_border_switch(&Popstar, true);
		gmw_set_rowno_switch(&Popstar, true);//显示行号
		gmw_set_colno_switch(&Popstar, true);//显示列标

		//显示框架
		gmw_draw_frame(&Popstar);
		/* 上状态栏显示内容 */
		char temp[256];
		sprintf(temp, "%d行%d列", Popstar.lines, Popstar.cols);
		gmw_status_line(&Popstar, TOP_STATUS_LINE, temp);

		//显示内部值/* 将内部数组展现到屏幕上 */
		for (i = 0; i < row; i++)
			for (j = 0; j < col; j++) {
				gmw_draw_block(&Popstar, i, j, n[i][j] - '0', bdi_normal);
			}
		to_be_continued(gname, "初始化完毕", &Popstar);//按回车键开始游戏

		c = searchall(row, col, n); //有无连续相同值（排除0）
		while (c) {

			mouse_keyboard(row, col, n, hint, &Popstar);


			scoresum(row, col, &score, &sum, n, hint);//计算得分

			sprintf(temp, "本次得分:%d 总得分:%d", score, sum);
			gmw_status_line(&Popstar, TOP_STATUS_LINE, temp);


			for (i = 0; i < 10; ++i) {
				for (j = 0; j < 10; ++j) {
					if (hint[i][j] == '*')
						hint[i][j] = '0';
				}
			}

			star_down(row, col, n, &Popstar);

			d = refreshright(row, col, n, 1, &Popstar);
			if (d)
				refreshright(row, col, n, 3, &Popstar);
			c = searchall(row, col, n);


			gmw_status_line(&Popstar, LOWER_STATUS_LINE, "按下回车键进行下一回合，按c可退出游戏");
			char button = '0';
			while (button != 'c' && button != '\n' && button != '\r') {
				button = _getche();
			}
			if (button == 'c')
				break;
			if (button == '\n' || button == '\r')
				continue;
		}

		if (c == false) {
			
			sprintf(temp, "剩余%d个不可消除项，本关结束！！！", row * col - sum / 5);
			gmw_status_line(&Popstar, LOWER_STATUS_LINE, temp);
		}

		int ret = endpcgi(&Popstar, gname);

		if (ret==1)
			continue;
		else
			break;

	}
	return 0;
}