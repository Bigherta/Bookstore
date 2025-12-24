#pragma once
#include <QtWidgets>
#include "../ui/ui_passwd.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../../include/Log.hpp"

// 修改密码对话框
class PasswdDialog : public QDialog
{
    Q_OBJECT

public:
    // 构造函数：传入核心模块引用
    explicit PasswdDialog(Parser &p, UserManager &um, Log &l, QWidget *parent = nullptr)
        : QDialog(parent), parser(p), userManager(um), Logger(l)
    {
        ui.setupUi(this);
        // 点击“修改密码”按钮触发槽函数
        connect(ui.pushButton_change, &QPushButton::clicked,
                this, &PasswdDialog::onChangeClicked);
    }

private slots:
    // 处理修改密码操作
    void onChangeClicked()
    {
        QString userID = ui.lineEdit_userID->text().trimmed();
        QString oldPassword = ui.lineEdit_oldPassword->text();
        QString newPassword = ui.lineEdit_newPassword->text();

        // 必填项检查
        if (userID.isEmpty() || newPassword.isEmpty())
        {
            QMessageBox::warning(this, "Warning", "UserID and new password must be filled!");
            return;
        }

        // 构造并执行 passwd 命令
        std::string command = "passwd " + userID.toStdString() + " "
                              + oldPassword.toStdString() + " " + newPassword.toStdString();
        bool running = true;
        std::string result = parser.execute(command, userManager, Logger, running);

        // 执行结果处理
        if (result == "Invalid\n")
        {
            QMessageBox::critical(this, "Error", "Password change failed!");
        }
        else
        {
            accept(); // 成功则关闭对话框
        }
    }

private:
    Ui::PasswdDialog ui;      // 界面对象
    Parser &parser;           // 命令解析器
    UserManager &userManager; // 用户管理
    Log &Logger;              // 日志模块
};
