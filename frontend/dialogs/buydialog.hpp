#pragma once
#include <QtWidgets>
#include "../../include/Log.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../ui/ui_buy.hpp"

class BuyDialog : public QDialog
{
    Q_OBJECT
public:
    explicit BuyDialog(Parser &p, UserManager &um, Log &l, QWidget *parent = nullptr)
        : QDialog(parent), parser(p), userManager(um), Logger(l)
    {
        ui.setupUi(this);
        connect(ui.pushButtonBuy, &QPushButton::clicked, this, &BuyDialog::onBuyClicked);
    }

private slots:
    void onBuyClicked()
    {
        QString isbn = ui.lineEditISBN->text();
        QString quantity = ui.lineEditQuantity->text();

        if (isbn.isEmpty() || quantity.isEmpty())
        {
            QMessageBox::warning(this, "Warning", "Please enter ISBN and quantity!");
            return;
        }

        std::string command = "buy " + isbn.toStdString() + " " + quantity.toStdString();
        bool running = true;
        std::string result = parser.execute(command, userManager, Logger, running);

        if (result == "Invalid\n")
        {
            QMessageBox::critical(this, "Error", "Operation not valid!");
            return;
        }

        QMessageBox::information(this, "Total Cost", QString::fromStdString(result));
        accept();
    }

private:
    Ui::BuyDialog ui;
    Parser &parser;
    UserManager &userManager;
    Log &Logger;
};
