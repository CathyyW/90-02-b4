/* 2354180 ���Ϻ� �ƿ� */
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
		cct_setfontsize("������", 16);
		cct_setconsoleborder(100, 40);
		cct_setcursor(CURSOR_INVISIBLE);	//�رչ��
		cct_cls();
		int row, col, num_mines;


		char n[16][30];//�׵�������鷶Χ
		int cover[16][30] = { 0 };//�Ƿ��

		input_mines(n, &row, &col, &num_mines);
		cct_cls();

		const char* gname = "Minessweeper";
		CONSOLE_GRAPHICS_INFO Minesweeper; //����һ��CGI����

		/*��ȱʡֵ��ʼ�������ڱ�����/ǰ���ף�����16*8�����������޶������У�����״̬�����У����к�/�б꣬�������Ϊ˫�ߣ�ɫ����2/�߶�1/��С�߿���ɫ�ԣ�*/
		gmw_init(&Minesweeper);

		gmw_set_rowcol(&Minesweeper, row, col);
		gmw_set_color(&Minesweeper, COLOR_BLACK, COLOR_WHITE);
		gmw_set_font(&Minesweeper, "������", 16, 8);
		gmw_set_frame_style(&Minesweeper, 4, 2, true);	//ɫ����߿򣬿��Ϊ6���߶�Ϊ3
		gmw_set_frame_color(&Minesweeper, COLOR_HWHITE, COLOR_BLACK);
		gmw_set_block_border_switch(&Minesweeper, false);
		gmw_set_rowno_switch(&Minesweeper, true);//��ʾ�к�
		gmw_set_colno_switch(&Minesweeper, true);//��ʾ�б�

		//��ʾ���
		gmw_draw_frame(&Minesweeper);
		/* ��״̬����ʾ���� */
		gmw_status_line(&Minesweeper, TOP_STATUS_LINE, "ESC�˳����ո���ʾʱ��");
		//��ʼ��ɫ��ֵ
		init_mines(n, row, col);

		//��ӡɫ��
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				gmw_draw_block(&Minesweeper, i, j, n[i][j] - '0', bdi_cover);
			}
		}


		mouseread(row, col, n, cover, &num_mines, &Minesweeper);//��ʼ��Ϸ

		int ret = endpcgi(&Minesweeper, gname);

		if (ret == 1)
			continue;
		else
			break;
	}

}