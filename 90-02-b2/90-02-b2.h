/* 2354180 王韵涵 计科 */
#pragma once

/* 打开状态 */
const BLOCK_DISPLAY_INFO bdi_uncover[] = {
	{0, COLOR_WHITE, COLOR_WHITE, "  "},  //0不显示，用空格填充即可
	{1,COLOR_WHITE, COLOR_BLACK, "1 "},
	{2, COLOR_WHITE,COLOR_YELLOW,  "2 "},
	{3, COLOR_WHITE,COLOR_HGREEN, "3 "},
	{4, COLOR_WHITE,COLOR_HCYAN,  "4 "},
	{5, COLOR_WHITE,COLOR_HRED, "5 "},
	{6, COLOR_WHITE,COLOR_HPINK,"6 "},
	{7, COLOR_WHITE,COLOR_HYELLOW, "7 "},
	{8, COLOR_WHITE,COLOR_CYAN,"8 "},
	{9, COLOR_WHITE,COLOR_HBLACK, "* "},
	{BDI_VALUE_END, -1, -1, NULL} //判断结束条件为-999
};
/* 遮盖状态 */
const BLOCK_DISPLAY_INFO bdi_cover[] = {
	{0,  COLOR_YELLOW,-1, "  "},  //0不显示，用空格填充即可
	{1, COLOR_YELLOW,-1, "  "},
	{2, COLOR_YELLOW,-1,  "  "},
	{3, COLOR_YELLOW,-1, "  "},
	{4, COLOR_YELLOW, -1, "  "},
	{5, COLOR_YELLOW,-1, "  "},
	{6,COLOR_YELLOW, -1,"  "},
	{7,COLOR_YELLOW,-1, "  "},
	{8, COLOR_YELLOW, -1,"  "},
	{9, COLOR_YELLOW,-1, "  "},
	{BDI_VALUE_END, -1, -1, NULL} //判断结束条件为-999
};

void init_mines(char n[][30], int row, int col);

void input_mines(char n[][30], int* row, int* col, int* num_mines);

void uncover(int mrow,int mcol,int row,int col,char n[][30], int cover[][30], const CONSOLE_GRAPHICS_INFO* const pCGI);

void mouseread(int row, int col, char n[][30], int cover[][30],int *nums_mine ,const CONSOLE_GRAPHICS_INFO* const pCGI);