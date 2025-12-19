#ifndef UI_LOGIN_H
#define UI_LOGIN_H

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

class Ui_LoginDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *gridOuterLayout;
    QSpacerItem *horizontalSpacerLeft;
    QWidget *formWidget;
    QGridLayout *gridLayout;
    QLabel *label_userID;
    QLineEdit *lineEdit_userID;
    QLabel *label_password;
    QLineEdit *lineEdit_password;
    QSpacerItem *horizontalSpacerRight;
    QHBoxLayout *buttonLayout;
    QSpacerItem *buttonSpacerLeft;
    QPushButton *pushButton;
    QSpacerItem *buttonSpacerRight;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("LoginDialog"));
        Dialog->resize(400, 200);
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridOuterLayout = new QHBoxLayout();
        gridOuterLayout->setObjectName(QString::fromUtf8("gridOuterLayout"));
        horizontalSpacerLeft = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridOuterLayout->addItem(horizontalSpacerLeft);

        formWidget = new QWidget(Dialog);
        formWidget->setObjectName(QString::fromUtf8("formWidget"));
        gridLayout = new QGridLayout(formWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_userID = new QLabel(formWidget);
        label_userID->setObjectName(QString::fromUtf8("label_userID"));

        gridLayout->addWidget(label_userID, 0, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter);

        lineEdit_userID = new QLineEdit(formWidget);
        lineEdit_userID->setObjectName(QString::fromUtf8("lineEdit_userID"));
        lineEdit_userID->setMaximumSize(QSize(200, 16777215));
        lineEdit_userID->setAlignment(Qt::AlignHCenter);
        lineEdit_userID->setMaxLength(30);

        gridLayout->addWidget(lineEdit_userID, 0, 1, 1, 1);

        label_password = new QLabel(formWidget);
        label_password->setObjectName(QString::fromUtf8("label_password"));

        gridLayout->addWidget(label_password, 1, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter);

        lineEdit_password = new QLineEdit(formWidget);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setMaximumSize(QSize(200, 16777215));
        lineEdit_password->setEchoMode(QLineEdit::Password);
        lineEdit_password->setAlignment(Qt::AlignHCenter);
        lineEdit_password->setMaxLength(30);

        gridLayout->addWidget(lineEdit_password, 1, 1, 1, 1);


        gridOuterLayout->addWidget(formWidget);

        horizontalSpacerRight = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridOuterLayout->addItem(horizontalSpacerRight);


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

        pushButton->setDefault(true);


        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Log In", nullptr));

        label_userID->setText(QCoreApplication::translate("LoginDialog", "userID:", nullptr));
        label_password->setText(QCoreApplication::translate("LoginDialog", "password:", nullptr));
        pushButton->setText(QCoreApplication::translate("LoginDialog", "Log In", nullptr));
    }
};

namespace Ui
{
    class LoginDialog : public Ui_LoginDialog
    {
    };
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
