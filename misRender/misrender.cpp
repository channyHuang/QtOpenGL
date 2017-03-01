#include "misrender.h"

#include <QHBoxLayout>

misRender::misRender(QWidget *parent)
	:ui(new Ui::misRender), QWidget(parent)
{
	ui->setupUi(this);

	glwidget = new GLWidget();

	QHBoxLayout *mainlayout = new QHBoxLayout();
	mainlayout->addWidget(glwidget);

	setLayout(mainlayout);
}

misRender::~misRender()
{
	delete ui;
}
