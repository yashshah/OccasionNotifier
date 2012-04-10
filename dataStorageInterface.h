#ifndef DATASTORAGEINTERFACE_H
#define DATASTORAGEINTERFACE_H
#include "eventData.h"
#include<QList>
#include <QFile>
class dataStorageInterface
{
public:
    virtual bool addOccasions(QList<eventData> eventListToBeAdded)=0;
    virtual QList<eventData> retrieveOcassions()=0;
    virtual ~dataStorageInterface();
    QFile file;
};

#endif // DATASTORAGEINTERFACE_H
