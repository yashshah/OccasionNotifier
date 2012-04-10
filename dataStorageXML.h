#ifndef XMLEVENTSTORE_H
#define XMLEVENTSTORE_H
#include "dataStorageInterface.h"
#include<QtXml/QDomDocument>
#include<QtXml/QDomElement>
#include<QtXml/QDomNode>

class dataStorageXML: public dataStorageInterface
{
public:
    dataStorageXML();
    bool addOccasions(QList<eventData> eventListToBeAdded);
    QList<eventData> retrieveOcassions();
    QList<QDomElement> eventToNode(QDomDocument &DomDocument, QList<eventData> eventListToBeAdded);

private:
    QDomDocument doc;
    QDomElement root;
    QFile file;
};

#endif // XMLEVENTSTORE_H
