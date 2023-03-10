#include "window.h"
#include "glwidget.h"

#include <QGridLayout>
#include <QLabel>
#include <QTimer>

Window::Window()
{
    setWindowTitle(tr("CostMap Display"));

    //新建底层layout
    QGridLayout *mainLayout = new QGridLayout;

    //新建GLWidget控件
    GLWidget *openGL = new GLWidget(&helper, this);

    //在底层layout中添加layout和控件
    mainLayout->addWidget(openGL,0,1);

    setLayout(mainLayout);
}


