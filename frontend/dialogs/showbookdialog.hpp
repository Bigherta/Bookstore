#include <QtWidgets>
#include "../../include/Log.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../ui/ui_showbook.hpp"

class ShowBookDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ShowBookDialog(Parser &p, UserManager &um, Log &l, QWidget *parent = nullptr) :
        QDialog(parent), parser(p), userManager(um), Logger(l)
    {
        ui.setupUi(this);

        // 绑定按钮点击事件
        connect(ui.pushButton, &QPushButton::clicked, this, &ShowBookDialog::onShowClicked);

        // 绑定文本变化事件，实现“只能编辑一个字段”
        auto connectExclusive = [this](QLineEdit *edit) {
            connect(edit, &QLineEdit::textChanged, this,
                    [this, edit](const QString &text) { handleExclusiveEditing(edit, text); });
        };

        connectExclusive(ui.lineEdit_ISBN);
        connectExclusive(ui.lineEdit_title);
        connectExclusive(ui.lineEdit_author);
        connectExclusive(ui.lineEdit_keyword);
    }

    void setBookInfo(const QString &isbn, const QString &title, const QString &author, const QString &keyword)
    {
        ui.lineEdit_ISBN->setText(isbn);
        ui.lineEdit_title->setText(title);
        ui.lineEdit_author->setText(author);
        ui.lineEdit_keyword->setText(keyword);
    }

private slots:
    void onShowClicked()
    {
        QString isbn = ui.lineEdit_ISBN->text();
        QString title = ui.lineEdit_title->text();
        QString author = ui.lineEdit_author->text();
        QString keyword = ui.lineEdit_keyword->text();

        int count = 0;
        if (!isbn.isEmpty())
            count++;
        if (!title.isEmpty())
            count++;
        if (!author.isEmpty())
            count++;
        if (!keyword.isEmpty())
            count++;

        if (count > 1)
        {
            QMessageBox::warning(this, "Warning", "Please fill only one field!");
            return;
        }

        // 构造 show 命令
        std::string command = "show";
        if (!isbn.isEmpty())
            command += " -ISBN=" + isbn.toStdString();
        else if (!title.isEmpty())
            command += " -name=\"" + title.toStdString() + "\"";
        else if (!author.isEmpty())
            command += " -author=\"" + author.toStdString() + "\"";
        else if (!keyword.isEmpty())
            command += " -keyword=\"" + keyword.toStdString() + "\"";


        bool running = true;
        std::string result = parser.execute(command, userManager, Logger, running);

        if (result == "\n")
        {
            QMessageBox::critical(this, "Error", "No matching books found!");
        }
        else if (result == "Invalid\n")
        {
            QMessageBox::critical(this, "Error", "Too many keywords!");
        }
        else
        {
            QMessageBox::information(this, "Books", QString::fromStdString(result));
            accept(); // 关闭对话框
        }
    }

private:
    Ui::ShowBookDialog ui;
    Parser &parser;
    UserManager &userManager;
    Log &Logger;

    void handleExclusiveEditing(QLineEdit *sender, const QString &text)
    {
        QList<QLineEdit *> others = {ui.lineEdit_ISBN, ui.lineEdit_title, ui.lineEdit_author, ui.lineEdit_keyword};
        others.removeOne(sender);

        if (!text.isEmpty())
        {
            for (QLineEdit *edit: others)
            {
                edit->setReadOnly(true);
                edit->clear(); // 可选
            }
        }
        else
        {
            for (QLineEdit *edit: others)
            {
                edit->setReadOnly(false);
            }
        }
    }
};
