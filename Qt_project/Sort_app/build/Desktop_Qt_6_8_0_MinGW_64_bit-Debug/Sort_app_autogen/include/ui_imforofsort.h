/********************************************************************************
** Form generated from reading UI file 'imforofsort.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMFOROFSORT_H
#define UI_IMFOROFSORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_imforOfSort
{
public:
    QPushButton *btn_goHome;
    QPushButton *btn_goBack_mainsort;
    QLabel *lbInforSort;

    void setupUi(QWidget *imforOfSort)
    {
        if (imforOfSort->objectName().isEmpty())
            imforOfSort->setObjectName("imforOfSort");
        imforOfSort->resize(400, 574);
        btn_goHome = new QPushButton(imforOfSort);
        btn_goHome->setObjectName("btn_goHome");
        btn_goHome->setEnabled(true);
        btn_goHome->setGeometry(QRect(364, 11, 31, 31));
        btn_goHome->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_goHome->setAutoFillBackground(false);
        btn_goHome->setStyleSheet(QString::fromUtf8("border-image: url(:/image/image/home_icon.png);"));
        btn_goBack_mainsort = new QPushButton(imforOfSort);
        btn_goBack_mainsort->setObjectName("btn_goBack_mainsort");
        btn_goBack_mainsort->setGeometry(QRect(4, 21, 21, 16));
        btn_goBack_mainsort->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_goBack_mainsort->setStyleSheet(QString::fromUtf8("border-image: url(:/image/image/back.png);"));
        lbInforSort = new QLabel(imforOfSort);
        lbInforSort->setObjectName("lbInforSort");
        lbInforSort->setGeometry(QRect(40, 10, 165, 32));
        QFont font;
        font.setPointSize(14);
        lbInforSort->setFont(font);
        lbInforSort->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        retranslateUi(imforOfSort);

        QMetaObject::connectSlotsByName(imforOfSort);
    } // setupUi

    void retranslateUi(QWidget *imforOfSort)
    {
        imforOfSort->setWindowTitle(QCoreApplication::translate("imforOfSort", "Form", nullptr));
        btn_goHome->setText(QString());
        btn_goBack_mainsort->setText(QString());
        lbInforSort->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class imforOfSort: public Ui_imforOfSort {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMFOROFSORT_H
