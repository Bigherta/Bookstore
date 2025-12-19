#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QMessageBox>
#include "../../include/Log.hpp"
#include "../../include/parser.hpp"
#include "../../include/user.hpp"
#include "../ui/ui_mainwindow.hpp"

// 前置声明对话框
class LoginDialog;
class RegisterDialog;
class PasswdDialog;
class UserAddDialog;
class DeleteDialog;
class ShowBookDialog;
class SelectDialog;
class BuyDialog;
class ModifyDialog;
class ImportDialog;
class FinanceDialog;
class ReportDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Parser &p, UserManager &um, Log &l, QWidget *parent = nullptr);
    ~MainWindow() = default;
    void updateActionsByPrivilege();
private slots:
    // --- User Menu ---
    void onLogin();
    void onLogout();
    void onRegister();
    void onPasswd();
    void onUserAdd();
    void onUserDelete();

    // --- Book Menu ---
    void onBookShow();
    void onBookSelect();
    void onBookBuy();
    void onBookModify();
    void onBookImport();

    // --- Log Menu ---
    void onShowFinance();
    void onReport();
    void onLogAll();

private:
    Ui::MainWindow ui; // 使用 UI 类
    Parser &parser;
    UserManager &userManager;
    Log &Logger;
};

#endif // MAINWINDOW_HPP
