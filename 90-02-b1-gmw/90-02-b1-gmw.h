/* 2354180 ���Ϻ� �ƿ� */
#pragma once




const BLOCK_DISPLAY_INFO bdi_normal[] = {
		{0, -1, -1, "  "},  //0����ʾ���ÿո���伴��
		{1, COLOR_HBLUE, COLOR_BLACK, "��"},
		{2, COLOR_HGREEN, COLOR_BLACK, "��"},
		{3, COLOR_HCYAN, COLOR_BLACK, "��"},
		{4, COLOR_HRED, COLOR_BLACK, "��"},
		{5, COLOR_HPINK, COLOR_BLACK, "��"},
		{-999, -1, -1, NULL} //�жϽ�������Ϊ-999
};
/* ����1-5�������ú�����ʽ��ʾ�ڽ����ϣ���ǰѡ����״̬+ѡ�к������״̬�� */
const BLOCK_DISPLAY_INFO bdi_related[] = {
	{BDI_VALUE_BLANK, -1, -1, "  "},  //�հ�
	{1, COLOR_HBLUE, COLOR_WHITE, "��"},
	{2, COLOR_HGREEN, COLOR_WHITE, "��"},
	{3, COLOR_HCYAN, COLOR_WHITE, "��"},
	{4, COLOR_HRED, COLOR_WHITE, "��"},
	{5, COLOR_HPINK, COLOR_WHITE, "��"},
	{BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
};
/* ����1-5�������ú�����ʽ��ʾ�ڽ����ϣ�����ƶ���״̬�� */
const BLOCK_DISPLAY_INFO bdi_selected[] = {
	{BDI_VALUE_BLANK, -1, -1, "  "},  //�հ�
	{1, COLOR_HBLUE, COLOR_HWHITE, "��"},
	{2, COLOR_HGREEN, COLOR_HWHITE, "��"},
	{3, COLOR_HCYAN, COLOR_HWHITE, "��"},
	{4, COLOR_HRED, COLOR_HWHITE, "��"},
	{5, COLOR_HPINK, COLOR_HWHITE, "��"},
	{BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
};

void to_be_continued(const char* game_name, const char* prompt, const CONSOLE_GRAPHICS_INFO* const bgi);

bool searchall(int row, int col, char n[][10]);

bool searcharound(int row, int col, int mrow, int mcol, char n[][10], int step, char hint[][10]);

bool printaround(int mrow, int mcol, int row, int col, char n[][10], int step, char hint[][10], const CONSOLE_GRAPHICS_INFO* const pCGI);

void clear(int mrow, int mcol, int row, int col, char n[][10], char hint[][10], const CONSOLE_GRAPHICS_INFO* const pCGI);

void mouse_keyboard(int row, int col, char n[][10], char hint[][10], const CONSOLE_GRAPHICS_INFO* const pCGI);

void scoresum(int row, int col, int* score, int* sum, char n[][10], char hint[][10]);

void star_down(int row, int col, char n[][10], const CONSOLE_GRAPHICS_INFO* const pCGI);

bool refreshright(int row, int col, char n[][10], int step, const CONSOLE_GRAPHICS_INFO* const pCGI);