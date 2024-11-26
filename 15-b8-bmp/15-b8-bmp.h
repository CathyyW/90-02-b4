/* 2354180 ���Ϻ� �ƿ� */
#pragma once

//����������κ�ͷ�ļ����ر���<Windows.h>���鵽����0�������ǵ���-20 ������

//���в���������ϣ��˽������⼸��Ԥ������������ã����ܷ�������ҵ�������㣡����
//#pragma pack(show) //�Ծ�����Ϣ����ʽ��ʾ��ǰ�ֽڶ����ֵ
//#pragma pack(push) //����ǰ�ֽڶ���ֵѹ�������ջ��ջ��
//#pragma pack(push, 4) //����ǰ�ֽڶ���ֵѹ�������ջ��ջ����Ȼ���ٽ�4���õ�ǰֵ
//#pragma pack(pop)  //��������ջջ�����ֽڶ���ֵ����������Ϊ��ǰֵ
//#pragma pack() //���������ǻָ�Ĭ��ֵ


//������������Ҫ�Ľṹ�壨�ࣩ����������������
#pragma pack(push,1)
struct bitmap_fileheader {
   
    unsigned short bfType;       // �ļ����� 
    unsigned int bfSize;         // �ļ���С���ֽڣ�
    unsigned short bfReserved1;  // �����ֶΣ�����Ϊ 0
    unsigned short bfReserved2;  // �����ֶΣ�����Ϊ 0
    unsigned int offbits;      // ��������ƫ����


};
#pragma pack()
#pragma pack(push,1)
struct bitmap_infoheader {
    unsigned int biSize;         // ��Ϣͷ��С���ֽڣ�
    int biWidth;                 // ͼ���ȣ����أ�
    int biHeight;                // ͼ��߶ȣ����أ�
    unsigned short biPlanes;     // ��ɫƽ����������Ϊ 1��
    unsigned short biBitCount;   // ÿ����λ����1/16/256/24/32 �ȣ�
    unsigned int biCompression;  // ѹ����ʽ��0 ��ʾ��ѹ����
    unsigned int biSizeImage;    // ͼ�����ݴ�С���ֽڣ�
    int biXPelsPerMeter;         // ˮƽ�ֱ��ʣ�����/�ף�
    int biYPelsPerMeter;         // ��ֱ�ֱ��ʣ�����/�ף�
    unsigned int biClrUsed;      // ʹ�õ���ɫ����0 ��ʾȫʹ�ã�
    unsigned int biClrImportant; // ��Ҫ��ɫ����0 ��ʾ������ɫ����Ҫ��


};
#pragma pack()
#pragma pack(push,1)
struct color_table {
    unsigned char rgbBlue;   // ��ɫ����
    unsigned char rgbGreen;  // ��ɫ����
    unsigned char rgbRed;    // ��ɫ����
    unsigned char rgbReserved; // �����ֶΣ�ͨ��Ϊ 0
};
#pragma pack()


class bitmap {
private:
    //�����������Ҫ�����ݳ�Ա����Ա����������������
    bitmap_fileheader FILE;

    bitmap_infoheader INFO;

    color_table CT[256];
    unsigned char* data;

public:
    //���в��ֲ���������κ�����
    bitmap(const char* const filename);
    ~bitmap();
    int show(const int top_left_x, const int top_left_y, const int angle, const bool is_mirror, 
                void (*draw_point)(const int x, const int y, const unsigned char red, const unsigned char green, const unsigned char blue)) const;
};
