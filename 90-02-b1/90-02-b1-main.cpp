/* 2354180 �ƿ� ���Ϻ� */
#include <iostream>
#include<iomanip>
#include<conio.h>
#include "../include/cmd_console_tools.h"
#include"../include/common_menu.h"
#include"../include/common_tools.h"
#include"90-02-b1.h"
using namespace std;

int main()
{
	cct_setcolor();
	cct_cls();
	cct_setconsoleborder(120, 31, 120, 9001);
	cout << "--------------------------------------------" << endl;
	cout << "A.�������ҳ����������ʶ" << endl;
	cout << "B.���������һ���������ֲ�����ʾ��" << endl;
	cout << "C.���������һ�أ��ֲ�����ʾ��" << endl;
	cout << "D.αͼ�ν����������ѡ��һ��ɫ�飨�޷ָ��ߣ�" << endl;
	cout << "E.αͼ�ν����������ѡ��һ��ɫ�飨�зָ��ߣ�" << endl;
	cout << "F.αͼ�ν������һ���������ֲ��裩" << endl;
	cout << "G.αͼ�ν���������" << endl;
	cout << "Q.�˳�" << endl;
	cout << "--------------------------------------------" << endl;
	cout << "[��ѡ��]:";
	char choice;
	choice = menu_starball(2);

	if (choice == 'Q')
		return 0;
	//aʵ���߼�
	if (choice == 'A' || choice == 'A' + 32|| choice == 'B' || choice == 'B' + 32|| choice == 'C' || choice == 'C' + 32) {
		cct_cls();
		int row, col;
		bool b=false;
		bool c = false;
		bool d = false;
		char n[10][10];
		char hint[10][10] = { 0 };
		int sum = 0, score = 0;
		//��ʼ�����飨����������
		input(&row, &col, n[0], 2);
		
		//��ѭ�� �Ƿ�ѡ�������
		while (1) {
			cout << "��ǰ���飺" << endl;
			printbase(row, col, n[0], 2);
			//��λ��������
			char cord_r, cord_c;
			char answer;
			
			while (1) {
				while (1) {
					cout << "������ĸ + ������ʽ[����c2]����������꣺";
					cord_r = _getche();
					cord_c = _getche();
					//��ȷ��Χ�Լ���λ�ò���0
					if (((cord_r >= 'A' && cord_r <= row - 1 + 'A') || (cord_r >= 'A' + 32 && cord_r <= row - 1 + 'A' + 32)) && (cord_c >= '0' && cord_c <= '0' + col - 1)&&(n[cord_r-'A'][cord_c-'0']!='0'&& n[cord_r - 'a'][cord_c - '0'] != '0')) {
						
						break;
					}
					cout << endl;
				}
				if (cord_r >= 'A' + 32 && cord_r <= row - 1 + 'A' + 32)
					cord_r = cord_r - 32;
				//�����Ƿ�������ֵ
				cout << "����Ϊ" << cord_r << "��" << cord_c << "��" << endl;
				b = search(row, col, cord_r, cord_c, n[0], 1, hint);
				if (b) {
					break;
				}
				else {
					cout << "����ľ�������λ�ô���������ֵͬ������������" << endl;
				}
			}
			//����������ʶ����
			//������hint���³�ʼ��
			for (int i = 0; i < 10; ++i) {
				for (int j = 0; j < 10; ++j) {
					hint[i][j] = '\0';
				}
			}

			b = search(row, col, cord_r, cord_c, n[0], 2, hint);
			
			printconse(row, col, n, hint, 1);//��ӡ0*����
			printconse(row, col, n, hint, 2);//��ӡ����ֵ������
			
			if (choice == 'A' || choice == 'A' + 32) {
				break;
			}
			if (choice == 'B' || choice == 'B' + 32 || choice == 'C' || choice == 'C' + 32) {
				cout << "��ȷ���Ƿ��" << cord_r << cord_c << "����Χ����ֵͬ����(Y / N / Q)��";
				while (1) {
					answer = _getche();
					
					if (answer == 'Y' || answer == 'y') {
						//��������ȫ����ֵΪ0
						for (int i = 0; i < 10; ++i) {
							for (int j = 0; j < 10; ++j) {
								if (hint[i][j] == '*')
									n[i][j] = '0';
							}
						}
						cout << endl;
						printconse(row, col, n, hint, 3);//��ӡ�����������
						scoresum(row, col, &score, &sum, n, hint);//����÷�
						cout << "���ε÷֣�" <<score << " �ܵ÷֣�" << sum<< endl;
				
						break;
					}
					if (answer == 'N' || answer == 'n' ) 

						break;
					
					if (answer == 'Q' || answer == 'q') 
						break;
					
				}
				
				if (answer == 'N' || answer == 'n') {
					cout << endl;
					continue;
				}
				
				if (answer == 'Q' || answer == 'q')
					break;

			}
			if (choice == 'A' || choice == 'A' + 32 || choice == 'B' || choice == 'B' + 32) {
				break;
			}
			if (choice == 'C' || choice == 'C' + 32) {
				//��������
				cout << "���س������������������...";
				while (getchar() != '\n') {
				}
				cout << endl;
				cout << "���������飺" << endl;
				refreshdown(row, col, n[0], 2);
				
				printbase(row, col, n[0], 2);
				
				//����Ƿ���Ҫ����
				d = refreshright(row, col, n, 1,choice);
				if (d) {
					cout << "���ƺ������:" << endl;
					refreshright(row, col, n, 2,choice);
					printbase(row, col, n[0], 2);
				}

				//�����Ƿ�����һ��
				cout << "�����������������س���������һ�ε�����...";
				while (getchar() != '\n') {
				}
				cout << endl;
				c=searchsame(row, col, n);
				if (c)
					continue;
				else {
					
					int left;
					left = row * col - sum / 5;
					
					cct_setcolor(13, 1);
					cout << "ʣ��" << left << "��������������ؽ���������" << endl;
					cct_setcolor();
					break;
				}

			}


		}
		
		//��һ�δ�ѭ��������
		end();
		main();
		
		
	}
	if (choice == 'D'||choice=='d'||choice == 'E' || choice == 'e'||choice=='F'||choice=='f'||choice=='G'||choice=='g') {
		cct_cls();
		int row, col;
		int i, j;
		bool c = false;
		bool d = false;
		char n[10][10];
		char hint[10][10] = { 0 };
		int sum = 0, score = 0;
		//��ʼ�����飨����������
		input(&row, &col, n[0], 2);
		cct_cls();

		printtext(row, col, choice);
		printgraph(row, col, choice);
		for (i = 0; i < row; i++) {
			for (j = 0; j < col; j++) {
				printstar(i, j, n[0], choice, 0);
			}
		}
		cout << endl << endl << endl;
		//�����̲���
		
		if (choice == 'G' || choice == 'g') {
			c = searchsame(row, col, n); //����������ֵͬ���ų�0��
			while (c) {
				
				mouse_keyboard(row, col, choice, n[0],hint);
				

				cct_gotoxy(0, row * 4 + 3);
				cout << "                                                         ";
				cct_gotoxy(0, row * 4 + 3);
				scoresum(row, col, &score, &sum, n, hint);//����÷�
				cct_gotoxy(0, 0);
				cout << "���ε÷֣�" << score << " �ܵ÷֣�" << sum << endl;
				for (i = 0; i < 10; ++i) {
					for (j = 0; j < 10; ++j) {
						if (hint[i][j] == '*')
							hint[i][j] = '0';
					}
				}

				star_down(row, col, n[0], choice);
				d = refreshright(row, col, n, 1, choice);
				if(d)
					refreshright(row, col, n, 3, choice);
				c = searchsame(row, col, n);

				cct_gotoxy(0, row * 4 + 3);
				cout << "                                                         ";
				cct_gotoxy(0, row * 4 + 3);

				cout << "���»س���������һ�غϣ���c���˳���Ϸ";//
				
					char button = _getche();
					if (button == 'c')
						break;
					if (button == '\n' || button == '\r')
						continue;
				
				
			}
			if (c == false) {
				cct_gotoxy(0, row * 4 + 4);
				cout << "                                                    ";
				cct_gotoxy(0, row * 4 + 4);
				cct_setcolor(13, 1);
				cout << "ʣ��" << row * col - sum / 5 << "��������������ؽ���������           " << endl;
				cct_setcolor();
			}
			cct_gotoxy(0, row * 4 + 3);

			end();
			main();
		}

		if (choice == 'D' || choice == 'd' || choice == 'E' || choice == 'e') {
			mouse_keyboard(row, col, choice, n[0],hint);
			end();
			main();
		}
		if (choice == 'F' || choice == 'f') {
			mouse_keyboard(row, col, choice, n[0],hint);
			cct_gotoxy(0, row * 3 + 4);
			cout << "                                                         ";
			cct_gotoxy(0, row * 3 + 4);
			cout << "���»س������ɽ��������ƽ�Ʋ���";
			while (getchar() != '\n') {
			}

			star_down(row, col, n[0], choice);
			refreshright(row, col, n, 3,choice);

			
			cct_gotoxy(0, row * 3 + 4);
			cout << "                                                         ";
			cct_gotoxy(0, row * 3 + 4);
			cout << "���»س������ɽ�����һ�غϵĲ���";
			while (getchar() != '\n') {
			}
			cct_gotoxy(0, row * 3 + 4);
			end();
			main();
		}
		
	}
}
