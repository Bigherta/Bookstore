#pragma once
#include <QtWidgets>
#include "../ui/ui_delete.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../../include/Log.hpp"

class DeleteDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DeleteDialog(Parser& p, UserManager& um, Log& l, QWidget* parent = nullptr)
        : QDialog(parent), parser(p), userManager(um), Logger(l)
    {
        ui.setupUi(this);
        connect(ui.pushButtonDelete, &QPushButton::clicked, this, &DeleteDialog::onDeleteClicked);
    }

private slots:
    void onDeleteClicked()
    {
        QString userID = ui.lineEditUserID->text();

        if (userID.isEmpty()) {
            QMessageBox::warning(this, "Warning", "Please enter a User ID!");
            return;
        }

        std::string command = "delete " + userID.toStdString();
        bool running = true;
        std::string result = parser.execute(command, userManager, Logger, running);

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
