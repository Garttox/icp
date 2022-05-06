#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QJsonObject>
#include <QJsonArray>

/**
 * @brief Tuple for storing template type T or nothing.
 * @author Martin Bednář (xbedna77)
 */
template <class T>
struct Optional {
    Optional(T value, bool ok) : value(value), ok(ok) {}
    const T value;
    const bool ok;
};

template<class DATA>
Optional<QList<DATA*>> loadArray(QJsonValueRef value)
{
    QList<DATA*> list;

    if (value.isNull())
    {
        return Optional(list, true);
    }
    if (!value.isArray())
    {
        return Optional(list, false);
    }

    foreach (auto item, value.toArray())
    {
        DATA* data = new DATA();
        if (data->load(item.toObject()))
        {
            list.append(data);
        }
        else
        {
             return Optional(list, false);
        }
    }
    return Optional(list, true);
}

template<class... T>
bool hasNull(T... values)
{
    QList<QJsonValue> list = { values... };
    foreach (auto value, list)
    {
        if (value.isNull())
        {
            return true;
        }
    }
    return false;
}


#endif // UTILS_H
