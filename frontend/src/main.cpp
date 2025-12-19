#include <QApplication>
#include "mainwindow.hpp"
#include "../../include/Parser.hpp"
#include "../../include/user.hpp"
#include "../../include/Log.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // 初始化后端对象
    Parser parser;
    UserManager userManager;
    Log Logger;

    // 创建主窗口并传入后端对象
    MainWindow w(parser, userManager, Logger);
    w.show();

    return app.exec();
}
