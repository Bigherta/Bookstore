#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

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
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(717, 495);

        // Actions
        actionLogin = new QAction(MainWindow);
        actionLogin->setObjectName(QString::fromUtf8("actionLogin"));
        actionLogout = new QAction(MainWindow);
        actionLogout->setObjectName(QString::fromUtf8("actionLogout"));
        actionRegister = new QAction(MainWindow);
        actionRegister->setObjectName(QString::fromUtf8("actionRegister"));
        actionPasswd = new QAction(MainWindow);
        actionPasswd->setObjectName(QString::fromUtf8("actionPasswd"));
        actionUserAdd = new QAction(MainWindow);
        actionUserAdd->setObjectName(QString::fromUtf8("actionUserAdd"));
        actionUserDelete = new QAction(MainWindow);
        actionUserDelete->setObjectName(QString::fromUtf8("actionUserDelete"));
        actionBookShow = new QAction(MainWindow);
        actionBookShow->setObjectName(QString::fromUtf8("actionBookShow"));
        actionBookSelect = new QAction(MainWindow);
        actionBookSelect->setObjectName(QString::fromUtf8("actionBookSelect"));
        actionBookBuy = new QAction(MainWindow);
        actionBookBuy->setObjectName(QString::fromUtf8("actionBookBuy"));
        actionBookModify = new QAction(MainWindow);
        actionBookModify->setObjectName(QString::fromUtf8("actionBookModify"));
        actionBookImport = new QAction(MainWindow);
        actionBookImport->setObjectName(QString::fromUtf8("actionBookImport"));
        actionShowFinance = new QAction(MainWindow);
        actionShowFinance->setObjectName(QString::fromUtf8("actionShowFinance"));
        actionReport = new QAction(MainWindow);
        actionReport->setObjectName(QString::fromUtf8("actionReport"));
        actionLogAll = new QAction(MainWindow);
        actionLogAll->setObjectName(QString::fromUtf8("actionLogAll"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));

        // Central widget
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);

        // Menu bar
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 717, 20));
        MainWindow->setMenuBar(menubar);

        // Menus
        menuUser = new QMenu(menubar);
        menuUser->setObjectName(QString::fromUtf8("menuUser"));
        menuBook = new QMenu(menubar);
        menuBook->setObjectName(QString::fromUtf8("menuBook"));
        menuLog = new QMenu(menubar);
        menuLog->setObjectName(QString::fromUtf8("menuLog"));
        menuExit = new QMenu(menubar);
        menuExit->setObjectName(QString::fromUtf8("menuExit"));

        // Status bar
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
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
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Cyrene's Bookstore", nullptr));
        actionLogin->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        actionLogout->setText(QCoreApplication::translate("MainWindow", "Logout", nullptr));
        actionRegister->setText(QCoreApplication::translate("MainWindow", "Register", nullptr));
        actionPasswd->setText(QCoreApplication::translate("MainWindow", "Change Password", nullptr));
        actionUserAdd->setText(QCoreApplication::translate("MainWindow", "Add User", nullptr));
        actionUserDelete->setText(QCoreApplication::translate("MainWindow", "Delete User", nullptr));
        actionBookShow->setText(QCoreApplication::translate("MainWindow", "Show Books", nullptr));
        actionBookSelect->setText(QCoreApplication::translate("MainWindow", "Select Book", nullptr));
        actionBookBuy->setText(QCoreApplication::translate("MainWindow", "Buy Book", nullptr));
        actionBookModify->setText(QCoreApplication::translate("MainWindow", "Modify Book", nullptr));
        actionBookImport->setText(QCoreApplication::translate("MainWindow", "Import Books", nullptr));
        actionShowFinance->setText(QCoreApplication::translate("MainWindow", "Show Finance", nullptr));
        actionReport->setText(QCoreApplication::translate("MainWindow", "Report", nullptr));
        actionLogAll->setText(QCoreApplication::translate("MainWindow", "Log All", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));

        menuUser->setTitle(QCoreApplication::translate("MainWindow", "User", nullptr));
        menuBook->setTitle(QCoreApplication::translate("MainWindow", "Book", nullptr));
        menuLog->setTitle(QCoreApplication::translate("MainWindow", "Log", nullptr));
        menuExit->setTitle(QCoreApplication::translate("MainWindow", "Exit", nullptr));
    }
};

namespace Ui {
    class MainWindow : public Ui_MainWindow {};
}

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
