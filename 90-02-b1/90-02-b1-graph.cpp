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
void printtext(int row, int col, char choice)
{
	cct_setfontsize("������", 16);
	if (choice == 'D' || choice == 'd'||choice=='F'||choice=='f') {//�޷ָ���
		cct_setconsoleborder(55 + (col - 8) * 6, 32 + (row - 8) * 3, 55 + (col - 8) * 6, 32 + (row - 8) * 3);
		cout << "��Ļ��" <<32 + (row-8)*3 << "��" <<55+(col-8)*6 << "��" << endl;

	}
	if (choice == 'E' || choice == 'e'|| choice == 'G' || choice == 'g') {//�зָ���
		cct_setconsoleborder(69 + (col - 8) * 8, 39 + (row - 8) * 4, 55 + (col - 8) * 6, 69 + (col - 8) * 8);
		cout << "��Ļ��" << 39 + (row - 8) * 4 << "��" << 69 + (col - 8) * 8 << "��" << endl;

	}
	if(choice == 'D' || choice == 'd'||choice == 'F' || choice == 'f')
		cct_gotoxy(0, row * 3 + 4);
	if (choice == 'E' || choice == 'e'||choice == 'G' || choice == 'g')
		cct_gotoxy(0, row * 4 + 3);
	
	cout << "��ͷ��/����ƶ����س���/�������ѡ�񲢽���" << endl;

}

void printgraph(int row, int col, char choice)
{
	int i, j;
	int x, y;
	//��һ������
	cct_gotoxy(0, 1);
	cout << "    ";
	for (j = 0; j < col; j++) {
		cout << "  " << j << "   ";
		if (choice == 'E' || choice == 'e'|| choice == 'G' || choice == 'g')
			cout << "  ";
	}
	//��һ�б߿�
	cct_gotoxy(0, 2);
	cout << "  ";
	cct_setcolor(15, 0);//�������ף�ǰ����
	cct_getxy(x, y);
	cct_showstr(x, y, "��", COLOR_HWHITE, COLOR_BLACK);
	
	for (j = 0; j < col; j++) {
		Sleep(30);
		cct_getxy(x, y);
		cct_showstr(x, y, "������", COLOR_HWHITE, COLOR_BLACK);
		
		if ((choice == 'E' || choice == 'e'|| choice == 'G' || choice == 'g')&&j!=col-1) {
			cct_getxy(x, y);
			cct_showstr(x, y, "��", COLOR_HWHITE, COLOR_BLACK);
			
		}
	}
	cct_getxy(x, y);
	cct_showstr(x, y, "��", COLOR_HWHITE, COLOR_BLACK);
	
	cct_setcolor(0, 7);
	cout << endl;
	//�м伸��
	if (choice == 'D' || choice == 'd'||choice == 'F' || choice == 'f') {
		for (i = 1; i <= row * 3; i++) {
			cct_setcolor(0, 7);
			if ((i - 2) % 3 == 0)
				cout << char('A' + (i - 2) / 3) << " ";
			else
				cout << "  ";
			cct_setcolor(15, 0);//�������ף�ǰ����
			cct_getxy(x, y);
			cct_showstr(x, y, "��", COLOR_HWHITE, COLOR_BLACK);
			
			
			for (j = 1; j <= col; j++)
				cout << "      ";

			
			cct_getxy(x, y);
			cct_showstr(x, y, "��", COLOR_HWHITE, COLOR_BLACK);
			cct_setcolor(0, 7);
			cout << endl; //����cout<<" "<<endl;��������С�봰�ڴ�С��ͬ�����Կո��������Զ���ת����һ�У�����Ҫendl
		}
	}
	if (choice == 'E' || choice == 'e'||choice == 'G' || choice == 'g') {
		for (i = 1; i <= row * 4-1; i++) {
			cct_setcolor(0, 7);
			if ((i - 2) % 4 == 0)
				cout << char('A' + (i - 2) /4) << " ";
			else
				cout << "  ";
			cct_setcolor(15, 0);//�������ף�ǰ����
			if (i % 4 == 0) {
				for (j = 1; j <= col; j++) {
					if (j == 1) {
						cct_getxy(x, y);
						cct_showstr(x, y, "�ǩ�������", COLOR_HWHITE, COLOR_BLACK);
						
					}
					else if (j == col) {
						cct_getxy(x, y);
						cct_showstr(x, y, "��������", COLOR_HWHITE, COLOR_BLACK);
						
					}
					else {
						cct_getxy(x, y);
						cct_showstr(x, y, "��������", COLOR_HWHITE, COLOR_BLACK);
						
					}
				}
				
			}

			else {
				cct_getxy(x, y);
				cct_showstr(x, y, "��", COLOR_HWHITE, COLOR_BLACK);
				
				for (j = 1; j <= col; j++) {
					cct_getxy(x, y);
					cct_showstr(x, y, "      ��", COLOR_HWHITE, COLOR_BLACK);
				}
					
			}

			
			cct_setcolor(0, 7);
			cout << endl; //����cout<<" "<<endl;��������С�봰�ڴ�С��ͬ�����Կո��������Զ���ת����һ�У�����Ҫendl
		}
	}
		//���һ��
		cout << "  ";
		cct_setcolor(15, 0);//�������ף�ǰ����
		cct_getxy(x, y);
		cct_showstr(x, y, "��", COLOR_HWHITE, COLOR_BLACK);
		
		for (j = 0; j < col; j++) {
			Sleep(30);
			cct_getxy(x, y);
			cct_showstr(x, y, "������", COLOR_HWHITE, COLOR_BLACK);
			
			if ((choice == 'E' || choice == 'e'||choice == 'G' || choice == 'g') && j != col - 1) {
				cct_getxy(x, y);
				cct_showstr(x, y, "��", COLOR_HWHITE, COLOR_BLACK);
				
			}
		}
		cct_getxy(x, y);
		cct_showstr(x, y, "��", COLOR_HWHITE, COLOR_BLACK);
		
		cct_setcolor(0, 7);
	
	

}
void printstar(int i, int j, char* str, char choice,int color)
{
	int k = 6, t = 3;
	if (choice == 'E' || choice == 'e'||choice == 'G' || choice == 'g')
		k = 8, t = 4;
	
	Sleep(30);
	cct_showstr(4+k*(j), 3 + i*t, "�X", str[i * 10 + j], color);
	cct_showstr(6 +k * (j), 3 + i*t, "�T", str[i * 10 + j],color);
	cct_showstr(8 + k * (j), 3 + i*t, "�[", str[i * 10 + j],color);

	cct_showstr(4 + k * (j), 4 + i*t, "�U", str[i * 10 + j], color);
	cct_showstr(6+ k * (j), 4 + i*t, "��", str[i * 10 + j], color);
	cct_showstr(8 + k * (j), 4 + i*t, "�U", str[i * 10 + j], color);

	cct_showstr(4 + k * (j), 5 + i * t, "�^", str[i * 10 + j],color);
	cct_showstr(6 + k * (j), 5 + i * t, "�T", str[i * 10 + j], color);
	cct_showstr(8 +k * (j), 5 + i * t, "�a", str[i * 10 + j],color);
		
	cct_setcolor();
	
}
void printselect(int X, int Y, int row, int col, char choice, char* str)
{
	static bool hint[1000] = { 0 };
	static bool* p = &hint[999];
	int hang=0, lie=0,i;
	bool yuejie = false;
	int row_power=0, col_power=0;

	if (choice == 'D' || choice == 'd'||choice == 'F' || choice == 'f') {
		hang = Y / 3 - 1;
		lie = (X + 2) / 6 - 1;
		row_power = 3, col_power = 6;
		if (hang >= row || lie >= col || hang < 0 || lie < 0)
			yuejie = true;

	}
	if (choice == 'E' || choice == 'e'||choice == 'G' || choice == 'g') {
		hang = (Y + 1) / 4 - 1;
		lie = (X + 4) / 8-1;
		row_power = 4, col_power = 8;
		if (hang >= row || lie >= col || hang < 0 || lie < 0|| (X + 4) %8==6|| (X + 4) % 8 == 7|| (Y + 1)% 4==3|| str[hang * 10 + lie]=='0')
			yuejie = true;
	}
	
	if ((p != &hint[hang * 10 + lie]&&p!=&hint[999] && str[p - hint] != '0')||(yuejie && p != &hint[999]&& str[p - hint]!='0')) {//���Ǳ��ˣ�����ǰ�ı�Ϊ��ɫ
		cct_showstr(4 + col_power * ((p - hint) % 10), 3 + ((p - hint) / 10) * row_power, "�X", str[p - hint], 0);
		cct_showstr(6 + col_power * ((p - hint) % 10), 3 + ((p - hint) / 10) * row_power, "�T", str[p - hint], 0);
		cct_showstr(8 + col_power * ((p - hint) % 10), 3 + ((p - hint) / 10) * row_power, "�[", str[p - hint], 0);

		cct_showstr(4 + col_power * ((p - hint) % 10), 4 + ((p - hint) / 10) * row_power, "�U", str[p - hint], 0);
		cct_showstr(6 + col_power * ((p - hint) % 10), 4 + ((p - hint) / 10) * row_power, "��", str[p - hint], 0);
		cct_showstr(8 + col_power * ((p - hint) % 10), 4 + ((p - hint) / 10) * row_power, "�U", str[p - hint], 0);

		cct_showstr(4 + col_power * ((p - hint) % 10), 5 + ((p - hint) / 10) * row_power, "�^", str[p - hint], 0);
		cct_showstr(6 + col_power * ((p - hint) % 10), 5 + ((p - hint) / 10) * row_power, "�T", str[p - hint], 0);
		cct_showstr(8 + col_power * ((p - hint) % 10), 5 + ((p - hint) / 10) * row_power, "�a", str[p - hint], 0);
		cct_setcolor();
		if (yuejie == true) {
			*p = false;
			p = &hint[999];
		}
	}
	if (hint[hang*10+lie]==false&&!yuejie){//����ǰ�Ǻڵ�Ϳ��
		
		cct_showstr(4 + col_power * (lie), 3 + hang * row_power, "�X", str[hang * 10 + lie], 15);
		cct_showstr(6 + col_power * (lie), 3 + hang * row_power, "�T", str[hang * 10 + lie], 15);
		cct_showstr(8 + col_power * (lie), 3 + hang * row_power, "�[", str[hang * 10 + lie], 15);

		cct_showstr(4 + col_power * (lie), 4 + hang * row_power, "�U", str[hang * 10 + lie], 15);
		cct_showstr(6 + col_power * (lie), 4 + hang * row_power, "��", str[hang * 10 + lie], 15);
		cct_showstr(8 + col_power * (lie), 4 + hang * row_power, "�U", str[hang * 10 + lie], 15);

		cct_showstr(4 + col_power * (lie), 5 + hang * row_power, "�^", str[hang * 10 + lie], 15);
		cct_showstr(6 + col_power * (lie), 5 + hang * row_power, "�T", str[hang * 10 + lie], 15);
		cct_showstr(8 + col_power * (lie), 5 + hang * row_power, "�a", str[hang * 10 + lie], 15);
		cct_setcolor();
		for (i = 0; i < 1000; i++)
			hint[i] = false;
		hint[hang * 10 + lie] = true;
		p = &hint[hang * 10 + lie];

	}
	
}
void clear(int X, int Y, int row, int col, char choice, char* str,char hint[][10])
{

	char cord_r = 'A' + Y / 3 - 1;
	char cord_c = '0' + (X + 2) / 6 - 1;
	int i, j;

	int k = 6, t = 3;
	if (choice == 'G' || choice == 'g') {
		k = 8, t = 4;
		cord_r = 'A' + (Y + 1) / 4 - 1;
		cord_c = '0' + (X + 4) / 8 - 1;
	}
	search(row, col, cord_r, cord_c, str, 2, hint);
	
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (hint[i][j] == '*') {
				cct_showstr(4 + k * (j), 3 + i * t, "  ", 15, 15);
				cct_showstr(6 + k * (j), 3 + i * t, "  ", 15, 15);
				cct_showstr(8 + k * (j), 3 + i * t, "  ", 15, 15);

				cct_showstr(4 + k * (j), 4 + i * t, "  ", 15, 15);
				cct_showstr(6 + k * (j), 4 + i * t, "  ", 15, 15);
				cct_showstr(8 + k * (j), 4 + i * t, "  ", 15, 15);

				cct_showstr(4 + k * (j), 5 + i * t, "  ", 15, 15);
				cct_showstr(6 + k * (j), 5 + i * t, "  ", 15, 15);
				cct_showstr(8 + k * (j), 5 + i * t, "  ", 15, 15);
				str[i * 10 + j] = '0';
				

				cct_setcolor();
			}
		}
	}




}
void star_down(int row, int col, char* str, char choice)
{
	int i, j, t;
	int k = 6, q = 3,h=2,g=2;
	if (choice == 'G' || choice == 'g')
		k = 8, q = 4, h = 1,g=4;
	for (j = 0; j < col; j++) {
		for (i = 0; i < row - 1; i++) {
			for (t = 0; t < row - (i + 1); t++) {
				if (str[10*(t + 1)+j] == '0' && t + 1 < row && str[10 * t + j] != '0') {

					str[10 * (t + 1) + j] = str[10 * t + j];
					str[10 * t + j] = '0';
					//�ƶ�
					cct_showstr(k * (j + 1) - g, q * (t + 1)+h-2, "      ", 15, 15);
					cct_showstr(k * (j + 1) - g,q * (t + 1) + h-1, "�X�T�[", str[10 * (t + 1) + j], 0);//��һ��
					cct_showstr(k * (j + 1) - g, q * (t + 1) + h, "�U��U", str[10 * (t + 1) + j], 0);//�ڶ���
					cct_showstr(k * (j + 1) - g,q * (t + 1) + h+1, "�^�T�a", str[10 * (t + 1) + j], 0);//������
					Sleep(10);

					cct_showstr(k * (j + 1) - g, q * (t + 1)+h-1, "      ", 15, 15);
					cct_showstr(k * (j + 1) - g, q * (t + 1) + h, "�X�T�[", str[10 * (t + 1) + j], 0);//��һ��
					cct_showstr(k * (j + 1) - g, q * (t + 1) + h+1, "�U��U", str[10 * (t + 1) + j], 0);//�ڶ���
					cct_showstr(k * (j + 1) - g, q * (t + 1) + h+2, "�^�T�a", str[10 * (t + 1) + j], 0);//������
					Sleep(10);

					cct_showstr(k * (j + 1) - g,q * (t + 1) + h, "      ", 15, 15);
					cct_showstr(k * (j + 1) - g, q * (t + 1) + h+1, "�X�T�[", str[10 * (t + 1) + j], 0);//��һ��
					cct_showstr(k * (j + 1) - g, q * (t + 1) + h+2, "�U��U", str[10 * (t + 1) + j], 0);//�ڶ���
					cct_showstr(k * (j + 1) - g, q * (t + 1) + h+3, "�^�T�a", str[10 * (t + 1) + j], 0);//������
					Sleep(10);
					
					if (choice == 'G' || choice == 'g') {
						cct_showstr(k * (j + 1) - g, q * (t + 1) + h+1, "������", 15, 0);
						cct_showstr(k * (j + 1) - g, q * (t + 1) + h+2, "�X�T�[", str[10 * (t + 1) + j], 0);//��һ��
						cct_showstr(k * (j + 1) - g, q * (t + 1) + h+3, "�U��U", str[10 * (t + 1) + j], 0);//�ڶ���
						cct_showstr(k * (j + 1) - g, q * (t + 1) + h+4, "�^�T�a", str[10 * (t + 1) + j], 0);//������
						Sleep(10);
					}

					cct_setcolor(0, 7);

				}
			}

		}
	}

}
