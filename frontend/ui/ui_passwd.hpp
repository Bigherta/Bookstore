#ifndef UI_PASSWD_H
#define UI_PASSWD_H

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
            Dialog->setObjectName(QString::fromUtf8("PasswdDialog"));
        Dialog->resize(420, 260);
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        centerLayout = new QHBoxLayout();
        centerLayout->setObjectName(QString::fromUtf8("centerLayout"));
        leftSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        centerLayout->addItem(leftSpacer);

        formWidget = new QWidget(Dialog);
        formWidget->setObjectName(QString::fromUtf8("formWidget"));
        gridLayout = new QGridLayout(formWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_userID = new QLabel(formWidget);
        label_userID->setObjectName(QString::fromUtf8("label_userID"));

        gridLayout->addWidget(label_userID, 0, 0, 1, 1, Qt::AlignRight|Qt::AlignVCenter);

        lineEdit_userID = new QLineEdit(formWidget);
        lineEdit_userID->setObjectName(QString::fromUtf8("lineEdit_userID"));
        lineEdit_userID->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(lineEdit_userID, 0, 1, 1, 1);

        label_oldPassword = new QLabel(formWidget);
        label_oldPassword->setObjectName(QString::fromUtf8("label_oldPassword"));

        gridLayout->addWidget(label_oldPassword, 1, 0, 1, 1, Qt::AlignRight|Qt::AlignVCenter);

        lineEdit_oldPassword = new QLineEdit(formWidget);
        lineEdit_oldPassword->setObjectName(QString::fromUtf8("lineEdit_oldPassword"));
        lineEdit_oldPassword->setMaximumSize(QSize(200, 16777215));
        lineEdit_oldPassword->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(lineEdit_oldPassword, 1, 1, 1, 1);

        label_newPassword = new QLabel(formWidget);
        label_newPassword->setObjectName(QString::fromUtf8("label_newPassword"));

        gridLayout->addWidget(label_newPassword, 2, 0, 1, 1, Qt::AlignRight|Qt::AlignVCenter);

        lineEdit_newPassword = new QLineEdit(formWidget);
        lineEdit_newPassword->setObjectName(QString::fromUtf8("lineEdit_newPassword"));
        lineEdit_newPassword->setMaximumSize(QSize(200, 16777215));
        lineEdit_newPassword->setMaxLength(30);
        lineEdit_newPassword->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(lineEdit_newPassword, 2, 1, 1, 1);


        centerLayout->addWidget(formWidget);

        rightSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        centerLayout->addItem(rightSpacer);


        verticalLayout->addLayout(centerLayout);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName(QString::fromUtf8("buttonLayout"));
        buttonLeftSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        buttonLayout->addItem(buttonLeftSpacer);

        pushButton_change = new QPushButton(Dialog);
        pushButton_change->setObjectName(QString::fromUtf8("pushButton_change"));

        buttonLayout->addWidget(pushButton_change);

        buttonRightSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        buttonLayout->addItem(buttonRightSpacer);


        verticalLayout->addLayout(buttonLayout);


        retranslateUi(Dialog);

        pushButton_change->setDefault(true);


        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("PasswdDialog", "Change Password", nullptr));
        label_userID->setText(QCoreApplication::translate("PasswdDialog", "User ID:", nullptr));
        label_oldPassword->setText(QCoreApplication::translate("PasswdDialog", "Original Password:", nullptr));
        label_newPassword->setText(QCoreApplication::translate("PasswdDialog", "New Password:", nullptr));
        pushButton_change->setText(QCoreApplication::translate("PasswdDialog", "Change", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PasswdDialog: public Ui_PasswdDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASSWD_H
