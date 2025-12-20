#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

#include <QtWidgets>

QT_BEGIN_NAMESPACE

class Ui_RegisterDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *formOuterLayout;
    QSpacerItem *leftSpacer;
    QWidget *formWidget;
    QGridLayout *gridLayout;

    QLabel *label_userID;
    QLineEdit *lineEdit_userID;
    QLabel *label_password;
    QLineEdit *lineEdit_password;
    QLabel *label_username;
    QLineEdit *lineEdit_username;

    QSpacerItem *rightSpacer;
    QHBoxLayout *buttonLayout;
    QSpacerItem *buttonLeftSpacer;
    QPushButton *pushButton_register;
    QSpacerItem *buttonRightSpacer;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("RegisterDialog"));
        Dialog->resize(400, 300);
        Dialog->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);

        verticalLayout = new QVBoxLayout(Dialog);

        formOuterLayout = new QHBoxLayout();
        leftSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        formOuterLayout->addItem(leftSpacer);

        formWidget = new QWidget(Dialog);
        gridLayout = new QGridLayout(formWidget);
        gridLayout->setContentsMargins(0,0,0,0);

        // 用户ID
        label_userID = new QLabel(formWidget);
        gridLayout->addWidget(label_userID, 0, 0, Qt::AlignRight | Qt::AlignVCenter);
        lineEdit_userID = new QLineEdit(formWidget);
        lineEdit_userID->setMaximumSize(QSize(200, 16777215));
        lineEdit_userID->setMaxLength(30);
        gridLayout->addWidget(lineEdit_userID, 0, 1);

        // 密码
        label_password = new QLabel(formWidget);
        gridLayout->addWidget(label_password, 1, 0, Qt::AlignRight | Qt::AlignVCenter);
        lineEdit_password = new QLineEdit(formWidget);
        lineEdit_password->setEchoMode(QLineEdit::Password);
        lineEdit_password->setMaximumSize(QSize(200, 16777215));
        lineEdit_password->setMaxLength(30);
        gridLayout->addWidget(lineEdit_password, 1, 1);

        // 用户名
        label_username = new QLabel(formWidget);
        gridLayout->addWidget(label_username, 2, 0, Qt::AlignRight | Qt::AlignVCenter);
        lineEdit_username = new QLineEdit(formWidget);
        lineEdit_username->setMaximumSize(QSize(200, 16777215));
        lineEdit_username->setMaxLength(30);
        gridLayout->addWidget(lineEdit_username, 2, 1);

        formOuterLayout->addWidget(formWidget);
        rightSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        formOuterLayout->addItem(rightSpacer);
        verticalLayout->addLayout(formOuterLayout);

        // 按钮布局
        buttonLayout = new QHBoxLayout();
        buttonLeftSpacer = new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum);
        buttonLayout->addItem(buttonLeftSpacer);

        pushButton_register = new QPushButton(Dialog);
        buttonLayout->addWidget(pushButton_register);

        buttonRightSpacer = new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum);
        buttonLayout->addItem(buttonRightSpacer);

        verticalLayout->addLayout(buttonLayout);

        retranslateUi(Dialog);
        pushButton_register->setDefault(true);
        QMetaObject::connectSlotsByName(Dialog);
    }

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("RegisterDialog","Register"));
        label_userID->setText(QCoreApplication::translate("RegisterDialog","User ID:"));
        label_password->setText(QCoreApplication::translate("RegisterDialog","Password:"));
        label_username->setText(QCoreApplication::translate("RegisterDialog","Username:"));
        pushButton_register->setText(QCoreApplication::translate("RegisterDialog","Register"));
    }
};

namespace Ui {
    class RegisterDialog : public Ui_RegisterDialog {};
}

QT_END_NAMESPACE

#endif // UI_REGISTERDIALOG_H
