/* 2354180 ���Ϻ� �ƿ� */
#include<iostream>
#include<iomanip>
#include<conio.h>
#include "90-01-b2-magic_ball.h"
#include "../include/cmd_console_tools.h"
using namespace std;
#include"../include/common_menu.h"

int main()
{
	cct_cls();
	cct_setcolor();
	char choice;
	cct_setconsoleborder(120, 30, 120, 150);
	cct_setfontsize("������", 16);

	cout << "------------------------------------------------------------" << endl;
	cout << "1.�ڲ����飬���ɳ�ʼ״̬��Ѱ���Ƿ��г�ʼ��������" << endl;
	cout << "2.�ڲ����飬������ʼ����������0�����䲢��0���" << endl;
	cout << "3.�ڲ����飬������ʼ������������������ʾ" << endl;
	cout << "4.n * n�Ŀ��(�޷ָ���)����ʾ��ʼ״̬" << endl;
	cout << "5.n * n�Ŀ��(�зָ���)����ʾ��ʼ״̬" << endl;
	cout << "6.n * n�Ŀ��(�޷ָ���)����ʾ��ʼ״̬����ʼ��������" << endl;
	cout << "7.n * n�Ŀ��(�зָ���)��������ʼ�����������ʾ������ʾ" << endl;
	cout << "8.cmdͼ�ν���������(�зָ��ߣ�����ƶ�ʱ��ʾ���꣬�Ҽ��˳�)" << endl;
	cout << "9.cmdͼ�ν���������" << endl;
	cout << "0.�˳�" << endl;
	cout << "------------------------------------------------------------" << endl;
	cout << "[��ѡ��:]";
	choice=menu_starball(1);
	
	if (choice == '0')
		return 0;
	else if (choice >= '1' && choice <= '3')
		menu1(choice);
	else if (choice == '9')
		menu3(choice);
	else
		menu2(choice);
	
	return 0;
}
