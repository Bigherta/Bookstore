#pragma once
#include <QtWidgets>
#include "../ui/ui_report.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../../include/Log.hpp"

class ReportDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ReportDialog(Parser& p, UserManager& um, Log& l, QWidget* parent = nullptr)
        : QDialog(parent), parser(p), userManager(um), Logger(l)
    {
        ui.setupUi(this);
        connect(ui.pushButtonFinance, &QPushButton::clicked, this, &ReportDialog::onFinanceClicked);
        connect(ui.pushButtonEmployee, &QPushButton::clicked, this, &ReportDialog::onEmployeeClicked);
    }

private slots:
    void onFinanceClicked() {
        std::string command = "report finance";
        bool running = true;
        std::string result = parser.execute(command, userManager, Logger, running);

        if (result == "Invalid\n") {
            QMessageBox::critical(this,"Error","Failed to generate finance report!");
        } else {
            QMessageBox::information(this,"Finance Report",QString::fromStdString(result));
        }
    }

    void onEmployeeClicked() {
        std::string command = "report employee";
        bool running = true;
        std::string result = parser.execute(command, userManager, Logger, running);

        if (result == "Invalid\n") {
            QMessageBox::critical(this,"Error","Failed to generate employee report!");
        } else {
            QMessageBox::information(this,"Employee Report",QString::fromStdString(result));
        }
    }

private:
    Ui::ReportDialog ui;
    Parser& parser;
    UserManager& userManager;
    Log& Logger;
};
