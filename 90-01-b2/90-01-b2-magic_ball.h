/* 2354180 Õı‘œ∫≠ –≈12 */
#pragma once

void menu1(char choice);
void menu2(char choice);
void menu3(char choice);
void input(int *row,int *col,char n[][9]);
void printbase(int row, int col, char n[][9]);
bool search0(int row, int col, char n[][9]);
void end();
int tj_strcasencmp(const char* s1, const char* s2, const int len);
int main();
void Delete(int row, int col, char n[][9]);
void printfill(int row, int col, char n[][9]);
void hint(int row, int col, char n[][9]);
void printgraph(int row, int col, char n[][9],char choice);
void printball(int row, int col, char n[][9],char choice);
bool searchball0(int row, int col, char n[][9], char choice);
void note0(int row, int col, char n[][9], char choice);
bool hintball(int row,int col,char n[][9], char choice, int hint[][9]);
void Deleteball(int row, int col, char n[][9]);
void fillball(int row, int col, char n[][9], char choice);
void mouseread(int row, int col, char n[][9], int hint[][9],char choice);
bool click(int row, int col, char n[][9], int hint[][9],int i,int j);
void changeball(int row, int col, char n[][9], int hint[][9]);