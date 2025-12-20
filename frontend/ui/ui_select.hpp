#ifndef UI_SELECTDIALOG_H
#define UI_SELECTDIALOG_H

#include <QtWidgets>

QT_BEGIN_NAMESPACE

class Ui_SelectDialog
{
public:
    QVBoxLayout *verticalLayout;

    QHBoxLayout *formOuterLayout;
    QSpacerItem *leftSpacer;
    QWidget *formWidget;
    QGridLayout *gridLayout;
    QLabel *labelISBN;
    QLineEdit *lineEditISBN;
    QSpacerItem *rightSpacer;

    QHBoxLayout *buttonLayout;
    QSpacerItem *buttonSpacerLeft;
    QPushButton *pushButtonSelect;
    QSpacerItem *buttonSpacerRight;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("SelectDialog"));
        Dialog->resize(400, 200);
        Dialog->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);

        verticalLayout = new QVBoxLayout(Dialog);

        // 表单布局
        formOuterLayout = new QHBoxLayout();
        leftSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        formOuterLayout->addItem(leftSpacer);

        formWidget = new QWidget(Dialog);
        gridLayout = new QGridLayout(formWidget);
        gridLayout->setContentsMargins(0,0,0,0);

        labelISBN = new QLabel(formWidget);
        gridLayout->addWidget(labelISBN, 0, 0, Qt::AlignRight | Qt::AlignVCenter);

        lineEditISBN = new QLineEdit(formWidget);
        lineEditISBN->setMaximumSize(QSize(180,16777215));
        lineEditISBN->setMaxLength(20);
        lineEditISBN->setAlignment(Qt::AlignHCenter);
        gridLayout->addWidget(lineEditISBN, 0, 1);

        formOuterLayout->addWidget(formWidget);

        rightSpacer = new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum);
        formOuterLayout->addItem(rightSpacer);

        verticalLayout->addLayout(formOuterLayout);

        // 按钮布局
        buttonLayout = new QHBoxLayout();
        buttonSpacerLeft = new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum);
        buttonLayout->addItem(buttonSpacerLeft);

        pushButtonSelect = new QPushButton(Dialog);
        pushButtonSelect->setMinimumSize(QSize(120,35));
        buttonLayout->addWidget(pushButtonSelect);

        buttonSpacerRight = new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum);
        buttonLayout->addItem(buttonSpacerRight);

        verticalLayout->addLayout(buttonLayout);

        retranslateUi(Dialog);
        pushButtonSelect->setDefault(true); // 回车触发
        QMetaObject::connectSlotsByName(Dialog);
    }

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("SelectDialog","Select"));
        labelISBN->setText(QCoreApplication::translate("SelectDialog","ISBN:"));
        pushButtonSelect->setText(QCoreApplication::translate("SelectDialog","Select it!"));
    }
};

namespace Ui {
    class SelectDialog: public Ui_SelectDialog {};
}

QT_END_NAMESPACE

#endif // UI_SELECTDIALOG_H
