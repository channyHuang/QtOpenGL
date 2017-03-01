#ifndef GLTRANSLATIONDEMO_H
#define GLTRANSLATIONDEMO_H

#include <QtWidgets/QWidget>
#include "ui_gltranslationdemo.h"
#include <QPushButton>
#include <QGroupBox>
#include <QSpinBox>
#include <QGridLayout>

#include "glWindow.h"
#include "glWindow3D.h"

namespace Ui
{
	class glTranslationDemo;
}

class glTranslationDemo : public QWidget
{
	Q_OBJECT

public:
	glTranslationDemo(QWidget *parent = 0);
	~glTranslationDemo();

protected:
	void initwidgets();
	void initconnects();

	void showmatrix();

private slots:
	void resetview();
	void resetmodel();
	void computeMatrix();

	void resetmatrix();

private:
	Ui::glTranslationDemo *ui;

	glWindow *glwindow;
	glWindow3D *glwindow3d;

	QGroupBox *viewparambox, *modelparambox;
	QGroupBox *modelviewbox, *viewmatrixbox, *modelmatrixbox;

	QSpinBox *viewxbox, *viewybox, *viewzbox;
	QSpinBox *pitchbox, *rollbox, *yawbox;
	QSpinBox *modelxbox, *modelybox, *modelzbox;
	QSpinBox *rotxbox, *rotybox, *rotzbox;

	QPushButton *resetviewbtn, *resetmodelbtn;

	QGridLayout *modelviewmatrixshow;
	QGridLayout *viewmatrixshow;
	QGridLayout *modelmatrixshow;
};

#endif // GLTRANSLATIONDEMO_H
