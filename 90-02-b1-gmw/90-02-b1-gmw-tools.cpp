/* 2354180 ���Ϻ� �ƿ� */
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

	//�ж���Χ�Ƿ�����ͬɫ��
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
	//�ݹ鷽ʽ������ѡ�����ͬɫ����
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
	
	bool judge = false;//�ж��Ƿ�������ֵ

	if (step == 0) {//Ϳ��
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

		judge = searcharound(row, col, mrow,mcol, n, 1, hint);//��鵱ǰɫ����Χ����ֵͬ
		if (judge) {
			searcharound(row, col, mrow, mcol, n, 2, hint);//��ѡ�к���Χȫ������
			for (i = 0; i < row; i++) {
				for (j = 0; j < col; j++) {
					if (hint[i][j] == '*')//���˴�ѡ�е�Ϳ��
						gmw_draw_block(pCGI,i,j, n[i][j] - '0', bdi_related);
				}
			}
		}
		else {
			
			gmw_status_line(pCGI, LOWER_STATUS_LINE, "��Χ����ͬ����,������ѡ��");
			Sleep(500);
			return false;
		}
	}
	return true;
}

void to_be_continued(const char* game_name, const char* prompt, const CONSOLE_GRAPHICS_INFO* const bgi)
{

	if (bgi->inited == CGI_INITED) { //��ʼ����
		cct_setcolor(bgi->area_bgcolor, bgi->area_fgcolor); //�ָ���ʼ��ɫ

		cct_gotoxy(0, bgi->SLI.lower_start_y + 2);//����赽ָ��λ��
		cout << setw(bgi->cols - 1) << ' '; //���ÿո��������

		cct_gotoxy(0, bgi->SLI.lower_start_y + 2);//����赽ָ��λ��
		cout << game_name << '-' << (bgi->CFI.separator ? "��" : "��") << "�ָ���-" << prompt << "�����س�������...";
	}
	else {
		cct_setcolor(); //�ָ�ȱʡ��ɫ
		cct_gotoxy(0, 0);//����赽ָ��λ��
		cout << game_name << '-' << prompt << "�����س�������...   ";
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
	int maction, old_mrow, old_mcol, mrow =0 , mcol = 0;//��ʼֵ���Ͻ�0,0
	int keycode1, keycode2;
	int ret;
	char temp[256];
	cct_enable_mouse();

	/* ��ӡ��ʼ���λ��[0,0] */
	cct_setcursor(CURSOR_INVISIBLE);	//�رչ��
	while (loop) {
		old_mrow = mrow;
		old_mcol = mcol;
		ret = gmw_read_keyboard_and_mouse(pCGI, maction, mrow, mcol, keycode1, keycode2);
		
		
		if (ret == CCT_MOUSE_EVENT) {
			if (maction == MOUSE_ONLY_MOVED) {
				
				if (n[mrow][mcol] != '0') {//�����Ѿ�������״̬
					//�µ��԰״���
					gmw_draw_block(pCGI, mrow, mcol, n[mrow][mcol] - '0', bdi_selected);
					//�ɵ��Ժ�
					if(old_mrow>=0&&old_mcol>=0)
						gmw_draw_block(pCGI, old_mrow, old_mcol, n[old_mrow][old_mcol] - '0', bdi_normal);
					
				}
				else {
					gmw_status_line(pCGI, LOWER_STATUS_LINE, "[��ǰ���] λ�÷Ƿ�");//��ס�����������
					if (old_mrow >= 0 && old_mcol >= 0)
						gmw_draw_block(pCGI, old_mrow, old_mcol, n[old_mrow][old_mcol] - '0', bdi_normal);
				}

			}
			if (maction == MOUSE_LEFT_BUTTON_CLICK) {
				if (n[mrow][mcol] != '0') {//�����Ѿ�������״̬
					
						sprintf(temp, "[��ǰѡ��] %c��%d��", char('A' + mrow), mcol); //δ����mrow����26��mcol����99�������������Ҫ�������д���
						gmw_status_line(pCGI, LOWER_STATUS_LINE, temp);
						//���ѡ������Χ
						bool d;
						d = printaround(mrow, mcol, row, col, n, 1, hint, pCGI);//Ϳ��
						
					
						while (d) {
							gmw_status_line(pCGI, LOWER_STATUS_LINE, "��ͷ��/����ƶ�ȡ����ǰѡ�񣬻س���/��������ϳ�");
							int secondx, secondy;
							ret = cct_read_keyboard_and_mouse(secondx, secondy, maction, keycode1, keycode2);
							if ((mrow== (secondy + 1) / 4 - 1) && (mcol == (secondx + 4) / 8)-1 && (maction == MOUSE_LEFT_BUTTON_CLICK || keycode1 == 13)) {
								clear(mrow, mcol, row, col, n, hint,pCGI);//�ϲ�����
								loop = 0;
								break;
							}
							if (mrow!= (secondy + 1) / 4 - 1 || (mcol!= (secondx + 4) / 8-1)) {
								printaround(mrow, mcol, row, col, n, 0, hint,pCGI);//Ĩ��
								break;
							}
						}
						gmw_status_line(pCGI, LOWER_STATUS_LINE, "                                                   ");//����
					

				}
				else {
					gmw_status_line(pCGI, LOWER_STATUS_LINE, "[��ǰ���] λ�÷Ƿ�");//��ס�����������

				}
			}

			
		}//������
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
					//�µ��԰״���
					gmw_draw_block(pCGI, mrow, mcol, n[mrow][mcol] - '0', bdi_selected);
					//�ɵ��Ժ�
					if (old_mrow >= 0 && old_mcol >= 0)
						gmw_draw_block(pCGI, old_mrow, old_mcol, n[old_mrow][old_mcol] - '0', bdi_normal);
					sprintf(temp, "[��ǰ����] %d��%d��", mrow, mcol);
					gmw_status_line(pCGI, LOWER_STATUS_LINE, temp);


				}
				else {
					gmw_status_line(pCGI, LOWER_STATUS_LINE, "[��ǰ����] λ�÷Ƿ�");
					if (old_mrow >= 0 && old_mcol >= 0)
						gmw_draw_block(pCGI, old_mrow, old_mcol, n[old_mrow][old_mcol] - '0', bdi_normal);
				}
			}
			else if (keycode1 == 13) {
				if (n[mrow][mcol] != '0') {//�����Ѿ�������״̬

					sprintf(temp, "[��ǰѡ��] %c��%d��", char('A' + mrow), mcol); //δ����mrow����26��mcol����99�������������Ҫ�������д���
					gmw_status_line(pCGI, LOWER_STATUS_LINE, temp);
					//���ѡ������Χ
					bool d;
					d = printaround(mrow, mcol, row, col, n, 1, hint, pCGI);//Ϳ��

					while (d) {
						gmw_status_line(pCGI, LOWER_STATUS_LINE, "��ͷ��/����ƶ�ȡ����ǰѡ�񣬻س���/��������ϳ�");
						int secondx, secondy;
						ret = cct_read_keyboard_and_mouse(secondx, secondy, maction, keycode1, keycode2);
						if (((mrow == (secondy + 1) / 4 - 1 && mcol == (secondx + 4) / 8) - 1 && maction == MOUSE_LEFT_BUTTON_CLICK) ||( keycode1 == 13)) {
							clear(mrow, mcol, row, col, n, hint, pCGI);//�ϲ�����
							loop = 0;
							break;
						}
						if (mrow != (secondy + 1) / 4 - 1 || (mcol != (secondx + 4) / 8 - 1)) {
							printaround(mrow, mcol, row, col, n, 0, hint, pCGI);//Ĩ��
							break;
						}
					}
					gmw_status_line(pCGI, LOWER_STATUS_LINE, "                                                   ");//����


				}
				else {
					gmw_status_line(pCGI, LOWER_STATUS_LINE, "[��ǰ����] λ�÷Ƿ�");//��ס�����������

				}


			}

		}

	}

	cct_disable_mouse();	//�������
	



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
				hint[j] = 1;//���Ҫ�ƶ�����
				number++;//���е�����
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