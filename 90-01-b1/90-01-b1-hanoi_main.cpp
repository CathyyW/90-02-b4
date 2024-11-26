/* 2354180 �ƿ� ���Ϻ� */
#include<iostream>
#include<iomanip>
#include<conio.h>
#include"../include/cmd_console_tools.h"
#include"90-01-b1-hanoi.h"
#include"../include/common_menu.h"
using namespace std;
/* ----------------------------------------------------------------------------------

     ���ļ����ܣ�
	1����main����
	2����ʼ����Ļ
	3�����ò˵�������hanoi_menu.cpp�У�������ѡ��
	4������ѡ����ò˵������Ӧ��ִ�к�����hanoi_multiple_solutions.cpp�У�

     ���ļ�Ҫ��
	1������������ȫ�ֱ��������ⲿȫ�ֺ;�̬ȫ�֣�const��#define�������Ʒ�Χ�ڣ�
	2����̬�ֲ����������������ƣ���ʹ��׼��Ҳ�ǣ����á����á��ܲ��þ�������
	3���������ϵͳͷ�ļ����Զ���ͷ�ļ��������ռ��

   ----------------------------------------------------------------------------------- */

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main()
{
	char choi;
	cct_cls();
	/* demo������ִ�д˾䣬��cmd��������Ϊ40��x120�У�����������120�У�����9000�У���cmd�����Ҳ���д�ֱ�����ˣ�*/
	cct_setconsoleborder(120, 40, 120, 9000);
	cout << "---------------------------------" << endl;
	cout << "1.������" << endl;
	cout << "2.������(������¼)" << endl;
	cout << "3.�ڲ�������ʾ(����)" << endl;
	cout << "4.�ڲ�������ʾ(����+����)" << endl;
	cout << "5.ͼ�ν� - Ԥ�� - ������Բ��" << endl;
	cout << "6.ͼ�ν� - Ԥ�� - ����ʼ���ϻ�n������" << endl;
	cout << "7.ͼ�ν� - Ԥ�� - ��һ���ƶ�" << endl;
	cout << "8.ͼ�ν� - �Զ��ƶ��汾" << endl;
	cout << "9.ͼ�ν� - ��Ϸ��" << endl;
	cout << "0.�˳�" << endl;
	cout << "---------------------------------" << endl;
	cout << "[��ѡ��:]";
	
	char ch;
	
	while (1) {
		cct_cls();
		/* demo������ִ�д˾䣬��cmd��������Ϊ40��x120�У�����������120�У�����9000�У���cmd�����Ҳ���д�ֱ�����ˣ�*/
		cct_setconsoleborder(120, 40, 120, 9000);
		cout << "---------------------------------" << endl;
		cout << "1.������" << endl;
		cout << "2.������(������¼)" << endl;
		cout << "3.�ڲ�������ʾ(����)" << endl;
		cout << "4.�ڲ�������ʾ(����+����)" << endl;
		cout << "5.ͼ�ν� - Ԥ�� - ������Բ��" << endl;
		cout << "6.ͼ�ν� - Ԥ�� - ����ʼ���ϻ�n������" << endl;
		cout << "7.ͼ�ν� - Ԥ�� - ��һ���ƶ�" << endl;
		cout << "8.ͼ�ν� - �Զ��ƶ��汾" << endl;
		cout << "9.ͼ�ν� - ��Ϸ��" << endl;
		cout << "0.�˳�" << endl;
		cout << "---------------------------------" << endl;
		cout << "[��ѡ��:]";
		choi = menu_starball(1);
		int choice = choi - '0';
		cout << endl;
		cct_cls();
		if (choice == 1||choice==2||choice==3||choice==4) 
			solutions1234(choice);
		if (choice == 5)
			solutions5();
		if (choice == 6)
			solutions6();
		if (choice == 7)
			solutions7();
		if (choice == 8)
			solutions8();
		if (choice == 9)
			solutions9();
		if (choice == 0)
			return 0;
		cout << "���س�������";
		while (1) {
			
			ch = getchar();
			if (ch == '\n') {
				break;
			}
		}
	}
	return 0;
}