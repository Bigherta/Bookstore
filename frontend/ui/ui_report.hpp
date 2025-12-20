#ifndef UI_REPORTDIALOG_H
#define UI_REPORTDIALOG_H

#include <QtWidgets>

QT_BEGIN_NAMESPACE

class Ui_ReportDialog
{
public:
    QVBoxLayout *verticalLayout;

    QHBoxLayout *hLayoutFinance;
    QSpacerItem *leftSpacer1;
    QPushButton *pushButtonFinance;
    QSpacerItem *rightSpacer1;

    QHBoxLayout *hLayoutEmployee;
    QSpacerItem *leftSpacer2;
    QPushButton *pushButtonEmployee;
    QSpacerItem *rightSpacer2;

    QTableWidget *tableReport; // 报表表格

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("ReportDialog"));
        Dialog->resize(500, 400); // 调整窗口大小
        Dialog->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);

        verticalLayout = new QVBoxLayout(Dialog);

        // 财务报表按钮
        hLayoutFinance = new QHBoxLayout();
        leftSpacer1 = new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum);
        hLayoutFinance->addItem(leftSpacer1);

        pushButtonFinance = new QPushButton(Dialog);
        pushButtonFinance->setMinimumSize(QSize(120, 35));
        hLayoutFinance->addWidget(pushButtonFinance);

        rightSpacer1 = new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum);
        hLayoutFinance->addItem(rightSpacer1);
        verticalLayout->addLayout(hLayoutFinance);

        // 员工报表按钮
        hLayoutEmployee = new QHBoxLayout();
        leftSpacer2 = new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum);
        hLayoutEmployee->addItem(leftSpacer2);

        pushButtonEmployee = new QPushButton(Dialog);
        pushButtonEmployee->setMinimumSize(QSize(120, 35));
        hLayoutEmployee->addWidget(pushButtonEmployee);

        rightSpacer2 = new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum);
        hLayoutEmployee->addItem(rightSpacer2);
        verticalLayout->addLayout(hLayoutEmployee);

        // 报表表格
        tableReport = new QTableWidget(Dialog);
        tableReport->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableReport->setSelectionBehavior(QAbstractItemView::SelectRows);
        verticalLayout->addWidget(tableReport);

        retranslateUi(Dialog);
        QMetaObject::connectSlotsByName(Dialog);
    }

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("ReportDialog","Report"));
        pushButtonFinance->setText(QCoreApplication::translate("ReportDialog","Finance"));
        pushButtonEmployee->setText(QCoreApplication::translate("ReportDialog","Employee"));
    }
};

namespace Ui {
    class ReportDialog: public Ui_ReportDialog {};
}

QT_END_NAMESPACE

#endif // UI_REPORTDIALOG_H
