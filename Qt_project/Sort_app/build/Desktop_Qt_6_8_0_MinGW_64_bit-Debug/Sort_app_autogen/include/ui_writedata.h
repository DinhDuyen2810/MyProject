/********************************************************************************
** Form generated from reading UI file 'writedata.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WRITEDATA_H
#define UI_WRITEDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_writeData
{
public:
    QPushButton *btn_goBack_writeNumber;
    QPlainTextEdit *txtToWrite;
    QPushButton *btn_start_sort;
    QLabel *lblNameOfSort;
    QPushButton *btn_goHome;
    QLabel *label;
    QLabel *lbl_ready;

    void setupUi(QWidget *writeData)
    {
        if (writeData->objectName().isEmpty())
            writeData->setObjectName("writeData");
        writeData->resize(766, 574);
        btn_goBack_writeNumber = new QPushButton(writeData);
        btn_goBack_writeNumber->setObjectName("btn_goBack_writeNumber");
        btn_goBack_writeNumber->setGeometry(QRect(10, 20, 21, 16));
        btn_goBack_writeNumber->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_goBack_writeNumber->setStyleSheet(QString::fromUtf8("border-image: url(:/image/image/back.png);"));
        txtToWrite = new QPlainTextEdit(writeData);
        txtToWrite->setObjectName("txtToWrite");
        txtToWrite->setGeometry(QRect(40, 110, 691, 311));
        QFont font;
        font.setPointSize(10);
        txtToWrite->setFont(font);
        btn_start_sort = new QPushButton(writeData);
        btn_start_sort->setObjectName("btn_start_sort");
        btn_start_sort->setGeometry(QRect(340, 430, 91, 51));
        QFont font1;
        font1.setPointSize(22);
        btn_start_sort->setFont(font1);
        btn_start_sort->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_start_sort->setStyleSheet(QString::fromUtf8("background-color: rgb(184, 184, 184);"));
        lblNameOfSort = new QLabel(writeData);
        lblNameOfSort->setObjectName("lblNameOfSort");
        lblNameOfSort->setGeometry(QRect(46, 9, 301, 32));
        QFont font2;
        font2.setPointSize(14);
        lblNameOfSort->setFont(font2);
        lblNameOfSort->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        btn_goHome = new QPushButton(writeData);
        btn_goHome->setObjectName("btn_goHome");
        btn_goHome->setEnabled(true);
        btn_goHome->setGeometry(QRect(730, 10, 31, 31));
        btn_goHome->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_goHome->setAutoFillBackground(false);
        btn_goHome->setStyleSheet(QString::fromUtf8("border-image: url(:/image/image/home_icon.png);"));
        label = new QLabel(writeData);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 65, 341, 31));
        QFont font3;
        font3.setPointSize(12);
        label->setFont(font3);
        lbl_ready = new QLabel(writeData);
        lbl_ready->setObjectName("lbl_ready");
        lbl_ready->setGeometry(QRect(290, 490, 201, 51));
        lbl_ready->setFont(font3);
        lbl_ready->setAlignment(Qt::AlignmentFlag::AlignCenter);

        retranslateUi(writeData);

        QMetaObject::connectSlotsByName(writeData);
    } // setupUi

    void retranslateUi(QWidget *writeData)
    {
        writeData->setWindowTitle(QCoreApplication::translate("writeData", "Form", nullptr));
        btn_goBack_writeNumber->setText(QString());
        btn_start_sort->setText(QCoreApplication::translate("writeData", "Sort", nullptr));
        lblNameOfSort->setText(QCoreApplication::translate("writeData", "T\341\273\261 nh\341\272\255p d\341\273\257 li\341\273\207u", nullptr));
        btn_goHome->setText(QString());
        label->setText(QCoreApplication::translate("writeData", "Vui l\303\262ng nh\341\272\255p d\341\273\257 li\341\273\207u b\341\272\241n mu\341\273\221n s\341\272\257p x\341\272\277p", nullptr));
        lbl_ready->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class writeData: public Ui_writeData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WRITEDATA_H
