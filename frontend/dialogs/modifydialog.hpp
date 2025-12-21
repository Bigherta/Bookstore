#pragma once
#include <QtWidgets>
#include "../ui/ui_modify.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../../include/Log.hpp"

class ModifyDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ModifyDialog(Parser &p, UserManager &um, Log &l, QWidget *parent = nullptr)
        : QDialog(parent), parser(p), userManager(um), Logger(l)
    {
        ui.setupUi(this);
        connect(ui.pushButtonModify, &QPushButton::clicked, this, &ModifyDialog::onModifyClicked);
    }

private slots:
    void onModifyClicked()
    {
        QString isbn = ui.lineEditISBN->text().trimmed();
        QString title = ui.lineEditTitle->text().trimmed();
        QString author = ui.lineEditAuthor->text().trimmed();
        QString keyword = ui.lineEditKeyword->text().trimmed();
        QString price = ui.lineEditPrice->text().trimmed();  

        // 检查至少有一个字段被修改
        if (isbn.isEmpty() && title.isEmpty() && author.isEmpty() && keyword.isEmpty() && price.isEmpty())
        {
            QMessageBox::warning(this, "Warning", "Cannot be empty!");
            return;
        }

        // 构造命令
        std::string command = "modify";
        if (!isbn.isEmpty()) command += " -ISBN=" + isbn.toStdString();
        if (!title.isEmpty()) command += " -name=\"" + title.toStdString() + "\"";
        if (!author.isEmpty()) command += " -author=\"" + author.toStdString() + "\"";
        if (!keyword.isEmpty()) command += " -keyword=\"" + keyword.toStdString() + "\"";

        // 如果价格非空，校验合法性后加入命令
        if (!price.isEmpty())
        {
            bool ok;
            double priceVal = price.toDouble(&ok);
            if (!ok || priceVal < 0)
            {
                QMessageBox::critical(this, "Error", "Price must be a non-negative number!");
                return;
            }
            command += " -price=" + std::to_string(priceVal);
        }

        bool running = true;
        std::string result = parser.execute(command, userManager, Logger, running);

        if (result == "Invalid\n")
        {
            QMessageBox::critical(this, "Error", "Operation not valid!");
        }
        else
        {
            accept();
        }
    }

private:
    Ui::ModifyDialog ui;
    Parser &parser;
    UserManager &userManager;
    Log &Logger;
};
