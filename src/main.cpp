/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file main.cpp
 * @author Michal Trlica (xtrlic02), Martin Bednář (xbedna77)
 */
#include "app.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    App w;
    w.show();

    return a.exec();
}
