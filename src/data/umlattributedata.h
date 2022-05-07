/**
 * ICP - UML Application
 * @date 1/5/2022
 * @file umlattributedata.h
 * @author Martin Bednář (xbedna77)
 */

#ifndef UMLATTRIBUTEDATA_H
#define UMLATTRIBUTEDATA_H
#include <QString>

/**
 * @brief Data class for holding UML attribute data.
 */
class UMLAttributeData
{
public:
    QString getName() const;
    QString getType() const;
    QString getAccess() const;

protected:
    QString name;
    QString type;
    QString access;


};

#endif // UMLATTRIBUTEDATA_H
