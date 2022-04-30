#include "umlclassnotifier.h"

UMLClassNotifier::UMLClassNotifier() : QObject()
{}

UMLClassNotifier* UMLClassNotifier::getInstance()
{
    static UMLClassNotifier* instance = new UMLClassNotifier();
    return instance;
}
