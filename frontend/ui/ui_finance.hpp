#ifndef UI_FINANCE_H
#define UI_FINANCE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_FinanceDialog
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("FinanceDialog"));
        Dialog->resize(400, 300);
        label = new QLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(90, 100, 57, 15));
        lineEdit = new QLineEdit(Dialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(140, 100, 113, 23));
        lineEdit->setMaxLength(10);
        pushButton = new QPushButton(Dialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(129, 160, 101, 23));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("FinanceDialog", "Show Finance", nullptr));
        label->setText(QCoreApplication::translate("FinanceDialog", "Count:", nullptr));
        pushButton->setText(QCoreApplication::translate("FinanceDialog", "Show Finance", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FinanceDialog: public Ui_FinanceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINANCE_H
