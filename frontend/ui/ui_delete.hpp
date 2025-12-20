#ifndef UI_DELETEDIALOG_H
#define UI_DELETEDIALOG_H

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

class Ui_DeleteDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *formOuterLayout;
    QSpacerItem *leftSpacer;
    QWidget *formWidget;
    QGridLayout *gridLayout;
    QLabel *labelUserID;
    QLineEdit *lineEditUserID;
    QSpacerItem *rightSpacer;
    QHBoxLayout *buttonLayout;
    QSpacerItem *buttonSpacerLeft;
    QPushButton *pushButtonDelete;
    QSpacerItem *buttonSpacerRight;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("DeleteDialog"));
        Dialog->resize(400, 200);
        Dialog->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);

        verticalLayout = new QVBoxLayout(Dialog);

        // 表单布局
        formOuterLayout = new QHBoxLayout();
        leftSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        formOuterLayout->addItem(leftSpacer);

        formWidget = new QWidget(Dialog);
        gridLayout = new QGridLayout(formWidget);
        gridLayout->setContentsMargins(0, 0, 0, 0);

        labelUserID = new QLabel(formWidget);
        gridLayout->addWidget(labelUserID, 0, 0, 1, 1, Qt::AlignRight);

        lineEditUserID = new QLineEdit(formWidget);
        lineEditUserID->setMaximumSize(QSize(180, 16777215));
        lineEditUserID->setMaxLength(30);
        gridLayout->addWidget(lineEditUserID, 0, 1, 1, 1);

        formOuterLayout->addWidget(formWidget);
        rightSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        formOuterLayout->addItem(rightSpacer);
        verticalLayout->addLayout(formOuterLayout);

        // 按钮布局
        buttonLayout = new QHBoxLayout();
        buttonSpacerLeft = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        buttonLayout->addItem(buttonSpacerLeft);

        pushButtonDelete = new QPushButton(Dialog);
        buttonLayout->addWidget(pushButtonDelete);

        buttonSpacerRight = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        buttonLayout->addItem(buttonSpacerRight);
        verticalLayout->addLayout(buttonLayout);

        retranslateUi(Dialog);
        pushButtonDelete->setDefault(true);
        QMetaObject::connectSlotsByName(Dialog);
    }

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("DeleteDialog", "Delete"));
        labelUserID->setText(QCoreApplication::translate("DeleteDialog", "User ID:"));
        pushButtonDelete->setText(QCoreApplication::translate("DeleteDialog", "Delete"));
    }
};

namespace Ui {
    class DeleteDialog: public Ui_DeleteDialog {};
}

QT_END_NAMESPACE

#endif // UI_DELETEDIALOG_H
