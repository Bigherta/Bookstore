#pragma once
#include <QtWidgets>
#include "../ui/ui_import.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../../include/Log.hpp"

class ImportDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ImportDialog(Parser& p, UserManager& um, Log& l, QWidget* parent = nullptr)
        : QDialog(parent), parser(p), userManager(um), Logger(l)
    {
        ui.setupUi(this);
        connect(ui.pushButtonImport, &QPushButton::clicked, this, &ImportDialog::onImportClicked);
    }

private slots:
    void onImportClicked()
    {
        QString quantityStr = ui.lineEditQuantity->text();
        QString costStr = ui.lineEditCost->text();

        if (quantityStr.isEmpty() || costStr.isEmpty()) {
            QMessageBox::warning(this, "Warning", "Please enter both quantity and cost!");
            return;
        }

        bool ok1, ok2;
        int quantity = quantityStr.toInt(&ok1);
        double cost = costStr.toDouble(&ok2);

        if (!ok1 || !ok2 || quantity <= 0 || cost <= 0.0) {
            QMessageBox::critical(this, "Error", "Invalid quantity or cost!");
            return;
        }

        std::string command = "import " + std::to_string(quantity) + " " + std::to_string(cost);
        bool running = true;
        std::string result = parser.execute(command, userManager, Logger, running);

        if (result == "Invalid\n") {
            QMessageBox::critical(this, "Failed", QString::fromStdString(result));
        } else {
            ui.lineEditQuantity->clear();
            ui.lineEditCost->clear();
            accept();
        }
    }

private:
    Ui::ImportDialog ui;
    Parser& parser;
    UserManager& userManager;
    Log& Logger;
};
