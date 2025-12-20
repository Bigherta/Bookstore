#include <QtWidgets>
#include "../../include/Log.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../ui/ui_useradd.hpp"

class UserAddDialog : public QDialog
{
    Q_OBJECT
public:
    explicit UserAddDialog(Parser &p, UserManager &um, Log &l, QWidget *parent = nullptr)
        : QDialog(parent), parser(p), userManager(um), Logger(l)
    {
        ui.setupUi(this);

        // 密码框密码模式
        ui.lineEdit_password->setEchoMode(QLineEdit::Password);

        // 回车触发 Add 按钮
        for (auto edit : {ui.lineEdit_userID, ui.lineEdit_password, ui.lineEdit_privilege, ui.lineEdit_username}) {
            connect(edit, &QLineEdit::returnPressed, ui.pushButton, &QPushButton::click);
        }

        // 按钮点击事件
        connect(ui.pushButton, &QPushButton::clicked, this, &UserAddDialog::onAddClicked);
    }

private slots:
    void onAddClicked()
    {
        QString userID = ui.lineEdit_userID->text().trimmed();
        QString password = ui.lineEdit_password->text();
        QString privilege = ui.lineEdit_privilege->text().trimmed();
        QString username = ui.lineEdit_username->text().trimmed();

        if (userID.isEmpty() || password.isEmpty() || privilege.isEmpty() || username.isEmpty()) {
            QMessageBox::warning(this, "Warning", "All fields must be filled!");
            return;
        }

        if (privilege != "1" && privilege != "3") {
            QMessageBox::warning(this, "Warning", "Privilege must be 1 (User) or 3 (Admin)!");
            return;
        }

        std::string command = "useradd " + userID.toStdString() + " " + password.toStdString() + " " +
                              privilege.toStdString() + " " + username.toStdString();

        bool running = true;
        std::string result = parser.execute(command, userManager, Logger, running);

        if (result == "Invalid\n") {
            QMessageBox::critical(this, "Error", "Failed to add user!");
            return;
        }

        QMessageBox::information(this, "Success", "User added successfully!");
        accept(); // 关闭对话框
    }

private:
    Ui::UseraddDialog ui;
    Parser &parser;
    UserManager &userManager;
    Log &Logger;
};
