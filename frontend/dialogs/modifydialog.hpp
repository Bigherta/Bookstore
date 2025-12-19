#include <QtWidgets>
#include "../ui/ui_modify.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../../include/Log.hpp"

class ModifyDialog : public QDialog
{
    Q_OBJECT
public:
    // 构造函数接收后端对象引用
    explicit ModifyDialog(Parser& p, UserManager& um, Log& l, QWidget* parent = nullptr)
        : QDialog(parent), parser(p), userManager(um), Logger(l)
    {
        ui.setupUi(this);
        connect(ui.pushButton, &QPushButton::clicked, this, &ModifyDialog::onModifyClicked);
    }

private slots:
    void onModifyClicked() {
        // 获取用户输入
        QString isbn = ui.lineEdit_ISBN->text().trimmed();
        QString title = ui.lineEdit_title->text().trimmed();
        QString author = ui.lineEdit_author->text().trimmed();
        QString keyword = ui.lineEdit_keyword->text().trimmed();

        // 基本输入校验
        if (isbn.isEmpty() && title.isEmpty() && author.isEmpty() && keyword.isEmpty()) {
            QMessageBox::warning(this, "Warning", "cannot be empty!");
            return;
        }

        // 构造命令
        std::string command = "modify";
        if (!isbn.isEmpty()) command += " -ISBN=" + isbn.toStdString();
        if (!title.isEmpty()) command += " -name=\"" + title.toStdString() + "\"";
        if (!author.isEmpty()) command += " -author=\"" + author.toStdString() + "\"";
        if (!keyword.isEmpty()) command += " -keyword=\"" + keyword.toStdString() + "\"";

        bool running = true;
        std::string result = parser.execute(command, userManager, Logger, running);

        if (result == "Invalid\n") {
            QMessageBox::critical(this, "Error", "Operation not valid!");
        } else {
            QMessageBox::information(this, "Success", QString::fromStdString(result));
            accept(); // 关闭对话框并返回 QDialog::Accepted
        }
    }

private:
    Ui::ModifyDialog ui;
    Parser& parser;
    UserManager& userManager;
    Log& Logger;
};
