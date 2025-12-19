#include <QtWidgets>
#include "../../include/Log.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../ui/ui_register.hpp"

class RegisterDialog : public QDialog
{
    Q_OBJECT
public:
    explicit RegisterDialog(Parser &p, UserManager &um, Log &l, QWidget *parent = nullptr) :
        QDialog(parent), parser(p), userManager(um), Logger(l)
    {
        ui.setupUi(this);
        connect(ui.pushButton, &QPushButton::clicked, this, &RegisterDialog::onRegisterClicked);
    }

private slots:
    void onRegisterClicked()
    {
        QString userID = ui.lineEdit_userID->text().trimmed();
        QString password = ui.lineEdit_password->text();
        QString username = ui.lineEdit_username->text().trimmed();

        // 输入校验
        if (userID.isEmpty() || password.isEmpty() || username.isEmpty())
        {
            QMessageBox::warning(this, "Warning", "All fields must be filled!");
            return;
        }

        // 构造注册命令
        std::string command =
                "register " + userID.toStdString() + " " + password.toStdString() + " " + username.toStdString();
        bool running = true;

        // 调用后端 parser 执行
        std::string result = parser.execute(command, userManager, Logger, running);

        if (result == "Invalid\n")
        {
            QMessageBox::critical(this, "Error", "Registration failed!");
            return;
        }
        accept(); // 关闭对话框并返回 QDialog::Accepted
    }

private:
    Ui::RegisterDialog ui;
    Parser &parser;
    UserManager &userManager;
    Log &Logger;
};
