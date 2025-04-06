/********************************************************************************
** Form generated from reading UI file 'choosesort.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSESORT_H
#define UI_CHOOSESORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chooseSort
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QFrame *frame_2;
    QPushButton *btn_goHome;
    QPushButton *btn_goBack_choosesort;
    QLabel *lblMainSort;
    QFrame *frame;
    QLabel *label;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QPushButton *btn_Sort_8;
    QPushButton *btn_Sort_7;
    QPushButton *btn_Sort_10;
    QPushButton *btn_Sort_4;
    QPushButton *btn_Sort_14;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_Sort_5;
    QSpacerItem *verticalSpacer;
    QPushButton *btn_Sort_11;
    QPushButton *btn_Sort_1;
    QPushButton *btn_Sort_13;
    QPushButton *btn_Sort_3;
    QPushButton *btn_Sort_12;
    QPushButton *btn_Sort_6;
    QPushButton *btn_Sort_9;
    QPushButton *btn_Sort_2;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *chooseSort)
    {
        if (chooseSort->objectName().isEmpty())
            chooseSort->setObjectName("chooseSort");
        chooseSort->resize(766, 574);
        verticalLayout_2 = new QVBoxLayout(chooseSort);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(-1, 9, -1, 18);
        frame_2 = new QFrame(chooseSort);
        frame_2->setObjectName("frame_2");
        frame_2->setMinimumSize(QSize(50, 50));
        QFont font;
        font.setPointSize(12);
        frame_2->setFont(font);
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        btn_goHome = new QPushButton(frame_2);
        btn_goHome->setObjectName("btn_goHome");
        btn_goHome->setEnabled(true);
        btn_goHome->setGeometry(QRect(710, 10, 31, 31));
        btn_goHome->setFont(font);
        btn_goHome->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_goHome->setAutoFillBackground(false);
        btn_goHome->setStyleSheet(QString::fromUtf8("border-image: url(:/image/image/home_icon.png);"));
        btn_goBack_choosesort = new QPushButton(frame_2);
        btn_goBack_choosesort->setObjectName("btn_goBack_choosesort");
        btn_goBack_choosesort->setGeometry(QRect(10, 10, 21, 16));
        btn_goBack_choosesort->setFont(font);
        btn_goBack_choosesort->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_goBack_choosesort->setStyleSheet(QString::fromUtf8("border-image: url(:/image/image/back.png);"));
        lblMainSort = new QLabel(frame_2);
        lblMainSort->setObjectName("lblMainSort");
        lblMainSort->setGeometry(QRect(40, 0, 201, 31));
        QFont font1;
        font1.setPointSize(14);
        lblMainSort->setFont(font1);
        lblMainSort->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        verticalLayout->addWidget(frame_2);

        frame = new QFrame(chooseSort);
        frame->setObjectName("frame");
        frame->setMinimumSize(QSize(50, 50));
        frame->setFont(font);
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 20, 380, 21));
        QFont font2;
        font2.setPointSize(16);
        label->setFont(font2);
        label->setAlignment(Qt::AlignmentFlag::AlignBottom|Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft);

        verticalLayout->addWidget(frame);


        verticalLayout_2->addLayout(verticalLayout);

        scrollArea = new QScrollArea(chooseSort);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setFont(font);
        scrollArea->setFrameShape(QFrame::Shape::NoFrame);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 731, 980));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinAndMaxSize);
        gridLayout->setHorizontalSpacing(6);
        gridLayout->setVerticalSpacing(20);
        gridLayout->setContentsMargins(20, 0, 20, 0);
        btn_Sort_8 = new QPushButton(scrollAreaWidgetContents);
        btn_Sort_8->setObjectName("btn_Sort_8");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btn_Sort_8->sizePolicy().hasHeightForWidth());
        btn_Sort_8->setSizePolicy(sizePolicy);
        btn_Sort_8->setMinimumSize(QSize(300, 50));
        btn_Sort_8->setFont(font);
        btn_Sort_8->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_Sort_8->setStyleSheet(QString::fromUtf8("background-color: rgb(182, 182, 182);"));

        gridLayout->addWidget(btn_Sort_8, 8, 1, 1, 1);

        btn_Sort_7 = new QPushButton(scrollAreaWidgetContents);
        btn_Sort_7->setObjectName("btn_Sort_7");
        sizePolicy.setHeightForWidth(btn_Sort_7->sizePolicy().hasHeightForWidth());
        btn_Sort_7->setSizePolicy(sizePolicy);
        btn_Sort_7->setMinimumSize(QSize(300, 50));
        btn_Sort_7->setFont(font);
        btn_Sort_7->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_Sort_7->setStyleSheet(QString::fromUtf8("background-color: rgb(182, 182, 182);"));

        gridLayout->addWidget(btn_Sort_7, 7, 1, 1, 1);

        btn_Sort_10 = new QPushButton(scrollAreaWidgetContents);
        btn_Sort_10->setObjectName("btn_Sort_10");
        sizePolicy.setHeightForWidth(btn_Sort_10->sizePolicy().hasHeightForWidth());
        btn_Sort_10->setSizePolicy(sizePolicy);
        btn_Sort_10->setMinimumSize(QSize(300, 50));
        btn_Sort_10->setFont(font);
        btn_Sort_10->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_Sort_10->setStyleSheet(QString::fromUtf8("background-color: rgb(182, 182, 182);"));

        gridLayout->addWidget(btn_Sort_10, 10, 1, 1, 1);

        btn_Sort_4 = new QPushButton(scrollAreaWidgetContents);
        btn_Sort_4->setObjectName("btn_Sort_4");
        sizePolicy.setHeightForWidth(btn_Sort_4->sizePolicy().hasHeightForWidth());
        btn_Sort_4->setSizePolicy(sizePolicy);
        btn_Sort_4->setMinimumSize(QSize(300, 50));
        btn_Sort_4->setFont(font);
        btn_Sort_4->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_Sort_4->setStyleSheet(QString::fromUtf8("background-color: rgb(182, 182, 182);\n"
""));

        gridLayout->addWidget(btn_Sort_4, 4, 1, 1, 1);

        btn_Sort_14 = new QPushButton(scrollAreaWidgetContents);
        btn_Sort_14->setObjectName("btn_Sort_14");
        btn_Sort_14->setMinimumSize(QSize(300, 50));
        btn_Sort_14->setFont(font);
        btn_Sort_14->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_Sort_14->setStyleSheet(QString::fromUtf8("background-color: rgb(182, 182, 182);"));

        gridLayout->addWidget(btn_Sort_14, 14, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(100, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        btn_Sort_5 = new QPushButton(scrollAreaWidgetContents);
        btn_Sort_5->setObjectName("btn_Sort_5");
        sizePolicy.setHeightForWidth(btn_Sort_5->sizePolicy().hasHeightForWidth());
        btn_Sort_5->setSizePolicy(sizePolicy);
        btn_Sort_5->setMinimumSize(QSize(300, 50));
        btn_Sort_5->setFont(font);
        btn_Sort_5->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_Sort_5->setStyleSheet(QString::fromUtf8("background-color: rgb(182, 182, 182);"));

        gridLayout->addWidget(btn_Sort_5, 5, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer, 15, 1, 1, 1);

        btn_Sort_11 = new QPushButton(scrollAreaWidgetContents);
        btn_Sort_11->setObjectName("btn_Sort_11");
        sizePolicy.setHeightForWidth(btn_Sort_11->sizePolicy().hasHeightForWidth());
        btn_Sort_11->setSizePolicy(sizePolicy);
        btn_Sort_11->setMinimumSize(QSize(300, 50));
        btn_Sort_11->setFont(font);
        btn_Sort_11->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_Sort_11->setStyleSheet(QString::fromUtf8("background-color: rgb(182, 182, 182);"));

        gridLayout->addWidget(btn_Sort_11, 11, 1, 1, 1);

        btn_Sort_1 = new QPushButton(scrollAreaWidgetContents);
        btn_Sort_1->setObjectName("btn_Sort_1");
        sizePolicy.setHeightForWidth(btn_Sort_1->sizePolicy().hasHeightForWidth());
        btn_Sort_1->setSizePolicy(sizePolicy);
        btn_Sort_1->setMinimumSize(QSize(300, 50));
        btn_Sort_1->setFont(font);
        btn_Sort_1->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_Sort_1->setStyleSheet(QString::fromUtf8("background-color: rgb(182, 182, 182);"));

        gridLayout->addWidget(btn_Sort_1, 1, 1, 1, 1);

        btn_Sort_13 = new QPushButton(scrollAreaWidgetContents);
        btn_Sort_13->setObjectName("btn_Sort_13");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btn_Sort_13->sizePolicy().hasHeightForWidth());
        btn_Sort_13->setSizePolicy(sizePolicy1);
        btn_Sort_13->setMinimumSize(QSize(300, 50));
        btn_Sort_13->setFont(font);
        btn_Sort_13->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_Sort_13->setStyleSheet(QString::fromUtf8("background-color: rgb(182, 182, 182);"));

        gridLayout->addWidget(btn_Sort_13, 13, 1, 1, 1);

        btn_Sort_3 = new QPushButton(scrollAreaWidgetContents);
        btn_Sort_3->setObjectName("btn_Sort_3");
        sizePolicy.setHeightForWidth(btn_Sort_3->sizePolicy().hasHeightForWidth());
        btn_Sort_3->setSizePolicy(sizePolicy);
        btn_Sort_3->setMinimumSize(QSize(300, 50));
        btn_Sort_3->setFont(font);
        btn_Sort_3->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_Sort_3->setStyleSheet(QString::fromUtf8("background-color: rgb(182, 182, 182);"));

        gridLayout->addWidget(btn_Sort_3, 3, 1, 1, 1);

        btn_Sort_12 = new QPushButton(scrollAreaWidgetContents);
        btn_Sort_12->setObjectName("btn_Sort_12");
        sizePolicy.setHeightForWidth(btn_Sort_12->sizePolicy().hasHeightForWidth());
        btn_Sort_12->setSizePolicy(sizePolicy);
        btn_Sort_12->setMinimumSize(QSize(300, 50));
        btn_Sort_12->setFont(font);
        btn_Sort_12->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_Sort_12->setStyleSheet(QString::fromUtf8("background-color: rgb(182, 182, 182);"));

        gridLayout->addWidget(btn_Sort_12, 12, 1, 1, 1);

        btn_Sort_6 = new QPushButton(scrollAreaWidgetContents);
        btn_Sort_6->setObjectName("btn_Sort_6");
        sizePolicy.setHeightForWidth(btn_Sort_6->sizePolicy().hasHeightForWidth());
        btn_Sort_6->setSizePolicy(sizePolicy);
        btn_Sort_6->setMinimumSize(QSize(300, 50));
        btn_Sort_6->setFont(font);
        btn_Sort_6->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_Sort_6->setStyleSheet(QString::fromUtf8("background-color: rgb(182, 182, 182);"));

        gridLayout->addWidget(btn_Sort_6, 6, 1, 1, 1);

        btn_Sort_9 = new QPushButton(scrollAreaWidgetContents);
        btn_Sort_9->setObjectName("btn_Sort_9");
        sizePolicy.setHeightForWidth(btn_Sort_9->sizePolicy().hasHeightForWidth());
        btn_Sort_9->setSizePolicy(sizePolicy);
        btn_Sort_9->setMinimumSize(QSize(300, 50));
        btn_Sort_9->setFont(font);
        btn_Sort_9->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_Sort_9->setStyleSheet(QString::fromUtf8("background-color: rgb(182, 182, 182);"));

        gridLayout->addWidget(btn_Sort_9, 9, 1, 1, 1);

        btn_Sort_2 = new QPushButton(scrollAreaWidgetContents);
        btn_Sort_2->setObjectName("btn_Sort_2");
        sizePolicy.setHeightForWidth(btn_Sort_2->sizePolicy().hasHeightForWidth());
        btn_Sort_2->setSizePolicy(sizePolicy);
        btn_Sort_2->setMinimumSize(QSize(300, 50));
        btn_Sort_2->setFont(font);
        btn_Sort_2->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_Sort_2->setStyleSheet(QString::fromUtf8("background-color: rgb(182, 182, 182);"));

        gridLayout->addWidget(btn_Sort_2, 2, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(100, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 2, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);


        retranslateUi(chooseSort);

        QMetaObject::connectSlotsByName(chooseSort);
    } // setupUi

    void retranslateUi(QWidget *chooseSort)
    {
        chooseSort->setWindowTitle(QCoreApplication::translate("chooseSort", "Form", nullptr));
        btn_goHome->setText(QString());
        btn_goBack_choosesort->setText(QString());
        lblMainSort->setText(QCoreApplication::translate("chooseSort", "S\341\272\257p x\341\272\277p d\341\273\257 li\341\273\207u", nullptr));
        label->setText(QCoreApplication::translate("chooseSort", "Vui l\303\262ng l\341\273\261a ch\341\273\215n thu\341\272\255t to\303\241n:", nullptr));
        btn_Sort_8->setText(QCoreApplication::translate("chooseSort", "Shell sort (S\341\272\257p x\341\272\277p v\341\273\217 s\303\262)", nullptr));
        btn_Sort_7->setText(QCoreApplication::translate("chooseSort", "Selection sort (S\341\272\257p x\341\272\277p ch\341\273\215n)", nullptr));
        btn_Sort_10->setText(QCoreApplication::translate("chooseSort", "Radix sort (S\341\272\257p x\341\272\277p theo c\306\241 s\341\273\221)", nullptr));
        btn_Sort_4->setText(QCoreApplication::translate("chooseSort", "Interchange sort (S\341\272\257p x\341\272\277p \304\221\341\273\225i ch\341\273\227)", nullptr));
        btn_Sort_14->setText(QCoreApplication::translate("chooseSort", "Cube sort (S\341\272\257p x\341\272\277p song song)", nullptr));
        btn_Sort_5->setText(QCoreApplication::translate("chooseSort", "Merge sort (S\341\272\257p x\341\272\277p tr\341\273\231n)", nullptr));
        btn_Sort_11->setText(QCoreApplication::translate("chooseSort", "Bucket sort (S\341\272\257p x\341\272\277p th\303\271ng)", nullptr));
        btn_Sort_1->setText(QCoreApplication::translate("chooseSort", "Bubble sort (S\341\272\257p x\341\272\277p n\341\273\225i b\341\273\215t)", nullptr));
        btn_Sort_13->setText(QCoreApplication::translate("chooseSort", "Shaker Sort (S\341\272\257p x\341\272\277p cocktai)", nullptr));
        btn_Sort_3->setText(QCoreApplication::translate("chooseSort", "Insertion sort (S\341\272\257p x\341\272\277p ch\303\250n)", nullptr));
        btn_Sort_12->setText(QCoreApplication::translate("chooseSort", "Flash sort (S\341\272\257p x\341\272\277p ph\303\242n ph\341\273\221i)", nullptr));
        btn_Sort_6->setText(QCoreApplication::translate("chooseSort", "Quick sort (S\341\272\257p x\341\272\277p nhanh)", nullptr));
        btn_Sort_9->setText(QCoreApplication::translate("chooseSort", "Counting Sort (S\341\272\257p x\341\272\277p \304\221\341\272\277m)", nullptr));
        btn_Sort_2->setText(QCoreApplication::translate("chooseSort", "Heap sort (S\341\272\257p x\341\272\277p vun \304\221\341\273\221ng)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class chooseSort: public Ui_chooseSort {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSESORT_H
