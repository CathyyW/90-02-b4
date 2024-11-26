/* 2354180 王韵涵 计科 */
#pragma once

/* ------------------------------------------------------------------------------------------------------

     本文件功能：
	1、为了保证 hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp 能相互访问函数的函数声明
	2、一个以上的cpp中用到的宏定义（#define）或全局只读（const）变量，个数不限
	3、可以参考 cmd_console_tools.h 的写法（认真阅读并体会）
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