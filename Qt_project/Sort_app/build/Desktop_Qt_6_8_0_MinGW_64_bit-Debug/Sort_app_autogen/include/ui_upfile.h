/********************************************************************************
** Form generated from reading UI file 'upfile.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPFILE_H
#define UI_UPFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_upFile
{
public:
    QPushButton *btn_goBack_upFile;
    QPushButton *btn_goHome;
    QLabel *lblNameOfSort;
    QPushButton *btn_start_sort;
    QLabel *lbl_ready;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_upFile;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;

    void setupUi(QWidget *upFile)
    {
        if (upFile->objectName().isEmpty())
            upFile->setObjectName("upFile");
        upFile->resize(766, 574);
        btn_goBack_upFile = new QPushButton(upFile);
        btn_goBack_upFile->setObjectName("btn_goBack_upFile");
        btn_goBack_upFile->setGeometry(QRect(10, 20, 21, 16));
        btn_goBack_upFile->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_goBack_upFile->setStyleSheet(QString::fromUtf8("border-image: url(:/image/image/back.png);"));
        btn_goHome = new QPushButton(upFile);
        btn_goHome->setObjectName("btn_goHome");
        btn_goHome->setEnabled(true);
        btn_goHome->setGeometry(QRect(730, 10, 31, 31));
        btn_goHome->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_goHome->setAutoFillBackground(false);
        btn_goHome->setStyleSheet(QString::fromUtf8("border-image: url(:/image/image/home_icon.png);"));
        lblNameOfSort = new QLabel(upFile);
        lblNameOfSort->setObjectName("lblNameOfSort");
        lblNameOfSort->setGeometry(QRect(46, 9, 301, 32));
        QFont font;
        font.setPointSize(14);
        lblNameOfSort->setFont(font);
        lblNameOfSort->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        btn_start_sort = new QPushButton(upFile);
        btn_start_sort->setObjectName("btn_start_sort");
        btn_start_sort->setGeometry(QRect(350, 440, 81, 41));
        QFont font1;
        font1.setPointSize(22);
        btn_start_sort->setFont(font1);
        btn_start_sort->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_start_sort->setStyleSheet(QString::fromUtf8("background-color: rgb(184, 184, 184);"));
        lbl_ready = new QLabel(upFile);
        lbl_ready->setObjectName("lbl_ready");
        lbl_ready->setGeometry(QRect(20, 490, 731, 41));
        QFont font2;
        font2.setPointSize(18);
        lbl_ready->setFont(font2);
        lbl_ready->setAlignment(Qt::AlignmentFlag::AlignCenter);
        layoutWidget = new QWidget(upFile);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(170, 110, 441, 301));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        frame = new QFrame(layoutWidget);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(130, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn_upFile = new QPushButton(frame);
        btn_upFile->setObjectName("btn_upFile");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btn_upFile->sizePolicy().hasHeightForWidth());
        btn_upFile->setSizePolicy(sizePolicy);
        btn_upFile->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_upFile->setStyleSheet(QString::fromUtf8("border-image: url(:/image/image/up-loading.png);"));

        horizontalLayout->addWidget(btn_upFile);

        horizontalSpacer_2 = new QSpacerItem(130, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(frame);

        label = new QLabel(layoutWidget);
        label->setObjectName("label");
        QFont font3;
        font3.setPointSize(20);
        label->setFont(font3);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label);


        retranslateUi(upFile);

        QMetaObject::connectSlotsByName(upFile);
    } // setupUi

    void retranslateUi(QWidget *upFile)
    {
        upFile->setWindowTitle(QCoreApplication::translate("upFile", "Form", nullptr));
        btn_goBack_upFile->setText(QString());
        btn_goHome->setText(QString());
        lblNameOfSort->setText(QCoreApplication::translate("upFile", "T\341\272\243i l\303\252n File", nullptr));
        btn_start_sort->setText(QCoreApplication::translate("upFile", "Sort", nullptr));
        lbl_ready->setText(QString());
        btn_upFile->setText(QString());
        label->setText(QCoreApplication::translate("upFile", "UpLoad Your File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class upFile: public Ui_upFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPFILE_H
