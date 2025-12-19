#include <QtWidgets>
#include "../../include/Log.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../ui/ui_passwd.hpp"

class PasswdDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PasswdDialog(Parser &p, UserManager &um, Log &l, QWidget *parent = nullptr) :
        QDialog(parent), parser(p), userManager(um), Logger(l)
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

        // 基本输入校验
        if (userID.isEmpty() || oldPassword.isEmpty() || newPassword.isEmpty())
        {
            QMessageBox::warning(this, "Warning", "All fields must be filled!");
            return;
        }

        // 构造修改密码命令
        std::string command =
                "passwd " + userID.toStdString() + " " + oldPassword.toStdString() + " " + newPassword.toStdString();
        bool running = true;

        // 调用后端 parser 执行
        std::string result = parser.execute(command, userManager, Logger, running);

        if (result == "Invalid\n")
        {
            QMessageBox::critical(this, "Error", "Password change failed!");
            return;
        }
        else
        {
            accept(); // 关闭对话框并返回 QDialog::Accepted
        }
    }

private:
    Ui::PasswdDialog ui;
    Parser &parser;
    UserManager &userManager;
    Log &Logger;
};
