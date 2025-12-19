#include <QtWidgets>
#include "../../include/Log.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../ui/ui_useradd.hpp"

class UserAddDialog : public QDialog
{
    Q_OBJECT
public:
    explicit UserAddDialog(Parser &p, UserManager &um, Log &l, QWidget *parent = nullptr) :
        QDialog(parent), parser(p), userManager(um), Logger(l)
    {
        ui.setupUi(this);

        // 设置密码框为密码模式
        ui.lineEdit_password->setEchoMode(QLineEdit::Password);

        // 绑定按钮点击事件
        connect(ui.pushButton, &QPushButton::clicked, this, &UserAddDialog::onAddClicked);
    }

private slots:
    void onAddClicked()
    {
        QString userID = ui.lineEdit_userID->text().trimmed();
        QString password = ui.lineEdit_password->text();
        QString privilege = ui.lineEdit_privilege->text().trimmed();
        QString username = ui.lineEdit_username->text().trimmed();

        // 简单输入验证
        if (userID.isEmpty() || password.isEmpty() || privilege.isEmpty() || username.isEmpty())
        {
            QMessageBox::warning(this, "Warning", "All fields must be filled!");
            return;
        }

        // 限制权限输入
        if (privilege != "1" && privilege != "3")
        {
            QMessageBox::warning(this, "Warning", "Privilege must be 1 (User) or 3 (Admin)!");
            return;
        }

        // 构造 useradd 命令
        std::string command = "useradd " + userID.toStdString() + " " + password.toStdString() + " " +
                              privilege.toStdString() + " " + username.toStdString();

        bool running = true;
        std::string result = parser.execute(command, userManager, Logger, running);

        if (result == "Invalid\n")
        {
            QMessageBox::critical(this, "Error", "Failed to add user!");
            return;
        }
        accept(); // 成功后关闭对话框
    }

private:
    Ui::UseraddDialog ui;
    Parser &parser;
    UserManager &userManager;
    Log &Logger;
};
