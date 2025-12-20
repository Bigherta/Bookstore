#ifndef UI_FINANCEDIALOG_H
#define UI_FINANCEDIALOG_H

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

class Ui_FinanceDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *formLayout;
    QLabel *labelCount;
    QLineEdit *lineEditCount;
    QHBoxLayout *buttonLayout;
    QSpacerItem *leftSpacer;
    QPushButton *pushButtonShow;
    QSpacerItem *rightSpacer;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("FinanceDialog"));
        Dialog->resize(400, 200);

        // Qt6 弹窗带系统边框和标题栏
        Dialog->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);

        verticalLayout = new QVBoxLayout(Dialog);

        // 表单布局
        formLayout = new QHBoxLayout();
        labelCount = new QLabel(Dialog);
        lineEditCount = new QLineEdit(Dialog);
        lineEditCount->setMaxLength(10);
        formLayout->addWidget(labelCount);
        formLayout->addWidget(lineEditCount);
        verticalLayout->addLayout(formLayout);

        // 按钮布局
        buttonLayout = new QHBoxLayout();
        leftSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        rightSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        pushButtonShow = new QPushButton(Dialog);

        buttonLayout->addItem(leftSpacer);
        buttonLayout->addWidget(pushButtonShow);
        buttonLayout->addItem(rightSpacer);
        verticalLayout->addLayout(buttonLayout);

        retranslateUi(Dialog);
        pushButtonShow->setDefault(true);
        QMetaObject::connectSlotsByName(Dialog);
    }

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("FinanceDialog", "Show Finance"));
        labelCount->setText(QCoreApplication::translate("FinanceDialog", "Count:"));
        pushButtonShow->setText(QCoreApplication::translate("FinanceDialog", "Show Finance"));
    }
};

namespace Ui {
    class FinanceDialog: public Ui_FinanceDialog {};
}

QT_END_NAMESPACE

#endif // UI_FINANCEDIALOG_H
