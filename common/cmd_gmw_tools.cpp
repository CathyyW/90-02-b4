/* 2354180 王韵涵 计科 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <climits>
#include <conio.h>
#include "../include/cmd_console_tools.h"
#include "../include/cmd_gmw_tools.h"
#include<Windows.h>
using namespace std;

/* --------------------------------------------------
		此处可以给出需要的静态全局变量（尽可能少，最好没有）、静态全局只读变量/宏定义（个数不限）等
   -------------------------------------------------- */


/* --------------------------------------------------
		此处可以给出需要的内部辅助工具函数
		1、函数名不限，建议为 gmw_inner_* 
		2、个数不限
		3、必须是static函数，确保只在本源文件中使用
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
		i++;  // 移动到下一个元素
	}

	int bgcolor = (bdi[num].bgcolor == -1) ? pCGI->CFI.bgcolor : bdi[num].bgcolor;
	int fgcolor = (bdi[num].fgcolor == -1) ? pCGI->CFI.fgcolor : bdi[num].fgcolor;
	int X=x,Y=y;//左上角坐标
	//当content为NULL 特殊处理预先
	int length = snprintf(NULL, 0, "%d", bdi[num].value); // 获取所需长度
	char* str = new char[length + 1]; // 动态分配内存，包括结束符
	// 将整数转换为字符串
	snprintf(str, length + 1, "%d", bdi[num].value);

	//延时
	

	//左上角
	if (pCGI->CBI.block_border && bdi[num].value != BDI_VALUE_BLANK)
		cct_showstr(x, y, "╔", bgcolor, fgcolor);
	else
		cct_showstr(x, y, "  ", bgcolor, fgcolor);
	//第一行中间
	for (int i = 0; i < (pCGI->CFI.block_width - 4) / 2; i++) {//横线部分
		cct_getxy(x, y);//更新坐标
		if (pCGI->CBI.block_border && bdi[num].value != BDI_VALUE_BLANK)
			cct_showstr(x, y, "═", bgcolor, fgcolor);
		else
			cct_showstr(x, y, "  ", bgcolor, fgcolor);
	}
	//右上角
	x = X + pCGI->CFI.block_width - 2;
	if (pCGI->CBI.block_border && bdi[num].value != BDI_VALUE_BLANK)
		cct_showstr(x, y, "╗", bgcolor, fgcolor);
	else
		cct_showstr(x, y, "  ", bgcolor, fgcolor);
	
	//中间
	for (int j = 0; j < (pCGI->CFI.block_high - 2); j++) {
		x = X;
		y++;
		if (pCGI->CBI.block_border && bdi[num].value != BDI_VALUE_BLANK)
			cct_showstr(x, y, "║", bgcolor, fgcolor);
		else
			cct_showstr(x, y, "  ", bgcolor, fgcolor);
		//显示图案
		if (bdi[num].content != NULL) {
			for (int i = 0; i < (pCGI->CFI.block_width - 4) / 2; i++) {//横线部分
				cct_getxy(x, y);//更新坐标
				if (x == X + pCGI->CFI.block_width / 2 - 1 && y == Y + (pCGI->CFI.block_high - 1) / 2) {

					cct_showstr(x, y, bdi[num].content, bgcolor, fgcolor);
				
				}
				else
					cct_showstr(x, y, "  ", bgcolor, fgcolor);
			}
		}
		//显示数字
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

				}//保证填满

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
			cct_showstr(x, y, "║", bgcolor, fgcolor);
		else
			cct_showstr(x, y, "  ", bgcolor, fgcolor);


	}
	

	//最后
	x = X;
	y = Y + pCGI->CFI.block_high - 1;
	if (pCGI->CBI.block_border && bdi[num].value != BDI_VALUE_BLANK)
		cct_showstr(x, y, "╚", bgcolor, fgcolor);
	else
		cct_showstr(x, y, "  ", bgcolor, fgcolor);

	for (int i = 0; i < (pCGI->CFI.block_width - 4) / 2; i++) {//横线部分
		cct_getxy(x, y);//更新坐标
		if (pCGI->CBI.block_border && bdi[num].value != BDI_VALUE_BLANK)
			cct_showstr(x, y, "═", bgcolor, fgcolor);
		else
			cct_showstr(x, y, "  ", bgcolor, fgcolor);
	}

	x = X + pCGI->CFI.block_width - 2;
	if (pCGI->CBI.block_border && bdi[num].value != BDI_VALUE_BLANK)
		cct_showstr(x, y, "╝", bgcolor, fgcolor);
	else
		cct_showstr(x, y, "  ", bgcolor, fgcolor);

	//为防止图案被覆盖
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
		sprintf(temp, "[当前光标] 位置非法");
		gmw_status_line(pCGI, LOWER_STATUS_LINE, temp);
	}
	else {
		sprintf(temp, "[当前光标] %d行%d列",nrow,ncol);
		gmw_status_line(pCGI, LOWER_STATUS_LINE, temp);
	}

	return 0;
}
static int gmw_inner_tran(const CONSOLE_GRAPHICS_INFO* const pCGI,int& nrow, int& ncol, int x, int y)
{
	if (x > pCGI->frametop_x + 1 && x<pCGI->frametop_x + pCGI->col_num * pCGI->CFI.bwidth + 2 - pCGI->CFI.separator * 2
		&& y>pCGI->frametop_y && y < pCGI->framelower_y) {
		if (pCGI->CFI.separator) {
			if ((y - pCGI->frametop_y) % (pCGI->CFI.bhigh) != 0&&((x-pCGI->frametop_x)%(pCGI->CFI.bwidth)!=0&&(x-pCGI->frametop_x-1)% (pCGI->CFI.bwidth) != 0) ){//不在分割线上
				nrow = ((y - pCGI->frametop_y) - 1) / (pCGI->CFI.block_high + 1);
				ncol = ((x - pCGI->frametop_x) - 2) / (pCGI->CFI.block_width + 2);

			}
			else {//在分割线上
				return -1;//位置非法
			}

		}
		else {
			nrow = ((y - pCGI->frametop_y) - 1) / (pCGI->CFI.block_high );
			ncol = ((x - pCGI->frametop_x) - 2) / (pCGI->CFI.block_width);

			
		}
	}
	else
		return -1;//在游戏区域外,位置非法

	return 0;
		
}
static int gmw_inner_drawno(const CONSOLE_GRAPHICS_INFO* const pCGI)
{
	

	if (pCGI->draw_frame_with_col_no) {
		int x = pCGI->frametop_x+pCGI->CFI.block_width/2+1, y = pCGI->frametop_y - 1;//起始位置
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
		int x = pCGI->frametop_x -2, y = pCGI->frametop_y + (pCGI->CFI.block_high+1) / 2;//起始位置
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
		strncpy(dst, "  ", n); // 用两个空格替代NULL
		return 0;
	}

	int len = strlen(src);
	if (len > 2) {
		strncpy(dst, src, 2); // 只取前2字节
	}
	else {
		strncpy(dst, src, len); // 复制实际长度
		if (len == 1) {
			dst[1] = ' '; // 如果是1字节，补一个空格
		}
	}
	dst[2] = '\0'; // 确保字符串以'\0'结束
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
		colno = 1;//多出一行
	if (pCGI->draw_frame_with_row_no)
		rowno = 2;//多出两列
	if (pCGI->CFI.separator) {
		rowsepar = 1;
		colsepar = 2;
	}
		
	
	pCGI->start_x = pCGI->extern_left_cols;//列数
	pCGI->start_y = pCGI->extern_up_lines; //行数

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
		实现下面给出的函数（函数声明不准动）
   ----------------------------------------------- */
/***************************************************************************
  函数名称：
  功    能：设置游戏主框架的行列数
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int row						：行数(错误则为0，不设上限，人为保证正确性)
			const int col						：列数(错误则为0，不设上限，人为保证正确性)
  返 回 值：
  说    明：1、指消除类游戏的矩形区域的行列值
            2、行列的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int gmw_set_rowcol(CONSOLE_GRAPHICS_INFO *const pCGI, const int row, const int col)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (row < 0)
		pCGI->row_num = 0;
	if (col < 0)
		pCGI->col_num = 0;
	pCGI->col_num = col;
	pCGI->row_num = row;
	//影响窗口大小与起始坐标
	gmw_inner_cal(pCGI);


	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置整个窗口（含游戏区、附加区在内的整个cmd窗口）的颜色
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const int bg_color					：前景色（缺省COLOR_BLACK）
		   const int fg_color					：背景色（缺省COLOR_WHITE）
		   const bool cascade					：是否级联（缺省为true-级联）
  返 回 值：
  说    明：1、cascade = true时
				同步修改游戏主区域的颜色
				同步修改上下状态栏的正常文本的背景色和前景色，醒目文本的背景色（前景色不变）
			2、不检查颜色值错误及冲突，需要人为保证
				例：颜色非0-15
				    前景色背景色的值一致导致无法看到内容
					前景色正好是状态栏醒目前景色，导致无法看到醒目提示
					...
***************************************************************************/
int gmw_set_color(CONSOLE_GRAPHICS_INFO *const pCGI, const int bgcolor, const int fgcolor, const bool cascade)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;

	pCGI->area_bgcolor = bgcolor;
	pCGI->area_fgcolor = fgcolor;
	//cct_setcolor(bgcolor, fgcolor);//设置窗口颜色

	if (cascade) {
		gmw_set_frame_color(pCGI);//游戏主区域
		//上状态栏
		gmw_set_status_line_color(pCGI, TOP_STATUS_LINE,-1,-1,-1,pCGI->SLI.top_catchy_fgcolor);
		//下状态栏
		gmw_set_status_line_color(pCGI, LOWER_STATUS_LINE, -1, -1, -1, pCGI->SLI.top_catchy_fgcolor);
	}
	
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置窗口的字体
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const char *fontname					：字体名称（只能是"Terminal"和"新宋体"两种，错误则返回-1，不改变字体）
		   const int fs_high					：字体高度（缺省及错误为16，不设其它限制，人为保证）
		   const int fs_width					：字体高度（缺省及错误为8，不设其它限制，人为保证）
  返 回 值：
  说    明：1、与cmd_console_tools中的setfontsize相似，目前只支持“点阵字体”和“新宋体”
            2、若设置其它字体则直接返回，保持原字体设置不变
***************************************************************************/
int gmw_set_font(CONSOLE_GRAPHICS_INFO *const pCGI, const char *fontname, const int fs_high, const int fs_width)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;

	if (fontname != "Terminal" && fontname != "新宋体")
		return -1;

	
	strncpy(pCGI->CFT.font_type, fontname, FONTNAME_LEN);

	pCGI->CFT.font_size_high = fs_high;
	pCGI->CFT.font_size_width = fs_width;
	if (fontname != "Terminal")
		pCGI->CFT.font_size_width = 0;
	

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置延时
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const int type						：延时的类型（目前为3种）
		   const int delay_ms					：以ms为单位的延时
			   画边框的延时：0 ~ 不设上限，人为保证正确（<0则置0）
			   画色块的延时：0 ~ 不设上限，人为保证正确（<0则置0）
			   色块移动的延时：BLOCK_MOVED_DELAY_MS ~ 不设上限，人为保证正确（ <BLOCK_MOVED_DELAY_MS 则置 BLOCK_MOVED_DELAY_MS）
  返 回 值：
  说    明：
***************************************************************************/
int gmw_set_delay(CONSOLE_GRAPHICS_INFO *const pCGI, const int type, const int delay_ms)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	//延时设置
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

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  输入参数：设置游戏主框架结构之外需要保留的额外区域
  功    能：CONSOLE_GRAPHICS_INFO *const pCGI	：
		   const int up_lines					：上部额外的行（缺省及错误为0，不设上限，人为保证）
		   const int down_lines				：下部额外的行（缺省及错误为0，不设上限，人为保证）
		   const int left_cols					：左边额外的列（缺省及错误为0，不设上限，人为保证）
		   const int right_cols				：右边额外的列（缺省及错误为0，不设上限，人为保证）
  返 回 值：
  说    明：额外行列的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int gmw_set_ext_rowcol(CONSOLE_GRAPHICS_INFO *const pCGI, const int up_lines, const int down_lines, const int left_cols, const int right_cols)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	//上下左右无额外行列
	pCGI->extern_down_lines = down_lines;
	pCGI->extern_up_lines = up_lines;
	pCGI->extern_right_cols = right_cols;
	pCGI->extern_left_cols = left_cols;
	//影响窗口大小与起始坐标
	gmw_inner_cal(pCGI);


	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_FRAME_TYPE 结构中的11种线型（缺省4种）
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int type						：1 - 全线 2 - 全单线 3 - 横双竖单 4 - 横单竖双
  返 回 值：
  说    明：
***************************************************************************/
int gmw_set_frame_default_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const int type)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (type == 1) {//双线
		strncpy(pCGI->CFI.top_left, "╔", CFI_LEN);
		strncpy(pCGI->CFI.lower_left, "╚", CFI_LEN);
		strncpy(pCGI->CFI.top_right, "╗", CFI_LEN);
		strncpy(pCGI->CFI.lower_right, "╝", CFI_LEN);
		strncpy(pCGI->CFI.h_normal, "═", CFI_LEN);
		strncpy(pCGI->CFI.v_normal, "║", CFI_LEN);
		strncpy(pCGI->CFI.h_top_separator, "╦", CFI_LEN);
		strncpy(pCGI->CFI.h_lower_separator, "╩", CFI_LEN);
		strncpy(pCGI->CFI.v_left_separator, "╠", CFI_LEN);
		strncpy(pCGI->CFI.v_right_separator, "╣", CFI_LEN);
		strncpy(pCGI->CFI.mid_separator, "╬", CFI_LEN);
	}
	if (type == 2) {//单线
		strncpy(pCGI->CFI.top_left, "┏", CFI_LEN);
		strncpy(pCGI->CFI.lower_left, "┗", CFI_LEN);
		strncpy(pCGI->CFI.top_right, "┓", CFI_LEN);
		strncpy(pCGI->CFI.lower_right, "┛", CFI_LEN);
		strncpy(pCGI->CFI.h_normal, "━", CFI_LEN);
		strncpy(pCGI->CFI.v_normal, "┃", CFI_LEN);
		strncpy(pCGI->CFI.h_top_separator, "┳", CFI_LEN);
		strncpy(pCGI->CFI.h_lower_separator, "┻", CFI_LEN);
		strncpy(pCGI->CFI.v_left_separator, "┣", CFI_LEN);
		strncpy(pCGI->CFI.v_right_separator, "┫", CFI_LEN);
		strncpy(pCGI->CFI.mid_separator, "╋", CFI_LEN);
	}
	if (type == 3) {//横双竖单
		strncpy(pCGI->CFI.top_left, "╒", CFI_LEN);
		strncpy(pCGI->CFI.lower_left, "╘", CFI_LEN);
		strncpy(pCGI->CFI.top_right, "╕", CFI_LEN);
		strncpy(pCGI->CFI.lower_right, "╛", CFI_LEN);
		strncpy(pCGI->CFI.h_normal, "═", CFI_LEN);
		strncpy(pCGI->CFI.v_normal, "┃", CFI_LEN);
		strncpy(pCGI->CFI.h_top_separator, "╤", CFI_LEN);
		strncpy(pCGI->CFI.h_lower_separator, "╧", CFI_LEN);
		strncpy(pCGI->CFI.v_left_separator, "╞", CFI_LEN);
		strncpy(pCGI->CFI.v_right_separator, "╡", CFI_LEN);
		strncpy(pCGI->CFI.mid_separator, "╪", CFI_LEN);
	}
	if (type == 4) {//横单竖双
		strncpy(pCGI->CFI.top_left, "╓", CFI_LEN);
		strncpy(pCGI->CFI.lower_left, "╙", CFI_LEN);
		strncpy(pCGI->CFI.top_right, "╖", CFI_LEN);
		strncpy(pCGI->CFI.lower_right, "╜", CFI_LEN);
		strncpy(pCGI->CFI.h_normal, "━", CFI_LEN);
		strncpy(pCGI->CFI.v_normal, "║", CFI_LEN);
		strncpy(pCGI->CFI.h_top_separator, "╥", CFI_LEN);
		strncpy(pCGI->CFI.h_lower_separator, "╨", CFI_LEN);
		strncpy(pCGI->CFI.v_left_separator, "╟", CFI_LEN);
		strncpy(pCGI->CFI.v_right_separator, "╢", CFI_LEN);
		strncpy(pCGI->CFI.mid_separator, "╫", CFI_LEN);
	}
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_FRAME_TYPE 结构中的11种线型
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const char *...						：共11种，具体见.h，此处略
  返 回 值：
  说    明：约定为一个中文制表符，可以使用其它内容，人为保证2字节
			1、超过2字节则只取前2字节
			2、如果给NULL，用两个空格替代
			3、如果给1字节，则补一个空格，如果因此而导致显示乱，不算错
***************************************************************************/
int gmw_set_frame_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const char *top_left, const char *lower_left, const char *top_right,
	const char *lower_right, const char *h_normal, const char *v_normal, const char *h_top_separator,
	const char *h_lower_separator, const char *v_left_separator, const char *v_right_separator, const char *mid_separator)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
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


	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_FRAME_TYPE 结构中的色块数量大小、是否需要分隔线等
  输入参数：输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int block_width						：宽度（错误及缺省2，因为约定表格线为中文制表符，如果给出奇数，要+1）
			const int block_high						：高度（错误及缺省1）
			const bool separator						：是否需要分隔线（缺省为true，需要分隔线）
  返 回 值：
  说    明：框架大小/是否需要分隔线等的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int gmw_set_frame_style(CONSOLE_GRAPHICS_INFO *const pCGI, const int block_width, const int block_high, const bool separator)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	
	pCGI->CFI.block_width = block_width+block_width%2;
	pCGI->CFI.block_high = block_high;
	//无分隔线
	pCGI->CFI.separator = separator;

	//影响窗口大小和起始坐标
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


	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_BORDER_TYPE 结构中的颜色
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int bg_color					：背景色（缺省 -1表示用窗口背景色）
			const int fg_color					：前景色（缺省 -1表示用窗口前景色）
  返 回 值：
  说    明：不检查颜色值错误及冲突，需要人为保证
				例：颜色非0-15，前景色背景色的值一致导致无法看到内容等
***************************************************************************/
int gmw_set_frame_color(CONSOLE_GRAPHICS_INFO *const pCGI, const int bgcolor, const int fgcolor)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
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
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_BLOCK_INFO 结构中的6种线型（缺省4种）
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int type						：1 - 全双线 2 - 全单线 3 - 横双竖单 4 - 横单竖双
  返 回 值：
  说    明：
***************************************************************************/
int gmw_set_block_default_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const int type)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (type == 1) {//双线
		strncpy(pCGI->CBI.top_left, "╔", CFI_LEN);
		strncpy(pCGI->CBI.lower_left, "╚", CFI_LEN);
		strncpy(pCGI->CBI.top_right, "╗", CFI_LEN);
		strncpy(pCGI->CBI.lower_right, "╝", CFI_LEN);
		strncpy(pCGI->CBI.h_normal, "═", CFI_LEN);
		strncpy(pCGI->CBI.v_normal, "║", CFI_LEN);
		
	}
	if (type == 2) {//单线
		strncpy(pCGI->CBI.top_left, "┏", CFI_LEN);
		strncpy(pCGI->CBI.lower_left, "┗", CFI_LEN);
		strncpy(pCGI->CBI.top_right, "┓", CFI_LEN);
		strncpy(pCGI->CBI.lower_right, "┛", CFI_LEN);
		strncpy(pCGI->CBI.h_normal, "━", CFI_LEN);
		strncpy(pCGI->CBI.v_normal, "┃", CFI_LEN);
		
	}
	if (type == 3) {//横双竖单
		strncpy(pCGI->CBI.top_left, "╒", CFI_LEN);
		strncpy(pCGI->CBI.lower_left, "╘", CFI_LEN);
		strncpy(pCGI->CBI.top_right, "╕", CFI_LEN);
		strncpy(pCGI->CBI.lower_right, "╛", CFI_LEN);
		strncpy(pCGI->CBI.h_normal, "═", CFI_LEN);
		strncpy(pCGI->CBI.v_normal, "┃", CFI_LEN);
	
	}
	if (type == 4) {//横单竖双
		strncpy(pCGI->CBI.top_left, "╓", CFI_LEN);
		strncpy(pCGI->CBI.lower_left, "╙", CFI_LEN);
		strncpy(pCGI->CBI.top_right, "╖", CFI_LEN);
		strncpy(pCGI->CBI.lower_right, "╜", CFI_LEN);
		strncpy(pCGI->CBI.h_normal, "━", CFI_LEN);
		strncpy(pCGI->CBI.v_normal, "║", CFI_LEN);
		
	}
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_BLOCK_INFO 结构中的6种线型
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const char *...					：共6种，具体见.h，此处略
  返 回 值：
  说    明：约定为一个中文制表符，可以使用其它内容，人为保证2字节
			1、超过2字节则只取前2字节
			2、如果给NULL，用两个空格替代
			3、如果给1字节，则补一个空格，如果因此而导致显示乱，不算错
***************************************************************************/
int gmw_set_block_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const char *top_left, const char *lower_left, const char *top_right, const char *lower_right, const char *h_normal, const char *v_normal)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;

	gmw_inner_safecpy(pCGI->CBI.top_left, top_left, CFI_LEN);
	gmw_inner_safecpy(pCGI->CBI.lower_left, lower_left, CFI_LEN);
	gmw_inner_safecpy(pCGI->CBI.top_right, top_right, CFI_LEN);
	gmw_inner_safecpy(pCGI->CBI.lower_right, lower_right, CFI_LEN);
	gmw_inner_safecpy(pCGI->CBI.h_normal, h_normal, CFI_LEN);
	gmw_inner_safecpy(pCGI->CBI.v_normal, v_normal, CFI_LEN);


	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置每个游戏色块(彩球)是否需要小边框
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const bool on_off					：true - 需要 flase - 不需要（缺省false）
  返 回 值：
  说    明：边框约定为中文制表符，双线
***************************************************************************/
int gmw_set_block_border_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const bool on_off)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	//是否需要小边框
	pCGI->CBI.block_border = on_off;
	

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置是否显示上下状态栏
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int type						：状态栏类型（上/下）
			const bool on_off					：true - 需要 flase - 不需要（缺省true）
  返 回 值：
  说    明：1、状态栏的相关约定如下：
			   1.1、上状态栏只能一行，在主区域最上方框线/列标的上面，为主区域的最开始一行（主区域的左上角坐标就是上状态栏的坐标）
			   1.2、下状态栏只能一行，在主区域最下方框线的下面
			   1.3、状态栏的宽度为主区域宽度，如果信息过长则截断
		   2、行列的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int gmw_set_status_line_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const int type, const bool on_off)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
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
	//改变窗口大小和起始坐标
	gmw_inner_cal(pCGI);



	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置上下状态栏的颜色
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int type						：状态栏类型（上/下）
			const int normal_bgcolor			：正常文本背景色（缺省 -1表示使用窗口背景色）
			const int normal_fgcolor			：正常文本前景色（缺省 -1表示使用窗口前景色）
			const int catchy_bgcolor			：醒目文本背景色（缺省 -1表示使用窗口背景色）
			const int catchy_fgcolor			：醒目文本前景色（缺省 -1表示使用亮黄色）
  输入参数：
  返 回 值：
  说    明：不检查颜色值错误及冲突，需要人为保证
				例：颜色非0-15，前景色背景色的值一致导致无法看到内容等
***************************************************************************/
int gmw_set_status_line_color(CONSOLE_GRAPHICS_INFO *const pCGI, const int type, const int normal_bgcolor, const int normal_fgcolor, const int catchy_bgcolor, const int catchy_fgcolor)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
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



	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置是否显示行号
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const bool on_off					：true - 显示 flase - 不显示（缺省false）
  返 回 值：
  说    明：1、行号约定为字母A开始连续排列（如果超过26，则从a开始，超过52的统一为*，实际应用不可能）
            2、是否显示行号的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int gmw_set_rowno_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const bool on_off)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->draw_frame_with_row_no = on_off;
	//改变窗口大小和起始地址
	gmw_inner_cal(pCGI);

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置是否显示列标
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const bool on_off					：true - 显示 flase - 不显示（缺省false）
  返 回 值：
  说    明：1、列标约定为数字0开始连续排列（数字0-99，超过99统一为**，实际应用不可能）
            2、是否显示列标的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int gmw_set_colno_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const bool on_off)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->draw_frame_with_col_no = on_off;
	//改变窗口大小和起始地址
	gmw_inner_cal(pCGI);

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：打印 CONSOLE_GRAPHICS_INFO 结构体中的各成员值
  输入参数：
  返 回 值：
  说    明：1、仅供调试用，打印格式自定义
            2、本函数测试用例中未调用过，可以不实现
***************************************************************************/
int gmw_print(const CONSOLE_GRAPHICS_INFO *const pCGI)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;



	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：将 CONSOLE_GRAPHICS_INFO 结构体用缺省值进行初始化
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI：整体结构指针
		   const int row					：游戏区域色块行数（缺省10）
		   const int col					：游戏区域色块列数（缺省10）
		   const int bgcolor				：整个窗口背景色（缺省 COLOR_BLACK）
		   const int fgcolor				：整个窗口背景色（缺省 COLOR_WHITE）
  返 回 值：
  说    明：窗口背景黑/前景白，点阵16*8，上下左右无额外行列，上下状态栏均有，无行号/列标，框架线型为双线，色块宽度2/高度1/无小边框，颜色略
***************************************************************************/
int gmw_init(CONSOLE_GRAPHICS_INFO *const pCGI, const int row, const int col, const int bgcolor, const int fgcolor)
{
	/* 首先置标记 */
	pCGI->inited = CGI_INITED;
	
	//带分隔线,色块宽2高1
	gmw_set_frame_style(pCGI);
	//整个窗口颜色设置ok，游戏区域，状态栏
	gmw_set_color(pCGI,bgcolor,fgcolor);
	
	//延时设置
	gmw_set_delay(pCGI, DELAY_OF_BLOCK_MOVED, 15);
	gmw_set_delay(pCGI, DELAY_OF_DRAW_BLOCK, 0);
	gmw_set_delay(pCGI, DELAY_OF_DRAW_FRAME, 0);

	//主区与行列数
	gmw_set_rowcol(pCGI, row,col);
	
	//字体设置
	gmw_set_font(pCGI,"新宋体");

	//上下左右无额外行列
	gmw_set_ext_rowcol(pCGI);

	//上下状态栏均有
	gmw_set_status_line_switch(pCGI, TOP_STATUS_LINE);
	gmw_set_status_line_switch(pCGI, LOWER_STATUS_LINE);
	//下状态栏颜色
	gmw_set_status_line_color(pCGI, LOWER_STATUS_LINE);
	//上状态栏颜色
	gmw_set_status_line_color(pCGI, TOP_STATUS_LINE);
	//无行号/列标
	gmw_set_colno_switch(pCGI);
	gmw_set_rowno_switch(pCGI);
	//框架线型
	gmw_set_frame_default_linetype(pCGI, 1);
	
	//色块无小边框
	gmw_set_block_border_switch(pCGI);
	

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：画主游戏框架
  输入参数：const CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
  返 回 值：
  说    明：具体可参考demo的效果
***************************************************************************/
int gmw_draw_frame(const CONSOLE_GRAPHICS_INFO *const pCGI)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	int x, y;
	//先进行窗口设置
	cct_setcolor(pCGI->area_bgcolor, pCGI->area_fgcolor);
	
	cct_setfontsize(pCGI->CFT.font_type,pCGI->CFT.font_size_high, pCGI->CFT.font_size_width);
	cct_setconsoleborder(pCGI->cols, pCGI->lines);
	cct_setcolor();//恢复缺省颜色
	
	//延时设置
	Sleep(pCGI->delay_of_draw_frame);

	//第一行边框
	cct_gotoxy(pCGI->frametop_x, pCGI->frametop_y);
	//左上角
	cct_showstr(pCGI->frametop_x, pCGI->frametop_y, pCGI->CFI.top_left, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
	for (int j = 0; j <pCGI->col_num; j++) {
		Sleep(pCGI->delay_of_draw_frame);
		for (int i = 0; i < pCGI->CFI.block_width/ 2; i++) {
			cct_getxy(x, y);
			cct_showstr(x, y, pCGI->CFI.h_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
		}
		//有分割线
		if (pCGI->CFI.separator&& j != pCGI->col_num - 1) {
				cct_getxy(x, y);
				cct_showstr(x, y, pCGI->CFI.h_top_separator, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
			
		}
		

	}
    cct_getxy(x, y);
    cct_showstr(x, y, pCGI->CFI.top_right, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
	
	//中间几行
	for (int k = 0; k < pCGI->row_num-1; k++) {
		x = pCGI->frametop_x;
		for (int i = 0; i < pCGI->CFI.block_high; i++) {
			x = pCGI->frametop_x,y++;
			cct_showstr(x, y, pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
			cct_getxy(x, y);
			if (pCGI->CFI.separator) {
				for (int j = 0; j < pCGI->col_num - 1; j++) {//除掉最边上两个
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
   //最后一行

	for (int i = 0; i < pCGI->CFI.block_high; i++) {
		x = pCGI->frametop_x,y++;
		cct_showstr(x, y, pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
		cct_getxy(x, y);
		if (pCGI->CFI.separator) {
			for (int j = 0; j < pCGI->col_num - 1; j++) {//除掉最边上两个
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
	//左下角
	cct_showstr(x, y, pCGI->CFI.lower_left, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
	for (int j = 0; j < pCGI->col_num; j++) {
		Sleep(pCGI->delay_of_draw_frame);
		for (int i = 0; i < pCGI->CFI.block_width / 2; i++) {
			cct_getxy(x, y);
			cct_showstr(x, y, pCGI->CFI.h_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
		}
		//有分割线
		if (pCGI->CFI.separator && j != pCGI->col_num - 1) {
			cct_getxy(x, y);
			cct_showstr(x, y, pCGI->CFI.h_lower_separator, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);

		}


	}
	cct_getxy(x, y);
	cct_showstr(x, y, pCGI->CFI.lower_right, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
	

//行列标
	gmw_inner_drawno(pCGI);
	


	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：在状态栏上显示信息
  输入参数：const CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const int type							：指定是上/下状态栏
		   const char *msg						：正常信息
		   const char *catchy_msg					：需要特别标注的信息（在正常信息前显示）
  返 回 值：
  说    明：1、输出宽度限定为主框架的宽度（含行号列标位置），超出则截去
			2、如果最后一个字符是某汉字的前半个，会导致后面乱码，要处理
***************************************************************************/
int gmw_status_line(const CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const char* msg, const char* catchy_msg)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	int x, y;


	int len1 = catchy_msg ? strlen(catchy_msg) : 0;
	int len2 = msg ? strlen(msg) : 0;

	int min1 = min(len1, pCGI->SLI.width);
	int min2 = min(len2, pCGI->SLI.width);
	if (type == TOP_STATUS_LINE) {//就是起始地址
		if (!pCGI->SLI.is_top_status_line)
			return -1;
		x = pCGI->SLI.top_start_x, y = pCGI->SLI.top_start_y;


		for (int i = 0; i < min1; i++) {
			if (i == min1 - 1)
				if (catchy_msg[i] >= 0xA1 && catchy_msg[i] <= 0xFE)
					break;

			cct_showch(x, y, catchy_msg[i], pCGI->SLI.top_catchy_bgcolor, pCGI->SLI.top_catchy_fgcolor);
			cct_getxy(x, y);//更新坐标

		}

		for (int i = 0; i < min2; i++) {
			if (i == min2 - 1)
				if (msg[i] >= 0xA1 && msg[i] <= 0xFE)
					break;

			cct_showch(x, y, msg[i], pCGI->SLI.top_normal_bgcolor, pCGI->SLI.top_normal_fgcolor);
			cct_getxy(x, y);//更新坐标

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
			cct_getxy(x, y);//更新坐标

		}
		for (int i = 0; i < min2; i++) {
			if (i == min2 - 1)
				if (msg[i] >= 0xA1 && msg[i] <= 0xFE)
					break;
			if(i==0)
				cct_showstr(x, y, "                                      ", pCGI->SLI.lower_normal_bgcolor, pCGI->SLI.lower_normal_fgcolor);

			cct_showch(x, y, msg[i], pCGI->SLI.lower_normal_bgcolor, pCGI->SLI.lower_normal_fgcolor);
			cct_getxy(x, y);//更新坐标

		}
	}


	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：显示某一个色块(内容为字符串，坐标为row/col)
  输入参数：const CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const int row_no						：行号（从0开始，人为保证正确性，程序不检查）
		   const int col_no						：列号（从0开始，人为保证正确性，程序不检查）
		   const int bdi_value						：需要显示的值
		   const BLOCK_DISPLAY_INFO *const bdi		：存放该值对应的显示信息的结构体数组
  返 回 值：
  说    明：1、BLOCK_DISPLAY_INFO 的含义见头文件，用法参考测试样例
			2、bdi_value为 BDI_VALUE_BLANK 表示空白块，要特殊处理
***************************************************************************/
int gmw_draw_block(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, const int bdi_value, const BLOCK_DISPLAY_INFO* const bdi)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	int num = 0, i = 0;
	while (bdi[i].value != BDI_VALUE_END) {
		if (bdi[i].value == bdi_value) {
			num = i;
			break;
		}
		i++;  // 移动到下一个元素
	}



	//起始位置
	int bgcolor = (bdi[num].bgcolor == -1) ? pCGI->CFI.bgcolor : bdi[num].bgcolor;
	int fgcolor = (bdi[num].fgcolor == -1) ? pCGI->CFI.fgcolor : bdi[num].fgcolor;
	int x = pCGI->frametop_x + 2 + col_no * pCGI->CFI.bwidth, y = pCGI->frametop_y + 1 + row_no * pCGI->CFI.bhigh;

	//当content为NULL 特殊处理预先
	int length = snprintf(NULL, 0, "%d", bdi[num].value); // 获取所需长度
	char* str = new char[length + 1]; // 动态分配内存，包括结束符
	// 将整数转换为字符串
	snprintf(str, length + 1, "%d", bdi[num].value);

	//延时
	Sleep(pCGI->delay_of_draw_block);
	
	//左上角
	if (pCGI->CBI.block_border&& bdi[num].value!=BDI_VALUE_BLANK)
		cct_showstr(x, y, "╔", bgcolor, fgcolor);
	else
		cct_showstr(x, y, "  ", bgcolor, fgcolor);
	//第一行中间
	
	for (int i = 0; i < (pCGI->CFI.block_width - 4) / 2; i++) {//横线部分
		cct_getxy(x, y);//更新坐标
		if (pCGI->CBI.block_border&& bdi[num].value != BDI_VALUE_BLANK)
			cct_showstr(x, y, "═", bgcolor, fgcolor);
		else
			cct_showstr(x, y, "  ", bgcolor, fgcolor);
	}
	//右上角
	
	x = pCGI->frametop_x + 2 + col_no * pCGI->CFI.bwidth + (pCGI->CFI.block_width - 2);
	if (pCGI->CBI.block_border && bdi[num].value != BDI_VALUE_BLANK)
		cct_showstr(x, y, "╗", bgcolor, fgcolor);
	else
		cct_showstr(x, y, "  ", bgcolor, fgcolor);
	//中间
	
	for (int j = 0; j < (pCGI->CFI.block_high - 2); j++) {
		x = pCGI->frametop_x + 2 + col_no * pCGI->CFI.bwidth;
		y++;
		if (pCGI->CBI.block_border && bdi[num].value != BDI_VALUE_BLANK)
			cct_showstr(x, y, "║", bgcolor, fgcolor);
		else
			cct_showstr(x, y, "  ", bgcolor, fgcolor);

		//显示图案
		if (bdi[num].content != NULL||bdi[num].value==BDI_VALUE_BLANK) {
			for (int i = 0; i < (pCGI->CFI.block_width - 4) / 2; i++) {//横线部分
				cct_getxy(x, y);//更新坐标
				if (x == pCGI->frametop_x + 1 + col_no * pCGI->CFI.bwidth + pCGI->CFI.block_width / 2
					&& y == pCGI->frametop_y + row_no * pCGI->CFI.bhigh + (pCGI->CFI.block_high + 1) / 2 && bdi[num].value != BDI_VALUE_BLANK) {

					cct_showstr(x, y, bdi[num].content, bgcolor, fgcolor);

				}

				else
					cct_showstr(x, y, "  ", bgcolor, fgcolor);
			}
		}
		//显示数字
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

				}//保证填满

			}
			else {
				for (int i = 0; i < (pCGI->CFI.block_width - 4) / 2; i++) {
					cct_getxy(x, y);
					cct_showstr(x, y, "  ", bgcolor, fgcolor);
				}
			}
		 
		}
		//最右
		x = pCGI->frametop_x + 2 + col_no * pCGI->CFI.bwidth+(pCGI->CFI.block_width-2);
		if (pCGI->CBI.block_border && bdi[num].value != BDI_VALUE_BLANK)
			cct_showstr(x, y, "║", bgcolor, fgcolor);
		else
			cct_showstr(x, y, "  ", bgcolor, fgcolor);
	}
	//最后
	x = pCGI->frametop_x + 2 + col_no * pCGI->CFI.bwidth;
	y = pCGI->frametop_y + row_no * pCGI->CFI.bhigh + pCGI->CFI.block_high;
	if (pCGI->CBI.block_border && bdi[num].value != BDI_VALUE_BLANK)
		cct_showstr(x, y, "╚", bgcolor, fgcolor);
	else
		cct_showstr(x, y, "  ", bgcolor, fgcolor);

	for (int i = 0; i < (pCGI->CFI.block_width - 4) / 2; i++) {//横线部分
		cct_getxy(x, y);//更新坐标
		if (pCGI->CBI.block_border && bdi[num].value != BDI_VALUE_BLANK)
			cct_showstr(x, y, "═", bgcolor, fgcolor);
		else
			cct_showstr(x, y, "  ", bgcolor, fgcolor);
	}

	x = pCGI->frametop_x + 2 + col_no * pCGI->CFI.bwidth + (pCGI->CFI.block_width - 2);
	if (pCGI->CBI.block_border && bdi[num].value != BDI_VALUE_BLANK)
		cct_showstr(x, y, "╝", bgcolor, fgcolor);
	else
		cct_showstr(x, y, "  ", bgcolor, fgcolor);

	//为防止图案被覆盖
		x = pCGI->frametop_x + 1 + col_no * pCGI->CFI.bwidth + pCGI->CFI.block_width / 2;
		y = pCGI->frametop_y + row_no * pCGI->CFI.bhigh + (pCGI->CFI.block_high + 1) / 2;

		if (bdi[num].content != NULL)
			cct_showstr(x, y, bdi[num].content, bgcolor, fgcolor);
		
		
	
	delete[] str;
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：移动某一个色块
  输入参数：const CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const int row_no						：行号（从0开始，人为保证正确性，程序不检查）
		   const int col_no						：列号（从0开始，人为保证正确性，程序不检查）
		   const int bdi_value						：需要显示的值
		   const int blank_bdi_value				：移动过程中用于动画效果显示时用于表示空白的值（一般为0，此处做为参数代入，是考虑到可能出现的特殊情况）
		   const BLOCK_DISPLAY_INFO *const bdi		：存放显示值/空白值对应的显示信息的结构体数组
		   const int direction						：移动方向，一共四种，具体见cmd_gmw_tools.h
		   const int distance						：移动距离（从1开始，人为保证正确性，程序不检查）
  返 回 值：
  说    明：
***************************************************************************/
int gmw_move_block(const CONSOLE_GRAPHICS_INFO *const pCGI, const int row_no, const int col_no, const int bdi_value, const int blank_bdi_value, const BLOCK_DISPLAY_INFO *const bdi, const int direction, const int distance)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	int x, y;//当前坐标
	//定位初始左上角
	int X = col_no * (pCGI->CFI.bwidth) + pCGI->frametop_x + 2;
	int Y = row_no * (pCGI->CFI.bhigh) + pCGI->frametop_y + 1;
	
	
	if (direction == UP_TO_DOWN) {
		for (int k = 0; k < distance * pCGI->CFI.bhigh; k++) {
			Sleep(pCGI->delay_of_block_moved);

			for (int i = 0; i < pCGI->CFI.block_width / 2; i++) {
				y = Y+k;//色块的第k层
				x = X+2*i;//色块左上角
				
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
				y = Y+pCGI->CFI.block_high-1 - k;//色块的第k层
				x = X + 2 * i;//色块左下角

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
				x = X+k*2 ;//色块左上角

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
				x = X+pCGI->CFI.block_width-2 - k * 2;//右上角

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


	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：读键盘或鼠标
  输入参数：const CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   int &MAction							：如果返回 CCT_MOUSE_EVENT，则此值有效，为 MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK/MOUSE_RIGHT_BUTTON_CLICK 三者之一
		                                               如果返回 CCT_KEYBOARD_EVENT，则此值无效
		   int &MRow								：如果返回 CCT_MOUSE_EVENT 且 MAction = MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK，则此值有效，表示左键选择的游戏区域的行号（从0开始）
												  其余情况此值无效（如果访问无效值导致错误，不是本函数的错!!!）
		   int &MCol								：如果返回 CCT_MOUSE_EVENT 且 MAction = MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK，则此值有效，表示左键选择的游戏区域的列号（从0开始）
												  其余情况此值无效（如果访问无效值导致错误，不是本函数的错!!!）
		   int &KeyCode1							：如果返回 CCT_KEYBOARD_EVENT，则此值有效，为读到的键码（如果双键码，则为第一个）
												  其余情况此值无效（如果访问无效值导致错误，不是本函数的错!!!）
		   int &KeyCode2							：如果返回 CCT_KEYBOARD_EVENT，则此值有效，为读到的键码（如果双键码，则为第二个，如果是单键码，则为0）
												  其余情况此值无效（如果访问无效值导致错误，不是本函数的错!!!）
		   const bool update_lower_status_line		：鼠标移动时，是否要在本函数中显示"[当前光标] *行*列/位置非法"的信息（true=显示，false=不显示，缺省为true）
  返 回 值：函数返回约定
		   1、如果是鼠标移动，得到的MRow/MCol与传入的相同(鼠标指针微小的移动)，则不返回，继续读
							  得到行列非法位置，则不返回，根据 update_lower_status_line 的设置在下状态栏显示"[当前光标] 位置非法"
							  得到的MRow/MCol与传入的不同(行列至少一个变化)，根据 update_lower_status_line 的设置在下状态栏显示"[当前光标] *行*列"，再返回MOUSE_ONLY_MOVED（有些游戏返回后要处理色块的不同颜色显示）
		   2、如果是按下鼠标左键，且当前鼠标指针停留在主游戏区域的*行*列上，则返回 CCT_MOUSE_EVENT ，MAction 为 MOUSE_LEFT_BUTTON_CLICK, MRow 为行号，MCol 为列标
		                          且当前鼠标指针停留在非法区域（非游戏区域，游戏区域中的分隔线），则不返回，根据 update_lower_status_line 的设置在下状态栏显示"[当前光标] 位置非法"
		   3、如果是按下鼠标右键，则不判断鼠标指针停留区域是否合法，直接返回 CCT_MOUSE_EVENT ，MAction 为 MOUSE_RIGHT_BUTTON_CLICK, MRow、MCol取当前值（因为消灭星星的右键标记需要坐标）
		   4、如果按下键盘上的某键（含双键码按键），则直接返回 CCT_KEYBOARD_EVENT，KeyCode1/KeyCode2中为对应的键码值
 说    明：通过调用 cmd_console_tools.cpp 中的 read_keyboard_and_mouse 函数实现
***************************************************************************/
int gmw_read_keyboard_and_mouse(const CONSOLE_GRAPHICS_INFO *const pCGI, int &MAction, int &MRow, int &MCol, int &KeyCode1, int &KeyCode2, const bool update_lower_status_line)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	int X, Y;
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;
	int nrow, ncol;
	int rett;

	cct_enable_mouse();
	cct_setcursor(CURSOR_INVISIBLE);	//关闭光标
	while (loop) {
		ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

		

		if (ret == CCT_MOUSE_EVENT) {
			rett = gmw_inner_tran(pCGI, nrow, ncol, X, Y);//得到行号列标

			if (maction == MOUSE_ONLY_MOVED) {//移动
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
			else if (maction == MOUSE_LEFT_BUTTON_CLICK) {//左键
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
			else {//右键

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
	return 0; //此句可根据需要修改
}
