/**
 * ICP - UML Application
 * @date 22/4/2022
 * @file main.cpp
 * @author Michal Trlica (xtrlic02), Martin Bednář (xbedna77)
 */
#include "app.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication qa(argc, argv);
    App app;
    app.show();
    return qa.exec();
}
