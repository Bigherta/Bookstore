#ifndef UI_DELETE_H
#define UI_DELETE_H

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

class Ui_DeleteDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *formOuterLayout;
    QSpacerItem *leftSpacer;
    QWidget *formWidget;
    QGridLayout *gridLayout;
    QLabel *label_userID;
    QLineEdit *lineEdit_userID;
    QSpacerItem *rightSpacer;
    QHBoxLayout *buttonLayout;
    QSpacerItem *buttonSpacerLeft;
    QPushButton *pushButton;
    QSpacerItem *buttonSpacerRight;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("DeleteDialog"));
        Dialog->resize(400, 200);
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
        Dialog->setWindowTitle(QCoreApplication::translate("DeleteDialog", "Delete", nullptr));
        label_userID->setText(QCoreApplication::translate("DeleteDialog", "User ID:", nullptr));
        pushButton->setText(QCoreApplication::translate("DeleteDialog", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DeleteDialog: public Ui_DeleteDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELETE_H
