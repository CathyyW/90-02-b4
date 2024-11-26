/* 2354180 王韵涵 计科 */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include<conio.h>
#include "../include/cmd_gmw_tools.h"
#include "../include/cmd_console_tools.h"
#include "90-01-b2-gmw.h"
#include"../include/common_tools.h"

using namespace std;
int main()
{
	while (1) {
		cct_setfontsize("新宋体", 16);
		cct_setconsoleborder(100, 40);
		cct_setcursor(CURSOR_INVISIBLE);	//关闭光标
		
		int row, col, score = 0;
		char n[9][9];
		int hint[9][9] = { 0 };
		cct_cls();
		input(&row, &col, n[0], 1);
		printbase(row, col, n[0], 1);
		cout << endl;
		const char* gname = "MagicBall";
		cout << "初始数组显示完毕,按回车键继续...";
		while (_getch() != '\r')
			;
 
		cct_cls();
		
		CONSOLE_GRAPHICS_INFO Magicball; //声明一个CGI变量
		/*用缺省值初始化（窗口背景黑/前景白，点阵16*8，上下左右无额外行列，上下状态栏均有，无行号/列标，框架线型为双线，色块宽度2/高度1/无小边框，颜色略）*/
		gmw_init(&Magicball);

		//初始化行列值
		gmw_set_rowcol(&Magicball, row, col);
		//初始化细节
		gmw_set_ext_rowcol(&Magicball, 0, 0, 0, 2);						//右边留30列
		gmw_set_color(&Magicball, COLOR_BLACK, COLOR_HWHITE);			//整个窗口颜色
		gmw_set_font(&Magicball, "新宋体", 36);							//字体
		gmw_set_frame_style(&Magicball, 2, 1, false);									//游戏主区域风格：每个色块宽2高1，有分隔线
		gmw_set_frame_default_linetype(&Magicball, 1);					//游戏主区域线型
		gmw_set_frame_color(&Magicball, COLOR_HWHITE, COLOR_BLACK);		//游戏主区域颜色
		gmw_set_rowno_switch(&Magicball, false);							//不显示行号
		gmw_set_colno_switch(&Magicball, false);							//不显示列标
		gmw_set_status_line_switch(&Magicball, TOP_STATUS_LINE, true);	//不需要上状态栏
		gmw_set_status_line_switch(&Magicball, LOWER_STATUS_LINE, true);	//需要下状态栏

		//显示框架
		gmw_draw_frame(&Magicball);

		char temp[256];
		char temp2[256];
		/* 上状态栏显示内容 */
		sprintf(temp, "%d行%d列", Magicball.lines, Magicball.cols);
		sprintf(temp2, " 分数：%d", score);
		gmw_status_line(&Magicball, TOP_STATUS_LINE, temp2, temp);

		/* 将内部数组展现到屏幕上 */
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				gmw_draw_block(&Magicball, i, j, n[i][j] - '0', bdi_normal);
			}
		}
		to_be_continued(gname, "初始化完毕", &Magicball);
		bool b = true;
		bool c = true;
		b = searchball0(row, col, n);

		if (!b) {//给出消除提示
			c=hintball(row, col, n, hint, &Magicball);
			if (!c) {
				gmw_status_line(&Magicball, LOWER_STATUS_LINE, "已无可消除项，游戏结束");


				cct_setcolor(Magicball.area_bgcolor, Magicball.area_fgcolor); //恢复初始颜色

				char ch = '0';
				while (ch != 'c' && ch != 'q') {
					cct_gotoxy(0, Magicball.SLI.lower_start_y + 2);//光标设到指定位置
					cout << setw(Magicball.cols - 1) << ' '; //先用空格清空整行

					cct_gotoxy(0, Magicball.SLI.lower_start_y + 2);//光标设到指定位置

					cout << gname << '-' << "输入c继续，输入q退出";

					ch = getchar();
				}
				if (ch == 'c')
					continue;
				else
					break;
			}

		}
		else {//一直循环直到当前无初始可消除项
			while (b) {

				deleteball(row, col, n, &Magicball);

				fillball(row, col, n, &Magicball);


				b = searchball0(row, col, n);
			}

			hintball(row, col, n, hint, &Magicball);
		}
		//正式开始计分
		mouseread(row, col, n, hint, &Magicball);

		changeball(row, col, n, hint, &Magicball);

		while (1) {

			b = searchball0(row, col, n);

			while (b) {


				deleteball(row, col, n, &Magicball);
				for (int i = 0; i < row; i++) {
					for (int j = 0; j < col; j++) {
						if (n[i][j] == '0')
							score++;
					}
				}
				sprintf(temp, "%d行%d列", Magicball.lines, Magicball.cols);
				sprintf(temp2, " 分数：%d", score);
				gmw_status_line(&Magicball, TOP_STATUS_LINE, temp2, temp);

				fillball(row, col, n, &Magicball);
				b = searchball0(row, col, n);
			}

			c = hintball(row, col, n, hint, &Magicball);
			if (c == false) {
				break;
			}

			mouseread(row, col, n, hint, &Magicball);

			changeball(row, col, n, hint, &Magicball);



		}
		gmw_status_line(&Magicball, LOWER_STATUS_LINE, "已无可消除项，游戏结束");


		int ret = endpcgi(&Magicball, gname);

		if (ret == 1)
			continue;
		else
			break;

	}
	return 0;
}