/* 2354180 ���Ϻ� �ƿ� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <climits>
#include <conio.h>
#include "../include/cmd_console_tools.h"
#include "../include/cmd_gmw_tools.h"
#include<Windows.h>
using namespace std;

/* --------------------------------------------------
		�˴����Ը�����Ҫ�ľ�̬ȫ�ֱ������������٣����û�У�����̬ȫ��ֻ������/�궨�壨�������ޣ���
   -------------------------------------------------- */


/* --------------------------------------------------
		�˴����Ը�����Ҫ���ڲ��������ߺ���
		1�����������ޣ�����Ϊ gmw_inner_* 
		2����������
		3��������static������ȷ��ֻ�ڱ�Դ�ļ���ʹ��
   -------------------------------------------------- */
static int gmw_inner_moveblock(const CONSOLE_GRAPHICS_INFO* const pCGI, int x, int y, const int bdi_value, 
	const int blank_bdi_value, const BLOCK_DISPLAY_INFO* const bdi)
{

	int num = 0, i = 0;
	while (bdi[i].value != BDI_VALUE_END) {
		if (bdi[i].value == bdi_value) {
			num = i;
			break;
		}
		i++;  // �ƶ�����һ��Ԫ��
	}

	int bgcolor = (bdi[num].bgcolor == -1) ? pCGI->CFI.bgcolor : bdi[num].bgcolor;
	int fgcolor = (bdi[num].fgcolor == -1) ? pCGI->CFI.fgcolor : bdi[num].fgcolor;
	int X=x,Y=y;//���Ͻ�����
	//��contentΪNULL ���⴦��Ԥ��
	int length = snprintf(NULL, 0, "%d", bdi[num].value); // ��ȡ���賤��
	char* str = new char[length + 1]; // ��̬�����ڴ棬����������
	// ������ת��Ϊ�ַ���
	snprintf(str, length + 1, "%d", bdi[num].value);

	//��ʱ
	

	//���Ͻ�
	if (pCGI->CBI.block_border && bdi[num].value != BDI_VALUE_BLANK)
		cct_showstr(x, y, "�X", bgcolor, fgcolor);
	else
		cct_showstr(x, y, "  ", bgcolor, fgcolor);
	//��һ���м�
	for (int i = 0; i < (pCGI->CFI.block_width - 4) / 2; i++) {//���߲���
		cct_getxy(x, y);//��������
		if (pCGI->CBI.block_border && bdi[num].value != BDI_VALUE_BLANK)
			cct_showstr(x, y, "�T", bgcolor, fgcolor);
		else
			cct_showstr(x, y, "  ", bgcolor, fgcolor);
	}
	//���Ͻ�
	x = X + pCGI->CFI.block_width - 2;
	if (pCGI->CBI.block_border && bdi[num].value != BDI_VALUE_BLANK)
		cct_showstr(x, y, "�[", bgcolor, fgcolor);
	else
		cct_showstr(x, y, "  ", bgcolor, fgcolor);
	
	//�м�
	for (int j = 0; j < (pCGI->CFI.block_high - 2); j++) {
		x = X;
		y++;
		if (pCGI->CBI.block_border && bdi[num].value != BDI_VALUE_BLANK)
			cct_showstr(x, y, "�U", bgcolor, fgcolor);
		else
			cct_showstr(x, y, "  ", bgcolor, fgcolor);
		//��ʾͼ��
		if (bdi[num].content != NULL) {
			for (int i = 0; i < (pCGI->CFI.block_width - 4) / 2; i++) {//���߲���
				cct_getxy(x, y);//��������
				if (x == X + pCGI->CFI.block_width / 2 - 1 && y == Y + (pCGI->CFI.block_high - 1) / 2) {

					cct_showstr(x, y, bdi[num].content, bgcolor, fgcolor);
				
				}
				else
					cct_showstr(x, y, "  ", bgcolor, fgcolor);
			}
		}
		//��ʾ����
		if (bdi[num].content == NULL) {
			if (y == Y + (pCGI->CFI.block_high - 1) / 2) {
				for (int i = 0; i < (pCGI->CFI.block_width - length - 4) / 2; i++) {
					cct_getxy(x, y);
					cct_showstr(x, y, " ", bgcolor, fgcolor);

				}
				cct_getxy(x, y);
				cct_showstr(x, y, str, bgcolor, fgcolor);
				for (int i = 0; i < pCGI->CFI.block_width - length - 4 - (pCGI->CFI.block_width - length - 4) / 2; i++) {
					cct_getxy(x, y);
					cct_showstr(x, y, " ", bgcolor, fgcolor);

				}//��֤����

			}
			else {
				for (int i = 0; i < (pCGI->CFI.block_width - 4) / 2; i++) {
					cct_getxy(x, y);
					cct_showstr(x, y, "  ", bgcolor, fgcolor);
				}
			}
			
			
		}
		x = X + pCGI->CFI.block_width - 2;
		if (pCGI->CBI.block_border && bdi[num].value != BDI_VALUE_BLANK)
			cct_showstr(x, y, "�U", bgcolor, fgcolor);
		else
			cct_showstr(x, y, "  ", bgcolor, fgcolor);


	}
	

	//���
	x = X;
	y = Y + pCGI->CFI.block_high - 1;
	if (pCGI->CBI.block_border && bdi[num].value != BDI_VALUE_BLANK)
		cct_showstr(x, y, "�^", bgcolor, fgcolor);
	else
		cct_showstr(x, y, "  ", bgcolor, fgcolor);

	for (int i = 0; i < (pCGI->CFI.block_width - 4) / 2; i++) {//���߲���
		cct_getxy(x, y);//��������
		if (pCGI->CBI.block_border && bdi[num].value != BDI_VALUE_BLANK)
			cct_showstr(x, y, "�T", bgcolor, fgcolor);
		else
			cct_showstr(x, y, "  ", bgcolor, fgcolor);
	}

	x = X + pCGI->CFI.block_width - 2;
	if (pCGI->CBI.block_border && bdi[num].value != BDI_VALUE_BLANK)
		cct_showstr(x, y, "�a", bgcolor, fgcolor);
	else
		cct_showstr(x, y, "  ", bgcolor, fgcolor);

	//Ϊ��ֹͼ��������
	x = X + pCGI->CFI.block_width / 2 - 1;
	y = Y + (pCGI->CFI.block_high - 1) / 2;

	if (bdi[num].content != NULL)
		cct_showstr(x, y, bdi[num].content, bgcolor, fgcolor);
	


	delete[] str;



	return 0;
}
static int gmw_inner_updatesli(const CONSOLE_GRAPHICS_INFO* const pCGI, int nrow, int ncol)
{
	char temp[256];
	if (nrow == -1 && ncol == -1) {
		sprintf(temp, "[��ǰ���] λ�÷Ƿ�");
		gmw_status_line(pCGI, LOWER_STATUS_LINE, temp);
	}
	else {
		sprintf(temp, "[��ǰ���] %d��%d��",nrow,ncol);
		gmw_status_line(pCGI, LOWER_STATUS_LINE, temp);
	}

	return 0;
}
static int gmw_inner_tran(const CONSOLE_GRAPHICS_INFO* const pCGI,int& nrow, int& ncol, int x, int y)
{
	if (x > pCGI->frametop_x + 1 && x<pCGI->frametop_x + pCGI->col_num * pCGI->CFI.bwidth + 2 - pCGI->CFI.separator * 2
		&& y>pCGI->frametop_y && y < pCGI->framelower_y) {
		if (pCGI->CFI.separator) {
			if ((y - pCGI->frametop_y) % (pCGI->CFI.bhigh) != 0&&((x-pCGI->frametop_x)%(pCGI->CFI.bwidth)!=0&&(x-pCGI->frametop_x-1)% (pCGI->CFI.bwidth) != 0) ){//���ڷָ�����
				nrow = ((y - pCGI->frametop_y) - 1) / (pCGI->CFI.block_high + 1);
				ncol = ((x - pCGI->frametop_x) - 2) / (pCGI->CFI.block_width + 2);

			}
			else {//�ڷָ�����
				return -1;//λ�÷Ƿ�
			}

		}
		else {
			nrow = ((y - pCGI->frametop_y) - 1) / (pCGI->CFI.block_high );
			ncol = ((x - pCGI->frametop_x) - 2) / (pCGI->CFI.block_width);

			
		}
	}
	else
		return -1;//����Ϸ������,λ�÷Ƿ�

	return 0;
		
}
static int gmw_inner_drawno(const CONSOLE_GRAPHICS_INFO* const pCGI)
{
	

	if (pCGI->draw_frame_with_col_no) {
		int x = pCGI->frametop_x+pCGI->CFI.block_width/2+1, y = pCGI->frametop_y - 1;//��ʼλ��
		for (int j = 0; j < pCGI->col_num; j++) {
			cct_gotoxy(x, y);
			cct_setcolor(pCGI->area_bgcolor, pCGI->area_fgcolor);
			if (j <= 99)
				cout << j;
			else
				cout << "**";
			cct_setcolor();
			x += pCGI->CFI.bwidth;
		}

	}
	if (pCGI->draw_frame_with_row_no) {
		int x = pCGI->frametop_x -2, y = pCGI->frametop_y + (pCGI->CFI.block_high+1) / 2;//��ʼλ��
		for (int i = 1; i <= pCGI->row_num; i++) {
			cct_gotoxy(x, y);
			cct_setcolor(pCGI->area_bgcolor, pCGI->area_fgcolor);
			if (i <= 26)
				cout << char('A' + i-1);
			else if (i > 26 && i <= 52)
				cout <<char( 'a' + i - 27);
			else
				cout << "*";
			cct_setcolor();
			y += pCGI->CFI.bhigh;
		}
	}
	return 0;
}
static int gmw_inner_safecpy(char* dst, const char* src, int n)
{
	if (src == NULL) {
		strncpy(dst, "  ", n); // �������ո����NULL
		return 0;
	}

	int len = strlen(src);
	if (len > 2) {
		strncpy(dst, src, 2); // ֻȡǰ2�ֽ�
	}
	else {
		strncpy(dst, src, len); // ����ʵ�ʳ���
		if (len == 1) {
			dst[1] = ' '; // �����1�ֽڣ���һ���ո�
		}
	}
	dst[2] = '\0'; // ȷ���ַ�����'\0'����
	return 0;


}
static int gmw_inner_cal(CONSOLE_GRAPHICS_INFO* const pCGI)
{
	int topline = 0, lowerline = 0;;
	int rowno = 0, colno = 0;
	int rowsepar = 2;
	int colsepar = 4;
	if (pCGI->top_status_line)
		topline = 1;
	if (pCGI->lower_status_line)
		lowerline = 1;
	if (pCGI->draw_frame_with_col_no)
		colno = 1;//���һ��
	if (pCGI->draw_frame_with_row_no)
		rowno = 2;//�������
	if (pCGI->CFI.separator) {
		rowsepar = 1;
		colsepar = 2;
	}
		
	
	pCGI->start_x = pCGI->extern_left_cols;//����
	pCGI->start_y = pCGI->extern_up_lines; //����

	pCGI->lines = pCGI->extern_up_lines + topline + colno
		+pCGI->row_num*pCGI->CFI.bhigh+rowsepar+lowerline+pCGI->extern_down_lines+4;
	pCGI->cols = pCGI->extern_left_cols + rowno 
		+pCGI->col_num * pCGI->CFI.bwidth + colsepar + pCGI->extern_right_cols + 1;

	pCGI->frametop_x = pCGI->start_x + rowno;
	pCGI->frametop_y = pCGI->start_y + topline + colno;
	pCGI->framelower_x = pCGI->frametop_x;
	pCGI->framelower_y = pCGI->frametop_y + pCGI->row_num * pCGI->CFI.bhigh + (rowsepar - 1);

	pCGI->SLI.top_start_x = pCGI->start_x;
	pCGI->SLI.top_start_y = pCGI->start_y;
	pCGI->SLI.lower_start_x = pCGI->start_x;
	pCGI->SLI.lower_start_y = pCGI->framelower_y + 1;

	pCGI->SLI.width = pCGI->col_num * pCGI->CFI.bwidth + (colsepar - 2) + rowno+2;
	return 0;
	
}
/* ----------------------------------------------- 
		ʵ����������ĺ���������������׼����
   ----------------------------------------------- */
/***************************************************************************
  �������ƣ�
  ��    �ܣ�������Ϸ����ܵ�������
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int row						������(������Ϊ0���������ޣ���Ϊ��֤��ȷ��)
			const int col						������(������Ϊ0���������ޣ���Ϊ��֤��ȷ��)
  �� �� ֵ��
  ˵    ����1��ָ��������Ϸ�ľ������������ֵ
            2�����еı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_rowcol(CONSOLE_GRAPHICS_INFO *const pCGI, const int row, const int col)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (row < 0)
		pCGI->row_num = 0;
	if (col < 0)
		pCGI->col_num = 0;
	pCGI->col_num = col;
	pCGI->row_num = row;
	//Ӱ�촰�ڴ�С����ʼ����
	gmw_inner_cal(pCGI);


	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������������ڣ�����Ϸ�������������ڵ�����cmd���ڣ�����ɫ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int bg_color					��ǰ��ɫ��ȱʡCOLOR_BLACK��
		   const int fg_color					������ɫ��ȱʡCOLOR_WHITE��
		   const bool cascade					���Ƿ�����ȱʡΪtrue-������
  �� �� ֵ��
  ˵    ����1��cascade = trueʱ
				ͬ���޸���Ϸ���������ɫ
				ͬ���޸�����״̬���������ı��ı���ɫ��ǰ��ɫ����Ŀ�ı��ı���ɫ��ǰ��ɫ���䣩
			2���������ɫֵ���󼰳�ͻ����Ҫ��Ϊ��֤
				������ɫ��0-15
				    ǰ��ɫ����ɫ��ֵһ�µ����޷���������
					ǰ��ɫ������״̬����Ŀǰ��ɫ�������޷�������Ŀ��ʾ
					...
***************************************************************************/
int gmw_set_color(CONSOLE_GRAPHICS_INFO *const pCGI, const int bgcolor, const int fgcolor, const bool cascade)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	pCGI->area_bgcolor = bgcolor;
	pCGI->area_fgcolor = fgcolor;
	//cct_setcolor(bgcolor, fgcolor);//���ô�����ɫ

	if (cascade) {
		gmw_set_frame_color(pCGI);//��Ϸ������
		//��״̬��
		gmw_set_status_line_color(pCGI, TOP_STATUS_LINE,-1,-1,-1,pCGI->SLI.top_catchy_fgcolor);
		//��״̬��
		gmw_set_status_line_color(pCGI, LOWER_STATUS_LINE, -1, -1, -1, pCGI->SLI.top_catchy_fgcolor);
	}
	
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ô��ڵ�����
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const char *fontname					���������ƣ�ֻ����"Terminal"��"������"���֣������򷵻�-1�����ı����壩
		   const int fs_high					������߶ȣ�ȱʡ������Ϊ16�������������ƣ���Ϊ��֤��
		   const int fs_width					������߶ȣ�ȱʡ������Ϊ8�������������ƣ���Ϊ��֤��
  �� �� ֵ��
  ˵    ����1����cmd_console_tools�е�setfontsize���ƣ�Ŀǰֻ֧�֡��������塱�͡������塱
            2������������������ֱ�ӷ��أ�����ԭ�������ò���
***************************************************************************/
int gmw_set_font(CONSOLE_GRAPHICS_INFO *const pCGI, const char *fontname, const int fs_high, const int fs_width)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	if (fontname != "Terminal" && fontname != "������")
		return -1;

	
	strncpy(pCGI->CFT.font_type, fontname, FONTNAME_LEN);

	pCGI->CFT.font_size_high = fs_high;
	pCGI->CFT.font_size_width = fs_width;
	if (fontname != "Terminal")
		pCGI->CFT.font_size_width = 0;
	

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������ʱ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int type						����ʱ�����ͣ�ĿǰΪ3�֣�
		   const int delay_ms					����msΪ��λ����ʱ
			   ���߿����ʱ��0 ~ �������ޣ���Ϊ��֤��ȷ��<0����0��
			   ��ɫ�����ʱ��0 ~ �������ޣ���Ϊ��֤��ȷ��<0����0��
			   ɫ���ƶ�����ʱ��BLOCK_MOVED_DELAY_MS ~ �������ޣ���Ϊ��֤��ȷ�� <BLOCK_MOVED_DELAY_MS ���� BLOCK_MOVED_DELAY_MS��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_set_delay(CONSOLE_GRAPHICS_INFO *const pCGI, const int type, const int delay_ms)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	//��ʱ����
	if (delay_ms < 0) {
		if (type == DELAY_OF_BLOCK_MOVED)
			pCGI->delay_of_block_moved = 0;
		if (type == DELAY_OF_DRAW_BLOCK)
			pCGI->delay_of_draw_block = 0;
		if (type == DELAY_OF_DRAW_FRAME)
			pCGI->delay_of_draw_frame =0;
	}
	else {
		if (type == DELAY_OF_BLOCK_MOVED)
			pCGI->delay_of_block_moved = delay_ms;
		if (type == DELAY_OF_DRAW_BLOCK)
			pCGI->delay_of_draw_block = delay_ms;
		if (type == DELAY_OF_DRAW_FRAME)
			pCGI->delay_of_draw_frame = delay_ms;
	}

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ���������������Ϸ����ܽṹ֮����Ҫ�����Ķ�������
  ��    �ܣ�CONSOLE_GRAPHICS_INFO *const pCGI	��
		   const int up_lines					���ϲ�������У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
		   const int down_lines				���²�������У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
		   const int left_cols					����߶�����У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
		   const int right_cols				���ұ߶�����У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
  �� �� ֵ��
  ˵    �����������еı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_ext_rowcol(CONSOLE_GRAPHICS_INFO *const pCGI, const int up_lines, const int down_lines, const int left_cols, const int right_cols)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	//���������޶�������
	pCGI->extern_down_lines = down_lines;
	pCGI->extern_up_lines = up_lines;
	pCGI->extern_right_cols = right_cols;
	pCGI->extern_left_cols = left_cols;
	//Ӱ�촰�ڴ�С����ʼ����
	gmw_inner_cal(pCGI);


	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_TYPE �ṹ�е�11�����ͣ�ȱʡ4�֣�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��1 - ȫ�� 2 - ȫ���� 3 - ��˫���� 4 - �ᵥ��˫
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_set_frame_default_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const int type)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (type == 1) {//˫��
		strncpy(pCGI->CFI.top_left, "�X", CFI_LEN);
		strncpy(pCGI->CFI.lower_left, "�^", CFI_LEN);
		strncpy(pCGI->CFI.top_right, "�[", CFI_LEN);
		strncpy(pCGI->CFI.lower_right, "�a", CFI_LEN);
		strncpy(pCGI->CFI.h_normal, "�T", CFI_LEN);
		strncpy(pCGI->CFI.v_normal, "�U", CFI_LEN);
		strncpy(pCGI->CFI.h_top_separator, "�j", CFI_LEN);
		strncpy(pCGI->CFI.h_lower_separator, "�m", CFI_LEN);
		strncpy(pCGI->CFI.v_left_separator, "�d", CFI_LEN);
		strncpy(pCGI->CFI.v_right_separator, "�g", CFI_LEN);
		strncpy(pCGI->CFI.mid_separator, "�p", CFI_LEN);
	}
	if (type == 2) {//����
		strncpy(pCGI->CFI.top_left, "��", CFI_LEN);
		strncpy(pCGI->CFI.lower_left, "��", CFI_LEN);
		strncpy(pCGI->CFI.top_right, "��", CFI_LEN);
		strncpy(pCGI->CFI.lower_right, "��", CFI_LEN);
		strncpy(pCGI->CFI.h_normal, "��", CFI_LEN);
		strncpy(pCGI->CFI.v_normal, "��", CFI_LEN);
		strncpy(pCGI->CFI.h_top_separator, "��", CFI_LEN);
		strncpy(pCGI->CFI.h_lower_separator, "��", CFI_LEN);
		strncpy(pCGI->CFI.v_left_separator, "��", CFI_LEN);
		strncpy(pCGI->CFI.v_right_separator, "��", CFI_LEN);
		strncpy(pCGI->CFI.mid_separator, "��", CFI_LEN);
	}
	if (type == 3) {//��˫����
		strncpy(pCGI->CFI.top_left, "�V", CFI_LEN);
		strncpy(pCGI->CFI.lower_left, "�\", CFI_LEN);
		strncpy(pCGI->CFI.top_right, "�Y", CFI_LEN);
		strncpy(pCGI->CFI.lower_right, "�_", CFI_LEN);
		strncpy(pCGI->CFI.h_normal, "�T", CFI_LEN);
		strncpy(pCGI->CFI.v_normal, "��", CFI_LEN);
		strncpy(pCGI->CFI.h_top_separator, "�h", CFI_LEN);
		strncpy(pCGI->CFI.h_lower_separator, "�k", CFI_LEN);
		strncpy(pCGI->CFI.v_left_separator, "�b", CFI_LEN);
		strncpy(pCGI->CFI.v_right_separator, "�e", CFI_LEN);
		strncpy(pCGI->CFI.mid_separator, "�n", CFI_LEN);
	}
	if (type == 4) {//�ᵥ��˫
		strncpy(pCGI->CFI.top_left, "�W", CFI_LEN);
		strncpy(pCGI->CFI.lower_left, "�]", CFI_LEN);
		strncpy(pCGI->CFI.top_right, "�Z", CFI_LEN);
		strncpy(pCGI->CFI.lower_right, "�`", CFI_LEN);
		strncpy(pCGI->CFI.h_normal, "��", CFI_LEN);
		strncpy(pCGI->CFI.v_normal, "�U", CFI_LEN);
		strncpy(pCGI->CFI.h_top_separator, "�i", CFI_LEN);
		strncpy(pCGI->CFI.h_lower_separator, "�l", CFI_LEN);
		strncpy(pCGI->CFI.v_left_separator, "�c", CFI_LEN);
		strncpy(pCGI->CFI.v_right_separator, "�f", CFI_LEN);
		strncpy(pCGI->CFI.mid_separator, "�o", CFI_LEN);
	}
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_TYPE �ṹ�е�11������
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const char *...						����11�֣������.h���˴���
  �� �� ֵ��
  ˵    ����Լ��Ϊһ�������Ʊ��������ʹ���������ݣ���Ϊ��֤2�ֽ�
			1������2�ֽ���ֻȡǰ2�ֽ�
			2�������NULL���������ո����
			3�������1�ֽڣ���һ���ո������˶�������ʾ�ң������
***************************************************************************/
int gmw_set_frame_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const char *top_left, const char *lower_left, const char *top_right,
	const char *lower_right, const char *h_normal, const char *v_normal, const char *h_top_separator,
	const char *h_lower_separator, const char *v_left_separator, const char *v_right_separator, const char *mid_separator)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	gmw_inner_safecpy(pCGI->CFI.top_left, top_left, CFI_LEN);
	gmw_inner_safecpy(pCGI->CFI.lower_left, lower_left, CFI_LEN);
	gmw_inner_safecpy(pCGI->CFI.top_right, top_right, CFI_LEN);
	gmw_inner_safecpy(pCGI->CFI.lower_right, lower_right, CFI_LEN);
	gmw_inner_safecpy(pCGI->CFI.h_normal, h_normal, CFI_LEN);
	gmw_inner_safecpy(pCGI->CFI.v_normal, v_normal, CFI_LEN);
	gmw_inner_safecpy(pCGI->CFI.h_top_separator, h_top_separator, CFI_LEN);
	gmw_inner_safecpy(pCGI->CFI.h_lower_separator, h_lower_separator, CFI_LEN);
	gmw_inner_safecpy(pCGI->CFI.v_left_separator, v_left_separator, CFI_LEN);
	gmw_inner_safecpy(pCGI->CFI.v_right_separator, v_right_separator, CFI_LEN);
	gmw_inner_safecpy(pCGI->CFI.mid_separator, mid_separator, CFI_LEN);


	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_TYPE �ṹ�е�ɫ��������С���Ƿ���Ҫ�ָ��ߵ�
  ������������������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int block_width						����ȣ�����ȱʡ2����ΪԼ�������Ϊ�����Ʊ�����������������Ҫ+1��
			const int block_high						���߶ȣ�����ȱʡ1��
			const bool separator						���Ƿ���Ҫ�ָ��ߣ�ȱʡΪtrue����Ҫ�ָ��ߣ�
  �� �� ֵ��
  ˵    ������ܴ�С/�Ƿ���Ҫ�ָ��ߵȵı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_frame_style(CONSOLE_GRAPHICS_INFO *const pCGI, const int block_width, const int block_high, const bool separator)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	
	pCGI->CFI.block_width = block_width+block_width%2;
	pCGI->CFI.block_high = block_high;
	//�޷ָ���
	pCGI->CFI.separator = separator;

	//Ӱ�촰�ڴ�С����ʼ����
	if (separator) {
		pCGI->CFI.block_high_ext = 1;
		pCGI->CFI.block_width_ext = 2;
	}
	else {
		pCGI->CFI.block_high_ext = 0;
		pCGI->CFI.block_width_ext = 0;
	}
	pCGI->CFI.bwidth = pCGI->CFI.block_width_ext + pCGI->CFI.block_width;
	pCGI->CFI.bhigh = pCGI->CFI.block_high_ext + pCGI->CFI.block_high;
	
	gmw_inner_cal(pCGI);


	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_BORDER_TYPE �ṹ�е���ɫ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int bg_color					������ɫ��ȱʡ -1��ʾ�ô��ڱ���ɫ��
			const int fg_color					��ǰ��ɫ��ȱʡ -1��ʾ�ô���ǰ��ɫ��
  �� �� ֵ��
  ˵    �����������ɫֵ���󼰳�ͻ����Ҫ��Ϊ��֤
				������ɫ��0-15��ǰ��ɫ����ɫ��ֵһ�µ����޷��������ݵ�
***************************************************************************/
int gmw_set_frame_color(CONSOLE_GRAPHICS_INFO *const pCGI, const int bgcolor, const int fgcolor)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (bgcolor == -1) 
		pCGI->CFI.bgcolor = pCGI->area_bgcolor;
	else 
		pCGI->CFI.bgcolor = bgcolor;
	if (fgcolor == -1) 
		pCGI->CFI.fgcolor = pCGI->area_fgcolor;
	else 
		pCGI->CFI.fgcolor = fgcolor;
	
	//cct_setcolor(pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_BLOCK_INFO �ṹ�е�6�����ͣ�ȱʡ4�֣�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��1 - ȫ˫�� 2 - ȫ���� 3 - ��˫���� 4 - �ᵥ��˫
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_set_block_default_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const int type)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (type == 1) {//˫��
		strncpy(pCGI->CBI.top_left, "�X", CFI_LEN);
		strncpy(pCGI->CBI.lower_left, "�^", CFI_LEN);
		strncpy(pCGI->CBI.top_right, "�[", CFI_LEN);
		strncpy(pCGI->CBI.lower_right, "�a", CFI_LEN);
		strncpy(pCGI->CBI.h_normal, "�T", CFI_LEN);
		strncpy(pCGI->CBI.v_normal, "�U", CFI_LEN);
		
	}
	if (type == 2) {//����
		strncpy(pCGI->CBI.top_left, "��", CFI_LEN);
		strncpy(pCGI->CBI.lower_left, "��", CFI_LEN);
		strncpy(pCGI->CBI.top_right, "��", CFI_LEN);
		strncpy(pCGI->CBI.lower_right, "��", CFI_LEN);
		strncpy(pCGI->CBI.h_normal, "��", CFI_LEN);
		strncpy(pCGI->CBI.v_normal, "��", CFI_LEN);
		
	}
	if (type == 3) {//��˫����
		strncpy(pCGI->CBI.top_left, "�V", CFI_LEN);
		strncpy(pCGI->CBI.lower_left, "�\", CFI_LEN);
		strncpy(pCGI->CBI.top_right, "�Y", CFI_LEN);
		strncpy(pCGI->CBI.lower_right, "�_", CFI_LEN);
		strncpy(pCGI->CBI.h_normal, "�T", CFI_LEN);
		strncpy(pCGI->CBI.v_normal, "��", CFI_LEN);
	
	}
	if (type == 4) {//�ᵥ��˫
		strncpy(pCGI->CBI.top_left, "�W", CFI_LEN);
		strncpy(pCGI->CBI.lower_left, "�]", CFI_LEN);
		strncpy(pCGI->CBI.top_right, "�Z", CFI_LEN);
		strncpy(pCGI->CBI.lower_right, "�`", CFI_LEN);
		strncpy(pCGI->CBI.h_normal, "��", CFI_LEN);
		strncpy(pCGI->CBI.v_normal, "�U", CFI_LEN);
		
	}
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_BLOCK_INFO �ṹ�е�6������
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const char *...					����6�֣������.h���˴���
  �� �� ֵ��
  ˵    ����Լ��Ϊһ�������Ʊ��������ʹ���������ݣ���Ϊ��֤2�ֽ�
			1������2�ֽ���ֻȡǰ2�ֽ�
			2�������NULL���������ո����
			3�������1�ֽڣ���һ���ո������˶�������ʾ�ң������
***************************************************************************/
int gmw_set_block_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const char *top_left, const char *lower_left, const char *top_right, const char *lower_right, const char *h_normal, const char *v_normal)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	gmw_inner_safecpy(pCGI->CBI.top_left, top_left, CFI_LEN);
	gmw_inner_safecpy(pCGI->CBI.lower_left, lower_left, CFI_LEN);
	gmw_inner_safecpy(pCGI->CBI.top_right, top_right, CFI_LEN);
	gmw_inner_safecpy(pCGI->CBI.lower_right, lower_right, CFI_LEN);
	gmw_inner_safecpy(pCGI->CBI.h_normal, h_normal, CFI_LEN);
	gmw_inner_safecpy(pCGI->CBI.v_normal, v_normal, CFI_LEN);


	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����ÿ����Ϸɫ��(����)�Ƿ���ҪС�߿�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const bool on_off					��true - ��Ҫ flase - ����Ҫ��ȱʡfalse��
  �� �� ֵ��
  ˵    �����߿�Լ��Ϊ�����Ʊ����˫��
***************************************************************************/
int gmw_set_block_border_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	//�Ƿ���ҪС�߿�
	pCGI->CBI.block_border = on_off;
	

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ƿ���ʾ����״̬��
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��״̬�����ͣ���/�£�
			const bool on_off					��true - ��Ҫ flase - ����Ҫ��ȱʡtrue��
  �� �� ֵ��
  ˵    ����1��״̬�������Լ�����£�
			   1.1����״̬��ֻ��һ�У������������Ϸ�����/�б�����棬Ϊ��������ʼһ�У�����������Ͻ����������״̬�������꣩
			   1.2����״̬��ֻ��һ�У������������·����ߵ�����
			   1.3��״̬���Ŀ��Ϊ�������ȣ������Ϣ������ض�
		   2�����еı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_status_line_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const int type, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (type == TOP_STATUS_LINE) {
		pCGI->SLI.is_top_status_line = on_off;
		pCGI->top_status_line = on_off;
	}
	if (type == LOWER_STATUS_LINE) {
		pCGI->SLI.is_lower_status_line = on_off;
		pCGI->lower_status_line = on_off;
		
	}
	//�ı䴰�ڴ�С����ʼ����
	gmw_inner_cal(pCGI);



	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���������״̬������ɫ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��״̬�����ͣ���/�£�
			const int normal_bgcolor			�������ı�����ɫ��ȱʡ -1��ʾʹ�ô��ڱ���ɫ��
			const int normal_fgcolor			�������ı�ǰ��ɫ��ȱʡ -1��ʾʹ�ô���ǰ��ɫ��
			const int catchy_bgcolor			����Ŀ�ı�����ɫ��ȱʡ -1��ʾʹ�ô��ڱ���ɫ��
			const int catchy_fgcolor			����Ŀ�ı�ǰ��ɫ��ȱʡ -1��ʾʹ������ɫ��
  ���������
  �� �� ֵ��
  ˵    �����������ɫֵ���󼰳�ͻ����Ҫ��Ϊ��֤
				������ɫ��0-15��ǰ��ɫ����ɫ��ֵһ�µ����޷��������ݵ�
***************************************************************************/
int gmw_set_status_line_color(CONSOLE_GRAPHICS_INFO *const pCGI, const int type, const int normal_bgcolor, const int normal_fgcolor, const int catchy_bgcolor, const int catchy_fgcolor)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if(type==TOP_STATUS_LINE){
		if(normal_bgcolor==-1)
			pCGI->SLI.top_normal_bgcolor = pCGI->area_bgcolor;
		else
			pCGI->SLI.top_normal_bgcolor =normal_bgcolor;
		if (normal_fgcolor==-1)
			pCGI->SLI.top_normal_fgcolor = pCGI->area_fgcolor;
		else
			pCGI->SLI.top_normal_fgcolor = normal_fgcolor;
		if (catchy_bgcolor == -1)
			pCGI->SLI.top_catchy_bgcolor = pCGI->area_bgcolor;
		else
			pCGI->SLI.top_catchy_bgcolor = catchy_bgcolor;
		if (catchy_fgcolor==-1)
			pCGI->SLI.top_catchy_fgcolor = COLOR_HYELLOW;
		else
			pCGI->SLI.top_catchy_fgcolor = catchy_fgcolor;
		

	}
	if (type == LOWER_STATUS_LINE) {
		if (normal_bgcolor == -1)
			pCGI->SLI.lower_normal_bgcolor = pCGI->area_bgcolor;
		else
			pCGI->SLI.lower_normal_bgcolor = normal_bgcolor;
		if (normal_fgcolor==-1)
			pCGI->SLI.lower_normal_fgcolor = pCGI->area_fgcolor;
		else
			pCGI->SLI.lower_normal_fgcolor = normal_fgcolor;
		if (catchy_bgcolor == -1)
			pCGI->SLI.lower_catchy_bgcolor = pCGI->area_bgcolor;
		else
			pCGI->SLI.lower_catchy_bgcolor = catchy_bgcolor;
		if (catchy_fgcolor==-1)
			pCGI->SLI.lower_catchy_fgcolor = COLOR_HYELLOW;
		else
			pCGI->SLI.lower_catchy_fgcolor = catchy_fgcolor;

	}



	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ƿ���ʾ�к�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const bool on_off					��true - ��ʾ flase - ����ʾ��ȱʡfalse��
  �� �� ֵ��
  ˵    ����1���к�Լ��Ϊ��ĸA��ʼ�������У��������26�����a��ʼ������52��ͳһΪ*��ʵ��Ӧ�ò����ܣ�
            2���Ƿ���ʾ�кŵı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_rowno_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->draw_frame_with_row_no = on_off;
	//�ı䴰�ڴ�С����ʼ��ַ
	gmw_inner_cal(pCGI);

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ƿ���ʾ�б�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const bool on_off					��true - ��ʾ flase - ����ʾ��ȱʡfalse��
  �� �� ֵ��
  ˵    ����1���б�Լ��Ϊ����0��ʼ�������У�����0-99������99ͳһΪ**��ʵ��Ӧ�ò����ܣ�
            2���Ƿ���ʾ�б�ı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_colno_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->draw_frame_with_col_no = on_off;
	//�ı䴰�ڴ�С����ʼ��ַ
	gmw_inner_cal(pCGI);

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ӡ CONSOLE_GRAPHICS_INFO �ṹ���еĸ���Աֵ
  ���������
  �� �� ֵ��
  ˵    ����1�����������ã���ӡ��ʽ�Զ���
            2������������������δ���ù������Բ�ʵ��
***************************************************************************/
int gmw_print(const CONSOLE_GRAPHICS_INFO *const pCGI)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;



	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��� CONSOLE_GRAPHICS_INFO �ṹ����ȱʡֵ���г�ʼ��
  ���������CONSOLE_GRAPHICS_INFO *const pCGI������ṹָ��
		   const int row					����Ϸ����ɫ��������ȱʡ10��
		   const int col					����Ϸ����ɫ��������ȱʡ10��
		   const int bgcolor				���������ڱ���ɫ��ȱʡ COLOR_BLACK��
		   const int fgcolor				���������ڱ���ɫ��ȱʡ COLOR_WHITE��
  �� �� ֵ��
  ˵    �������ڱ�����/ǰ���ף�����16*8�����������޶������У�����״̬�����У����к�/�б꣬�������Ϊ˫�ߣ�ɫ����2/�߶�1/��С�߿���ɫ��
***************************************************************************/
int gmw_init(CONSOLE_GRAPHICS_INFO *const pCGI, const int row, const int col, const int bgcolor, const int fgcolor)
{
	/* �����ñ�� */
	pCGI->inited = CGI_INITED;
	
	//���ָ���,ɫ���2��1
	gmw_set_frame_style(pCGI);
	//����������ɫ����ok����Ϸ����״̬��
	gmw_set_color(pCGI,bgcolor,fgcolor);
	
	//��ʱ����
	gmw_set_delay(pCGI, DELAY_OF_BLOCK_MOVED, 15);
	gmw_set_delay(pCGI, DELAY_OF_DRAW_BLOCK, 0);
	gmw_set_delay(pCGI, DELAY_OF_DRAW_FRAME, 0);

	//������������
	gmw_set_rowcol(pCGI, row,col);
	
	//��������
	gmw_set_font(pCGI,"������");

	//���������޶�������
	gmw_set_ext_rowcol(pCGI);

	//����״̬������
	gmw_set_status_line_switch(pCGI, TOP_STATUS_LINE);
	gmw_set_status_line_switch(pCGI, LOWER_STATUS_LINE);
	//��״̬����ɫ
	gmw_set_status_line_color(pCGI, LOWER_STATUS_LINE);
	//��״̬����ɫ
	gmw_set_status_line_color(pCGI, TOP_STATUS_LINE);
	//���к�/�б�
	gmw_set_colno_switch(pCGI);
	gmw_set_rowno_switch(pCGI);
	//�������
	gmw_set_frame_default_linetype(pCGI, 1);
	
	//ɫ����С�߿�
	gmw_set_block_border_switch(pCGI);
	

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������Ϸ���
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
  �� �� ֵ��
  ˵    ��������ɲο�demo��Ч��
***************************************************************************/
int gmw_draw_frame(const CONSOLE_GRAPHICS_INFO *const pCGI)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	int x, y;
	//�Ƚ��д�������
	cct_setcolor(pCGI->area_bgcolor, pCGI->area_fgcolor);
	
	cct_setfontsize(pCGI->CFT.font_type,pCGI->CFT.font_size_high, pCGI->CFT.font_size_width);
	cct_setconsoleborder(pCGI->cols, pCGI->lines);
	cct_setcolor();//�ָ�ȱʡ��ɫ
	
	//��ʱ����
	Sleep(pCGI->delay_of_draw_frame);

	//��һ�б߿�
	cct_gotoxy(pCGI->frametop_x, pCGI->frametop_y);
	//���Ͻ�
	cct_showstr(pCGI->frametop_x, pCGI->frametop_y, pCGI->CFI.top_left, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
	for (int j = 0; j <pCGI->col_num; j++) {
		Sleep(pCGI->delay_of_draw_frame);
		for (int i = 0; i < pCGI->CFI.block_width/ 2; i++) {
			cct_getxy(x, y);
			cct_showstr(x, y, pCGI->CFI.h_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
		}
		//�зָ���
		if (pCGI->CFI.separator&& j != pCGI->col_num - 1) {
				cct_getxy(x, y);
				cct_showstr(x, y, pCGI->CFI.h_top_separator, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
			
		}
		

	}
    cct_getxy(x, y);
    cct_showstr(x, y, pCGI->CFI.top_right, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
	
	//�м伸��
	for (int k = 0; k < pCGI->row_num-1; k++) {
		x = pCGI->frametop_x;
		for (int i = 0; i < pCGI->CFI.block_high; i++) {
			x = pCGI->frametop_x,y++;
			cct_showstr(x, y, pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
			cct_getxy(x, y);
			if (pCGI->CFI.separator) {
				for (int j = 0; j < pCGI->col_num - 1; j++) {//�������������
					x += pCGI->CFI.block_width;
					cct_showstr(x, y, pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
					cct_getxy(x, y);
				}
				cct_showstr(pCGI->frametop_x + pCGI->col_num * pCGI->CFI.bwidth, y,
					pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
			}
			else {
				cct_showstr(pCGI->frametop_x + pCGI->col_num * pCGI->CFI.bwidth+2, y,
					pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
			}

		}
		x = pCGI->frametop_x;//
		if (pCGI->CFI.separator) {
			    
			y++;
			cct_showstr(x, y, pCGI->CFI.v_left_separator, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
			cct_getxy(x, y);
		
			
			for (int j = 0; j < pCGI->col_num; j++) {
				Sleep(pCGI->delay_of_draw_frame);
				for (int i = 0; i < pCGI->CFI.block_width / 2; i++) {
					cct_getxy(x, y);
					cct_showstr(x, y, pCGI->CFI.h_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
				}
				
				if (j != pCGI->col_num - 1) {
					
						cct_getxy(x, y);
						cct_showstr(x, y, pCGI->CFI.mid_separator, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
					

				}
				else {
					
						cct_getxy(x, y);
						cct_showstr(x, y, pCGI->CFI.v_right_separator, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
					
				}

			}
		}

	}
   //���һ��

	for (int i = 0; i < pCGI->CFI.block_high; i++) {
		x = pCGI->frametop_x,y++;
		cct_showstr(x, y, pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
		cct_getxy(x, y);
		if (pCGI->CFI.separator) {
			for (int j = 0; j < pCGI->col_num - 1; j++) {//�������������
				x += pCGI->CFI.block_width;
				cct_showstr(x, y, pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
				cct_getxy(x, y);
			}
			cct_showstr(pCGI->frametop_x + pCGI->col_num * pCGI->CFI.bwidth, y,
				pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
		}
		else {
			cct_showstr(pCGI->frametop_x + pCGI->col_num * pCGI->CFI.bwidth + 2, y,
				pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
		}

	}
	x = pCGI->frametop_x, y++;
	//���½�
	cct_showstr(x, y, pCGI->CFI.lower_left, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
	for (int j = 0; j < pCGI->col_num; j++) {
		Sleep(pCGI->delay_of_draw_frame);
		for (int i = 0; i < pCGI->CFI.block_width / 2; i++) {
			cct_getxy(x, y);
			cct_showstr(x, y, pCGI->CFI.h_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
		}
		//�зָ���
		if (pCGI->CFI.separator && j != pCGI->col_num - 1) {
			cct_getxy(x, y);
			cct_showstr(x, y, pCGI->CFI.h_lower_separator, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);

		}


	}
	cct_getxy(x, y);
	cct_showstr(x, y, pCGI->CFI.lower_right, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
	

//���б�
	gmw_inner_drawno(pCGI);
	


	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���״̬������ʾ��Ϣ
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int type							��ָ������/��״̬��
		   const char *msg						��������Ϣ
		   const char *catchy_msg					����Ҫ�ر��ע����Ϣ����������Ϣǰ��ʾ��
  �� �� ֵ��
  ˵    ����1���������޶�Ϊ����ܵĿ�ȣ����к��б�λ�ã����������ȥ
			2��������һ���ַ���ĳ���ֵ�ǰ������ᵼ�º������룬Ҫ����
***************************************************************************/
int gmw_status_line(const CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const char* msg, const char* catchy_msg)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	int x, y;


	int len1 = catchy_msg ? strlen(catchy_msg) : 0;
	int len2 = msg ? strlen(msg) : 0;

	int min1 = min(len1, pCGI->SLI.width);
	int min2 = min(len2, pCGI->SLI.width);
	if (type == TOP_STATUS_LINE) {//������ʼ��ַ
		if (!pCGI->SLI.is_top_status_line)
			return -1;
		x = pCGI->SLI.top_start_x, y = pCGI->SLI.top_start_y;


		for (int i = 0; i < min1; i++) {
			if (i == min1 - 1)
				if (catchy_msg[i] >= 0xA1 && catchy_msg[i] <= 0xFE)
					break;

			cct_showch(x, y, catchy_msg[i], pCGI->SLI.top_catchy_bgcolor, pCGI->SLI.top_catchy_fgcolor);
			cct_getxy(x, y);//��������

		}

		for (int i = 0; i < min2; i++) {
			if (i == min2 - 1)
				if (msg[i] >= 0xA1 && msg[i] <= 0xFE)
					break;

			cct_showch(x, y, msg[i], pCGI->SLI.top_normal_bgcolor, pCGI->SLI.top_normal_fgcolor);
			cct_getxy(x, y);//��������

		}
	}
	if (type == LOWER_STATUS_LINE) {
		if (!pCGI->SLI.is_lower_status_line)
			return -1;
		x = pCGI->SLI.lower_start_x, y = pCGI->SLI.lower_start_y;
		for (int i = 0; i < min1; i++) {
			if (i == min1 - 1)
				if (catchy_msg[i] >= 0xA1 && catchy_msg[i] <= 0xFE)
					break;

			cct_showch(x, y, catchy_msg[i], pCGI->SLI.lower_catchy_bgcolor, pCGI->SLI.lower_catchy_fgcolor);
			cct_getxy(x, y);//��������

		}
		for (int i = 0; i < min2; i++) {
			if (i == min2 - 1)
				if (msg[i] >= 0xA1 && msg[i] <= 0xFE)
					break;
			if(i==0)
				cct_showstr(x, y, "                                      ", pCGI->SLI.lower_normal_bgcolor, pCGI->SLI.lower_normal_fgcolor);

			cct_showch(x, y, msg[i], pCGI->SLI.lower_normal_bgcolor, pCGI->SLI.lower_normal_fgcolor);
			cct_getxy(x, y);//��������

		}
	}


	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʾĳһ��ɫ��(����Ϊ�ַ���������Ϊrow/col)
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int row_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int col_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int bdi_value						����Ҫ��ʾ��ֵ
		   const BLOCK_DISPLAY_INFO *const bdi		����Ÿ�ֵ��Ӧ����ʾ��Ϣ�Ľṹ������
  �� �� ֵ��
  ˵    ����1��BLOCK_DISPLAY_INFO �ĺ����ͷ�ļ����÷��ο���������
			2��bdi_valueΪ BDI_VALUE_BLANK ��ʾ�հ׿飬Ҫ���⴦��
***************************************************************************/
int gmw_draw_block(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, const int bdi_value, const BLOCK_DISPLAY_INFO* const bdi)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	int num = 0, i = 0;
	while (bdi[i].value != BDI_VALUE_END) {
		if (bdi[i].value == bdi_value) {
			num = i;
			break;
		}
		i++;  // �ƶ�����һ��Ԫ��
	}



	//��ʼλ��
	int bgcolor = (bdi[num].bgcolor == -1) ? pCGI->CFI.bgcolor : bdi[num].bgcolor;
	int fgcolor = (bdi[num].fgcolor == -1) ? pCGI->CFI.fgcolor : bdi[num].fgcolor;
	int x = pCGI->frametop_x + 2 + col_no * pCGI->CFI.bwidth, y = pCGI->frametop_y + 1 + row_no * pCGI->CFI.bhigh;

	//��contentΪNULL ���⴦��Ԥ��
	int length = snprintf(NULL, 0, "%d", bdi[num].value); // ��ȡ���賤��
	char* str = new char[length + 1]; // ��̬�����ڴ棬����������
	// ������ת��Ϊ�ַ���
	snprintf(str, length + 1, "%d", bdi[num].value);

	//��ʱ
	Sleep(pCGI->delay_of_draw_block);
	
	//���Ͻ�
	if (pCGI->CBI.block_border&& bdi[num].value!=BDI_VALUE_BLANK)
		cct_showstr(x, y, "�X", bgcolor, fgcolor);
	else
		cct_showstr(x, y, "  ", bgcolor, fgcolor);
	//��һ���м�
	
	for (int i = 0; i < (pCGI->CFI.block_width - 4) / 2; i++) {//���߲���
		cct_getxy(x, y);//��������
		if (pCGI->CBI.block_border&& bdi[num].value != BDI_VALUE_BLANK)
			cct_showstr(x, y, "�T", bgcolor, fgcolor);
		else
			cct_showstr(x, y, "  ", bgcolor, fgcolor);
	}
	//���Ͻ�
	
	x = pCGI->frametop_x + 2 + col_no * pCGI->CFI.bwidth + (pCGI->CFI.block_width - 2);
	if (pCGI->CBI.block_border && bdi[num].value != BDI_VALUE_BLANK)
		cct_showstr(x, y, "�[", bgcolor, fgcolor);
	else
		cct_showstr(x, y, "  ", bgcolor, fgcolor);
	//�м�
	
	for (int j = 0; j < (pCGI->CFI.block_high - 2); j++) {
		x = pCGI->frametop_x + 2 + col_no * pCGI->CFI.bwidth;
		y++;
		if (pCGI->CBI.block_border && bdi[num].value != BDI_VALUE_BLANK)
			cct_showstr(x, y, "�U", bgcolor, fgcolor);
		else
			cct_showstr(x, y, "  ", bgcolor, fgcolor);

		//��ʾͼ��
		if (bdi[num].content != NULL||bdi[num].value==BDI_VALUE_BLANK) {
			for (int i = 0; i < (pCGI->CFI.block_width - 4) / 2; i++) {//���߲���
				cct_getxy(x, y);//��������
				if (x == pCGI->frametop_x + 1 + col_no * pCGI->CFI.bwidth + pCGI->CFI.block_width / 2
					&& y == pCGI->frametop_y + row_no * pCGI->CFI.bhigh + (pCGI->CFI.block_high + 1) / 2 && bdi[num].value != BDI_VALUE_BLANK) {

					cct_showstr(x, y, bdi[num].content, bgcolor, fgcolor);

				}

				else
					cct_showstr(x, y, "  ", bgcolor, fgcolor);
			}
		}
		//��ʾ����
		if (bdi[num].content == NULL&& bdi[num].value!=BDI_VALUE_BLANK) {
			if (y == pCGI->frametop_y + row_no * pCGI->CFI.bhigh + (pCGI->CFI.block_high + 1) / 2) {
				for (int i = 0; i < (pCGI->CFI.block_width - length-4) / 2; i++){
					cct_getxy(x, y);
					cct_showstr(x, y, " ", bgcolor, fgcolor);

				}
				cct_getxy(x, y);
				cct_showstr(x, y, str, bgcolor, fgcolor);

				for (int i = 0; i < pCGI->CFI.block_width- length-4- (pCGI->CFI.block_width - length-4) / 2; i++) {
					cct_getxy(x, y);
					cct_showstr(x, y, " ", bgcolor, fgcolor);

				}//��֤����

			}
			else {
				for (int i = 0; i < (pCGI->CFI.block_width - 4) / 2; i++) {
					cct_getxy(x, y);
					cct_showstr(x, y, "  ", bgcolor, fgcolor);
				}
			}
		 
		}
		//����
		x = pCGI->frametop_x + 2 + col_no * pCGI->CFI.bwidth+(pCGI->CFI.block_width-2);
		if (pCGI->CBI.block_border && bdi[num].value != BDI_VALUE_BLANK)
			cct_showstr(x, y, "�U", bgcolor, fgcolor);
		else
			cct_showstr(x, y, "  ", bgcolor, fgcolor);
	}
	//���
	x = pCGI->frametop_x + 2 + col_no * pCGI->CFI.bwidth;
	y = pCGI->frametop_y + row_no * pCGI->CFI.bhigh + pCGI->CFI.block_high;
	if (pCGI->CBI.block_border && bdi[num].value != BDI_VALUE_BLANK)
		cct_showstr(x, y, "�^", bgcolor, fgcolor);
	else
		cct_showstr(x, y, "  ", bgcolor, fgcolor);

	for (int i = 0; i < (pCGI->CFI.block_width - 4) / 2; i++) {//���߲���
		cct_getxy(x, y);//��������
		if (pCGI->CBI.block_border && bdi[num].value != BDI_VALUE_BLANK)
			cct_showstr(x, y, "�T", bgcolor, fgcolor);
		else
			cct_showstr(x, y, "  ", bgcolor, fgcolor);
	}

	x = pCGI->frametop_x + 2 + col_no * pCGI->CFI.bwidth + (pCGI->CFI.block_width - 2);
	if (pCGI->CBI.block_border && bdi[num].value != BDI_VALUE_BLANK)
		cct_showstr(x, y, "�a", bgcolor, fgcolor);
	else
		cct_showstr(x, y, "  ", bgcolor, fgcolor);

	//Ϊ��ֹͼ��������
		x = pCGI->frametop_x + 1 + col_no * pCGI->CFI.bwidth + pCGI->CFI.block_width / 2;
		y = pCGI->frametop_y + row_no * pCGI->CFI.bhigh + (pCGI->CFI.block_high + 1) / 2;

		if (bdi[num].content != NULL)
			cct_showstr(x, y, bdi[num].content, bgcolor, fgcolor);
		
		
	
	delete[] str;
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ƶ�ĳһ��ɫ��
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int row_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int col_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int bdi_value						����Ҫ��ʾ��ֵ
		   const int blank_bdi_value				���ƶ����������ڶ���Ч����ʾʱ���ڱ�ʾ�հ׵�ֵ��һ��Ϊ0���˴���Ϊ�������룬�ǿ��ǵ����ܳ��ֵ����������
		   const BLOCK_DISPLAY_INFO *const bdi		�������ʾֵ/�հ�ֵ��Ӧ����ʾ��Ϣ�Ľṹ������
		   const int direction						���ƶ�����һ�����֣������cmd_gmw_tools.h
		   const int distance						���ƶ����루��1��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_move_block(const CONSOLE_GRAPHICS_INFO *const pCGI, const int row_no, const int col_no, const int bdi_value, const int blank_bdi_value, const BLOCK_DISPLAY_INFO *const bdi, const int direction, const int distance)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	int x, y;//��ǰ����
	//��λ��ʼ���Ͻ�
	int X = col_no * (pCGI->CFI.bwidth) + pCGI->frametop_x + 2;
	int Y = row_no * (pCGI->CFI.bhigh) + pCGI->frametop_y + 1;
	
	
	if (direction == UP_TO_DOWN) {
		for (int k = 0; k < distance * pCGI->CFI.bhigh; k++) {
			Sleep(pCGI->delay_of_block_moved);

			for (int i = 0; i < pCGI->CFI.block_width / 2; i++) {
				y = Y+k;//ɫ��ĵ�k��
				x = X+2*i;//ɫ�����Ͻ�
				
				if (pCGI->CFI.separator && (y - Y - pCGI->CFI.block_high) % pCGI->CFI.bhigh == 0)
					cct_showstr(x, y, pCGI->CFI.h_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
				else
					cct_showstr(x, y, "  ", pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
				
			}
			y = Y + (k + 1);
			x = X;
			gmw_inner_moveblock(pCGI, x, y, bdi_value, blank_bdi_value, bdi);

		}
	}
	if (direction == DOWN_TO_UP) {
		for (int k = 0; k < distance * pCGI->CFI.bhigh; k++) {
			Sleep(pCGI->delay_of_block_moved);

			for (int i = 0; i < pCGI->CFI.block_width / 2; i++) {
				y = Y+pCGI->CFI.block_high-1 - k;//ɫ��ĵ�k��
				x = X + 2 * i;//ɫ�����½�

				if (pCGI->CFI.separator && (Y + pCGI->CFI.block_high - 1 -y - pCGI->CFI.block_high) % pCGI->CFI.bhigh == 0)
					cct_showstr(x, y, pCGI->CFI.h_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
				else
					cct_showstr(x, y, "  ", pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);


			}
			y = Y - (k + 1);
			x = X;
			gmw_inner_moveblock(pCGI, x, y, bdi_value, blank_bdi_value, bdi);

		}
	}
	if (direction == LEFT_TO_RIGHT) {
		for (int k = 0; k < (distance * pCGI->CFI.bwidth)/2; k++) {
			Sleep(pCGI->delay_of_block_moved);

			for (int i = 0; i < pCGI->CFI.block_high ; i++) {
				y = Y+i;
				x = X+k*2 ;//ɫ�����Ͻ�

				if (pCGI->CFI.separator && (x - X- pCGI->CFI.block_width) % pCGI->CFI.bwidth == 0)
					cct_showstr(x, y, pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
				else
					cct_showstr(x, y, "  ", pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);

			}
			y = Y;
			x = X+(k+1)*2;
			gmw_inner_moveblock(pCGI, x, y, bdi_value, blank_bdi_value, bdi);

		}
	}
	if (direction == RIGHT_TO_LEFT) {
		for (int k = 0; k < (distance * pCGI->CFI.bwidth)/2; k++) {
			Sleep(pCGI->delay_of_block_moved);

			for (int i = 0; i < pCGI->CFI.block_high; i++) {
				y = Y + i;
				x = X+pCGI->CFI.block_width-2 - k * 2;//���Ͻ�

				if (pCGI->CFI.separator && (X + pCGI->CFI.block_width - 2 -x - pCGI->CFI.block_width) % pCGI->CFI.bwidth == 0)
					cct_showstr(x, y, pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
				else
					cct_showstr(x, y, "  ", pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);

			}
			y = Y;
			x = X - (k + 1) * 2;
			gmw_inner_moveblock(pCGI, x, y, bdi_value, blank_bdi_value, bdi);

		}
	}


	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������̻����
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   int &MAction							��������� CCT_MOUSE_EVENT�����ֵ��Ч��Ϊ MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK/MOUSE_RIGHT_BUTTON_CLICK ����֮һ
		                                               ������� CCT_KEYBOARD_EVENT�����ֵ��Ч
		   int &MRow								��������� CCT_MOUSE_EVENT �� MAction = MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK�����ֵ��Ч����ʾ���ѡ�����Ϸ������кţ���0��ʼ��
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   int &MCol								��������� CCT_MOUSE_EVENT �� MAction = MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK�����ֵ��Ч����ʾ���ѡ�����Ϸ������кţ���0��ʼ��
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   int &KeyCode1							��������� CCT_KEYBOARD_EVENT�����ֵ��Ч��Ϊ�����ļ��루���˫���룬��Ϊ��һ����
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   int &KeyCode2							��������� CCT_KEYBOARD_EVENT�����ֵ��Ч��Ϊ�����ļ��루���˫���룬��Ϊ�ڶ���������ǵ����룬��Ϊ0��
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   const bool update_lower_status_line		������ƶ�ʱ���Ƿ�Ҫ�ڱ���������ʾ"[��ǰ���] *��*��/λ�÷Ƿ�"����Ϣ��true=��ʾ��false=����ʾ��ȱʡΪtrue��
  �� �� ֵ����������Լ��
		   1�����������ƶ����õ���MRow/MCol�봫�����ͬ(���ָ��΢С���ƶ�)���򲻷��أ�������
							  �õ����зǷ�λ�ã��򲻷��أ����� update_lower_status_line ����������״̬����ʾ"[��ǰ���] λ�÷Ƿ�"
							  �õ���MRow/MCol�봫��Ĳ�ͬ(��������һ���仯)������ update_lower_status_line ����������״̬����ʾ"[��ǰ���] *��*��"���ٷ���MOUSE_ONLY_MOVED����Щ��Ϸ���غ�Ҫ����ɫ��Ĳ�ͬ��ɫ��ʾ��
		   2������ǰ������������ҵ�ǰ���ָ��ͣ��������Ϸ�����*��*���ϣ��򷵻� CCT_MOUSE_EVENT ��MAction Ϊ MOUSE_LEFT_BUTTON_CLICK, MRow Ϊ�кţ�MCol Ϊ�б�
		                          �ҵ�ǰ���ָ��ͣ���ڷǷ����򣨷���Ϸ������Ϸ�����еķָ��ߣ����򲻷��أ����� update_lower_status_line ����������״̬����ʾ"[��ǰ���] λ�÷Ƿ�"
		   3������ǰ�������Ҽ������ж����ָ��ͣ�������Ƿ�Ϸ���ֱ�ӷ��� CCT_MOUSE_EVENT ��MAction Ϊ MOUSE_RIGHT_BUTTON_CLICK, MRow��MColȡ��ǰֵ����Ϊ�������ǵ��Ҽ������Ҫ���꣩
		   4��������¼����ϵ�ĳ������˫���밴��������ֱ�ӷ��� CCT_KEYBOARD_EVENT��KeyCode1/KeyCode2��Ϊ��Ӧ�ļ���ֵ
 ˵    ����ͨ������ cmd_console_tools.cpp �е� read_keyboard_and_mouse ����ʵ��
***************************************************************************/
int gmw_read_keyboard_and_mouse(const CONSOLE_GRAPHICS_INFO *const pCGI, int &MAction, int &MRow, int &MCol, int &KeyCode1, int &KeyCode2, const bool update_lower_status_line)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	int X, Y;
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;
	int nrow, ncol;
	int rett;

	cct_enable_mouse();
	cct_setcursor(CURSOR_INVISIBLE);	//�رչ��
	while (loop) {
		ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

		

		if (ret == CCT_MOUSE_EVENT) {
			rett = gmw_inner_tran(pCGI, nrow, ncol, X, Y);//�õ��к��б�

			if (maction == MOUSE_ONLY_MOVED) {//�ƶ�
				if (rett==0&&nrow == MRow && ncol == MCol) {
					continue;
				}
				else if (rett==-1){
					gmw_inner_updatesli(pCGI, -1, -1);
					continue;
				}
				else {
					gmw_inner_updatesli(pCGI, nrow, ncol);
					MRow = nrow, MCol = ncol;
					MAction = MOUSE_ONLY_MOVED;
					return CCT_MOUSE_EVENT;
				}
			}
			else if (maction == MOUSE_LEFT_BUTTON_CLICK) {//���
				if (rett == 0) {
					
					MRow = nrow, MCol = ncol;
					MAction = MOUSE_LEFT_BUTTON_CLICK;
					return CCT_MOUSE_EVENT;
				}
				else {
					gmw_inner_updatesli(pCGI, -1, -1);
					continue;
				}
			}
			else {//�Ҽ�

				MAction = MOUSE_RIGHT_BUTTON_CLICK;
				return CCT_MOUSE_EVENT;
			}

		}
		else if (ret == CCT_KEYBOARD_EVENT) {
			KeyCode1 = keycode1;
			KeyCode2 = keycode2;
			return CCT_KEYBOARD_EVENT;
		}


	}
	return 0; //�˾�ɸ�����Ҫ�޸�
}
