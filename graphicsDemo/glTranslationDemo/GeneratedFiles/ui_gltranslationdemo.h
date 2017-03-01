/********************************************************************************
** Form generated from reading UI file 'gltranslationdemo.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GLTRANSLATIONDEMO_H
#define UI_GLTRANSLATIONDEMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_glTranslationDemo
{
public:

    void setupUi(QWidget *glTranslationDemo)
    {
        if (glTranslationDemo->objectName().isEmpty())
            glTranslationDemo->setObjectName(QStringLiteral("glTranslationDemo"));
        glTranslationDemo->resize(600, 400);

        retranslateUi(glTranslationDemo);

        QMetaObject::connectSlotsByName(glTranslationDemo);
    } // setupUi

    void retranslateUi(QWidget *glTranslationDemo)
    {
        glTranslationDemo->setWindowTitle(QApplication::translate("glTranslationDemo", "glTranslationDemo", 0));
    } // retranslateUi

};

namespace Ui {
    class glTranslationDemo: public Ui_glTranslationDemo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GLTRANSLATIONDEMO_H
