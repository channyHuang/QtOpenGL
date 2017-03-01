#ifndef RELIGHTINGDRAFT_H
#define RELIGHTINGDRAFT_H

#include <QtWidgets/QWidget>
#include "ui_relightingdraft.h"

#include "modelGLWidget.h"
#include "mainGLWidget.h"

namespace Ui
{
	class relightingDraft;
}

class relightingDraft : public QWidget
{
	Q_OBJECT

public:
	relightingDraft(QWidget *parent = 0);
	~relightingDraft();

	void initWidgets();
	void initConnects();

protected:
	void keyPressEvent(QKeyEvent *e);
private:
	Ui::relightingDraft *ui;

	ModelGLWidget *modelWidget;
	MainGLWidget *mainWidget;

	bool modelWindowOn;
};

#endif // RELIGHTINGDRAFT_H
