/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *btnNumOne;
    QPushButton *btnNumFour;
    QPushButton *btnNumSeven;
    QPushButton *btnNumFive;
    QPushButton *btnNumEight;
    QPushButton *btnNumTwo;
    QPushButton *btnNumSix;
    QPushButton *btnNumNine;
    QPushButton *btnNumThree;
    QPushButton *btnMinus;
    QPushButton *btnMulti;
    QPushButton *btnPlus;
    QPushButton *btnNumZero;
    QPushButton *btnEqual;
    QPushButton *btnDel;
    QPushButton *btnDivine;
    QPushButton *btnUndo;
    QPushButton *btnExit;
    QPushButton *btnFParen;
    QPushButton *btnSParen;
    QPushButton *btnChangeBinary;
    QPushButton *btnPow;
    QLabel *lblNumber;
    QLineEdit *lineEdit;
    QMenuBar *menubar;
    QMenu *menuCalculator;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(335, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        btnNumOne = new QPushButton(centralwidget);
        btnNumOne->setObjectName("btnNumOne");
        btnNumOne->setGeometry(QRect(120, 220, 41, 31));
        QFont font;
        font.setPointSize(11);
        btnNumOne->setFont(font);
        btnNumFour = new QPushButton(centralwidget);
        btnNumFour->setObjectName("btnNumFour");
        btnNumFour->setGeometry(QRect(120, 260, 41, 31));
        btnNumFour->setFont(font);
        btnNumSeven = new QPushButton(centralwidget);
        btnNumSeven->setObjectName("btnNumSeven");
        btnNumSeven->setGeometry(QRect(120, 300, 41, 31));
        btnNumSeven->setFont(font);
        btnNumFive = new QPushButton(centralwidget);
        btnNumFive->setObjectName("btnNumFive");
        btnNumFive->setGeometry(QRect(180, 260, 41, 31));
        btnNumFive->setFont(font);
        btnNumEight = new QPushButton(centralwidget);
        btnNumEight->setObjectName("btnNumEight");
        btnNumEight->setGeometry(QRect(180, 300, 41, 31));
        btnNumEight->setFont(font);
        btnNumTwo = new QPushButton(centralwidget);
        btnNumTwo->setObjectName("btnNumTwo");
        btnNumTwo->setGeometry(QRect(180, 220, 41, 31));
        btnNumTwo->setFont(font);
        btnNumSix = new QPushButton(centralwidget);
        btnNumSix->setObjectName("btnNumSix");
        btnNumSix->setGeometry(QRect(240, 260, 41, 31));
        btnNumSix->setFont(font);
        btnNumNine = new QPushButton(centralwidget);
        btnNumNine->setObjectName("btnNumNine");
        btnNumNine->setGeometry(QRect(240, 300, 41, 31));
        btnNumNine->setFont(font);
        btnNumThree = new QPushButton(centralwidget);
        btnNumThree->setObjectName("btnNumThree");
        btnNumThree->setGeometry(QRect(240, 220, 41, 31));
        btnNumThree->setFont(font);
        btnMinus = new QPushButton(centralwidget);
        btnMinus->setObjectName("btnMinus");
        btnMinus->setGeometry(QRect(60, 260, 41, 31));
        btnMinus->setFont(font);
        btnMulti = new QPushButton(centralwidget);
        btnMulti->setObjectName("btnMulti");
        btnMulti->setGeometry(QRect(60, 300, 41, 31));
        btnMulti->setFont(font);
        btnPlus = new QPushButton(centralwidget);
        btnPlus->setObjectName("btnPlus");
        btnPlus->setGeometry(QRect(60, 220, 41, 31));
        btnPlus->setFont(font);
        btnNumZero = new QPushButton(centralwidget);
        btnNumZero->setObjectName("btnNumZero");
        btnNumZero->setGeometry(QRect(180, 340, 41, 31));
        btnNumZero->setFont(font);
        btnEqual = new QPushButton(centralwidget);
        btnEqual->setObjectName("btnEqual");
        btnEqual->setGeometry(QRect(240, 340, 41, 31));
        btnEqual->setFont(font);
        btnDel = new QPushButton(centralwidget);
        btnDel->setObjectName("btnDel");
        btnDel->setGeometry(QRect(120, 340, 41, 31));
        btnDel->setFont(font);
        btnDivine = new QPushButton(centralwidget);
        btnDivine->setObjectName("btnDivine");
        btnDivine->setGeometry(QRect(60, 340, 41, 31));
        btnDivine->setFont(font);
        btnUndo = new QPushButton(centralwidget);
        btnUndo->setObjectName("btnUndo");
        btnUndo->setGeometry(QRect(120, 180, 41, 31));
        btnUndo->setFont(font);
        btnExit = new QPushButton(centralwidget);
        btnExit->setObjectName("btnExit");
        btnExit->setGeometry(QRect(180, 380, 101, 31));
        btnFParen = new QPushButton(centralwidget);
        btnFParen->setObjectName("btnFParen");
        btnFParen->setGeometry(QRect(180, 180, 41, 31));
        btnFParen->setFont(font);
        btnSParen = new QPushButton(centralwidget);
        btnSParen->setObjectName("btnSParen");
        btnSParen->setGeometry(QRect(240, 180, 41, 31));
        btnSParen->setFont(font);
        btnChangeBinary = new QPushButton(centralwidget);
        btnChangeBinary->setObjectName("btnChangeBinary");
        btnChangeBinary->setGeometry(QRect(60, 380, 101, 31));
        btnPow = new QPushButton(centralwidget);
        btnPow->setObjectName("btnPow");
        btnPow->setGeometry(QRect(60, 180, 41, 31));
        btnPow->setFont(font);
        lblNumber = new QLabel(centralwidget);
        lblNumber->setObjectName("lblNumber");
        lblNumber->setGeometry(QRect(60, 120, 221, 41));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Agency FB")});
        font1.setPointSize(18);
        lblNumber->setFont(font1);
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(60, 80, 221, 41));
        lineEdit->setFont(font1);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 335, 22));
        menuCalculator = new QMenu(menubar);
        menuCalculator->setObjectName("menuCalculator");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuCalculator->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnNumOne->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        btnNumFour->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        btnNumSeven->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        btnNumFive->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        btnNumEight->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        btnNumTwo->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        btnNumSix->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        btnNumNine->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
        btnNumThree->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        btnMinus->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        btnMulti->setText(QCoreApplication::translate("MainWindow", "*", nullptr));
        btnPlus->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        btnNumZero->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        btnEqual->setText(QCoreApplication::translate("MainWindow", "=", nullptr));
        btnDel->setText(QCoreApplication::translate("MainWindow", "Del", nullptr));
        btnDivine->setText(QCoreApplication::translate("MainWindow", "/", nullptr));
        btnUndo->setText(QCoreApplication::translate("MainWindow", "\342\206\220", nullptr));
        btnExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        btnFParen->setText(QCoreApplication::translate("MainWindow", "(", nullptr));
        btnSParen->setText(QCoreApplication::translate("MainWindow", ")", nullptr));
        btnChangeBinary->setText(QCoreApplication::translate("MainWindow", "Change Binary", nullptr));
        btnPow->setText(QCoreApplication::translate("MainWindow", "^", nullptr));
        lblNumber->setText(QString());
        menuCalculator->setTitle(QCoreApplication::translate("MainWindow", "Calculator", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
