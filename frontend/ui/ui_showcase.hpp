#ifndef UI_OUTCOMEDIALOG_H
#define UI_OUTCOMEDIALOG_H

#include <QtWidgets>

QT_BEGIN_NAMESPACE

class Ui_OutcomeDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTitle;
    QTableWidget *tableWidget;
    QHBoxLayout *buttonLayout;
    QSpacerItem *horizontalSpacerLeft;
    QPushButton *closeButton;
    QSpacerItem *horizontalSpacerRight;

    void setupUi(QDialog *dialog)
    {
        if (dialog->objectName().isEmpty())
            dialog->setObjectName(QStringLiteral("OutcomeDialog"));
        dialog->resize(700, 500);

        // 系统边框和标题栏
        dialog->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);

        verticalLayout = new QVBoxLayout(dialog);

        // Title
        labelTitle = new QLabel(dialog);
        labelTitle->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        labelTitle->setFont(font);
        verticalLayout->addWidget(labelTitle);

        // Table
        tableWidget = new QTableWidget(dialog);
        tableWidget->setRowCount(0);
        tableWidget->setColumnCount(6);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setAlternatingRowColors(true);
        tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        verticalLayout->addWidget(tableWidget);

        // Buttons
        buttonLayout = new QHBoxLayout();
        horizontalSpacerLeft = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        buttonLayout->addItem(horizontalSpacerLeft);

        closeButton = new QPushButton(dialog);
        closeButton->setMinimumSize(QSize(100, 30));
        buttonLayout->addWidget(closeButton);

        horizontalSpacerRight = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        buttonLayout->addItem(horizontalSpacerRight);

        verticalLayout->addLayout(buttonLayout);

        retranslateUi(dialog);

        // 关闭按钮默认关闭窗口
        QObject::connect(closeButton, &QPushButton::clicked, dialog, &QDialog::accept);

        QMetaObject::connectSlotsByName(dialog);
    }

    void retranslateUi(QDialog *dialog)
    {
        dialog->setWindowTitle(QCoreApplication::translate("OutcomeDialog", "Query Result"));
        labelTitle->setText(QCoreApplication::translate("OutcomeDialog", "Query Result"));
        tableWidget->setHorizontalHeaderLabels(QStringList()
            << QCoreApplication::translate("OutcomeDialog", "ISBN")
            << QCoreApplication::translate("OutcomeDialog", "Bookname")
            << QCoreApplication::translate("OutcomeDialog", "Author")
            << QCoreApplication::translate("OutcomeDialog", "Keywords")
            << QCoreApplication::translate("OutcomeDialog", "Price")
            << QCoreApplication::translate("OutcomeDialog", "Stock"));
        closeButton->setText(QCoreApplication::translate("OutcomeDialog", "Close"));
    }
};

namespace Ui {
    class OutcomeDialog : public Ui_OutcomeDialog {};
}

QT_END_NAMESPACE

#endif // UI_OUTCOMEDIALOG_H
