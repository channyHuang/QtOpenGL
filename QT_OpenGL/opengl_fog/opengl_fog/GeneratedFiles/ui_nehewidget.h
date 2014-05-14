/********************************************************************************
** Form generated from reading UI file 'nehewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEHEWIDGET_H
#define UI_NEHEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_nehewidgetClass
{
public:

    void setupUi(QWidget *nehewidgetClass)
    {
        if (nehewidgetClass->objectName().isEmpty())
            nehewidgetClass->setObjectName(QStringLiteral("nehewidgetClass"));
        nehewidgetClass->resize(600, 400);

        retranslateUi(nehewidgetClass);

        QMetaObject::connectSlotsByName(nehewidgetClass);
    } // setupUi

    void retranslateUi(QWidget *nehewidgetClass)
    {
        nehewidgetClass->setWindowTitle(QApplication::translate("nehewidgetClass", "nehewidget", 0));
    } // retranslateUi

};

namespace Ui {
    class nehewidgetClass: public Ui_nehewidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEHEWIDGET_H
