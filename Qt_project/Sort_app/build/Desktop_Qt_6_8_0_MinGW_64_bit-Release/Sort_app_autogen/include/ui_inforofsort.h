/********************************************************************************
** Form generated from reading UI file 'inforofsort.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFOROFSORT_H
#define UI_INFOROFSORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_inforOfSort
{
public:
    QPushButton *btn_goHome;
    QPushButton *btn_goBack_inforsort;
    QLabel *lblinforSort;
    QPushButton *btn_start;
    QTextEdit *txt_infor;

    void setupUi(QWidget *inforOfSort)
    {
        if (inforOfSort->objectName().isEmpty())
            inforOfSort->setObjectName("inforOfSort");
        inforOfSort->resize(766, 574);
        btn_goHome = new QPushButton(inforOfSort);
        btn_goHome->setObjectName("btn_goHome");
        btn_goHome->setEnabled(true);
        btn_goHome->setGeometry(QRect(730, 10, 31, 31));
        btn_goHome->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_goHome->setAutoFillBackground(false);
        btn_goHome->setStyleSheet(QString::fromUtf8("border-image: url(:/image/image/home_icon.png);"));
        btn_goBack_inforsort = new QPushButton(inforOfSort);
        btn_goBack_inforsort->setObjectName("btn_goBack_inforsort");
        btn_goBack_inforsort->setGeometry(QRect(4, 21, 21, 16));
        btn_goBack_inforsort->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_goBack_inforsort->setStyleSheet(QString::fromUtf8("border-image: url(:/image/image/back.png);"));
        lblinforSort = new QLabel(inforOfSort);
        lblinforSort->setObjectName("lblinforSort");
        lblinforSort->setGeometry(QRect(40, 10, 321, 32));
        QFont font;
        font.setPointSize(14);
        lblinforSort->setFont(font);
        lblinforSort->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        btn_start = new QPushButton(inforOfSort);
        btn_start->setObjectName("btn_start");
        btn_start->setGeometry(QRect(360, 270, 41, 41));
        btn_start->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_start->setStyleSheet(QString::fromUtf8("border-image: url(:/image/image/play.png);"));
        txt_infor = new QTextEdit(inforOfSort);
        txt_infor->setObjectName("txt_infor");
        txt_infor->setGeometry(QRect(20, 320, 731, 241));
        QFont font1;
        font1.setPointSize(12);
        txt_infor->setFont(font1);

        retranslateUi(inforOfSort);

        QMetaObject::connectSlotsByName(inforOfSort);
    } // setupUi

    void retranslateUi(QWidget *inforOfSort)
    {
        inforOfSort->setWindowTitle(QCoreApplication::translate("inforOfSort", "Form", nullptr));
        btn_goHome->setText(QString());
        btn_goBack_inforsort->setText(QString());
        lblinforSort->setText(QString());
        btn_start->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class inforOfSort: public Ui_inforOfSort {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFOROFSORT_H
