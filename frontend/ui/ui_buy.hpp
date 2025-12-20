#ifndef UI_BUYDIALOG_H
#define UI_BUYDIALOG_H

#include <QDialog>
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_BuyDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *formOuterLayout;
    QSpacerItem *leftSpacer;
    QWidget *formWidget;
    QGridLayout *gridLayout;
    QLabel *labelISBN;
    QLineEdit *lineEditISBN;
    QLabel *labelQuantity;
    QLineEdit *lineEditQuantity;
    QSpacerItem *rightSpacer;
    QHBoxLayout *buttonLayout;
    QSpacerItem *buttonSpacerLeft;
    QPushButton *pushButtonBuy;
    QSpacerItem *buttonSpacerRight;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("BuyDialog"));
        Dialog->resize(400, 250);
        Dialog->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);

        verticalLayout = new QVBoxLayout(Dialog);

        // 表单布局
        formOuterLayout = new QHBoxLayout();
        leftSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        formOuterLayout->addItem(leftSpacer);

        formWidget = new QWidget(Dialog);
        gridLayout = new QGridLayout(formWidget);

        labelISBN = new QLabel(formWidget);
        gridLayout->addWidget(labelISBN, 0, 0, 1, 1, Qt::AlignRight);
        lineEditISBN = new QLineEdit(formWidget);
        gridLayout->addWidget(lineEditISBN, 0, 1, 1, 1);

        labelQuantity = new QLabel(formWidget);
        gridLayout->addWidget(labelQuantity, 1, 0, 1, 1, Qt::AlignRight);
        lineEditQuantity = new QLineEdit(formWidget);
        gridLayout->addWidget(lineEditQuantity, 1, 1, 1, 1);

        formOuterLayout->addWidget(formWidget);
        rightSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        formOuterLayout->addItem(rightSpacer);
        verticalLayout->addLayout(formOuterLayout);

        // 按钮布局
        buttonLayout = new QHBoxLayout();
        buttonSpacerLeft = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        buttonLayout->addItem(buttonSpacerLeft);
        pushButtonBuy = new QPushButton(Dialog);
        buttonLayout->addWidget(pushButtonBuy);
        buttonSpacerRight = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        buttonLayout->addItem(buttonSpacerRight);
        verticalLayout->addLayout(buttonLayout);

        retranslateUi(Dialog);
        QMetaObject::connectSlotsByName(Dialog);
    }

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("BuyDialog", "Buy Book"));
        labelISBN->setText(QCoreApplication::translate("BuyDialog", "ISBN:"));
        labelQuantity->setText(QCoreApplication::translate("BuyDialog", "Quantity:"));
        lineEditQuantity->setInputMask(QStringLiteral("9999999999"));
        pushButtonBuy->setText(QCoreApplication::translate("BuyDialog", "Buy it!"));
    }
};

namespace Ui {
    class BuyDialog: public Ui_BuyDialog {};
}

QT_END_NAMESPACE

#endif // UI_BUYDIALOG_H
