/********************************************************************************
** Form generated from reading UI file 'graphicsdemo.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHICSDEMO_H
#define UI_GRAPHICSDEMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_graphicsDemo
{
public:

    void setupUi(QWidget *graphicsDemo)
    {
        if (graphicsDemo->objectName().isEmpty())
            graphicsDemo->setObjectName(QStringLiteral("graphicsDemo"));
        graphicsDemo->resize(600, 400);

        retranslateUi(graphicsDemo);

        QMetaObject::connectSlotsByName(graphicsDemo);
    } // setupUi

    void retranslateUi(QWidget *graphicsDemo)
    {
        graphicsDemo->setWindowTitle(QApplication::translate("graphicsDemo", "graphicsDemo", 0));
    } // retranslateUi

};

namespace Ui {
    class graphicsDemo: public Ui_graphicsDemo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHICSDEMO_H
