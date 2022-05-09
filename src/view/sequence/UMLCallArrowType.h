/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file umlcallarrowtype.h
 * @author Michal Trlica (xtrlic02)
 */
#ifndef UMLCALLARROWTYPE_H
#define UMLCALLARROWTYPE_H

/**
 * @brief Indicates type of CallArrow
 * @author Michal Trlica (xtrlic02)
 */
enum class UMLCallArrowType
{
    CALL_MESSAGE,
    RETURN_MESSAGE,
    CREATE,
    DESTROY,
};

#endif // UMLCALLARROWTYPE_H
