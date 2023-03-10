#include "helper.h"

//初始化绘图工具
Helper::Helper()
{
    background = QBrush(QColor(125,125,125));		//背景色
    zeroArea = QBrush(Qt::gray);					//数据为零部分
    otherArea = QBrush(Qt::white);					//数据不为零部分
	lineColor = QPen(Qt::red);						//线标记数据
	recEdge = QPen(Qt::white);
}

//读取二进制数据
void Helper::readDat()
{
    using namespace std;
    fstream datFile;
    datFile.open("../resource/costmap.dat", ios::in | ios::binary);
    if (!datFile.is_open())
    {
        qErrnoWarning("Open file error!");
        return;
    }
    char data=0;
    for (int i=0; i<789;i++)
    {
		QVector<char>temp;
		for (int j=0; j<341;j++)
        {
            datFile.read((char*)&data, 1);     //按照char类型，每次读取一个字节
			temp.push_back(data);
        }
		mapFileList.push_back(temp);
    }
    datFile.close();
}
//读取线标记数据(转为绘图坐标点)
void Helper::readTxt()
{
    using namespace std;
    FILE *txtFile;
    fopen("../resource/costmap.txt","rt+");
    if(!txtFile)
    {
        qErrnoWarning("Open file error!");
        return;
    }
    int a[3];
    double b[10];
    char c[20]=" ";
    while (!feof(txtFile))
    {
        fscanf(txtFile, "%d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %d %d %s\n",
            &a[0], &b[0], &b[1], &b[2], &b[3], &b[4], &b[5], &b[6], &b[7], &b[8], &b[9], &a[1], &a[2], c, 100);
        QVector<float>temp;
		temp.push_back(float(b[2]));
		temp.push_back(float(b[1]));
        coordLineList.push_back(temp);
    }
    fclose(txtFile);
}

//绘图主函数
void Helper::paint(QPainter *painter)
{
    /*
	一、底图绘制
    每次触发event过后，底图的绘制都只需要计算当前的初始坐标first_x,first_y和缩放比例zoom。
    接着进入绘图主函数，按照新的初始坐标点，重新绘制底图。
    */
	painter->setPen(recEdge);
	
    for(int i=0;i<mapFileList.size();i++)
    {
        for(int j=0;j<mapFileList[1].size();j++)
        {
			if (mapFileList[i][j] == 0)
			{ 
				painter->setBrush(zeroArea);
				painter->drawRect(paintMapList_x[j], paintMapList_y[i], width, width);
			}
			else
				continue;
		}
    }
	/*
	二、标记线绘制
	每次触发event过后，需要重复使用缩放矩阵、平移矩阵。
	计算曲线的每个坐标点，再按照顺序绘制。
	*/
    for(int i=0;i<coordLineList.size()-1;i++)
	{
		painter->setPen(lineColor);
		painter->drawLine(paintLineList[i][0],paintLineList[i][1],paintLineList[i+1][0],paintLineList[i+1][1]);
    }
}
