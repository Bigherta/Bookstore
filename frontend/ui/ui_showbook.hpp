/********************************************************************************
** Form generated from reading UI file 'showbook.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWBOOK_H
#define UI_SHOWBOOK_H

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

class Ui_ShowDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *formOuterLayout;
    QSpacerItem *leftSpacer;
    QWidget *formWidget;
    QGridLayout *gridLayout;
    QLabel *label_ISBN;
    QLineEdit *lineEdit_ISBN;
    QLabel *label_title;
    QLineEdit *lineEdit_title;
    QLabel *label_author;
    QLineEdit *lineEdit_author;
    QLabel *label_keyword;
    QLineEdit *lineEdit_keyword;
    QSpacerItem *rightSpacer;
    QHBoxLayout *buttonLayout;
    QSpacerItem *buttonSpacerLeft;
    QPushButton *pushButton;
    QSpacerItem *buttonSpacerRight;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
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
        label_ISBN = new QLabel(formWidget);
        label_ISBN->setObjectName(QString::fromUtf8("label_ISBN"));

        gridLayout->addWidget(label_ISBN, 0, 0, 1, 1, Qt::AlignRight);

        lineEdit_ISBN = new QLineEdit(formWidget);
        lineEdit_ISBN->setObjectName(QString::fromUtf8("lineEdit_ISBN"));
        lineEdit_ISBN->setMaximumSize(QSize(180, 16777215));
        lineEdit_ISBN->setMaxLength(20);

        gridLayout->addWidget(lineEdit_ISBN, 0, 1, 1, 1);

        label_title = new QLabel(formWidget);
        label_title->setObjectName(QString::fromUtf8("label_title"));

        gridLayout->addWidget(label_title, 1, 0, 1, 1, Qt::AlignRight);

        lineEdit_title = new QLineEdit(formWidget);
        lineEdit_title->setObjectName(QString::fromUtf8("lineEdit_title"));
        lineEdit_title->setMaximumSize(QSize(250, 16777215));
        lineEdit_title->setMaxLength(60);
        lineEdit_title->setInputMethodHints(Qt::ImhPreferNumbers|Qt::ImhMultiLine);

        gridLayout->addWidget(lineEdit_title, 1, 1, 1, 1);

        label_author = new QLabel(formWidget);
        label_author->setObjectName(QString::fromUtf8("label_author"));

        gridLayout->addWidget(label_author, 2, 0, 1, 1, Qt::AlignRight);

        lineEdit_author = new QLineEdit(formWidget);
        lineEdit_author->setObjectName(QString::fromUtf8("lineEdit_author"));
        lineEdit_author->setMaximumSize(QSize(250, 16777215));
        lineEdit_author->setMaxLength(60);
        lineEdit_author->setInputMethodHints(Qt::ImhPreferNumbers|Qt::ImhMultiLine);

        gridLayout->addWidget(lineEdit_author, 2, 1, 1, 1);

        label_keyword = new QLabel(formWidget);
        label_keyword->setObjectName(QString::fromUtf8("label_keyword"));

        gridLayout->addWidget(label_keyword, 3, 0, 1, 1, Qt::AlignRight);

        lineEdit_keyword = new QLineEdit(formWidget);
        lineEdit_keyword->setObjectName(QString::fromUtf8("lineEdit_keyword"));
        lineEdit_keyword->setMaximumSize(QSize(250, 16777215));
        lineEdit_keyword->setMaxLength(60);
        lineEdit_keyword->setInputMethodHints(Qt::ImhPreferNumbers|Qt::ImhMultiLine);

        gridLayout->addWidget(lineEdit_keyword, 3, 1, 1, 1);


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
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        label_ISBN->setText(QCoreApplication::translate("Dialog", "ISBN:", nullptr));
        label_title->setText(QCoreApplication::translate("Dialog", "Title:", nullptr));
        label_author->setText(QCoreApplication::translate("Dialog", "Author:", nullptr));
        label_keyword->setText(QCoreApplication::translate("Dialog", "Keyword:", nullptr));
        pushButton->setText(QCoreApplication::translate("Dialog", "Show", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowBookDialog: public Ui_ShowDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWBOOK_H
