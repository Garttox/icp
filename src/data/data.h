/**
 * ICP - UML Application
 * @date 1/5/2022
 * @file data.h
 * @author Martin Bednář (xbedna77)
 */

#ifndef DATA_H
#define DATA_H

#include "utils.h"

/**
 * @brief Base data class with shared functionality.
 * @author Martin Bednář (xbedna77)
 */
template <class MODEL, class CONTEXT = void>
class Data
{
public:
    virtual bool load(QJsonObject object) = 0;
    virtual void fromModel(MODEL* model) = 0;
    // virtual QJsonObject toJson() const;
    virtual MODEL* toModel(CONTEXT* context = nullptr) = 0;

};

#endif // DATA_H
