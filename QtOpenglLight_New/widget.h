#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QKeyEvent>

#include "glwidget.h"
#include "modelWidget.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void keyPressEvent(QKeyEvent *e);

private:
    QHBoxLayout *mainLayout = nullptr;
    GlWidget *mainWidget = nullptr; // result widget
    ModelWidget *modelWidget = nullptr; // model widget

    bool modelWindowOn = false;
};
#endif // WIDGET_H
