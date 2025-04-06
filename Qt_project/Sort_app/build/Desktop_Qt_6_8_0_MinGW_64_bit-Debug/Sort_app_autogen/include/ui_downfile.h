/********************************************************************************
** Form generated from reading UI file 'downfile.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOWNFILE_H
#define UI_DOWNFILE_H

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

class Ui_downFile
{
public:
    QPushButton *btn_goHome;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_downFile;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QLabel *lbl_ready;

    void setupUi(QWidget *downFile)
    {
        if (downFile->objectName().isEmpty())
            downFile->setObjectName("downFile");
        downFile->resize(766, 574);
        btn_goHome = new QPushButton(downFile);
        btn_goHome->setObjectName("btn_goHome");
        btn_goHome->setEnabled(true);
        btn_goHome->setGeometry(QRect(730, 10, 31, 31));
        btn_goHome->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_goHome->setAutoFillBackground(false);
        btn_goHome->setStyleSheet(QString::fromUtf8("border-image: url(:/image/image/home_icon.png);"));
        layoutWidget = new QWidget(downFile);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(170, 70, 441, 371));
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
        horizontalSpacer = new QSpacerItem(120, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn_downFile = new QPushButton(frame);
        btn_downFile->setObjectName("btn_downFile");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btn_downFile->sizePolicy().hasHeightForWidth());
        btn_downFile->setSizePolicy(sizePolicy);
        btn_downFile->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_downFile->setStyleSheet(QString::fromUtf8("border-image: url(:/image/image/up-loading.png);\n"
"border-image: url(:/image/image/downloads.png);"));

        horizontalLayout->addWidget(btn_downFile);

        horizontalSpacer_2 = new QSpacerItem(120, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(frame);

        label = new QLabel(layoutWidget);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(20);
        label->setFont(font);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label);

        lbl_ready = new QLabel(downFile);
        lbl_ready->setObjectName("lbl_ready");
        lbl_ready->setGeometry(QRect(10, 440, 731, 41));
        QFont font1;
        font1.setPointSize(12);
        lbl_ready->setFont(font1);

        retranslateUi(downFile);

        QMetaObject::connectSlotsByName(downFile);
    } // setupUi

    void retranslateUi(QWidget *downFile)
    {
        downFile->setWindowTitle(QCoreApplication::translate("downFile", "Form", nullptr));
        btn_goHome->setText(QString());
        btn_downFile->setText(QString());
        label->setText(QCoreApplication::translate("downFile", "DownLoad Your File", nullptr));
        lbl_ready->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class downFile: public Ui_downFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOWNFILE_H
