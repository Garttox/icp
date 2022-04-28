#include "umlclassnotifier.h"

UMLClassNotifier::UMLClassNotifier(QObject *parent)
    : QObject(parent)
{}

UMLClassNotifier* UMLClassNotifier::getInstance()
{
    static UMLClassNotifier* instance = new UMLClassNotifier();
    return instance;
}
