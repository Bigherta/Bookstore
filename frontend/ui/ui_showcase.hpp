#ifndef UI_SHOWCASE_H
#define UI_SHOWCASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Outcome
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTitle;
    QTableWidget *tableWidget;
    QHBoxLayout *buttonLayout;
    QSpacerItem *horizontalSpacerLeft;
    QPushButton *closeButton;
    QSpacerItem *horizontalSpacerRight;

    void setupUi(QDialog *Outcome)
    {
        if (Outcome->objectName().isEmpty())
            Outcome->setObjectName(QString::fromUtf8("Outcome"));
        Outcome->resize(700, 500);

        verticalLayout = new QVBoxLayout(Outcome);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        // Title
        labelTitle = new QLabel(Outcome);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
        labelTitle->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        labelTitle->setFont(font);
        verticalLayout->addWidget(labelTitle);

        // Table
        tableWidget = new QTableWidget(Outcome);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setRowCount(6);       // 初始行数
        tableWidget->setColumnCount(6);    // 6 列
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

        // 表头自适应列宽
        tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        tableWidget->horizontalHeader()->setVisible(true);
        tableWidget->verticalHeader()->setVisible(true);

        verticalLayout->addWidget(tableWidget);

        // Buttons
        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName(QString::fromUtf8("buttonLayout"));

        horizontalSpacerLeft = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        buttonLayout->addItem(horizontalSpacerLeft);

        closeButton = new QPushButton(Outcome);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        buttonLayout->addWidget(closeButton);

        horizontalSpacerRight = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        buttonLayout->addItem(horizontalSpacerRight);

        verticalLayout->addLayout(buttonLayout);

        retranslateUi(Outcome);

        // 关闭按钮默认关闭窗口
        QObject::connect(closeButton, &QPushButton::clicked, Outcome, &QDialog::accept);

        QMetaObject::connectSlotsByName(Outcome);
    } // setupUi

    void retranslateUi(QDialog *Outcome)
    {
        Outcome->setWindowTitle(QCoreApplication::translate("Outcome", "Query Result", nullptr));
        labelTitle->setText(QCoreApplication::translate("Outcome", "Query Result", nullptr));
        tableWidget->setHorizontalHeaderLabels(QStringList()
            << QCoreApplication::translate("Outcome", "ISBN", nullptr)
            << QCoreApplication::translate("Outcome", "Bookname", nullptr)
            << QCoreApplication::translate("Outcome", "Author", nullptr)
            << QCoreApplication::translate("Outcome", "Keywords", nullptr)
            << QCoreApplication::translate("Outcome", "Price", nullptr)
            << QCoreApplication::translate("Outcome", "Stock", nullptr));
        closeButton->setText(QCoreApplication::translate("Outcome", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Outcome: public Ui_Outcome {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWCASE_H
