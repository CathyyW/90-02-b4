/* 2354180 ���Ϻ� �ƿ� */
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
		cct_setfontsize("������", 16);
		cct_setconsoleborder(100, 40);
		cct_setcursor(CURSOR_INVISIBLE);	//�رչ��
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
		CONSOLE_GRAPHICS_INFO Popstar; //����һ��CGI����

		/*��ȱʡֵ��ʼ�������ڱ�����/ǰ���ף�����16*8�����������޶������У�����״̬�����У����к�/�б꣬�������Ϊ˫�ߣ�ɫ����2/�߶�1/��С�߿���ɫ�ԣ�*/
		gmw_init(&Popstar);

		gmw_set_rowcol(&Popstar, row, col);
		gmw_set_color(&Popstar, COLOR_BLACK, COLOR_WHITE);
		gmw_set_font(&Popstar, "������", 16, 8);
		gmw_set_frame_style(&Popstar, 6, 3, true);	//ɫ����߿򣬿��Ϊ6���߶�Ϊ3
		gmw_set_frame_color(&Popstar, COLOR_WHITE, COLOR_BLACK);
		gmw_set_block_border_switch(&Popstar, true);
		gmw_set_rowno_switch(&Popstar, true);//��ʾ�к�
		gmw_set_colno_switch(&Popstar, true);//��ʾ�б�

		//��ʾ���
		gmw_draw_frame(&Popstar);
		/* ��״̬����ʾ���� */
		char temp[256];
		sprintf(temp, "%d��%d��", Popstar.lines, Popstar.cols);
		gmw_status_line(&Popstar, TOP_STATUS_LINE, temp);

		//��ʾ�ڲ�ֵ/* ���ڲ�����չ�ֵ���Ļ�� */
		for (i = 0; i < row; i++)
			for (j = 0; j < col; j++) {
				gmw_draw_block(&Popstar, i, j, n[i][j] - '0', bdi_normal);
			}
		to_be_continued(gname, "��ʼ�����", &Popstar);//���س�����ʼ��Ϸ

		c = searchall(row, col, n); //����������ֵͬ���ų�0��
		while (c) {

			mouse_keyboard(row, col, n, hint, &Popstar);


			scoresum(row, col, &score, &sum, n, hint);//����÷�

			sprintf(temp, "���ε÷�:%d �ܵ÷�:%d", score, sum);
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


			gmw_status_line(&Popstar, LOWER_STATUS_LINE, "���»س���������һ�غϣ���c���˳���Ϸ");
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
			
			sprintf(temp, "ʣ��%d��������������ؽ���������", row * col - sum / 5);
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