#ifndef UMLINSTANCELIFELINE_H
#define UMLINSTANCELIFELINE_H

#include <QGraphicsItem>
#include <QObject>

class UMLInstanceLifeLine : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit UMLInstanceLifeLine(QObject *parent = nullptr);

signals:

};

#endif // UMLINSTANCELIFELINE_H
