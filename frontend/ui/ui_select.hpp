#ifndef UI_SELECT_H
#define UI_SELECT_H

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

class Ui_SelectDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *formOuterLayout;
    QSpacerItem *leftSpacer;
    QWidget *formWidget;
    QGridLayout *gridLayout;
    QLabel *label_isbn;
    QLineEdit *lineEdit_isbn;
    QSpacerItem *rightSpacer;
    QHBoxLayout *buttonLayout;
    QSpacerItem *buttonSpacerLeft;
    QPushButton *pushButton_select;
    QSpacerItem *buttonSpacerRight;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("SelectDialog"));
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
        label_isbn = new QLabel(formWidget);
        label_isbn->setObjectName(QString::fromUtf8("label_isbn"));

        gridLayout->addWidget(label_isbn, 0, 0, 1, 1, Qt::AlignRight|Qt::AlignVCenter);

        lineEdit_isbn = new QLineEdit(formWidget);
        lineEdit_isbn->setObjectName(QString::fromUtf8("lineEdit_isbn"));
        lineEdit_isbn->setMaximumSize(QSize(180, 16777215));
        lineEdit_isbn->setMaxLength(20);

        gridLayout->addWidget(lineEdit_isbn, 0, 1, 1, 1);


        formOuterLayout->addWidget(formWidget);

        rightSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formOuterLayout->addItem(rightSpacer);


        verticalLayout->addLayout(formOuterLayout);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName(QString::fromUtf8("buttonLayout"));
        buttonSpacerLeft = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        buttonLayout->addItem(buttonSpacerLeft);

        pushButton_select = new QPushButton(Dialog);
        pushButton_select->setObjectName(QString::fromUtf8("pushButton_select"));

        buttonLayout->addWidget(pushButton_select);

        buttonSpacerRight = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        buttonLayout->addItem(buttonSpacerRight);


        verticalLayout->addLayout(buttonLayout);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("SelectDialog", "Select", nullptr));
        label_isbn->setText(QCoreApplication::translate("SelectDialog", "ISBN:", nullptr));
        pushButton_select->setText(QCoreApplication::translate("SelectDialog", "Select it!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectDialog: public Ui_SelectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECT_H
