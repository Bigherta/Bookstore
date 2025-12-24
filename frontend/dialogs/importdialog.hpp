#pragma once
#include <QtWidgets>
#include "../ui/ui_import.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../../include/Log.hpp"

// 进货对话框，处理 import 操作
class ImportDialog : public QDialog
{
    Q_OBJECT

public:
    // 构造函数：传入核心模块引用
    explicit ImportDialog(Parser& p, UserManager& um, Log& l, QWidget* parent = nullptr)
        : QDialog(parent), parser(p), userManager(um), Logger(l)
    {
        ui.setupUi(this);
        // 点击import按钮触发槽函数
        connect(ui.pushButtonImport, &QPushButton::clicked,
                this, &ImportDialog::onImportClicked);
    }

private slots:
    // 处理按钮点击事件
    void onImportClicked()
    {
        QString quantityStr = ui.lineEditQuantity->text();
        QString costStr = ui.lineEditCost->text();

        // 输入检查
        if (quantityStr.isEmpty() || costStr.isEmpty()) {
            QMessageBox::warning(this, "Warning", "Please enter both quantity and cost!");
            return;
        }

        // 字符串转数值并校验
        bool ok1, ok2;
        int quantity = quantityStr.toInt(&ok1);
        double cost = costStr.toDouble(&ok2);

        if (!ok1 || !ok2 || quantity <= 0 || cost <= 0.0) {
            QMessageBox::critical(this, "Error", "Invalid quantity or cost!");
            return;
        }

        // 构造并执行 import 命令
        std::string command =
            "import " + std::to_string(quantity) + " " + std::to_string(cost);
        bool running = true;
        std::string result = parser.execute(command, userManager, Logger, running);

        // 执行结果处理
        if (result == "Invalid\n") {
            QMessageBox::critical(this, "Failed", QString::fromStdString(result));
        } else {
            ui.lineEditQuantity->clear();
            ui.lineEditCost->clear();
            accept();
        }
    }

private:
    Ui::ImportDialog ui;   // 界面对象
    Parser& parser;        // 命令解析器
    UserManager& userManager; // 用户管理
    Log& Logger;           // 日志模块
};
