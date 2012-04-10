#ifndef DATASTORAGECSV_H
#define DATASTORAGECSV_H
#include "dataStorageInterface.h"
#include "eventData.h"
#include <QFile>
#include <QTextStream>

class dataStorageCSV: public dataStorageInterface
{
public:
    dataStorageCSV();
    bool addOccasions(QList<eventData> eventListToBeAdded);
    QList<eventData> retrieveOcassions();

private:
    QFile file;
};

#endif // DATASTORAGECSV_H
