#include "mainwindow.hpp"
#include "../dialogs/buydialog.hpp"
#include "../dialogs/deletedialog.hpp"
#include "../dialogs/financedialog.hpp"
#include "../dialogs/importdialog.hpp"
#include "../dialogs/logindialog.hpp"
#include "../dialogs/modifydialog.hpp"
#include "../dialogs/passwddialog.hpp"
#include "../dialogs/registerdialog.hpp"
#include "../dialogs/reportdialog.hpp"
#include "../dialogs/selectdialog.hpp"
#include "../dialogs/showbookdialog.hpp"
#include "../dialogs/useradddialog.hpp"
#include "../dialogs/logdialog.hpp"

MainWindow::MainWindow(Parser &p, UserManager &um, Log &l, QWidget *parent) :
    QMainWindow(parent), parser(p), userManager(um), Logger(l)
{
    ui.setupUi(this);
    updateActionsByPrivilege();

    // --- User Menu ---
    connect(ui.actionLogin, &QAction::triggered, this, &MainWindow::onLogin);
    connect(ui.actionLogout, &QAction::triggered, this, &MainWindow::onLogout);
    connect(ui.actionRegister, &QAction::triggered, this, &MainWindow::onRegister);
    connect(ui.actionPasswd, &QAction::triggered, this, &MainWindow::onPasswd);
    connect(ui.actionUserAdd, &QAction::triggered, this, &MainWindow::onUserAdd);
    connect(ui.actionUserDelete, &QAction::triggered, this, &MainWindow::onUserDelete);

    // --- Book Menu ---
    connect(ui.actionBookShow, &QAction::triggered, this, &MainWindow::onBookShow);
    connect(ui.actionBookSelect, &QAction::triggered, this, &MainWindow::onBookSelect);
    connect(ui.actionBookBuy, &QAction::triggered, this, &MainWindow::onBookBuy);
    connect(ui.actionBookModify, &QAction::triggered, this, &MainWindow::onBookModify);
    connect(ui.actionBookImport, &QAction::triggered, this, &MainWindow::onBookImport);

    // --- Log Menu ---
    connect(ui.actionShowFinance, &QAction::triggered, this, &MainWindow::onShowFinance);
    connect(ui.actionReport, &QAction::triggered, this, &MainWindow::onReport);
    connect(ui.actionLogAll, &QAction::triggered, this, &MainWindow::onLogAll);

    // --- File Menu ---
    connect(ui.actionExit, &QAction::triggered, this, &QMainWindow::close);
}
void MainWindow::updateActionsByPrivilege()
{
    int privilege = 0;

    privilege = userManager.getCurrentUser().privilegeLevel;

    // --- User Menu ---
    ui.actionUserAdd->setEnabled(privilege == 7);
    ui.actionUserDelete->setEnabled(privilege == 7);
    ui.actionRegister->setEnabled(privilege >= 0);
    ui.actionPasswd->setEnabled(privilege >= 1);
    ui.actionLogin->setEnabled(true);
    ui.actionLogout->setEnabled(privilege >= 1);

    // --- Book Menu ---
    ui.actionBookShow->setEnabled(privilege >= 1);
    ui.actionBookBuy->setEnabled(privilege >= 1);
    ui.actionBookSelect->setEnabled(privilege >= 3);
    ui.actionBookModify->setEnabled(privilege >= 3);
    ui.actionBookImport->setEnabled(privilege >= 3);

    // --- Log Menu ---
    ui.actionShowFinance->setEnabled(privilege == 7);
    ui.actionReport->setEnabled(privilege == 7);
    ui.actionLogAll->setEnabled(privilege == 7);

    // --- File Menu ---
    ui.actionExit->setEnabled(true);
}


// ------------------- User Actions -------------------

void MainWindow::onLogin()
{
    LoginDialog dlg(parser, userManager, Logger, this);
    if (dlg.exec() == QDialog::Accepted)
    {
        updateActionsByPrivilege(); // 登录成功后刷新菜单
    }
}

void MainWindow::onLogout()
{
    // 构造 logout 命令
    bool running = true;
    std::string result = parser.execute("logout", userManager, Logger, running);
    updateActionsByPrivilege();
    qApp->processEvents(); // 强制处理事件，刷新 UI
}

void MainWindow::onRegister()
{
    RegisterDialog dlg(parser, userManager, Logger, this);
    dlg.exec();
}

void MainWindow::onPasswd()
{
    PasswdDialog dlg(parser, userManager, Logger, this);
    dlg.exec();
}

void MainWindow::onUserAdd()
{
    UserAddDialog dlg(parser, userManager, Logger, this);
    dlg.exec();
}

void MainWindow::onUserDelete()
{
    DeleteDialog dlg(parser, userManager, Logger, this);
    dlg.exec();
}

// ------------------- Book Actions -------------------

void MainWindow::onBookShow()
{
    ShowBookDialog dlg(parser, userManager, Logger, this);
    dlg.exec();
}

void MainWindow::onBookSelect()
{
    SelectDialog dlg(parser, userManager, Logger, this);
    dlg.exec();
}

void MainWindow::onBookBuy()
{
    BuyDialog dlg(parser, userManager, Logger, this);
    dlg.exec();
}

void MainWindow::onBookModify()
{
    ModifyDialog dlg(parser, userManager, Logger, this);
    dlg.exec();
}

void MainWindow::onBookImport()
{
    ImportDialog dlg(parser, userManager, Logger, this);
    dlg.exec();
}

// ------------------- Log Actions -------------------

void MainWindow::onShowFinance()
{
    FinanceDialog dlg(parser, userManager, Logger, this);
    dlg.exec();
}

void MainWindow::onReport()
{
    ReportDialog dlg(parser, userManager, Logger, this);
    dlg.exec();
}

void MainWindow::onLogAll()
{
    LogDialog dlg(parser, userManager, Logger, this);
    dlg.exec(); // 弹出表格对话框显示日志
}
