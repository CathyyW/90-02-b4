/* 2354180 ���Ϻ� �ƿ� */
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
		cct_setfontsize("������", 16);
		cct_setconsoleborder(100, 40);
		cct_setcursor(CURSOR_INVISIBLE);	//�رչ��
		
		int row, col, score = 0;
		char n[9][9];
		int hint[9][9] = { 0 };
		cct_cls();
		input(&row, &col, n[0], 1);
		printbase(row, col, n[0], 1);
		cout << endl;
		const char* gname = "MagicBall";
		cout << "��ʼ������ʾ���,���س�������...";
		while (_getch() != '\r')
			;
 
		cct_cls();
		
		CONSOLE_GRAPHICS_INFO Magicball; //����һ��CGI����
		/*��ȱʡֵ��ʼ�������ڱ�����/ǰ���ף�����16*8�����������޶������У�����״̬�����У����к�/�б꣬�������Ϊ˫�ߣ�ɫ����2/�߶�1/��С�߿���ɫ�ԣ�*/
		gmw_init(&Magicball);

		//��ʼ������ֵ
		gmw_set_rowcol(&Magicball, row, col);
		//��ʼ��ϸ��
		gmw_set_ext_rowcol(&Magicball, 0, 0, 0, 2);						//�ұ���30��
		gmw_set_color(&Magicball, COLOR_BLACK, COLOR_HWHITE);			//����������ɫ
		gmw_set_font(&Magicball, "������", 36);							//����
		gmw_set_frame_style(&Magicball, 2, 1, false);									//��Ϸ��������ÿ��ɫ���2��1���зָ���
		gmw_set_frame_default_linetype(&Magicball, 1);					//��Ϸ����������
		gmw_set_frame_color(&Magicball, COLOR_HWHITE, COLOR_BLACK);		//��Ϸ��������ɫ
		gmw_set_rowno_switch(&Magicball, false);							//����ʾ�к�
		gmw_set_colno_switch(&Magicball, false);							//����ʾ�б�
		gmw_set_status_line_switch(&Magicball, TOP_STATUS_LINE, true);	//����Ҫ��״̬��
		gmw_set_status_line_switch(&Magicball, LOWER_STATUS_LINE, true);	//��Ҫ��״̬��

		//��ʾ���
		gmw_draw_frame(&Magicball);

		char temp[256];
		char temp2[256];
		/* ��״̬����ʾ���� */
		sprintf(temp, "%d��%d��", Magicball.lines, Magicball.cols);
		sprintf(temp2, " ������%d", score);
		gmw_status_line(&Magicball, TOP_STATUS_LINE, temp2, temp);

		/* ���ڲ�����չ�ֵ���Ļ�� */
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				gmw_draw_block(&Magicball, i, j, n[i][j] - '0', bdi_normal);
			}
		}
		to_be_continued(gname, "��ʼ�����", &Magicball);
		bool b = true;
		bool c = true;
		b = searchball0(row, col, n);

		if (!b) {//����������ʾ
			c=hintball(row, col, n, hint, &Magicball);
			if (!c) {
				gmw_status_line(&Magicball, LOWER_STATUS_LINE, "���޿��������Ϸ����");


				cct_setcolor(Magicball.area_bgcolor, Magicball.area_fgcolor); //�ָ���ʼ��ɫ

				char ch = '0';
				while (ch != 'c' && ch != 'q') {
					cct_gotoxy(0, Magicball.SLI.lower_start_y + 2);//����赽ָ��λ��
					cout << setw(Magicball.cols - 1) << ' '; //���ÿո��������

					cct_gotoxy(0, Magicball.SLI.lower_start_y + 2);//����赽ָ��λ��

					cout << gname << '-' << "����c����������q�˳�";

					ch = getchar();
				}
				if (ch == 'c')
					continue;
				else
					break;
			}

		}
		else {//һֱѭ��ֱ����ǰ�޳�ʼ��������
			while (b) {

				deleteball(row, col, n, &Magicball);

				fillball(row, col, n, &Magicball);


				b = searchball0(row, col, n);
			}

			hintball(row, col, n, hint, &Magicball);
		}
		//��ʽ��ʼ�Ʒ�
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
				sprintf(temp, "%d��%d��", Magicball.lines, Magicball.cols);
				sprintf(temp2, " ������%d", score);
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
		gmw_status_line(&Magicball, LOWER_STATUS_LINE, "���޿��������Ϸ����");


		int ret = endpcgi(&Magicball, gname);

		if (ret == 1)
			continue;
		else
			break;

	}
	return 0;
}