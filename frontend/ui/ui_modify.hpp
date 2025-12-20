#ifndef UI_MODIFYDIALOG_H
#define UI_MODIFYDIALOG_H

#include <QtWidgets>

QT_BEGIN_NAMESPACE

class Ui_ModifyDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *formOuterLayout;
    QSpacerItem *leftSpacer;
    QWidget *formWidget;
    QGridLayout *gridLayout;
    QLabel *labelISBN;
    QLineEdit *lineEditISBN;
    QLabel *labelTitle;
    QLineEdit *lineEditTitle;
    QLabel *labelAuthor;
    QLineEdit *lineEditAuthor;
    QLabel *labelKeyword;
    QLineEdit *lineEditKeyword;
    QSpacerItem *rightSpacer;
    QHBoxLayout *buttonLayout;
    QSpacerItem *buttonSpacerLeft;
    QPushButton *pushButtonModify;
    QSpacerItem *buttonSpacerRight;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("ModifyDialog"));
        Dialog->resize(400, 300);

        verticalLayout = new QVBoxLayout(Dialog);

        formOuterLayout = new QHBoxLayout();
        leftSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        formOuterLayout->addItem(leftSpacer);

        formWidget = new QWidget(Dialog);
        gridLayout = new QGridLayout(formWidget);
        gridLayout->setContentsMargins(0, 0, 0, 0);

        // ISBN
        labelISBN = new QLabel(formWidget);
        gridLayout->addWidget(labelISBN, 0, 0, Qt::AlignRight);
        lineEditISBN = new QLineEdit(formWidget);
        lineEditISBN->setMaximumSize(QSize(180, 16777215));
        lineEditISBN->setMaxLength(20);
        gridLayout->addWidget(lineEditISBN, 0, 1);

        // Title
        labelTitle = new QLabel(formWidget);
        gridLayout->addWidget(labelTitle, 1, 0, Qt::AlignRight);
        lineEditTitle = new QLineEdit(formWidget);
        lineEditTitle->setMaximumSize(QSize(250, 16777215));
        lineEditTitle->setMaxLength(60);
        gridLayout->addWidget(lineEditTitle, 1, 1);

        // Author
        labelAuthor = new QLabel(formWidget);
        gridLayout->addWidget(labelAuthor, 2, 0, Qt::AlignRight);
        lineEditAuthor = new QLineEdit(formWidget);
        lineEditAuthor->setMaximumSize(QSize(250, 16777215));
        lineEditAuthor->setMaxLength(60);
        gridLayout->addWidget(lineEditAuthor, 2, 1);

        // Keyword
        labelKeyword = new QLabel(formWidget);
        gridLayout->addWidget(labelKeyword, 3, 0, Qt::AlignRight);
        lineEditKeyword = new QLineEdit(formWidget);
        lineEditKeyword->setMaximumSize(QSize(250, 16777215));
        lineEditKeyword->setMaxLength(60);
        gridLayout->addWidget(lineEditKeyword, 3, 1);

        formOuterLayout->addWidget(formWidget);
        rightSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        formOuterLayout->addItem(rightSpacer);
        verticalLayout->addLayout(formOuterLayout);

        // Button
        buttonLayout = new QHBoxLayout();
        buttonSpacerLeft = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        buttonLayout->addItem(buttonSpacerLeft);

        pushButtonModify = new QPushButton(Dialog);
        buttonLayout->addWidget(pushButtonModify);

        buttonSpacerRight = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        buttonLayout->addItem(buttonSpacerRight);
        verticalLayout->addLayout(buttonLayout);

        retranslateUi(Dialog);
        pushButtonModify->setDefault(true);
        QMetaObject::connectSlotsByName(Dialog);
    }

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("ModifyDialog", "Modify"));
        labelISBN->setText(QCoreApplication::translate("ModifyDialog", "ISBN:"));
        labelTitle->setText(QCoreApplication::translate("ModifyDialog", "Title:"));
        labelAuthor->setText(QCoreApplication::translate("ModifyDialog", "Author:"));
        labelKeyword->setText(QCoreApplication::translate("ModifyDialog", "Keyword:"));
        pushButtonModify->setText(QCoreApplication::translate("ModifyDialog", "Modify"));
    }
};

namespace Ui {
    class ModifyDialog : public Ui_ModifyDialog {};
}

QT_END_NAMESPACE

#endif // UI_MODIFYDIALOG_H
