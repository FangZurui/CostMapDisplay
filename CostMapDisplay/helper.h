#ifndef HELPER_H
#define HELPER_H

#include <vector>
#include <cstdio>
#include <stdio.h>
#include <string>
#include <fstream>

#include <QPainter>
#include <QPaintEvent>
#include <QWidget>

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>
#include <QPainter>
#include <QWheelEvent>
#include <QMouseEvent>


class Helper
{
public:
    Helper();
public:
    /*add functions here*/
    //绘图主函数
    void paint(QPainter *painter);

    //读取dat文件函数
    void readDat();

    //读取txt文件函数
    void readTxt();

public:
    //存放二进制数据的数组
	QVector<QVector<char>>mapFileList;
	QVector<float>paintMapList_x;
	QVector<float>paintMapList_y;

    //存放标记线数据的数组
	QVector<QVector<float>>coordLineList;
    QVector<QVector<float>>paintLineList;

    //颜色设置
	QPen recEdge;
	QPen lineColor;
    QBrush background;
    QBrush zeroArea;
    QBrush otherArea;
	
    //初始点位置坐标
	float first_x = 0.0, first_y = 0.0;
    //鼠标移动位置坐标
	float current_x = 0.0, current_y = 0.0;
    //鼠标点按时位置坐标
	float last_x = 0.0, last_y = 0.0;
    //初始缩放比例
	float zoom;
    //初始化方格宽
	float width = 2.0;
};

#endif // HELPER_H
