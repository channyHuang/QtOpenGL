#include "mainwidget.h"

#include <QHBoxLayout>

#include "glwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *mainlayout = new QHBoxLayout();
    mainlayout->addWidget(new GlWidget(this));

    this->setMinimumSize(QSize(640, 480));
    setLayout(mainlayout);
}

MainWidget::~MainWidget() {}
