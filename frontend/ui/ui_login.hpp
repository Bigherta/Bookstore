#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

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

class Ui_LoginDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *formOuterLayout;
    QSpacerItem *leftSpacer;
    QWidget *formWidget;
    QGridLayout *gridLayout;
    QLabel *labelUserID;
    QLineEdit *lineEditUserID;
    QLabel *labelPassword;
    QLineEdit *lineEditPassword;
    QSpacerItem *rightSpacer;
    QHBoxLayout *buttonLayout;
    QSpacerItem *buttonSpacerLeft;
    QPushButton *pushButtonLogin;
    QSpacerItem *buttonSpacerRight;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("LoginDialog"));
        Dialog->resize(400, 200);

        // 系统边框和标题栏
        Dialog->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);

        verticalLayout = new QVBoxLayout(Dialog);

        // 表单外层布局
        formOuterLayout = new QHBoxLayout();
        leftSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        formOuterLayout->addItem(leftSpacer);

        formWidget = new QWidget(Dialog);
        gridLayout = new QGridLayout(formWidget);
        gridLayout->setContentsMargins(0, 0, 0, 0);

        labelUserID = new QLabel(formWidget);
        gridLayout->addWidget(labelUserID, 0, 0, Qt::AlignRight | Qt::AlignVCenter);

        lineEditUserID = new QLineEdit(formWidget);
        lineEditUserID->setMaximumSize(QSize(200, 16777215));
        lineEditUserID->setAlignment(Qt::AlignHCenter);
        lineEditUserID->setMaxLength(30);
        gridLayout->addWidget(lineEditUserID, 0, 1);

        labelPassword = new QLabel(formWidget);
        gridLayout->addWidget(labelPassword, 1, 0, Qt::AlignRight | Qt::AlignVCenter);

        lineEditPassword = new QLineEdit(formWidget);
        lineEditPassword->setMaximumSize(QSize(200, 16777215));
        lineEditPassword->setEchoMode(QLineEdit::Password);
        lineEditPassword->setAlignment(Qt::AlignHCenter);
        lineEditPassword->setMaxLength(30);
        gridLayout->addWidget(lineEditPassword, 1, 1);

        formOuterLayout->addWidget(formWidget);
        rightSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        formOuterLayout->addItem(rightSpacer);
        verticalLayout->addLayout(formOuterLayout);

        // 按钮布局
        buttonLayout = new QHBoxLayout();
        buttonSpacerLeft = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        buttonLayout->addItem(buttonSpacerLeft);

        pushButtonLogin = new QPushButton(Dialog);
        buttonLayout->addWidget(pushButtonLogin);

        buttonSpacerRight = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        buttonLayout->addItem(buttonSpacerRight);
        verticalLayout->addLayout(buttonLayout);

        retranslateUi(Dialog);
        pushButtonLogin->setDefault(true);
        QMetaObject::connectSlotsByName(Dialog);
    }

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Log In"));
        labelUserID->setText(QCoreApplication::translate("LoginDialog", "User ID:"));
        labelPassword->setText(QCoreApplication::translate("LoginDialog", "Password:"));
        pushButtonLogin->setText(QCoreApplication::translate("LoginDialog", "Log In"));
    }
};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
}

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
