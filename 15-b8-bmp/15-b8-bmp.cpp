/* 2354180 王韵涵 计科 */
#include <iostream>
#include <fstream>
//不再允许加入任何头文件，特别是<Windows.h>，查到就是0分甚至是倒扣-20!!!!!
using namespace std;

#include "15-b8-bmp.h"

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：按需补充
***************************************************************************/
bitmap::bitmap(const char *const filename)
{
	ifstream gfile;
	gfile.open(filename, ios::in | ios::binary);
	if (!gfile.is_open()) {
		cout << "bmp文件打开失败！" << endl;
		return;
	}
	gfile.read((char*)&FILE, sizeof(FILE));
	if (FILE.bfType != 0x4D42) {  
		gfile.close();
		return;
	}
	gfile.read((char*)&INFO, sizeof(INFO));

	if (INFO.biBitCount <= 8) { // 位深度 <= 8 时存在颜色表
		int color_table_size = 1 << INFO.biBitCount; // 颜色表条目数
		for (int i = 0; i < color_table_size; ++i) {
			gfile.read((char*)&CT[i].rgbBlue, 1);  // 蓝色分量
			gfile.read((char*)&CT[i].rgbGreen, 1); // 绿色分量
			gfile.read((char*)&CT[i].rgbRed, 1);   // 红色分量
			gfile.read((char*)&CT[i].rgbReserved, 1); // 保留字节
		}
	}


	data = new unsigned char[INFO.biSizeImage];
	for (unsigned int i = 0; i < INFO.biSizeImage; i++) {
		data[i] = gfile.get();
	}



}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：按需补充
***************************************************************************/
bitmap::~bitmap()
{
	delete[]data;

}

//按需增加内容

int bitmap::show(const int top_left_x, const int top_left_y, const int angle, const bool is_mirror,
	void (*draw_point)(const int x, const int y, const unsigned char red, const unsigned char green, const unsigned char blue)) const
{
	
		if (INFO.biBitCount == 1 || INFO.biBitCount == 4 || INFO.biBitCount == 8) {
			int bytes_per_row = ((INFO.biWidth * INFO.biBitCount + 31) / 32) * 4; // 每行字节数，4 字节对齐
			for (int index_y = 0; index_y < INFO.biHeight; index_y++) {
				for (int index_x = 0; index_x < INFO.biWidth; index_x++) {
					
					int byte_index = ((INFO.biHeight - 1 - index_y) * bytes_per_row) + (index_x * INFO.biBitCount / 8);
					int bit_offset = index_x % (8 / INFO.biBitCount);
						
					unsigned char color_index = (data[byte_index] >> (8 - INFO.biBitCount * (bit_offset + 1))) & ((1 << INFO.biBitCount) - 1);
					unsigned char red = CT[color_index].rgbRed;
					unsigned char green = CT[color_index].rgbGreen;
					unsigned char blue = CT[color_index].rgbBlue;

					int draw_x,draw_y;
					int base_x = is_mirror ? (INFO.biWidth - 1 - index_x) : index_x;

					// 根据旋转角度调整最终的绘制坐标
					if (angle == 90) {
						draw_x = top_left_x + index_y;
						draw_y = top_left_y + INFO.biWidth - 1 - base_x;
					}
					else if (angle == 180) {
						draw_x = top_left_x + INFO.biWidth - 1 - base_x;
						draw_y = top_left_y + INFO.biHeight - 1 - index_y;
					}
					else if (angle == 270) {
						draw_x = top_left_x + INFO.biHeight - 1 - index_y;
						draw_y = top_left_y + base_x;
					}
					else { // 默认无旋转
						draw_x = top_left_x + base_x;
						draw_y = top_left_y + index_y;
					}
					
					draw_point(draw_x, draw_y, red, green, blue);
				}
			}
		}
		if (INFO.biBitCount == 24 || INFO.biBitCount == 32) {
			int bytes_per_row = ((INFO.biWidth * INFO.biBitCount + 31) / 32) * 4;

			for (int index_y = 0; index_y < INFO.biHeight; index_y++) {
				for (int index_x = 0; index_x < INFO.biWidth; index_x++) {

					int pixel_offset = (INFO.biHeight - 1 - index_y) * bytes_per_row + index_x * (INFO.biBitCount / 8);
					
					unsigned char blue = data[pixel_offset];
					unsigned char green = data[pixel_offset + 1];
					unsigned char red = data[pixel_offset + 2];


					int draw_x,draw_y;
					int base_x = is_mirror ? (INFO.biWidth - 1 - index_x) : index_x;

					// 根据旋转角度调整最终的绘制坐标
					if (angle == 90) {
						draw_x = top_left_x + index_y;
						draw_y = top_left_y + INFO.biWidth - 1 - base_x;
					}
					else if (angle == 180) {
						draw_x = top_left_x + INFO.biWidth - 1 - base_x;
						draw_y = top_left_y + INFO.biHeight - 1 - index_y;
					}
					else if (angle == 270) {
						draw_x = top_left_x + INFO.biHeight - 1 - index_y;
						draw_y = top_left_y + base_x;
					}
					else { // 默认无旋转
						draw_x = top_left_x + base_x;
						draw_y = top_left_y + index_y;
					}

					draw_point(draw_x, draw_y, red, green, blue);
				}
			}
		}



		
		return 0;
}