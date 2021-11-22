#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QHBoxLayout(this);
    setGeometry(100, 100, 640, 480);

    modelWidget = new ModelWidget(this);
    mainWidget = new GlWidget(this);

    mainLayout->addWidget(mainWidget);
    mainLayout->addWidget(modelWidget);
    setLayout(mainLayout);
}

Widget::~Widget()
{
}

void Widget::keyPressEvent(QKeyEvent *e) {
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
            modelWidget->m_vRot[0] -= 8.0f;
            if (modelWidget->m_vRot[0] < -360)
                modelWidget->m_vRot[0] = 0;
            mainWidget->m_lightRot[0] = modelWidget->m_vRot[0];
        }
        else {
            mainWidget->m_vRot[0] -= 8.0f;
            if (mainWidget->m_vRot[0] < -360)
                mainWidget->m_vRot[0] = 0;
        }
        break;
    case Qt::Key_Y:
        if (modelWindowOn) {
            modelWidget->m_vRot[1] += 8.0f;
            if (modelWidget->m_vRot[1] > 360)
                modelWidget->m_vRot[1] = 0;
            mainWidget->m_lightRot[1] = modelWidget->m_vRot[1];
        }
        else {
            mainWidget->m_vRot[1] += 8.0f;
            if (mainWidget->m_vRot[1] > 360)
                mainWidget->m_vRot[1] = 0;
        }
        break;
    case Qt::Key_Z:
        if (modelWindowOn) {
            modelWidget->m_vRot[2] += 8.0f;
            if (modelWidget->m_vRot[2] > 360)
                modelWidget->m_vRot[2] = 0;
            mainWidget->m_lightRot[2] = modelWidget->m_vRot[2];
        }
        else {
            mainWidget->m_vRot[2] -= 8.0f;
            if (mainWidget->m_vRot[2] < -360)
                mainWidget->m_vRot[2] = 0;
        }
        break;
    default:
        break;
    }
}
