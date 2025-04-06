/********************************************************************************
** Form generated from reading UI file 'outcomparion.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OUTCOMPARION_H
#define UI_OUTCOMPARION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_outComparion
{
public:
    QPushButton *btn_goHome;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QTableWidget *tableWidget;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *outComparion)
    {
        if (outComparion->objectName().isEmpty())
            outComparion->setObjectName("outComparion");
        outComparion->resize(766, 574);
        btn_goHome = new QPushButton(outComparion);
        btn_goHome->setObjectName("btn_goHome");
        btn_goHome->setEnabled(true);
        btn_goHome->setGeometry(QRect(730, 10, 31, 31));
        QFont font;
        font.setPointSize(12);
        btn_goHome->setFont(font);
        btn_goHome->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btn_goHome->setAutoFillBackground(false);
        btn_goHome->setStyleSheet(QString::fromUtf8("border-image: url(:/image/image/home_icon.png);"));
        widget = new QWidget(outComparion);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 90, 761, 411));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        tableWidget = new QTableWidget(widget);
        tableWidget->setObjectName("tableWidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy);
        tableWidget->setMinimumSize(QSize(551, 351));
        tableWidget->setMaximumSize(QSize(551, 351));
        QFont font1;
        font1.setPointSize(14);
        tableWidget->setFont(font1);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents);
        tableWidget->setDragDropOverwriteMode(true);
        tableWidget->setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerItem);
        tableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollMode::ScrollPerItem);
        tableWidget->horizontalHeader()->setVisible(true);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setMinimumSectionSize(45);
        tableWidget->horizontalHeader()->setDefaultSectionSize(150);
        tableWidget->horizontalHeader()->setHighlightSections(false);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setVisible(true);
        tableWidget->verticalHeader()->setCascadingSectionResizes(true);
        tableWidget->verticalHeader()->setMinimumSectionSize(34);
        tableWidget->verticalHeader()->setDefaultSectionSize(69);
        tableWidget->verticalHeader()->setProperty("showSortIndicator", QVariant(true));
        tableWidget->verticalHeader()->setStretchLastSection(false);

        horizontalLayout->addWidget(tableWidget);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        retranslateUi(outComparion);

        QMetaObject::connectSlotsByName(outComparion);
    } // setupUi

    void retranslateUi(QWidget *outComparion)
    {
        outComparion->setWindowTitle(QCoreApplication::translate("outComparion", "Form", nullptr));
        btn_goHome->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class outComparion: public Ui_outComparion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OUTCOMPARION_H
