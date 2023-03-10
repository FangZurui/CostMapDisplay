#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>

class Helper;
class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    GLWidget(Helper *helper,QWidget *parent);

protected:
    //绘图事件函数
    void paintEvent(QPaintEvent *event) override;

    //鼠标滚轮事件函数
    void wheelEvent(QWheelEvent *event)override;

    //鼠标移动事件函数
    void mouseReleaseEvent(QMouseEvent *event)override;

    //鼠标点击事件函数
    void mousePressEvent(QMouseEvent *event)override;

private:
    Helper *helper;
};

#endif // GLWIDGET_H
