#pragma once
#include <QtWidgets>
#include "../../include/Log.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../ui/ui_buy.hpp"

// 购书对话框，负责处理 buy 操作
class BuyDialog : public QDialog
{
    Q_OBJECT

public:
    // 构造函数：接收核心模块的引用，避免拷贝
    explicit BuyDialog(Parser &p, UserManager &um, Log &l, QWidget *parent = nullptr)
        : QDialog(parent), parser(p), userManager(um), Logger(l)
    {
        ui.setupUi(this);
        // 点击“购买”按钮时触发 onBuyClicked
        connect(ui.pushButtonBuy, &QPushButton::clicked,
                this, &BuyDialog::onBuyClicked);
    }

private slots:
    // 处理购买按钮点击事件
    void onBuyClicked()
    {
        QString isbn = ui.lineEditISBN->text();
        QString quantity = ui.lineEditQuantity->text();

        // 输入检查
        if (isbn.isEmpty() || quantity.isEmpty())
        {
            QMessageBox::warning(this, "Warning", "Please enter ISBN and quantity!");
            return;
        }

        // 构造并执行 buy 命令
        std::string command = "buy " + isbn.toStdString() + " " + quantity.toStdString();
        bool running = true;
        std::string result = parser.execute(command, userManager, Logger, running);

        // 执行失败
        if (result == "Invalid\n")
        {
            QMessageBox::critical(this, "Error", "Operation not valid!");
            return;
        }

        // 显示总价并关闭对话框
        QMessageBox::information(this, "Total Cost", QString::fromStdString(result));
        accept();
    }

private:
    Ui::BuyDialog ui;      // 界面对象
    Parser &parser;        // 命令解析器
    UserManager &userManager; // 用户管理
    Log &Logger;           // 日志模块
};
