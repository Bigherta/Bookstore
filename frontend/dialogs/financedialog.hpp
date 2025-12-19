#include <QtWidgets>
#include "../ui/ui_finance.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../../include/Log.hpp"

class FinanceDialog : public QDialog
{
    Q_OBJECT
public:
    // 构造函数接收后端对象引用
    FinanceDialog(Parser& p, UserManager& um, Log& l, QWidget* parent = nullptr)
        : QDialog(parent), parser(p), userManager(um), Logger(l)
    {
        ui.setupUi(this);
        connect(ui.pushButton, &QPushButton::clicked, this, &FinanceDialog::onFinanceClicked);
    }

private slots:
    void onFinanceClicked() {
        QString count = ui.lineEdit->text();

        if (count.isEmpty()) {
            QMessageBox::warning(this, "Warning", "Please enter a value!");
            return;
        }

        // 构造命令
        std::string command = "show finance " + count.toStdString();
        bool running = true;

        // 调用后端执行
        std::string result = parser.execute(command, userManager, Logger, running);

        // 弹窗显示结果
        if (result == "Invalid\n") {
            QMessageBox::critical(this, "Error", "Operation not valid!");
        } else {
            QMessageBox::information(this, "Success", QString::fromStdString(result));
        }
    }

private:
    Ui::FinanceDialog ui;
    Parser& parser;
    UserManager& userManager;
    Log& Logger;
};
