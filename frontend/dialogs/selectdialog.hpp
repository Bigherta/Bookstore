#pragma once
#include <QtWidgets>
#include "../ui/ui_select.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../../include/Log.hpp"

// 选择书籍对话框
class SelectDialog : public QDialog
{
    Q_OBJECT

public:
    // 构造函数：传入核心模块引用
    explicit SelectDialog(Parser &p, UserManager &um, Log &l, QWidget *parent = nullptr) :
        QDialog(parent), parser(p), userManager(um), Logger(l)
    {
        ui.setupUi(this);
        // 点击“选择”按钮触发槽函数
        connect(ui.pushButtonSelect, &QPushButton::clicked,
                this, &SelectDialog::onSelectClicked);
    }

    // 获取用户输入的 ISBN
    QString getISBN() const { return isbn; }

private slots:
    // 处理选择操作
    void onSelectClicked()
    {
        isbn = ui.lineEditISBN->text().trimmed();

        // 输入检查
        if (isbn.isEmpty()) {
            QMessageBox::warning(this,"Warning","ISBN cannot be empty!");
            return;
        }

        // 构造并执行 select 命令
        std::string command = "select " + isbn.toStdString();
        bool running = true;
        std::string result = parser.execute(command, userManager, Logger, running);

        // 执行失败处理
        if (result == "Invalid\n") {
            QMessageBox::critical(this,"Error","Invalid!");
            return;
        }

        accept(); // 成功则关闭对话框
    }

private:
    Ui::SelectDialog ui;        // 界面对象
    QString isbn;               // 用户输入的 ISBN
    Parser &parser;             // 命令解析器
    UserManager &userManager;   // 用户管理
    Log &Logger;                // 日志模块
};
