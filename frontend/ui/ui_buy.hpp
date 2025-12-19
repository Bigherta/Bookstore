#ifndef UI_BUYDIALOG_H
#define UI_BUYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BuyDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *formOuterLayout;
    QSpacerItem *leftSpacer;
    QWidget *formWidget;
    QGridLayout *gridLayout;
    QLabel *label_isbn;
    QLineEdit *lineEdit_isbn;
    QLabel *label_quantity;
    QLineEdit *lineEdit_quantity;
    QSpacerItem *rightSpacer;
    QHBoxLayout *buttonLayout;
    QSpacerItem *buttonSpacerLeft;
    QPushButton *pushButton_buy;
    QSpacerItem *buttonSpacerRight;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("BuyDialog"));
        Dialog->resize(400, 250);

        verticalLayout = new QVBoxLayout(Dialog);
        formOuterLayout = new QHBoxLayout();
        leftSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        formOuterLayout->addItem(leftSpacer);

        formWidget = new QWidget(Dialog);
        gridLayout = new QGridLayout(formWidget);

        label_isbn = new QLabel(formWidget);
        gridLayout->addWidget(label_isbn, 0, 0, 1, 1, Qt::AlignRight);
        lineEdit_isbn = new QLineEdit(formWidget);
        gridLayout->addWidget(lineEdit_isbn, 0, 1, 1, 1);

        label_quantity = new QLabel(formWidget);
        gridLayout->addWidget(label_quantity, 1, 0, 1, 1, Qt::AlignRight);
        lineEdit_quantity = new QLineEdit(formWidget);
        gridLayout->addWidget(lineEdit_quantity, 1, 1, 1, 1);

        formOuterLayout->addWidget(formWidget);
        rightSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        formOuterLayout->addItem(rightSpacer);
        verticalLayout->addLayout(formOuterLayout);

        buttonLayout = new QHBoxLayout();
        buttonSpacerLeft = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        buttonLayout->addItem(buttonSpacerLeft);
        pushButton_buy = new QPushButton(Dialog);
        buttonLayout->addWidget(pushButton_buy);
        buttonSpacerRight = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        buttonLayout->addItem(buttonSpacerRight);
        verticalLayout->addLayout(buttonLayout);

        retranslateUi(Dialog);
        QMetaObject::connectSlotsByName(Dialog);
    }

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("BuyDialog", "Buy Book", nullptr));
        label_isbn->setText(QCoreApplication::translate("BuyDialog", "ISBN:", nullptr));
        label_quantity->setText(QCoreApplication::translate("BuyDialog", "Quantity:", nullptr));
        lineEdit_quantity->setInputMask(QCoreApplication::translate("BuyDialog", "9999999999", nullptr));
        pushButton_buy->setText(QCoreApplication::translate("BuyDialog", "Buy it!", nullptr));
    }
};

namespace Ui {
    class BuyDialog: public Ui_BuyDialog {};
}

QT_END_NAMESPACE

#endif // UI_BUYDIALOG_H
