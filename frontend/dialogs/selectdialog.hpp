#pragma once
#include <QtWidgets>
#include "../ui/ui_select.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../../include/Log.hpp"

class SelectDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SelectDialog(Parser &p, UserManager &um, Log &l, QWidget *parent = nullptr) :
        QDialog(parent), parser(p), userManager(um), Logger(l)
    {
        ui.setupUi(this);
        connect(ui.pushButtonSelect, &QPushButton::clicked, this, &SelectDialog::onSelectClicked);
    }

    QString getISBN() const { return isbn; }

private slots:
    void onSelectClicked()
    {
        isbn = ui.lineEditISBN->text().trimmed();
        if (isbn.isEmpty()) {
            QMessageBox::warning(this,"Warning","ISBN cannot be empty!");
            return;
        }

        std::string command = "select " + isbn.toStdString();
        bool running = true;
        std::string result = parser.execute(command,userManager,Logger,running);

        if (result == "Invalid\n") {
            QMessageBox::critical(this,"Error","Invalid!");
            return;
        }
        accept();
    }

private:
    Ui::SelectDialog ui;
    QString isbn;
    Parser &parser;
    UserManager &userManager;
    Log &Logger;
};
