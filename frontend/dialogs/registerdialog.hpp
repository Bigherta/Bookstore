#pragma once
#include <QtWidgets>
#include "../ui/ui_register.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../../include/Log.hpp"

// 注册用户对话框
class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    // 构造函数：传入核心模块引用
    explicit RegisterDialog(Parser &p, UserManager &um, Log &l, QWidget *parent = nullptr)
        : QDialog(parent), parser(p), userManager(um), Logger(l)
    {
        ui.setupUi(this);
        // 点击“注册”按钮触发槽函数
        connect(ui.pushButton_register, &QPushButton::clicked,
                this, &RegisterDialog::onRegisterClicked);
    }

private slots:
    // 处理注册操作
    void onRegisterClicked()
    {
        QString userID = ui.lineEdit_userID->text().trimmed();
        QString password = ui.lineEdit_password->text();
        QString username = ui.lineEdit_username->text().trimmed();

        // 必填项检查
        if(userID.isEmpty() || password.isEmpty() || username.isEmpty())
        {
            QMessageBox::warning(this,"Warning","All fields must be filled!");
            return;
        }

        // 构造并执行 register 命令
        std::string command = "register " + userID.toStdString() + " "
                              + password.toStdString() + " "
                              + username.toStdString();
        bool running = true;
        std::string result = parser.execute(command, userManager, Logger, running);

        // 执行结果处理
        if(result == "Invalid\n")
        {
            QMessageBox::critical(this,"Error","Registration failed!");
        }
        else
        {
            accept(); // 成功则关闭对话框
        }
    }

private:
    Ui::RegisterDialog ui;      // 界面对象
    Parser &parser;             // 命令解析器
    UserManager &userManager;   // 用户管理
    Log &Logger;                // 日志模块
};
