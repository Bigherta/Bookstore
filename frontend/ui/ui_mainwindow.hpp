#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtWidgets>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    // Actions
    QAction *actionLogin;
    QAction *actionLogout;
    QAction *actionRegister;
    QAction *actionPasswd;
    QAction *actionUserAdd;
    QAction *actionUserDelete;
    QAction *actionBookShow;
    QAction *actionBookSelect;
    QAction *actionBookBuy;
    QAction *actionBookModify;
    QAction *actionBookImport;
    QAction *actionShowFinance;
    QAction *actionReport;
    QAction *actionLogAll;
    QAction *actionExit;

    // Widgets
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuUser;
    QMenu *menuBook;
    QMenu *menuLog;
    QMenu *menuExit;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(717, 495);

        // Actions
        actionLogin = new QAction(MainWindow);
        actionLogout = new QAction(MainWindow);
        actionRegister = new QAction(MainWindow);
        actionPasswd = new QAction(MainWindow);
        actionUserAdd = new QAction(MainWindow);
        actionUserDelete = new QAction(MainWindow);
        actionBookShow = new QAction(MainWindow);
        actionBookSelect = new QAction(MainWindow);
        actionBookBuy = new QAction(MainWindow);
        actionBookModify = new QAction(MainWindow);
        actionBookImport = new QAction(MainWindow);
        actionShowFinance = new QAction(MainWindow);
        actionReport = new QAction(MainWindow);
        actionLogAll = new QAction(MainWindow);
        actionExit = new QAction(MainWindow);

        // Central widget
        centralwidget = new QWidget(MainWindow);
        MainWindow->setCentralWidget(centralwidget);

        // Menu bar
        menubar = new QMenuBar(MainWindow);
        MainWindow->setMenuBar(menubar);

        // Menus
        menuUser = new QMenu(menubar);
        menuBook = new QMenu(menubar);
        menuLog = new QMenu(menubar);
        menuExit = new QMenu(menubar);

        // Status bar
        statusbar = new QStatusBar(MainWindow);
        MainWindow->setStatusBar(statusbar);

        // Menu order: User | Book | Log | Exit
        menubar->addAction(menuUser->menuAction());
        menubar->addAction(menuBook->menuAction());
        menubar->addAction(menuLog->menuAction());
        menubar->addAction(menuExit->menuAction());

        // Exit menu
        menuExit->addAction(actionExit);

        // User menu
        menuUser->addAction(actionLogin);
        menuUser->addAction(actionLogout);
        menuUser->addSeparator();
        menuUser->addAction(actionRegister);
        menuUser->addAction(actionPasswd);
        menuUser->addSeparator();
        menuUser->addAction(actionUserAdd);
        menuUser->addAction(actionUserDelete);

        // Book menu
        menuBook->addAction(actionBookShow);
        menuBook->addAction(actionBookSelect);
        menuBook->addSeparator();
        menuBook->addAction(actionBookBuy);
        menuBook->addAction(actionBookModify);
        menuBook->addSeparator();
        menuBook->addAction(actionBookImport);

        // Log menu
        menuLog->addAction(actionShowFinance);
        menuLog->addAction(actionReport);
        menuLog->addAction(actionLogAll);

        retranslateUi(MainWindow);
        QMetaObject::connectSlotsByName(MainWindow);
    }

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Cyrene's Bookstore"));
        actionLogin->setText(QCoreApplication::translate("MainWindow", "Login"));
        actionLogout->setText(QCoreApplication::translate("MainWindow", "Logout"));
        actionRegister->setText(QCoreApplication::translate("MainWindow", "Register"));
        actionPasswd->setText(QCoreApplication::translate("MainWindow", "Change Password"));
        actionUserAdd->setText(QCoreApplication::translate("MainWindow", "Add User"));
        actionUserDelete->setText(QCoreApplication::translate("MainWindow", "Delete User"));
        actionBookShow->setText(QCoreApplication::translate("MainWindow", "Show Books"));
        actionBookSelect->setText(QCoreApplication::translate("MainWindow", "Select Book"));
        actionBookBuy->setText(QCoreApplication::translate("MainWindow", "Buy Book"));
        actionBookModify->setText(QCoreApplication::translate("MainWindow", "Modify Book"));
        actionBookImport->setText(QCoreApplication::translate("MainWindow", "Import Books"));
        actionShowFinance->setText(QCoreApplication::translate("MainWindow", "Show Finance"));
        actionReport->setText(QCoreApplication::translate("MainWindow", "Report"));
        actionLogAll->setText(QCoreApplication::translate("MainWindow", "Log All"));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Confirm"));

        menuUser->setTitle(QCoreApplication::translate("MainWindow", "User"));
        menuBook->setTitle(QCoreApplication::translate("MainWindow", "Book"));
        menuLog->setTitle(QCoreApplication::translate("MainWindow", "Log"));
        menuExit->setTitle(QCoreApplication::translate("MainWindow", "Exit"));
    }
};

namespace Ui {
    class MainWindow : public Ui_MainWindow {};
}

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
