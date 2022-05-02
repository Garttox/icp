/**
 * ICP - UML Application
 * @date 25/4/2022
 * @file umlclassnotifier.cpp
 * @author Martin Bednář (xbedna77)
 */

#include "umlclassnotifier.h"

UMLClassNotifier::UMLClassNotifier() : QObject()
{}

UMLClassNotifier* UMLClassNotifier::getInstance()
{
    static UMLClassNotifier* instance = new UMLClassNotifier();
    return instance;
}
