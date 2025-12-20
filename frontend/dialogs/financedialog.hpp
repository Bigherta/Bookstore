#include <QtWidgets>
#include "../../include/Log.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../ui/ui_finance.hpp"

class FinanceDialog : public QDialog
{
    Q_OBJECT
public:
    // 构造函数接收后端对象引用
    FinanceDialog(Parser &p, UserManager &um, Log &l, QWidget *parent = nullptr) :
        QDialog(parent), parser(p), userManager(um), Logger(l)
    {
        ui.setupUi(this);
        connect(ui.pushButton, &QPushButton::clicked, this, &FinanceDialog::onFinanceClicked);
    }

private slots:
    void onFinanceClicked()
    {
        QString count = ui.lineEdit->text();
        
        // 构造命令
        std::string command = "show finance " + count.toStdString();
        bool running = true;

        // 调用后端执行
        std::string result = parser.execute(command, userManager, Logger, running);

        // 弹窗显示结果
        if (result == "Invalid\n")
        {
            QMessageBox::critical(this, "Error", "Operation not valid!");
        }
        else if (result == "\n")
        {
            QDialog dlg(this);
            dlg.setWindowTitle("Special Reward!");

            QVBoxLayout *layout = new QVBoxLayout(&dlg);
            QLabel *label = new QLabel(&dlg);

            QPixmap pixmap("../image/specialreward.png");
            if (!pixmap.isNull())
            {
                // 获取屏幕大小
                QSize screenSize = qApp->primaryScreen()->availableSize();
                int maxWidth = screenSize.width() * 0.5; // 图片最大宽度为屏幕宽度的一半
                int maxHeight = screenSize.height() * 0.5; // 图片最大高度为屏幕高度的一半

                // 等比缩放
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
        }
        else
        {
            QMessageBox::information(this, "Success", QString::fromStdString(result));
        }
    }

private:
    Ui::FinanceDialog ui;
    Parser &parser;
    UserManager &userManager;
    Log &Logger;
};
