/* 2354180 王韵涵 计科 */
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
	cct_setfontsize("新宋体", 16);

	cout << "------------------------------------------------------------" << endl;
	cout << "1.内部数组，生成初始状态，寻找是否有初始可消除项" << endl;
	cout << "2.内部数组，消除初始可消除项后非0项下落并用0填充" << endl;
	cout << "3.内部数组，消除初始可消除项后查找消除提示" << endl;
	cout << "4.n * n的框架(无分隔线)，显示初始状态" << endl;
	cout << "5.n * n的框架(有分隔线)，显示初始状态" << endl;
	cout << "6.n * n的框架(无分隔线)，显示初始状态及初始可消除项" << endl;
	cout << "7.n * n的框架(有分隔线)，消除初始可消除项后显示消除提示" << endl;
	cout << "8.cmd图形界面完整版(有分隔线，鼠标移动时显示坐标，右键退出)" << endl;
	cout << "9.cmd图形界面完整版" << endl;
	cout << "0.退出" << endl;
	cout << "------------------------------------------------------------" << endl;
	cout << "[请选择:]";
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
