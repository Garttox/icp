/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file umlcalldragrect.h
 * @author Michal Trlica (xtrlic02)
 */
#ifndef UMLCALLDRAGRECT_H
#define UMLCALLDRAGRECT_H

#include <QObject>
#include <QGraphicsRectItem>

class UMLCall;

class UMLCallDragRect : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    UMLCallDragRect(UMLCall *parent);
};

#endif // UMLCALLDRAGRECT_H
