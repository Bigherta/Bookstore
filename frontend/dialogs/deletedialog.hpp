#pragma once
#include <QtWidgets>
#include "../ui/ui_delete.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../../include/Log.hpp"

// 删除用户对话框
class DeleteDialog : public QDialog
{
    Q_OBJECT

public:
    // 构造函数：传入核心模块引用，避免对象拷贝
    explicit DeleteDialog(Parser& p, UserManager& um, Log& l, QWidget* parent = nullptr)
        : QDialog(parent), parser(p), userManager(um), Logger(l)
    {
        ui.setupUi(this);
        // 点击“删除”按钮时触发槽函数
        connect(ui.pushButtonDelete, &QPushButton::clicked,
                this, &DeleteDialog::onDeleteClicked);
    }

private slots:
    // 处理删除按钮点击事件
    void onDeleteClicked()
    {
        QString userID = ui.lineEditUserID->text();

        // 输入检查
        if (userID.isEmpty()) {
            QMessageBox::warning(this, "Warning", "Please enter a User ID!");
            return;
        }

        // 构造并执行 delete 命令
        std::string command = "delete " + userID.toStdString();
        bool running = true;
        std::string result = parser.execute(command, userManager, Logger, running);

        // 执行失败
        if (result == "Invalid\n") {
            QMessageBox::critical(this, "Error", "Operation not valid!");
            return;
        }

        // 执行成功，关闭对话框
        accept();
    }

private:
    Ui::DeleteDialog ui;   // 界面对象
    Parser& parser;        // 命令解析器
    UserManager& userManager; // 用户管理
    Log& Logger;           // 日志模块
};
