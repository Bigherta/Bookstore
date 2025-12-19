/********************************************************************************
** Form generated from reading UI file 'report.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPORT_H
#define UI_REPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ReportDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *hLayoutFinance;
    QSpacerItem *leftSpacer1;
    QPushButton *pushButton;
    QSpacerItem *rightSpacer1;
    QHBoxLayout *hLayoutEmployee;
    QSpacerItem *leftSpacer2;
    QPushButton *pushButton_2;
    QSpacerItem *rightSpacer2;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        hLayoutFinance = new QHBoxLayout();
        hLayoutFinance->setObjectName(QString::fromUtf8("hLayoutFinance"));
        leftSpacer1 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hLayoutFinance->addItem(leftSpacer1);

        pushButton = new QPushButton(Dialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(80, 23));

        hLayoutFinance->addWidget(pushButton);

        rightSpacer1 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hLayoutFinance->addItem(rightSpacer1);


        verticalLayout->addLayout(hLayoutFinance);

        hLayoutEmployee = new QHBoxLayout();
        hLayoutEmployee->setObjectName(QString::fromUtf8("hLayoutEmployee"));
        leftSpacer2 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hLayoutEmployee->addItem(leftSpacer2);

        pushButton_2 = new QPushButton(Dialog);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(80, 23));

        hLayoutEmployee->addWidget(pushButton_2);

        rightSpacer2 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hLayoutEmployee->addItem(rightSpacer2);


        verticalLayout->addLayout(hLayoutEmployee);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("Dialog", "Finance", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Dialog", "Employee", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ReportDialog: public Ui_ReportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPORT_H
