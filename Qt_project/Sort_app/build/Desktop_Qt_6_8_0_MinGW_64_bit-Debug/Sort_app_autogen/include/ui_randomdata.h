/********************************************************************************
** Form generated from reading UI file 'randomdata.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RANDOMDATA_H
#define UI_RANDOMDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_randomData
{
public:
    QPushButton *btn_goHome;
    QPushButton *btn_start_sort;
    QLabel *lbl_ready;
    QLabel *lblNameOfSort;
    QPushButton *btn_goBack_randomData;
    QFrame *frame;
    QLineEdit *lneRandom;
    QLabel *label;
    QLineEdit *lneBottom;
    QLabel *label_3;
    QLabel *label_2;
    QLineEdit *lneTop;

    void setupUi(QWidget *randomData)
    {
        if (randomData->objectName().isEmpty())
            randomData->setObjectName("randomData");
        randomData->resize(766, 574);
        btn_goHome = new QPushButton(randomData);
        btn_goHome->setObjectName("btn_goHome");
        btn_goHome->setEnabled(true);
        btn_goHome->setGeometry(QRect(730, 10, 31, 31));
        btn_goHome->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_goHome->setAutoFillBackground(false);
        btn_goHome->setStyleSheet(QString::fromUtf8("border-image: url(:/image/image/home_icon.png);"));
        btn_start_sort = new QPushButton(randomData);
        btn_start_sort->setObjectName("btn_start_sort");
        btn_start_sort->setGeometry(QRect(340, 420, 91, 51));
        QFont font;
        font.setPointSize(22);
        btn_start_sort->setFont(font);
        btn_start_sort->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_start_sort->setStyleSheet(QString::fromUtf8("background-color: rgb(184, 184, 184);"));
        lbl_ready = new QLabel(randomData);
        lbl_ready->setObjectName("lbl_ready");
        lbl_ready->setGeometry(QRect(320, 480, 141, 41));
        QFont font1;
        font1.setPointSize(16);
        lbl_ready->setFont(font1);
        lbl_ready->setAlignment(Qt::AlignmentFlag::AlignCenter);
        lblNameOfSort = new QLabel(randomData);
        lblNameOfSort->setObjectName("lblNameOfSort");
        lblNameOfSort->setGeometry(QRect(46, 9, 301, 32));
        QFont font2;
        font2.setPointSize(14);
        lblNameOfSort->setFont(font2);
        lblNameOfSort->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        btn_goBack_randomData = new QPushButton(randomData);
        btn_goBack_randomData->setObjectName("btn_goBack_randomData");
        btn_goBack_randomData->setGeometry(QRect(10, 20, 21, 16));
        btn_goBack_randomData->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_goBack_randomData->setStyleSheet(QString::fromUtf8("border-image: url(:/image/image/back.png);"));
        frame = new QFrame(randomData);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(30, 70, 681, 311));
        frame->setFont(font1);
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        lneRandom = new QLineEdit(frame);
        lneRandom->setObjectName("lneRandom");
        lneRandom->setGeometry(QRect(90, 70, 101, 31));
        QFont font3;
        font3.setPointSize(10);
        lneRandom->setFont(font3);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 20, 501, 41));
        label->setFont(font2);
        lneBottom = new QLineEdit(frame);
        lneBottom->setObjectName("lneBottom");
        lneBottom->setGeometry(QRect(90, 160, 101, 31));
        lneBottom->setFont(font3);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(40, 200, 381, 41));
        label_3->setFont(font2);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 110, 481, 41));
        label_2->setFont(font2);
        lneTop = new QLineEdit(frame);
        lneTop->setObjectName("lneTop");
        lneTop->setGeometry(QRect(90, 250, 101, 31));
        lneTop->setFont(font3);

        retranslateUi(randomData);

        QMetaObject::connectSlotsByName(randomData);
    } // setupUi

    void retranslateUi(QWidget *randomData)
    {
        randomData->setWindowTitle(QCoreApplication::translate("randomData", "Form", nullptr));
        btn_goHome->setText(QString());
        btn_start_sort->setText(QCoreApplication::translate("randomData", "Sort", nullptr));
        lbl_ready->setText(QString());
        lblNameOfSort->setText(QCoreApplication::translate("randomData", "Random d\341\273\257 li\341\273\207u", nullptr));
        btn_goBack_randomData->setText(QString());
        label->setText(QCoreApplication::translate("randomData", "Nh\341\272\255p s\341\273\221 ph\341\272\247n t\341\273\255 b\341\272\241n mu\341\273\221n random", nullptr));
        label_3->setText(QCoreApplication::translate("randomData", "Nh\341\272\255p c\341\272\255n tr\303\252n m\303\240 b\341\272\241n mu\341\273\221n random", nullptr));
        label_2->setText(QCoreApplication::translate("randomData", "Nh\341\272\255p c\341\272\255n d\306\260\341\273\233i m\303\240 b\341\272\241n mu\341\273\221n random", nullptr));
    } // retranslateUi

};

namespace Ui {
    class randomData: public Ui_randomData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RANDOMDATA_H
