#include <QApplication>
#include <QWidget>
#include "mainscreen.h"

int main(int argc, char *argv[])
{
    QApplication app (argc, argv);

    MainScreen mainScreen;
    mainScreen.show();

    return app.exec();
}
