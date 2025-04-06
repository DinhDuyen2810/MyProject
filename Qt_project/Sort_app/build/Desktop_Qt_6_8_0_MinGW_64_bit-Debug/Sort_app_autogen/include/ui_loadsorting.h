/********************************************************************************
** Form generated from reading UI file 'loadsorting.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADSORTING_H
#define UI_LOADSORTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loadSorting
{
public:
    QLabel *lblLoading;
    QLabel *label_2;

    void setupUi(QWidget *loadSorting)
    {
        if (loadSorting->objectName().isEmpty())
            loadSorting->setObjectName("loadSorting");
        loadSorting->resize(400, 574);
        loadSorting->setStyleSheet(QString::fromUtf8("background-color: rgb(176, 168, 172);\n"
"background-color: rgb(255, 255, 255);"));
        lblLoading = new QLabel(loadSorting);
        lblLoading->setObjectName("lblLoading");
        lblLoading->setGeometry(QRect(120, 180, 131, 131));
        lblLoading->setStyleSheet(QString::fromUtf8(""));
        label_2 = new QLabel(loadSorting);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(110, 340, 171, 81));
        QFont font;
        font.setPointSize(28);
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        retranslateUi(loadSorting);

        QMetaObject::connectSlotsByName(loadSorting);
    } // setupUi

    void retranslateUi(QWidget *loadSorting)
    {
        loadSorting->setWindowTitle(QCoreApplication::translate("loadSorting", "Form", nullptr));
        lblLoading->setText(QString());
        label_2->setText(QCoreApplication::translate("loadSorting", "Loading", nullptr));
    } // retranslateUi

};

namespace Ui {
    class loadSorting: public Ui_loadSorting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADSORTING_H
