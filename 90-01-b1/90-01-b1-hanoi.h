/* 2354180 ���Ϻ� �ƿ� */
#pragma once

/* ------------------------------------------------------------------------------------------------------

     ���ļ����ܣ�
	1��Ϊ�˱�֤ hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp ���໥���ʺ����ĺ�������
	2��һ�����ϵ�cpp���õ��ĺ궨�壨#define����ȫ��ֻ����const����������������
	3�����Բο� cmd_console_tools.h ��д���������Ķ�����ᣩ
   ------------------------------------------------------------------------------------------------------ */
#define column_x1 1
#define column_x2 33
#define column_x3 65
#define column_y 16
int menu();
void input(int choice,int *n, char *start_col, char *end_col);

void hanoi(int choice, int n, char src, char tmp, char dst);

void solutions1234(int choice);
void solutions5();
void solutions6();
void solutions7();
void solutions8();
void print(int choice,int n,char src,char tmp,char dst);
void change(char src,char tmp,char dst);
void hengxiang();
void zongxiang(int choice,int n, char src, char tmp, char dst);
void pause();
void column();
void plate(int n,char src);
void move(int choice,int n, char src, char tmp, char dst);
void solutions9();