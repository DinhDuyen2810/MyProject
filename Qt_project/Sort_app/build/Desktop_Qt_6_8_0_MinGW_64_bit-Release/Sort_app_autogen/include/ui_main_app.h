/********************************************************************************
** Form generated from reading UI file 'main_app.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_APP_H
#define UI_MAIN_APP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_main_app
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *lbl_main_app;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btn_main_start;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *main_app)
    {
        if (main_app->objectName().isEmpty())
            main_app->setObjectName("main_app");
        main_app->resize(766, 574);
        widget = new QWidget(main_app);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 170, 761, 91));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        lbl_main_app = new QLabel(widget);
        lbl_main_app->setObjectName("lbl_main_app");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lbl_main_app->sizePolicy().hasHeightForWidth());
        lbl_main_app->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(48);
        lbl_main_app->setFont(font);
        lbl_main_app->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        lbl_main_app->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        lbl_main_app->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout->addWidget(lbl_main_app);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        widget1 = new QWidget(main_app);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(0, 360, 761, 91));
        horizontalLayout_2 = new QHBoxLayout(widget1);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_3 = new QSpacerItem(250, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        btn_main_start = new QPushButton(widget1);
        btn_main_start->setObjectName("btn_main_start");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Rockwell")});
        font1.setPointSize(26);
        btn_main_start->setFont(font1);
        btn_main_start->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_main_start->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 85, 255);\n"
"background-color: rgb(185, 185, 185);\n"
""));

        horizontalLayout_2->addWidget(btn_main_start);

        horizontalSpacer_4 = new QSpacerItem(250, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        retranslateUi(main_app);

        QMetaObject::connectSlotsByName(main_app);
    } // setupUi

    void retranslateUi(QWidget *main_app)
    {
        main_app->setWindowTitle(QCoreApplication::translate("main_app", "Form", nullptr));
        lbl_main_app->setText(QCoreApplication::translate("main_app", "Sort Application", nullptr));
        btn_main_start->setText(QCoreApplication::translate("main_app", "Start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class main_app: public Ui_main_app {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_APP_H
