#include <QtWidgets>
#include "../../include/Log.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../ui/ui_select.hpp"

class SelectDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SelectDialog(Parser &p, UserManager &um, Log &l, QWidget *parent = nullptr) :
        QDialog(parent), parser(p), userManager(um), Logger(l)
    {
        ui.setupUi(this);
        connect(ui.pushButton_select, &QPushButton::clicked, this, &SelectDialog::onSelectClicked);
    }

    QString getISBN() const { return isbn; }

private slots:
    void onSelectClicked()
    {
        // 获取用户输入的 ISBN
        isbn = ui.lineEdit_isbn->text().trimmed();
        if (isbn.isEmpty())
        {
            QMessageBox::warning(this, "Warning", "ISBN cannot be empty!");
            return;
        }

        // 构造 select 命令
        std::string command = "select " + isbn.toStdString();
        bool running = true;
        std::string result = parser.execute(command, userManager, Logger, running);

        if (result == "Invalid\n")
        {
            QMessageBox::critical(this, "Error", "Book not found or invalid!");
            return;
        }
        accept(); // 关闭对话框并返回 QDialog::Accepted
    }

private:
    Ui::SelectDialog ui;
    QString isbn;
    Parser &parser;
    UserManager &userManager;
    Log &Logger;
};
