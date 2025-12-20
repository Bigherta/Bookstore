#ifndef UI_LOGDIALOG_H
#define UI_LOGDIALOG_H

#include <QtWidgets>

QT_BEGIN_NAMESPACE

class Ui_LogDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *tableLog;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("LogDialog"));
        Dialog->resize(600, 400);
        Dialog->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);

        verticalLayout = new QVBoxLayout(Dialog);

        tableLog = new QTableWidget(Dialog);
        tableLog->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableLog->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableLog->setColumnCount(2);
        tableLog->setHorizontalHeaderLabels(QStringList() << "Type" << "Log");
        tableLog->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        tableLog->horizontalHeader()->setStretchLastSection(true);

        verticalLayout->addWidget(tableLog);

        QMetaObject::connectSlotsByName(Dialog);
    }
};

namespace Ui {
    class LogDialog : public Ui_LogDialog {};
}

QT_END_NAMESPACE

#endif // UI_LOGDIALOG_H
