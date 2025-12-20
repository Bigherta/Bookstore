#pragma once
#include <QtWidgets>
#include "../ui/ui_finance.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../../include/Log.hpp"

class FinanceDialog : public QDialog
{
    Q_OBJECT
public:
    explicit FinanceDialog(Parser &p, UserManager &um, Log &l, QWidget *parent = nullptr)
        : QDialog(parent), parser(p), userManager(um), Logger(l)
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

        if (result == "Invalid\n") {
            QMessageBox::critical(this, "Error", "Operation not valid!");
        }
        else if (result == "\n") {
            QDialog dlg(this);
            dlg.setWindowTitle("Special Reward!");

            QVBoxLayout *layout = new QVBoxLayout(&dlg);
            QLabel *label = new QLabel(&dlg);

            QPixmap pixmap("../frontend/image/specialreward.png");
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
            else {
                QMessageBox::warning(this, "Warning", "Image not found!");
            }
        }
        else {
            QMessageBox::information(this, "Success", QString::fromStdString(result));
        }
    }

private:
    Ui::FinanceDialog ui;
    Parser &parser;
    UserManager &userManager;
    Log &Logger;
};
