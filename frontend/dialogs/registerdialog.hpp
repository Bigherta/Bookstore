#pragma once
#include <QtWidgets>
#include "../ui/ui_register.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../../include/Log.hpp"

class RegisterDialog : public QDialog
{
    Q_OBJECT
public:
    explicit RegisterDialog(Parser &p, UserManager &um, Log &l, QWidget *parent = nullptr)
        : QDialog(parent), parser(p), userManager(um), Logger(l)
    {
        ui.setupUi(this);
        connect(ui.pushButton_register, &QPushButton::clicked, this, &RegisterDialog::onRegisterClicked);
    }

private slots:
    void onRegisterClicked()
    {
        QString userID = ui.lineEdit_userID->text().trimmed();
        QString password = ui.lineEdit_password->text();
        QString username = ui.lineEdit_username->text().trimmed();

        if(userID.isEmpty() || password.isEmpty() || username.isEmpty())
        {
            QMessageBox::warning(this,"Warning","All fields must be filled!");
            return;
        }

        std::string command = "register " + userID.toStdString() + " "
                              + password.toStdString() + " "
                              + username.toStdString();
        bool running = true;
        std::string result = parser.execute(command, userManager, Logger, running);

        if(result == "Invalid\n")
        {
            QMessageBox::critical(this,"Error","Registration failed!");
        }
        else
        {
            accept();
        }
    }

private:
    Ui::RegisterDialog ui;
    Parser &parser;
    UserManager &userManager;
    Log &Logger;
};
