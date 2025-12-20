#pragma once
#include <QtWidgets>
#include "../../include/Log.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../ui/ui_report.hpp"

class ReportDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ReportDialog(Parser &p, UserManager &um, Log &l, QWidget *parent = nullptr) :
        QDialog(parent), parser(p), userManager(um), Logger(l)
    {
        ui.setupUi(this);
        connect(ui.pushButtonFinance, &QPushButton::clicked, this, &ReportDialog::onFinanceClicked);
        connect(ui.pushButtonEmployee, &QPushButton::clicked, this, &ReportDialog::onEmployeeClicked);
    }

private slots:
    void onFinanceClicked() { showReport("report finance", {"Income", "Expense"}, true); }

    void onEmployeeClicked() { showReport("report employee", {"Name", "Operation"}, false); }

private:
    void showReport(const std::string &command, const QStringList &headers, bool isFinance)
    {
        bool running = true;
        std::string result = parser.execute(command, userManager, Logger, running);

        if (result == "Invalid\n")
        {
            QMessageBox::critical(this, "Error", "Failed to generate report!");
            return;
        }

        ui.tableReport->clear();
        ui.tableReport->setRowCount(0);
        ui.tableReport->setColumnCount(headers.size());
        ui.tableReport->setHorizontalHeaderLabels(headers);

        std::stringstream ss(result);
        std::string line;
        while (std::getline(ss, line))
        {
            if (line.empty())
                continue;

            int row = ui.tableReport->rowCount();
            ui.tableReport->insertRow(row);

            if (isFinance)
            {
                // 财务报表 "+收入 -支出"
                std::stringstream lineStream(line);
                std::string incomeSign, incomeVal, expenseSign, expenseVal;
                lineStream >> incomeSign >> incomeVal >> expenseSign >> expenseVal;

                auto *incomeItem = new QTableWidgetItem(QString::fromStdString(incomeSign + incomeVal));
                incomeItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
                ui.tableReport->setItem(row, 0, incomeItem);

                auto *expenseItem = new QTableWidgetItem(QString::fromStdString(expenseSign + expenseVal));
                expenseItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
                ui.tableReport->setItem(row, 1, expenseItem);
            }
            else
            {
                // 员工报表按空格分列
                std::stringstream lineStream(line);
                std::string cell;
                int col = 0;
                while (lineStream >> cell && col < headers.size())
                {
                    auto *item = new QTableWidgetItem(QString::fromStdString(cell));
                    item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
                    ui.tableReport->setItem(row, col, item);
                    col++;
                }
            }
        }

        QHeaderView *header = ui.tableReport->horizontalHeader();
        if (isFinance)
        {
            // 财务报表列宽等分
            header->setSectionResizeMode(QHeaderView::Stretch);
        }
        else
        {
            // 员工报表列宽根据内容自适应
            for (int i = 0; i < headers.size(); ++i)
            {
                header->setSectionResizeMode(i, QHeaderView::ResizeToContents);
            }
        }

        // 行高自适应内容
        ui.tableReport->resizeRowsToContents();
    }

private:
    Ui::ReportDialog ui;
    Parser &parser;
    UserManager &userManager;
    Log &Logger;
};
