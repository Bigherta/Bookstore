#pragma once
#include <QtWidgets>
#include "../ui/ui_showcase.hpp"

class OutcomeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit OutcomeDialog(QWidget *parent = nullptr) : QDialog(parent)
    {
        ui.setupUi(this);
    }

    void fillTable(const std::string &result)
    {
        QStringList rows = QString::fromStdString(result).split("\n", Qt::SkipEmptyParts);
        ui.tableWidget->clearContents();
        ui.tableWidget->setRowCount(rows.size());

        int columnCount = ui.tableWidget->columnCount();

        for (int i = 0; i < rows.size(); ++i)
        {
            QStringList fields = rows[i].split('\t');
            while (fields.size() < columnCount)
                fields.append("");

            for (int j = 0; j < columnCount; ++j)
            {
                auto* item = new QTableWidgetItem(fields[j].trimmed());
                item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter); // 左对齐
                ui.tableWidget->setItem(i, j, item);
            }
        }

        // 列宽等分
        QHeaderView* header = ui.tableWidget->horizontalHeader();
        header->setSectionResizeMode(QHeaderView::Stretch);

        // 行高自适应内容
        ui.tableWidget->resizeRowsToContents();
    }

private:
    Ui::OutcomeDialog ui;
};
