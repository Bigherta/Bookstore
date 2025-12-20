#pragma once
#include <QtWidgets>
#include "../ui/ui_log.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../../include/Log.hpp"

class LogDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LogDialog(Parser& p, UserManager& um, Log& l, QWidget* parent = nullptr)
        : QDialog(parent), parser(p), userManager(um), Logger(l)
    {
        ui.setupUi(this);
        showLogs();
    }

private:
    void showLogs()
    {
        bool running = true;
        std::string result = parser.execute("log", userManager, Logger, running);

        // 清空表格
        ui.tableLog->setRowCount(0);

        // 假设日志格式每条以 \n 分割
        std::stringstream ss(result);
        std::string line;
        QString type;
        while (std::getline(ss, line))
        {
            if (line.empty()) continue;

            int row = ui.tableLog->rowCount();
            ui.tableLog->insertRow(row);

            // 简单按“System Log:” 或 “Finance Log:”开头判断类型
            QString content = QString::fromLocal8Bit(line.c_str());
            if (line.find("System Log:") != std::string::npos)
                type = "System";
            else if (line.find("Finance Log:") != std::string::npos)
                type = "Finance";

            ui.tableLog->setItem(row, 0, new QTableWidgetItem(type));
            ui.tableLog->setItem(row, 1, new QTableWidgetItem(content));
        }

        ui.tableLog->resizeColumnsToContents();
        ui.tableLog->horizontalHeader()->setStretchLastSection(true);
    }

private:
    Ui::LogDialog ui;
    Parser& parser;
    UserManager& userManager;
    Log& Logger;
};
