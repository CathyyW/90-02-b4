/* 2354180 ���Ϻ� �ƿ� */
#pragma once
#include"../include/cmd_gmw_tools.h"

void input(int* row, int* col, char *str,int program);
void printbase(int row, int col, char *str,int program);//�߻��߱��
int tj_strcasencmp(const char* s1, const char* s2, const int len);
void end();
void refreshdown(int row, int col, char* str, int program);
int endpcgi(const CONSOLE_GRAPHICS_INFO* const pCGI, const char* gname);