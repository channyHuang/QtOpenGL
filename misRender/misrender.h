#ifndef MISRENDER_H
#define MISRENDER_H

#include <QtWidgets/QWidget>
#include "ui_misrender.h"

#include "GLWidget.h"

namespace Ui
{
	class misRender;
}

class misRender : public QWidget
{
	Q_OBJECT

public:
	misRender(QWidget *parent = 0);
	~misRender();

private:
	Ui::misRender *ui;

	GLWidget *glwidget;
};

#endif // MISRENDER_H
