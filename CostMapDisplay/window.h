#ifndef WINDOW_H
#define WINDOW_H

#include "helper.h"

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QToolButton>

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();

private:
    Helper helper;
};
#endif // WINDOW_H
