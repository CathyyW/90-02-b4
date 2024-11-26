/* 2354180 �ƿ� ���Ϻ� */
#include <iostream>
#include<iomanip>
#include<conio.h>
#include<Windows.h>
#include "../include/cmd_console_tools.h"
#include"../include/common_menu.h"
#include"../include/common_tools.h"
#include"90-02-b1.h"
using namespace std;

bool search(int row, int col,char cord_r,char cord_c,char* str, int step,char hint[][10])
{
	
	int cord_h, cord_l;
	cord_h = cord_r - 'A' ; //ʵ�ʵ�һ�У���ʾΪ0
	cord_l = cord_c - '0' ;
	
	if (step == 1) {
		//left,right,up,down
		if ((str[cord_h * 10 + cord_l - 1] == str[cord_h * 10 + cord_l] && cord_l - 1 >= 0) || (
			str[cord_h * 10 + cord_l + 1] == str[cord_h * 10 + cord_l] && cord_l + 1 < col) ||
			(str[(cord_h - 1) * 10 + cord_l] == str[cord_h * 10 + cord_l] && cord_h - 1 >= 0) ||
			(str[(cord_h + 1) * 10 + cord_l] == str[cord_h * 10 + cord_l] && cord_h + 1 < row)) {

			return true;
		}
		return false;
	}
	if (str[cord_h * 10 + cord_l - 1] == str[cord_h * 10 + cord_l] && cord_l - 1 >= 0) {
		if (hint[cord_h][cord_l - 1] != '*' ||hint[cord_h][cord_l] != '*') {
			hint[cord_h][cord_l - 1] = '*';
			hint[cord_h][cord_l] = '*';
			search(row, col, cord_r, cord_c - 1, str, 2, hint);//left
		}
	}
	if (str[cord_h * 10 + cord_l + 1] == str[cord_h * 10 + cord_l] && cord_l+ 1 < col) {
		if (hint[cord_h][cord_l + 1] != '*' || hint[cord_h][cord_l] != '*') {
			hint[cord_h][cord_l + 1] = '*';
			hint[cord_h][cord_l] = '*';
			search(row, col, cord_r, cord_c + 1, str, 2, hint);//right
		}
	}
	if (str[(cord_h - 1) * 10 + cord_l] == str[cord_h * 10 + cord_l] && cord_h - 1 >= 0) {
		if (hint[cord_h-1][cord_l] != '*' || hint[cord_h][cord_l] != '*') {
			hint[(cord_h - 1)][cord_l] = '*';
			hint[cord_h][cord_l] = '*';
			search(row, col, cord_r - 1, cord_c, str, 2, hint);//up
		}
	}
	if (str[(cord_h + 1) * 10 + cord_l] == str[cord_h * 10 + cord_l] && cord_h + 1 < row) {
		if (hint[cord_h + 1][cord_l] != '*'|| hint[cord_h][cord_l] != '*') {
			hint[(cord_h + 1)][cord_l] = '*';
			hint[cord_h][cord_l] = '*';
			search(row, col, cord_r + 1, cord_c, str, 2, hint);//down
		}
	}
	
	
	
	return true;
}
void printconse(int row, int col, char n[][10], char hint[][10], int step)
{
	if (step == 1)
		cout << "���ҽ�����飺" << endl;
	if (step == 2)
		cout << "������飨��ͬ��ʶ����" << endl;
	if (step == 3) {
		cout << "��ֵͬ�鲢�������(��ͬɫ��ʶ)��" << endl;
	}

	int i, j, x, y;
	cout << "  |";

	for (i = 0; i <= col - 1; i++) {
		cout << "  " << i;
	}
	cout << endl << "--+";
	cout << setfill('-') << setw(col * 3 + 1) << "" << endl;
	for (i = 0; i < row; i++) {
		cout << char('A' + i) << " |";
		for (j = 0; j < col; j++) {
			if (step == 1) {
				if (hint[i][j] == '\0') {
					cout << "  " << '0';
				}
				else {
					cout << "  " << hint[i][j];
				}
			}
			if (step == 2||step==3) {
				if (hint[i][j] == '*') {
					cout << "  ";
					cct_getxy(x, y);
					cct_showch(x, y, n[i][j], 14, 1);
					
					cct_setcolor();
				}
				else
					cout << "  " << n[i][j];

			}

		}
		cout << endl;
	}
}
void scoresum(int row, int col,int *score,int *sum,char n[][10], char hint[][10])
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
bool searchsame(int row, int col, char n[][10])
{
	int i, j;
	
	

	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {

			if (n[i - 1][j] == n[i][j] && i - 1 >= 0 &&n[i][j]!='0') {
				return true;
			}
			if (n[i][j - 1] == n[i][j] && j - 1 >= 0 && n[i][j]!='0') {
				return true;
			}
			if (n[i][j +1] == n[i][j] && j+ 1 <col && n[i][j] != '0') {
				return true;
			}
		    if (n[i+1][j] == n[i][j] && i+1<row&& n[i][j] != '0') {
				return true;
			}

		}
	}
	return false;
}
bool refreshright(int row, int col, char n[][10],int step,char choice)
{
	int i, j,t;
	bool d = false;
	int hint[10] = { 0 };
	for (j = 0; j < col; j++) {
		for (i = 0; i < row; i++) {
			if (n[i][j] != '0')
				break;
			if (i == row - 1) {
				hint[j] = 1;
				d = true;
			}
		}

	}
	if (step == 2||step==3) {
		for (i = col - 1; i >= 0; i--) {
			if (hint[i] == 1) {
				for (j=i; j + 1 < col; j++) {
					for (t = 0; t < row; t++) {

						n[t][j] = n[t][j + 1];
						n[t][j + 1] = '0';
						if (step == 3&&n[t][j]!='0') {
							cct_showstr(8 * (j + 2) , 4 * (t + 1)-1, "  ", 15, 15);
							cct_showstr(8 * (j + 2) , 4 * (t + 1), "  ", 15, 15);
							cct_showstr(8 * (j + 2) , 4 * (t + 1) + 1, "  ", 15, 15);

							cct_showstr(8 * (j + 2) -2, 4 * (t + 1) -1, "�[", n[t][j], 0);//��һ��
							cct_showstr(8 * (j + 2) -2, 4 * (t + 1) , "�U", n[t][j], 0);//�ڶ���
							cct_showstr(8 * (j + 2) -2, 4 * (t + 1) + 1, "�a", n[t][j], 0);//������

							cct_showstr(8 * (j + 2)-4 , 4 * (t + 1)-1, "�T", n[t][j], 0);//��һ��
							cct_showstr(8 * (j + 2 )-4, 4 * (t + 1) , "��", n[t][j], 0);//�ڶ���
							cct_showstr(8 * (j + 2)-4, 4* (t + 1) + 1, "�T", n[t][j], 0);//������

							cct_showstr(8 * (j + 2) - 6, 4 * (t + 1)-1, "�X", n[t][j], 0);//��һ��
							cct_showstr(8 * (j + 2) - 6, 4 * (t + 1) , "�U", n[t][j], 0);//�ڶ���
							cct_showstr(8 * (j + 2) -6, 4* (t + 1) + 1, "�^", n[t][j], 0);//������

							Sleep(10);

							cct_showstr(8 * (j + 2) - 2, 4 * (t + 1)-1, "  ", 15, 15);
							cct_showstr(8 * (j + 2) - 2, 4 * (t + 1) , "  ", 15, 15);
							cct_showstr(8 * (j + 2) - 2, 4 * (t + 1) +1, "  ", 15, 15);
					
							cct_showstr(8 * (j + 2) -4, 4 * (t + 1)-1, "�[", n[t][j], 0);//��һ��
							cct_showstr(8 * (j + 2) -4, 4 * (t + 1) , "�U", n[t][j], 0);//�ڶ���
							cct_showstr(8 * (j + 2)-4 ,  4* (t + 1) + 1, "�a", n[t][j], 0);//������

							cct_showstr(8 * (j + 2)-6, 4 * (t + 1)-1, "�T", n[t][j], 0);//��һ��
							cct_showstr(8 * (j + 2)-6, 4 * (t + 1) , "��", n[t][j], 0);//�ڶ���
							cct_showstr(8 * (j + 2)-6, 4 * (t + 1) + 1, "�T", n[t][j], 0);//������

							cct_showstr(8 * (j + 2) - 8, 4 * (t + 1)-1, "�X", n[t][j], 0);//��һ��
							cct_showstr(8 * (j + 2) - 8, 4 * (t + 1) , "�U", n[t][j], 0);//�ڶ���
							cct_showstr(8 * (j + 2) - 8, 4 * (t + 1) + 1, "�^", n[t][j], 0);//������
							
							Sleep(10);

							cct_showstr(8 * (j + 2)-4 , 4* (t + 1)-1, "  ", 15, 15);
							cct_showstr(8 * (j + 2) -4, 4 * (t + 1) , "  ", 15, 15);
							cct_showstr(8 * (j + 2) -4, 4 * (t + 1) + 1, "  ", 15, 15);

							cct_showstr(8 * (j + 2)-6, 4 * (t + 1)-1, "�[", n[t][j], 0);//��һ��
							cct_showstr(8 * (j + 2)-6, 4 * (t + 1) , "�U", n[t][j], 0);//�ڶ���
							cct_showstr(8 * (j + 2)-6, 4 * (t + 1) + 1, "�a", n[t][j], 0);//������

							cct_showstr(8 * (j + 2) - 8, 4 * (t + 1)-1, "�T", n[t][j], 0);//��һ��
							cct_showstr(8 * (j + 2) - 8, 4 * (t + 1)  , "��", n[t][j], 0);//�ڶ���
							cct_showstr(8 * (j + 2) - 8, 4 * (t + 1) + 1, "�T", n[t][j], 0);//������

							cct_showstr(8 * (j + 2) - 10, 4 * (t + 1)-1, "�X", n[t][j], 0);//��һ��
							cct_showstr(8 * (j + 2) - 10, 4 * (t + 1) , "�U", n[t][j], 0);//�ڶ���
							cct_showstr(8 * (j + 2) - 10, 4 * (t + 1) + 1, "�^", n[t][j], 0);//������

							Sleep(10);

							cct_showstr(8 * (j + 2) - 6, 4 * (t + 1) - 1, "��", 15, 0);
							cct_showstr(8 * (j + 2) - 6, 4 * (t + 1), "��", 15, 0);
							cct_showstr(8 * (j + 2) - 6, 4 * (t + 1) + 1, "��", 15, 0);

							cct_showstr(8 * (j + 2) - 8, 4 * (t + 1) - 1, "�[", n[t][j], 0);//��һ��
							cct_showstr(8 * (j + 2) - 8, 4 * (t + 1), "�U", n[t][j], 0);//�ڶ���
							cct_showstr(8 * (j + 2) - 8, 4 * (t + 1) + 1, "�a", n[t][j], 0);//������

							cct_showstr(8 * (j + 2) - 10, 4 * (t + 1) - 1, "�T", n[t][j], 0);//��һ��
							cct_showstr(8 * (j + 2) - 10, 4 * (t + 1), "��", n[t][j], 0);//�ڶ���
							cct_showstr(8 * (j + 2) - 10, 4 * (t + 1) + 1, "�T", n[t][j], 0);//������

							cct_showstr(8 * (j + 2) - 12, 4 * (t + 1) - 1, "�X", n[t][j], 0);//��һ��
							cct_showstr(8 * (j + 2) - 12, 4 * (t + 1), "�U", n[t][j], 0);//�ڶ���
							cct_showstr(8 * (j + 2) - 12, 4 * (t + 1) + 1, "�^", n[t][j], 0);//������

							Sleep(10);





							cct_setcolor();
						}

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
bool printaround(int X,int Y, int row, int col, char* str, char choice,int step,char hint[][10])
{
	

	int i, j;
	int k = 6, t = 3;
	char cord_r = 'A' + Y / 3 - 1;
	char cord_c = '0' + (X + 2) / 6 - 1;
	if (choice == 'G' || choice == 'g') {
		k = 8, t = 4;
		cord_r = 'A' + (Y + 1) / 4 - 1;
		cord_c = '0' + (X + 4) / 8-1;
	}
		
	bool judge = false;//�ж��Ƿ�������ֵ
	
	if (step == 0) {
		for (i = 0; i < row; i++) {
			for (j = 0; j < col; j++) {
				if (hint[i][j] == '*') {
					printstar(i, j, str, choice, 0);
					hint[i][j] = '0';
				}

			}
		}
	}
	
	if (((hint[Y / 3 - 1][(X + 2) / 6 - 1] != '*'&&(choice=='F'||choice=='f')&&step == 1)|| (hint[(Y + 1) / 4 - 1][(X + 4) / 8 - 1] != '*' && (choice == 'G' || choice == 'g')) && step == 1)) {

		
		judge = search(row, col, cord_r, cord_c, str, 1, hint);
		if (judge) {
			if(choice=='f'||choice=='F')
				cct_gotoxy(0, row * 3 + 5);
			if(choice=='G'||choice=='g')
				cct_gotoxy(0, row * 4 + 4);
			cout << "                                     ";
			search(row, col, cord_r, cord_c, str, 2, hint);
			for (i = 0; i < row; i++) {
				for (j = 0; j < col; j++) {
					if (hint[i][j] == '*')//���˴�ѡ�е�Ϳ��
						printstar(i, j, str, choice, 7);
				}
			}
		}
		else {
			if (choice == 'f' || choice == 'F') {
				cct_gotoxy(0, row * 3 + 5);
				cout << "                                     ";
				cct_gotoxy(0, row * 3 + 5);
			}
			if (choice == 'G' || choice == 'g') {
				cct_gotoxy(0, row * 4 + 4);
				cout << "                                     ";
				cct_gotoxy(0, row * 4 + 4);
			}
			cout << "��Χ����ֵͬ��������ѡ��!!!";
			Sleep(100);
			int x,y;
			cct_getxy(x, y);
			cct_gotoxy(0, y);
			cout << "                                ";
			return false;
		}
	}
	return true;
}


void mouse_keyboard(int row, int col, char choice, char* str,char hint[][10])
{
	int X = 4, Y = 3;
	
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;

	cct_enable_mouse();

	/* ��ӡ��ʼ���λ��[0,0] */
	cct_setcursor(CURSOR_INVISIBLE);	//�رչ��
	while (loop) {
		/* �����/���̣�����ֵΪ���������е�ĳһ��, ��ǰ���λ����<X,Y>�� */
		ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

		if (ret == CCT_MOUSE_EVENT) {

			switch (choice) {
				case 'D':
				case 'd':
				case 'F':
				case 'f':
					cct_gotoxy(0, row * 3 + 4);
					cout << "                                                   ";
					cct_gotoxy(0, row * 3 + 4);
					cout << "[��ǰ���] ";
					if (X >= 4 && X <= 9 + (col - 1) * 6 && Y >= 3 && Y <= 5 + (row - 1) * 3) {
						cout << char('A' + Y / 3 - 1) << "��" << (X + 2) / 6 - 1 << "��            ";
						printselect(X, Y, row, col, choice, str);//���԰�ɫ

						if (maction == MOUSE_LEFT_BUTTON_CLICK) {//��� 
							cct_gotoxy(0, row * 3 + 4);
							cout << "                                                   ";
							cct_gotoxy(0, row * 3 + 4);
							cout << "ѡ����" << char('A' + Y / 3 - 1) << "��" << (X + 2) / 6 - 1 << "��" << endl;
							if (choice == 'D' || choice == 'd')
								loop = 0;
							if (choice == 'F' || choice == 'f') {
								bool d;
								d = printaround(X, Y, row, col, str, choice,1,hint);//Ϳ��
								while (d) {
									int secondx, secondy;
									ret = cct_read_keyboard_and_mouse(secondx, secondy, maction, keycode1, keycode2);
									cct_gotoxy(0, row * 3 + 4);
									cout << "                                     ";
									cct_gotoxy(0, row * 3 + 4);
									cout << "��ͷ��/����ƶ�ȡ����ǰѡ�񣬻س���/��������ϳ�";
									if ((Y / 3 - 1 == secondy / 3 - 1) && ((X + 2) / 6 - 1 == (secondx + 2) / 6 - 1) && (maction == MOUSE_LEFT_BUTTON_CLICK || keycode1 == 13)) {
										clear(X, Y, row, col, choice, str,hint);//�ϲ�����
										loop = 0;
										break;
									}
									if ((Y / 3 - 1 != secondy / 3 - 1) || ((X + 2) / 6 - 1 != (secondx + 2) / 6 - 1)) {
										printaround(X, Y, row, col, str, choice,0,hint);//Ĩ��
										break;
									}
								}


							}

						}
					}
					else {
							cout << "λ�÷Ƿ�";
							printselect(X, Y, row, col, choice, str);//ȡ������
						}
					break;
				case 'E':
				case 'e':
				case 'G':
				case 'g':
					cct_gotoxy(0, row * 4 + 3);
					cout << "                                                   ";
					cct_gotoxy(0, row * 4 + 3);
					cout << "[��ǰ���] ";
					if ((X + 4) % 8 >= 0 && (X + 4) % 8 <= 5 && X >= 4 && X <= 9 + (col - 1) * 8 && Y >= 3 && Y <= 4 * row + 1 && (Y + 1) % 4 >= 0 && (Y + 1) % 4 <= 2&&str[10* ((Y + 1) / 4 - 1)+ (X + 4) / 8 - 1]!='0') {
						cout << char('A' + (Y + 1) / 4 - 1) << "��" << (X + 4) / 8-1 << "��            ";
						printselect(X, Y, row, col, choice, str);//���԰�ɫ
						if (maction == MOUSE_LEFT_BUTTON_CLICK) {//��� 
							cct_gotoxy(0, row * 4 + 3);
							cout << "                                                   ";
							cct_gotoxy(0, row * 4 + 3);
							cout << "ѡ����" << char('A' + (Y + 1) / 4 - 1) << "��" << (X + 4) / 8-1 << "��" << endl;
							if (choice == 'E' || choice == 'e')
								loop = 0;
							if (choice == 'G' || choice == 'g') {
								bool d;
								d = printaround(X, Y, row, col, str, choice, 1,hint);//Ϳ��
								while (d) {
									int secondx, secondy;
									ret = cct_read_keyboard_and_mouse(secondx, secondy, maction, keycode1, keycode2);
									cct_gotoxy(0, row * 4 + 3);
									cout << "                                     ";
									cct_gotoxy(0, row * 4 + 3);
									cout << "��ͷ��/����ƶ�ȡ����ǰѡ�񣬻س���/��������ϳ�";
									if (((Y + 1) / 4 - 1 == (secondy + 1) / 4 - 1) && ((X + 4) / 8 == (secondx + 4) / 8) && (maction == MOUSE_LEFT_BUTTON_CLICK||keycode1==13) ){
										clear(X, Y, row, col, choice, str,hint);//�ϲ�����
										loop = 0;
										break;
									}
									if ((Y + 1) / 4 - 1 != (secondy + 1) / 4 - 1 || ((X + 4) / 8 != (secondx + 4) / 8)) {
										printaround(X, Y, row, col, str, choice, 0,hint);//Ĩ��
										break;
									}
								}


							}

						}

					}
					else {
						cout << "λ�÷Ƿ�";
						
							printselect(X, Y, row, col, choice, str);//ȡ������
						
					}
					break;
					
			}//���switch����
		}//������
		if (ret == CCT_KEYBOARD_EVENT) {
			if ((choice=='G'||choice=='g')&&!((X + 4) % 8 >= 0 && (X + 4) % 8 <= 5 && X >= 4 && X <= 9 + (col - 1) * 8 && Y >= 3 && Y <= 4 * row + 1 && (Y + 1) % 4 >= 0 && (Y + 1) % 4 <= 2 && str[10 * ((Y + 1) / 4 - 1) + (X + 4) / 8 - 1] != '0')) {
				Y = 4*row-1;
				X = 4;
			}
			if ((choice == 'F' || choice == 'f') && !(X >= 4 && X <= 9 + (col - 1) * 6 && Y >= 3 && Y <= 5 + (row - 1) * 3) && str[10 * (Y / 3 - 1) + (X + 2) / 6 - 1] != '0') {
				Y = 3 * row ;
				X = 4;
			}
			if (keycode1 == 0xe0 && keycode2 == KB_ARROW_UP) {
				if (Y == 3 || Y == 4 || Y == 5) {
					switch (choice) {
						case 'D':
						case 'd':
						case 'F':
						case 'f':
							Y = row * 3;
							break;
						case 'E':
						case 'e':
						case 'G':
						case 'g':
							Y = 4 * row - 1;
							break;
					}
				}
				else {
					switch (choice) {
						case 'D':
						case 'd':
						case 'F':
						case 'f':
							Y = Y - 3;
							break;
						case 'E':
						case 'e':
						case 'G':
						case 'g':
							Y = Y - 4;
							break;
					}
				}
			}
			if (keycode1 == 0xe0 && keycode2 == KB_ARROW_DOWN) {
				if ((Y >= row * 3 && Y <= row * 3 + 2 && (choice == 'D' || choice == 'd'||choice=='F'||choice=='f')) || (Y >= row * 4 - 1 && Y <= row * 4 + 1 && (choice == 'E' || choice == 'e'||choice=='G'||choice=='g')))
					Y = 3;

				else
					switch (choice) {
						case 'D':
						case 'd':
						case 'F':
						case 'f':
							Y = Y + 3;
							break;
						case 'E':
						case 'e':
						case 'G':
						case 'g':
							Y = Y + 4;
							break;
					}
			}
			if (keycode1 == 0xe0 && keycode2 == KB_ARROW_LEFT) {
				if (X >= 4 && X <= 9)
					switch (choice) {
						case 'D':
						case 'd':
						case 'F':
						case 'f':
							X = 6 * col - 2;
							break;
						case 'E':
						case 'e':
						case 'G':
						case 'g':
							X = 4 + (col - 1) * 8;
							break;
					}
				else
					switch (choice) {
						case 'D':
						case 'd':
						case 'F':
						case 'f':
							X = X - 6;
							break;
						case 'E':
						case 'e':
						case 'G':
						case 'g':
							X = X - 8;
							break;
					}
			}
			if (keycode1 == 0xe0 && keycode2 == KB_ARROW_RIGHT) {
				if ((X >= 6 * col - 2 && X <= 6 * col + 3 && (choice == 'D' || choice == 'd'||choice == 'F' || choice == 'f')) || (X >= 4 + (col - 1) * 8 && X <= 9 + (col - 1) * 8 && (choice == 'E' || choice == 'e'||choice=='G'||choice=='g')))
					X = 4;
				else
					switch (choice) {
						case 'D':
						case 'd':
						case 'F':
						case 'f':
							X = X + 6;
							break;
						case 'E':
						case 'e':
						case 'G':
						case 'g':
							X = X + 8;
							break;
					}
			}
			switch (choice) {
				case 'D':
				case 'd':
				case 'F':
				case 'f':
					cct_gotoxy(0, row * 3 + 4);
					cout << "                                                   ";
					cct_gotoxy(0, row * 3 + 4);
					cout << "[��ǰ����] ";
					cout << char('A' + Y / 3 - 1) << "��" << (X + 2) / 6 - 1 << "��            ";
					break;
				case 'E':
				case 'e':
				case 'G':
				case 'g':
					cct_gotoxy(0, row * 4 + 3);
					cout << "                                                   ";
					cct_gotoxy(0, row * 4 + 3);
					cout << "[��ǰ����] ";

					cout << char('A' + (Y + 1) / 4 - 1) << "��" << (X + 4) / 8-1 << "��            ";
					break;

			}
			if (str[((Y + 1) / 4 - 1) * 10 + (X + 4) / 8 - 1] != '0') {

				printselect(X, Y, row, col, choice, str);//���԰�ɫ
				if (keycode1 == 13) {
					switch (choice) {
						case 'D':
						case 'd':
						case 'F':
						case 'f':
							cct_gotoxy(0, row * 3 + 4);
							cout << "                                                   ";
							cct_gotoxy(0, row * 3 + 4);
							cout << "ѡ����" << char('A' + Y / 3 - 1) << "��" << (X + 2) / 6 - 1 << "��" << endl;
							if (choice == 'D' || choice == 'd')
								loop = 0;
							if (choice == 'F' || choice == 'f') {
								bool d;
								d = printaround(X, Y, row, col, str, choice, 1, hint);//Ϳ��
								while (d) {
									int secondx, secondy;
									ret = cct_read_keyboard_and_mouse(secondx, secondy, maction, keycode1, keycode2);
									cct_gotoxy(0, row * 3 + 4);
									cout << "                                     ";
									cct_gotoxy(0, row * 3 + 4);
									cout << "��ͷ��/����ƶ�ȡ����ǰѡ�񣬻س���/��������ϳ�";
									if (keycode1 == 13) {

										clear(X, Y, row, col, choice, str, hint);//�ϲ�����
										loop = 0;
										break;
									}
									else {
										printaround(X, Y, row, col, str, choice, 0, hint);//Ĩ��
										break;
									}
								}


							}


							break;
						case 'E':
						case 'e':
						case 'G':
						case 'g':
							cct_gotoxy(0, row * 4 + 3);
							cout << "                                                   ";
							cct_gotoxy(0, row * 4 + 3);
							cout << "ѡ����" << char('A' + (Y + 1) / 4 - 1) << "��" << (X + 4) / 8 - 1 << "��            ";
							if (choice == 'E' || choice == 'e')
								loop = 0;
							if (choice == 'G' || choice == 'g') {
								bool d;
								d = printaround(X, Y, row, col, str, choice, 1, hint);//Ϳ��
								while (d) {
									int secondx, secondy;
									ret = cct_read_keyboard_and_mouse(secondx, secondy, maction, keycode1, keycode2);
									cct_gotoxy(0, row * 4 + 3);
									cout << "                                     ";
									cct_gotoxy(0, row * 4 + 3);
									cout << "��ͷ��/����ƶ�ȡ����ǰѡ�񣬻س���/��������ϳ�";
									if (keycode1 == 13) {

										clear(X, Y, row, col, choice, str, hint);//�ϲ�����
										loop = 0;
										break;
									}
									else {
										printaround(X, Y, row, col, str, choice, 0, hint);//Ĩ��
										break;
									}
								}


							}


							break;
					}

				}
			}
			else {
				cout <<endl<< "λ�÷Ƿ�";
				
				printselect(X, Y, row, col, choice, str);//ȡ������

			}

		}

	}
		
	cct_disable_mouse();	//�������
	cct_setcursor(CURSOR_VISIBLE_NORMAL);	//�򿪹��



}

