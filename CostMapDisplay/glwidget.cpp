#include "glwidget.h"
#include "helper.h"

#include <QPainter>

//GLWidget初始化
GLWidget::GLWidget(Helper *helper,QWidget *parent)
    : QOpenGLWidget(parent), helper(helper)
{
	setFixedSize(900,900);
    setAutoFillBackground(true);
	//读取文件
    helper->readDat();
    helper->readTxt();
	//将初始状态地图的方块rec的左上角坐标位置存入数组paintMapList_x和paintMapList_y
	for (int i = 0; i<helper->mapFileList.size(); i++)
	{
		for (int j = 0; j<helper->mapFileList[1].size(); j++)
		{
			//按照初始坐标和宽度width，循环得到每个矩形左上角的坐标
			helper->paintMapList_x.push_back(j*helper->width);
		}
		helper->paintMapList_y.push_back(i*helper->width);
	}
	//将高斯坐标系转换为绘图坐标系，并存入数组paintLineList
	for (int i = 0; i<helper->coordLineList.size(); i++)
	{
		QVector<float>temp;
		temp.push_back(float((helper->coordLineList[i][0] - (546132.8125 - (0.2 * 341) - helper->first_x)) * 5));		//方块宽度为0.2，这里除以0.2即乘上5
		temp.push_back(float((helper->coordLineList[i][1] - (3366640 - helper->first_y)) * 5));
		helper->paintLineList.push_back(temp);
	}
}

//绘图事件函数
void GLWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    helper->paint(&painter);
}

//鼠标滚轮事件函数
void GLWidget::wheelEvent(QWheelEvent *event)
{
	helper->zoom = 0.0;
	//向上滚动
	if (event->delta() > 0)
	{
		helper->zoom += 0.5;
		helper->width = helper->width*(1 + helper->zoom);
	}		
	else
	{
		//限制缩放过小
		if (helper->width < 2)
			return;
		helper->zoom -= 0.5;
		helper->width = helper->width*(1 + helper->zoom);
	}
    //计算绘图坐标
	for (int i = 0; i < helper->paintMapList_x.size(); i++)
	{
		helper->paintMapList_x[i] = helper->current_x - ((1.0 + helper->zoom)*(helper->current_x - helper->paintMapList_x[i]));
	}
	for (int j = 0; j < helper->paintMapList_y.size(); j++)
	{
		helper->paintMapList_y[j] = helper->current_y - ((1.0 + helper->zoom)*(helper->current_y - helper->paintMapList_y[j]));
	}
	for (int k = 0; k < helper->paintLineList.size(); k++)
	{
		helper->paintLineList[k][0] = helper->current_x - ((1.0 + helper->zoom)*(helper->current_x - helper->paintLineList[k][0]));
		helper->paintLineList[k][1] = helper->current_y - ((1.0 + helper->zoom)*(helper->current_y - helper->paintLineList[k][1]));
	}
    update();
}

//鼠标移动事件函数
void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
	//获取当前鼠标位置
	helper->current_x =event->x();
    helper->current_y =event->y();

	//平移地图
	for (int i = 0; i < (int)helper->paintMapList_x.size(); i++)
	{
		helper->paintMapList_x[i] = helper->paintMapList_x[i] + (helper->current_x - helper->last_x);
	}
	for (int j = 0; j < (int)helper->paintMapList_y.size(); j++)
	{
		helper->paintMapList_y[j] = helper->paintMapList_y[j] + (helper->current_y - helper->last_y);
	}
	//平移标记线
	for (int k = 0; k < (int)helper->paintLineList.size(); k++)
	{
		helper->paintLineList[k][0] = helper->paintLineList[k][0] + (helper->current_x - helper->last_x);
		helper->paintLineList[k][1] = helper->paintLineList[k][1] + (helper->current_y - helper->last_y);
	}
    update();
}

//鼠标点击事件函数
void GLWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)       //点击了鼠标并且是左键
    {
        //获取当前鼠标位置
		helper->last_x=event->x();
        helper->last_y=event->y();

        //根据鼠标位置弹出指定格子坐标
        QString x=QString::number(546132.8125-(0.2*341)+int((helper->last_x-helper->first_x)/helper->width)*0.2,'f',2);
        QString y=QString::number(3366640+int((helper->last_y-helper->first_y)/helper->width)*0.2,'f',2);

        //用气泡Tooltip展示当前格子坐标
        toolTip();
        QString str=x+":"+y;
        setToolTip(str);
    }
}
