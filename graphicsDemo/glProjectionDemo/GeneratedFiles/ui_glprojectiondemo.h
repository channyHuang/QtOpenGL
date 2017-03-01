/********************************************************************************
** Form generated from reading UI file 'glprojectiondemo.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GLPROJECTIONDEMO_H
#define UI_GLPROJECTIONDEMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_glProjectionDemo
{
public:

    void setupUi(QWidget *glProjectionDemo)
    {
        if (glProjectionDemo->objectName().isEmpty())
            glProjectionDemo->setObjectName(QStringLiteral("glProjectionDemo"));
        glProjectionDemo->resize(600, 400);

        retranslateUi(glProjectionDemo);

        QMetaObject::connectSlotsByName(glProjectionDemo);
    } // setupUi

    void retranslateUi(QWidget *glProjectionDemo)
    {
        glProjectionDemo->setWindowTitle(QApplication::translate("glProjectionDemo", "glProjectionDemo", 0));
    } // retranslateUi

};

namespace Ui {
    class glProjectionDemo: public Ui_glProjectionDemo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GLPROJECTIONDEMO_H
