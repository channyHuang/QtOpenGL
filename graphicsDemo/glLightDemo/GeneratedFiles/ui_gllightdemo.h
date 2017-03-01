/********************************************************************************
** Form generated from reading UI file 'gllightdemo.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GLLIGHTDEMO_H
#define UI_GLLIGHTDEMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_glLightDemo
{
public:

    void setupUi(QWidget *glLightDemo)
    {
        if (glLightDemo->objectName().isEmpty())
            glLightDemo->setObjectName(QStringLiteral("glLightDemo"));
        glLightDemo->resize(600, 400);

        retranslateUi(glLightDemo);

        QMetaObject::connectSlotsByName(glLightDemo);
    } // setupUi

    void retranslateUi(QWidget *glLightDemo)
    {
        glLightDemo->setWindowTitle(QApplication::translate("glLightDemo", "glLightDemo", 0));
    } // retranslateUi

};

namespace Ui {
    class glLightDemo: public Ui_glLightDemo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GLLIGHTDEMO_H
