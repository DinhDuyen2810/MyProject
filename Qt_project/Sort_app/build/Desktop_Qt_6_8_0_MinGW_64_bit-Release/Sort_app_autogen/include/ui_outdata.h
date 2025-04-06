/********************************************************************************
** Form generated from reading UI file 'outdata.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OUTDATA_H
#define UI_OUTDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_outData
{
public:
    QPlainTextEdit *txtoutPut;
    QPushButton *btn_goHome;
    QLabel *label;

    void setupUi(QWidget *outData)
    {
        if (outData->objectName().isEmpty())
            outData->setObjectName("outData");
        outData->resize(766, 574);
        txtoutPut = new QPlainTextEdit(outData);
        txtoutPut->setObjectName("txtoutPut");
        txtoutPut->setGeometry(QRect(30, 110, 711, 431));
        QFont font;
        font.setPointSize(10);
        txtoutPut->setFont(font);
        btn_goHome = new QPushButton(outData);
        btn_goHome->setObjectName("btn_goHome");
        btn_goHome->setEnabled(true);
        btn_goHome->setGeometry(QRect(730, 10, 31, 31));
        btn_goHome->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_goHome->setAutoFillBackground(false);
        btn_goHome->setStyleSheet(QString::fromUtf8("border-image: url(:/image/image/home_icon.png);"));
        label = new QLabel(outData);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 65, 261, 31));
        QFont font1;
        font1.setPointSize(12);
        label->setFont(font1);

        retranslateUi(outData);

        QMetaObject::connectSlotsByName(outData);
    } // setupUi

    void retranslateUi(QWidget *outData)
    {
        outData->setWindowTitle(QCoreApplication::translate("outData", "Form", nullptr));
        btn_goHome->setText(QString());
        label->setText(QCoreApplication::translate("outData", "D\341\273\257 li\341\273\207u sau khi b\341\272\241n s\341\272\257p x\341\272\277p l\303\240: ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class outData: public Ui_outData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OUTDATA_H
