/* 2354180 º∆ø∆ Õı‘œ∫≠ */
#include<iostream>
#include<iomanip>
#include<conio.h>
#include"../include/cmd_console_tools.h"


using namespace std;


char menu_starball(int program)
{
	char choice;
	while (1) {
		choice = _getche();
		if (choice >= '0' && choice <= '9'&&program==1)
			break;
		if (((choice >= 'A' && choice <= 'G')||choice=='Q'||( choice >= 'A'+32 && choice <= 'G'+32)|| choice == 'Q'+32)&&program==2)
			break;

	}
	return choice;
}

