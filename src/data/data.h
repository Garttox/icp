#ifndef DATA_H
#define DATA_H

#include "utils.h"

/**
 * @brief Base data class with shared functionality.
 * @author Martin Bednář (xbedna77)
 */
template <class MODEL>
class Data
{
public:
    virtual bool load(QJsonObject object) = 0;
    virtual void fromModel(MODEL* model) = 0;
    virtual MODEL* toModel() = 0;

};

#endif // DATA_H
