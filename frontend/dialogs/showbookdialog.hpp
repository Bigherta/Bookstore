#include <QtWidgets>
#include "../../include/Log.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../ui/ui_showbook.hpp"
#include "outcomedialog.hpp"

class ShowBookDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ShowBookDialog(Parser &p, UserManager &um, Log &l, QWidget *parent = nullptr) :
        QDialog(parent), parser(p), userManager(um), Logger(l)
    {
        ui.setupUi(this);

        // 回车触发按钮
        for (auto edit: {ui.lineEditISBN, ui.lineEditTitle, ui.lineEditAuthor, ui.lineEditKeyword})
        {
            connect(edit, &QLineEdit::returnPressed, ui.pushButtonShow, &QPushButton::click);
        }

        // 单字段输入逻辑
        auto connectExclusive = [this](QLineEdit *edit) {
            connect(edit, &QLineEdit::textChanged, this,
                    [this, edit](const QString &text) { handleExclusiveEditing(edit, text); });
        };
        connectExclusive(ui.lineEditISBN);
        connectExclusive(ui.lineEditTitle);
        connectExclusive(ui.lineEditAuthor);
        connectExclusive(ui.lineEditKeyword);

        // 查询按钮
        connect(ui.pushButtonShow, &QPushButton::clicked, this, &ShowBookDialog::onShowClicked);
    }

private slots:
    void onShowClicked()
    {
        QString isbn = ui.lineEditISBN->text().trimmed();
        QString title = ui.lineEditTitle->text().trimmed();
        QString author = ui.lineEditAuthor->text().trimmed();
        QString keyword = ui.lineEditKeyword->text().trimmed();

        int count = 0;
        for (auto s: {isbn, title, author, keyword})
            if (!s.isEmpty())
                count++;
        if (count > 1)
        {
            QMessageBox::warning(this, "Warning", "Please fill No more than one field!");
            return;
        }

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

        if (result.empty() || result == "\n")
        {
            QMessageBox::critical(this, "Error", "No matching books found!");
        }
        else if (result == "Invalid\n")
        {
            QMessageBox::critical(this, "Error", "Too many keywords!");
        }
        else
        {
            OutcomeDialog dlg(this);
            dlg.setWindowTitle("Query Result");
            dlg.fillTable(result);
            dlg.exec();
        }
    }

private:
    Ui::ShowBookDialog ui;
    Parser &parser;
    UserManager &userManager;
    Log &Logger;

    void handleExclusiveEditing(QLineEdit *sender, const QString &text)
    {
        QList<QLineEdit *> others = {ui.lineEditISBN, ui.lineEditTitle, ui.lineEditAuthor, ui.lineEditKeyword};
        others.removeOne(sender);
        for (auto edit: others)
        {
            edit->setReadOnly(!text.isEmpty());
            if (!text.isEmpty())
                edit->clear();
        }
    }
};
