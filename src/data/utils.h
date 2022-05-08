/**
 * ICP - UML Application
 * @date 1/5/2022
 * @file utils.h
 * @author Martin Bednář (xbedna77)
 */

#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>

/**
 * @brief Tuple for storing template type T or nothing.
 */
template <class T>
struct Optional {
    Optional(T value, bool ok) : value(value), ok(ok) {}
    const T value;
    const bool ok;
};

/**
 * @brief Loads list of DATA classes from JSON array.
 * @param value Reference to JSON array.
 * @return List of DATA classes.
 */
template<class DATA>
Optional<QList<DATA*>> fromJsonArray(QJsonValueRef value)
{
    QList<DATA*> list;
    if (value.isNull())
    {
        return Optional<DATA*>(list, true);
    }
    if (!value.isArray())
    {
        return Optional<DATA*>(list, false);
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
             return Optional<DATA*>(list, false);
        }
    }
    return Optional<DATA*>(list, true);
}

/**
 * @brief Loads list of DATA classes from JSON array.
 * @param value Reference to JSON array.
 * @return List of DATA classes.
 */
template<class DATA>
QJsonArray toJsonArray(QList<DATA*> list)
{
    QJsonArray array;
    foreach (auto item, list)
    {
        array.append(item->toJson());
    }
    return array;
}

/**
 * @brief Creates list of MODELs from list of DATAs.
 * @param data List of DATA classes.
 * @return List of MODEL classes.
 */
template<class DATA, class MODEL, class ARG = void>
QList<MODEL*> toModels(QList<DATA*> data, ARG* arg = nullptr)
{
    QList<MODEL*> list;
    foreach (auto item, data)
    {
        auto model = item->toModel(arg);
        list.append(model);
    }
    return list;
}

/**
 * @brief Creates list of DATAs from list of MODELs.
 * @param models List of MODEL classes.
 * @return List of DATA classes.
 */
template<class MODEL, class DATA>
QList<DATA*> fromModels(QList<MODEL*> models)
{
    QList<DATA*> list;
    foreach (auto model, models)
    {
        auto item = new DATA();
        item->fromModel(model);
        list.append(item);
    }
    return list;
}

/**
 * @brief Returns true, if any of the JSON value from given values is null.
 * @param values JSON values.
 * @return True, if has null in it, false otherwise.
 */
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
