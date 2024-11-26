/* 2354180 计科 王韵涵 */
#include<iostream>
#include<iomanip>
#include<conio.h>
#include"../include/cmd_console_tools.h"
#include"90-01-b1-hanoi.h"
#include<windows.h>
#include"../include/common_menu.h"
using namespace std;
#define MAX_LAYER 10
#define BASE_X 10
#define BASE_Y 15
static int bushu = 0;
static int speed = 0;
static int A[10] = { 0 };
static int B[10] = { 0 };
static int C[10] = { 0 };

static int zhizhen_A = 0;
static int zhizhen_B = 0;
static int zhizhen_C = 0;
/* ----------------------------------------------------------------------------------

     本文件功能：
	1、存放被 hanoi_main.cpp 中根据菜单返回值调用的各菜单项对应的执行函数

     本文件要求：
	1、不允许定义外部全局变量（const及#define不在限制范围内）
	2、允许定义静态全局变量（具体需要的数量不要超过文档显示，全局变量的使用准则是：少用、慎用、能不用尽量不用）
	3、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	4、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */
void Speed() 
{
    if (speed == 1||speed==0)
        Sleep(30);
    if (speed == 2)
        Sleep(80);
    if (speed == 3)
        Sleep(60);
    if (speed == 4)
        Sleep(30);
    if (speed == 5)
        Sleep(10);

}
void move(int choice, int n, char src, char tmp, char dst)
{
    int i,x,y;
    char t;
    if (choice == 7) {
        for (i = n - 1; i >= 1; i--) {
            t = dst;
            dst = tmp;
            tmp = t;
        }
        if (src == 'A') {
            zhizhen_A = n-1;
        }
        if (src == 'B') {
            zhizhen_B = n - 1;
        }
        if (src == 'C') {
            zhizhen_C = n - 1;
        }
        if (dst == 'A') {
            zhizhen_A = 1;
        }
        if (dst == 'B') {
            zhizhen_B = 1;
        }
        if (dst == 'C') {
            zhizhen_C = 1;
        }
        n = 1;
        
    }
    
        /*上移*/
        if (src == 'A') {
            for (y = column_y - zhizhen_A - 2; y >= 1; y--) {
                Speed();
                cct_showch(column_x1 + 11 - n, y + 1, ' ', COLOR_BLACK, COLOR_WHITE, 2*n+1);
                cct_showch(column_x1 + 11, y + 1, ' ', 14, COLOR_WHITE, 1);
                cct_showch(column_x1 + 11 - n, y, ' ', n + 1, 1, 2 * n + 1);
                Speed();
            }
        }
        if (src == 'B') {
            for (y = column_y - zhizhen_B - 2; y >= 1; y--) {
                Speed();
                cct_showch(column_x2 + 11 - n, y + 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);
                cct_showch(column_x2 + 11, y + 1, ' ', 14, COLOR_WHITE, 1);
                cct_showch(column_x2 + 11 - n, y, ' ', n + 1, 1, 2 * n + 1);
                Speed();
            }
        }
        if (src == 'C') {
            for (y = column_y - zhizhen_C - 2; y >= 1; y--) {
                Speed();
                cct_showch(column_x3 + 11 - n, y + 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);
                cct_showch(column_x3 + 11, y + 1, ' ', 14, COLOR_WHITE, 1);
                cct_showch(column_x3 + 11 - n, y, ' ', n + 1, 1, 2 * n + 1);
                Speed();
            }
        }
        /*平移*/
        if (src == 'A' && dst == 'B') {
            for (x = column_x1 + 11 - n + 1; x <= column_x2 + 11 - n; x++) {
                Speed();
                cct_showch(x - 1, 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);

                cct_showch(x, 1, ' ', n+1, 1, 2 * n + 1);
                Speed();
            }
        }
        if (src == 'B' && dst == 'A') {
            for (x = column_x2 + 11 - n - 1; x >= column_x1 + 11 - n; x--) {
                Speed();
                cct_showch(x + 1, 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);

                cct_showch(x, 1, ' ', n+1, 1, 2 * n + 1);
                Speed();
            }
        }
        if (src == 'A' && dst == 'C') {
            for (x = column_x1 + 11 - n + 1; x <= column_x3 + 11 - n; x++) {
                Speed();
                cct_showch(x - 1, 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);

                cct_showch(x, 1, ' ', n+1, 1, 2 * n + 1);
                Speed();
            }
        }
        if (src == 'C' && dst == 'A') {
            for (x = column_x3 + 11 - n - 1; x >= column_x1 + 11 - n; x--) {
                Speed();
                cct_showch(x + 1, 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);

                cct_showch(x, 1, ' ', n+1, 1, 2 * n + 1);
                Speed();
            }
        }
        if (src == 'B' && dst == 'C') {
            for (x = column_x2 + 11 - n + 1; x <= column_x3 + 11 - n; x++) {
                Speed();
                cct_showch(x - 1, 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);

                cct_showch(x, 1, ' ', n+1, 1, 2 * n + 1);
                Speed();
            }
        }
        if (src == 'C' && dst == 'B') {
            for (x = column_x3 + 11 - n - 1; x >= column_x2 + 11 - n; x--) {
                Speed();
                cct_showch(x + 1, 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);

                cct_showch(x, 1, ' ', n+1, 1, 2 * n + 1);
                Speed();
            }
        }
        /*下移*/
        
        if (dst == 'A') {
            for (y = 2; y <= column_y - zhizhen_A; y++) {
                Speed();
                cct_showch(column_x1 + 11 - n, y - 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);
                if (y - 1 > 1)
                    cct_showch(column_x1 + 11, y - 1, ' ', 14, COLOR_WHITE, 1);
                cct_showch(column_x1 + 11 - n, y, ' ', n+1, 1, 2 * n + 1);
                Speed();
            }

        }
        if (dst == 'B') {
            for (y = 2; y <= column_y - zhizhen_B; y++) {
                Speed();
                cct_showch(column_x2 + 11 - n, y - 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);
                if (y - 1 > 1)
                    cct_showch(column_x2 + 11, y - 1, ' ', 14, COLOR_WHITE, 1);
                cct_showch(column_x2 + 11 - n, y, ' ', n + 1, 1, 2 * n + 1);
                Speed();
            }

        }
        if (dst == 'C') {
            for (y = 2; y <= column_y - zhizhen_C; y++) {
                Speed();
                cct_showch(column_x3 + 11 - n, y - 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * n + 1);
                if (y - 1 > 1)
                    cct_showch(column_x3 + 11, y - 1, ' ', 14, COLOR_WHITE, 1);
                cct_showch(column_x3 + 11 - n, y, ' ', n + 1, 1, 2 * n + 1);
                Speed();
            }

        }
    

 
       
}
void plate(int n,char src)
{
    int i;
    int y = column_y-1;
    for (i = n; i >= 1; i--) {
        Sleep(200);
        if (src == 'A') {
            
            cct_showch(column_x1 + 11-i, y, ' ', 1+i, 1, 2*i+1);
            y--;
        }
        if (src == 'B') {

            cct_showch(column_x2 + 11 - i, y, ' ', 1 + i, 1, 2 * i + 1);
            y--;
        }
        if (src == 'C') {

            cct_showch(column_x3 + 11 - i, y, ' ', 1 + i, 1, 2 * i + 1);
            y--;
        }
        
    }
}
void column()
{
   
    int i;
    int x = column_x1, y = column_y;
    for (i = 1; i <= 3; i++) {
        Sleep(500);
        cct_showch(x,y, ' ', 14, 1, 23);
        x += 32;
    }
    for (y = column_y; y >= 2; y--) {
        Sleep(200);
        cct_showch(column_x1+11, y, ' ', 14, 1, 1);
        cct_showch(column_x2+11, y, ' ', 14, 1, 1);
        cct_showch(column_x3+11, y, ' ', 14, 1, 1);

    }
}
void pause()
{
    char ch;
    if (speed == 0) {
        while (1) {
            ch = _getch();
            if (ch == '\r') {
                break;
            }
        }
    }
    if (speed == 1)
        Sleep(2000);
    if (speed == 2)
        Sleep(1000);
    if (speed == 3)
        Sleep(800);
    if (speed == 4)
        Sleep(400);
    if (speed == 5)
        Sleep(10);
    
}


void zongxiang(int choice,int n,char src,char tmp,char dst) 
{
    int x = BASE_X, y = BASE_Y;
    if (choice == 4) {
       x = BASE_X, y = BASE_Y;
    }
    if (choice == 8||choice==9) {
        x = BASE_X, y = BASE_Y+15;
    }
    if (dst == 'A' && src == 'B') {
        cct_gotoxy(x + 10, y - 2 - zhizhen_B);
        cout << " ";
        cct_gotoxy(x, y - 2 - zhizhen_A + 1);
        cout << n;
    }
    if (dst == 'B' && src == 'A') {
        cct_gotoxy(x, y - 2 - zhizhen_A);
        cout << " ";
        cct_gotoxy(x + 10, y - 2 - zhizhen_B + 1);
        cout << n;
    }
    if (dst == 'A' && src == 'C') {
        cct_gotoxy(x + 20, y - 2 - zhizhen_C);
        cout << " ";
        cct_gotoxy(x, y - 2 - zhizhen_A + 1);
        cout << n;
    }
    if (dst == 'C' && src == 'A') {
        cct_gotoxy(x, y - 2 - zhizhen_A);
        cout << " ";
        cct_gotoxy(x + 20, y - 2 - zhizhen_C + 1);
        cout << n;

    }
    if (dst == 'B' && src == 'C') {
        cct_gotoxy(x + 20,y - 2 - zhizhen_C);
        cout << " ";
        cct_gotoxy(x + 10, y - 2 - zhizhen_B + 1);
        cout << n;
    }
    if (dst == 'C' && src == 'B') {
        cct_gotoxy(x+ 10, y - 2 - zhizhen_B);
        cout << " ";
        cct_gotoxy(x + 20, y- 2 - zhizhen_C + 1);
        cout << n;
    }
   
    
    
}


void change(char src,char tmp,char dst)
{
    if (dst == 'A' && src == 'B') {
        A[zhizhen_A++] = B[--zhizhen_B];
        B[zhizhen_B] = 0;
    }
    if (dst == 'B' && src == 'A') {
        B[zhizhen_B++] = A[--zhizhen_A];
        A[zhizhen_A] = 0;
    }
    if (dst == 'A' && src == 'C') {
        A[zhizhen_A++] = C[--zhizhen_C];
        C[zhizhen_C] = 0;
    }
    if (dst == 'C' && src == 'A') {
        C[zhizhen_C++] = A[--zhizhen_A];
        A[zhizhen_A] = 0;

    }
    if (dst == 'B' && src == 'C') {
        B[zhizhen_B++] = C[--zhizhen_C];
        C[zhizhen_C] = 0;
    }
    if (dst == 'C' && src == 'B') {
        C[zhizhen_C++] = B[--zhizhen_B];
        B[zhizhen_B] = 0;
    }
}


void hengxiang()
{

    int i;
    
    cout<<"A:";
    for (i = 0; i < 10; i++) {
        if (A[i] == 0)
           cout<<"  ";

        else {
            cout<<setw(2)<<A[i];
        }
    }
    cout << "  ";
    cout << "B:";
    for (i = 0; i < 10; i++) {
        if (B[i] == 0)
            cout << "  ";
        else {
            cout << setw(2) << B[i];
        }
    }
    cout << "  ";
    cout << "C:";
    for (i = 0; i < 10; i++) {
        if (C[i] == 0)
            cout << "  ";
        else {
            cout << setw(2) << C[i];
        }
    }

    
}


void print(int choice,int n,char src,char tmp,char dst)
{
   
   
    if (choice == 2||choice==3)
        cout << "第" << setw(4) << ++bushu << " 步(";
    if(choice!=4&&choice!=8)
        cout << setw(2) << n << "#: " << src << "-->" << dst << ")  ";
    if (choice == 3) {
        change(src,tmp,dst);
        hengxiang();
    }
    if (choice == 4) {
        cct_gotoxy(0, 20);
        cout << "第" << setw(4) << ++bushu << " 步(";
        cout << setw(2) << n << "#: " << src << "-->" << dst << ")  ";
        change(src, tmp, dst);
        hengxiang();
        zongxiang(4,n, src, tmp, dst);
        pause();

    }
    if (choice == 8) {
        cct_gotoxy(0, 35);
        cct_setcolor();
        cout << "第" << setw(4) << ++bushu << " 步(";
        cout << setw(2) << n << "#: " << src << "-->" << dst << ")  ";
        change(src, tmp, dst);
        hengxiang();
        zongxiang(8,n, src, tmp, dst);
        move(8, n, src, tmp, dst);
        pause();
        cct_gotoxy(0, 35);
        cct_setcolor();
   }
  
}





void hanoi(int choice, int n, char src, char tmp, char dst)
{
    if (n == 1) {
       
        print(choice,n,src,tmp,dst);
        cout << endl;
    }
    else {
        hanoi(choice,n - 1, src, dst, tmp);
        
        print(choice, n, src, tmp, dst);
        cout << endl;
        hanoi(choice,n - 1, tmp, src, dst);
    }
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void input(int choice,int *n, char *start_col, char *end_col) 
{
    while (1) {
        cout << "请输入汉诺塔的层数(1-10)" << endl;
        cin >> *n;
        if (!cin.good()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }
        
        if (*n >= 1 && *n <= MAX_LAYER) {
            break;
        }


    }
    while (1) {
        cout << "请输入起始柱(A-C)" << endl;
        cin >> *start_col;

        if (*start_col >= 'a') {
            *start_col = *start_col - 32;
        }

        if (!cin.good()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }
        cin.ignore(INT_MAX, '\n');
        if (*start_col >= 'A' && *start_col <= 'C') {
            break;
        }
    }
    while (1) {
        cout << "请输入目标柱(A-C)" << endl;
        cin >> *end_col;
        if (*end_col >= 'a') {
            *end_col = *end_col - 32;
        }
        if (*end_col == *start_col) {
            cout << "目标柱(" << *end_col << ")不能与起始柱(" << *start_col << ")相同" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }
        if (!cin.good()) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }
        cin.ignore(INT_MAX, '\n');
        if (*end_col >= 'A' && *end_col <= 'C' && *end_col != *start_col) {
            break;
        }
    }
    if (choice == 4||choice==8) {
        while (1) {
            cout << "请输入移动速度(0-5: 0-按回车单步演示 1-延时最长 5-延时最短)" << endl;
            cin >> speed;
            if (speed >= 0 && speed <= 5) {
                break;
            }
            if (!cin.good()) {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                continue;
            }

        }
    }

}
void solutions1234(int choice)
{
    bushu = 0;
   
    zhizhen_A = 0;
    zhizhen_B = 0;
    zhizhen_C = 0;
    int n,i;
    for (i = 0; i < 10; i++) {
        A[i] = 0;
        B[i] = 0;
        C[i] = 0;
    }
    char start_col, end_col, tmp_col;

    input(choice,&n, &start_col, &end_col);
    tmp_col = 'A' + 'B' + 'C' - start_col - end_col;
    int t = n;
    if ('A' == start_col) {
        for (i = 0; n > 0; i++) {
            A[i] = n;
            n--;
        }
        n = t;
        zhizhen_A = n;

    }
    if ('B' == start_col) {
        for (i = 0; n > 0; i++) {
            B[i] = n;
            n--;
        }
        n = t;
        zhizhen_B = n;
    }
    if ('C' == start_col) {
        for (i = 0; n > 0; i++) {
            C[i] = n;
            n--;
        }
        n = t;
        zhizhen_C = n;
    }
    if (choice == 4) {
        cct_cls();
        cout << "从 " << start_col << " 移动到 " << end_col << "，共" << n << "层，延时设置为 " <<speed;
        cct_gotoxy(0, 20);
        cout << "初始：  ";
        hengxiang();
        cct_gotoxy(BASE_X, BASE_Y);
        cout << "A         B         C";
        cct_gotoxy(BASE_X - 2, BASE_Y - 1);
        cout << "=========================";
        for (i = 0; i < 10; i++) {
            cct_gotoxy(BASE_X, BASE_Y - 2 - i);
            if (A[i] == 0)
                break;
            cout << A[i];

        }
        for (i = 0; i < 10; i++) {
            cct_gotoxy(BASE_X + 10, BASE_Y - 2 - i);
            if (B[i] == 0)
                break;
            cout << B[i];

        }
        for (i = 0; i < 10; i++) {
            cct_gotoxy(BASE_X + 20, BASE_Y - 2 - i);
            if (C[i] == 0)
                break;
            cout << C[i];

        }
       
        pause();
    }
    hanoi(choice, n, start_col, tmp_col, end_col);

}
void solutions5()
{
    cct_cls();
    column();
    cct_gotoxy(0, 30);
    cct_setcolor(); 
    
}
void solutions6()
{
    int n;
    char start_col,end_col;
    input(6, &n, &start_col, &end_col);
    cct_cls();
    cout << "从 " << start_col << " 移动到 " << end_col << "，共" << n << "层";
    column();
    plate(n, start_col);
    cct_gotoxy(0, 30);
    cct_setcolor();

}
void solutions7()
{
    int n;
    char start_col,tmp_col, end_col;
    input(7, &n, &start_col, &end_col);
    tmp_col = 'A' + 'B' + 'C' - start_col - end_col;
    cct_cls();
    cout << "从 " << start_col << " 移动到 " << end_col << "，共" << n << "层";
    column();
    
    plate(n, start_col);
    move(7, n, start_col, tmp_col, end_col);

    
    cct_gotoxy(0, 30);
    cct_setcolor();
}
void solutions8()
{
    bushu = 0;
    zhizhen_A = 0;
    zhizhen_B = 0;
    zhizhen_C = 0;
    int n, i;
    for (i = 0; i < 10; i++) {
        A[i] = 0;
        B[i] = 0;
        C[i] = 0;
    }
    char start_col, end_col, tmp_col;

    input(8, &n, &start_col, &end_col);
    int t = n;
    tmp_col = 'A' + 'B' + 'C' - start_col - end_col;
    if ('A' == start_col) {
        for (i = 0; n > 0; i++) {
            A[i] = n;
            n--;
        }
        n = t;
        zhizhen_A = n;

    }
    if ('B' == start_col) {
        for (i = 0; n > 0; i++) {
            B[i] = n;
            n--;
        }
        n = t;
        zhizhen_B = n;
    }
    if ('C' == start_col) {
        for (i = 0; n > 0; i++) {
            C[i] = n;
            n--;
        }
        n = t;
        zhizhen_C = n;
    }
    cct_cls();
    cout << "从 " << start_col << " 移动到 " << end_col << "，共" << n << "层，延时设置为 " << speed;
    cct_gotoxy(0, 20+15);
    cout << "初始：  ";
    hengxiang();
    cct_gotoxy(BASE_X, BASE_Y+15);
    cout << "A         B         C";
    cct_gotoxy(BASE_X - 2, BASE_Y - 1+15);
    cout << "=========================";
    for (i = 0; i < 10; i++) {
        cct_gotoxy(BASE_X, BASE_Y - 2 - i+15);
        if (A[i] == 0)
            break;
        cout << A[i];

    }
    for (i = 0; i < 10; i++) {
        cct_gotoxy(BASE_X + 10, BASE_Y - 2 - i+15);
        if (B[i] == 0)
            break;
        cout << B[i];

    }
    for (i = 0; i < 10; i++) {
        cct_gotoxy(BASE_X + 20, BASE_Y - 2 - i+15);
        if (C[i] == 0)
            break;
        cout << C[i];

    }
    column();
    plate(n, start_col);

    pause();
    hanoi(8, n, start_col, tmp_col, end_col);
    cct_gotoxy(0, 40);
    cct_setcolor();

}
void solutions9()
{
    cct_setcolor();
    bushu = 0;
    zhizhen_A = 0;
    zhizhen_B = 0;
    zhizhen_C = 0;
    int n, i;
    for (i = 0; i < 10; i++) {
        A[i] = 0;
        B[i] = 0;
        C[i] = 0;
    }
    char start_col, end_col, tmp_col;
    input(9, &n, &start_col, &end_col);
    int t = n;
    tmp_col = 'A' + 'B' + 'C' - start_col - end_col;
    if ('A' == start_col) {
        for (i = 0; n > 0; i++) {
            A[i] = n;
            n--;
        }
        n = t;
        zhizhen_A = n;

    }
    if ('B' == start_col) {
        for (i = 0; n > 0; i++) {
            B[i] = n;
            n--;
        }
        n = t;
        zhizhen_B = n;
    }
    if ('C' == start_col) {
        for (i = 0; n > 0; i++) {
            C[i] = n;
            n--;
        }
        n = t;
        zhizhen_C = n;
    }
    cct_cls();
    cout << "从 " << start_col << " 移动到 " << end_col << "，共" << n << "层";
    cct_gotoxy(0, 20 + 15);
    cout << "初始：  ";
    hengxiang();
    cct_gotoxy(BASE_X, BASE_Y + 15);
    cout << "A         B         C";
    cct_gotoxy(BASE_X - 2, BASE_Y - 1 + 15);
    cout << "=========================";
    for (i = 0; i < 10; i++) {
        cct_gotoxy(BASE_X, BASE_Y - 2 - i + 15);
        if (A[i] == 0)
            break;
        cout << A[i];

    }
    for (i = 0; i < 10; i++) {
        cct_gotoxy(BASE_X + 10, BASE_Y - 2 - i + 15);
        if (B[i] == 0)
            break;
        cout << B[i];

    }
    for (i = 0; i < 10; i++) {
        cct_gotoxy(BASE_X + 20, BASE_Y - 2 - i + 15);
        if (C[i] == 0)
            break;
        cout << C[i];

    }
    column();
    plate(n, start_col);
    cct_setcolor();
    cct_gotoxy(0, 37);
    while (1) {
        cct_gotoxy(60, 37);
        cout << "             ";
        cct_gotoxy(0, 37);
        cout << "请输入移动的柱号(命令形式：AC=A顶端的盘子移动到C，Q=退出) ：";
        char src, dst,tmp;
        cin.ignore(INT_MAX, '\n');
        cin >> src >> dst;
        if (src == 'Q' || src == 'q')
            break;
        if (src >= 'a') {
            src= src - 32;
        }
        if (dst >= 'a') {
            dst = dst - 32;
        }
        if (src == 'A' && zhizhen_A == 0) {
            cout << endl;
            cout << "源柱为空！";
            Sleep(300);
            cct_gotoxy(0, 39);
            cout << "           ";
            cct_gotoxy(60, 37);
            cout << "                   ";
            continue;
        }
        if (src == 'B' && zhizhen_B == 0) {
            cout << endl;
            cout << "源柱为空！";
            Sleep(300);
            cct_gotoxy(0, 39);
            cout << "           ";
            cct_gotoxy(60, 37);
            cout << "                  ";
            continue;
        }
        if (src == 'C' && zhizhen_C == 0) {
            cout << endl;
            cout << "源柱为空！";
            Sleep(300);
            cct_gotoxy(0, 39);
            cout << "           ";
            cct_gotoxy(60, 37);
            cout << "                   ";
            continue;
        }
        if (src == 'A' && dst == 'B'&& A[zhizhen_A - 1] > B[zhizhen_B - 1]&&zhizhen_B!=0) {
            
            cout << "大盘压小盘，非法移动！";
            Sleep(300);
            cct_gotoxy(0, 38);
            cout << "                        ";
            cct_gotoxy(60, 37);
            cout << "                        ";
            continue;
        }
        if (src == 'A' && dst == 'C'&& A[zhizhen_A - 1] > C[zhizhen_C - 1]&&zhizhen_C != 0) {
            
            cout << "大盘压小盘，非法移动！";
            Sleep(300);
            cct_gotoxy(0, 38);
            cout << "                      ";
            cct_gotoxy(60, 37);
            cout << "                        ";
            continue;
        }
        if (src == 'B' && dst == 'A'&& B[zhizhen_B - 1] > A[zhizhen_A - 1] && zhizhen_A != 0) {
           
            cout << "大盘压小盘，非法移动！";
            Sleep(300);
            cct_gotoxy(0, 38);
            cout << "                       ";
            cct_gotoxy(60, 37);
            cout << "                       ";
            continue;
        }
        if (src == 'B' && dst == 'C'&& B[zhizhen_B - 1] > C[zhizhen_C - 1] && zhizhen_C != 0) {
            
            cout << "大盘压小盘，非法移动！";
            Sleep(300);
            cct_gotoxy(0, 38);
            cout << "                      ";
            cct_gotoxy(60, 37);
            cout << "                              ";
            continue;
        }
        if (src == 'C' && dst == 'A' &&C[zhizhen_C - 1] > A[zhizhen_A - 1] && zhizhen_A != 0) {
           
            cout << "大盘压小盘，非法移动！";
            Sleep(300);
            cct_gotoxy(0, 38);
            cout << "                       ";
            cct_gotoxy(60, 37);
            cout << "                      ";
            continue;
        }
        if (src == 'C' && dst == 'B'&& C[zhizhen_C - 1] > B[zhizhen_B - 1] && zhizhen_B != 0) {
           
            cout << "大盘压小盘，非法移动！";
            Sleep(300);
            cct_gotoxy(0, 38);
            cout << "                      ";
            cct_gotoxy(60, 37);
            cout << "                        ";
            continue;
        }
        tmp = 'A' + 'B' + 'C' - src - dst;
        int pan=0;
        if (src == 'A')
            pan = A[zhizhen_A - 1];
        if (src == 'B')
            pan = B[zhizhen_B - 1];
        if (src == 'C')
            pan = C[zhizhen_C - 1];

        cct_gotoxy(0, 35);
        cout << "第" << setw(4) << ++bushu << " 步(";
        cout << setw(2) << pan << "#: " << src << "-->" << dst << ")  ";
        change(src, tmp, dst);
        hengxiang();
        zongxiang(9, pan, src, tmp, dst);
        move(9, pan, src, tmp, dst);
        cct_setcolor();
        if ((end_col== 'A')&&zhizhen_A==n&&A[zhizhen_A-1]==1) {
            cct_gotoxy(0, 38);
            cout << " 游戏结束!!!!!";
            break;
        }
        if ((end_col == 'B') && zhizhen_B == n && B[zhizhen_B - 1] == 1) {
            cout << " 游戏结束!!!!!";
            break;
        }
        if ((end_col == 'C') && zhizhen_C == n && C[zhizhen_C - 1] == 1) {
            cout << " 游戏结束!!!!!";
            break;
        }
       


    }
    cct_gotoxy(0, 41);
    
}