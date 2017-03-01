#include "relightingdraft.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

relightingDraft::relightingDraft(QWidget *parent)
	:ui(new Ui::relightingDraft), QWidget(parent)
{
	ui->setupUi(this);
	setGeometry(100, 100, 640, 480);

	modelWindowOn = true;
	initWidgets();

	QVBoxLayout *modellayout = new QVBoxLayout();
	modellayout->addWidget(modelWidget);
//	modellayout->addStretch(1);
	QHBoxLayout *mainlayout = new QHBoxLayout();
	mainlayout->addLayout(modellayout);
	mainlayout->addWidget(mainWidget);

	setLayout(mainlayout);
}

relightingDraft::~relightingDraft()
{
	delete ui;
}

void relightingDraft::initWidgets()
{
	modelWidget = new ModelGLWidget(this);
	mainWidget = new MainGLWidget(this);
}
void relightingDraft::initConnects()
{}

void relightingDraft::keyPressEvent(QKeyEvent *e)
{
	switch (e->key())
	{
	case Qt::Key_Q:
		exit(0);
		break;
	case Qt::Key_M:
		modelWindowOn = !modelWindowOn;
		break;
	case Qt::Key_X:
		if (modelWindowOn) {
			modelWidget->xrot -= 8.0f;
			if (modelWidget->xrot < -360)
				modelWidget->xrot = 0;
			mainWidget->lightxrot = modelWidget->xrot;
		}
		else {
			mainWidget->xrot -= 8.0f;
			if (mainWidget->xrot < -360)
				mainWidget->xrot = 0;
		}
		break;
	case Qt::Key_Y:
		if (modelWindowOn) {
			modelWidget->yrot += 8.0f;
			if (modelWidget->yrot > 360)
				modelWidget->yrot = 0;
			mainWidget->lightyrot = modelWidget->yrot;
		}
		else {
			mainWidget->yrot += 8.0f;
			if (mainWidget->yrot > 360)
				mainWidget->yrot = 0;
		}
		break;
	case Qt::Key_Z:
		if (modelWindowOn) {
			modelWidget->zrot += 8.0f;
			if (modelWidget->zrot > 360)
				modelWidget->zrot = 0;
			mainWidget->lightzrot = modelWidget->zrot;
		}
		else {
			mainWidget->zrot -= 8.0f;
			if (mainWidget->zrot < -360)
				mainWidget->zrot = 0;
		}
		break;
	default:
		break;
	}
}