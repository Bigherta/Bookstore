#include <QtWidgets>
#include "../ui/ui_import.hpp"  // UI 文件生成的头
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../../include/Log.hpp"

class ImportDialog : public QDialog
{
    Q_OBJECT
public:
    // 构造函数接收后端对象引用
    explicit ImportDialog(Parser& p, UserManager& um, Log& l, QWidget* parent = nullptr)
        : QDialog(parent), parser(p), userManager(um), Logger(l)
    {
        ui.setupUi(this);
        connect(ui.pushButton_import, &QPushButton::clicked,
                this, &ImportDialog::onImportClicked);
    }

private slots:
    void onImportClicked()
    {
        // 获取输入
        QString quantityStr = ui.lineEdit_quantity->text();
        QString costStr = ui.lineEdit_cost->text();

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

        // 构造命令
        std::string command = "import " + std::to_string(quantity) +
                              " " + std::to_string(cost);
        bool running = true;

        // 调用后端逻辑
        std::string result = parser.execute(command, userManager, Logger, running);

        // 显示结果
        if (result == "Invalid\n") {
            QMessageBox::critical(this, "Failed", QString::fromStdString(result));
        } else {
            ui.lineEdit_quantity->clear();
            ui.lineEdit_cost->clear();
        }
    }

private:
    Ui::ImportDialog ui;  // import.ui 生成的 UI 类
    Parser& parser;
    UserManager& userManager;
    Log& Logger;
};
