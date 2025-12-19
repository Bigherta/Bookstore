#include <QtWidgets>
#include "../ui/ui_buy.hpp"
#include "../../include/user.hpp"
#include "../../include/Log.hpp"
#include "../../include/parser.hpp"

class BuyDialog : public QDialog
{
    Q_OBJECT
public:
    BuyDialog(Parser& p, UserManager& um, Log& l, QWidget* parent = nullptr)
        : QDialog(parent), parser(p), userManager(um), Logger(l)
    {
        ui.setupUi(this);
        connect(ui.pushButton_buy, &QPushButton::clicked, this, &BuyDialog::onBuyClicked);
    }

private slots:
    void onBuyClicked() {
        QString isbn = ui.lineEdit_isbn->text();
        QString quantity = ui.lineEdit_quantity->text();

        if (isbn.isEmpty() || quantity.isEmpty()) {
            QMessageBox::warning(this, "Warning", "Please enter ISBN and quantity!");
            return;
        }

        std::string command = "buy " + isbn.toStdString() + " " + quantity.toStdString();
        bool running = true;
        std::string result = parser.execute(command, userManager, Logger, running);

        if (result == "Invalid\n") {
            QMessageBox::critical(this, "Error", "Operation not valid!");
        } else {
            QMessageBox::information(this, "Success", QString::fromStdString(result));
        }
    }

private:
    Ui::BuyDialog ui;
    Parser& parser;
    UserManager& userManager;
    Log& Logger;
};
