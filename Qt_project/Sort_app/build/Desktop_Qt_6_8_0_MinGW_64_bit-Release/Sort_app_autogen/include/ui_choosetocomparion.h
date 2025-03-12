/********************************************************************************
** Form generated from reading UI file 'choosetocomparion.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSETOCOMPARION_H
#define UI_CHOOSETOCOMPARION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chooseToComparion
{
public:
    QPushButton *btn_goHome;
    QLabel *lblNameOfSort;
    QPushButton *btn_goBack_chooseCom;
    QLabel *label;
    QPushButton *btn_next;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QCheckBox *box1;
    QCheckBox *box6;
    QCheckBox *box11;
    QCheckBox *box2;
    QCheckBox *box7;
    QCheckBox *box12;
    QCheckBox *box3;
    QCheckBox *box8;
    QCheckBox *box13;
    QCheckBox *box4;
    QCheckBox *box9;
    QCheckBox *box14;
    QCheckBox *box5;
    QCheckBox *box10;

    void setupUi(QWidget *chooseToComparion)
    {
        if (chooseToComparion->objectName().isEmpty())
            chooseToComparion->setObjectName("chooseToComparion");
        chooseToComparion->resize(766, 574);
        btn_goHome = new QPushButton(chooseToComparion);
        btn_goHome->setObjectName("btn_goHome");
        btn_goHome->setEnabled(true);
        btn_goHome->setGeometry(QRect(730, 10, 31, 31));
        btn_goHome->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_goHome->setAutoFillBackground(false);
        btn_goHome->setStyleSheet(QString::fromUtf8("border-image: url(:/image/image/home_icon.png);"));
        lblNameOfSort = new QLabel(chooseToComparion);
        lblNameOfSort->setObjectName("lblNameOfSort");
        lblNameOfSort->setGeometry(QRect(46, 9, 301, 32));
        QFont font;
        font.setPointSize(14);
        lblNameOfSort->setFont(font);
        lblNameOfSort->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        btn_goBack_chooseCom = new QPushButton(chooseToComparion);
        btn_goBack_chooseCom->setObjectName("btn_goBack_chooseCom");
        btn_goBack_chooseCom->setGeometry(QRect(10, 20, 21, 16));
        btn_goBack_chooseCom->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_goBack_chooseCom->setStyleSheet(QString::fromUtf8("border-image: url(:/image/image/back.png);"));
        label = new QLabel(chooseToComparion);
        label->setObjectName("label");
        label->setGeometry(QRect(60, 80, 431, 41));
        QFont font1;
        font1.setPointSize(12);
        label->setFont(font1);
        btn_next = new QPushButton(chooseToComparion);
        btn_next->setObjectName("btn_next");
        btn_next->setGeometry(QRect(680, 470, 61, 61));
        btn_next->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_next->setStyleSheet(QString::fromUtf8("border-image: url(:/image/image/right.png);"));
        layoutWidget = new QWidget(chooseToComparion);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 140, 743, 291));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        box1 = new QCheckBox(layoutWidget);
        box1->setObjectName("box1");
        box1->setFont(font1);
        box1->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        gridLayout->addWidget(box1, 0, 0, 1, 1);

        box6 = new QCheckBox(layoutWidget);
        box6->setObjectName("box6");
        box6->setFont(font1);
        box6->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        gridLayout->addWidget(box6, 0, 1, 1, 1);

        box11 = new QCheckBox(layoutWidget);
        box11->setObjectName("box11");
        box11->setFont(font1);
        box11->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        gridLayout->addWidget(box11, 0, 2, 1, 1);

        box2 = new QCheckBox(layoutWidget);
        box2->setObjectName("box2");
        box2->setFont(font1);
        box2->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        gridLayout->addWidget(box2, 1, 0, 1, 1);

        box7 = new QCheckBox(layoutWidget);
        box7->setObjectName("box7");
        box7->setFont(font1);
        box7->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        gridLayout->addWidget(box7, 1, 1, 1, 1);

        box12 = new QCheckBox(layoutWidget);
        box12->setObjectName("box12");
        box12->setFont(font1);
        box12->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        gridLayout->addWidget(box12, 1, 2, 1, 1);

        box3 = new QCheckBox(layoutWidget);
        box3->setObjectName("box3");
        box3->setFont(font1);
        box3->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        gridLayout->addWidget(box3, 2, 0, 1, 1);

        box8 = new QCheckBox(layoutWidget);
        box8->setObjectName("box8");
        box8->setFont(font1);
        box8->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        gridLayout->addWidget(box8, 2, 1, 1, 1);

        box13 = new QCheckBox(layoutWidget);
        box13->setObjectName("box13");
        box13->setFont(font1);
        box13->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        gridLayout->addWidget(box13, 2, 2, 1, 1);

        box4 = new QCheckBox(layoutWidget);
        box4->setObjectName("box4");
        box4->setFont(font1);
        box4->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        gridLayout->addWidget(box4, 3, 0, 1, 1);

        box9 = new QCheckBox(layoutWidget);
        box9->setObjectName("box9");
        box9->setFont(font1);
        box9->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        gridLayout->addWidget(box9, 3, 1, 1, 1);

        box14 = new QCheckBox(layoutWidget);
        box14->setObjectName("box14");
        box14->setFont(font1);
        box14->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        gridLayout->addWidget(box14, 3, 2, 1, 1);

        box5 = new QCheckBox(layoutWidget);
        box5->setObjectName("box5");
        box5->setFont(font1);
        box5->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        gridLayout->addWidget(box5, 4, 0, 1, 1);

        box10 = new QCheckBox(layoutWidget);
        box10->setObjectName("box10");
        box10->setFont(font1);
        box10->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        gridLayout->addWidget(box10, 4, 1, 1, 1);


        retranslateUi(chooseToComparion);

        QMetaObject::connectSlotsByName(chooseToComparion);
    } // setupUi

    void retranslateUi(QWidget *chooseToComparion)
    {
        chooseToComparion->setWindowTitle(QCoreApplication::translate("chooseToComparion", "Form", nullptr));
        btn_goHome->setText(QString());
        lblNameOfSort->setText(QCoreApplication::translate("chooseToComparion", "So s\303\241nh thu\341\272\255t to\303\241n", nullptr));
        btn_goBack_chooseCom->setText(QString());
        label->setText(QCoreApplication::translate("chooseToComparion", "Vui l\303\262ng l\341\273\261a ch\341\273\215n c\303\241c thu\341\272\255t to\303\241n b\341\272\241n mu\341\273\221n so s\303\241nh:", nullptr));
        btn_next->setText(QString());
        box1->setText(QCoreApplication::translate("chooseToComparion", "Bubble Sort(S\341\272\257p x\341\272\277p n\341\273\225i b\341\273\215t)", nullptr));
        box6->setText(QCoreApplication::translate("chooseToComparion", "Quick sort (S\341\272\257p x\341\272\277p nhanh)", nullptr));
        box11->setText(QCoreApplication::translate("chooseToComparion", "Bucket sort (S\341\272\257p x\341\272\277p th\303\271ng)", nullptr));
        box2->setText(QCoreApplication::translate("chooseToComparion", "Heap sort (S\341\272\257p x\341\272\277p vun \304\221\341\273\221ng)", nullptr));
        box7->setText(QCoreApplication::translate("chooseToComparion", "Selection sort (S\341\272\257p x\341\272\277p ch\341\273\215n)", nullptr));
        box12->setText(QCoreApplication::translate("chooseToComparion", "Flash sort (S\341\272\257p x\341\272\277p ph\303\242n ph\341\273\221i)", nullptr));
        box3->setText(QCoreApplication::translate("chooseToComparion", "Insertion sort (S\341\272\257p x\341\272\277p ch\303\250n)", nullptr));
        box8->setText(QCoreApplication::translate("chooseToComparion", "Shell sort (S\341\272\257p x\341\272\277p v\341\273\217 s\303\262)", nullptr));
        box13->setText(QCoreApplication::translate("chooseToComparion", "Shaker Sort (S\341\272\257p x\341\272\277p cocktai)", nullptr));
        box4->setText(QCoreApplication::translate("chooseToComparion", "Interchange sort (S\341\272\257p x\341\272\277p \304\221\341\273\225i ch\341\273\227)", nullptr));
        box9->setText(QCoreApplication::translate("chooseToComparion", "Counting Sort (S\341\272\257p x\341\272\277p \304\221\341\272\277m)", nullptr));
        box14->setText(QCoreApplication::translate("chooseToComparion", "Cube sort (S\341\272\257p x\341\272\277p song song)", nullptr));
        box5->setText(QCoreApplication::translate("chooseToComparion", "Merge sort (S\341\272\257p x\341\272\277p tr\341\273\231n)", nullptr));
        box10->setText(QCoreApplication::translate("chooseToComparion", "Radix sort (S\341\272\257p x\341\272\277p theo c\306\241 s\341\273\221)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class chooseToComparion: public Ui_chooseToComparion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSETOCOMPARION_H
