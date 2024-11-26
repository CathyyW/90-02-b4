/* 2354180 王韵涵 计科 */
#pragma once



bool search(int row, int col, char cord_r, char cord_c, char* str, int step, char hint[][10]);
void printconse(int row, int col, char n[][10],char hint[][10],int step);
void scoresum(int row, int col, int* score, int* sum,char n[][10], char hint[][10]);
bool searchsame(int row, int col, char n[][10]);
bool refreshright(int row, int col, char n[][10], int step,char choice);
void clear(int X, int Y, int row, int col, char choice, char* str,char hint[][10]);

//以后可提炼为公共函数,数组全用指针法表示
void printgraph(int row, int col, char choice);
void printtext(int row, int col,  char choice);
void printstar(int i, int j, char *str, char choice,int color);
void mouse_keyboard(int row, int col, char choice, char* str,char hint[][10]);
void printselect(int X,int Y,int row, int col, char choice, char* str);
bool printaround(int X, int Y, int row, int col, char* str, char choice, int step,char hint[][10]);
void star_down(int row, int col, char* str, char choice);

