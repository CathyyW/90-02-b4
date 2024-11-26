/* 2354180 ���Ϻ� �ƿ� */
#pragma once


/* ����1-9�������ú�����ʽ��ʾ�ڽ����ϣ�����״̬�� */
const BLOCK_DISPLAY_INFO bdi_normal[] = {
	{BDI_VALUE_BLANK, -1, -1, "  "},  //0����ʾ���ÿո���伴��
	{1, COLOR_HBLACK, -1, "��"},
	{2, COLOR_YELLOW, -1, "��"},
	{3, COLOR_HGREEN, -1, "��"},
	{4, COLOR_HCYAN, -1, "��"},
	{5, COLOR_HRED, -1, "��"},
	{6, COLOR_HPINK, -1, "��"},
	{7, COLOR_HYELLOW, -1, "��"},
	{8, COLOR_CYAN, -1, "��"},
	{9, COLOR_WHITE, -1, "��"},
	{BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
};
/* ����1-9�������ú�����ʽ��ʾ�ڽ����ϣ�������ѡ��״̬�� */
const BLOCK_DISPLAY_INFO bdi_click[] = {
	{BDI_VALUE_BLANK, -1, -1, "  "},  //�հ�
	{1, COLOR_HBLACK, COLOR_HWHITE, "��"},
	{2, COLOR_YELLOW, COLOR_HWHITE, "��"},
	{3, COLOR_HGREEN, COLOR_HWHITE, "��"},
	{4, COLOR_HCYAN,COLOR_HWHITE, "��"},
	{5, COLOR_HRED, COLOR_HWHITE, "��"},
	{6, COLOR_HPINK, COLOR_HWHITE, "��"},
	{7, COLOR_HYELLOW, COLOR_HWHITE, "��"},
	{8, COLOR_CYAN, COLOR_HWHITE, "��"},
	{9, COLOR_WHITE, COLOR_HWHITE, "��"},
	{BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
};



/* ����1-9�������ú�����ʽ��ʾ�ڽ����ϣ�ѡ��״̬�� */
const BLOCK_DISPLAY_INFO bdi_selected[] = {
	{BDI_VALUE_BLANK, -1, -1, "  "},  //�հ�
	{1, COLOR_HBLACK, -1, "��"},
	{2, COLOR_YELLOW, -1, "��"},
	{3, COLOR_HGREEN, -1, "��"},
	{4, COLOR_HCYAN, -1, "��"},
	{5, COLOR_HRED, -1, "��"},
	{6, COLOR_HPINK, -1, "��"},
	{7, COLOR_HYELLOW, -1, "��"},
	{8, COLOR_CYAN, -1, "��"},
	{9, COLOR_WHITE, -1, "��"},
	{BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
};
/* ����1-9�������ú�����ʽ��ʾ�ڽ����ϣ���������ʾ״̬�� */
const BLOCK_DISPLAY_INFO bdi_prompt[] = {
	{BDI_VALUE_BLANK, -1, -1, "  "},  //�հ�
	{1, COLOR_HBLACK, -1, "��"},
	{2, COLOR_YELLOW, -1, "��"},
	{3, COLOR_HGREEN, -1, "��"},
	{4, COLOR_HCYAN, -1, "��"},
	{5, COLOR_HRED, -1, "��"},
	{6, COLOR_HPINK, -1, "��"},
	{7, COLOR_HYELLOW, -1, "��"},
	{8, COLOR_CYAN, -1, "��"},
	{9, COLOR_WHITE, -1, "��"},
	{BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
};
/* ����1-9�������ú�����ʽ��ʾ�ڽ����ϣ���ը/����״̬�� */
const BLOCK_DISPLAY_INFO bdi_exploded[] = {
	{BDI_VALUE_BLANK, -1, -1, "  "},  //�հ�
	{1, COLOR_HBLACK, -1, "��"},
	{2, COLOR_YELLOW, -1, "��"},
	{3, COLOR_HGREEN, -1, "��"},
	{4, COLOR_HCYAN, -1, "��"},
	{5, COLOR_HRED, -1, "��"},
	{6, COLOR_HPINK, -1, "��"},
	{7, COLOR_HYELLOW, -1, "��"},
	{8, COLOR_CYAN, -1, "��"},
	{9, COLOR_WHITE, -1, "��"},
	{BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
};

bool searchball0(int row, int col, char n[][9]);
void deleteball(int row, int col, char n[][9], const CONSOLE_GRAPHICS_INFO* const pCGI);
bool hintball(int row, int col, char n[][9], int hint[][9], const CONSOLE_GRAPHICS_INFO* const pCGI);
void to_be_continued(const char* game_name, const char* prompt, const CONSOLE_GRAPHICS_INFO* const bgi);
void fillball(int row, int col, char n[][9], const CONSOLE_GRAPHICS_INFO* const pCGI);
bool click(int row, int col, char n[][9], int hint[][9], int i, int j);
bool check(int row, int col, char n[][9], int hint[][9], int i, int j);
void mouseread(int row, int col, char n[][9], int hint[][9], const CONSOLE_GRAPHICS_INFO* const pCGI);
void changeball(int row, int col, char n[][9], int hint[][9], const CONSOLE_GRAPHICS_INFO* const pCGI);