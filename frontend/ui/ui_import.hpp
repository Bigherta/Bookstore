#ifndef UI_IMPORTDIALOG_H
#define UI_IMPORTDIALOG_H

#include <QDialog>
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImportDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *quantityLayout;
    QLabel *labelQuantity;
    QLineEdit *lineEditQuantity;
    QHBoxLayout *costLayout;
    QLabel *labelCost;
    QLineEdit *lineEditCost;
    QHBoxLayout *buttonLayout;
    QSpacerItem *leftSpacer;
    QPushButton *pushButtonImport;
    QSpacerItem *rightSpacer;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("ImportDialog"));
        Dialog->resize(400, 250);

        // Qt6 弹窗带系统边框和标题栏
        Dialog->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);

        verticalLayout = new QVBoxLayout(Dialog);

        // 数量布局
        quantityLayout = new QHBoxLayout();
        labelQuantity = new QLabel(Dialog);
        lineEditQuantity = new QLineEdit(Dialog);
        lineEditQuantity->setMaxLength(10);
        quantityLayout->addWidget(labelQuantity);
        quantityLayout->addWidget(lineEditQuantity);
        verticalLayout->addLayout(quantityLayout);

        // 价格布局
        costLayout = new QHBoxLayout();
        labelCost = new QLabel(Dialog);
        lineEditCost = new QLineEdit(Dialog);
        lineEditCost->setMaxLength(13);
        costLayout->addWidget(labelCost);
        costLayout->addWidget(lineEditCost);
        verticalLayout->addLayout(costLayout);

        // 按钮布局
        buttonLayout = new QHBoxLayout();
        leftSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        rightSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        pushButtonImport = new QPushButton(Dialog);

        buttonLayout->addItem(leftSpacer);
        buttonLayout->addWidget(pushButtonImport);
        buttonLayout->addItem(rightSpacer);
        verticalLayout->addLayout(buttonLayout);

        retranslateUi(Dialog);
        pushButtonImport->setDefault(true);
        QMetaObject::connectSlotsByName(Dialog);
    }

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("ImportDialog", "Import"));
        labelQuantity->setText(QCoreApplication::translate("ImportDialog", "Quantity:"));
        labelCost->setText(QCoreApplication::translate("ImportDialog", "Cost:"));
        pushButtonImport->setText(QCoreApplication::translate("ImportDialog", "Import"));
    }
};

namespace Ui {
    class ImportDialog: public Ui_ImportDialog {};
}

QT_END_NAMESPACE

#endif // UI_IMPORTDIALOG_H
