/********************************************************************************
** Form generated from reading UI file 'selectsort.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTSORT_H
#define UI_SELECTSORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_selectSort
{
public:
    QPushButton *btn_goHome;
    QPushButton *btn_goBack_selectsort;
    QLabel *lblNameOfSort;
    QLabel *label;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QPushButton *btn_chooseUpFile;
    QPushButton *btn_chooseWrite;
    QPushButton *btn_chooseRandom;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *selectSort)
    {
        if (selectSort->objectName().isEmpty())
            selectSort->setObjectName("selectSort");
        selectSort->resize(766, 574);
        btn_goHome = new QPushButton(selectSort);
        btn_goHome->setObjectName("btn_goHome");
        btn_goHome->setEnabled(true);
        btn_goHome->setGeometry(QRect(730, 10, 31, 31));
        btn_goHome->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_goHome->setAutoFillBackground(false);
        btn_goHome->setStyleSheet(QString::fromUtf8("border-image: url(:/image/image/home_icon.png);"));
        btn_goBack_selectsort = new QPushButton(selectSort);
        btn_goBack_selectsort->setObjectName("btn_goBack_selectsort");
        btn_goBack_selectsort->setGeometry(QRect(10, 20, 21, 16));
        btn_goBack_selectsort->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_goBack_selectsort->setStyleSheet(QString::fromUtf8("border-image: url(:/image/image/back.png);"));
        lblNameOfSort = new QLabel(selectSort);
        lblNameOfSort->setObjectName("lblNameOfSort");
        lblNameOfSort->setGeometry(QRect(46, 9, 301, 32));
        QFont font;
        font.setPointSize(14);
        lblNameOfSort->setFont(font);
        lblNameOfSort->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        label = new QLabel(selectSort);
        label->setObjectName("label");
        label->setGeometry(QRect(70, 120, 411, 31));
        label->setFont(font);
        widget = new QWidget(selectSort);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 200, 761, 301));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(170, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(19);
        verticalLayout->setObjectName("verticalLayout");
        btn_chooseUpFile = new QPushButton(widget);
        btn_chooseUpFile->setObjectName("btn_chooseUpFile");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btn_chooseUpFile->sizePolicy().hasHeightForWidth());
        btn_chooseUpFile->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setPointSize(16);
        btn_chooseUpFile->setFont(font1);
        btn_chooseUpFile->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_chooseUpFile->setStyleSheet(QString::fromUtf8("background-color: rgb(184, 184, 184);"));

        verticalLayout->addWidget(btn_chooseUpFile);

        btn_chooseWrite = new QPushButton(widget);
        btn_chooseWrite->setObjectName("btn_chooseWrite");
        sizePolicy.setHeightForWidth(btn_chooseWrite->sizePolicy().hasHeightForWidth());
        btn_chooseWrite->setSizePolicy(sizePolicy);
        btn_chooseWrite->setFont(font1);
        btn_chooseWrite->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_chooseWrite->setStyleSheet(QString::fromUtf8("background-color: rgb(184, 184, 184);"));

        verticalLayout->addWidget(btn_chooseWrite);

        btn_chooseRandom = new QPushButton(widget);
        btn_chooseRandom->setObjectName("btn_chooseRandom");
        sizePolicy.setHeightForWidth(btn_chooseRandom->sizePolicy().hasHeightForWidth());
        btn_chooseRandom->setSizePolicy(sizePolicy);
        btn_chooseRandom->setFont(font1);
        btn_chooseRandom->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_chooseRandom->setStyleSheet(QString::fromUtf8("background-color: rgb(184, 184, 184);"));

        verticalLayout->addWidget(btn_chooseRandom);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer_2 = new QSpacerItem(170, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        retranslateUi(selectSort);

        QMetaObject::connectSlotsByName(selectSort);
    } // setupUi

    void retranslateUi(QWidget *selectSort)
    {
        selectSort->setWindowTitle(QCoreApplication::translate("selectSort", "Form", nullptr));
        btn_goHome->setText(QString());
        btn_goBack_selectsort->setText(QString());
        lblNameOfSort->setText(QString());
        label->setText(QCoreApplication::translate("selectSort", "B\341\272\241n l\341\273\261a ch\341\273\215n ph\306\260\306\241ng th\341\273\251c n\303\240o?", nullptr));
        btn_chooseUpFile->setText(QCoreApplication::translate("selectSort", "T\341\272\243i l\303\252n File", nullptr));
        btn_chooseWrite->setText(QCoreApplication::translate("selectSort", "T\341\273\261 nh\341\272\255p", nullptr));
        btn_chooseRandom->setText(QCoreApplication::translate("selectSort", "Random", nullptr));
    } // retranslateUi

};

namespace Ui {
    class selectSort: public Ui_selectSort {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTSORT_H
