/* 2354180 计科 王韵涵 */
#include<iostream>
#include<iomanip>
#include<conio.h>
#include"../include/cmd_console_tools.h"
#include"90-01-b1-hanoi.h"
#include"../include/common_menu.h"
using namespace std;
/* ----------------------------------------------------------------------------------

     本文件功能：
	1、放main函数
	2、初始化屏幕
	3、调用菜单函数（hanoi_menu.cpp中）并返回选项
	4、根据选项调用菜单各项对应的执行函数（hanoi_multiple_solutions.cpp中）

     本文件要求：
	1、不允许定义全局变量（含外部全局和静态全局，const及#define不在限制范围内）
	2、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	3、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main()
{
	char choi;
	cct_cls();
	/* demo中首先执行此句，将cmd窗口设置为40行x120列（缓冲区宽度120列，行数9000行，即cmd窗口右侧带有垂直滚动杆）*/
	cct_setconsoleborder(120, 40, 120, 9000);
	cout << "---------------------------------" << endl;
	cout << "1.基本解" << endl;
	cout << "2.基本解(步数记录)" << endl;
	cout << "3.内部数组显示(横向)" << endl;
	cout << "4.内部数组显示(纵向+横向)" << endl;
	cout << "5.图形解 - 预备 - 画三个圆柱" << endl;
	cout << "6.图形解 - 预备 - 在起始柱上画n个盘子" << endl;
	cout << "7.图形解 - 预备 - 第一次移动" << endl;
	cout << "8.图形解 - 自动移动版本" << endl;
	cout << "9.图形解 - 游戏版" << endl;
	cout << "0.退出" << endl;
	cout << "---------------------------------" << endl;
	cout << "[请选择:]";
	
	char ch;
	
	while (1) {
		cct_cls();
		/* demo中首先执行此句，将cmd窗口设置为40行x120列（缓冲区宽度120列，行数9000行，即cmd窗口右侧带有垂直滚动杆）*/
		cct_setconsoleborder(120, 40, 120, 9000);
		cout << "---------------------------------" << endl;
		cout << "1.基本解" << endl;
		cout << "2.基本解(步数记录)" << endl;
		cout << "3.内部数组显示(横向)" << endl;
		cout << "4.内部数组显示(纵向+横向)" << endl;
		cout << "5.图形解 - 预备 - 画三个圆柱" << endl;
		cout << "6.图形解 - 预备 - 在起始柱上画n个盘子" << endl;
		cout << "7.图形解 - 预备 - 第一次移动" << endl;
		cout << "8.图形解 - 自动移动版本" << endl;
		cout << "9.图形解 - 游戏版" << endl;
		cout << "0.退出" << endl;
		cout << "---------------------------------" << endl;
		cout << "[请选择:]";
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
		cout << "按回车键继续";
		while (1) {
			
			ch = getchar();
			if (ch == '\n') {
				break;
			}
		}
	}
	return 0;
}
