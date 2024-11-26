/* 2354180 ���Ϻ� �ƿ� */
#include <iostream>
#include <fstream>
//������������κ�ͷ�ļ����ر���<Windows.h>���鵽����0�������ǵ���-20!!!!!
using namespace std;

#include "15-b8-bmp.h"

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    �������貹��
***************************************************************************/
bitmap::bitmap(const char *const filename)
{
	ifstream gfile;
	gfile.open(filename, ios::in | ios::binary);
	if (!gfile.is_open()) {
		cout << "bmp�ļ���ʧ�ܣ�" << endl;
		return;
	}
	gfile.read((char*)&FILE, sizeof(FILE));
	if (FILE.bfType != 0x4D42) {  
		gfile.close();
		return;
	}
	gfile.read((char*)&INFO, sizeof(INFO));

	if (INFO.biBitCount <= 8) { // λ��� <= 8 ʱ������ɫ��
		int color_table_size = 1 << INFO.biBitCount; // ��ɫ����Ŀ��
		for (int i = 0; i < color_table_size; ++i) {
			gfile.read((char*)&CT[i].rgbBlue, 1);  // ��ɫ����
			gfile.read((char*)&CT[i].rgbGreen, 1); // ��ɫ����
			gfile.read((char*)&CT[i].rgbRed, 1);   // ��ɫ����
			gfile.read((char*)&CT[i].rgbReserved, 1); // �����ֽ�
		}
	}


	data = new unsigned char[INFO.biSizeImage];
	for (unsigned int i = 0; i < INFO.biSizeImage; i++) {
		data[i] = gfile.get();
	}



}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    �������貹��
***************************************************************************/
bitmap::~bitmap()
{
	delete[]data;

}

//������������

int bitmap::show(const int top_left_x, const int top_left_y, const int angle, const bool is_mirror,
	void (*draw_point)(const int x, const int y, const unsigned char red, const unsigned char green, const unsigned char blue)) const
{
	
		if (INFO.biBitCount == 1 || INFO.biBitCount == 4 || INFO.biBitCount == 8) {
			int bytes_per_row = ((INFO.biWidth * INFO.biBitCount + 31) / 32) * 4; // ÿ���ֽ�����4 �ֽڶ���
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

					// ������ת�Ƕȵ������յĻ�������
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
					else { // Ĭ������ת
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

					// ������ת�Ƕȵ������յĻ�������
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
					else { // Ĭ������ת
						draw_x = top_left_x + base_x;
						draw_y = top_left_y + index_y;
					}

					draw_point(draw_x, draw_y, red, green, blue);
				}
			}
		}



		
		return 0;
}