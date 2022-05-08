#include "umlcallmodel.h"

UMLCallModel::UMLCallModel(UMLInstanceModel *source, UMLInstanceModel *destination, UMLMethodModel *method, bool async, int duration, int atTime, UMLCallType type) :
    source(source), destination(destination), method(method), async(async), duration(duration), atTime(atTime), type(type)
{}

UMLInstanceModel *UMLCallModel::getDestination() const
{
    return destination;
}

UMLInstanceModel *UMLCallModel::getSource() const
{
    return source;
}

UMLCallType UMLCallModel::getType() const
{
    return type;
}

int UMLCallModel::getAtTime() const
{
    return atTime;
}

void UMLCallModel::setAtTime(int atTime)
{
    this->atTime = atTime;
    emit modelChanged(this);
}

UMLMethodModel *UMLCallModel::getMethod() const
{
    return method;
}

bool UMLCallModel::getAsync() const
{
    return async;
}

int UMLCallModel::getDuration() const
{
    return duration;
}

QString UMLCallModel::getDisplayMethodName() const
{
    QStringList paramList;
    foreach(UMLParameterModel *parameter, method->getParameters())
    {
        paramList.append(parameter->getType());
    }

    return QString("%1(%2) : %3").arg(method->getName(), paramList.join(", "), method->getType());
}
