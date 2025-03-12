/********************************************************************************
** Form generated from reading UI file 'main_sort.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_SORT_H
#define UI_MAIN_SORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_main_sort
{
public:
    QPushButton *btn_goHome;
    QPushButton *btn_goBack_mainsort;
    QLabel *lblMainSort;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QPushButton *btn_chooseSort;
    QPushButton *btn_comparison;
    QPushButton *btn_information;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *main_sort)
    {
        if (main_sort->objectName().isEmpty())
            main_sort->setObjectName("main_sort");
        main_sort->resize(766, 574);
        btn_goHome = new QPushButton(main_sort);
        btn_goHome->setObjectName("btn_goHome");
        btn_goHome->setEnabled(true);
        btn_goHome->setGeometry(QRect(730, 10, 31, 31));
        btn_goHome->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_goHome->setAutoFillBackground(false);
        btn_goHome->setStyleSheet(QString::fromUtf8("border-image: url(:/image/image/home_icon.png);"));
        btn_goBack_mainsort = new QPushButton(main_sort);
        btn_goBack_mainsort->setObjectName("btn_goBack_mainsort");
        btn_goBack_mainsort->setGeometry(QRect(10, 20, 21, 16));
        btn_goBack_mainsort->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_goBack_mainsort->setStyleSheet(QString::fromUtf8("border-image: url(:/image/image/back.png);"));
        lblMainSort = new QLabel(main_sort);
        lblMainSort->setObjectName("lblMainSort");
        lblMainSort->setGeometry(QRect(46, 9, 165, 32));
        QFont font;
        font.setPointSize(14);
        lblMainSort->setFont(font);
        lblMainSort->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        widget = new QWidget(main_sort);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 160, 761, 301));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(170, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(30);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, -1, -1, -1);
        btn_chooseSort = new QPushButton(widget);
        btn_chooseSort->setObjectName("btn_chooseSort");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(30);
        sizePolicy.setVerticalStretch(30);
        sizePolicy.setHeightForWidth(btn_chooseSort->sizePolicy().hasHeightForWidth());
        btn_chooseSort->setSizePolicy(sizePolicy);
        btn_chooseSort->setMinimumSize(QSize(50, 20));
        QFont font1;
        font1.setPointSize(16);
        btn_chooseSort->setFont(font1);
        btn_chooseSort->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_chooseSort->setStyleSheet(QString::fromUtf8("background-color: rgb(185, 185, 185);\n"
""));

        verticalLayout->addWidget(btn_chooseSort);

        btn_comparison = new QPushButton(widget);
        btn_comparison->setObjectName("btn_comparison");
        sizePolicy.setHeightForWidth(btn_comparison->sizePolicy().hasHeightForWidth());
        btn_comparison->setSizePolicy(sizePolicy);
        btn_comparison->setMinimumSize(QSize(50, 20));
        btn_comparison->setFont(font1);
        btn_comparison->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_comparison->setStyleSheet(QString::fromUtf8("background-color: rgb(185, 185, 185);\n"
"\n"
""));

        verticalLayout->addWidget(btn_comparison);

        btn_information = new QPushButton(widget);
        btn_information->setObjectName("btn_information");
        sizePolicy.setHeightForWidth(btn_information->sizePolicy().hasHeightForWidth());
        btn_information->setSizePolicy(sizePolicy);
        btn_information->setMinimumSize(QSize(50, 20));
        btn_information->setFont(font1);
        btn_information->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_information->setStyleSheet(QString::fromUtf8("background-color: rgb(185, 185, 185);\n"
""));

        verticalLayout->addWidget(btn_information);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer_2 = new QSpacerItem(170, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        retranslateUi(main_sort);

        QMetaObject::connectSlotsByName(main_sort);
    } // setupUi

    void retranslateUi(QWidget *main_sort)
    {
        main_sort->setWindowTitle(QCoreApplication::translate("main_sort", "Form", nullptr));
        btn_goHome->setText(QString());
        btn_goBack_mainsort->setText(QString());
        lblMainSort->setText(QCoreApplication::translate("main_sort", "Sort Application", nullptr));
        btn_chooseSort->setText(QCoreApplication::translate("main_sort", "S\341\272\257p x\341\272\277p d\341\273\257 li\341\273\207u", nullptr));
        btn_comparison->setText(QCoreApplication::translate("main_sort", "So s\303\241nh thu\341\272\255t to\303\241n", nullptr));
        btn_information->setText(QCoreApplication::translate("main_sort", "Th\303\264ng tin chi ti\341\272\277t", nullptr));
    } // retranslateUi

};

namespace Ui {
    class main_sort: public Ui_main_sort {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_SORT_H
