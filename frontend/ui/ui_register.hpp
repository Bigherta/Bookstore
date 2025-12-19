#ifndef UI_REGISTER_H
#define UI_REGISTER_H

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

class Ui_RegisterDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *gridOuterLayout;
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
    QSpacerItem *buttonSpacerLeft;
    QPushButton *pushButton;
    QSpacerItem *buttonSpacerRight;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("RegisterDialog"));
        Dialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridOuterLayout = new QHBoxLayout();
        gridOuterLayout->setObjectName(QString::fromUtf8("gridOuterLayout"));
        leftSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridOuterLayout->addItem(leftSpacer);

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
        lineEdit_userID->setMaximumSize(QSize(150, 16777215));
        lineEdit_userID->setMaxLength(30);
        lineEdit_userID->setAlignment(Qt::AlignHCenter);

        gridLayout->addWidget(lineEdit_userID, 0, 1, 1, 1);

        label_password = new QLabel(formWidget);
        label_password->setObjectName(QString::fromUtf8("label_password"));

        gridLayout->addWidget(label_password, 1, 0, 1, 1, Qt::AlignRight|Qt::AlignVCenter);

        lineEdit_password = new QLineEdit(formWidget);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setEchoMode(QLineEdit::Password);
        lineEdit_password->setMaximumSize(QSize(150, 16777215));
        lineEdit_password->setMaxLength(30);
        lineEdit_password->setAlignment(Qt::AlignHCenter);

        gridLayout->addWidget(lineEdit_password, 1, 1, 1, 1);

        label_username = new QLabel(formWidget);
        label_username->setObjectName(QString::fromUtf8("label_username"));

        gridLayout->addWidget(label_username, 2, 0, 1, 1, Qt::AlignRight|Qt::AlignVCenter);

        lineEdit_username = new QLineEdit(formWidget);
        lineEdit_username->setObjectName(QString::fromUtf8("lineEdit_username"));
        lineEdit_username->setMaximumSize(QSize(150, 16777215));
        lineEdit_username->setMaxLength(30);
        lineEdit_username->setAlignment(Qt::AlignHCenter);

        gridLayout->addWidget(lineEdit_username, 2, 1, 1, 1);


        gridOuterLayout->addWidget(formWidget);

        rightSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridOuterLayout->addItem(rightSpacer);


        verticalLayout->addLayout(gridOuterLayout);

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

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("RegisterDialog", "Register", nullptr));
        label_userID->setText(QCoreApplication::translate("RegisterDialog", "User ID:", nullptr));
        label_password->setText(QCoreApplication::translate("RegisterDialog", "Password:", nullptr));
        label_username->setText(QCoreApplication::translate("RegisterDialog", "Username:", nullptr));
        pushButton->setText(QCoreApplication::translate("RegisterDialog", "Register", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterDialog: public Ui_RegisterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTER_H
