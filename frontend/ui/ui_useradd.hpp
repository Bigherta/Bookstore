#ifndef UI_USERADD_H
#define UI_USERADD_H

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

class Ui_UseraddDialog
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
    QLabel *label_privilege;
    QLineEdit *lineEdit_privilege;
    QLabel *label_username;
    QLineEdit *lineEdit_username;
    QSpacerItem *rightSpacer;
    QHBoxLayout *buttonLayout;
    QSpacerItem *buttonSpacerLeft;
    QPushButton *pushButton;
    QSpacerItem *buttonSpacerRight;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("UseraddDialog"));
        Dialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formOuterLayout = new QHBoxLayout();
        formOuterLayout->setObjectName(QString::fromUtf8("formOuterLayout"));
        leftSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formOuterLayout->addItem(leftSpacer);

        formWidget = new QWidget(Dialog);
        formWidget->setObjectName(QString::fromUtf8("formWidget"));
        gridLayout = new QGridLayout(formWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_userID = new QLabel(formWidget);
        label_userID->setObjectName(QString::fromUtf8("label_userID"));

        gridLayout->addWidget(label_userID, 0, 0, 1, 1, Qt::AlignRight);

        lineEdit_userID = new QLineEdit(formWidget);
        lineEdit_userID->setObjectName(QString::fromUtf8("lineEdit_userID"));
        lineEdit_userID->setMaximumSize(QSize(180, 16777215));
        lineEdit_userID->setMaxLength(30);

        gridLayout->addWidget(lineEdit_userID, 0, 1, 1, 1);

        label_password = new QLabel(formWidget);
        label_password->setObjectName(QString::fromUtf8("label_password"));

        gridLayout->addWidget(label_password, 1, 0, 1, 1, Qt::AlignRight);

        lineEdit_password = new QLineEdit(formWidget);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setMaximumSize(QSize(180, 16777215));
        lineEdit_password->setEchoMode(QLineEdit::Password);
        lineEdit_password->setMaxLength(30);

        gridLayout->addWidget(lineEdit_password, 1, 1, 1, 1);

        label_privilege = new QLabel(formWidget);
        label_privilege->setObjectName(QString::fromUtf8("label_privilege"));

        gridLayout->addWidget(label_privilege, 2, 0, 1, 1, Qt::AlignRight);

        lineEdit_privilege = new QLineEdit(formWidget);
        lineEdit_privilege->setObjectName(QString::fromUtf8("lineEdit_privilege"));
        lineEdit_privilege->setMaximumSize(QSize(180, 16777215));
        lineEdit_privilege->setMaxLength(30);

        gridLayout->addWidget(lineEdit_privilege, 2, 1, 1, 1);

        label_username = new QLabel(formWidget);
        label_username->setObjectName(QString::fromUtf8("label_username"));

        gridLayout->addWidget(label_username, 3, 0, 1, 1, Qt::AlignRight);

        lineEdit_username = new QLineEdit(formWidget);
        lineEdit_username->setObjectName(QString::fromUtf8("lineEdit_username"));
        lineEdit_username->setMaximumSize(QSize(180, 16777215));
        lineEdit_username->setMaxLength(30);

        gridLayout->addWidget(lineEdit_username, 3, 1, 1, 1);


        formOuterLayout->addWidget(formWidget);

        rightSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formOuterLayout->addItem(rightSpacer);


        verticalLayout->addLayout(formOuterLayout);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName(QString::fromUtf8("buttonLayout"));
        buttonSpacerLeft = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        buttonLayout->addItem(buttonSpacerLeft);

        pushButton = new QPushButton(Dialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        buttonLayout->addWidget(pushButton);

        buttonSpacerRight = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        buttonLayout->addItem(buttonSpacerRight);


        verticalLayout->addLayout(buttonLayout);


        retranslateUi(Dialog);

        pushButton->setDefault(true);


        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("UseraddDialog", "Add User", nullptr));
        label_userID->setText(QCoreApplication::translate("UseraddDialog", "User ID:", nullptr));
        label_password->setText(QCoreApplication::translate("UseraddDialog", "Password:", nullptr));
        label_privilege->setText(QCoreApplication::translate("UseraddDialog", "Privilege:", nullptr));
        label_username->setText(QCoreApplication::translate("UseraddDialog", "Username:", nullptr));
        pushButton->setText(QCoreApplication::translate("UseraddDialog", "Add", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UseraddDialog: public Ui_UseraddDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERADD_H
