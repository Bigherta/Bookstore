#ifndef UI_SHOWBOOK_H
#define UI_SHOWBOOK_H

#include <QApplication>
#include <QDialog>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowDialog
{
public:
    QVBoxLayout *verticalLayout;

    QHBoxLayout *formOuterLayout;
    QSpacerItem *leftSpacer;
    QWidget *formWidget;
    QGridLayout *gridLayout;

    QLabel *labelISBN;
    QLineEdit *lineEditISBN; // [ISBN], 最大长度20

    QLabel *labelTitle;
    QLineEdit *lineEditTitle; // [BookName], 最大长度60

    QLabel *labelAuthor;
    QLineEdit *lineEditAuthor; // [Author], 最大长度60

    QLabel *labelKeyword;
    QLineEdit *lineEditKeyword; // [Keyword], 最大长度60

    QSpacerItem *rightSpacer;

    QHBoxLayout *buttonLayout;
    QSpacerItem *buttonSpacerLeft;
    QPushButton *pushButtonShow;
    QSpacerItem *buttonSpacerRight;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("ShowDialog"));
        Dialog->resize(400, 300);

        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        // 表单区域
        formOuterLayout = new QHBoxLayout();
        formOuterLayout->setObjectName(QString::fromUtf8("formOuterLayout"));

        leftSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        formOuterLayout->addItem(leftSpacer);

        formWidget = new QWidget(Dialog);
        formWidget->setObjectName(QString::fromUtf8("formWidget"));

        gridLayout = new QGridLayout(formWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);

        // ISBN
        labelISBN = new QLabel(formWidget);
        labelISBN->setObjectName(QString::fromUtf8("labelISBN"));
        gridLayout->addWidget(labelISBN, 0, 0, 1, 1, Qt::AlignRight);

        lineEditISBN = new QLineEdit(formWidget);
        lineEditISBN->setObjectName(QString::fromUtf8("lineEditISBN"));
        lineEditISBN->setMaximumSize(QSize(180, 16777215));
        lineEditISBN->setMaxLength(20);
        gridLayout->addWidget(lineEditISBN, 0, 1, 1, 1);

        // Book Name
        labelTitle = new QLabel(formWidget);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
        gridLayout->addWidget(labelTitle, 1, 0, 1, 1, Qt::AlignRight);

        lineEditTitle = new QLineEdit(formWidget);
        lineEditTitle->setObjectName(QString::fromUtf8("lineEditTitle"));
        lineEditTitle->setMaximumSize(QSize(250, 16777215));
        lineEditTitle->setMaxLength(60);
        gridLayout->addWidget(lineEditTitle, 1, 1, 1, 1);

        // Author
        labelAuthor = new QLabel(formWidget);
        labelAuthor->setObjectName(QString::fromUtf8("labelAuthor"));
        gridLayout->addWidget(labelAuthor, 2, 0, 1, 1, Qt::AlignRight);

        lineEditAuthor = new QLineEdit(formWidget);
        lineEditAuthor->setObjectName(QString::fromUtf8("lineEditAuthor"));
        lineEditAuthor->setMaximumSize(QSize(250, 16777215));
        lineEditAuthor->setMaxLength(60);
        gridLayout->addWidget(lineEditAuthor, 2, 1, 1, 1);

        // Keyword
        labelKeyword = new QLabel(formWidget);
        labelKeyword->setObjectName(QString::fromUtf8("labelKeyword"));
        gridLayout->addWidget(labelKeyword, 3, 0, 1, 1, Qt::AlignRight);

        lineEditKeyword = new QLineEdit(formWidget);
        lineEditKeyword->setObjectName(QString::fromUtf8("lineEditKeyword"));
        lineEditKeyword->setMaximumSize(QSize(250, 16777215));
        lineEditKeyword->setMaxLength(60);
        gridLayout->addWidget(lineEditKeyword, 3, 1, 1, 1);

        formOuterLayout->addWidget(formWidget);

        rightSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        formOuterLayout->addItem(rightSpacer);

        verticalLayout->addLayout(formOuterLayout);

        // 按钮区域
        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName(QString::fromUtf8("buttonLayout"));

        buttonSpacerLeft = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        buttonLayout->addItem(buttonSpacerLeft);

        pushButtonShow = new QPushButton(Dialog);
        pushButtonShow->setObjectName(QString::fromUtf8("pushButtonShow"));
        pushButtonShow->setMinimumSize(QSize(100, 30));
        pushButtonShow->setDefault(true);
        buttonLayout->addWidget(pushButtonShow);

        buttonSpacerRight = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        buttonLayout->addItem(buttonSpacerRight);

        verticalLayout->addLayout(buttonLayout);

        retranslateUi(Dialog);
        QMetaObject::connectSlotsByName(Dialog);
    }

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("ShowDialog", "Show Books", nullptr));
        labelISBN->setText(QCoreApplication::translate("ShowDialog", "ISBN:", nullptr));
        labelTitle->setText(QCoreApplication::translate("ShowDialog", "Title:", nullptr));
        labelAuthor->setText(QCoreApplication::translate("ShowDialog", "Author:", nullptr));
        labelKeyword->setText(QCoreApplication::translate("ShowDialog", "Keyword:", nullptr));
        pushButtonShow->setText(QCoreApplication::translate("ShowDialog", "Show", nullptr));
    }
};

namespace Ui {
    class ShowBookDialog: public Ui_ShowDialog {};
}

QT_END_NAMESPACE

#endif // UI_SHOWBOOK_H
