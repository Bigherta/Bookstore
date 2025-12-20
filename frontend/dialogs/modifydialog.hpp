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

        if (isbn.isEmpty() && title.isEmpty() && author.isEmpty() && keyword.isEmpty())
        {
            QMessageBox::warning(this, "Warning", "Cannot be empty!");
            return;
        }

        std::string command = "modify";
        if (!isbn.isEmpty()) command += " -ISBN=" + isbn.toStdString();
        if (!title.isEmpty()) command += " -name=\"" + title.toStdString() + "\"";
        if (!author.isEmpty()) command += " -author=\"" + author.toStdString() + "\"";
        if (!keyword.isEmpty()) command += " -keyword=\"" + keyword.toStdString() + "\"";

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
