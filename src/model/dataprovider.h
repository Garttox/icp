#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

class UMLData;

class DataProvider
{
public:
    static DataProvider& getInstance();
    void setUMLData(UMLData *umlData);
    UMLData* getUMLData();

    DataProvider(DataProvider const&) = delete;
    void operator=(DataProvider const&) = delete;
private:
    DataProvider() {}

    UMLData *umlData;
};

#endif // DATAPROVIDER_H
