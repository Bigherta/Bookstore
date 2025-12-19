#pragma once
#include <QtWidgets>
#include "../ui/ui_login.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../../include/Log.hpp"

class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LoginDialog(Parser& p, UserManager& um, Log& l, QWidget* parent = nullptr)
        : QDialog(parent), parser(p), userManager(um), Logger(l)
    {
        ui.setupUi(this);

        // 默认按 Enter 键触发登录
        ui.pushButton->setDefault(true);

        // 绑定按钮点击事件
        connect(ui.pushButton, &QPushButton::clicked, this, &LoginDialog::onLoginClicked);
    }

private slots:
    void onLoginClicked()
    {
        QString userID = ui.lineEdit_userID->text().trimmed();
        QString password = ui.lineEdit_password->text();

        if (userID.isEmpty() || password.isEmpty()) {
            QMessageBox::warning(this, "Warning", "Please enter both user ID and password!");
            return;
        }

        // 构造命令，例如：su -u userID -p password
        std::string command = "su " + userID.toStdString() + " " + password.toStdString();
        bool running = true;

        // 调用后端 parser 执行
        std::string result = parser.execute(command, userManager, Logger, running);

        if (result == "Invalid\n") {
            QMessageBox::critical(this, "Login Failed", "Invalid user ID or password!");
            return;
        }
        accept(); // 关闭对话框，返回 QDialog::Accepted
    }

private:
    Ui::LoginDialog ui;
    Parser& parser;
    UserManager& userManager;
    Log& Logger;
};
