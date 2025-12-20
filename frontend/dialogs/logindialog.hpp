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
        ui.pushButtonLogin->setDefault(true);

        // 绑定按钮点击事件
        connect(ui.pushButtonLogin, &QPushButton::clicked, this, &LoginDialog::onLoginClicked);
    }

private slots:
    void onLoginClicked()
    {
        QString userID = ui.lineEditUserID->text().trimmed();
        QString password = ui.lineEditPassword->text();

        if (userID.isEmpty()) {
            QMessageBox::warning(this, "Warning", "Please enter user ID!");
            return;
        }

        std::string command = "su " + userID.toStdString() + " " + password.toStdString();
        bool running = true;

        std::string result = parser.execute(command, userManager, Logger, running);

        if (result == "Invalid\n") {
            QMessageBox::critical(this, "Login Failed", "Invalid user ID or password!");
            return;
        }
        accept();
    }

private:
    Ui::LoginDialog ui;
    Parser& parser;
    UserManager& userManager;
    Log& Logger;
};
