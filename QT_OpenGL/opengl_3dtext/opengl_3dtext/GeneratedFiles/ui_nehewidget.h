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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_nehewidgetClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *nehewidgetClass)
    {
        if (nehewidgetClass->objectName().isEmpty())
            nehewidgetClass->setObjectName(QStringLiteral("nehewidgetClass"));
        nehewidgetClass->resize(600, 400);
        menuBar = new QMenuBar(nehewidgetClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        nehewidgetClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(nehewidgetClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        nehewidgetClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(nehewidgetClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        nehewidgetClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(nehewidgetClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        nehewidgetClass->setStatusBar(statusBar);

        retranslateUi(nehewidgetClass);

        QMetaObject::connectSlotsByName(nehewidgetClass);
    } // setupUi

    void retranslateUi(QMainWindow *nehewidgetClass)
    {
        nehewidgetClass->setWindowTitle(QApplication::translate("nehewidgetClass", "nehewidget", 0));
    } // retranslateUi

};

namespace Ui {
    class nehewidgetClass: public Ui_nehewidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEHEWIDGET_H
