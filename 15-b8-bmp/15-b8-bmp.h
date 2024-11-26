/* 2354180 王韵涵 计科 */
#pragma once

//不允许加入任何头文件，特别是<Windows.h>，查到就是0分甚至是倒扣-20 ！！！

//自行查阅相关资料，了解下面这几个预编译命令的作用，看能否给你的作业带来方便！！！
//#pragma pack(show) //以警告信息的形式显示当前字节对齐的值
//#pragma pack(push) //将当前字节对齐值压入编译器栈的栈顶
//#pragma pack(push, 4) //将当前字节对齐值压入编译器栈的栈顶，然后再将4设置当前值
//#pragma pack(pop)  //将编译器栈栈顶的字节对齐值弹出并设置为当前值
//#pragma pack() //不带参数是恢复默认值


//允许定义其它需要的结构体（类）、常量、常变量等
#pragma pack(push,1)
struct bitmap_fileheader {
   
    unsigned short bfType;       // 文件类型 
    unsigned int bfSize;         // 文件大小（字节）
    unsigned short bfReserved1;  // 保留字段，必须为 0
    unsigned short bfReserved2;  // 保留字段，必须为 0
    unsigned int offbits;      // 像素数据偏移量


};
#pragma pack()
#pragma pack(push,1)
struct bitmap_infoheader {
    unsigned int biSize;         // 信息头大小（字节）
    int biWidth;                 // 图像宽度（像素）
    int biHeight;                // 图像高度（像素）
    unsigned short biPlanes;     // 颜色平面数（必须为 1）
    unsigned short biBitCount;   // 每像素位数（1/16/256/24/32 等）
    unsigned int biCompression;  // 压缩方式（0 表示不压缩）
    unsigned int biSizeImage;    // 图像数据大小（字节）
    int biXPelsPerMeter;         // 水平分辨率（像素/米）
    int biYPelsPerMeter;         // 垂直分辨率（像素/米）
    unsigned int biClrUsed;      // 使用的颜色数（0 表示全使用）
    unsigned int biClrImportant; // 重要颜色数（0 表示所有颜色都重要）


};
#pragma pack()
#pragma pack(push,1)
struct color_table {
    unsigned char rgbBlue;   // 蓝色分量
    unsigned char rgbGreen;  // 绿色分量
    unsigned char rgbRed;    // 红色分量
    unsigned char rgbReserved; // 保留字段，通常为 0
};
#pragma pack()


class bitmap {
private:
    //自行添加你需要的数据成员及成员函数，不限制数量
    bitmap_fileheader FILE;

    bitmap_infoheader INFO;

    color_table CT[256];
    unsigned char* data;

public:
    //公有部分不允许添加任何内容
    bitmap(const char* const filename);
    ~bitmap();
    int show(const int top_left_x, const int top_left_y, const int angle, const bool is_mirror, 
                void (*draw_point)(const int x, const int y, const unsigned char red, const unsigned char green, const unsigned char blue)) const;
};
