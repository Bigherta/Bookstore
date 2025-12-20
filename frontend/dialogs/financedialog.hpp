#pragma once
#include <QtWidgets>
#include "../../include/Log.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../ui/ui_finance.hpp"

class FinanceDialog : public QDialog
{
    Q_OBJECT
public:
    explicit FinanceDialog(Parser &p, UserManager &um, Log &l, QWidget *parent = nullptr) :
        QDialog(parent), parser(p), userManager(um), Logger(l)
    {
        ui.setupUi(this);
        connect(ui.pushButtonShow, &QPushButton::clicked, this, &FinanceDialog::onFinanceClicked);
    }

private slots:
    void onFinanceClicked()
    {
        QString count = ui.lineEditCount->text();
        std::string command = "show finance " + count.toStdString();
        bool running = true;
        std::string result = parser.execute(command, userManager, Logger, running);

        if (result == "Invalid\n")
        {
            QMessageBox::critical(this, "Error", "Operation not valid!");
            return;
        }
        else if (result == "\n")
        {
            QDialog dlg(this);
            dlg.setWindowTitle("Special Reward!");
            QVBoxLayout *layout = new QVBoxLayout(&dlg);
            QLabel *label = new QLabel(&dlg);

            QPixmap pixmap(":/images/specialreward.png");
            if (!pixmap.isNull())
            {
                QSize screenSize = qApp->primaryScreen()->availableSize();
                int maxWidth = screenSize.width() * 0.5;
                int maxHeight = screenSize.height() * 0.5;
                pixmap = pixmap.scaled(maxWidth, maxHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

                label->setPixmap(pixmap);
                label->setAlignment(Qt::AlignCenter);
                layout->addWidget(label);
                dlg.setLayout(layout);
                dlg.exec();
            }
            else
            {
                QMessageBox::warning(this, "Warning", "Image not found!");
            }
            return;
        }

        // ----------------------- 填充表格 -----------------------
        ui.tableFinance->clear();
        ui.tableFinance->setRowCount(0);
        ui.tableFinance->setColumnCount(2);
        QStringList headers;
        headers << "income" << "expense";
        ui.tableFinance->setHorizontalHeaderLabels(headers);
        ui.tableFinance->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui.tableFinance->setEditTriggers(QAbstractItemView::NoEditTriggers);

        std::stringstream ss(result);
        std::string line;
        while (std::getline(ss, line))
        {
            if (line.empty())
                continue;

            // 分割字符串
            std::stringstream lineStream(line);
            std::string sign1, value1, sign2, value2;
            lineStream >> sign1 >> value1 >> sign2 >> value2;

            std::string income = sign1 + value1; // "+100.00"
            std::string expense = sign2 + value2; // "-50.00"

            int row = ui.tableFinance->rowCount();
            ui.tableFinance->insertRow(row);

            ui.tableFinance->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(income)));
            ui.tableFinance->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(expense)));
        }
    }


private:
    Ui::FinanceDialog ui;
    Parser &parser;
    UserManager &userManager;
    Log &Logger;
};
