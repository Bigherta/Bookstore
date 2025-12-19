#include <QtWidgets>
#include "../ui/ui_delete.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../../include/Log.hpp"

class DeleteDialog : public QDialog
{
    Q_OBJECT
public:
    // 构造函数接收后端对象引用
    DeleteDialog(Parser& p, UserManager& um, Log& l, QWidget* parent = nullptr)
        : QDialog(parent), parser(p), userManager(um), Logger(l)
    {
        ui.setupUi(this);
        connect(ui.pushButton, &QPushButton::clicked, this, &DeleteDialog::onDeleteClicked);
    }

private slots:
    void onDeleteClicked() {
        QString userID = ui.lineEdit_userID->text();

        if (userID.isEmpty()) {
            QMessageBox::warning(this, "Warning", "Please enter a User ID!");
            return;
        }

        // 构造命令
        std::string command = "delete " + userID.toStdString();
        bool running = true;

        // 调用后端执行
        std::string result = parser.execute(command, userManager, Logger, running);

        // 弹窗显示结果
        if (result == "Invalid\n") {
            QMessageBox::critical(this, "Error", "Operation not valid!");
            return;
        } 
        accept();
    }

private:
    Ui::DeleteDialog ui;
    Parser& parser;
    UserManager& userManager;
    Log& Logger;
};
