#ifndef UI_PASSWDDIALOG_H
#define UI_PASSWDDIALOG_H

#include <QtWidgets>

QT_BEGIN_NAMESPACE

class Ui_PasswdDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *centerLayout;
    QSpacerItem *leftSpacer;
    QWidget *formWidget;
    QGridLayout *gridLayout;

    QLabel *label_userID;
    QLineEdit *lineEdit_userID;
    QLabel *label_oldPassword;
    QLineEdit *lineEdit_oldPassword;
    QLabel *label_newPassword;
    QLineEdit *lineEdit_newPassword;

    QSpacerItem *rightSpacer;
    QHBoxLayout *buttonLayout;
    QSpacerItem *buttonLeftSpacer;
    QPushButton *pushButton_change;
    QSpacerItem *buttonRightSpacer;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("PasswdDialog"));
        Dialog->resize(420, 260);

        // 系统边框和标题栏
        Dialog->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);

        verticalLayout = new QVBoxLayout(Dialog);

        centerLayout = new QHBoxLayout();
        leftSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        centerLayout->addItem(leftSpacer);

        formWidget = new QWidget(Dialog);
        gridLayout = new QGridLayout(formWidget);
        gridLayout->setContentsMargins(0, 0, 0, 0);

        // 用户ID
        label_userID = new QLabel(formWidget);
        gridLayout->addWidget(label_userID, 0, 0, Qt::AlignRight | Qt::AlignVCenter);
        lineEdit_userID = new QLineEdit(formWidget);
        lineEdit_userID->setMaximumSize(QSize(200, 16777215));
        lineEdit_userID->setMaxLength(30);
        gridLayout->addWidget(lineEdit_userID, 0, 1);

        // 原密码
        label_oldPassword = new QLabel(formWidget);
        gridLayout->addWidget(label_oldPassword, 1, 0, Qt::AlignRight | Qt::AlignVCenter);
        lineEdit_oldPassword = new QLineEdit(formWidget);
        lineEdit_oldPassword->setMaximumSize(QSize(200, 16777215));
        lineEdit_oldPassword->setMaxLength(30);
        lineEdit_oldPassword->setEchoMode(QLineEdit::Password);
        gridLayout->addWidget(lineEdit_oldPassword, 1, 1);

        // 新密码
        label_newPassword = new QLabel(formWidget);
        gridLayout->addWidget(label_newPassword, 2, 0, Qt::AlignRight | Qt::AlignVCenter);
        lineEdit_newPassword = new QLineEdit(formWidget);
        lineEdit_newPassword->setMaximumSize(QSize(200, 16777215));
        lineEdit_newPassword->setMaxLength(30);
        lineEdit_newPassword->setEchoMode(QLineEdit::Password);
        gridLayout->addWidget(lineEdit_newPassword, 2, 1);

        centerLayout->addWidget(formWidget);
        rightSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        centerLayout->addItem(rightSpacer);

        verticalLayout->addLayout(centerLayout);

        // 按钮布局
        buttonLayout = new QHBoxLayout();
        buttonLeftSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        buttonLayout->addItem(buttonLeftSpacer);

        pushButton_change = new QPushButton(Dialog);
        buttonLayout->addWidget(pushButton_change);

        buttonRightSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        buttonLayout->addItem(buttonRightSpacer);

        verticalLayout->addLayout(buttonLayout);

        retranslateUi(Dialog);
        pushButton_change->setDefault(true);

        QMetaObject::connectSlotsByName(Dialog);
    }

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("PasswdDialog", "Change Password"));
        label_userID->setText(QCoreApplication::translate("PasswdDialog", "User ID:"));
        label_oldPassword->setText(QCoreApplication::translate("PasswdDialog", "Original Password (可省略，权限7可不填):"));
        label_newPassword->setText(QCoreApplication::translate("PasswdDialog", "New Password:"));
        pushButton_change->setText(QCoreApplication::translate("PasswdDialog", "Change"));
    }
};

namespace Ui {
    class PasswdDialog : public Ui_PasswdDialog {};
}

QT_END_NAMESPACE

#endif // UI_PASSWDDIALOG_H
