/********************************************************************************
** Form generated from reading UI file 'import.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMPORT_H
#define UI_IMPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ImportDialog
{
public:
    QLabel *label_quantity;
    QLineEdit *lineEdit_quantity;
    QLabel *label_cost;
    QLineEdit *lineEdit_cost;
    QPushButton *pushButton_import;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(400, 250);
        label_quantity = new QLabel(Dialog);
        label_quantity->setObjectName(QString::fromUtf8("label_quantity"));
        label_quantity->setGeometry(QRect(100, 60, 57, 15));
        lineEdit_quantity = new QLineEdit(Dialog);
        lineEdit_quantity->setObjectName(QString::fromUtf8("lineEdit_quantity"));
        lineEdit_quantity->setGeometry(QRect(160, 60, 113, 23));
        lineEdit_quantity->setMaxLength(10);
        label_cost = new QLabel(Dialog);
        label_cost->setObjectName(QString::fromUtf8("label_cost"));
        label_cost->setGeometry(QRect(100, 100, 57, 15));
        lineEdit_cost = new QLineEdit(Dialog);
        lineEdit_cost->setObjectName(QString::fromUtf8("lineEdit_cost"));
        lineEdit_cost->setGeometry(QRect(160, 100, 113, 23));
        lineEdit_cost->setMaxLength(13);
        pushButton_import = new QPushButton(Dialog);
        pushButton_import->setObjectName(QString::fromUtf8("pushButton_import"));
        pushButton_import->setGeometry(QRect(140, 150, 80, 23));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        label_quantity->setText(QCoreApplication::translate("Dialog", "Quantity:", nullptr));
        label_cost->setText(QCoreApplication::translate("Dialog", "Cost:", nullptr));
        pushButton_import->setText(QCoreApplication::translate("Dialog", "Import", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImportDialog: public Ui_ImportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMPORT_H
