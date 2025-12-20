#pragma once
#include <QtWidgets>
#include "../ui/ui_passwd.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../../include/Log.hpp"

class PasswdDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PasswdDialog(Parser &p, UserManager &um, Log &l, QWidget *parent = nullptr)
        : QDialog(parent), parser(p), userManager(um), Logger(l)
    {
        ui.setupUi(this);
        connect(ui.pushButton_change, &QPushButton::clicked, this, &PasswdDialog::onChangeClicked);
    }

private slots:
    void onChangeClicked()
    {
        QString userID = ui.lineEdit_userID->text().trimmed();
        QString oldPassword = ui.lineEdit_oldPassword->text();
        QString newPassword = ui.lineEdit_newPassword->text();

        if (userID.isEmpty() || newPassword.isEmpty())
        {
            QMessageBox::warning(this, "Warning", "UserID and new password must be filled!");
            return;
        }

        std::string command = "passwd " + userID.toStdString() + " "
                              + oldPassword.toStdString() + " " + newPassword.toStdString();
        bool running = true;
        std::string result = parser.execute(command, userManager, Logger, running);

        if (result == "Invalid\n")
        {
            QMessageBox::critical(this, "Error", "Password change failed!");
        }
        else
        {
            accept();
        }
    }

private:
    Ui::PasswdDialog ui;
    Parser &parser;
    UserManager &userManager;
    Log &Logger;
};
